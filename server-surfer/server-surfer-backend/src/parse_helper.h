#pragma once

#include <iterator>
#include <regex>
#include <vector>

#include "curl_helper.h"

using std::string;
using std::vector;

class Parse {
    public:
    // A method to format URL such that it's IP will be able to be looked up.
    // This is done by removing the preceding http:// or https:// in a link.
    static string CleanURL(string);

    // Extract all links from a webpage that starts with the substring "http".
    // This is implemented so that the game does not have an excessive amount of dead links.
    static vector<string> ExtractLinks(string);

    // Format the JSON obtain by curling ipinfo.io so that it looks presentable.
    static string CleanJSON(string);

    // Format nmap result to look better by only extracting the parts between an extract start point and blank line.
    static string CleanNmapResult(string, string);


    private:
    // A method to erase the first occurence of a certain substring from a string.
    static void EraseSubstring(string&, string);

    // A method to erase queries from a URL.
    static void EraseQueries(string&);

    // A method to extract all links from a webpage.
    static vector<string> ExtractRawLinks(string);

    // A method to eliminate all characters from a string.
    static string FilterCharacter(string, char);
};

