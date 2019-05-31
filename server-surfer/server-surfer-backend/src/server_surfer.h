#pragma once

#include <iostream>
#include <vector>

#include "curl/curl.h"
#include "curl_helper.h"
#include "parse_helper.h"
#include "execute.h"

using std::string;
using std::vector;

class Game {
    public:
    // The constructor of the game.
    Game();

    // A method that is used to make one move in the game.
    void MakeMove(string);

    // A method to check whether a URL is valid or not.
    bool IsValidURL(string);

    // Getters utilized by the UI codes.
    string GetStartServerInfo();
    string GetCurrentServerURL();
    string GetCurrentServerInfo();
    string ScanCurrentServerPort();
    string ScanCurrentServerSubdomain();
    string ScanCurrentServerSubdirectory();
    vector<string> GetLinks();
    int GetMovesTaken();
    int CalculateScore();


    private:
    // Gets the IP address of a server using its URL.
    string GetIpAddress(string);

    // Gets the information of a server by curling ipinfo.io
    string GetServerInfo(string);

    // Gets the location of a server by curling ipinfo.io
    vector<float> GetServerLocation(string);

    string start_server_info;
    string current_server_info;
    string current_server_url;
    vector<float> start_server_location;
    vector<float> current_server_location;
    vector<string> extracted_links;
    int moves_taken;
};

const static float SCORE_MULTIPLIER = 100;
const static string PORT_SCAN_ARGUMENT = "nmap -F ";
const static string SUBDOMAIN_SCAN_ARGUMENT = "nmap --script dns-brute.nse -F ";
const static string SUBDIRECTORY_SCAN_ARGUMENT = "nmap --script http-enum.nse -F ";
const static string PORT_SCAN_EXTRACT_POINT = "PORT";
const static string SUBDOMAIN_SCAN_EXTRACT_POINT = "Host script results:";
const static string SUBDIRECTORY_SCAN_EXTRACT_POINT = "PORT";
