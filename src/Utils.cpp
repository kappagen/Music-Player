#include "Utils.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

vector<string> Utils::split(const string& str, char delimiter) {
    vector<string> tokens;
    istringstream stream(str);
    string token;

    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

string Utils::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

string Utils::toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool Utils::isNumeric(const string& str) {
    if (str.empty()) return false;
    
    for (char c : str) {
        if (!isdigit(c) && c != '-' && c != '+') {
            return false;
        }
    }
    return true;
}

string Utils::getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return trim(input);
}

int Utils::getIntInput(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        // Check for EOF or failed input
        if (cin.eof() || cin.fail()) {
            cout << "\nInput error or EOF reached. Exiting...\n";
            exit(1);
        }
        
        // Allow empty input for optional fields
        if (input.empty()) {
            cout << "";
            continue;
        }
        
        try {
            int value = stoi(input);
            if (value >= min && value <= max) {
                return value;
            }
            cout << "Please enter a number between " << min << " and " << max << ".\n";
        } catch (...) {
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}
