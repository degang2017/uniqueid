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
   | Authors: shendegang <php_shen@163.com>                              |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_uniqueid.h"

/* If you declare any globals in php_uniqueid.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(uniqueid)
*/

/* True global resources - no need for thread safety here */
static int le_uniqueid;
struct timeval tv;
sem_t mysem;
key_t mykey;

void generate() {
	gettimeofday(&tv, NULL);	
	cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    uuid = ((uuid & cur_time) << 22) 
        | ((iden & 0x000000000000FFF) << 10 ) | icrn_num;
}


unsigned long int id_time() {
    return  uuid >> 22;
}

unsigned int id_icrn() {
    return (uuid << 54) >> 54;
}

unsigned int id_iden() {
    return (uuid >> 10)&0x0000000000000FFF;
}

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_uniqueid_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_uniqueid_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "uniqueid", arg);

	RETURN_STR(strg);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(uniqueid)
{
    icrn_num = 0;
    iden = 0;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(uniqueid)
{
    delete_shm();
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(uniqueid)
{
#if defined(COMPILE_DL_UNIQUEID) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(uniqueid)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(uniqueid)
{
	php_info_print_table_start();
	php_info_print_table_header(2,  "uniqueid support", "enabled");
	php_info_print_table_row(2,     "uniqueid version", PHP_UNIQUEID_VERSION);
	php_info_print_table_end();

}
/* }}} */

PHP_FUNCTION(generate_id_time) 
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l", &uuid) == FAILURE) {
        RETURN_NULL();  
    }

	RETURN_LONG(id_time());
}


PHP_FUNCTION(generate_id_iden) 
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l", &uuid) == FAILURE) {
        RETURN_NULL();  
    }

	RETURN_LONG(id_iden());
}

PHP_FUNCTION(generate_id)
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l", &iden) == FAILURE) {
        RETURN_NULL();  
    }

    mykey = ftok("./", iden);
    mysem = create_sem(mykey, 1);
    create_shm(mykey);

    union semun sem;
    uuid = 0xFFFFFFFFFFFFFFFF;

    sem_p(mysem);
    icrn_num = icrn_shm();    
    generate();
	sem_v(mysem);

    delete_shm();
	RETURN_LONG(uuid);
}

/* {{{ uniqueid_functions[]
 *
 * Every user visible function must have an entry in uniqueid_functions[].
 */
const zend_function_entry uniqueid_functions[] = {
	PHP_FE(confirm_uniqueid_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(generate_id,                 NULL) 
	PHP_FE(generate_id_time,            NULL) 
	PHP_FE(generate_id_iden,            NULL) 
	PHP_FE_END	/* Must be the last line in uniqueid_functions[] */
};
/* }}} */

/* {{{ uniqueid_module_entry
 */
zend_module_entry uniqueid_module_entry = {
	STANDARD_MODULE_HEADER,
	"uniqueid",
	uniqueid_functions,
	PHP_MINIT(uniqueid),
	PHP_MSHUTDOWN(uniqueid),
	PHP_RINIT(uniqueid),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(uniqueid),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(uniqueid),
	PHP_UNIQUEID_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_UNIQUEID
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(uniqueid)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
