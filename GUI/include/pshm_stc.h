#ifndef PSHM_STC_H
#define PSHM_STC_H

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0)

struct shm_data{
    pthread_rwlock_t rw;
    pthread_rwlockattr_t attr;
    double Y;
    double U;
    double Z;

};

#endif // PSHM_STC_H
