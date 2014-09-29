dnl Functions for libcdirectory
dnl
dnl Version: 20140929

dnl Function to detect if libcdirectory is available
dnl ac_libcdirectory_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_DEFUN([AX_LIBCDIRECTORY_CHECK_LIB],
 [dnl Check if parameters were provided
 AS_IF(
  [test "x$ac_cv_with_libcdirectory" != x && test "x$ac_cv_with_libcdirectory" != xno && test "x$ac_cv_with_libcdirectory" != xauto-detect],
  [AS_IF(
   [test -d "$ac_cv_with_libcdirectory"],
   [CFLAGS="$CFLAGS -I${ac_cv_with_libcdirectory}/include"
   LDFLAGS="$LDFLAGS -L${ac_cv_with_libcdirectory}/lib"],
   [AC_MSG_WARN([no such directory: $ac_cv_with_libcdirectory])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_with_libcdirectory" = xno],
  [ac_cv_libcdirectory=no],
  [dnl Check for a pkg-config file
  AS_IF(
   [test "x$cross_compiling" != "xyes" && test "x$PKGCONFIG" != "x"],
   [PKG_CHECK_MODULES(
    [libcdirectory],
    [libcdirectory >= 20120423],
    [ac_cv_libcdirectory=yes],
    [ac_cv_libcdirectory=no])
   ])

  AS_IF(
   [test "x$ac_cv_libcdirectory" = xyes],
   [ac_cv_libcdirectory_CPPFLAGS="$pkg_cv_libcdirectory_CFLAGS"
   ac_cv_libcdirectory_LIBADD="$pkg_cv_libcdirectory_LIBS"],
   [dnl Check for headers
   AC_CHECK_HEADERS([libcdirectory.h])
 
   AS_IF(
    [test "x$ac_cv_header_libcdirectory_h" = xno],
    [ac_cv_libcdirectory=no],
    [dnl Check for the individual functions
    ac_cv_libcdirectory=yes

    AC_CHECK_LIB(
     cdirectory,
     libcdirectory_get_version,
     [ac_cv_libcdirectory_dummy=yes],
     [ac_cv_libcdirectory=no])
  
    dnl TODO add functions

    ac_cv_libcdirectory_LIBADD="-lcdirectory"
    ])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_libcdirectory" = xyes],
  [AC_DEFINE(
   [HAVE_LIBCDIRECTORY],
   [1],
   [Define to 1 if you have the `cdirectory' library (-lcdirectory).])
  ])

 AS_IF(
  [test "x$ac_cv_libcdirectory" = xyes],
  [AC_SUBST(
   [HAVE_LIBCDIRECTORY],
   [1]) ],
  [AC_SUBST(
   [HAVE_LIBCDIRECTORY],
   [0])
  ])
 ])

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
 
 ac_cv_libcdirectory_CPPFLAGS="-I../libcdirectory";
 ac_cv_libcdirectory_LIBADD="../libcdirectory/libcdirectory.la";

 ac_cv_libcdirectory=local
 ])

