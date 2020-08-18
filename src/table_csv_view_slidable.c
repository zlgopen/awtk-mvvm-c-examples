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
 * 2020-07-24 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "mvvm/mvvm.h"
#include "csv_file_object.h"
#include "table_view_register.h"
#include "../res/assets_default.inc"
#include "table_client_custom_binder.h"
#include "slidable_row_register.h"

view_model_t *scores_view_model_create(navigator_request_t *req) {
  csv_file_t *csv = csv_file_create("data/scores_large.csv", ',');
  object_t *obj = csv_file_object_create(csv);

  return view_model_array_object_wrapper_create(obj);
}

ret_t application_init(void) {
  table_view_register();
  slidable_row_register();
  table_client_custom_binder_register();

  view_model_factory_register("scores", scores_view_model_create);

  return navigator_to("table_view_slidable");
}

#define GLOBAL_INIT() mvvm_init()
#define GLOBAL_EXIT() mvvm_deinit()

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
