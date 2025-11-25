#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

/**
 * @brief Parses command-line arguments and stores them in a map.
 * Arguments must be in the format: -flag value (e.g., -a 100000).
 */
map<string, string> Utils::parseArgs(int argc, char* argv[])
{
    map<string, string> argsMap;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        // Check if the argument is a flag (starts with '-')
        if (arg.size() > 1 && arg[0] == '-') {
            // Check if there is a next argument (the value)
            if (i + 1 < argc) {
                // Store the flag and the next argument as its value
                argsMap[arg] = argv[i + 1];
                i++; // Skip the value argument
            } else {
                // Flag without a value at the end is invalid
                throw invalid_argument("Missing value for argument: " + arg);
            }
        } else {
            // Argument is not a flag, treat as positional or error
            throw invalid_argument("Unexpected argument format: " + arg);
        }
    }
    return argsMap;
}

/**
 * @brief Displays the correct usage information for the application.
 */
void Utils::printUsage(const std::string& appName)
{
    cout << "\n------------------------------------------------------------\n";
    cout << "Usage: " << appName << " -a <amount> -i <interest> -n <period> [-p <payment>]\n";
    cout << "------------------------------------------------------------\n";
    cout << "Required parameters:\n";
    cout << "  -a <double>  : Loan amount (A)\n";
    cout << "  -i <double>  : Yearly interest rate percentage (i)\n";
    cout << "  -n <int>     : Total loan period in months (N)\n";
    cout << "Optional parameters:\n";
    cout << "  -p <double>  : Monthly payment amount (P) (for calculation of N or A)\n";
    cout << "  -e <int>     : Elapsed period in months (n) (for calculating balance)\n";
    cout << "  -f <double>  : Flat opening fee\n";
    cout << "  -c <double>  : Percentage opening fee\n";
    cout << "\nExamples:\n";
    cout << "  Calculate EMI: " << appName << " -a 100000 -i 8.0 -n 360\n";
    cout << "  Calculate Balance: " << appName << " -a 100000 -i 8.0 -p 733.76 -e 12\n";
    cout << "------------------------------------------------------------\n\n";
}