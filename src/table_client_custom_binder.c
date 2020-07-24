/**
 * File:  table_client_custom_binder.c
 * Author: AWTK Develop Team
 * Brief: table_client_custom_binder
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
#include "table_row/table_row.h"
#include "table_client/table_client.h"

static ret_t table_row_update_cursor(void *ctx, const void *rule) {
  widget_t *row = WIDGET(ctx);
  widget_t *iter = WIDGET(BINDING_RULE(rule)->widget);

  if (widget_is_parent_of(row, iter)) {
    BINDING_RULE(rule)->cursor = TABLE_ROW(ctx)->index;
  }

  return RET_OK;
}

static ret_t table_client_on_load_data_mvvm(void *ctx, uint32_t row_index,
                                            widget_t *row) {
  binding_context_t *bctx = BINDING_CONTEXT(ctx);

  darray_foreach(&(bctx->data_bindings), table_row_update_cursor, row);
  darray_foreach(&(bctx->command_bindings), table_row_update_cursor, row);
  
  return binding_context_update_widget(bctx, row);
}

static ret_t table_client_bind(void *widget, binding_context_t *ctx) {
  int rows = 0;
  widget_t *table_client = WIDGET(widget);
  return_value_if_fail(table_client != NULL && ctx != NULL, RET_BAD_PARAMS);

  table_client_set_on_load_data(table_client, table_client_on_load_data_mvvm, ctx);

  rows = object_get_prop_int(OBJECT(ctx->view_model), "items", 0);
  table_client_set_rows(table_client, rows);

  table_client_ensure_children(table_client);
  WIDGET_FOR_EACH_CHILD_BEGIN(table_client, iter, i)
    if(i < rows) {
      binding_context_bind(BINDING_CONTEXT(ctx), iter);
    }
  WIDGET_FOR_EACH_CHILD_END();

  table_client_reload(table_client);

  return RET_OK;
}

ret_t table_client_custom_binder_register(void) {
  return custom_binder_register(WIDGET_TYPE_TABLE_CLIENT, table_client_bind);
}

