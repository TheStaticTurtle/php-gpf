/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+

 */

#ifndef PHP_GPF_H
#define PHP_GPF_H

#include "gpf_php.h"

#define PHP_GPF_VERSION "0.1.0"

extern zend_module_entry gpf_module_entry;
#define phpext_gpf_ptr &gpf_module_entry

# if defined(ZTS) && defined(COMPILE_DL_GPF)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

ZEND_BEGIN_MODULE_GLOBALS(gpf)
	zend_long scale;
ZEND_END_MODULE_GLOBALS(gpf)

ZEND_EXTERN_MODULE_GLOBALS(gpf)

#define TEST_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(gpf, v)

#endif /* PHP_GPF_H */