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
#include "semop.h"

sem_t create_sem(key_t key, int value) {
    union semun sem;
    sem_t semid;
    sem.val = value;
    semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0666);
    if (-1 == semid) {
        semid = semget(key, 1, IPC_EXCL|0666);
    } else {
        if (semctl(semid, 0, SETVAL, sem) == -1) {
            fprintf(stderr, "sem ctl error %d\n", errno);
            return -1;
        }
    }

    return semid;
}

//add sem
int sem_p(sem_t sem_id) {
    struct sembuf sops = {0, -1, SEM_UNDO};
    if (semop(sem_id,&sops, 1) == -1) {
        fprintf(stderr, "sem op error %d\n", errno);
        return -1;
    }
    return 0;
}

int sem_v(sem_t sem_id) {
    struct sembuf sops = {0, +1, SEM_UNDO};
    if (semop(sem_id, &sops, 1) == -1) {
        fprintf(stderr, "sem op error %d\n", errno);
        return -1;
    }
    return 0;
}

void sem_destroy(sem_t sem_id) {
    union semun sem;
    sem.val = 0;
    if (sem_id != 0 && semctl(sem_id, 0, IPC_RMID, sem) == -1) {
        fprintf(stderr, "sem destroy erro %d\n", errno);
    }
}
