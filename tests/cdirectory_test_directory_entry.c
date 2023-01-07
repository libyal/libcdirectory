/*
 * Library directory entry type test program
 *
 * Copyright (C) 2008-2023, Joachim Metz <joachim.metz@gmail.com>
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
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdirectory_test_libcdirectory.h"
#include "cdirectory_test_libcerror.h"
#include "cdirectory_test_macros.h"
#include "cdirectory_test_memory.h"
#include "cdirectory_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT )

extern \
int libcdirectory_directory_entry_copy(
     libcdirectory_directory_entry_t *destination_directory_entry,
     libcdirectory_directory_entry_t *source_directory_entry,
     libcerror_error_t **error );

#endif /* #if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT ) */

/* Tests the libcdirectory_directory_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_initialize(
     void )
{
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )
	int number_of_malloc_fail_tests                  = 1;
	int number_of_memset_fail_tests                  = 1;
	int test_number                                  = 0;
#endif

	/* Test regular cases
	 */
	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	directory_entry = NULL;

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcdirectory_directory_entry_initialize with malloc failing
		 */
		cdirectory_test_malloc_attempts_before_fail = test_number;

		result = libcdirectory_directory_entry_initialize(
		          &directory_entry,
		          &error );

		if( cdirectory_test_malloc_attempts_before_fail != -1 )
		{
			cdirectory_test_malloc_attempts_before_fail = -1;

			if( directory_entry != NULL )
			{
				libcdirectory_directory_entry_free(
				 &directory_entry,
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
			 "directory_entry",
			 directory_entry );

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
		/* Test libcdirectory_directory_entry_initialize with memset failing
		 */
		cdirectory_test_memset_attempts_before_fail = test_number;

		result = libcdirectory_directory_entry_initialize(
		          &directory_entry,
		          &error );

		if( cdirectory_test_memset_attempts_before_fail != -1 )
		{
			cdirectory_test_memset_attempts_before_fail = -1;

			if( directory_entry != NULL )
			{
				libcdirectory_directory_entry_free(
				 &directory_entry,
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
			 "directory_entry",
			 directory_entry );

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

#if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT )

/* Tests the libcdirectory_directory_entry_copy function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_copy(
     void )
{
	libcdirectory_directory_entry_t *destination_directory_entry = NULL;
	libcdirectory_directory_entry_t *directory_entry             = NULL;
	libcerror_error_t *error                                     = NULL;
	int result                                                   = 0;

	/* Initialize test
	 */
	result = libcdirectory_directory_entry_initialize(
	          &directory_entry,
	          &error );

	result = libcdirectory_directory_entry_initialize(
	          &destination_directory_entry,
	          &error );

	/* Test directory entry copy
	 */
	result = libcdirectory_directory_entry_copy(
	          destination_directory_entry,
	          directory_entry,
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
	result = libcdirectory_directory_entry_copy(
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

	result = libcdirectory_directory_entry_copy(
	          destination_directory_entry,
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

	/* Test libcdirectory_directory_entry_initialize with memcpy failing
	 */
	cdirectory_test_memcpy_attempts_before_fail = 0;

	result = libcdirectory_directory_entry_copy(
	          destination_directory_entry,
	          directory_entry,
	          &error );

	if( cdirectory_test_memcpy_attempts_before_fail != -1 )
	{
		cdirectory_test_memcpy_attempts_before_fail = -1;
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
	result = libcdirectory_directory_entry_free(
	          &destination_directory_entry,
	          NULL );

	result = libcdirectory_directory_entry_free(
	          &directory_entry,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( destination_directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &destination_directory_entry,
		 NULL );
	}
	if( directory_entry != NULL )
	{
		libcdirectory_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( 0 );
}

#endif /* #if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT ) */

/* Tests the libcdirectory_directory_entry_get_type function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_get_type(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;
	uint8_t entry_type                               = 0;

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

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	/* Test retrieving the type of a directory entry
	 */
	result = libcdirectory_directory_entry_get_type(
	          directory_entry,
	          &entry_type,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "entry_type",
	 entry_type,
	 LIBCDIRECTORY_ENTRY_TYPE_FILE );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_directory_entry_get_type(
	          NULL,
	          &entry_type,
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

	result = libcdirectory_directory_entry_get_type(
	          directory_entry,
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

/* Tests the libcdirectory_directory_entry_get_name function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_get_name(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	char *entry_name                                 = NULL;
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

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	/* Test retrieving the name of a directory entry
	 */
	result = libcdirectory_directory_entry_get_name(
	          directory_entry,
	          &entry_name,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          entry_name,
	          "Makefile.am",
	          11 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libcdirectory_directory_entry_get_name(
	          NULL,
	          &entry_name,
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

	result = libcdirectory_directory_entry_get_name(
	          directory_entry,
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

/* Tests the libcdirectory_directory_entry_get_name_wide function
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_entry_get_name_wide(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	wchar_t *entry_name                              = NULL;
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

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"Makefile.am",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_FILE,
	          0,
	          &error );

	/* Test retrieving the name of a directory entry
	 */
	result = libcdirectory_directory_entry_get_name_wide(
	          directory_entry,
	          &entry_name,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = wide_string_compare(
	          entry_name,
	          L"Makefile.am",
	          11 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libcdirectory_directory_entry_get_name_wide(
	          NULL,
	          &entry_name,
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

	result = libcdirectory_directory_entry_get_name_wide(
	          directory_entry,
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
	 "libcdirectory_directory_entry_initialize",
	 cdirectory_test_directory_entry_initialize );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_free",
	 cdirectory_test_directory_entry_free );

#if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_copy",
	 cdirectory_test_directory_entry_copy );

#endif /* #if defined( __GNUC__ ) && !defined( LIBCDIRECTORY_DLL_IMPORT ) */

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_get_type",
	 cdirectory_test_directory_entry_get_type );

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_get_name",
	 cdirectory_test_directory_entry_get_name );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_entry_get_name_wide",
	 cdirectory_test_directory_entry_get_name_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

