#include "includes.hpp"

int stringToInt (string input) {
    stringstream stream;
    stream << input;
    int number;
    stream >> number;
    return number;
    }

string intToString (int input) {
    stringstream stream;
    stream << input;
    string output;
    stream >> output;
    return output;
    }

string stringToUpper (std::string& s) {
    string::iterator i = s.begin();
    string::iterator end = s.end();
    while (i != end) {
        (*i) = toupper((unsigned char)*i);
        i++;
        }
    return s;
    }

