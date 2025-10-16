#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "url.h"
#include "backe.h"

void handle_redirect(urlData *urls, int client_s, char* shorty) {
  char* l = longUrl(urls, shorty);
  char *response = "HTTP/1.1 301 Moved Permanently\r\n"
                 "Location: %s\r\n"
                 "Content-Length: 0\r\n"
                 "\r\n";
  char r[BUFFER_SIZE];
  sprintf(r, response, l);
  send(client_s, r, strlen(r), 0);
}

void handle_request(urlData *urls, int client_s) {
  char buffer[BUFFER_SIZE];
  recv(client_s, buffer, sizeof(buffer), 0);

  if (strncmp(buffer, "GET /", 5) == 0) {
    char* f = buffer+5;
    *strchr(f, ' ') = 0;
    handle_redirect(urls, client_s, f);
  } else {
    char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
    send(client_s, response, strlen(response), 0);
  }
  close(client_s);
}

void startServer(urlData *urls) {
  int server_s, client_s;
  struct sockaddr_in addr_s, addr_c;
  socklen_t addr_len = sizeof(addr_c);

  server_s = socket(AF_INET, SOCK_STREAM, 0);
  if (server_s == -1) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  addr_s.sin_family = AF_INET;
  addr_s.sin_addr.s_addr = INADDR_ANY;
  addr_s.sin_port = htons(PORT);

  if (bind(server_s, (struct sockaddr *)&addr_s, sizeof(addr_s)) < 0) {
    perror("Binding failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_s, 10) < 0) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Listening on port %d\n", PORT);

  while (1) {
    client_s = accept(server_s, (struct sockaddr *)&addr_c, &addr_len);
    if (client_s < 0) {
      perror("Client accept failed");
      continue;
    }

    handle_request(urls, client_s);
  }

  close(server_s);
}
