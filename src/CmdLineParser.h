#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class CmdLineOption {
public:
    CmdLineOption(const string &name, const string &description) 
        : name_(name), description_(description) {}
    virtual ~CmdLineOption() {}
    string getName() { return name_; }
    string getDescription() { return description_; }
    virtual bool parse(string &val) = 0;
protected:
    string name_;
    string description_;
};

class CmdLineOptionFloat : public CmdLineOption {
public:
    CmdLineOptionFloat(const string &name, const string &description) 
        : CmdLineOption(name, description), value_(0.0) {}
    bool parse(string &val) { value_ = stof(val); return true; }
    float getValue() { return value_; }
private:
    float value_;
};

class CmdLineOptionInt : public CmdLineOption {
public:
    CmdLineOptionInt(const string &name, const string &description) 
        : CmdLineOption(name, description), value_(0) {}
    bool parse(string &val) { value_ = stoi(val); return true; }
    int getValue() { return value_; }
private:
    int value_;
};

class CmdLineOptionFlag : public CmdLineOption {
public:
    CmdLineOptionFlag(const string &name, const string &description, bool hasValue, int key) 
        : CmdLineOption(name, description), hasValue_(hasValue), key_(key) {}
    bool parse(string &val) { return true; }
    int getValueKey() { return key_; }
private:
    bool hasValue_;
    int key_;
};

class CmdLineParser {
public:
    CmdLineParser();
    ~CmdLineParser();
    void setMainHelpText(const string &text) { mainHelpText_ = text; }
    void addCmdLineOption(CmdLineOption *option);
    void addMutExclCmdLineOption(CmdLineOption *option);
    bool parseCmdLine(int argc, char **argv);
    void printUsage();
    CmdLineOption* getCmdLineOption(const string &name);
    CmdLineOption* getMutExclOption() { return mutExclOption_; }
private:
    string mainHelpText_;
    map<string, CmdLineOption*> options_;
    CmdLineOption *mutExclOption_;
};

#endif