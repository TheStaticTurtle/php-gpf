/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+

 */

#include "php_pgf.h"
#include "php_pgf_int.h"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

/* {{{ local prototypes */
static PHP_MINIT_FUNCTION(pgf);
static PHP_MSHUTDOWN_FUNCTION(pgf);
static PHP_MINFO_FUNCTION(pgf);

static PHP_GINIT_FUNCTION(pgf);

static PHP_FUNCTION(pgf_fn1);
static PHP_FUNCTION(pgf_fn2);
/* }}} */


/* {{{ globals */
ZEND_DECLARE_MODULE_GLOBALS(pgf)
/* }}} */


/* {{{ ini entries */
PHP_INI_BEGIN()
PHP_INI_END()
/* }}} */


/* {{{ argument informations */
ZEND_BEGIN_ARG_INFO_EX(arginfo_pgf_fn1, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_pgf_fn2, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

static zend_function_entry pgf_functions[] = {
	PHP_FE(pgf_fn1,		arginfo_pgf_fn1)
	PHP_FE(pgf_fn2,		arginfo_pgf_fn2)
	PHP_FE_END
};
/* }}} */

/* {{{ cross-extension dependencies */
static zend_module_dep pgf_deps[] = {
//	ZEND_MOD_OPTIONAL("date")
	ZEND_MOD_END
};
/* }}} */


zend_module_entry pgf_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	pgf_deps,
	"pgf",
	pgf_functions,
	PHP_MINIT(pgf),
	PHP_MSHUTDOWN(pgf),
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	PHP_MINFO(pgf),
	PHP_PGF_VERSION,
	PHP_MODULE_GLOBALS(pgf),
	PHP_GINIT(pgf),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_PGF
ZEND_GET_MODULE(pgf)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif


static PHP_MINIT_FUNCTION(pgf) {
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(pgf) {
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(pgf) {
    php_info_print_table_start();
    php_info_print_table_row(2, "PGF Support", "enabled");
    php_info_print_table_row(2, "Version", PHP_PGF_VERSION);
    php_info_print_table_row(2, "PGFCodec Version", std::string(PGFCodecVersion).c_str());
    php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(pgf) {
}


PHP_FUNCTION(pgf_fn1){
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "pgf");
	
	RETURN_NULL();
}

PHP_FUNCTION(pgf_fn2){
	zend_string *input;
	
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S", &input)) {
		return;
	}
	
    zend_string *hex_str = zend_string_safe_alloc(2, ZSTR_LEN(input), 0, /* persistent */ 0);
    char *p = ZSTR_VAL(hex_str);
    for (size_t i = 0; i < ZSTR_LEN(input); i++) {
        const char *to_hex = "0123456789abcdef";
        unsigned char c = ZSTR_VAL(input)[i];
        *p++ = to_hex[c >> 4];
        *p++ = to_hex[c & 0xf];
    }
    *p = '\0';
	
	RETURN_STR(hex_str);
}