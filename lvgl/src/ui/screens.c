#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include "i18n/lv_i18n.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_settings_txt_dashboard(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 37, 0, e);
    }
}

static void event_handler_cb_settings_txt_username(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 40, 0, e);
    }
}

static void event_handler_cb_settings_txt_key(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 42, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    lv_obj_set_style_bg_image_src(obj, &img_bg_solar, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 292, 102);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_ofs_x(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_ofs_y(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, _("Hello, world!"));
        }
        {
            // btn_matrix_homepage
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.btn_matrix_homepage = obj;
            lv_obj_set_pos(obj, 9, 350);
            lv_obj_set_size(obj, 240, 240);
            static const char *map[4] = {
                "Settings",
                "\n",
                "Dashboard #1",
                NULL,
            };
            static lv_buttonmatrix_ctrl_t ctrl_map[2] = {
                1 | LV_BUTTONMATRIX_CTRL_CUSTOM_1,
                1,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_buttonmatrix_set_ctrl_map(obj, ctrl_map);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 6, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 127, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xffd1d1d1), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 79, 205);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            // keybrd
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keybrd = obj;
            lv_obj_set_pos(obj, 0, 300);
            lv_obj_set_size(obj, 1024, 300);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // menu_bar_settings
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.menu_bar_settings = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // tabview_settings
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.tabview_settings = obj;
            lv_obj_set_pos(obj, 0, 38);
            lv_obj_set_size(obj, 1024, 262);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
            lv_tabview_set_tab_bar_size(obj, 32);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tab_settings_wifi
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, _("WiFi Details"));
                    objects.tab_settings_wifi = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // btn_wifi_cancel
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_wifi_cancel = obj;
                            lv_obj_set_pos(obj, -7, 140);
                            lv_obj_set_size(obj, 148, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_cancel_wifi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_cancel_wifi = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, _("Cancel\nChanges"));
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -4, 9);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, _("SSID"));
                        }
                        {
                            // password
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.password = obj;
                            lv_obj_set_pos(obj, 109, 72);
                            lv_obj_set_size(obj, 371, 53);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, true);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -6, 80);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, _("PASS"));
                        }
                        {
                            // ssid
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.ssid = obj;
                            lv_obj_set_pos(obj, 109, 1);
                            lv_obj_set_size(obj, 371, 53);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                        }
                        {
                            // btn_save_wifi
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_save_wifi = obj;
                            lv_obj_set_pos(obj, 155, 140);
                            lv_obj_set_size(obj, 140, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_save_wifi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_save_wifi = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, _("Save\nChanges"));
                                }
                            }
                        }
                        {
                            // btn_scan_wifi
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_scan_wifi = obj;
                            lv_obj_set_pos(obj, 310, 140);
                            lv_obj_set_size(obj, 170, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_scan_wifi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_scan_wifi = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, _("Scan WiFi"));
                                }
                            }
                        }
                        {
                            // wifi_networks_list
                            lv_obj_t *obj = lv_list_create(parent_obj);
                            objects.wifi_networks_list = obj;
                            lv_obj_set_pos(obj, 492, -16);
                            lv_obj_set_size(obj, 512, 219);
                        }
                    }
                }
                {
                    // tab_settings_locale
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, _("Locale Settings"));
                    objects.tab_settings_locale = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // drp_location
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.drp_location = obj;
                            lv_obj_set_pos(obj, 222, -4);
                            lv_obj_set_size(obj, 594, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, _("Europe/London"));
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -10, 9);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Time Zone:");
                        }
                        {
                            // chk_24hr
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.chk_24hr = obj;
                            lv_obj_set_pos(obj, 545, 144);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, _("Use 24-hour Clock"));
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // chk_dst
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.chk_dst = obj;
                            lv_obj_set_pos(obj, -10, 144);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, _("Use Daylight Savings Time"));
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // btn_apply_locale
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_apply_locale = obj;
                            lv_obj_set_pos(obj, 834, -4);
                            lv_obj_set_size(obj, 151, 64);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_btn_locale_apply
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_btn_locale_apply = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, _("Apply"));
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -10, 82);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Date Format:");
                        }
                        {
                            // drp_decimal_sep
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.drp_decimal_sep = obj;
                            lv_obj_set_pos(obj, 782, 70);
                            lv_obj_set_size(obj, 203, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, ". (3.1415)\n, (3,1415)");
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 545, 83);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, _("Decimal Sep:"));
                        }
                        {
                            // drp_date_format
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.drp_date_format = obj;
                            lv_obj_set_pos(obj, 224, 70);
                            lv_obj_set_size(obj, 273, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, "%Y-%M-%d\n%M-%d\n%d-%M\n%d-%M-%Y\n%M-%d-%Y");
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // tab_settings_adafruit_io
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, _("Adafruit IO Details"));
                    objects.tab_settings_adafruit_io = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // btn_camera_settings
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_camera_settings = obj;
                            lv_obj_set_pos(obj, 457, -4);
                            lv_obj_set_size(obj, 299, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Import from Camera (QR Code)");
                                }
                            }
                        }
                        {
                            // btn_fetch_io_account
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_fetch_io_account = obj;
                            lv_obj_set_pos(obj, 771, -4);
                            lv_obj_set_size(obj, 224, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Sync time details from IO");
                                }
                            }
                        }
                        {
                            // btn_export_settings
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_export_settings = obj;
                            lv_obj_set_pos(obj, 228, -4);
                            lv_obj_set_size(obj, 213, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Export to \"secrets.json\"");
                                }
                            }
                        }
                        {
                            // btn_import_settings
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_import_settings = obj;
                            lv_obj_set_pos(obj, -12, -4);
                            lv_obj_set_size(obj, 224, 50);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Import from \"secrets.json\"");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -12, 136);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Adafruit IO Key:");
                        }
                        {
                            // txt_dashboard
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.txt_dashboard = obj;
                            lv_obj_set_pos(obj, 728, 65);
                            lv_obj_set_size(obj, 267, 42);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_text(obj, "tyeth/dashboards/oil");
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_add_event_cb(obj, event_handler_cb_settings_txt_dashboard, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 460, 64);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Dashboard Owner/Name:");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 461, 87);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "<OWNER>/dashboards/<NAME>");
                        }
                        {
                            // txt_username
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.txt_username = obj;
                            lv_obj_set_pos(obj, 228, 65);
                            lv_obj_set_size(obj, 213, 43);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_text(obj, "tyeth");
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_add_event_cb(obj, event_handler_cb_settings_txt_username, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -12, 75);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Adafruit IO Username:");
                        }
                        {
                            // txt_key
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.txt_key = obj;
                            lv_obj_set_pos(obj, 166, 126);
                            lv_obj_set_size(obj, 829, 42);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_text(obj, "YOUR_SECRET_KEY_HERE");
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_add_event_cb(obj, event_handler_cb_settings_txt_key, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
}

void create_screen_dashboard() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.dashboard = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 554);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_dashboard();
}

void tick_screen_dashboard() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}


static const char *screen_names[] = { "Main", "Settings", "Dashboard" };
static const char *object_names[] = { "main", "settings", "dashboard", "obj0", "txt_dashboard", "txt_username", "txt_key", "obj1", "btn_matrix_homepage", "keybrd", "menu_bar_settings", "tabview_settings", "tab_settings_wifi", "btn_wifi_cancel", "lbl_cancel_wifi", "password", "ssid", "btn_save_wifi", "lbl_save_wifi", "btn_scan_wifi", "lbl_scan_wifi", "wifi_networks_list", "tab_settings_locale", "drp_location", "chk_24hr", "chk_dst", "btn_apply_locale", "lbl_btn_locale_apply", "drp_decimal_sep", "drp_date_format", "tab_settings_adafruit_io", "btn_camera_settings", "btn_fetch_io_account", "btn_export_settings", "btn_import_settings" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_settings,
    tick_screen_dashboard,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_settings();
    create_screen_dashboard();
}
