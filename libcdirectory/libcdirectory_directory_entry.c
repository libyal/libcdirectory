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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#include <direct.h>
#endif

#if defined( HAVE_DIRENT_H )
#include <dirent.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "libcdirectory_definitions.h"
#include "libcdirectory_directory_entry.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_system_string.h"
#include "libcdirectory_types.h"

/* Creates a directory entry
 * Make sure the value directory_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_initialize(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_initialize";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	if( *directory_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory entry value already set.",
		 function );

		return( -1 );
	}
	internal_directory_entry = memory_allocate_structure(
			            libcdirectory_internal_directory_entry_t );

	if( internal_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_directory_entry,
	     0,
	     sizeof( libcdirectory_internal_directory_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory entry.",
		 function );

		goto on_error;
	}
	*directory_entry = (libcdirectory_directory_entry_t *) internal_directory_entry;

	return( 1 );

on_error:
	if( internal_directory_entry != NULL )
	{
		memory_free(
		 internal_directory_entry );
	}
	return( -1 );
}

/* Frees a directory entry
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_free(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_free";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	if( *directory_entry != NULL )
	{
		internal_directory_entry = (libcdirectory_internal_directory_entry_t *) *directory_entry;
		*directory_entry         = NULL;

#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( internal_directory_entry->narrow_name != NULL )
		{
			memory_free(
			 internal_directory_entry->narrow_name );
		}
#else
		if( internal_directory_entry->wide_name != NULL )
		{
			memory_free(
			 internal_directory_entry->wide_name );
		}
#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
		memory_free(
		 internal_directory_entry );
	}
	return( 1 );
}

/* Copies the directory entry including elements
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_copy(
     libcdirectory_directory_entry_t *destination_directory_entry,
     libcdirectory_directory_entry_t *source_directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_destination_directory_entry = NULL;
	libcdirectory_internal_directory_entry_t *internal_source_directory_entry      = NULL;
	static char *function                                                          = "libcdirectory_directory_entry_copy";

#if defined( WINAPI )
	size_t find_data_size                                                          = 0;
#endif

	if( destination_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination directory entry.",
		 function );

		return( -1 );
	}
	internal_destination_directory_entry = (libcdirectory_internal_directory_entry_t *) destination_directory_entry;

	if( source_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source directory entry.",
		 function );

		return( -1 );
	}
	internal_source_directory_entry = (libcdirectory_internal_directory_entry_t *) source_directory_entry;

#if defined( WINAPI )
	find_data_size = sizeof( WIN32_FIND_DATA );

	if( memory_copy(
	     &( internal_destination_directory_entry->find_data ),
	     &( internal_source_directory_entry->find_data ),
	     find_data_size ) == NULL )
#else
	if( memory_copy(
	     &( internal_destination_directory_entry->entry ),
	     &( internal_source_directory_entry->entry ),
	     sizeof( struct dirent ) ) == NULL )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy directory entry data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
        /* TODO copy narrow_name */
#else
        /* TODO copy wide_name */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Retrieves the directory entry type
 * This function uses the WINAPI directory entry structure for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_type";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_DEVICE ) != 0 )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_DEVICE;
	}
	else if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT ) != 0 )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_LINK;
	}
	else
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_FILE;
	}
	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI directory entry structure for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_DIRENT_H )

