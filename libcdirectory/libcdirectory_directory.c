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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
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
#include "libcdirectory_directory.h"
#include "libcdirectory_directory_entry.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_system_string.h"
#include "libcdirectory_types.h"
#include "libcdirectory_wide_string.h"

/* Creates a directory
 * Make sure the value directory is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_initialize(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_initialize";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory value already set.",
		 function );

		return( -1 );
	}
	internal_directory = memory_allocate_structure(
		              libcdirectory_internal_directory_t );

	if( internal_directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_directory,
	     0,
	     sizeof( libcdirectory_internal_directory_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory.",
		 function );

		goto on_error;
	}
#if defined( WINAPI )
	internal_directory->handle = INVALID_HANDLE_VALUE;
#endif

	*directory = (libcdirectory_directory_t *) internal_directory;

	return( 1 );

on_error:
	if( internal_directory != NULL )
	{
		memory_free(
		 internal_directory );
	}
	return( -1 );
}

/* Frees a directory
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_free(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_free";
	int result                                             = 1;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		internal_directory = (libcdirectory_internal_directory_t *) *directory;
	
#if defined( WINAPI )
		if( internal_directory->handle != INVALID_HANDLE_VALUE )
#else
		if( internal_directory->stream != NULL )
#endif
		{
			if( libcdirectory_directory_close(
			     *directory,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close directory.",
				 function );

				result = -1;
			}
		}
		*directory = NULL;

		memory_free(
		 internal_directory );
	}
	return( result );
}

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Opens a directory
 * This function uses the WINAPI function for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const char *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory                   = NULL;
	libcdirectory_internal_directory_entry_t *internal_first_directory_entry = NULL;
	system_character_t *system_directory_name                                = NULL;
	static char *function                                                    = "libcdirectory_directory_open";
	size_t directory_name_length                                             = 0;
	size_t system_directory_name_size                                        = 0;
	DWORD error_code                                                         = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - handle value already set.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - first entry value already set.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_entry_initialize(
	     &( internal_directory->first_entry ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create first entry.",
		 function );

		goto on_error;
	}
	if( internal_directory->first_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing first entry.",
		 function );

		goto on_error;
	}
	internal_first_directory_entry = (libcdirectory_internal_directory_entry_t *) internal_directory->first_entry;

	directory_name_length = narrow_string_length(
	                         directory_name );

	if( libcdirectory_system_string_size_from_narrow_string(
	     directory_name,
	     directory_name_length + 1,
	     &system_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine system character directory name size.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( ( directory_name_length < 2 )
	 || ( directory_name[ directory_name_length - 1 ] != '\\' ) )
	{
		system_directory_name_size += 1;
	}
	system_directory_name_size += 1;

	system_directory_name = system_string_allocate(
	                         system_directory_name_size );

	if( system_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create system character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_from_narrow_string(
	     system_directory_name,
	     system_directory_name_size,
	     directory_name,
	     directory_name_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set system character directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( ( directory_name_length < 2 )
	 || ( directory_name[ directory_name_length - 1 ] != '\\' ) )
	{
		system_directory_name[ system_directory_name_size - 3 ] = (system_character_t) '\\';
	}
	system_directory_name[ system_directory_name_size - 2 ] = (system_character_t) '*';
	system_directory_name[ system_directory_name_size - 1 ] = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	/* Cannot use FindFirstFileA here because it requires a narrow version of WIN32_FIND_DATA
	 */
	internal_directory->handle = FindFirstFileW(
	                              (LPCWSTR) system_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#else
	internal_directory->handle = FindFirstFileA(
	                              (LPCSTR) system_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#endif
	if( internal_directory->handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 error_code,
		 "%s: unable to open directory.",
		 function );

		goto on_error;
	}
	memory_free(
	 system_directory_name );

	return( 1 );

on_error:
	if( system_directory_name != NULL )
	{
		memory_free(
		 system_directory_name );
	}
	if( internal_directory->first_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &( internal_directory->first_entry ),
		 NULL );
	}
	return( -1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI open directory for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_OPENDIR )

