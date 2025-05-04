#pragma GCC push_options
#pragma GCC optimize("O3")

#include <Arduino.h>
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "pins_config.h"
#include "src/lcd/jd9165_lcd.h"
#include "src/touch/gt911_touch.h"
#include "esp_err.h"
#include "esp_log.h"

jd9165_lcd lcd = jd9165_lcd(LCD_RST);
gt911_touch touch = gt911_touch(TP_I2C_SDA, TP_I2C_SCL, TP_RST, TP_INT);

// static lv_disp_draw_buf_t draw_buf;
lv_display_t * disp_drv;
static uint32_t *buf;
static uint32_t *buf1;

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

  lv_demo_widgets(); /* 小部件示例 */
  // lv_demo_music();        /* 类似智能手机的现代音乐播放器演示 */
  // lv_demo_stress();       /* LVGL 压力测试 */
  // lv_demo_benchmark();    /* 用于测量 LVGL 性能或比较不同设置的演示 */
  Serial.println("setup done");
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
    delay(1);
  }
}
