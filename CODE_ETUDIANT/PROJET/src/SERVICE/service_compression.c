#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_compression.h"
#include "tubesem.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données


/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */ int fd, char *data)
{
    printf("Receive data\n");

    myRead(fd, data, strlen(data) *sizeof(char));

}

// fonction de traitement des données
static void computeResult(/* données récupérées, */ /* résultat */char *data, char *res)
{
    int len = strlen(data) * 2;
    res = malloc( sizeof(char) * len);
    int count = 0;
    int i  = 0;
    while(data[i] != "\n"){
        if(strcmp(data[i], data[i+1])){
            count++;
        }else{
            res[i] = count;
            res[i+1] = data[i];
        }
        i++;
    }

}

// fonction d'envoi du résultat
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */ int fd, char *res)
{
    printf("Sending data");
    
    myWrite(fd, res, strlen(res) * sizeof(char) );

}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_compression(int fdSC, int fdCS)
{
    // initialisations diverses
    char *res;
    char *data;

    receiveData(/* paramètres */fdCS, *data);
    computeResult(/* paramètres */*data, *res);
    sendResult(/* paramètres */fdSC, *res);

    // libération éventuelle de ressources
    free(res);
}
