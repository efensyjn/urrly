#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "url.h"

int main() {
  urlData *urls = initUrls();
  printf("%s\n", shortenUrl(urls, "https://example.com"));
  
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {
    AF_INET,
    0x901f,
    0
  };
  bind(s, (struct sockaddr *)&addr, sizeof(addr));
  listen(s, 10);

  int client = accept(s, 0, 0);

  char buffer[256] = {0};
  recv(client, buffer, 256, 0);

  char* f = buffer+5;
  *strchr(f, ' ') = 0;

  char* l = longUrl(urls, f);
  char *response = "HTTP/1.1 301 Moved Permanently\r\n"
                 "Location: %s\r\n"
                 "Content-Length: 0\r\n"
                 "\r\n";
  char r[256];
  sprintf(r, response, l);

  send(client, r, strlen(r), 0);

  close(client);
  close(s);

  freeUrls(urls);

  return 0;
}
