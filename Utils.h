#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <map>

/**
 * @brief Utility class containing helper functions for the loan calculator application.
 * This class primarily handles command-line argument parsing and validation.
 */
class Utils
{
public:
    /**
     * @brief Parses command-line arguments and stores them in a map.
     * Arguments must be in the format: -flag value (e.g., -a 100000).
     * @param argc The number of arguments passed to main.
     * @param argv The array of command-line arguments.
     * @return A std::map<std::string, std::string> containing flag-value pairs.
     */
    static std::map<std::string, std::string> parseArgs(int argc, char* argv[]);

    /**
     * @brief Displays the correct usage information for the application.
     * @param appName The name of the executable (argv[0]).
     */
    static void printUsage(const std::string& appName);
};

#endif // UTILS_H_INCLUDED