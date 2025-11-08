#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

/**
 * Utility functions for string processing and helper operations.
 */
class Utils {
public:
    /**
     * Split string by delimiter
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);
    
    /**
     * Trim whitespace from string
     */
    static std::string trim(const std::string& str);
    
    /**
     * Convert string to lowercase
     */
    static std::string toLower(const std::string& str);
    
    /**
     * Check if string is numeric
     */
    static bool isNumeric(const std::string& str);
    
    /**
     * Get user input with prompt
     */
    static std::string getInput(const std::string& prompt);
    
    /**
     * Get integer input with validation
     */
    static int getIntInput(const std::string& prompt, int min, int max);
};

#endif // UTILS_H