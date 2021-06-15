#include "../include/regulation.h"


Regulation::Regulation():
    shmpath("/regShm")
{

    int fd = shm_open(shmpath, O_CREAT | O_RDWR, S_IRUSR| S_IWUSR);
    // mozliwe ze trezba bedzie zmienic na  O_RDONLY
    //S_IRUSR read permission
    //S_IWUSR write permision
    if (fd == -1)
        errExit("shm_open");

    if (ftruncate(fd, sizeof(struct shm_data)) == -1)
        errExit("ftruncate");

    shm = (shm_data*) mmap(NULL, sizeof(struct shm_data), PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);

    if(pthread_rwlockattr_init(&shm->attr) != 0)
        qDebug()<<"rwlockattr_init";

    if(pthread_rwlockattr_setpshared(&shm->attr, PTHREAD_PROCESS_SHARED) != 0)
        qDebug()<<"setpshared";

    if(pthread_rwlock_init(&shm->rw, &shm->attr) == -1)
        qDebug()<<"rwlock_init";

    wyjscieZadane = 25;
}

Regulation::~Regulation(){
    pthread_rwlockattr_destroy(&shm->attr);
    pthread_rwlock_destroy(&shm->rw);
    shm_unlink(shmpath);
}

void Regulation::read()
{
    if(pthread_rwlock_tryrdlock(&shm->rw) == 0)
    {
        memcpy(&wyjscie,&shm->Y, sizeof(double));
        memcpy(&zaklucenie,&shm->Z, sizeof(double));
        memcpy(&sterowanie,&shm->U, sizeof(double));
        pthread_rwlock_unlock(&shm->rw);
    }

    emit valueWyjscieChanged(wyjscie, wyjscieZadane);
    emit valueSterowanieChanged(sterowanie);
    emit valueZaklucenieChanged(zaklucenie);
}

void Regulation::setWyjscieZadane(double val){
    if(val != wyjscieZadane){
        wyjscieZadane = val;
    }
}
