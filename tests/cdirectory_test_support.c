/*
 * Library support functions test program
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdirectory_test_libcdirectory.h"
#include "cdirectory_test_libcerror.h"
#include "cdirectory_test_macros.h"
#include "cdirectory_test_unused.h"

/* Tests the libcdirectory_get_version function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libcdirectory_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBCDIRECTORY_VERSION_STRING,
	          9 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcdirectory_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libcdirectory_get_codepage(
	          &codepage,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_get_codepage(
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

/* Tests the libcdirectory_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcdirectory_set_codepage(
	          0,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_set_codepage(
	          -1,
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
	 "libcdirectory_get_version",
	 cdirectory_test_get_version );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_get_codepage",
	 cdirectory_test_get_codepage );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_set_codepage",
	 cdirectory_test_set_codepage );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

