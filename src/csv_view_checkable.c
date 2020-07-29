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

static ret_t scores_view_on_can_exec(void *ctx, event_t *e) {
  csv_file_t *csv = (csv_file_t *)ctx;
  cmd_exec_event_t *evt = cmd_exec_event_cast(e);

  if (tk_str_eq(evt->name, "export_checked")) {
    evt->can_exec = csv_file_get_checked_rows(csv) > 0;
    return RET_STOP;
  }

  return RET_OK;
}

static ret_t scores_view_on_exec(void *ctx, event_t *e) {
  csv_file_t *csv = (csv_file_t *)ctx;
  cmd_exec_event_t *evt = cmd_exec_event_cast(e);

  if (tk_str_eq(evt->name, "export_checked")) {
    log_debug("export_checked:%u\n", csv_file_get_checked_rows(csv));
    return RET_STOP;
  }

  return RET_OK;
}

view_model_t *scores_view_model_create(navigator_request_t *req) {
  csv_file_t *csv = csv_file_create("data/scores.csv", ',');
  object_t *obj = csv_file_object_create(csv);

  emitter_on(EMITTER(obj), EVT_CMD_CAN_EXEC, scores_view_on_can_exec, csv);
  emitter_on(EMITTER(obj), EVT_CMD_WILL_EXEC, scores_view_on_exec, csv);

  return view_model_array_object_wrapper_create(obj);
}

ret_t application_init(void) {
  view_model_factory_register("scores", scores_view_model_create);

  return navigator_to("csv_view_checkable");
}

#define GLOBAL_INIT() mvvm_init()
#define GLOBAL_EXIT() mvvm_deinit()

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
