#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseutils.h"

typedef struct {
  char* url_;
  int id;
} url;

typedef struct {
  size_t length;
  url *arr[];
} urlData;

urlData* initUrls() {
  urlData *urls = malloc(sizeof(urlData));
  urls->length = 0;
  return urls;
}

void freeUrls(urlData *urls) {
  for (size_t i = 0; i < urls->length; i++) {
    free(urls->arr[i]);
  }
  free(urls);
}

int makeId(urlData *urls, char* url_) {
  return urls->length + 1000; 
}

char* urlFromId(urlData *urls, int id) {
  for (size_t i = 0; i < urls->length; i++) {
    if (urls->arr[i]->id == id) {
      return urls->arr[i]->url_;
    }
  }
}

int addUrl(urlData *urls, char* url_) {
  url *u = malloc(sizeof(url));
  urls->arr[urls->length] = u;
  u->url_ = url_;
  urls->length++;
  u->id = makeId(urls, url_);
  return u->id;
}

void printUrls(urlData *urls) {
  for (size_t i = 0; i < urls->length; i++) {
    printf("%d: %s\n", urls->arr[i]->id, urls->arr[i]->url_);
  }
  printf("Total size: %ld\n", urls->length);
}

char* shortenUrl(urlData *urls, char* url_) {
  int i = addUrl(urls, url_);
  char id[10000];
  sprintf(id, "%d", i);
  char* shorty = basetobase(id, 10, 62);
  return shorty;
}

char* longUrl(urlData *urls, char* b62) {
  int id = atoi(basetobase(b62, 62, 10));
  char* url_ = urlFromId(urls, id);
  return url_;
}

int main() {
  urlData *urls = initUrls();

  printf("%s\n", longUrl(urls, shortenUrl(urls, "https://example.com")));

  freeUrls(urls);
  return 0;
}
