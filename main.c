#include <stdio.h>
#include "googletranslate.c"


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("请输入要翻译的文本!!!\n");
        return 0;
    }
    int content_length = 0;

    for (int i = 1; i < argc; ++i) {
        content_length+= strlen(argv[i]);
    }
    char * content = (char *) malloc(content_length);
    for (int i = 1; i < argc; ++i) {
        strcat(content, argv[i]);
        strcat(content, " ");
    }
    CURL *curl_handle;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    struct curl_slist *list = NULL;
    char *header[] = {
            "User-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36",
            "Content-type: application/x-www-form-urlencoded;charset=UTF-8"};
    for (int i = 0; i < sizeof(header) / sizeof(header[0]); ++i) {
        list = curl_slist_append(list, header[i]);
    }
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, list);
//    curl_easy_setopt(curl_handle, CURLOPT_PROXY, "http://127.0.0.1:8888");
    getGoogleResult(curl_handle, "en", "zh-CN", content, content_length);
}
