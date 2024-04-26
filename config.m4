PHP_ARG_WITH(pgf, [whether to enable pgf suppot],
[  --with-pgf[[=DIR]]       Enable pgf support.
                          DIR is the path to pgf install prefix])

if pgf "$PHP_PGF" != "no"; then
  AC_DEFINE(HAVE_PGF, 1, [ ])
  PHP_NEW_EXTENSION(pgf, php_pgf.c, $ext_shared)
fi