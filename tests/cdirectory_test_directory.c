/*
 * Library directory type test program
 *
 * Copyright (C) 2008-2026, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( WINAPI ) && !defined( _WIN32 )
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open of file
	 */
	result = libcdirectory_directory_open(
	          directory,
	          "TestFile",
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
	          L"TestFile",
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

#if defined( HAVE_CDIRECTORY_TEST_MEMORY )

	/* Test libcdirectory_directory_read_entry with memset failing
	 */
	cdirectory_test_memset_attempts_before_fail = 0;

	result = libcdirectory_directory_read_entry(
	          directory,
	          directory_entry,
	          &error );

	if( cdirectory_test_memset_attempts_before_fail != -1 )
	{
		cdirectory_test_memset_attempts_before_fail = -1;
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

#if !defined( WINAPI ) && !defined( _WIN32 )

/* Removes the entries and directory created for the symbolic links test
 * Note the removal is best effort any errors are ignored
 */
static void cdirectory_test_directory_symlink_dir_cleanup(
     void )
{
	unlink( "TestSubDir/FileLink" );
	unlink( "TestSubDir/DireLink" );
	unlink( "TestSubDir/DeadLink" );
	unlink( "TestSubDir/RegularFile" );
	rmdir( "TestSubDir/SubDir" );
	rmdir( "TestSubDir" );
}

/* Tests the libcdirectory_directory_read_entry function
 * with a directory containing regular files, subdirectories and symbolic links
 * Returns 1 if successful or 0 if not
 */
int cdirectory_test_directory_read_entry_symlinks(
     void )
{
	libcdirectory_directory_t *directory             = NULL;
	libcdirectory_directory_entry_t *directory_entry = NULL;
	libcerror_error_t *error                         = NULL;
	FILE *file_stream                                = NULL;
	char *entry_name                                 = NULL;
	uint8_t entry_type                               = 0;
	int number_of_entries                            = 0;
	int result                                       = 0;
	int seen_current_dir                             = 0;
	int seen_parent_dir                              = 0;
	int seen_regular_file                            = 0;
	int seen_subdir                                  = 0;
	int seen_file_link                               = 0;
	int seen_dir_link                                = 0;
	int seen_dangling_link                           = 0;
	int created_file_link                            = 0;
	int created_dir_link                             = 0;
	int created_dangling_link                        = 0;

#if defined( HAVE_CASE_INSENSITIVE_FILE_SYSTEM ) || defined( WINAPI )
	uint8_t compare_flags                            = LIBCDIRECTORY_COMPARE_FLAG_NO_CASE;
#else
	uint8_t compare_flags                            = 0;
#endif

	/* Remove (if any) leftover test directory from a previous test run
	 */
	cdirectory_test_directory_symlink_dir_cleanup();

	if( mkdir( "TestSubDir", 0777 ) != 0 )
	{
		fprintf( stdout, "Unable to create TestSubDir: %s\n", strerror( errno ) );
		return( 0 );
	}
	file_stream = file_stream_open(
	               "TestSubDir/RegularFile",
	               FILE_STREAM_OPEN_WRITE );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "file_stream",
	 file_stream );

	result = file_stream_close(
	          file_stream );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	file_stream = NULL;

	/* Create a subdirectory in the test directory
	 */
	if( mkdir( "TestSubDir/SubDir", 0777 ) != 0 )
	{
		fprintf( stdout, "Unable to create TestSubDir/SubDir: %s\n", strerror( errno ) );
		goto on_error;
	}
	/* Add symbolic links to the test directory
	 * Note the corresponding checks are skipped if creating symbolic links is not supported
	 */
	created_file_link     = ( symlink( "RegularFile", "TestSubDir/FileLink" ) == 0 );
	created_dir_link      = ( symlink( "SubDir", "TestSubDir/DireLink" ) == 0 );
	created_dangling_link = ( symlink( "NonExistentFile42", "TestSubDir/DeadLink" ) == 0 );

	if( !created_file_link || !created_dir_link || !created_dangling_link )
	{
		printf( "Note one or more symbolic links could not be created the corresponding checks are skipped\n" );
	}

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

	result = libcdirectory_directory_open(
	          directory,
	          "TestSubDir",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

	/* Read all entries of the directory
	 * Test reading until the end of the directory
	 */
	while( 1 )
	{
		result = libcdirectory_directory_read_entry(
		          directory,
		          directory_entry,
		          &error );

		if( result == 0 )
		{
			break;
		}
		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CDIRECTORY_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		number_of_entries++;

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

		if( strcmp( entry_name, "." ) == 0 )
		{
			seen_current_dir++;
		}
		else if( strcmp( entry_name, ".." ) == 0 )
		{
			seen_parent_dir++;
		}
		else if( strcmp( entry_name, "RegularFile" ) == 0 )
		{
			seen_regular_file++;

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
		}
		else if( strcmp( entry_name, "SubDir" ) == 0 )
		{
			seen_subdir++;

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
			 LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
		else if( strcmp( entry_name, "FileLink" ) == 0 )
		{
			seen_file_link++;

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
			 LIBCDIRECTORY_ENTRY_TYPE_LINK );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
		else if( strcmp( entry_name, "DireLink" ) == 0 )
		{
			seen_dir_link++;

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
			 LIBCDIRECTORY_ENTRY_TYPE_LINK );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
		else if( strcmp( entry_name, "DeadLink" ) == 0 )
		{
			seen_dangling_link++;

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
			 LIBCDIRECTORY_ENTRY_TYPE_LINK );

			CDIRECTORY_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
	}
	CDIRECTORY_TEST_ASSERT_GREATER_THAN_INT(
	 "number_of_entries",
	 number_of_entries,
	 1 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "seen_current_dir",
	 seen_current_dir,
	 1 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "seen_parent_dir",
	 seen_parent_dir,
	 1 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "seen_regular_file",
	 seen_regular_file,
	 1 );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "seen_subdir",
	 seen_subdir,
	 1 );

	if( created_file_link )
	{
		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "seen_file_link",
		 seen_file_link,
		 1 );
	}
	if( created_dir_link )
	{
		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "seen_dir_link",
		 seen_dir_link,
		 1 );
	}
	if( created_dangling_link )
	{
		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "seen_dangling_link",
		 seen_dangling_link,
		 1 );
	}
	/* Test reading beyond the end of the directory
	 */
	result = libcdirectory_directory_read_entry(
	          directory,
	          directory_entry,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Note the directory needs to be re-opened before it can be searched
	 * has_entry starts searching at the current stream position
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

	result = libcdirectory_directory_open(
	          directory,
	          "TestSubDir",
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test has entry of a symbolic link
	 */
	if( created_file_link )
	{
		result = libcdirectory_directory_has_entry(
		          directory,
		          directory_entry,
		          "FileLink",
		          8,
		          LIBCDIRECTORY_ENTRY_TYPE_LINK,
		          compare_flags,
		          &error );

		CDIRECTORY_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CDIRECTORY_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test has entry non match
	 * (RegularFile is a regular file and not a symbolic link)
	 */
	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "RegularFile",
	          11,
	          LIBCDIRECTORY_ENTRY_TYPE_LINK,
	          compare_flags,
	          &error );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
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

	cdirectory_test_directory_symlink_dir_cleanup();

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
	cdirectory_test_directory_symlink_dir_cleanup();
	return( 0 );
}

#endif /* !defined( WINAPI ) && !defined( _WIN32 ) */

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

#if !defined( HAVE_CASE_INSENSITIVE_FILE_SYSTEM ) && !defined( WINAPI )

	/* Test has entry match
	 */
/* TODO: remove the need for the explicit open/close */
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

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "TestFile",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test has entry non-match
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

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "TESTFILE",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( HAVE_CASE_INSENSITIVE_FILE_SYSTEM ) && !defined( WINAPI ) */

	/* Test has entry with caseless compare
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

	result = libcdirectory_directory_has_entry(
	          directory,
	          directory_entry,
	          "TESTFILE",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_directory_has_entry(
	          NULL,
	          directory_entry,
	          "TestFile",
	          8,
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
	          "TestFile",
	          8,
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
	          "TestFile",
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
	          "TestFile",
	          8,
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
	          "TestFile",
	          8,
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

#if !defined( HAVE_CASE_INSENSITIVE_FILE_SYSTEM ) && !defined( WINAPI )

	/* Test has entry match
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

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"TestFile",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test has entry non-match
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

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"TESTFILE",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( HAVE_CASE_INSENSITIVE_FILE_SYSTEM ) && !defined( WINAPI ) */

	/* Test has entry with caseless compare
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

	result = libcdirectory_directory_has_entry_wide(
	          directory,
	          directory_entry,
	          L"TESTFILE",
	          8,
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

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CDIRECTORY_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdirectory_directory_has_entry_wide(
	          NULL,
	          directory_entry,
	          L"TestFile",
	          8,
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
	          L"TestFile",
	          8,
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
	          L"TestFile",
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
	          L"TestFile",
	          8,
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
	          L"TestFile",
	          8,
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
	FILE *file_stream = NULL;
	int result        = 0;

	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argc )
	CDIRECTORY_TEST_UNREFERENCED_PARAMETER( argv )

	file_stream = file_stream_open(
	               "TestFile",
	               "a" );

	CDIRECTORY_TEST_ASSERT_IS_NOT_NULL(
	 "file_stream",
	 file_stream );

	result = file_stream_close(
	          file_stream );

	CDIRECTORY_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	file_stream = NULL;

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

#if !defined( WINAPI ) && !defined( _WIN32 )

	CDIRECTORY_TEST_RUN(
	 "libcdirectory_directory_read_entry_symlinks",
	 cdirectory_test_directory_read_entry_symlinks );

#endif /* !defined( WINAPI ) && !defined( _WIN32 ) */

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

