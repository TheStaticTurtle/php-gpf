/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+

 */

#include "php_pgf.h"
#include "php_pgf_int.h"

#include "pgf_decode.hpp"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

/* {{{ local prototypes */
static PHP_MINIT_FUNCTION(pgf);
static PHP_MSHUTDOWN_FUNCTION(pgf);
static PHP_MINFO_FUNCTION(pgf);

static PHP_GINIT_FUNCTION(pgf);

static PHP_FUNCTION(pgf_decode_to_rgba);
#ifdef HAVE_PGF_TO_PNG
static PHP_FUNCTION(pgf_decode_to_png);
#endif
/* }}} */


/* {{{ globals */
ZEND_DECLARE_MODULE_GLOBALS(pgf)
/* }}} */


/* {{{ ini entries */
PHP_INI_BEGIN()
PHP_INI_END()
/* }}} */


/* {{{ argument informations */
ZEND_BEGIN_ARG_INFO_EX(arginfo_pgf_decode_to_rgba, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, pgf_data)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

#ifdef HAVE_PGF_TO_PNG
ZEND_BEGIN_ARG_INFO_EX(arginfo_pgf_decode_to_png, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, pgf_data)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()
#endif

static zend_function_entry pgf_functions[] = {
	PHP_FE(pgf_decode_to_rgba,		arginfo_pgf_decode_to_rgba)
#ifdef HAVE_PGF_TO_PNG
	PHP_FE(pgf_decode_to_png,		arginfo_pgf_decode_to_png)
#endif
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
    php_info_print_table_row(2, "PGF Codec version", std::string(PGFCodecVersion).c_str());
	#ifdef HAVE_PGF_TO_PNG
    	php_info_print_table_row(2, "Export to PNG support", "On");
    	php_info_print_table_row(2, "LodePNG version", LODEPNG_VERSION_STRING);
	#else
    	php_info_print_table_row(2, "Export to PNG support", "Off");
	#endif
    php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(pgf) {
}


PHP_FUNCTION(pgf_decode_to_rgba){
	zend_string* pgf_data;
	int level = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S|l", &pgf_data, &level)) {
		return;
	}
	
	auto rgba_result = pgf_decode_to_rgba({ZSTR_VAL(pgf_data), ZSTR_LEN(pgf_data)}, level);
	
	// TODO: Return width/height/bpp

    zend_string * result = zend_string_init((char*)rgba_result.data, rgba_result.size(), 0);
    RETURN_STR(result);
}

#ifdef HAVE_PGF_TO_PNG
PHP_FUNCTION(pgf_decode_to_png){
	zend_string* pgf_data;
	int level = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S|l", &pgf_data, &level)) {
		return;
	}
	
	auto png_result = pgf_decode_to_png({ZSTR_VAL(pgf_data), ZSTR_LEN(pgf_data)}, level)

	RETURN_STR(png_result.c_str(), png_result.size());
}
#endif