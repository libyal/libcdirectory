/*
 * Codepage definitions for libcdirectory
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

#if !defined( _LIBCDIRECTORY_CODEPAGE_H )
#define _LIBCDIRECTORY_CODEPAGE_H

#include <libcdirectory/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBCDIRECTORY_CODEPAGES
{
	LIBCDIRECTORY_CODEPAGE_ASCII				= 20127,

	LIBCDIRECTORY_CODEPAGE_ISO_8859_1			= 28591,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_2			= 28592,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_3			= 28593,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_4			= 28594,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_5			= 28595,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_6			= 28596,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_7			= 28597,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_8			= 28598,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_9			= 28599,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_10			= 28600,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_11			= 28601,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_13			= 28603,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_14			= 28604,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_15			= 28605,
	LIBCDIRECTORY_CODEPAGE_ISO_8859_16			= 28606,

	LIBCDIRECTORY_CODEPAGE_KOI8_R				= 20866,
	LIBCDIRECTORY_CODEPAGE_KOI8_U				= 21866,

	LIBCDIRECTORY_CODEPAGE_WINDOWS_874			= 874,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_932			= 932,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_936			= 936,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_949			= 949,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_950			= 950,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1250			= 1250,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1251			= 1251,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1252			= 1252,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1253			= 1253,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1254			= 1254,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1255			= 1255,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1256			= 1256,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1257			= 1257,
	LIBCDIRECTORY_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBCDIRECTORY_CODEPAGE_US_ASCII				LIBCDIRECTORY_CODEPAGE_ASCII

#define LIBCDIRECTORY_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBCDIRECTORY_CODEPAGE_ISO_8859_1
#define LIBCDIRECTORY_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBCDIRECTORY_CODEPAGE_ISO_8859_2
#define LIBCDIRECTORY_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBCDIRECTORY_CODEPAGE_ISO_8859_3
#define LIBCDIRECTORY_CODEPAGE_ISO_NORTH_EUROPEAN		LIBCDIRECTORY_CODEPAGE_ISO_8859_4
#define LIBCDIRECTORY_CODEPAGE_ISO_CYRILLIC			LIBCDIRECTORY_CODEPAGE_ISO_8859_5
#define LIBCDIRECTORY_CODEPAGE_ISO_ARABIC			LIBCDIRECTORY_CODEPAGE_ISO_8859_6
#define LIBCDIRECTORY_CODEPAGE_ISO_GREEK			LIBCDIRECTORY_CODEPAGE_ISO_8859_7
#define LIBCDIRECTORY_CODEPAGE_ISO_HEBREW			LIBCDIRECTORY_CODEPAGE_ISO_8859_8
#define LIBCDIRECTORY_CODEPAGE_ISO_TURKISH			LIBCDIRECTORY_CODEPAGE_ISO_8859_9
#define LIBCDIRECTORY_CODEPAGE_ISO_NORDIC			LIBCDIRECTORY_CODEPAGE_ISO_8859_10
#define LIBCDIRECTORY_CODEPAGE_ISO_THAI				LIBCDIRECTORY_CODEPAGE_ISO_8859_11
#define LIBCDIRECTORY_CODEPAGE_ISO_BALTIC			LIBCDIRECTORY_CODEPAGE_ISO_8859_13
#define LIBCDIRECTORY_CODEPAGE_ISO_CELTIC			LIBCDIRECTORY_CODEPAGE_ISO_8859_14

#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_1			LIBCDIRECTORY_CODEPAGE_ISO_8859_1
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_2			LIBCDIRECTORY_CODEPAGE_ISO_8859_2
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_3			LIBCDIRECTORY_CODEPAGE_ISO_8859_3
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_4			LIBCDIRECTORY_CODEPAGE_ISO_8859_4
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_5			LIBCDIRECTORY_CODEPAGE_ISO_8859_9
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_6			LIBCDIRECTORY_CODEPAGE_ISO_8859_10
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_7			LIBCDIRECTORY_CODEPAGE_ISO_8859_13
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_8			LIBCDIRECTORY_CODEPAGE_ISO_8859_14
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_9			LIBCDIRECTORY_CODEPAGE_ISO_8859_15
#define LIBCDIRECTORY_CODEPAGE_ISO_LATIN_10			LIBCDIRECTORY_CODEPAGE_ISO_8859_16

#define LIBCDIRECTORY_CODEPAGE_KOI8_RUSSIAN			LIBCDIRECTORY_CODEPAGE_KOI8_R
#define LIBCDIRECTORY_CODEPAGE_KOI8_UKRAINIAN			LIBCDIRECTORY_CODEPAGE_KOI8_U

#define LIBCDIRECTORY_CODEPAGE_WINDOWS_THAI			LIBCDIRECTORY_CODEPAGE_WINDOWS_874
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_JAPANESE			LIBCDIRECTORY_CODEPAGE_WINDOWS_932
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBCDIRECTORY_CODEPAGE_WINDOWS_936
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_KOREAN			LIBCDIRECTORY_CODEPAGE_WINDOWS_949
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBCDIRECTORY_CODEPAGE_WINDOWS_950
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN		LIBCDIRECTORY_CODEPAGE_WINDOWS_1250
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_CYRILLIC			LIBCDIRECTORY_CODEPAGE_WINDOWS_1251
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_WESTERN_EUROPEAN		LIBCDIRECTORY_CODEPAGE_WINDOWS_1252
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_GREEK			LIBCDIRECTORY_CODEPAGE_WINDOWS_1253
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_TURKISH			LIBCDIRECTORY_CODEPAGE_WINDOWS_1254
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_HEBREW			LIBCDIRECTORY_CODEPAGE_WINDOWS_1255
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_ARABIC			LIBCDIRECTORY_CODEPAGE_WINDOWS_1256
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_BALTIC			LIBCDIRECTORY_CODEPAGE_WINDOWS_1257
#define LIBCDIRECTORY_CODEPAGE_WINDOWS_VIETNAMESE		LIBCDIRECTORY_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDIRECTORY_CODEPAGE_H ) */

