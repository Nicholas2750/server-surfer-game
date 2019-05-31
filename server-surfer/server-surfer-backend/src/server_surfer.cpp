#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <regex>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <exception>
#include <math.h>

#include "curl/curl.h"
#include "server_surfer.h"

using std::string;
using std::exception;
using std::cout;
using std::cin;
using std::vector;

Game::Game() {
    moves_taken = 0;
}


string Game::GetIpAddress(string hostname) {
    struct hostent *he;
    struct in_addr **address_list;
    string ip_address;

    he = gethostbyname(hostname.c_str());
    address_list = (struct in_addr **)he->h_addr_list;
    ip_address = inet_ntoa(*address_list[0]);

    return ip_address;
}


string Game::GetServerInfo(string server_url) {
    string clean_url = Parse::CleanURL(server_url);

    string ip_address = GetIpAddress(clean_url);
    string curl_url = "ipinfo.io/" + ip_address;

    return Curl::CurlURL(curl_url);
}


string Game::ScanCurrentServerPort() {
    string clean_url = Parse::CleanURL(current_server_url);
    string nmap_result = Execute::Command(PORT_SCAN_ARGUMENT + clean_url);

    return Parse::CleanNmapResult(nmap_result, PORT_SCAN_EXTRACT_POINT);
}


string Game::ScanCurrentServerSubdomain() {
    string clean_url = Parse::CleanURL(current_server_url);
    string nmap_result = Execute::Command(SUBDOMAIN_SCAN_ARGUMENT + clean_url);

    return Parse::CleanNmapResult(nmap_result, SUBDOMAIN_SCAN_EXTRACT_POINT);
}


string Game::ScanCurrentServerSubdirectory() {
    string clean_url = Parse::CleanURL(current_server_url);
    string nmap_result = Execute::Command(SUBDIRECTORY_SCAN_ARGUMENT + clean_url);

    return Parse::CleanNmapResult(nmap_result, SUBDIRECTORY_SCAN_EXTRACT_POINT);
}


vector<float> Game::GetServerLocation(string server_url) {
    string clean_url = Parse::CleanURL(server_url);

    string ip_address = GetIpAddress(clean_url);
    string curl_url = "ipinfo.io/" + ip_address + "/loc";

    string complete_coordinate = Curl::CurlURL(curl_url);

    string latitude = "";
    string longitude = "";

    bool passed_comma = false;

    for (int i = 0; i < complete_coordinate.size(); i++) {
        if (complete_coordinate[i] == ',') {
            passed_comma = true;
            continue;
        }

        if (!passed_comma) {
            latitude += complete_coordinate[i];
        }

        longitude += complete_coordinate[i];
    }

    vector<float> server_location;
    server_location.push_back(stof(latitude));
    server_location.push_back(stof(longitude));

    return server_location;
}


int Game::CalculateScore() {
    float latitude_difference = start_server_location[0] - current_server_location[0];
    float longitude_difference = start_server_location[1] - current_server_location[1];

    float total_distance = sqrt(latitude_difference * latitude_difference + longitude_difference * longitude_difference);

    return (int) (total_distance * SCORE_MULTIPLIER);
}


bool Game::IsValidURL(string page_url) {
    return Curl::CurlURL(page_url).size() != 0;
}


void Game::MakeMove(string page_url) {
    ++moves_taken;

    current_server_url = page_url;

    string server_info = Parse::CleanJSON(GetServerInfo(page_url));
    vector<float> server_location = GetServerLocation(page_url);

    // If this is the first time MakeMove is called, update the information and location for starting server too.
    if (moves_taken == 1 && start_server_info.size() == 0) {
        start_server_info = server_info;
        start_server_location = server_location;
    }
    
    // Update the information and location of current server.
    current_server_info = server_info;
    current_server_location = server_location;

    extracted_links = Parse::ExtractLinks(page_url);
}

    
string Game::GetStartServerInfo() {
    return start_server_info;
}


string Game::GetCurrentServerInfo() {
    return current_server_info;
}


string Game::GetCurrentServerURL() {
    // Adds a preceding http to all links that does not start with http.
    // This is needed so Qt can recognize the string as a link.
    if (current_server_url.find("http") == string::npos) {
        return "http://" + current_server_url;
    }
    return current_server_url;
}


vector<string> Game::GetLinks() {
    return extracted_links;
}


int Game::GetMovesTaken() {
    return moves_taken;
}
