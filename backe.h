#ifndef BACKE_H
#define BACKE_H

#include "url.h"

#define PORT 8089
#define BUFFER_SIZE 1024

void handle_redirect(urlData *urls, int client_s, char* shorty);
void handle_request(urlData *urls, int client_s);
void startServer(urlData *urls);

#endif
