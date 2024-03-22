#include <stdexcept>
#include "driver.hpp"
#include "lexer.hpp"
#include <memory>
#include "visitor.hpp"

using namespace yy;
#define EVAL

int main() {
    int ret = 0;
    Driver driver{};
    std::string filename{"examples/input/base_test.in"};
    try {
        auto ret_parse = driver.parse();
        if (ret_parse) {
            auto root = driver.get_ast_root();
            AST::Visitor vis{filename};
            vis.eval(root);
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = 1;
    }
    return ret;
}
