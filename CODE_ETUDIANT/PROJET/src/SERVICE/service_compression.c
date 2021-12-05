#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_compression.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données


/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */ int fd[2], char *data)
{
    printf("Receive data\n");
    close(fd[1]);
    
    int ret;
    ret = read(fd[0], data, strlen(data) *sizeof(char));
    assert(ret == (int ) (strlen(res) *size(char)));
    
    close(fd[0]);
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
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */ int fd[2], char *res)
{
    printf("Sending data");
    
    close(fd[0]);
    int ret;
    ret = write(fd[1], res, strlen(res) * sizeof(char) );
    assert(ret == (int ) (strlen(res) *size(char)));

    close(fd[1]);
}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_compression(/* fd tubes nommés avec un client */int fd[2])
{
    // initialisations diverses
    char *res;
    char *data;

    receiveData(/* paramètres */fd, *data);
    computeResult(/* paramètres */*data, *res);
    sendResult(/* paramètres */fd, *res);

    // libération éventuelle de ressources
    free(res);
}
