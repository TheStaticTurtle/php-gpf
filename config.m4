dnl config.m4 for extension gpf

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([gpf],
dnl   [for gpf support],
dnl   [AS_HELP_STRING([--with-gpf],
dnl     [Include gpf support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([gpf],
  [whether to enable gpf support],
  [AS_HELP_STRING([--enable-gpf],
    [Enable gpf support])],
  [no])

if gpf "$PHP_TEST" != "no"; then
  AC_DEFINE(HAVE_GPF, 1, [ Have gpf support ])

  PHP_NEW_EXTENSION(gpf, php_gpf.c, $ext_shared)
fi