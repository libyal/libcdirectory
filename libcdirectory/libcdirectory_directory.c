/*
 * Directory functions
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

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
#include "libcdirectory_libclocale.h"
#include "libcdirectory_libcstring.h"
#include "libcdirectory_libuna.h"
#include "libcdirectory_types.h"

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
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	internal_directory->handle = INVALID_HANDLE_VALUE;
#elif defined( WINAPI )
	internal_directory->handle = -1;
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
	
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		if( internal_directory->handle != INVALID_HANDLE_VALUE )
#elif defined( WINAPI )
		if( internal_directory->handle != -1 )
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

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

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
	static char *function                                                    = "libcdirectory_directory_open";
	size_t directory_name_size                                               = 0;
	DWORD error_code                                                         = 0;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	wchar_t *wide_directory_name                                             = NULL;
	size_t wide_directory_name_size                                          = 0;
	int result                                                               = 0;
#else
	char *narrow_directory_name                                              = NULL;
	size_t narrow_directory_name_size                                        = 0;
#endif

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

	directory_name_size = 1 + libcstring_narrow_string_length(
	                           directory_name );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) directory_name,
		          directory_name_size,
		          &wide_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) directory_name,
		          directory_name_size,
		          &wide_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &wide_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &wide_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide character directory name size.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != '\\' )
	{
		wide_directory_name_size += 1;
	}
	wide_directory_name_size += 1;

	wide_directory_name = libcstring_wide_string_allocate(
	                       wide_directory_name_size );

	if( wide_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide character directory name.",
		 function );

		goto on_error;
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_directory_name,
		          wide_directory_name_size,
		          (libuna_utf8_character_t *) directory_name,
		          directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_directory_name,
		          wide_directory_name_size,
		          (libuna_utf8_character_t *) directory_name,
		          directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_directory_name,
		          wide_directory_name_size,
		          (uint8_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_directory_name,
		          wide_directory_name_size,
		          (uint8_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide character directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != '\\' )
	{
		wide_directory_name[ wide_directory_name_size - 3 ] = (wchar_t) '\\';
	}
	wide_directory_name[ wide_directory_name_size - 2 ] = (wchar_t) '*';
	wide_directory_name[ wide_directory_name_size - 1 ] = 0;

	/* Cannot use FindFirstFileA here because it requires a narrow version of WIN32_FIND_DATA
	 */
	internal_directory->handle = FindFirstFileW(
	                              (LPCWSTR) wide_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#else
	narrow_directory_name_size = directory_name_size;

	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] == '\\' )
	{
		narrow_directory_name_size += 1;
	}
	narrow_directory_name_size += 1;

	narrow_directory_name = libcstring_narrow_string_allocate(
	                         narrow_directory_name_size );

	if( narrow_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character directory name.",
		 function );

		goto on_error;
	}
	if( libcstring_narrow_string_copy(
	     narrow_directory_name,
	     directory_name,
	     directory_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != '\\' )
	{
		narrow_directory_name[ narrow_directory_name_size - 3 ] = (char) '\\';
	}
	narrow_directory_name[ narrow_directory_name_size - 2 ] = (char) '*';
	narrow_directory_name[ narrow_directory_name_size - 1 ] = 0;

	internal_directory->handle = FindFirstFileA(
	                              (LPCSTR) narrow_directory_name,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	memory_free(
	 wide_directory_name );

	wide_directory_name = NULL;
#else
	memory_free(
	 narrow_directory_name );

	narrow_directory_name = NULL;
#endif
	return( 1 );

on_error:
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( wide_directory_name != NULL )
	{
		memory_free(
		 wide_directory_name );
	}
#else
	if( narrow_directory_name != NULL )
	{
		memory_free(
		 narrow_directory_name );
	}
#endif
	if( internal_directory->first_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &( internal_directory->first_entry ),
		 NULL );
	}
	return( -1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI open directory for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Opens a directory
 * This function uses the Visual Studio C runtime library function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const char *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory                   = NULL;
	libcdirectory_internal_directory_entry_t *internal_first_directory_entry = NULL;
	static char *function                                                    = "libcdirectory_directory_open";
	char *narrow_directory_name                                              = NULL;
	size_t directory_name_size                                               = 0;
	size_t narrow_directory_name_size                                        = 0;

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
	if( internal_directory->handle != -1 )
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

	directory_name_size = 1 + libcstring_narrow_string_length(
	                           directory_name );

	narrow_directory_name_size = directory_name_size;

	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] == '\\' )
	{
		narrow_directory_name_size += 1;
	}
	narrow_directory_name_size += 1;

	narrow_directory_name = libcstring_wide_string_allocate(
	                         narrow_directory_name_size );

	if( narrow_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character directory name.",
		 function );

		goto on_error;
	}
	if( libcstring_narrow_string_copy(
	     narrow_directory_name,
	     directory_name,
	     directory_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != '\\' )
	{
		narrow_directory_name[ narrow_directory_name_size - 3 ] = (char) '\\';
	}
	narrow_directory_name[ narrow_directory_name_size - 2 ] = (char) '*';
	narrow_directory_name[ narrow_directory_name_size - 1 ] = 0;

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	internal_directory->handle = findfirst(
	                              narrow_directory_name,
	                              &( internal_first_directory_entry->find_data ),
	                              0 );
#else
	internal_directory->handle = _findfirst(
	                              narrow_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#endif
	if( internal_directory->handle == -1 )
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
	 narrow_directory_name );

	narrow_directory_name = NULL;

	return( 1 );

on_error:
	if( narrow_directory_name != NULL )
	{
		memory_free(
		 narrow_directory_name );
	}
	return( -1 );
}

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

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

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
	static char *function                                                    = "libcdirectory_directory_open_wide";
	size_t directory_name_size                                               = 0;
	DWORD error_code                                                         = 0;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	wchar_t *wide_directory_name                                             = NULL;
	size_t wide_directory_name_size                                          = 0;
