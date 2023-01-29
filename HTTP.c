//
// Created by 假如给我三十天假期 on 2023/1/29.
//
#include "curl/curl.h"

int HTTP_GET(CURL *curl_handle, char *url, char *header[], int header_length) {
    if (!curl_handle) {
        return CURLE_FAILED_INIT;
    }
    struct curl_slist *list = NULL;
    for (int i = 0; i < header_length; ++i) {
        list = curl_slist_append(list, header[i]);
    }
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    int res = curl_easy_perform(curl_handle);
    curl_slist_free_all(list);
    return res;
}

int HTTP_POST(CURL *curl_handle, char *url, char *data, int data_length, void *cb, void *userp) {
    if (!curl_handle) {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long) data_length);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);
    if (cb) {
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb);
    }
    if (userp) {
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) userp);
    }
    int res = curl_easy_perform(curl_handle);
    free(data);
    return res;
}