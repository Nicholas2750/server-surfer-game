#pragma once

#include <iterator>
#include <set>
#include <regex>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>

#include "curl/curl.h"

using std::string;

class Curl {
    public:
    // Returns the HTML of a URL. When given an invalid URL, returns a blank string.
    static string CurlURL(string);


    private:
    // A method that is used as a workaround so that libcurl's output can be extracted as a string.
    static size_t CurlWriteCallBackString(void*, size_t, size_t, string*);
};