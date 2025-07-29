import asyncio
import re
import yaml
import os

# import pdb; pdb.set_trace()  # Debugging breakpoint

# Set current working directory to the script's directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# --- CONFIG ---
SCREENS_FILE = r'..\ui\screens.c'
I18N_DIR = '.'
LANG_FILES = ['en-GB.yml', 'hr-HR.yml']  # Add more as needed
default_lang = LANG_FILES[0]  # Default language code

def extract_strings_from_file(filename):
    with open(filename, encoding='utf-8') as f:
        content = f.read()
    # Match _("...") or _('...')
    return set(re.findall(r'_\(\s*"(.*?)"\s*\)', content) + re.findall(r"_\(\s*'(.*?)'\s*\)", content))

def load_yaml(filepath):
    if not os.path.exists(filepath):
        return {}
    with open(filepath, encoding='utf-8') as f:
        return yaml.safe_load(f) or {}

class QuotedStr(str): pass

def quoted_presenter(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='"')

yaml.add_representer(QuotedStr, quoted_presenter)

class SingleQuotedStr(str): pass

def single_quoted_presenter(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style="'")

yaml.add_representer(SingleQuotedStr, single_quoted_presenter)

def save_yaml(filepath, data):
    # Recursively wrap all keys in SingleQuotedStr and all values in QuotedStr
    def wrap_quotes(obj):
        if isinstance(obj, dict):
            return {SingleQuotedStr(k): wrap_quotes(v) for k, v in obj.items()}
        elif isinstance(obj, str):
            return QuotedStr(obj)
        return obj
    data = wrap_quotes(data)
    with open(filepath, 'w', encoding='utf-8') as f:
        yaml.dump(data, f, allow_unicode=True, sort_keys=False)


async def async_translate_text(text, target_lang):
    tgt = target_lang.split('-')[0].lower()
    try:
        from googletrans import Translator as AsyncTranslator
        translator = AsyncTranslator()
        result = await translator.translate(text, dest=tgt)
        return result.text
    except Exception as e:
        print(f"Translation failed for '{text}' to '{target_lang}': {e}")
        return text

def translate_text(text, target_lang):
    return asyncio.run(async_translate_text(text, target_lang))

def update_i18n_files(strings, i18n_dir, lang_files):
    for lang_file in lang_files:
        lang_path = os.path.join(i18n_dir, lang_file)
        lang_code = os.path.splitext(lang_file)[0]
        data = load_yaml(lang_path)
        if lang_code not in data:
            data[lang_code] = {}
        updated = False
        for s in strings:
            old_s = s
            # s = re.sub(r'[^a-z_]','',re.sub(r'\s+','_',s.lower().replace('\\n','_')))
            if s not in data[lang_code] or data[default_lang][s] != old_s:
                print(f"Using key {s} for '{old_s}' in {lang_file}")
                if lang_code == default_lang:
                    data[lang_code][s] = old_s
                else:
                    data[lang_code][s] = translate_text(old_s, lang_code)
                updated = True
        if updated:
            print(f"Updating {lang_file}")
            save_yaml(lang_path, data)
        else:
            print(f"No changes for {lang_file}")

if __name__ == '__main__':
    strings = extract_strings_from_file(SCREENS_FILE)
    update_i18n_files(strings, I18N_DIR, LANG_FILES)

    print("All i18n files updated successfully. Now run:\n" \
    "npx lv_i18n compile -t './*.yml' -o '.' \n" \
    " to compile the translations.")