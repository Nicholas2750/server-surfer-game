#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using std::string;
using std::array;
using std::unique_ptr;

class Execute {
    public:
    // Executes an OS command and returns the output.
    static string Command(string);
};
