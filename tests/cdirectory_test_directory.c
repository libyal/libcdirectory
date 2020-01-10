/*
 * Library directory type test program
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdirectory_test_libcdirectory.h"
#include "cdirectory_test_libcerror.h"
#include "cdirectory_test_macros.h"
#include "cdirectory_test_memory.h"
#include "cdirectory_test_unused.h"

/* Tests the libcdirectory_directory_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_initialize(
     void )
{
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	int result                           = 0;

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )
	int number_of_malloc_fail_tests      = 1;
	int number_of_memset_fail_tests      = 1;
	int test_number                      = 0;
#endif

	/* Test regular cases
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "directory",
	 directory );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_free(
	          &directory,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "directory",
	 directory );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_directory_initialize(
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	directory = (libcdirectory_directory_t *) 0x12345678UL;

	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	directory = NULL;

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcdirectory_directory_initialize with malloc failing
		 */
		cdirectory_test_malloc_attempts_before_fail = test_number;

		result = libcdirectory_directory_initialize(
		          &directory,
		          &error );

		if( cdirectory_test_malloc_attempts_before_fail != -1 )
		{
			cdirectory_test_malloc_attempts_before_fail = -1;

			if( directory != NULL )
			{
				libcdirectory_directory_free(
				 &directory,
				 NULL );
			}
		}
		else
		{
			CDIRECTORY_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "directory",
			 directory );

			CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libcdirectory_directory_initialize with memset failing
		 */
		cdirectory_test_memset_attempts_before_fail = test_number;

		result = libcdirectory_directory_initialize(
		          &directory,
		          &error );

		if( cdirectory_test_memset_attempts_before_fail != -1 )
		{
			cdirectory_test_memset_attempts_before_fail = -1;

			if( directory != NULL )
			{
				libcdirectory_directory_free(
				 &directory,
				 NULL );
			}
		}
		else
		{
			CDIRECTORY_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "directory",
			 directory );

			CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_CDIRECTORY_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdirectory_directory_free function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcdirectory_directory_free(
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcdirectory_directory_open function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_open(
     void )
{
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	/* Test open of directory
	 */
	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open of directory that is already open
	 */
	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_close(
	          directory,
	          NULL );

	/* Test open of file
	 */
	result = libcdirectory_directory_open(
	          directory,
	          "Makefile.am",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error cases
	 */
	result = libcdirectory_directory_open(
	          NULL,
	          ".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_open(
	          directory,
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcdirectory_directory_open_wide function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_open_wide(
     void )
{
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	/* Test open of directory
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open of file
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L"Makefile.am",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open of directory that is already open
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_close(
	          directory,
	          NULL );

	/* Test error cases
	 */
	result = libcdirectory_directory_open_wide(
	          NULL,
	          L".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_open_wide(
	          directory,
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )

	/* Test libcdirectory_directory_initialize with malloc failing
	 */
	cdirectory_test_malloc_attempts_before_fail = 0;

	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	if( cdirectory_test_malloc_attempts_before_fail != -1 )
	{
		cdirectory_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CDIRECTORY_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libcdirectory_directory_close function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_close(
     void )
{
	libcdirectory_directory_t *directory = NULL;
	libcerror_error_t *error             = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	/* Test close of directory
	 */
	result = libcdirectory_directory_close(
	          directory,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_directory_close(
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdirectory_directory_read_entry function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_read_entry(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

	/* Test read entry of directory
	 */
	result = libcdirectory_directory_read_entry(
	          directory,
	          directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libcdirectory_directory_close(
	          directory,
	          NULL );

	/* Test error cases
	 */
	result = libcdirectory_directory_read_entry(
	          NULL,
	          directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_read_entry(
	          directory,
	          NULL,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_read_entry(
	          directory,
	          directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_entry_free(
	          &directory_entry,
	          NULL );

	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdirectory_directory_has_entry function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_has_entry(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

#if !defined( WINAPI )
	/* Test has entry match
	 */
/* TODO: remove the need for the explicit open/close */
	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

	/* Test has entry non-match
	 */
	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "MAKEFILE.AM",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

#endif /* !defined( WINAPI ) */

	/* Test has entry with caseless compare
	 */
	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "MAKEFILE.AM",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          LIBCDIRECTORY_COMPARE_FLAG_NO_CASE,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

	/* Test error cases
	 */
	result = libcdirectory_directory_has_entry(
	          NULL,
	          directory_entry,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          NULL,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          NULL,
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          (size_t) SSIZE_MAX + 1,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          11,
	          123,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          80,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_entry_free(
	          &directory_entry,
	          NULL );

	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcdirectory_directory_has_entry_wide function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_has_entry_wide(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

#if !defined( WINAPI )
	/* Test has entry match
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

	/* Test has entry non-match
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"MAKEFILE.AM",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

#endif /* !defined( WINAPI ) */

	/* Test has entry with caseless compare
	 */
	result = libcdirectory_directory_open_wide(
	          directory,
	          L".",
	          &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"MAKEFILE.AM",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          LIBCDIRECTORY_COMPARE_FLAG_NO_CASE,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdirectory_directory_close(
	          directory,
	          &error );

	/* Test error cases
	 */
	result = libcdirectory_directory_has_entry_wide(
	          NULL,
	          directory_entry,
	          L"Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          NULL,
	          L"Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          NULL,
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"Makefile.am",
	          (size_t) SSIZE_MAX + 1,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"Makefile.am",
	          11,
	          123,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          80,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcdirectory_directory_entry_free(
	          &directory_entry,
	          NULL );

	result = libcdirectory_directory_free(
	          &directory,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CDIRECTORY_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CDIRECTORY_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CDIRECTORY_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CDIRECTORY_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argc )
	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argv )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_initialize",
	 cdirectory_test_directory_initialize );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_free",
	 cdirectory_test_directory_free );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_open",
	 cdirectory_test_directory_open );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_open_wide",
	 cdirectory_test_directory_open_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_close",
	 cdirectory_test_directory_close );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_read_entry",
	 cdirectory_test_directory_read_entry );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_has_entry",
	 cdirectory_test_directory_has_entry );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_has_entry_wide",
	 cdirectory_test_directory_has_entry_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

