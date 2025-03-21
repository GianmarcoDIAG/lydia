#include "CLI/CLI.hpp"
#include "lydia/logic/to_ldlf.hpp"
#include <iostream>
#include <istream>
#include <lydia/dfa/mona_dfa.hpp>
// #include <lydia/parser/ppltl/driver.hpp>
#include <lydia/parser/ppltlplus/driver.hpp>
#include <lydia/to_dfa/core.hpp>
#include <lydia/to_dfa/strategies/compositional/base.hpp>
#include <lydia/utils/print.hpp>
#include <lydia/logic/ynf.hpp>
#include <lydia/logic/pp_pnf.hpp>
#include <synthesis/syn.h>

int main(int argc, char** argv) {

    // creates driver
    // std::shared_ptr<whitemech::lydia::AbstractDriver> driver;
    // driver = std::make_shared<whitemech::lydia::parsers::ppltl::PPLTLDriver>();

    // creates and parses PPLTL formula
    // std::string ppltl_formula = "!(O(a) -> H(b))";
    // std::string ppltl_formula = "O(Y(a) && O(b))";
    // std::string ppltl_formula = "Y(!(Y(a)))";
    // std::string ppltl_formula = "(a S b)";
    // std::string ppltl_formula = "(a T b)";
    // std::string ppltl_formula = "H(a || b)";
    // std::string ppltl_formula = "!(a S b)";
    // std::string ppltl_formula = "Y(a) && (!b S c) && H(d)";
    // std::stringstream formula_stream(ppltl_formula);
    // driver->parse(formula_stream);
    // auto parsed_formula = driver->get_result();

    // // result from parsing
    // whitemech::lydia::ppltl_ptr ppltl_parsed_formula = 
    //     std::static_pointer_cast<const whitemech::lydia::PPLTLFormula>(parsed_formula);

    // whitemech::lydia::StrPrinter printer;
    // auto printer_result = printer.apply(*ppltl_parsed_formula);

    // // get NNF
    // whitemech::lydia::NNFTransformer t;
    // auto nnf_ppltl_parsed_formula =
    //     t.apply(*ppltl_parsed_formula);

    // // get YNF
    // whitemech::lydia::YNFTransformer yt;
    // auto ynf_parsed_formula =
    //     yt.apply(*nnf_ppltl_parsed_formula);        
    
    // auto printer_nnf_result = printer.apply(*nnf_ppltl_parsed_formula);
    // auto printer_ynf_result = printer.apply(*ynf_parsed_formula);
    // std::cout << "Input formula: " << ppltl_formula << std::endl;
    // std::cout << "Formula in NNF: " << printer_nnf_result << std::endl;
    // std::cout << "Formula in YNF: " << printer_ynf_result << std::endl;

    // show subformulas
    // auto y_sub = yt.get_y_sub();
    // auto wy_sub = yt.get_wy_sub();
    // auto atoms  = yt.get_atoms();

    // for (const auto& y : y_sub) {
        // auto y_print = printer.apply(*y);
        // std::cout << "Y subformula: " << y_print << std::endl;
    // }

    // for (const auto& wy : wy_sub) {
        // auto wy_print = printer.apply(*wy);
        // std::cout << "WY subformula: " << wy_print << std::endl;
    // }

    // for (const auto& a : atoms) {
        // auto a_print = printer.apply(*a);
        // std::cout << "Atom: " << a_print << std::endl;
    // }

    whitemech::lydia::StrPrinter printer;

    std::shared_ptr<whitemech::lydia::AbstractDriver> driver_plus;
    driver_plus = std::make_shared<whitemech::lydia::parsers::ppltlplus::PPLTLPlusDriver>();

    std::string ppltl_plus_formula = 
        // "E(O(a)) && A(H(b)) && EA(c) && AE(d)";
        "!E(O(a)) || !A(H(b)) || !EA(c) || !AE(d)";
    std::stringstream plus_formula_stream(ppltl_plus_formula);
    driver_plus->parse(plus_formula_stream);

    auto parsed_formula_plus = driver_plus->get_result();
    whitemech::lydia::ppltl_plus_ptr ppltl_plus_parsed_formula = 
        std::static_pointer_cast<const whitemech::lydia::PPLTLPlusFormula>(parsed_formula_plus);

    auto printer_plus = printer.apply(*ppltl_plus_parsed_formula);
    std::cout << "Input formula: " << printer_plus << std::endl;

    // construct PNF of PPLTL+ formula
    whitemech::lydia::PPPNFTransformer pt;
    whitemech::lydia::PPPNFResult pnf_parsed_formula = 
        whitemech::lydia::get_pnf_result(*ppltl_plus_parsed_formula);

    // print PNF
    std::cout << "Color formula: " << pnf_parsed_formula.color_formula_ << std::endl;
    std::cout << "Subformula to color" << std::endl;
    for (const auto& [subformula, color] : pnf_parsed_formula.subformula_to_color_) {
        auto subformula_print = printer.apply(*subformula);
        std::cout << "Subformula: " << subformula_print << ". Color: " << color << std::endl;
    }
    std::cout << "Subformula to quantifier" << std::endl;
    for (const auto& [subformula, quantifier] : pnf_parsed_formula.subformula_to_quantifier_) {
        auto subformula_print = printer.apply(*subformula);
        // if quantifier == 0 print E, if quantifier == 1 print A, quantifier  == 2, print EA, quantifier == 3, print AE
        std::cout << "Subformula: " << subformula_print;
        if (quantifier == 0) std::cout << ". Quantifier: E" << std::endl;
        if (quantifier == 1) std::cout << ". Quantifier: A" << std::endl;
        if (quantifier == 2) std::cout << ". Quantifier: EA" << std::endl;
        if (quantifier == 3) std::cout << ". Quantifier: AE" << std::endl;        
    }
}