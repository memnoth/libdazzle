/* dzl-macros.h
 *
 * Copyright (C) 2017 Christian Hergert <chergert@redhat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DZL_MACROS_H
#define DZL_MACROS_H

#include <glib.h>
#include <string.h>

#ifdef __linux__
# include <sys/types.h>
# include <sys/syscall.h>
#endif

G_BEGIN_DECLS

#if defined(_MSC_VER)
# define DZL_ALIGNED_BEGIN(_N) __declspec(align(_N))
# define DZL_ALIGNED_END(_N)
#else
# define DZL_ALIGNED_BEGIN(_N)
# define DZL_ALIGNED_END(_N) __attribute__((aligned(_N)))
#endif

#define dzl_clear_weak_pointer(ptr) \
  (*(ptr) ? (g_object_remove_weak_pointer((GObject*)*(ptr), (gpointer*)ptr),*(ptr)=NULL,1) : 0)

#define dzl_set_weak_pointer(ptr,obj) \
  ((obj!=*(ptr))?(dzl_clear_weak_pointer(ptr),*(ptr)=obj,((obj)?g_object_add_weak_pointer((GObject*)obj,(gpointer*)ptr),NULL:NULL),1):0)

/* strlen() gets hoisted out automatically at -O0 for everything but MSVC */
#define DZL_LITERAL_LENGTH(s) (strlen(s))

static inline void
dzl_clear_signal_handler (gpointer  object,
                          gulong   *location_of_handler)
{
  if (*location_of_handler != 0)
    {
      gulong handler = *location_of_handler;
      *location_of_handler = 0;
      g_signal_handler_disconnect (object, handler);
    }
}

static inline gboolean
dzl_str_empty0 (gconstpointer str)
{
  /* We use a gconstpointer to allow passing both
   * signed and unsigned chars into this function */
  return str == NULL || *(char*)str == '\0';
}

static inline gboolean
dzl_str_equal0 (gconstpointer str1,
                gconstpointer str2)
{
  /* We use gconstpointer so that we can allow
   * both signed and unsigned chars here (such as xmlChar). */
  return g_strcmp0 (str1, str2) == 0;
}

static inline void
dzl_clear_source (guint *source_ptr)
{
  guint source = *source_ptr;
  *source_ptr = 0;
  if (source != 0)
    g_source_remove (source);
}

static inline void
dzl_assert_is_main_thread (void)
{
#ifndef __linux__
  static GThread *main;
  GThread *self = g_thread_self ();

  if G_LIKELY (main == self)
    return TRUE;

  /* Slow path, rely on task id == process id */
  if ((pid_t)syscall (SYS_gettid) == getpid ())
    {
      /* Allow for fast path next time */
      main = self;
      return;
    }

  g_assert_not_reached ();
#endif
}

G_END_DECLS

#endif /* DZL_MACROS_H */
