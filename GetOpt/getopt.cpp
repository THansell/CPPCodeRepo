/*
 * Copyright(C) NextGen Federal Systems, LLC - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 *
 * Proprietary and confidential
 */

#include "getopt.hpp"
#include <iostream>
#include <vector>

OptionsDef::OptionsDef() {
}

OptionsDef::OptionsDef( std::vector<std::string> opts, std::vector<std::string> flgs) {
    for( std::string s: opts) {
        this->addOption(s);
    }
    for (std::string s: flgs) {
        this->addFlag(s);
    }
}

void OptionsDef::addOption(std::string opt) {
    this->options.insert(opt);
}

void OptionsDef::addFlag(std::string flg) {
    this->flags.insert(flg);
}

std::string OptionsDef::matchesOption(std::string opt) {
    for ( std::string s: this->options ) {
        if ( s.compare(0, opt.length(), opt ) == 0 ) {
            return s;
        }
    }
    return std::string();
}

bool OptionsDef::isOption(std::string opt) {
    return ( !this->matchesOption(opt).empty() );
}

std::string OptionsDef::matchesFlag(std::string flg) {
    for (std::string s: this->flags) {
        if (s.compare(0,flg.length(), flg) == 0 ) {
            return s;
        }
    }
}

bool OptionsDef::isFlag(std::string flg) {
    return( !this->matchesFlag(flg).empty() );
}

/*
Options getOptions(const int argc, const char** argv, OptionsDef& known) {
  Options retval;
  bool errors = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    short mode = 0;
    while (arg.front() == '-') {
      arg.erase(0, 1);
      mode++;
    }

    size_t stop = arg.find('=');
    if (-1 == stop) {
      stop = arg.length();
    }

    if (mode == 0) {
      continue;
    }

    std::vector<std::string> matched;
    std::list<std::string>::iterator it = known.begin();
    for (it = known.begin(); it != known.end(); ++it) {
      std::string param = *it;
      bool match = true;
      for (int c = 1; c <= stop; ++c) {
        if (strncmp(arg.c_str(), param.c_str(), c) != 0) {
          match = false;
        }
      }

      if (match) {
        matched.push_back(param);
        if (mode == 2) {
          if (stop == arg.length()) {
            retval[param] = "true";
          } else {
            retval[param] = arg.substr(stop + 1);
          }
        }
        if (mode == 1) {
          if (i + 1 == argc || argv[i + 1][0] == '-') {
            retval[param] = "true";
          } else {
            retval[param] = argv[i + 1];
          }
        }
      }
    }
    if (matched.size() == 0) {
      errors = true;
      std::cout << "Unknown option: " << arg << std::endl;
    }
    if (matched.size() > 1) {
      errors = true;
      std::cout << "Option " << arg << " is ambiguous (";
      for (std::vector<std::string>::iterator it = matched.begin(); it != matched.end(); ++it) {
        std::cout << *it;
        if ((it + 1) != matched.end()) {
          std::cout << ",";
        }
      }
      std::cout << ")" << std::endl;
    }
  }

  if (errors) {
    exit(9);
  }

  return retval;
}
*/
