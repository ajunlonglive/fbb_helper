/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_kmf_helper.h"

/* If you declare any globals in php_kmf_helper.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(kmf_helper)
*/

/* True global resources - no need for thread safety here */
static int le_kmf_helper;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("kmf_helper.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_kmf_helper_globals, kmf_helper_globals)
    STD_PHP_INI_ENTRY("kmf_helper.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_kmf_helper_globals, kmf_helper_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_kmf_helper_compiled(string arg)
   Return a string to confirm that the module is compiled in */
//PHP_FUNCTION(kmf_array_map)
//{
//	HashTable *arr_input;
//	char *arg = NULL;
//	size_t arg_len, len;
//	//zend_string *strg;
//	zval *entry_key;
//
//	if (zend_parse_parameters(ZEND_NUM_ARGS(), "hs", &arr_input, &arg, &arg_len) == FAILURE) {
//		return;
//	}
//
//	//strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "kmf_helper", arg);
//
//	//RETURN_STR(strg);
//}
PHP_FUNCTION(kmf_array_map) {
	HashTable *keys;
	char *arg = NULL;
	char *arg_value = NULL;
	size_t arg_len;
	size_t arg_value_len;
	uint32_t pos_values = 0;
	zval *entry_keys, *entry_values, *tmp_val;
	int num_keys;
	zend_string *strkey, *str_key_value;
	

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "hs|s", &keys, &arg, &arg_len, &arg_value, &arg_value_len) == FAILURE) {
		return;
	}

	num_keys = zend_hash_num_elements(keys);
	//格式化字符串
	strkey = strpprintf(0, "%.78s", arg);
	//测试索引
	//RETURN_STR(strkey);

	if (num_keys == 0) {
		php_error_docref(NULL, E_WARNING, "The input arr was empty!");
		RETURN_FALSE;
	}
	//初始化返回的数组
	array_init_size(return_value, num_keys);
	//如果需转换的数组长度为0，则返回错误
	if (!num_keys) {
		return;
	}
	//遍历hash表
	ZEND_HASH_FOREACH_VAL(keys, entry_keys) {
		while (1) {
			if (pos_values >= keys->nNumUsed) {
				break;
			}
			else if (Z_TYPE(keys->arData[pos_values].val) != IS_UNDEF) {
				//如果数组内不存在指定的索引，则返回错误
				if (zend_hash_str_exists(Z_ARRVAL_P(entry_keys), arg, arg_len)) {
					//验证检查索引是否存在
					/*php_error_docref(NULL, E_WARNING, "defined index in array");
					RETURN_FALSE;*/
					//在hash表中查找指定索引对应的值
					tmp_val = zend_hash_find(Z_ARRVAL_P(entry_keys), strkey);
					if (arg_value == NULL) {
						entry_values = entry_keys;
					}
					else
					{
						str_key_value = strpprintf(0, "%s", arg_value);
						entry_values = zend_hash_find(Z_ARRVAL_P(entry_keys), str_key_value);
					}
							
							//如果指定索引的值为整型
							if (Z_TYPE_P(tmp_val) == IS_LONG) {
								entry_values = zend_hash_index_update(Z_ARRVAL_P(return_value),
									Z_LVAL_P(tmp_val), entry_values);
							}
							else {//否则为字符串
								zend_string *key = zval_get_string(tmp_val);
								entry_values = zend_symtable_update(Z_ARRVAL_P(return_value),
									key, entry_values);
								zend_string_release(key);
							}
							zval_add_ref(entry_values);
							pos_values++;
							break;

					
				}
				else {
					php_error_docref(NULL, E_WARNING, "undefined index in array");
					RETURN_FALSE;
				}
				
				
				
			}
			pos_values++;
		}
	} ZEND_HASH_FOREACH_END();
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_kmf_helper_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_kmf_helper_init_globals(zend_kmf_helper_globals *kmf_helper_globals)
{
	kmf_helper_globals->global_value = 0;
	kmf_helper_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(kmf_helper)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(kmf_helper)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(kmf_helper)
{
#if defined(COMPILE_DL_KMF_HELPER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(kmf_helper)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(kmf_helper)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "kmf_helper support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ kmf_helper_functions[]
 *
 * Every user visible function must have an entry in kmf_helper_functions[].
 */
const zend_function_entry kmf_helper_functions[] = {
	PHP_FE(kmf_array_map,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in kmf_helper_functions[] */
};
/* }}} */

/* {{{ kmf_helper_module_entry
 */
zend_module_entry kmf_helper_module_entry = {
	STANDARD_MODULE_HEADER,
	"kmf_helper",
	kmf_helper_functions,
	PHP_MINIT(kmf_helper),
	PHP_MSHUTDOWN(kmf_helper),
	PHP_RINIT(kmf_helper),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(kmf_helper),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(kmf_helper),
	PHP_KMF_HELPER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_KMF_HELPER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(kmf_helper)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