/* Opens a directory
 * This function uses the POSIX opendir function
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const char *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_open";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( internal_directory->stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - stream value already set.",
		 function );

		return( -1 );
	}
	internal_directory->stream = opendir(
	                              directory_name );

	if( internal_directory->stream == NULL )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open directory.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing open directory function
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Opens a directory
 * This function uses the WINAPI function for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open_wide(
     libcdirectory_directory_t *directory,
     const wchar_t *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory                   = NULL;
	libcdirectory_internal_directory_entry_t *internal_first_directory_entry = NULL;
	system_character_t *system_directory_name                                = NULL;
	static char *function                                                    = "libcdirectory_directory_open_wide";
	size_t directory_name_length                                             = 0;
	size_t system_directory_name_size                                        = 0;
	DWORD error_code                                                         = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - handle value already set.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - first entry value already set.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_entry_initialize(
	     &( internal_directory->first_entry ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create first entry.",
		 function );

		goto on_error;
	}
	if( internal_directory->first_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing first entry.",
		 function );

		goto on_error;
	}
	internal_first_directory_entry = (libcdirectory_internal_directory_entry_t *) internal_directory->first_entry;

	directory_name_length = wide_string_length(
	                         directory_name );

	if( libcdirectory_system_string_size_from_wide_string(
	     directory_name,
	     directory_name_length + 1,
	     &system_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine system character directory name size.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( ( directory_name_length < 2 )
	 || ( directory_name[ directory_name_length - 1 ] == (wchar_t) '\\' ) )
	{
		system_directory_name_size += 1;
	}
	system_directory_name_size += 1;

	system_directory_name = system_string_allocate(
	                         system_directory_name_size );

	if( system_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create system character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_from_wide_string(
	     system_directory_name,
	     system_directory_name_size,
	     directory_name,
	     directory_name_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set system character directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( ( directory_name_length < 2 )
	 || ( directory_name[ directory_name_length - 1 ] == (wchar_t) '\\' ) )
	{
		system_directory_name[ system_directory_name_size - 3 ] = (system_character_t) '\\';
	}
	system_directory_name[ system_directory_name_size - 2 ] = (system_character_t) '*';
	system_directory_name[ system_directory_name_size - 1 ] = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	internal_directory->handle = FindFirstFileW(
	                              (LPCWSTR) system_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#else
	/* Cannot use FindFirstFileW here because it requires a wide version of WIN32_FIND_DATA
	 */
	internal_directory->handle = FindFirstFileA(
	                              (LPCSTR) system_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#endif
	if( internal_directory->handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 error_code,
		 "%s: unable to open directory.",
		 function );

		goto on_error;
	}
	memory_free(
	 system_directory_name );

	return( 1 );

on_error:
	if( system_directory_name != NULL )
	{
		memory_free(
		 system_directory_name );
	}
	if( internal_directory->first_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &( internal_directory->first_entry ),
		 NULL );
	}
	return( -1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI open directory for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_OPENDIR )

/* Opens a directory
 * This function uses the POSIX opendir function
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open_wide(
     libcdirectory_directory_t *directory,
     const wchar_t *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_open_wide";
	char *system_directory_name                            = NULL;
	size_t directory_name_length                           = 0;
	size_t system_directory_name_size                      = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( internal_directory->stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - stream value already set.",
		 function );

		return( -1 );
	}
	directory_name_length = wide_string_length(
	                         directory_name );

	if( libcdirectory_system_string_size_from_wide_string(
	     directory_name,
	     directory_name_length + 1,
	     &system_directory_name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine system character directory name size.",
		 function );

		goto on_error;
	}
	system_directory_name = system_string_allocate(
	                         system_directory_name_size );

	if( system_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create system character directory name.",
		 function );

		goto on_error;
	}
	if( libcdirectory_system_string_copy_from_wide_string(
	     system_directory_name,
	     system_directory_name_size,
	     directory_name,
	     directory_name_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set system character directory name.",
		 function );

		goto on_error;
	}
	internal_directory->stream = opendir(
	                              system_directory_name );

	if( internal_directory->stream == NULL )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open directory.",
		 function );

		goto on_error;
	}
	memory_free(
	 system_directory_name );

	system_directory_name = NULL;

	return( 1 );

on_error:
	if( system_directory_name != NULL )
	{
		memory_free(
		 system_directory_name );
	}
	return( -1 );
}

#else
#error Missing wide open directory function
#endif

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Closes a directory
 * This function uses the WINAPI function for Windows XP or later
 * Returns 0 if successful or -1 on error
 */
int libcdirectory_directory_close(
     libcdirectory_directory_t *directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_close";
	int result                                             = 0;
	DWORD error_code                                       = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
	{
		if( FindClose(
		     internal_directory->handle ) == 0 )
		{
			error_code = GetLastError();

			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 error_code,
			 "%s: unable to close directory.",
			 function );

			result = -1;
		}
		internal_directory->handle = INVALID_HANDLE_VALUE;
	}
	if( internal_directory->first_entry != NULL )
	{
		if( libcdirectory_directory_entry_free(
		     &( internal_directory->first_entry ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free first entry.",
			 function );

			result = -1;
		}
	}
	return( result );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI close directory for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_CLOSEDIR )

/* Closes a directory
 * This function uses the POSIX closedir function
 * Returns 0 if successful or -1 on error
 */
int libcdirectory_directory_close(
     libcdirectory_directory_t *directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_close";
	int result                                             = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( internal_directory->stream != NULL )
	{
		if( closedir(
		     internal_directory->stream ) != 0 )
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 errno,
			 "%s: unable to close directory.",
			 function );

			result = -1;
		}
		internal_directory->stream = NULL;
	}
	return( result );
}

