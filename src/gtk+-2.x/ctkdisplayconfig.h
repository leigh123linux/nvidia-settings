/*
 * nvidia-settings: A tool for configuring the NVIDIA X driver on Unix
 * and Linux systems.
 *
 * Copyright (C) 2004 NVIDIA Corporation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of Version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See Version 2
 * of the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the:
 *
 *           Free Software Foundation, Inc.
 *           59 Temple Place - Suite 330
 *           Boston, MA 02111-1307, USA
 *
 */

#ifndef __CTK_DISPLAYCONFIG_H__
#define __CTK_DISPLAYCONFIG_H__

#include "ctkevent.h"
#include "ctkconfig.h"
#include "ctkdisplaylayout.h"


G_BEGIN_DECLS

#define CTK_TYPE_DISPLAY_CONFIG (ctk_display_config_get_type())

#define CTK_DISPLAY_CONFIG(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), CTK_TYPE_DISPLAY_CONFIG, \
                                 CtkDisplayConfig))

#define CTK_DISPLAY_CONFIG_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST ((klass), CTK_TYPE_DISPLAY_CONFIG, \
                              CtkDisplayConfigClass))

#define CTK_IS_DISPLAY_CONFIG(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CTK_TYPE_DISPLAY_CONFIG))

#define CTK_IS_DISPLAY_CONFIG_CLASS(class) \
    (G_TYPE_CHECK_CLASS_TYPE ((klass), CTK_TYPE_DISPLAY_CONFIG))

#define CTK_DISPLAY_CONFIG_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS ((obj), CTK_TYPE_DISPLAY_CONFIG, \
                                CtkDisplayConfigClass))


typedef struct _CtkDisplayConfig
{
    GtkVBox parent;

    NvCtrlAttributeHandle *handle;
    CtkConfig *ctk_config;

    gboolean page_selected; /* Is the display config page selected in the UI */

    /* Layout */
    nvLayoutPtr layout;
    GtkWidget *obj_layout;
    GtkWidget *label_layout;

    GtkWidget *chk_xinerama_enabled;
    GtkWidget *chk_primary_display;

    GtkWidget *notebook; /* Tabbed notebook for display and X screen pages */

    /* Display - Info */
    GtkWidget *display_page;

    GtkWidget *mnu_display_model;
    nvDisplayPtr *display_model_table; /* Lookup table for display modelname */
    int display_model_table_len;
    GtkWidget *txt_display_gpu;

    GtkWidget *btn_display_config;
    GtkWidget *txt_display_config;

    /* Display - Settings */
    GtkWidget *box_display_resolution;
    GtkWidget *mnu_display_resolution;
    nvModeLinePtr *resolution_table;
    int resolution_table_len;

    GtkWidget *mnu_display_refresh;
    nvModeLinePtr *refresh_table; /* Lookup table for refresh menu */
    int refresh_table_len;

    GtkWidget *box_display_modename;
    GtkWidget *txt_display_modename;

    GtkWidget *box_display_position;
    GtkWidget *mnu_display_position_type;     /* Absolute, Right of... */
    GtkWidget *mnu_display_position_relative; /* List of available devices */
    nvDisplayPtr *display_position_table; /* Lookup table for relative display position */
    int display_position_table_len;
    GtkWidget *txt_display_position_offset;   /* Absolute: +0+0 */

    GtkWidget *box_display_panning;
    GtkWidget *txt_display_panning;


    /* X Screen - Info */
    GtkWidget *screen_page;

    GtkWidget *txt_screen_num;

    /* X Screen - Settings */
    GtkWidget *box_screen_depth;
    GtkWidget *mnu_screen_depth;

    GtkWidget *box_screen_position;
    GtkWidget *mnu_screen_position_type;     /* Absolute, Right of... */
    GtkWidget *mnu_screen_position_relative; /* List of available devices */
    nvScreenPtr *screen_position_table;
    int screen_position_table_len;
    GtkWidget *txt_screen_position_offset;   /* Absolute: +0+0 */

    GtkWidget *box_screen_metamode;
    GtkWidget *btn_screen_metamode;
    GtkWidget *btn_screen_metamode_add;
    GtkWidget *btn_screen_metamode_delete;
    
    char *screen_depth_table;
    /* Dialogs */
    GtkWidget *dlg_display_config;
    GtkWidget *rad_display_config_disabled;
    GtkWidget *rad_display_config_xscreen;
    GtkWidget *rad_display_config_twinview;
    GtkWidget *btn_display_config_cancel;

    GtkWidget *dlg_display_disable;
    GtkWidget *txt_display_disable;
    GtkWidget *btn_display_disable_off;
    GtkWidget *btn_display_disable_cancel;

    GtkWidget *dlg_validation_override;
    GtkTextBuffer *buf_validation_override;
    GtkWidget *btn_validation_override_cancel;
    GtkWidget *box_validation_override_details;
    GtkWidget *btn_validation_override_show; /* Show details */

    GtkWidget *dlg_validation_apply;

    GtkWidget *dlg_reset_confirm;
    GtkWidget *btn_reset_cancel;

    GtkWidget *dlg_display_confirm;
    GtkWidget *txt_display_confirm;
    GtkWidget *btn_display_apply_cancel;
    guint display_confirm_timer;
    int display_confirm_countdown; /* Timeout to reset display config */

    GtkWidget *dlg_xconfig_save;     /* Save X config dialog */
    GtkWidget *scr_xconfig_save;     /* Scroll window */
    GtkWidget *txt_xconfig_save;     /* Text view of file contents */
    GtkTextBuffer *buf_xconfig_save; /* Text buffer (Actual) file contents */
    GtkWidget *btn_xconfig_merge;    /* Merge with existing X config */
    GtkWidget *btn_xconfig_preview;  /* Show/Hide button */
    GtkWidget *box_xconfig_save;     /* Show/Hide this box */
 
    GtkWidget *dlg_xconfig_file; /* File save dialog */
    GtkWidget *btn_xconfig_file;
    GtkWidget *txt_xconfig_file;


    /* Buttons */
    GtkWidget *btn_apply;
    gboolean apply_possible; /* True if all modifications are applicable */

    gboolean reset_required; /* Reser required to apply */
    gboolean forced_reset_allowed; /* OK to reset layout w/o user input */
    gboolean notify_user_of_reset; /* User was notified of reset requirement */
    gboolean ignore_reset_events; /* Ignore reset-causing events */

    int cur_screen_pos[2]; /* Keep track of the selected X screen's position */

    GtkWidget *btn_save;
    GtkWidget *btn_probe;

    GtkWidget *btn_advanced;
    gboolean   advanced_mode;  /* True if we are in advanced mode */

    GtkWidget *btn_reset;

} CtkDisplayConfig;

typedef struct _CtkDisplayConfigClass
{
    GtkVBoxClass parent_class;
} CtkDisplayConfigClass;


GType       ctk_display_config_get_type  (void) G_GNUC_CONST;
GtkWidget*  ctk_display_config_new       (NvCtrlAttributeHandle *,
                                          CtkConfig *);

GtkTextBuffer *ctk_display_config_create_help(GtkTextTagTable *,
                                              CtkDisplayConfig *);

void ctk_display_config_selected(GtkWidget *);
void ctk_display_config_unselected(GtkWidget *);


G_END_DECLS

#endif /* __CTK_DISPLAYCONFIG_H__ */
