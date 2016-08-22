/*
 * Library directory entry type testing program
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

/* Tests the libcdirectory_directory_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_initialize(
     void )
{
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

	/* Test libcdirectory_directory_entry_initialize
	 */
	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
         "directory_entry",
         directory_entry );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdirectory_directory_entry_free(
	          &directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "directory_entry",
         directory_entry );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdirectory_directory_entry_initialize(
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

	directory_entry = (libcdirectory_directory_entry_t *) 0x12345678UL;

	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
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

	directory_entry = NULL;

#if defined( HAVE_CDIRECTORY_TEST_MALLOC )

	/* Test libcdirectory_directory_entry_initialize with malloc failing
	 */
	cdirectory_test_malloc_attempts_before_fail = 0;

	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

	cdirectory_test_malloc_attempts_before_fail = -1;

	CDIRECTORY_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDIRECTORY_TEST_ASSERT_IS_NULL(
         "directory_entry",
         directory_entry );

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
	if( directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdirectory_directory_entry_free function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcdirectory_directory_entry_free(
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
	 "libcdirectory_directory_entry_initialize",
	 cdirectory_test_directory_entry_initialize() )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_free",
	 cdirectory_test_directory_entry_free() )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}
