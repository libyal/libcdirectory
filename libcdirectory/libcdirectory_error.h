/*
 * Error functions
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBCDIRECTORY_INTERNAL_ERROR_H )
#define _LIBCDIRECTORY_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBCDIRECTORY )
#include <libcdirectory/error.h>
#endif

#include "libcdirectory_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBCDIRECTORY )

LIBCDIRECTORY_EXTERN \
void libcdirectory_error_free(
      libcdirectory_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_error_fprint(
     libcdirectory_error_t *error,
     FILE *stream );

LIBCDIRECTORY_EXTERN \
int libcdirectory_error_sprint(
     libcdirectory_error_t *error,
     char *string,
     size_t size );

LIBCDIRECTORY_EXTERN \
int libcdirectory_error_backtrace_fprint(
     libcdirectory_error_t *error,
     FILE *stream );

LIBCDIRECTORY_EXTERN \
int libcdirectory_error_backtrace_sprint(
     libcdirectory_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBCDIRECTORY ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDIRECTORY_INTERNAL_ERROR_H ) */