#else
	char *narrow_directory_name                                              = NULL;
	size_t narrow_directory_name_size                                        = 0;
	int result                                                               = 0;
#endif

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

	directory_name_size = 1 + libcstring_wide_string_length(
	                           directory_name );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	wide_directory_name_size = directory_name_size;

	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] == '\\' )
	{
		wide_directory_name_size += 1;
	}
	wide_directory_name_size += 1;

	wide_directory_name = libcstring_wide_string_allocate(
	                       wide_directory_name_size );

	if( wide_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide character directory name.",
		 function );

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     wide_directory_name,
	     directory_name,
	     directory_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != (wchar_t) '\\' )
	{
		wide_directory_name[ wide_directory_name_size - 3 ] = (wchar_t) '\\';
	}
	wide_directory_name[ wide_directory_name_size - 2 ] = (wchar_t) '*';
	wide_directory_name[ wide_directory_name_size - 1 ] = 0;

	internal_directory->handle = FindFirstFileW(
	                              (LPCWSTR) wide_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          &narrow_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          &narrow_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &narrow_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &narrow_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character directory name size.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != (wchar_t) '\\' )
	{
		narrow_directory_name_size += 1;
	}
	narrow_directory_name_size += 1;

	narrow_directory_name = libcstring_narrow_string_allocate(
	                         narrow_directory_name_size );

	if( narrow_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character directory name.",
		 function );

		goto on_error;
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != (wchar_t) '\\' )
	{
		narrow_directory_name[ narrow_directory_name_size - 3 ] = (char) '\\';
	}
	narrow_directory_name[ narrow_directory_name_size - 2 ] = (char) '*';
	narrow_directory_name[ narrow_directory_name_size - 1 ] = 0;

	/* Cannot use FindFirstFileW here because it requires a wide version of WIN32_FIND_DATA
	 */
	internal_directory->handle = FindFirstFileA(
	                              (LPCSTR) narrow_directory_name,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	memory_free(
	 wide_directory_name );

	wide_directory_name = NULL;
#else
	memory_free(
	 narrow_directory_name );

	narrow_directory_name = NULL;
#endif
	return( 1 );

on_error:
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( wide_directory_name != NULL )
	{
		memory_free(
		 wide_directory_name );
	}
#else
	if( narrow_directory_name != NULL )
	{
		memory_free(
		 narrow_directory_name );
	}
#endif
	if( internal_directory->first_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &( internal_directory->first_entry ),
		 NULL );
	}
	return( -1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI open directory for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Opens a directory
 * This function uses the Visual Studio C runtime library function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open_wide(
     libcdirectory_directory_t *directory,
     const wchar_t *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory                   = NULL;
	libcdirectory_internal_directory_entry_t *internal_first_directory_entry = NULL;
	static char *function                                                    = "libcdirectory_directory_open_wide";
	wchar_t *wide_directory_name                                             = NULL;
	size_t directory_name_size                                               = 0;
	size_t wide_directory_name_size                                          = 0;

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
	if( internal_directory->handle != -1 )
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

	directory_name_size = 1 + libcstring_wide_string_length(
	                           directory_name );

	wide_directory_name_size = directory_name_size;

	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] == '\\' )
	{
		wide_directory_name_size += 1;
	}
	wide_directory_name_size += 1;

	wide_directory_name = libcstring_wide_string_allocate(
	                       wide_directory_name_size );

	if( wide_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide character directory name.",
		 function );

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     wide_directory_name,
	     directory_name,
	     directory_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy directory name.",
		 function );

		goto on_error;
	}
	/* Find files requires a search path, add a \ and * if necessary
	 */
	if( directory_name[ directory_name_size - 2 ] != (wchar_t) '\\' )
	{
		wide_directory_name[ wide_directory_name_size - 3 ] = (wchar_t) '\\';
	}
	wide_directory_name[ wide_directory_name_size - 2 ] = (wchar_t) '*';
	wide_directory_name[ wide_directory_name_size - 1 ] = 0;

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	internal_directory->handle = _wfindfirst(
	                              wide_directory_name,
	                              &( internal_first_directory_entry->find_data ),
	                              0 );
