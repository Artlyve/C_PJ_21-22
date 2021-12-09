#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_maximum.h"
#include "tubesem.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données


/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// ---- THREADS SERVICE ----

void myCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
    int test = pthread_create(thread, attr, start_routine, arg);
    myassert(test > -1, "ERROR : Thread isn't created !");
}

void myJoin(pthread_t thread, void **retval)
{
    int test = pthread_join(thread, retval);
    myassert(test > -1, "ERROR : Thread isn't join !");
}

/*Initialisation des thread*/
void preInitThread(int nbThread, float *tabFloat, int debut, int fin, ThreadData *data)
{
    for (int i = 0; i < nbThread; i++)
    {
        data[i].tabValue = tabFloat;
        data[i].res = 0;
        data[i].debut = debut;
        data[i].fin = fin;
    }
}

int length(float *tab)
{

    int count = 0;

    while(tab[count] != '\0')
    {
        count ++;
    }
    return count;
}


/*Code des threads du service*/
void *codeThread(void *var)
{
    ThreadData *d = (ThreadData*) var;

    int i;

    float maximum = d->tabValue[0];


    for(i = (d->debut); i < (d->fin); i++)
    {
        if(maximum < (d->tabValue[i]))
        {
            maximum = (d->tabValue[i]);
        }
    }

    *(d->res) = maximum;

    return NULL;
}

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */int fd, int nbThread, float *tabFloat)
{
    printf("Receive data\n");

    myRead(fd, &nbThread, sizeof(int));

    myRead(fd, tabFloat, sizeof(float));
}

// fonction de traitement des données
static void computeResult(/* données récupérées, */ /* résultat */int nbThread, float *tabFloat, float *res)
{
    int len = length(tabFloat);
    int coef = len/nbThread;

    pthread_t tabTid[nbThread];
    ThreadData data[nbThread];

    // pré-initialisation des données
    for(int i = 0; i < nbThread; i++)
    {
        if (i == nbThread - 1)
        {
            preInitThread(nbThread, tabFloat, (&data[i-1])->fin + 1, len, data);
        }
        else if (i == 0)
        {
            preInitThread(nbThread, tabFloat, 0, coef, data);
        }else
        {
            preInitThread(nbThread, tabFloat, (&data[i-1])->fin + 1, (&data[i-1])->fin + coef, data);
        }
    }

    // lancement des threads
    for(int i = 0; i < nbThread; i++)
    {
        myCreate(&(tabTid[i]), NULL, codeThread, &(data[i]));
    }

    //Attente de la fin des threads
    for(int i = 0; i < nbThread; i++)
    {
        myJoin(tabTid[i], NULL);
    }

    //Processus de recherche du maximum entre thread
    for(int i = 0; i < nbThread; i++)
    {
        if ((&data[i])->res > res)
        {
            res = (&data[i-1])->res;
        }
    }
}

// fonction d'envoi du résultat
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */int fd, float res)
{
    printf("Sending data");
    
    myWrite(fd, &res, sizeof(float));
}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_maximum(int fdSC, int fdCS)
{
    // initialisations diverses
    float *res = NULL;
    float *tabFloat = NULL;
    int nbTH = 0;
    
    receiveData(/* paramètres */fdCS, nbTH, tabFloat);
    computeResult(/* paramètres */nbTH, tabFloat, res);
    sendResult(/* paramètres */fdSC, *res);

    // libération éventuelle de ressources
}
