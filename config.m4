PHP_ARG_WITH(pgf, [whether to enable pgf suppot],
[  --with-pgf[[=DIR]]       Enable pgf support.
                          DIR is the path to pgf install prefix])

if pgf "$PHP_c" != "no"; then
	CXXFLAGS="-std=c++11"
	PHP_REQUIRE_CXX()
	PHP_SUBST(PGF_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, PGF_SHARED_LIBADD)
	
	PHP_ADD_INCLUDE(libpgf/include)
  
	AC_DEFINE(HAVE_PGF, 1, [ ])
	PHP_NEW_EXTENSION(pgf, php_pgf.cpp pgf_decode.cpp, $ext_shared)
fi