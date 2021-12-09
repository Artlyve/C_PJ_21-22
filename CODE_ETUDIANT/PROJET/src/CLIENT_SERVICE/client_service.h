#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

// Ici toutes les communications entre les services et les clients :
// - les deux tubes nommés pour la communication bidirectionnelle

#define CODE_ERROR_PSW 951
#define CODE_AGREE_PSW 159
#define RECEIPT 1111

#define CLIENT_SERVICE_0 "pipe_c2s_0"
#define SERVICE_CLIENT_0 "pipe_s2c_0"

#define CLIENT_SERVICE_1 "pipe_c2s_1"
#define SERVICE_CLIENT_1 "pipe_s2c_1"

#define CLIENT_SERVICE_2 "pipe_c2s_2"
#define SERVICE_CLIENT_2 "pipe_s2c_2"

struct cS{
    int tcs;
    int tsc;
};

// ---- CLIENT_SERVICE ----

/*Création et initialisation de la structure entre le client et l'orchestre*/
struct cS *initClientService(int w, int r,int s);

#endif