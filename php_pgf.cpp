/*
  +----------------------------------------------------------------------+
  | PHP-PGF                                                              |
  +----------------------------------------------------------------------+

 */

#include "php_pgf.h"
#include "php_pgf_int.h"

#include "pgf_decode.hpp"

#include <string>
#include <stdexcept>

#ifdef __cplusplus
extern "C" {
#endif

/* {{{ local prototypes */
static PHP_MINIT_FUNCTION(pgf);
static PHP_MSHUTDOWN_FUNCTION(pgf);
static PHP_MINFO_FUNCTION(pgf);

static PHP_GINIT_FUNCTION(pgf);

static PHP_FUNCTION(pgf_decode_to_rgba);
static PHP_FUNCTION(pgf_decode_to_png);
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_pgf_decode_to_png, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, pgf_data)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

static zend_function_entry pgf_functions[] = {
	PHP_FE(pgf_decode_to_rgba,		arginfo_pgf_decode_to_rgba)
	PHP_FE(pgf_decode_to_png,		arginfo_pgf_decode_to_png)
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
    php_info_print_table_row(2, "LodePNG version", LODEPNG_VERSION_STRING);
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
	
	rgba_image rgba_result;
	try {
		rgba_result = pgf_decode_to_rgba({ZSTR_VAL(pgf_data), ZSTR_LEN(pgf_data)}, level);
	} catch (...) {
		zend_throw_exception(NULL, "Failure occured while running \"pgf_decode_to_rgba\"", 0);
		RETURN_NULL();
	}

    //zend_string* data = zend_string_init((char*)rgba_result.data, rgba_result.size(), 0);
    //RETVAL_STR(data);

	array_init(return_value);
	add_assoc_long(return_value, "height", rgba_result.height);
	add_assoc_long(return_value, "width",  rgba_result.width);
	add_assoc_long(return_value, "byte_per_pixel", rgba_result.byte_per_pixel);
	add_assoc_stringl(return_value, "data", (char*)rgba_result.data, rgba_result.size());

    //RETVAL_ARR(result);
}

PHP_FUNCTION(pgf_decode_to_png){
	zend_string* pgf_data;
	int level = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S|l", &pgf_data, &level)) {
		return;
	}
	
	std::string png_result;
	try {
		png_result = pgf_decode_to_png({ZSTR_VAL(pgf_data), ZSTR_LEN(pgf_data)}, level);
	} catch (...) {
		zend_throw_exception(NULL, "Failure occured while running \"pgf_decode_to_png\"", 0);
		RETURN_NULL();
	}

    zend_string * result = zend_string_init(png_result.c_str(), png_result.size(), 0);
    RETURN_STR(result);
}