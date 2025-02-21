#include "CLI/CLI.hpp"
#include "lydia/logic/to_ldlf.hpp"
#include <iostream>
#include <istream>
#include <lydia/dfa/mona_dfa.hpp>
// #include <lydia/parser/ldlf/driver.hpp>
// #include <lydia/parser/ltlf/driver.hpp>
#include <lydia/parser/ppltl/driver.hpp>
#include <lydia/to_dfa/core.hpp>
#include <lydia/to_dfa/strategies/compositional/base.hpp>
#include <lydia/utils/print.hpp>
#include <synthesis/syn.h>

int main(int argc, char** argv) {

    // creates driver
    std::shared_ptr<whitemech::lydia::AbstractDriver> driver;
    driver = std::make_shared<whitemech::lydia::parsers::ppltl::PPLTLDriver>();

    // creates and parses PPLTL formula
    std::string ppltl_formula = "!(O(a) -> H(b))";
    std::stringstream formula_stream(ppltl_formula);
    driver->parse(formula_stream);
    auto parsed_formula = driver->get_result();

    // result from parsing
    whitemech::lydia::ppltl_ptr ppltl_parsed_formula = 
        std::static_pointer_cast<const whitemech::lydia::PPLTLFormula>(parsed_formula);

    whitemech::lydia::StrPrinter printer;
    auto printer_result = printer.apply(*ppltl_parsed_formula);

    // get NNF
    whitemech::lydia::NNFTransformer t;
    auto nnf_ppltl_parsed_formula =
        t.apply(*ppltl_parsed_formula);
    
    printer_result = printer.apply(*nnf_ppltl_parsed_formula);
    std::cout << "Input formula: " << ppltl_formula << ". Formula in NNF: " << printer_result << std::endl;
}