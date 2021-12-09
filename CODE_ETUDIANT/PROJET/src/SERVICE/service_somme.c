#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_somme.h"
#include "tubesem.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données


/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */int fd, float data1, float data2)
{
    printf("Receive data\n");

    myRead(fd, &data1, sizeof(float));

    
    myRead(fd, &data2, sizeof(float));

    
}

// fonction de traitement des données
static void computeResult(/* données récupérées, */ /* résultat */float data1, float data2, float *res)
{
    float summ = data1 + data2;
    res = &summ;
}

// fonction d'envoi du résultat
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */int fd, float *res)
{
    printf("Sending data");
    
    myWrite(fd, &res, sizeof(float));
}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_somme(/* fd tubes nommés avec un client */int fdSC, int fdCS)
{
    // initialisations diverses
    float *res = NULL; 
    float data1 = 0.;
    float data2 = 0.;
    
    receiveData(fdCS, data1, data2);
    computeResult(data1, data2, res);
    sendResult(fdSC, res);

    // libération éventuelle de ressources
}
