#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "orchestre_service.h"
#include "client_service.h"

#include "service_maximum.h"
#include "tubesem.h"
#include "myassert.h"

// définition éventuelle de types pour stocker les données

/*----------------------------------------------*
 * fonctions appelables par le service
 *----------------------------------------------*/

// fonction de réception des données
static void receiveData(/* fd_pipe_from_client, */ /* données à récupérer */int fd, float *tabFloat)
{
    printf("Receive data\n");

    myRead(fd, tabFloat, sizeof(float));
}

// fonction de traitement des données
static void computeResult(/* données récupérées, */ /* résultat */float *tabFloat, float res)
{
    
}

// fonction d'envoi du résultat
static void sendResult(/* fd_pipe_to_client,*/ /* résultat */)
{
}


/*----------------------------------------------*
 * fonction appelable par le main
 *----------------------------------------------*/
void service_maximum(int fdSC, int fdCS)
{
    // initialisations diverses
    
    receiveData(/* paramètres */);
    computeResult(/* paramètres */);
    sendResult(/* paramètres */);

    // libération éventuelle de ressources
}
