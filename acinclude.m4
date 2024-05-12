dnl Checks for required headers and functions
dnl
dnl Version: 20240413

dnl Function to detect if libcdirectory dependencies are available
AC_DEFUN([AX_LIBCDIRECTORY_CHECK_LOCAL],
  [AS_IF(
    [test "x$ac_cv_enable_winapi" = xno],
    [dnl Headers included in libcdirectory/libcdirectory_directory.h
    AC_CHECK_HEADERS([dirent.h errno.h sys/stat.h])

    dnl Directory functions used in libcdirectory/libcdirectory_directory.h
    AC_CHECK_FUNCS([closedir opendir readdir_r])

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
      [test "x$ac_cv_func_readdir_r" != xyes],
      [AC_MSG_FAILURE(
        [Missing functions: readdir_r],
        [1])
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

