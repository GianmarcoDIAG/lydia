#include <iostream>
#include <istream>
#include <sstream>
#include<lydia/logic/ltlf/progression.hpp>
#include<lydia/parser/ltlf/driver.hpp>
#include<lydia/utils/print.hpp>

int main(int argc, char** argv) {
 
    // create a parser for LTLf
    std::shared_ptr<whitemech::lydia::AbstractDriver> driver;
    driver = std::make_shared<whitemech::lydia::parsers::ltlf::LTLfDriver>();

    // create set of test LTLf formulas
    std::string f1 = "true";
    std::string f2 = "false";
    std::string f3 = "a";
    std::string f4 = "!a";
    std::string f5 = "a && b";
    std::string f6 = "!(a && b)";
    std::string f7 = "a || b";
    std::string f8 = "!(a || b)";
    std::string f9 = "X[!](a)";
    std::string f10 = "!(X[!](a))";
    std::string f11 = "X(a)";
    std::string f12 = "!X(a)";
    std::string f13 = "a U b";
    std::string f14 = "!(a U b)";
    std::string f15 = "a R b";
    std::string f16 = "!(a R b)";
    std::string f17 = "F(a)";
    std::string f18 = "!(F(a))";
    std::string f19 = "G(a)";
    std::string f20 = "!(G(a))";
    std::string f21 = "G(a -> F(b))";
    std::string f22 = "!G(a -> F(b))";
    std::string f23 = "F(a && X[!](b))";
    std::string f24 = "!F(a && X[!](b))";
    std::string f25 = "F(a && X[!](F(b)))";
    std::string f26 = "!F(a && X[!](F(b)))";

    // parse formulas and store results in vector
    std::vector<std::string> ltlf_test_strings = {f1, f2, f3, f4, f5, f6, f7, f8,
                                                  f9, f10, f11, f12, f13, f14,
                                                  f15, f16, f17, f18, f19, f20,
                                                  f21, f22, f23, f24, f25, f26};
    std::vector<whitemech::lydia::ltlf_ptr> ltlf_test_formulas;

    for (const auto& f : ltlf_test_strings) {
        std::stringstream formula_stream(f);
        driver->parse(formula_stream);
        auto parsed_formula = driver->get_result();
        whitemech::lydia::ltlf_ptr ltlf_parsed_formula =
            std::static_pointer_cast<const whitemech::lydia::LTLfFormula>(parsed_formula);
        ltlf_test_formulas.push_back(ltlf_parsed_formula);
    }

    // create a set of test interpretations and histories
    whitemech::lydia::Interpretation i1 = {{"a", true}, {"b", true}};
    whitemech::lydia::Interpretation i2 = {{"a", true}, {"b", false}};
    whitemech::lydia::Interpretation i3 = {{"a", false}, {"b", true}};
    whitemech::lydia::Interpretation i4 = {{"a", false}, {"b", false}};

    whitemech::lydia::History h1 = {i1};
    whitemech::lydia::History h2 = {i2};
    whitemech::lydia::History h3 = {i3};
    whitemech::lydia::History h4 = {i4};
    // all histories of length 2
    whitemech::lydia::History h5 = {i1, i1};
    whitemech::lydia::History h6 = {i1, i2};
    whitemech::lydia::History h7 = {i1, i3};
    whitemech::lydia::History h8 = {i1, i4};
    whitemech::lydia::History h9 = {i2, i1};
    whitemech::lydia::History h10 = {i2, i2};
    whitemech::lydia::History h11 = {i2, i3};
    whitemech::lydia::History h12 = {i2, i4};
    whitemech::lydia::History h13 = {i3, i1};
    whitemech::lydia::History h14 = {i3, i2};
    whitemech::lydia::History h15 = {i3, i3};
    whitemech::lydia::History h16 = {i3, i4};
    whitemech::lydia::History h17 = {i4, i1};
    whitemech::lydia::History h18 = {i4, i2};
    whitemech::lydia::History h19 = {i4, i3};
    whitemech::lydia::History h20 = {i4, i4};

    std::vector<whitemech::lydia::History> histories = {h1, h2, h3, h4,
                                                        h5, h6, h7, h8,
                                                        h9, h10, h11, h12,
                                                        h13, h14, h15, h16,
                                                        h17, h18, h19, h20};

    // initialize printer
    whitemech::lydia::StrPrinter printer;


    // iterate through all test formulas and histories and apply progression
    for (auto& f : ltlf_test_formulas) {
        std::cout << "---------- TEST CASE BEGIN ----------" << std::endl;
        auto strf = printer.apply(*f);
        std::cout << "LTLf formula: " << strf << std::endl;
        auto fnnf = whitemech::lydia::to_nnf(*f);
        auto strfnnf = printer.apply(*fnnf);
        std::cout << "NNF of LTLf formula: " << strfnnf << std::endl;
        for (auto& h : histories) {
            auto ch = h; // copy history to avoid modifying the original
            int t = 0;
            std::cout << std::endl;
            std::cout << "---- History (length: " << ch.size() << ") ----" << std::endl;
            for (const auto& pi : ch) {
                std::cout << "{t = " << t++ << std::endl;
                for (const auto& atom : pi) {
                    std::cout << "(Atom: " << atom.first << " = " << (atom.second ? "true" : "false") << ")" << std::endl;
                }
                std::cout << "}" << std::endl;
            }
            std::cout << "---- End of History ----" << std::endl;
            auto pf = whitemech::lydia::progression(*f, ch); // pf is the progression of f with respect to h
            auto strpf = printer.apply(*pf);
            std::cout << "Progression of LTLf formula: " << strpf << std::endl;

        }
        std::cout << "---------- TEST CASE END ----------" << std::endl;
        std::cout << std::endl;

        
    }
}