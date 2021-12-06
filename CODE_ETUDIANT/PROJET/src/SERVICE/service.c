#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <fcntl.h>


#include "orchestre_service.h"
#include "client_service.h"
#include "service.h"
#include "service_somme.h"
#include "service_compression.h"
#include "service_maximum.h"

typedef struct  oS *orchestre_service;
typedef struct cS *client_service;


static void usage(const char *exeName, const char *message)
{
    fprintf(stderr, "usage : %s <num_service> <clé_sémaphore> <fd_tube_anonyme> "
            "<nom_tube_service_vers_client> <nom_tube_client_vers_service>\n",
            exeName);
    fprintf(stderr, "        <num_service>     : entre 0 et %d\n", SERVICE_NB - 1);
    fprintf(stderr, "        <clé_sémaphore>   : entre ce service et l'orchestre (clé au sens ftok)\n");
    fprintf(stderr, "        <fd_tube_anonyme> : entre ce service et l'orchestre\n");
    fprintf(stderr, "        <nom_tube_...>    : noms des deux tubes nommés reliés à ce service\n");
    if (message != NULL)
        fprintf(stderr, "message : %s\n", message);
    exit(EXIT_FAILURE);
}

void callService(int numService, int fd[2]){
    switch (numService)
    {
    case 0:
        service_somme(fd);
        break;

    case 1:
        service_compression(fd);
        break;
        
    case 2:
        service_maximum(fd);
        break;    
    default:
        break;
    }
}

/*----------------------------------------------*
 * fonction main
 *----------------------------------------------*/
int main(int argc, char * argv[])
{
    if (argc != 6)
        usage(argv[0], "nombre paramètres incorrect");

    // initialisations diverses : analyse de argv
    client_service cs;
    orchestre_service os;

    int numService = atoi(argv[1]);
    int project_id = atoi(argv[2]);
    os->pipeMasterService = atoi(argv[3]);
    char *namesc = argv[4];
    char *namecs = argv[5];
    
    key_t key;
    os->sem = semget()

    while (true)
    {
        // attente d'un code de l'orchestre (via tube anonyme)
        // si code de fin
        //    sortie de la boucle
        // sinon
        //    réception du mot de passe de l'orchestre
        //    ouverture des deux tubes nommés avec le client
        //    attente du mot de passe du client
        //    si mot de passe incorrect
        //        envoi au client d'un code d'erreur
        //    sinon
        //        envoi au client d'un code d'acceptation
        //        appel de la fonction de communication avec le client :
        //            une fct par service selon numService (cf. argv[1]) :
        //                   . service_somme
        //                ou . service_compression
        //                ou . service_maximum
        //        attente de l'accusé de réception du client
        //    finsi
        //    fermeture ici des deux tubes nommés avec le client
        //    modification du sémaphore pour prévenir l'orchestre de la fin
        // finsi
        
        
        /*********Réception  code **********/
            close(fd[1]);
            int  code;
            read(fd[0], &code, sizeof(int));


            if(code == CODE_END){
                break;
            }else{

                /*REception mot de passe de l'orchestre*/
                int len;
                char *passwordOrchestre, *passwordClient;
                read(fd[0], &len, sizeof(int));
                read(fd[0], passwordOrchestre, len *sizeof(char));

                /*Ouverture des tube nommés*/
                int tsc = open(namesc, O_WRONLY); //Tube service -> Client
                int tcs = open(namecs, O_WRONLY);//Tube Client ->  service

                /*Reception du mot de passe du client*/
                read(tcs, passwordClient, sizeof(char));

                if(!(strcmp(passwordClient, passwordOrchestre))){
                    write(tsc, CODE_ERROR_PSW, sizeof(int));

                }else{
                    write(tsc, CODE_AGREE_PSW, sizeof(int));
                    callService(numService, tcs);
                    close(tcs);
                    close(tsc);
                }

            }


            close(fd[0]);
            


    }

    // libération éventuelle de ressources
    
    return EXIT_SUCCESS;
}
