#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "System.hpp"

namespace cmd {

    void commandLine(TS::System&);
    void execute(const std::string&, TS::System&);
    void help();
    void add(std::vector<std::string>&, TS::System&);
    void display(std::vector<std::string>&, TS::System&);
    void remove(std::vector<std::string>&, TS::System&);
    void search(std::vector<std::string>&, TS::System&);
    bool has_symbols(const std::string&);

} // namespace cmd

#endif //COMMANDS_HPP_