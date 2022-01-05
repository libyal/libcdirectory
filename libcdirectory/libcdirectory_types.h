/*
 * The internal type definitions
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

#if !defined( _LIBCDIRECTORY_INTERNAL_TYPES_H )
#define _LIBCDIRECTORY_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBCDIRECTORY for local use of libcdirectory
 * The definitions in <libcdirectory/types.h> are copied here
 * for local use of libcdirectory
 */
#if defined( HAVE_LOCAL_LIBCDIRECTORY )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libcdirectory_directory {}	libcdirectory_directory_t;
typedef struct libcdirectory_directory_entry {}	libcdirectory_directory_entry_t;

#else
typedef intptr_t libcdirectory_directory_t;
typedef intptr_t libcdirectory_directory_entry_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBCDIRECTORY ) */

#endif /* !defined( _LIBCDIRECTORY_INTERNAL_TYPES_H ) */

