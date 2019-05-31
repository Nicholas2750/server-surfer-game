#include <iostream>
#include <vector>

#include "curl/curl.h"
#include "curl_helper.h"

using std::string;

size_t Curl::CurlWriteCallBackString(void *contents, size_t size, size_t nmemb, std::string *str) {
    size_t new_length = size*nmemb;

    try {
        str->append((char*)contents, new_length);
    } catch (std::bad_alloc &e) {
        // Handles memory problem
        return 0;
    }

    return new_length;
}


string Curl::CurlURL(string server_url) {
    CURL *curl;
    string server_content;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {

        // Gets content of the URL
        curl_easy_setopt(curl, CURLOPT_URL, server_url.c_str());

	    // Follow redirection
	    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // For HTTPS
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Store content as a string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallBackString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &server_content);


        // Performs the request and store cleans up afterwards.
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return server_content;
}
