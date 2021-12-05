#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_somme.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données


/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */int fd[2], float data1, float data2)
{
    printf("Receive data\n");
    close(fd[1]);
    
    int ret;
    ret = read(fd[0], &data1, sizeof(float));
    assert(ret == sizeof(int));
    
    ret = read(fd[0], &data2, sizeof(float));
    assert(ret == sizeof(int));
    
    close(fd[0]);
}

// fonction de traitement des données
static void computeResult(/* données récupérées, */ /* résultat */float data1, float data2, float res)
{
    res = data1 + data2;
}

// fonction d'envoi du résultat
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */int fd[2], float res)
{
    printf("Sending data");
    
    close(fd[0]);
    int ret;
    ret = write(fd[1], &res, sizeof(float) );
    assert(ret == size(int));

    close(fd[1]);
}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_somme(/* fd tubes nommés avec un client */int fd[2])
{
    // initialisations diverses
    float *res; 
    float *data1, *data2;
    receiveData(fd, *data1, *data2);
    computeResult(*data1, *data2, *res);
    sendResult(fd, *res);

    // libération éventuelle de ressources
}
