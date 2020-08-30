import os
import scripts.app_helper as app

DEPENDS_LIBS = [
  {
    "root" : '../awtk-csv-file',
    'static_libs': ['csv'],
    'shared_libs': []
  },
  {
    "root" : '../awtk-mvvm',
    'shared_libs': ['mvvm'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view',
    'shared_libs': ['table_view'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-slidable-row',
    'shared_libs': ['slidable_row'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view-mvvm',
    'shared_libs': ['table_view_mvvm'],
    'static_libs': []
  }
]

helper = app.Helper(ARGUMENTS);
helper.set_deps(DEPENDS_LIBS).call(DefaultEnvironment)

CustomWidgetSConscriptFiles = []
SConscriptFiles = CustomWidgetSConscriptFiles + ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
SConscript(SConscriptFiles)
