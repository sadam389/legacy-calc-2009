#include <iostream>
#include <algorithm>
#include "CmdLineParser.h"

using namespace std;

CmdLineParser::CmdLineParser() : mutExclOption_(NULL) {}

CmdLineParser::~CmdLineParser() {
    for(auto const& x : options_) delete x.second;
}

void CmdLineParser::addCmdLineOption(CmdLineOption *option) {
    options_[option->getName()] = option;
}

void CmdLineParser::addMutExclCmdLineOption(CmdLineOption *option) {
    options_[option->getName()] = option;
}

bool CmdLineParser::parseCmdLine(int argc, char **argv) {
    for(int i=1; i<argc; ++i) {
        string arg = argv[i];
        if(options_.count(arg)) {
            CmdLineOption *opt = options_[arg];
            // Check if it is the mutual exclusive option (the calc type)
            CmdLineOptionFlag* flag = dynamic_cast<CmdLineOptionFlag*>(opt);
            if(flag && flag->getValueKey() >= 100) { 
                mutExclOption_ = opt;
            } else {
                // It's a value option, get the next arg
                if(i+1 < argc) {
                    string val = argv[++i];
                    opt->parse(val);
                }
            }
        }
    }
    return true;
}

void CmdLineParser::printUsage() {
    cout << mainHelpText_ << endl;
    cout << "Options:" << endl;
    for(auto const& x : options_) {
        cout << "  " << x.first << "\t" << x.second->getDescription() << endl;
    }
}

CmdLineOption* CmdLineParser::getCmdLineOption(const string &name) {
    if(options_.count(name)) return options_[name];
    return NULL;
}