#elif defined( __BORLANDC__ )
	internal_directory->handle = __wfindfirst(
	                              wide_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#else
	internal_directory->handle = _wfindfirst(
	                              wide_directory_name,
	                              &( internal_first_directory_entry->find_data ) );
#endif
	if( internal_directory->handle == -1 )
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
	 wide_directory_name );

	wide_directory_name = NULL;

	return( 1 );

on_error:
	if( wide_directory_name != NULL )
	{
		memory_free(
		 wide_directory_name );
	}
	return( -1 );
}

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
	char *narrow_directory_name                            = NULL;
	size_t directory_name_size                             = 0;
	size_t narrow_directory_name_size                      = 0;
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
	directory_name_size = 1 + libcstring_wide_string_length(
	                           directory_name );

	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          &narrow_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          &narrow_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &narrow_directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          libclocale_codepage,
		          &narrow_directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character directory name size.",
		 function );

		goto on_error;
	}
	narrow_directory_name = libcstring_narrow_string_allocate(
	                         narrow_directory_name_size );

	if( narrow_directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character directory name.",
		 function );

		goto on_error;
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) directory_name,
		          directory_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_directory_name,
		          narrow_directory_name_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) directory_name,
		          directory_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character directory name.",
		 function );

		goto on_error;
	}
	internal_directory->stream = opendir(
	                              narrow_directory_name );

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
	 narrow_directory_name );

	narrow_directory_name = NULL;

	return( 1 );

on_error:
	if( narrow_directory_name != NULL )
	{
		memory_free(
		 narrow_directory_name );
	}
	return( -1 );
}

#else
#error Missing wide open directory function
#endif

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

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

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI close directory for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Closes a directory
 * This function uses the Visual Studio C runtime library function or equivalent
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
	
	if( internal_directory->handle != -1 )
	{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
		if( findclose(
		     internal_directory->handle ) != 0 )
#else
		if( _findclose(
		     internal_directory->handle ) != 0 )
#endif
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
		internal_directory->handle = -1;
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

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

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
#if defined( HAVE_WIDE_CHARACTER_TYPE )
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
#endif
#endif
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

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI read directory entry for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Reads a directory
 * This function uses the Visual Studio C runtime library function or equivalent
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
	size_t finddata_size                                               = 0;
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

	if( internal_directory->handle != -1 )
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
		     &( internal_directory->first_entry ),
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
#if defined( HAVE_WIDE_CHARACTER_TYPE )
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
#endif
#endif
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = _wfindnext(
		          internal_directory->handle,
		          &( internal_first_directory_entry->find_data ),
		          0 );
#else
		result = findnext(
		          internal_directory->handle,
		          &( internal_first_directory_entry->find_data ),
		          0 );
#endif

#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( __BORLANDC__ )
		result = __wfindnext(
		          internal_directory->handle,
		          &( internal_first_directory_entry->find_data ) );
#else
		result = _wfindnext(
		          internal_directory->handle,
		          &( internal_first_directory_entry->find_data ) );

#endif /* defined( __BORLANDC__ ) */
#else
		result = _findnext(
		          internal_directory->handle,
		          &( internal_first_directory_entry->find_data ) );

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520 */

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
	}
	return( 1 );
}

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
#if defined( HAVE_WIDE_CHARACTER_TYPE )
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
#endif
#endif
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
			search_directory_entry_name_length = libcstring_narrow_string_length(
			                                      search_directory_entry_name );

			if( search_directory_entry_name_length == entry_name_length )
			{
				/* If there is an exact match we're done searching
				 */
				match = libcstring_narrow_string_compare(
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
					match = libcstring_narrow_string_compare_no_case(
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
			search_directory_entry_name_length = libcstring_wide_string_length(
			                                      search_directory_entry_name );

			if( search_directory_entry_name_length == entry_name_length )
			{
				/* If there is an exact match we're done searching
				 */
				match = libcstring_wide_string_compare(
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
					match = libcstring_wide_string_compare_no_case(
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

