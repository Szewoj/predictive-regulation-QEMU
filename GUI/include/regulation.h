#ifndef REGULATION_H
#define REGULATION_H

#include <QObject>
#include <include/pshm_stc.h>



class Regulation:public QObject
{
    Q_OBJECT
public:
    Regulation();
    ~Regulation();

    double getWyjscie();
    double getSterowanie();
    double getZaklucenie();

public slots:
    void read();
    void setWyjscieZadane(double val);

signals:
    void valueWyjscieChanged(double new_val, double val_zad);
    void valueSterowanieChanged(double new_val);
    void valueZaklucenieChanged(double new_val);
    //void valueWyjscieZadaneChanged(double new_val);

private:
    double wyjscieZadane;
    double wyjscie;
    double sterowanie;
    double zaklucenie;

    char *shmpath;
    int file_desc;
    struct shm_data *shm;
};

#endif // REGULATION_H
