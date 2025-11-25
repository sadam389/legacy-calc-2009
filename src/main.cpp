#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "CmdLineParser.h"
#include "Loan.h"

using namespace std;

// Define calculation types
enum CALC_TYPE {
    CALC_UNKNOWN = 0,
    CALC_BALANCE = 100,
    CALC_PAYMENT,
    CALC_NUMPAYMENTS,
    CALC_AMOUNT,
    CALC_INTEREST
};

// Define constants for arguments
const string ARG_CALC_BALANCE      = "-cb";
const string ARG_CALC_PAYMENT      = "-cp";
const string ARG_CALC_NUMPAYMENTS  = "-cn";
const string ARG_CALC_AMOUNT       = "-ca";
const string ARG_CALC_INTEREST     = "-ci";

const string ARG_PAYMENT           = "-p";
const string ARG_PERIOD_TOTAL      = "-N";
const string ARG_PERIOD_ELAPSED    = "-n";
const string ARG_AMOUNT            = "-a";
const string ARG_INITIAL_PAYMENT   = "-ai";
const string ARG_INTEREST          = "-i";
const string ARG_OPENFEE           = "-of";
const string ARG_OPENPERCENT       = "-op";

void loadCmdLine(CmdLineParser &clp) {
    clp.setMainHelpText("A simple loan calculator");
    
    // Calculation types
    clp.addMutExclCmdLineOption(new CmdLineOptionFlag(ARG_CALC_BALANCE, "Calculate loan balance", false, CALC_BALANCE));
    clp.addMutExclCmdLineOption(new CmdLineOptionFlag(ARG_CALC_PAYMENT, "Calculate monthly payment", false, CALC_PAYMENT));
    clp.addMutExclCmdLineOption(new CmdLineOptionFlag(ARG_CALC_NUMPAYMENTS, "Calculate number of payments", false, CALC_NUMPAYMENTS));
    clp.addMutExclCmdLineOption(new CmdLineOptionFlag(ARG_CALC_AMOUNT, "Calculate initial loan amount", false, CALC_AMOUNT));
    clp.addMutExclCmdLineOption(new CmdLineOptionFlag(ARG_CALC_INTEREST, "Calculate interest rate", false, CALC_INTEREST));

    // Values
    clp.addCmdLineOption(new CmdLineOptionFloat(ARG_PAYMENT, "Monthly loan payment"));
    clp.addCmdLineOption(new CmdLineOptionInt(ARG_PERIOD_TOTAL, "Total loan period in months"));
    clp.addCmdLineOption(new CmdLineOptionInt(ARG_PERIOD_ELAPSED, "Elapsed period in months"));
    clp.addCmdLineOption(new CmdLineOptionInt(ARG_AMOUNT, "Initial amount"));
    clp.addCmdLineOption(new CmdLineOptionFloat(ARG_INITIAL_PAYMENT, "Initial payment (down payment)"));
    clp.addCmdLineOption(new CmdLineOptionFloat(ARG_INTEREST, "Yearly interest rate"));
    clp.addCmdLineOption(new CmdLineOptionFloat(ARG_OPENFEE, "Opening fees"));
    clp.addCmdLineOption(new CmdLineOptionFloat(ARG_OPENPERCENT, "Opening fee percentage"));
}

// --- NEW FUNCTION: Read Config File ---
void readConfigFile(LoanCalculator &calculator) {
    ifstream file("config.txt");
    if (!file.is_open()) return; // If file doesn't exist, ignore

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        double value;
        
        // Format expected: "Key: Value"
        if (getline(ss, key, ':') && ss >> value) {
            if (key.find("Amount") != string::npos) calculator.setAmount(value);
            else if (key.find("Interest") != string::npos) calculator.setInterest(value);
            else if (key.find("Period") != string::npos) calculator.setPeriodTotal((int)value);
        }
    }
}
// --------------------------------------

CALC_TYPE parseCommandLine(int argc, char **argv, CmdLineParser &clp, LoanCalculator &calculator) {
    CALC_TYPE ct(CALC_UNKNOWN);

    if(!clp.parseCmdLine(argc, argv)) {
        clp.printUsage();
        return ct;
    }

    // 1. Read Config File First (Defaults)
    readConfigFile(calculator);

    // 2. Override with Command Line Arguments if present
    int cmdAmount = ((CmdLineOptionInt*) clp.getCmdLineOption(ARG_AMOUNT))->getValue();
    float cmdInterest = ((CmdLineOptionFloat*) clp.getCmdLineOption(ARG_INTEREST))->getValue();
    int cmdPeriod = ((CmdLineOptionInt*) clp.getCmdLineOption(ARG_PERIOD_TOTAL))->getValue();

    // Only set if non-zero (meaning user provided them)
    if (cmdAmount != 0) {
        if (cmdAmount < 0) { cerr << "Error: Amount cannot be negative." << endl; return CALC_UNKNOWN; }
        calculator.setAmount(cmdAmount);
    }
    if (cmdInterest != 0) {
         if (cmdInterest < 0) { cerr << "Error: Interest cannot be negative." << endl; return CALC_UNKNOWN; }
        calculator.setInterest(cmdInterest);
    }
    if (cmdPeriod != 0) {
         if (cmdPeriod < 0) { cerr << "Error: Period cannot be negative." << endl; return CALC_UNKNOWN; }
        calculator.setPeriodTotal(cmdPeriod);
    }

    calculator.setInitialPayment(((CmdLineOptionFloat*) clp.getCmdLineOption(ARG_INITIAL_PAYMENT))->getValue());
    calculator.setPayment(((CmdLineOptionFloat*) clp.getCmdLineOption(ARG_PAYMENT))->getValue());
    calculator.setPeriodElapsed(((CmdLineOptionInt*) clp.getCmdLineOption(ARG_PERIOD_ELAPSED))->getValue());
    calculator.setOpeningFee(((CmdLineOptionFloat*) clp.getCmdLineOption(ARG_OPENFEE))->getValue());
    calculator.setOpeningPercent(((CmdLineOptionFloat*) clp.getCmdLineOption(ARG_OPENPERCENT))->getValue());

    CmdLineOption *option(clp.getMutExclOption());
    if(option != NULL) ct = (CALC_TYPE) ((CmdLineOptionFlag*) option)->getValueKey();

    return ct;
}

int main(int argc, char **argv) {
    LoanCalculator calculator;
    CmdLineParser clp;
    loadCmdLine(clp);

    CALC_TYPE ct = parseCommandLine(argc, argv, clp, calculator);

    if (ct == CALC_UNKNOWN) return 1; 

    try {
        cout << endl;
        if(ct == CALC_BALANCE) {
            cout << "Loan Balance = " << (float) calculator.calculateLoanBalance() << endl;
        }
        else if(ct == CALC_PAYMENT) {
            float payment = calculator.calculatePayment();
            cout << "Monthly Payment = " << payment << endl;
        }
        else if(ct == CALC_NUMPAYMENTS) {
            cout << "Number of payments = " << (float) calculator.calculateNumberPayments() << endl;
        }
        else if(ct == CALC_AMOUNT) {
            cout << "Initial Loan amount = " << (float) calculator.calculateLoanAmount() << endl;
        }
        else if(ct == CALC_INTEREST) {
            cout << "Yearly Interest Rate = " << (float) calculator.calculateInterestRate() << "%" << endl;
        }
    }
    catch(const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
