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
#include "csv/csv_file_object.h"
#include "../res/assets_default.inc"

view_model_t* scores_view_model_create(navigator_request_t* req) {
  char path[MAX_PATH + 1] = {0};
  fs_get_exe(os_fs(), path);
  return_value_if_fail(tk_strlen(path) > 0, NULL);

  char* bin = strstr(path, "bin");
  tk_strcpy(bin, "data/scores.csv");

  csv_file_t* csv = csv_file_create(path, ',');
  object_t* obj = csv_file_object_create(csv);

  return view_model_array_object_wrapper_create(obj);
}

ret_t application_init(void) {
  mvvm_init();
  view_model_factory_register("scores", scores_view_model_create);

  return navigator_to("csv_view_remove");
}

ret_t application_exit() {
  mvvm_deinit();
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
