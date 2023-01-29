
#include "stdio.h"
#include "stdlib.h"
#include "HTTP.c"
#include "string.h"

struct memory {
    char *response;
    size_t size;
};

static size_t callBack(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *) userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}


int getGoogleResult(CURL *curl_handle, char *src, char *dst, char *content, int content_length) {
    struct memory chunk = {0};char front[] = {"<span id=\"tw-answ-target-text\">"};
    char rear[] = {"</span><span id=\"tw-answ-target-text-feminine\">"};
    char *url = "www.google.com/async/translate";
    char *value = "async=translate,sl:%s,tl:%s,st:%s,id:1672056488960,qc:true,ac:true,_id:tw-async-translate,_pms:s,_fmt:pc";
    char *encode_content = curl_easy_escape(curl_handle, content, content_length);
    int data_length = strlen(value) + strlen(dst) + strlen(encode_content) + strlen(src) - strlen("%s") * 3;
    char *data = malloc(data_length);
    sprintf(data, value, src, dst, encode_content);
    HTTP_POST(curl_handle, url, data, data_length, &callBack,  (void *)&chunk);
    char *start = strstr(chunk.response,front) + strlen(front);
    char *end = strstr(chunk.response,rear);
    char * p = end;
    *p = '\0';
    printf("翻译结果:\n");
    printf("%s\n",start);
    return 0;
}

