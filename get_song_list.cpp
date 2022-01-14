#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>

class CURLplusplus {

private:

    CURL* m_curl;
    std::stringstream m_ss;
    long m_httpCode{0};
    char* m_contentType;

private:
    
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
        
        return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
    }

    size_t Write(void *buffer, size_t size, size_t nmemb) {

        m_ss.str(std::string());
        m_ss.write((const char*)buffer,size*nmemb);
        return size*nmemb;
    }

public:

    CURLplusplus() : m_curl(curl_easy_init()) {}
    
    ~CURLplusplus() {

        if (m_curl) {

            curl_easy_cleanup(m_curl);
        } 
    }

    std::string Get(const std::string& url) {

        CURLcode res;
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
        
        res = curl_easy_perform(m_curl);
        
        if (res != CURLE_OK) {

            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_httpCode);
        curl_easy_getinfo(m_curl, CURLINFO_CONTENT_TYPE, &m_contentType);

        std::cout << "HTTP CODE: " << m_httpCode << std::endl;
        std::cout << "CONTENT TYPE: " << m_contentType << std::endl;

        return m_ss.str();
    }
};

/***********************************************************************/

int main (int argc, char** argv) {

    if(argc < 2) {

        std::cout << "Usage: " << argv[0] << " <URL>" << std::endl;
        return 1;
    }

    CURLplusplus client;
    std::string x = client.Get(argv[1]);

    std::cout << "PAYLOAD: " << x << std::endl;
}