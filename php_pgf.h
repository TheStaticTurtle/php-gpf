#ifndef PHP_PGF_H
#define PHP_PGF_H

#define PHP_PGF_VERSION "1.0.0"

#ifdef __cplusplus
extern "C" {
#endif
	#include <php.h>
	#include <php_ini.h>
	#include <SAPI.h>

	#include "zend_exceptions.h"

	#include <ext/standard/info.h>

	extern zend_module_entry pgf_module_entry;
	#define phpext_pgf_ptr &pgf_module_entry

	ZEND_BEGIN_MODULE_GLOBALS(pgf)
	ZEND_END_MODULE_GLOBALS(pgf)
	
	ZEND_EXTERN_MODULE_GLOBALS(pgf)

	static PHP_MINIT_FUNCTION(pgf);
	static PHP_MSHUTDOWN_FUNCTION(pgf);
	static PHP_MINFO_FUNCTION(pgf);
	static PHP_GINIT_FUNCTION(pgf);

	static PHP_FUNCTION(pgf_decode_to_rgba);
	static PHP_FUNCTION(pgf_decode_to_png);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PHP_PGF_H */