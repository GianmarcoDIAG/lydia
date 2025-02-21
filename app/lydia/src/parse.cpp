#include "CLI/CLI.hpp"
#include "lydia/logic/to_ldlf.hpp"
#include <iostream>
#include <istream>
#include <lydia/dfa/mona_dfa.hpp>
#include <lydia/parser/ldlf/driver.cpp>
#include <lydia/parser/ltlf/driver.cpp>
#include <lydia/parser/ppltl/driver.cpp>
#include <lydia/to_dfa/core.hpp>
#include <lydia/to_dfa/strategies/compositional/base.hpp>
#include <lydia/utils/print.hpp>
#include <synthesis/syn.h>

int main(int argc, char** argv) {

    // creates driver
    std::shared_ptr<whitemech::lydia::AbstractDriver> driver;
    driver = std::make_shared<whitemech::lydia::parsers::ppltl::PPLTLDriver>();

    // creates and parses PPLTL formula
    std::string ppltl_formula = "H(a -> Y(b))";
    std::stringstream formula_stream(ppltl_formula);
    driver->parse(formula_stream);
    auto parsed_formula = driver->get_result();

    // result from parsing
    whitemech::lydia::ppltl_ptr ppltl_parsed_formula = 
        std::static_pointer_cast<const whitemech::lydia::PPLTLFormula>(parsed_formula);

    whitemech::lydia::StrPrinter printer;
    auto printer_result = printer.apply(*ppltl_parsed_formula);

    std::cout << printer_result << std::endl;
}