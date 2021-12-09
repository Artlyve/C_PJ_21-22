/*PIERRE Guillaume
SALIHI Valdrin
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "memory.h"
#include "myassert.h"

#include "service.h"
#include "client_orchestre.h"
#include "client_service.h"

#include "client_arret.h"
#include "client_somme.h"
#include "client_maximum.h"
#include "client_compression.h"


static void usage(const char *exeName, const char *message)
{
    fprintf(stderr, "usage : %s <num_service> ...\n", exeName);
    fprintf(stderr, "        <num_service> : entre -1 et %d\n", SERVICE_NB - 1);
    fprintf(stderr, "                        -1 signifie l'arrêt de l'orchestre\n");
    fprintf(stderr, "        ...           : les paramètres propres au service\n");
    if (message != NULL)
        fprintf(stderr, "message : %s\n", message);
    exit(EXIT_FAILURE);
}

void verifArg(int num, int argc, char **argv){
    switch (num)
    {
    case 0:
        client_somme_verifArgs(argc, argv);
        break;
    case 1:
        client_compression_verifArgs(argc, argv);
        break;
    case 2:
        client_maximum_verifArgs(argc, argv);
        break;
    case REQUEST_STOP:
        client_arret_verifArgs(argc, argv);
        break;
    default:
        break;
    }
}

void comService(int num, int argc, char **argv, int fdcs, int fdsc){
    switch (num)
    {
    case 0:
        client_somme(fdcs, fdsc, argc, argv);
        break;
    case 1:
        client_compression(fdcs, fdsc, argc, argv);
        break;
    case 2:
        client_maximum(fdcs, fdcs, argc, argv);
        break;
    default:
        break;
    }
}

int main(int argc, char * argv[])
{
    if (argc < 2)
        usage(argv[0], "nombre paramètres incorrect");

    int numService = io_strToInt(argv[1]);
    if (numService < -1 || numService >= SERVICE_NB)
        usage(argv[0], "numéro service incorrect");

    // appeler la fonction de vérification des arguments
    //     une fct par service selon numService
    //            . client_arret_verifArgs
    //         ou . client_somme_verifArgs
    //         ou . client_compression_verifArgs
    //         ou . client_maximum_verifArgs
    verifArg(numService, argc, argv);
    
    // initialisations diverses s'il y a lieu
    int key = getKey("client_orchestre.h", CLIENT_ORCHESTRE_ID);
    int semClient = semGet(key);

    char *tsc = NULL;
    char *tcs = NULL;
    char *password = NULL;

    int tubesc = 0;
    int tubecs = 0;
    
    // entrée en section critique pour communiquer avec l'orchestre
    takeSem(semClient);
    // ouverture des tubes avec l'orchestre
    int tco =myOpen(CLIENT_ORCHESTRE , O_WRONLY);
    int toc = myOpen(ORCHESTRE_CLIENT, O_RDONLY);
    // envoi à l'orchestre du numéro du service
    myWrite(tco, &numService, sizeof(int));

    int code = 0;
    myRead(toc, &code, sizeof(int));

    // attente code de retour
    // si code d'erreur
    //     afficher un message erreur
    // sinon si demande d'arrêt (i.e. numService == -1)
    //     afficher un message
    // sinon
    //     récupération du mot de passe et des noms des 2 tubes
    // finsi
    //
    // envoi d'un accusé de réception à l'orchestre
    // fermeture des tubes avec l'orchestre
    // sortie de la section critique
    //
    // si pas d'erreur et service normal
    //     ouverture des tubes avec le service
    //     envoi du mot de passe au service
    //     attente de l'accusé de réception du service
    //     si mot de passe non accepté
    //         message d'erreur
    //     sinon
    //         appel de la fonction de communication avec le service :
    //             une fct par service selon numService :
    //                    . client_somme
    //                 ou . client_compression
    //                 ou . client_maximum
    //         envoi d'un accusé de réception au service
    //     finsi
    //     fermeture des tubes avec le service
    // finsi
    if(code == REQUEST_ERROR){
        fprintf(stderr, "ERROR Code in Client.c");
    }else if(code == REQUEST_STOP){
        printf("Code d'arrêt demandé");
    }else{
        myRead(toc, password, sizeof(char));
        myRead(toc, tsc, sizeof(char));
        myRead(toc, tcs, sizeof(char));
       
    }

    int c = CONTINUE;

    myWrite(tco, &c, sizeof(int));
    
    myClose(toc);
    myClose(tco);
    

    letSem(semClient);
    if(code == REQUEST_AGREE){
        tubesc = myOpen(tsc, O_RDONLY);
        tubecs = myOpen(tcs, O_WRONLY);
        myWrite(tubecs, password, sizeof(char));
        myRead(tubesc, &code, sizeof(int));
        if(code == CODE_ERROR_PSW){
            fprintf(stderr, "ERROR Code password in Client.c");
        }else{
            comService(numService, argc, argv, tubecs, tubesc);
            int r = RECEIPT;
            myWrite(tubecs, &r, sizeof(int));
        }
        myClose(tubesc);
        myClose(tubecs);
    }
    // libération éventuelle de ressources
    
    return EXIT_SUCCESS;
}
