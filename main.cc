#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <memory>

using namespace yy;

int main() {
    int ret = 0;
    Driver driver{};
    try {
        driver.parse();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}