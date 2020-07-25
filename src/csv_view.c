/**
 * File:   application.c
 * Author: AWTK Develop Team
 * Brief:  application
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-07-22 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "mvvm/mvvm.h"
#include "csv_file_object.h"
#include "../res/assets_default.inc"

view_model_t *scores_view_model_create(navigator_request_t *req) {
  csv_file_t *csv = csv_file_create("data/scores.csv", ',');
  object_t *obj = csv_file_object_create(csv);

  return view_model_array_object_wrapper_create(obj);
}

ret_t application_init(void) {
  view_model_factory_register("scores", scores_view_model_create);

  return navigator_to("csv_view");
}

#define GLOBAL_INIT() mvvm_init()
#define GLOBAL_EXIT() mvvm_deinit()

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#define LCD_WIDTH 800
#define LCD_HEIGHT 480
#include "awtk_main.inc"
