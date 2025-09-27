#include <stdio.h>
#include "url.h"

int main() {
  urlData *urls = initUrls();

  printf("%s\n", longUrl(urls, shortenUrl(urls, "https://example.com")));

  freeUrls(urls);
  return 0;
}
