#ifndef URL_H
#define URL_H

typedef struct {
  char* url_;
  int id;
} url;

typedef struct {
  size_t length;
  url *arr[];
} urlData;

urlData* initUrls();
void freeUrls(urlData *urls);

int makeId(urlData *urls, char* url_);
char* urlFromId(urlData *urls, int id);

int addUrl(urlData *urls, char* url_);
void printUrls(urlData *urls);

char* shortenUrl(urlData *urls, char* url_);
char* longUrl(urlData *urls, char* b62);

#endif
