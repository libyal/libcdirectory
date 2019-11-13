/*
 * Support functions
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBCDIRECTORY_SUPPORT_H )
#define _LIBCDIRECTORY_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libcdirectory_extern.h"
#include "libcdirectory_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBCDIRECTORY )

LIBCDIRECTORY_EXTERN \
const char *libcdirectory_get_version(
             void );

LIBCDIRECTORY_EXTERN \
int libcdirectory_get_codepage(
     int *codepage,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_set_codepage(
     int codepage,
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBCDIRECTORY ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDIRECTORY_SUPPORT_H ) */

