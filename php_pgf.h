/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+
 */

#ifndef PHP_PGF_H
#define PHP_PGF_H

#ifdef __cplusplus
extern "C" {
#endif

	#include <php.h>
	#include <php_ini.h>
	#include <SAPI.h>
	#ifdef ZTS
	#	include "TSRM.h"
	#endif

	#include <ext/standard/info.h>
	#include <ext/standard/base64.h>

#ifdef __cplusplus
} /* extern "C" */
#endif



#ifdef __cplusplus
extern "C" {
#endif

	#define PHP_PGF_VERSION "0.1.0"

	extern zend_module_entry pgf_module_entry;
	#define phpext_pgf_ptr &pgf_module_entry

	ZEND_BEGIN_MODULE_GLOBALS(pgf)
		zend_long scale;
	ZEND_END_MODULE_GLOBALS(pgf)

	ZEND_EXTERN_MODULE_GLOBALS(pgf)
	#ifdef ZTS
	#	define PGF_G(v) TSRMG(pgf_globals_id, zend_pgf_globals *, v)
	#else
	#	define PGF_G(v) (pgf_globals.v)
	#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* PHP_PGF_H */