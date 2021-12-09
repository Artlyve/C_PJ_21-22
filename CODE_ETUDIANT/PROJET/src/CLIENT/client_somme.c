#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tubesem.h"
#include "io.h"
#include "client_service.h"
#include "client_somme.h"


/*----------------------------------------------*
 * usage pour le client somme
 *----------------------------------------------*/

static void usage(const char *exeName, const char *numService, const char *message)
{
    fprintf(stderr, "Client somme de deux nombres\n");
    fprintf(stderr, "usage : %s %s <n1> <n2> <prefixe>\n", exeName, numService);
    fprintf(stderr, "        %s         : numéro du service\n", numService);
    fprintf(stderr, "        <n1>      : premier nombre à sommer\n");
    fprintf(stderr, "        <n2>      : deuxième nombre à sommer\n");
    fprintf(stderr, "        <prefixe> : chaîne à afficher avant le résultat\n");
    fprintf(stderr, "exemple d'appel :\n");
    fprintf(stderr, "    %s %s 22 33 \"le résultat est : \"\n", exeName, numService);
    if (message != NULL)
        fprintf(stderr, "message : %s\n", message);
    exit(EXIT_FAILURE);
}

/*----------------------------------------------*
 * fonction de vérification des paramètres
 *----------------------------------------------*/

void client_somme_verifArgs(int argc, char * argv[])
{
    if (argc != 5)
        usage(argv[0], argv[1], "nombre d'arguments");
    // éventuellement d'autres tests
}


/*----------------------------------------------*
 * fonctions de communication avec le service
 *----------------------------------------------*/

// ---------------------------------------------
// fonction d'envoi des données du client au service
// Les paramètres sont
// - le file descriptor du tube de communication vers le service
// - les deux float dont on veut la somme
static void sendData(/* fd_pipe_to_service,*/ /* entier1, */ /* entier2 */int fd, float val1, float val2)
{
    // envoi des deux nombres
    
    myWrite(fd, &val1, sizeof(float));
    myWrite(fd, &val2, sizeof(float));
}

// ---------------------------------------------
// fonction de réception des résultats en provenance du service et affichage
// Les paramètres sont
// - le file descriptor du tube de communication en provenance du service
// - le prefixe
// - autre chose si nécessaire
static void receiveResult(/* fd_pipe_from_service,*/ /* préfixe, */ /* autres paramètres si nécessaire */ int fd, char *str, float res)
{
    // récupération de la somme
    // affichage du préfixe et du résultat
    myRead(fd, &res, sizeof(float));
    printf("%s: %f",str, res);

}


// ---------------------------------------------
// Fonction appelée par le main pour gérer la communications avec le service
// Les paramètres sont
// - les deux file descriptors des tubes nommés avec le service
// - argc et argv fournis en ligne de commande
// Cette fonction analyse argv et en déduit les données à envoyer
//    - argv[2] : premier nombre
//    - argv[3] : deuxième nombre
//    - argv[4] : chaîne à afficher avant le résultat
void client_somme(/* fd des tubes avec le service, */ int fdCS, int fdSC, int argc, char * argv[])
{
    if(argc != 5)
    {
        fprintf(stderr, "ERROR ARGUMENT CLIENT_SOMME");
    }

    // variables locales éventuelles
    float val1 =  io_strToFloat(argv[2]);
    float val2 =  io_strToFloat(argv[3]);
    char *str =  argv[4];
    float res = 0.;
    
    sendData(fdCS, val1, val2);
    receiveResult(fdSC, str, res);
}