/* Retrieves the directory entry type
 * This function uses the POSIX directory entry structure
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_type";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	/* TODO what about DT_WHT ? */
	if( ( internal_directory_entry->entry.d_type == DT_BLK )
	 || ( internal_directory_entry->entry.d_type == DT_CHR ) )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_DEVICE;
	}
	else if( internal_directory_entry->entry.d_type == DT_DIR )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else if( internal_directory_entry->entry.d_type == DT_FIFO )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_PIPE;
	}
	else if( internal_directory_entry->entry.d_type == DT_LNK )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_LINK;
	}
	else if( internal_directory_entry->entry.d_type == DT_REG )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_FILE;
	}
	else if( internal_directory_entry->entry.d_type == DT_SOCK )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_SOCKET;
	}
	else if( internal_directory_entry->entry.d_type == DT_UNKNOWN )
	{
		*type = LIBCDIRECTORY_ENTRY_TYPE_UNDEFINED;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing directory entry structure definition
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Retrieves the directory entry name
 * This function uses the WINAPI directory entry structure for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     char **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *directory_name                                      = NULL;
	size_t directory_name_length                                       = 0;
	size_t narrow_directory_name_size                                  = 0;
#endif

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	directory_name = internal_directory_entry->find_data.cFileName;

	directory_name_length = wide_string_length(
	                         directory_name );

	if( libcdirectory_system_string_size_to_narrow_string(
	     directory_name,
	     directory_name_length + 1,
	     &narrow_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character directory name size.",
		 function );

		goto on_error;
	}
	internal_directory_entry->narrow_name = narrow_string_allocate(
	                                         narrow_directory_name_size );

	if( internal_directory_entry->narrow_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_to_narrow_string(
	     directory_name,
	     directory_name_length + 1,
	     internal_directory_entry->narrow_name,
	     narrow_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character directory name.",
		 function );

		goto on_error;
	}
	*name = internal_directory_entry->narrow_name;
#else
	*name = internal_directory_entry->find_data.cFileName;
#endif
	return( 1 );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
on_error:
	if( internal_directory_entry->narrow_name != NULL )
	{
		memory_free(
		 internal_directory_entry->narrow_name );

		internal_directory_entry->narrow_name = NULL;
	}
	return( -1 );
#endif
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI directory entry structure for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_DIRENT_H )

/* Retrieves the directory entry name
 * This function uses the POSIX directory entry structure
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     char **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	*name = internal_directory_entry->entry.d_name;

	return( 1 );
}

#else
#error Missing directory entry structure definition
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Retrieves the directory entry name
 * This function uses the WINAPI directory entry structure for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name_wide(
     libcdirectory_directory_entry_t *directory_entry,
     wchar_t **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const char *directory_name                                         = NULL;
	size_t directory_name_length                                       = 0;
	size_t wide_directory_name_size                                    = 0;
#endif

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	*name = internal_directory_entry->find_data.cFileName;
#else
	directory_name = internal_directory_entry->find_data.cFileName;

	directory_name_length = narrow_string_length(
	                         directory_name );

	if( libcdirectory_system_string_size_to_wide_string(
	     directory_name,
	     directory_name_length + 1,
	     &wide_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide character directory name size.",
		 function );

		goto on_error;
	}
	internal_directory_entry->wide_name = wide_string_allocate(
	                                       wide_directory_name_size );

	if( internal_directory_entry->wide_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_to_wide_string(
	     directory_name,
	     directory_name_length + 1,
	     internal_directory_entry->wide_name,
	     wide_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide character directory name.",
		 function );

		goto on_error;
	}
	*name = internal_directory_entry->wide_name;
#endif
	return( 1 );

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
on_error:
	if( internal_directory_entry->wide_name != NULL )
	{
		memory_free(
		 internal_directory_entry->wide_name );

		internal_directory_entry->wide_name = NULL;
	}
	return( -1 );
#endif
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI directory entry structure for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_DIRENT_H )

/* Retrieves the directory entry name
 * This function uses the POSIX directory entry structure
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name_wide(
     libcdirectory_directory_entry_t *directory_entry,
     wchar_t **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name_wide";
	size_t directory_name_length                                       = 0;
	size_t wide_directory_name_size                                    = 0;

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	directory_name_length = narrow_string_length(
	                         internal_directory_entry->entry.d_name );

	if( libcdirectory_system_string_size_to_wide_string(
	     internal_directory_entry->entry.d_name,
	     directory_name_length + 1,
	     &wide_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide character directory name size.",
		 function );

		goto on_error;
	}
	internal_directory_entry->wide_name = wide_string_allocate(
	                                       wide_directory_name_size );

	if( internal_directory_entry->wide_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_to_wide_string(
	     internal_directory_entry->entry.d_name,
	     directory_name_length + 1,
	     internal_directory_entry->wide_name,
	     wide_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide character directory name.",
		 function );

		goto on_error;
	}
	*name = internal_directory_entry->wide_name;

	return( 1 );

on_error:
	if( internal_directory_entry->wide_name != NULL )
	{
		memory_free(
		 internal_directory_entry->wide_name );

		internal_directory_entry->wide_name = NULL;
	}
	return( -1 );
}

#else
#error Missing directory entry structure definition
#endif

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

