/*
 * Copyright(C) NextGen Federal Systems, LLC - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 */

#ifndef _GETOPT_H
#define _GETOPT_H

#include <vector>
#include <set>
#include <map>
#include <string>

class OptionsDef {
private:
    std::set<std::string> options;
    std::set<std::string> flags;
public:
    OptionsDef();
    OptionsDef(std::vector<std::string> opts, std::vector<std::string> flgs);
    void addOption(std::string opt);
    void addFlag(std::string flg);
    std::string matchesOption(std::string opt);
    bool isOption(std::string opt);
    std::string matchesFlag(std::string flg);
    bool isFlag(std::string flag);
};

//typedef std::list<std::string> OptionsDef;
typedef std::map<std::string, std::string> Options;

Options getOptions(const int agrc, const char** argv, OptionsDef& known);

#endif  // !_GETOPT_H
