/*
 * Directory entry functions
 *
 * Copyright (C) 2008-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBCDIRECTORY_DIRECTORY_ENTRY_H )
#define _LIBCDIRECTORY_DIRECTORY_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#include <dir.h>
#endif

#if defined( HAVE_DIRENT_H )
#include <dirent.h>
#endif

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#include "libcdirectory_extern.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libcdirectory_internal_directory_entry libcdirectory_internal_directory_entry_t;

#if defined( WINAPI )
struct libcdirectory_internal_directory_entry
{
	WIN32_FIND_DATA find_data;

#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
	char *narrow_name;
#else
	wchar_t *wide_name;
#endif
};

#elif defined( HAVE_DIRENT_H )
struct libcdirectory_internal_directory_entry
{
	struct dirent entry;

#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
	char *narrow_name;
#else
	wchar_t *wide_name;
#endif
};

#endif /* defined( WINAPI ) */

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_entry_initialize(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_entry_free(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libcdirectory_directory_entry_copy(
     libcdirectory_directory_entry_t *destination_directory_entry,
     libcdirectory_directory_entry_t *source_directory_entry,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     char **name,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_entry_get_name_wide(
     libcdirectory_directory_entry_t *directory_entry,
     wchar_t **name,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDIRECTORY_DIRECTORY_ENTRY_H ) */

