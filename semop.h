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
#ifndef SEMOP_H
#define SEMOP_H
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>

typedef int sem_t;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arr;
};

extern sem_t create_sem(key_t key, int value);
extern int sem_p(sem_t sem_id);
extern int sem_v(sem_t sem_id);
extern void sem_destroy(sem_t sem_id);  

#endif
