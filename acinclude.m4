dnl Checks for required headers and functions
dnl
dnl Version: 20260529

dnl Function to detect whether a readdir_r is deprecated
AC_DEFUN([AX_LIBCDIRECTORY_CHECK_DEPRECATED_READDIR_R],
  [AC_REQUIRE([AC_PROG_CC])

  AC_MSG_CHECKING([whether readdir_r is deprecated])

  BACKUP_CFLAGS="$CFLAGS"

  # Force the compiler to treat warnings as errors
  CFLAGS="$CFLAGS -Werror -Wdeprecated-declarations"

  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
     [[#include <sys/types.h>
       #include <dirent.h>]],
     [[DIR *dirp = 0;
       struct dirent entry;
       struct dirent *result;
       readdir_r(dirp, &entry, &result);]])],
    [ac_cv_readdir_r_deprecated=no],
    [ac_cv_readdir_r_deprecated=yes])

  AC_MSG_RESULT(
    [$ac_cv_readdir_r_deprecated])

  AS_IF(
    [test "x$ac_cv_readdir_r_deprecated" = xyes],
    [AC_DEFINE(
      [HAVE_DEPRECATED_READDIR_R],
      [1],
      [Define to 1 whether readdir_r is deprecated.])
    ])

  CFLAGS="$BACKUP_CFLAGS"
  ])

dnl Function to detect if libcdirectory dependencies are available
AC_DEFUN([AX_LIBCDIRECTORY_CHECK_LOCAL],
  [AS_IF(
    [test "x$ac_cv_enable_winapi" = xno],
    [dnl Headers included in libcdirectory/libcdirectory_directory.h
    AC_CHECK_HEADERS([dirent.h errno.h sys/stat.h])

    dnl Directory functions used in libcdirectory/libcdirectory_directory.h
    AC_CHECK_FUNCS([closedir opendir readdir readdir_r])

    AS_IF(
      [test "x$ac_cv_func_closedir" != xyes],
      [AC_MSG_FAILURE(
        [Missing functions: closedir],
        [1])
      ])

    AS_IF(
      [test "x$ac_cv_func_opendir" != xyes],
      [AC_MSG_FAILURE(
        [Missing functions: opendir],
        [1])
      ])

    AS_IF(
      [test "x$ac_cv_func_readdir_r" = xyes],
      [AX_LIBCDIRECTORY_CHECK_DEPRECATED_READDIR_R],
      [AS_IF(
        [test "x$ac_cv_func_readdir" != xyes],
        [AC_MSG_FAILURE(
          [Missing functions: readdir and readdir_r],
          [1])
        ])
      ])
    ])
  ])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBCDIRECTORY_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBCDIRECTORY_DLL_EXPORT],
        ["-DLIBCDIRECTORY_DLL_EXPORT"])

      AC_SUBST(
        [LIBCDIRECTORY_DLL_IMPORT],
        ["-DLIBCDIRECTORY_DLL_IMPORT"])
      ])
    ])
  ])

