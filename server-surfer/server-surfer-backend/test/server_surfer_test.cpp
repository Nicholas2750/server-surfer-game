#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "./../src/curl_helper.h"
#include "./../src/parse_helper.h"
#include "./../src/server_surfer.h"
#include "./../src/execute.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;

SCENARIO("Curling functionalities work as intended") {
    GIVEN("a valid URL with https:// in the URL") {
		string url = "https://duckduckgo.com/";

        WHEN("CurlURL() is called") {
            string curl_result = Curl::CurlURL(url);

            THEN("a HTML page is returned") {
                REQUIRE(curl_result.size() > 0);
            }
        }
	}

    GIVEN("a valid URL with http:// in the URL") {
		string url = "http://duckduckgo.com/";

        WHEN("CurlURL() is called") {
            string curl_result = Curl::CurlURL(url);

            THEN("a HTML page is returned") {
                REQUIRE(curl_result.size() > 0);
            }
        }
	}

    GIVEN("a valid URL no https:// or http:// in the URL") {
		string url = "duckduckgo.com";

        WHEN("CurlURL() is called") {
            string curl_result = Curl::CurlURL(url);

            THEN("a HTML page is returned") {
                REQUIRE(curl_result.size() > 0);
            }
        }
	}

    GIVEN("a valid URL with queries in it") {
		string url = "https://duckduckgo.com/?q=query+test&atb=v165-2__&ia=web";

        WHEN("CurlURL() is called") {
            string curl_result = Curl::CurlURL(url);

            THEN("a HTML page is returned") {
                REQUIRE(curl_result.size() > 0);
            }

            THEN("the queries work as intende") {
                REQUIRE(curl_result != Curl::CurlURL("duckduckgo.com"));
            }
        }
	}

    GIVEN("an invalid URL") {
		string url = "www.thereisnowebsitelikethis.com";

        WHEN("CurlURL() is called") {
            string curl_result = Curl::CurlURL(url);

            THEN("no HTML page is returned") {
                REQUIRE(curl_result.size() == 0);
            }
        }
	}
}


SCENARIO("URL cleaning functionalities work as intended") {
    GIVEN("a URL with https:// in the URL") {
		string url = "https://duckduckgo.com";

        WHEN("CleanURL() is called") {
            string clean_url = Parse::CleanURL(url);

            THEN("the https:// is erased") {
                REQUIRE(clean_url == "duckduckgo.com");
            }
        }
	}

    GIVEN("a URL with http:// in the URL") {
		string url = "http://duckduckgo.com";

        WHEN("CleanURL() is called") {
            string clean_url = Parse::CleanURL(url);

            THEN("the http:// is erased") {
                REQUIRE(clean_url == "duckduckgo.com");
            }
        }
	}

    GIVEN("a URL with queries in it") {
		string url = "https://duckduckgo.com/?q=query+test&atb=v165-2__&ia=web";

        WHEN("CleanURL() is called") {
            string clean_url = Parse::CleanURL(url);

            THEN("the queires are erased") {
                REQUIRE(clean_url == "duckduckgo.com");
            }
        }
	}
}


SCENARIO("Link extraction functionalities work as intended") {
    GIVEN("a URL that leads to a webpage with no links") {
		string url = "google.com";

        WHEN("ExtractLinks() is called") {
            vector<string> links = Parse::ExtractLinks(url);

            THEN("no links are extracted") {
                REQUIRE(links.size() == 0);
            }
        }
	}
}


SCENARIO("JSON cleaning functionalities work as intended") {
    GIVEN("a JSON obtained from ipinfo.io") {
		string json = Curl::CurlURL("ipinfo.io/52.6.165.9");

        WHEN("CleanJSON() is called") {
            string cleaned_json = Parse::CleanJSON(json);

            THEN("All unwanted characters are removed") {
                REQUIRE(cleaned_json == "  ip: 52.6.165.9\n  hostname: ec2-52-6-165-9.compute-1.amazonaws.com\n  city: Beaumont\n  region: Texas\n  country: US\n  loc: 30.0866,-94.1274\n  postal: 77702\n  phone: 409\n  org: AS14618 Amazon.com, Inc.\n");
            }
        }
	}
}


SCENARIO("nmap cleaning functionalities work as intended") {
    GIVEN("an example of nmap result") {
		string nmap_result = "Starting Nmap 7.70 ( https://nmap.org ) at 2019-05-01 14:42 CDT\nNmap scan report for google.com (172.217.4.206)\nHost is up (0.0056s latency).\nOther addresses for google.com (not scanned): 2607:f8b0:4009:812::200e\nrDNS record for 172.217.4.206: lga15s48-in-f206.1e100.net\nNot shown: 98 filtered ports\nPORT    STATE SERVICE\n80/tcp  open  http\n443/tcp open  https";

        WHEN("CleanNmap() is called with PORT as it's breakpoint") {
            string cleaned_result = Parse::CleanNmapResult(nmap_result, "PORT");

            THEN("All unwanted characters are removed") {
                REQUIRE(cleaned_result == "PORT    STATE SERVICE\n80/tcp  open  http\n443/tcp open  https\n");
            }
        }
	}
}


SCENARIO("Executing command functionalities work as intended") {
    GIVEN("an example of command") {
		string command = "echo abcdefg";
        
        WHEN("Command() is called with that command") {
            string command_result = Execute::Command(command);

            THEN("the expected result is returned") {
                REQUIRE(command_result == "abcdefg\n");
            }
        }
	}
}
