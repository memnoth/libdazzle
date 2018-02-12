/* dzl-menu-manager.h
 *
 * Copyright (C) 2015 Christian Hergert <chergert@redhat.com>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DZL_MENU_MANAGER_H
#define DZL_MENU_MANAGER_H

#include <gtk/gtk.h>

#include "dzl-version-macros.h"

G_BEGIN_DECLS

#define DZL_TYPE_MENU_MANAGER (dzl_menu_manager_get_type())

DZL_AVAILABLE_IN_ALL
G_DECLARE_FINAL_TYPE (DzlMenuManager, dzl_menu_manager, DZL, MENU_MANAGER, GObject)

DZL_AVAILABLE_IN_ALL
DzlMenuManager *dzl_menu_manager_new            (void);
DZL_AVAILABLE_IN_ALL
guint           dzl_menu_manager_add_filename   (DzlMenuManager  *self,
                                                 const gchar     *filename,
                                                 GError         **error);
DZL_AVAILABLE_IN_ALL
guint           dzl_menu_manager_add_resource   (DzlMenuManager  *self,
                                                 const gchar     *resource,
                                                 GError         **error);
DZL_AVAILABLE_IN_ALL
guint           dzl_menu_manager_merge          (DzlMenuManager  *self,
                                                 const gchar     *menu_id,
                                                 GMenuModel      *model);
DZL_AVAILABLE_IN_ALL
void            dzl_menu_manager_remove         (DzlMenuManager  *self,
                                                 guint            merge_id);
DZL_AVAILABLE_IN_ALL
GMenu          *dzl_menu_manager_get_menu_by_id (DzlMenuManager  *self,
                                                 const gchar     *menu_id);

G_END_DECLS

#endif /* DZL_MENU_MANAGER_H */
