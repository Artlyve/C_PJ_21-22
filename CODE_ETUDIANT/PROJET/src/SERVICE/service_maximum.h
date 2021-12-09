#ifndef SERVICE_MAXIMUM_H
#define SERVICE_MAXIMUM_H

// on ne déclare ici que les fonctions appelables par le main

//Structure pour les thread
typedef struct
{
    float *tabValue;
    float *res;
    int debut;
    int fin;
}ThreadData;

// ---- THREADS CLIENT ----

void myCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
void myJoin(pthread_t thread, void **retval);

/*Initialisation des thread*/
void preInitThread(int nbThread, float *tabFloat, int debut, int fin, ThreadData *data);

/*Code des threads du client*/
void *codeThread(void *var);

// fonction pour gérer la communication avec le client
void service_maximum(int fdSC, int fdCS);

#endif