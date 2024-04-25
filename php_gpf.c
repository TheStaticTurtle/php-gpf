/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+

 */

#include "php.h"
#include "ext/standard/info.h"
#include "php_gpf.h"

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() ZEND_PARSE_PARAMETERS_START(0, 0) ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(pgf)


PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("gpf.scale", "1", PHP_INI_ALL, OnUpdateLong, scale, zend_gpf_globals, gpf_globals)
PHP_INI_END()


PHP_FUNCTION(gpf_fn1){
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "test");
}

PHP_FUNCTION(gpf_fn2){
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}


static PHP_GINIT_FUNCTION(gpf) {
	#if defined(COMPILE_DL_BCMATH) && defined(ZTS)
		ZEND_TSRMLS_CACHE_UPDATE();
	#endif
	gpf_globals->scale= 1;
}

PHP_MINIT_FUNCTION(gpf) {
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}


PHP_MINFO_FUNCTION(gpf) {
    php_info_print_table_start();
    php_info_print_table_row(2, "GPF Support", "enabled");
    php_info_print_table_row(2, "Version", GPF_VERSION);
    php_info_print_table_end();
}

ZEND_BEGIN_ARG_INFO(arginfo_gpf_fn1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gpf_fn2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()


static const zend_function_entry gpf_functions[] = {
	PHP_FE(gpf_fn1,		arginfo_gpf_fn1)
	PHP_FE(gpf_fn2,		arginfo_gpf_fn2)
	PHP_FE_END
};

zend_module_entry gpf_module_entry = {
	STANDARD_MODULE_HEADER,
	"gpf",					 /* Extension name */
	gpf_functions,			 /* zend_function_entry */
	PHP_MINIT(gpf),			 /* PHP_MINIT - Module initialization */
	NULL,					 /* PHP_MSHUTDOWN - Module shutdown */
	NULL,					 /* PHP_RINIT - Request initialization */
	NULL,					 /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(gpf),			 /* PHP_MINFO - Module info */
	PHP_TEST_VERSION,		 /* Version */
	PHP_MODULE_GLOBALS(gpf), /* Module globals */
	PHP_GINIT(gpf),			 /* PHP_GINIT - Globals initialization */
	NULL,					 /* PHP_GSHUTDOWN - Globals shutdown */
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_TEST
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(gpf)
#endif