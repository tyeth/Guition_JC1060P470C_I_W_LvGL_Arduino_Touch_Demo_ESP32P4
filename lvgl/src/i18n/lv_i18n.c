#include "./lv_i18n.h"


////////////////////////////////////////////////////////////////////////////////
// Define plural operands
// http://unicode.org/reports/tr35/tr35-numbers.html#Operands

// Integer version, simplified

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static lv_i18n_phrase_t en_gb_singulars[] = {
    {"greeting", "Hello world!"},
    {"options", "Option 1\nOption 2\nOption 3"},
    {"long_text", "This is a long text"},
    {"Cancel\\nChanges", "Cancel\\nChanges"},
    {"Save\\nChanges", "Save\\nChanges"},
    {"Locale Settings", "Locale Settings"},
    {"Scan WiFi", "Scan WiFi"},
    {"Adafruit IO Details", "Adafruit IO Details"},
    {"Hello, world!", "Hello, world!"},
    {"WiFi Details", "WiFi Details"},
    {NULL, NULL} // End mark
};



static uint8_t en_gb_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_gb_lang = {
    .locale_name = "en-GB",
    .singulars = en_gb_singulars,

    .locale_plural_fn = en_gb_plural_fn
};

static lv_i18n_phrase_t hr_hr_singulars[] = {
    {"greeting", "Pozdrav svijete!"},
    {"options", "Opcija 1\nOpcija 2\nOpcija 3"},
    {"long_text", "Ovo je dugacak tekst"},
    {"Cancel\\nChanges", "Otkaži \\ nchanges"},
    {"Save\\nChanges", "Spremi \\ Promjene"},
    {"Locale Settings", "Postavke lokaliteta"},
    {"Scan WiFi", "Skeni wifi"},
    {"Adafruit IO Details", "Adafruit io detalje"},
    {"Hello, world!", "Pozdrav, svijet!"},
    {"WiFi Details", "Pojedinosti o WiFi"},
    {NULL, NULL} // End mark
};



static uint8_t hr_hr_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t v = op_v(n); UNUSED(v);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t f = op_f(n); UNUSED(f);
    uint32_t i10 = i % 10;
    uint32_t i100 = i % 100;
    uint32_t f10 = f % 10;
    uint32_t f100 = f % 100;
    if ((v == 0 && i10 == 1 && i100 != 11) || (f10 == 1 && f100 != 11)) return LV_I18N_PLURAL_TYPE_ONE;
    if ((v == 0 && (2 <= i10 && i10 <= 4) && (!(12 <= i100 && i100 <= 14))) || ((2 <= f10 && f10 <= 4) && (!(12 <= f100 && f100 <= 14)))) return LV_I18N_PLURAL_TYPE_FEW;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t hr_hr_lang = {
    .locale_name = "hr-HR",
    .singulars = hr_hr_singulars,

    .locale_plural_fn = hr_hr_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &en_gb_lang,
    &hr_hr_lang,
    NULL // End mark
};

////////////////////////////////////////////////////////////////////////////////


// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
 * Reset internal state. For testing.
 */
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
 * Set the languages for internationalization
 * @param langs pointer to the array of languages. (Last element has to be `NULL`)
 */
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
    if(langs == NULL) return -1;
    if(langs[0] == NULL) return -1;

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
 * Change the localization (language)
 * @param l_name name of the translation locale to use. E.g. "en-GB"
 */
int lv_i18n_set_locale(const char * l_name)
{
    if(current_lang_pack == NULL) return -1;

    uint16_t i;

    for(i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
    uint16_t i;
    for(i = 0; trans[i].msg_id != NULL; i++) {
        if(strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if(trans[i].translation) return trans[i].translation;
        }
    }

    return NULL;
}


/**
 * Get the translation from a message ID
 * @param msg_id message ID
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text(const char * msg_id)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;

    // Search in current locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    return msg_id;
}

/**
 * Get the translation from a message ID and apply the language's plural rule to get correct form
 * @param msg_id message ID
 * @param num an integer to select the correct plural form
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    return msg_id;
}

/**
 * Get the name of the currently used locale.
 * @return name of the currently used locale. E.g. "en-GB"
 */
const char * lv_i18n_get_current_locale(void)
{
    if(!current_lang) return NULL;
    return current_lang->locale_name;
}
