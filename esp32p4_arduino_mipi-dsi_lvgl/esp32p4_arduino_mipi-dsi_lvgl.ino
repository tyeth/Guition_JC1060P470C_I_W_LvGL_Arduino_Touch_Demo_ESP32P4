#pragma GCC push_options
#pragma GCC optimize("O3")

// Don't forget to set these to Zero (0) in lv_conf.h
// #define LV_USE_ASSERT_MEM_INTEGRITY 0   /*Check the integrity of `lv_mem` after critical operations. (Slow)*/
// #define LV_USE_ASSERT_OBJ           0   /*Check the object's type and existence (e.g. not deleted). (Slow)*/


#include <Arduino.h>
#include "lvgl.h"
#include "../lvgl/src/ui/ui.h"
#include "../lvgl/src/ui/screens.h"
#include "../lvgl/src/i18n/lv_i18n.h"
#include "demos/lv_demos.h"
#include "pins_config.h"
#include "src/lcd/jd9165_lcd.h"
#include "src/touch/gt911_touch.h"
#include "esp_err.h"
#include "esp_log.h"
// TinyUSB / FFat / SD etc
#include "FFat.h"
#include "Adafruit_TinyUSB.h"

jd9165_lcd lcd = jd9165_lcd(LCD_RST);
gt911_touch touch = gt911_touch(TP_I2C_SDA, TP_I2C_SCL, TP_RST, TP_INT);

// static lv_disp_draw_buf_t draw_buf;
lv_display_t * disp_drv;
static uint32_t *buf;
static uint32_t *buf1;

// ffat vfs block device and tinyusb msc



// Function to handle button matrix events
static void btn_matrix_homepage_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = (lv_obj_t *)lv_event_get_target(e);
    uint32_t id = lv_buttonmatrix_get_selected_button(obj);

    if(id == 0) {
        // log_i("Settings button clicked");
        // set active screen
        // create_screen_by_id(SCREEN_ID_SETTINGS);
        lv_screen_load_anim(lv_obj_get_screen(objects.settings), LV_SCR_LOAD_ANIM_MOVE_LEFT, 150, 0, true);
    } else {
        lv_screen_load_anim(lv_obj_get_screen(objects.dashboard), LV_SCR_LOAD_ANIM_OUT_TOP, 150, 0, true);
    }
}


static void text_area_event_callback(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target_obj(e);
    lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        // lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static void turn_off_scrolling(lv_obj_t* obj) {
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ONE);
}


static void random_init()
{
  // Set the action for the button matrix
  lv_obj_add_event_cb(objects.btn_matrix_homepage, btn_matrix_homepage_event_handler, LV_EVENT_CLICKED, NULL);
  turn_off_scrolling(objects.tab_settings_wifi);
  turn_off_scrolling(objects.tab_settings_locale);
  turn_off_scrolling(objects.tab_settings_adafruit_io);
  lv_dropdown_set_options(objects.drp_location, "Europe-London\nAmerica-New York\nAmerica-Los Angeles\nAsia-Tokyo\nAustralia-Sydney");

}


// 显示刷新
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * color_map)
{
  const int offsetx1 = area->x1;
  const int offsetx2 = area->x2;
  const int offsety1 = area->y1;
  const int offsety2 = area->y2;
  lcd.lcd_draw_bitmap(offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
  lv_display_flush_ready(disp); // 告诉lvgl刷新完成
}

void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  // Serial.println("my_touchpad_read");
  // ESP_LOGI("my_touchpad_read", "my_touchpad_read");
  bool touched;
  uint16_t touchX, touchY;//[1]={0}, touchY[1]={0};

  touched = touch.getTouch(&touchX, &touchY);
  // touched = touch.getTouch(touchX, touchY);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    // 设置坐标
    data->point.x = touchX;
    data->point.y = touchY;
    // data->point.x = touchX[0];
    // data->point.y = touchY[0];
    Serial.printf("x=%d,y=%d \r\n",data->point.x,data->point.y);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32P4 MIPI DSI LVGL");
  // Wire.begin(TP_I2C_SDA, TP_I2C_SCL, 400000);
  ESP_LOGI("setup", "LCD BEGIN UPCOMING");
  lcd.begin();
  ESP_LOGI("setup", "touch begin I2C SDA: %d, SCL: %d", TP_I2C_SDA, TP_I2C_SCL);
  touch.begin();
  ESP_LOGI("setup", "touch begin done");

  lv_init();
  lv_i18n_init(lv_i18n_language_pack);
  lv_i18n_set_locale("en-GB");

  uint32_t buffer_size = LCD_H_RES * LCD_V_RES;
  
  buf = (uint32_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
  buf1 =(uint32_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
  assert(buf);
  assert(buf1);
  
  disp_drv = lv_display_create(LCD_H_RES, LCD_V_RES);
  lv_display_set_flush_cb(disp_drv, my_disp_flush);
  lv_display_set_buffers(disp_drv, buf, buf1, buffer_size * sizeof(uint32_t), LV_DISPLAY_RENDER_MODE_FULL);
  /*Initialize the display*/
  
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touchpad_read);
  // lv_indev_set_user_data(indev, &touch);
  lv_indev_enable(indev, true);
  
  lv_indev_set_display(indev, disp_drv);
  // lv_indev_set_cursor(indev, NULL); // lvgl cursor
  
  ui_init();
  random_init();
  // lv_demo_widgets(); /* 小部件示例 */
  // lv_demo_music();        /* 类似智能手机的现代音乐播放器演示 */
  // lv_demo_stress();       /* LVGL 压力测试 */
  // lv_demo_benchmark();    /* 用于测量 LVGL 性能或比较不同设置的演示 */
  Serial.println("setup done");

  // Check if FFat partition mounts okay (if partition exists, and is ffat, and has files, but/or corrupt, then format)


  // Now setup tinyusb to show MSC to host


  // Also support USB host mode, to receive USB Memory sticks (or WipperSnapper devices) with secrets.json for import


  // Link filemanager with filesystem/table
  // lv_file_explorer_get_file_table()
  // lvgl/examples/others/file_explorer/lv_example_file_explorer_3.c
  // https://github.com/lvgl/lvgl/blob/master/examples/others/file_explorer/lv_example_file_explorer_3.c
  // https://docs.lvgl.io/9.0/others/file_explorer.html#usage

  // Set quick access /mnt to usb host devices, main home folder to Flash:\, also SD cards if around.
  // Need attached detection, hotplug removal and insertion etc, retry on first failure, Kensington SD fix.

}

void loop()
{
  Serial.println("loop");
  Serial.flush();
  // lv_task_handler();
  while (1){
    // lv_task_handler();
    lv_tick_inc(1);
    lv_timer_handler();
    ui_tick();
    delay(1);
  }
}
