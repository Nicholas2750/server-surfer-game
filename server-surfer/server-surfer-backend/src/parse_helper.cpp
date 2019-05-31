#include <iterator>
#include <regex>
#include <vector>
#include <sstream>
#include <iostream>

#include "parse_helper.h"

using std::string;
using std::vector;
using std::istringstream;
using std::getline;


void Parse::EraseSubstring(string& original_string, string erased_substring) {
    if (original_string.find(erased_substring) != string::npos) {
        original_string.erase(original_string.find(erased_substring), erased_substring.length());
    }
}


void Parse::EraseQueries(string& original_string) {
    if (original_string.find("/") != string::npos) {
        original_string.erase(original_string.find("/"), original_string.length());
    }

    if (original_string.find("?") != string::npos) {
        original_string.erase(original_string.find("?"), original_string.length());
    }
}


string Parse::CleanURL(string original_url) {
    string clean_url = original_url;

    EraseSubstring(clean_url, "https://");
    EraseSubstring(clean_url, "http://");
    EraseQueries(clean_url);

    return clean_url;
}


vector<string> Parse::ExtractRawLinks(string page_html) {
	static const std::regex link_regex( "<a href=\"(.*?)\"", std::regex_constants::icase);

	return {std::sregex_token_iterator(page_html.begin(), page_html.end(), link_regex, 1), std::sregex_token_iterator{}};
}


vector<string> Parse::ExtractLinks(string page_url) {
    string page_html = Curl::CurlURL(page_url);

    std::vector<string> extracted_links = ExtractRawLinks(page_html);

    std::vector<string> complete_links;

    for (int i = 0; i < extracted_links.size(); ++i) {
        if ((extracted_links[i]).substr(0, 4) == "http") {
            complete_links.push_back(extracted_links[i]);
        }
    }
    
    return complete_links;
}


string Parse::FilterCharacter(string original_string, char character_to_erase) {
    string filtered_string;

    for (int i = 0; i < original_string.size(); i++) {
        if (character_to_erase == original_string[i]) {
            continue;
        }

        filtered_string.push_back(original_string[i]);
    }

    return filtered_string;
}


string Parse::CleanJSON(string json_string) {
    string clean_string;

    istringstream json_stream(json_string);
    string line;

    while (getline(json_stream, line)) {
        // Erases excess vertical spacing and the { } characters in the JSON.
        if (line.size() <= 1) {
            continue;
        }

        // Erases trailing commas at the end of each line.
        if (line[line.size() - 1] == ',') {
            line = line.substr(0, line.size() - 1);
        }

        // Erases all the " characters in the JSON file.
        clean_string += FilterCharacter(line, '\"');
        clean_string += "\n";
    }

    return clean_string;
}


string Parse::CleanNmapResult(string nmap_result, string extract_start_point) {
    string clean_result;

    istringstream nmap_stream(nmap_result);
    string line;

    bool reached_important_part = false;

    while (getline(nmap_stream, line)) {
        // Only start extracting strings when the line that start with the extract_start_point has been reached.
        if (line.substr(0, extract_start_point.size()) == extract_start_point) {
            reached_important_part = true;
        }

        if (reached_important_part) {
            clean_result += line;
            clean_result += "\n";
        }

        // Stop extracting once there is a blank line after extract_start_point line has been passed.
        if (reached_important_part && line.size() == 0) {
            break;
        }
    }

    return clean_result;
}