#else
#error Missing close directory function
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0501 )

/* Reads a directory
 * This function uses the WINAPI function for Windows XP or later
 * Returns 1 if successful, 0 if no such entry or -1 on error
 */
int libcdirectory_directory_read_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory             = NULL;
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_read_entry";
	DWORD error_code                                                   = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
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

	if( internal_directory->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing handle.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry != NULL )
	{
		if( libcdirectory_directory_entry_copy(
		     directory_entry,
		     internal_directory->first_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy first directory entry.",
			 function );

			return( -1 );
		}
		if( libcdirectory_directory_entry_free(
		     (libcdirectory_directory_t **) &( internal_directory->first_entry ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free first entry.",
			 function );

			return( -1 );
		}
	}
	else
	{
#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( internal_directory_entry->narrow_name != NULL )
		{
			memory_free(
			 internal_directory_entry->narrow_name );

			internal_directory_entry->narrow_name = NULL;
		}
#else
		if( internal_directory_entry->wide_name != NULL )
		{
			memory_free(
			 internal_directory_entry->wide_name );

			internal_directory_entry->wide_name = NULL;
		}
#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( FindNextFile(
		     internal_directory->handle,
		     &( internal_directory_entry->find_data ) ) == 0 )
		{
			error_code = GetLastError();

			if( error_code == ERROR_NO_MORE_FILES )
			{
				return( 0 );
			}
			else
			{
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 error_code,
				 "%s: unable to read from directory.",
				 function );
			}
			return( -1 );
		}
	}
	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI read directory entry for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_READDIR_R )

/* Reads a directory
 * This function uses the POSIX readdir_r function
 * Returns 1 if successful, 0 if no such entry or -1 on error
 */
