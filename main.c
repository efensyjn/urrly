#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "backe.h"
#include "url.h"

// void cli(urls) {
//   char cmd[100];
//   while (1) {
//     printf("> ");
//     fgets(cmd, sizeof(cmd), stdin);
//
//     cmd[strcspn(cmd, "\n")] = '\0';
//
//     if (strncmp(cmd, "short ", 6) == 0) {
//       printf("%s\n", shortenUrl(urls, cmd+6));
//     } else if (strcmp(cmd, "exit") == 0) {
//       //
//     }
//   }
// }

int main() {
  urlData *urls = initUrls();
  printf("%s\n", shortenUrl(urls, "https://example.com"));

  startServer(urls);
  /*
   * TODO:
   * thread
   */

  freeUrls(urls);

  return 0;
}
