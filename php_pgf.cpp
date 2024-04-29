#include "php_pgf.h"

#include "pgf_decode.hpp"

#include <string>
#include <stdexcept>

#ifdef __cplusplus
extern "C" {
#endif

ZEND_DECLARE_MODULE_GLOBALS(pgf)

PHP_INI_BEGIN()
PHP_INI_END()

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

static zend_module_dep pgf_deps[] = {
	ZEND_MOD_END
};

zend_module_entry pgf_module_entry = {
	STANDARD_MODULE_HEADER_EX,     /* size, zend_api, zend_debug, zts, ini_entry, deps */
	NULL,                          /* ini_entry */
	pgf_deps,                      /* deps */
	"pgf",                         /* name */
	pgf_functions,                 /* functions */
	PHP_MINIT(pgf),                /* module_startup_func   PHP_MINIT(pgf) */
	PHP_MSHUTDOWN(pgf),            /* module_shutdown_func  PHP_MSHUTDOWN(pgf) */
	NULL,                          /* request_startup_func  PHP_RINIT(pgf) */
	NULL,                          /* request_shutdown_func PHP_RSHUTDOWN(pgf) */
	PHP_MINFO(pgf),                /* info_func             PHP_MINFO(pgf) */
	PHP_PGF_VERSION,               /* version */
	PHP_MODULE_GLOBALS(pgf),       /* globals_size, globals_id_ptr, globals_ptr, globals_ctor, globals_dtor */
	PHP_GINIT(pgf),                /* globals_ctor          PHP_GINIT(pgf) */
	NULL,                          /* globals_dtor          PHP_GSHUTDOWN(pgf) */
	NULL,                          /* post_deactivate_func */
	STANDARD_MODULE_PROPERTIES_EX  /* module_started, type, handle, module_number */
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
static PHP_MINFO_FUNCTION(pgf) {
    php_info_print_table_start();
    php_info_print_table_row(2, "PGF Support", "enabled");
    php_info_print_table_row(2, "Version", PHP_PGF_VERSION);
    php_info_print_table_row(2, "PGF Codec version", std::string(PGFCodecVersion).c_str());
    php_info_print_table_row(2, "LodePNG version", LODEPNG_VERSION_STRING);
    php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
static PHP_GINIT_FUNCTION(pgf) {}


static PHP_FUNCTION(pgf_decode_to_rgba){
	zend_string* pgf_data;
	int level = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S|l", &pgf_data, &level)) {
		zend_throw_exception(NULL, "Invalid argument provided to \"pgf_decode_to_rgba\"", 0);
		RETURN_NULL();
	}
	
	rgba_image rgba_result;
	try {
		rgba_result = pgf_decode_to_rgba({ZSTR_VAL(pgf_data), ZSTR_LEN(pgf_data)}, level);
	} catch (...) {
		zend_throw_exception(NULL, "Failure occured while running \"pgf_decode_to_rgba\"", 0);
		RETURN_NULL();
	}

	array_init(return_value);
	add_assoc_long(return_value, "height", rgba_result.height);
	add_assoc_long(return_value, "width",  rgba_result.width);
	add_assoc_long(return_value, "byte_per_pixel", rgba_result.byte_per_pixel);
	add_assoc_stringl(return_value, "data", (char*)rgba_result.data, rgba_result.size());
}

static PHP_FUNCTION(pgf_decode_to_png){
	zend_string* pgf_data;
	int level = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "S|l", &pgf_data, &level)) {
		zend_throw_exception(NULL, "Invalid argument provided to \"pgf_decode_to_png\"", 0);
		RETURN_NULL();
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