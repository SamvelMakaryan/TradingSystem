#include <iostream>

#include "Signals.hpp"

namespace sig {
    
    void cntrlC(int) {
        std::cout << "Closing Trading System\n All changes are saved\n";
        std::exit(EXIT_SUCCESS);
    }

} // namespace sig
