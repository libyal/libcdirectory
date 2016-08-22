/*
 * Library directory type testing program
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
#include <file_stream.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdirectory_test_libcdirectory.h"
#include "cdirectory_test_libcerror.h"
#include "cdirectory_test_libcstring.h"
#include "cdirectory_test_macros.h"
#include "cdirectory_test_malloc.h"
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

	/* Test libcdirectory_directory_initialize
	 */
	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	directory = NULL;

#if defined( HAVE_CDIRECTORY_TEST_MALLOC )

	/* Test libcdirectory_directory_initialize with malloc failing
	 */
	cdirectory_test_malloc_attempts_before_fail = 0;

	result = libcdirectory_directory_initialize(
	          &directory,
	          &error );

	cdirectory_test_malloc_attempts_before_fail = -1;

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

#endif /* defined( HAVE_CDIRECTORY_TEST_MALLOC ) */

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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open of file
	 */
	result = libcdirectory_directory_open(
	          directory,
	          "Makefile.am",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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
	result = libcdirectory_directory_open(
	          directory,
	          L".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open of file
	 */
	result = libcdirectory_directory_open(
	          directory,
	          L"Makefile.am",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
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
	          L".",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_CDIRECTORY_TEST_MALLOC )

	/* Test libcdirectory_directory_initialize with malloc failing
	 */
	cdirectory_test_malloc_attempts_before_fail = 0;

	result = libcdirectory_directory_open(
	          directory,
	          L".",
	          &error );

	cdirectory_test_malloc_attempts_before_fail = -1;

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

#endif /* defined( HAVE_CDIRECTORY_TEST_MALLOC ) */

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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

	result = libcdirectory_directory_open(
	          directory,
	          ".",
	          &error );

	/* Test has entry
	 */

	/* Test error cases
	 */
	result = libcdirectory_directory_has_entry(
	          NULL,
	          directory_entry,
	          NULL,
	          0,
	          0,
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
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

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] CDIRECTORY_TEST_ATTRIBUTE_UNUSED )
#else
int main( int argc, char * const argv[] CDIRECTORY_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argc )
	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argv )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_initialize",
	 cdirectory_test_directory_initialize() )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_free",
	 cdirectory_test_directory_free() )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_open",
	 cdirectory_test_directory_open() )

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_open_wide",
	 cdirectory_test_directory_open_wide() )

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_close",
	 cdirectory_test_directory_close() )

	/* TODO: add test for libcdirectory_directory_read_entry */

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_has_entry",
	 cdirectory_test_directory_has_entry() )

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_has_entry_wide",
	 cdirectory_test_directory_has_entry_wide() )

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

