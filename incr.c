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
#include "incr.h"
   
int create_shm(key_t key) {
    shm_t shmid = shmget(key, 128, IPC_CREAT|IPC_EXCL|0604);

    if (shmid == -1) {
        shmid = shmget(key, 128, IPC_EXCL|0604);
    } 

    shms = (int *)shmat(shmid, 0, 0);
    if (*shms == -1) {
        fprintf(stderr, "shmat create error %d\n", errno);
        return -1;
    }
    return shmid;
}

int delete_shm() {
    if (shms != 0 && shmdt(shms) == -1) {
        fprintf(stderr, "shmdt delete error %d\n", errno);
        return -1;
    }
    return 0;
}

int icrn_shm() {
    if ((*shms) >= 4095) {
        (*shms) = 0;
    } else {
        (*shms) += 1;
    }
    return *shms;
}
