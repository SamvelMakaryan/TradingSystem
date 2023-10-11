#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "System.hpp"

namespace cmd {

    void commandLine(const TS::System&);
    void execute(const std::string&, const TS::System&);
    void help();
    void add(std::vector<std::string>&, const TS::System&);
    void display(std::vector<std::string>&, const TS::System&);
    void remove(std::vector<std::string>&, const TS::System&);
    void search(std::vector<std::string>&, const TS::System&);

} // namespace cmd

#endif //COMMANDS_HPP_