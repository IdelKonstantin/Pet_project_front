#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {

    return fwrite(ptr, size, nmemb, stream);
}

int main(int argc, char** argv) {

    if(argc < 3) {

        fprintf(stderr, "Usage: %s <URL> <filePath>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    FILE *fp;
    CURLcode res;
    
    curl = curl_easy_init();
    
    if (curl) {

        fp = fopen(argv[2], "wb"); //Ай-ай-ай, здесь должна быть проверка ошибок, а еще лучше использовать RAII-wrapper ;)

        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        res = curl_easy_perform(curl);  //Ай-ай-ай, и здесь она тоже должна быть... ;)

        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}