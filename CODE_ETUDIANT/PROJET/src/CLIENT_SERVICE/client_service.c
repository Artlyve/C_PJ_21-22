#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include "myassert.h"

#include "client_service.h"


/*** ---- FONCTIONS ---- ***/

// ---- CLIENT_SERVICE ----

struct cS *initClientService(int w, int r)
{
	struct cS *cs = malloc(sizeof(struct cS));

	cs->tcs = w;
	cs->tsc = r;
	return cs;
}