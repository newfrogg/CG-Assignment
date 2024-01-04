#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::string convertRGBToHex(int r, int g, int b) {
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0') << std::setw(2) << r;
    hexStream << std::hex << std::setfill('0') << std::setw(2) << g;
    hexStream << std::hex << std::setfill('0') << std::setw(2) << b;
    return hexStream.str();
}
