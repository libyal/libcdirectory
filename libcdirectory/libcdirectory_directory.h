/*
 * Directory functions
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

#if !defined( _LIBCDIRECTORY_DIRECTORY_H )
#define _LIBCDIRECTORY_DIRECTORY_H

#include <common.h>
#include <types.h>

#if defined( HAVE_DIRENT_H )
#include <dirent.h>
#endif

#include "libcdirectory_directory_entry.h"
#include "libcdirectory_extern.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libcdirectory_internal_directory libcdirectory_internal_directory_t;

#if defined( WINAPI )
struct libcdirectory_internal_directory
{
	HANDLE handle;

	libcdirectory_directory_entry_t *first_entry;
};

#elif defined( HAVE_DIRENT_H )
struct libcdirectory_internal_directory
{
	DIR *stream;
};

#endif

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_initialize(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_free(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const char *directory_name,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_open_wide(
     libcdirectory_directory_t *directory,
     const wchar_t *directory_name,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_close(
     libcdirectory_directory_t *directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_read_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_has_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     const char *entry_name,
     size_t entry_name_length,
     uint8_t entry_type,
     uint8_t compare_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_has_entry_wide(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     const wchar_t *entry_name,
     size_t entry_name_length,
     uint8_t entry_type,
     uint8_t compare_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDIRECTORY_DIRECTORY_H ) */