int libcdirectory_directory_read_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory             = NULL;
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	struct dirent *result_directory_entry                              = NULL;
	static char *function                                              = "libcdirectory_directory_read_entry";
	int result                                                         = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
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

	if( internal_directory->stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing stream.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( internal_directory_entry->narrow_name != NULL )
	{
		memory_free(
		 internal_directory_entry->narrow_name );

		internal_directory_entry->narrow_name = NULL;
	}
#else
	if( internal_directory_entry->wide_name != NULL )
	{
		memory_free(
		 internal_directory_entry->wide_name );

		internal_directory_entry->wide_name = NULL;
	}
#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) && defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	result = readdir_r(
	          internal_directory->stream,
	          &( internal_directory_entry->entry ),
	          &result_directory_entry );

	if( result != 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 errno,
		 "%s: unable to read from directory.",
		 function );

		return( -1 );
	}
	if( result_directory_entry == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

#else
#error Missing read directory entry function
#endif

/* Determines if a directory has a specific entry
 * Returns 1 if the directory has the corresponding entry, 0 if not or -1 on error
 */
int libcdirectory_directory_has_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     const char *entry_name,
     size_t entry_name_length,
     uint8_t entry_type,
     uint8_t compare_flags,
     libcerror_error_t **error )
{
	libcdirectory_directory_entry_t *search_directory_entry = NULL;
	char *search_directory_entry_name                       = NULL;
	static char *function                                   = "libcdirectory_directory_read_entry";
	size_t search_directory_entry_name_length               = 0;
	uint8_t search_directory_entry_type                     = 0;
	int entry_found                                         = 0;
	int match                                               = 0;
	int result                                              = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
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
	if( entry_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry name.",
		 function );

		return( -1 );
	}
	if( entry_name_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid entry name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_DEVICE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_FILE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_LINK )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_PIPE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_SOCKET )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_UNDEFINED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported entry type.",
		 function );

		return( -1 );
	}
	if( ( compare_flags & ~( LIBCDIRECTORY_COMPARE_FLAG_NO_CASE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported compare flags.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_entry_initialize(
	     &search_directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create search directory entry.",
		 function );

		goto on_error;
	}
	entry_found = 0;

	do
	{
		result = libcdirectory_directory_read_entry(
			  directory,
			  search_directory_entry,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory entry.",
			 function );

			goto on_error;
		}
		else if( result == 0 )
		{
			break;
		}
		if( libcdirectory_directory_entry_get_type(
		     search_directory_entry,
		     &search_directory_entry_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve directory entry type.",
			 function );

			goto on_error;
		}
		if( search_directory_entry_type == entry_type )
		{
			if( libcdirectory_directory_entry_get_name(
			     search_directory_entry,
			     &search_directory_entry_name,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve directory entry name.",
				 function );

				goto on_error;
			}
			search_directory_entry_name_length = narrow_string_length(
			                                      search_directory_entry_name );

			if( search_directory_entry_name_length == entry_name_length )
			{
				/* If there is an exact match we're done searching
				 */
				match = narrow_string_compare(
					 search_directory_entry_name,
					 entry_name,
					 entry_name_length );

				if( match == 0 )
				{
					if( libcdirectory_directory_entry_copy(
					     directory_entry,
					     search_directory_entry,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
						 "%s: unable to copy search directory entry.",
						 function );

						goto on_error;
					}
					entry_found = 1;

					break;
				}
				/* Ignore successive caseless matches
				 */
				if( ( ( compare_flags & LIBCDIRECTORY_COMPARE_FLAG_NO_CASE ) != 0 )
				 && ( entry_found == 0 ) )
				{
					match = narrow_string_compare_no_case(
						 search_directory_entry_name,
						 entry_name,
						 entry_name_length );

					if( match == 0 )
					{
						if( libcdirectory_directory_entry_copy(
						     directory_entry,
						     search_directory_entry,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_MEMORY,
							 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
							 "%s: unable to copy search directory entry.",
							 function );

							goto on_error;
						}
						entry_found = 1;
					}
				}
			}
		}
	}
	while( result != 0 );

	if( libcdirectory_directory_entry_free(
	     &search_directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free search directory entry.",
		 function );

		goto on_error;
	}
	return( entry_found );

on_error:
	if( search_directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &search_directory_entry,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a directory has a specific entry
 * Returns 1 if the directory has the corresponding entry, 0 if not or -1 on error
 */
int libcdirectory_directory_has_entry_wide(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     const wchar_t *entry_name,
     size_t entry_name_length,
     uint8_t entry_type,
     uint8_t compare_flags,
     libcerror_error_t **error )
{
	libcdirectory_directory_entry_t *search_directory_entry = NULL;
	wchar_t *search_directory_entry_name                    = NULL;
	static char *function                                   = "libcdirectory_directory_read_entry_wide";
	size_t search_directory_entry_name_length               = 0;
	uint8_t search_directory_entry_type                     = 0;
	int entry_found                                         = 0;
	int match                                               = 0;
	int result                                              = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
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
	if( entry_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry name.",
		 function );

		return( -1 );
	}
	if( entry_name_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid entry name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_DEVICE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_FILE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_LINK )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_PIPE )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_SOCKET )
	 && ( entry_type != LIBCDIRECTORY_ENTRY_TYPE_UNDEFINED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported entry type.",
		 function );

		return( -1 );
	}
	if( ( compare_flags & ~( LIBCDIRECTORY_COMPARE_FLAG_NO_CASE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported compare flags.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_entry_initialize(
	     &search_directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create search directory entry.",
		 function );

		goto on_error;
	}
	entry_found = 0;

	do
	{
		result = libcdirectory_directory_read_entry(
			  directory,
			  search_directory_entry,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory entry.",
			 function );

			goto on_error;
		}
		else if( result == 0 )
		{
			break;
		}
		if( libcdirectory_directory_entry_get_type(
		     search_directory_entry,
		     &search_directory_entry_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve directory entry type.",
			 function );

			goto on_error;
		}
		if( search_directory_entry_type == entry_type )
		{
			if( libcdirectory_directory_entry_get_name_wide(
			     search_directory_entry,
			     &search_directory_entry_name,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve directory entry name.",
				 function );

				goto on_error;
			}
			search_directory_entry_name_length = wide_string_length(
			                                      search_directory_entry_name );

			if( search_directory_entry_name_length == entry_name_length )
			{
				/* If there is an exact match we're done searching
				 */
				match = wide_string_compare(
					 search_directory_entry_name,
					 entry_name,
					 entry_name_length );

				if( match == 0 )
				{
					if( libcdirectory_directory_entry_copy(
					     directory_entry,
					     search_directory_entry,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
						 "%s: unable to copy search directory entry.",
						 function );

						goto on_error;
					}
					entry_found = 1;

					break;
				}
				/* Ignore successive caseless matches
				 */
				if( ( ( compare_flags & LIBCDIRECTORY_COMPARE_FLAG_NO_CASE ) != 0 )
				 && ( entry_found == 0 ) )
				{
					match = wide_string_compare_no_case(
						 search_directory_entry_name,
						 entry_name,
						 entry_name_length );

					if( match == 0 )
					{
						if( libcdirectory_directory_entry_copy(
						     directory_entry,
						     search_directory_entry,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_MEMORY,
							 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
							 "%s: unable to copy search directory entry.",
							 function );

							goto on_error;
						}
						entry_found = 1;
					}
				}
			}
		}
	}
	while( result != 0 );

	if( libcdirectory_directory_entry_free(
	     &search_directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free search directory entry.",
		 function );

		goto on_error;
	}
	return( entry_found );

on_error:
	if( search_directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &search_directory_entry,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

