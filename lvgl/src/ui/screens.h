#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *settings;
    lv_obj_t *dashboard;
    lv_obj_t *obj0;
    lv_obj_t *btn_matrix_homepage;
    lv_obj_t *menu_bar_settings;
    lv_obj_t *tabview_settings;
    lv_obj_t *btn_wifi_cancel;
    lv_obj_t *lbl_cancel_wifi;
    lv_obj_t *password;
    lv_obj_t *ssid;
    lv_obj_t *btn_save_wifi;
    lv_obj_t *lbl_save_wifi;
    lv_obj_t *btn_scan_wifi;
    lv_obj_t *lbl_scan_wifi;
    lv_obj_t *wifi_networks_list;
    lv_obj_t *drp_location;
    lv_obj_t *chk_24hr;
    lv_obj_t *chk_dst;
    lv_obj_t *btn_apply_locale;
    lv_obj_t *drp_decimal_sep;
    lv_obj_t *drp_date_format;
    lv_obj_t *btn_camera_settings;
    lv_obj_t *btn_fetch_io_account;
    lv_obj_t *btn_export_settings;
    lv_obj_t *btn_import_settings;
    lv_obj_t *txt_dashboard;
    lv_obj_t *txt_username;
    lv_obj_t *txt_key;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTINGS = 2,
    SCREEN_ID_DASHBOARD = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_settings();
void tick_screen_settings();

void create_screen_dashboard();
void tick_screen_dashboard();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/