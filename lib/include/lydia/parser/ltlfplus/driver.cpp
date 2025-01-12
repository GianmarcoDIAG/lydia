/*
 * This file is part of Lydia.
 *
 * Lydia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lydia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Lydia.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <fstream>

#include <lydia/parser/ltlf/driver.hpp>
#include <lydia/parser/ltlfplus/driver.hpp>

namespace whitemech::lydia::parsers::ltlfplus {

    LTLfPlusDriver::~LTLfPlusDriver() {
        delete (scanner);
        scanner = nullptr;
        delete (parser);
        parser = nullptr;
    }

    // TODO (Gianmarco). Add remaining methods
    void LTLfPlusDriver::parse(const char* const filename) {
      assert(filename != nullptr);
      std::ifstream in_file(filename);
      if (!in_file.good()) {
        exit(EXIT_FAILURE);
      }
      parse_helper(in_file);
    }

    void LTLfPlusDriver::parse(std::istream& stream) {
      if (!stream.good() && stream.eof()) {
        return;
      }
      parse_helper(stream);
    }

    void LTLfPlusDriver::parse_helper(std::istream& stream) {
      delete (scanner);
      try {
        scanner = new LTLfPlusScanner(&stream);
      } catch (std::bad_alloc& ba) {
        std::cerr << "Failed to allocate scanner: (" << ba.what()
              << "), exiting!\n";
        exit(EXIT_FAILURE);
      }

      delete (parser);
      try {
        parser = new LTLfPlusParser((*scanner) /* scanner */, (*this) /* driver */);
      } catch (std::bad_alloc& ba) {
        std::cerr << "Failed to allocate parser: (" << ba.what() << "), exiting!\n";
        exit(EXIT_FAILURE);
      }
      const int accept(0);
      if (parser->parse() != accept) {
        std::cerr << "Parse failed!\n";
        exit(EXIT_FAILURE);
      }
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfTrue() const { return context->makeLtlfTrue(); }

    ltlf_ptr LTLfPlusDriver::add_LTLfFalse() const { return context->makeLtlfFalse(); }

    ltlf_ptr LTLfPlusDriver::add_LTLfAtom(std::string s) const {
      return context->makeLtlfAtom(s);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfAnd(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      return context->makeLtlfAnd({lhs, rhs});
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfOr(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      return context->makeLtlfOr({lhs, rhs});
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfNot(ltlf_ptr& formula) const {
      return context->makeLtlfNot(formula);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfNext(ltlf_ptr& formula) const {
      return context->makeLtlfNext(formula);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfWeakNext(ltlf_ptr& formula) const {
      return context->makeLtlfWeakNext(formula);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfEventually(ltlf_ptr& formula) const {
      return context->makeLtlfEventually(formula);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfAlways(ltlf_ptr& formula) const {
      return context->makeLtlfAlways(formula);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfUntil(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      return context->makeLtlfUntil(lhs, rhs);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfRelease(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      return context->makeLtlfRelease(lhs, rhs);
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfImplication(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      return context->makeLtlfOr({context->makeLtlfNot(lhs), rhs});
    }

    ltlf_ptr LTLfPlusDriver::add_LTLfEquivalence(ltlf_ptr& lhs, ltlf_ptr& rhs) const {
      auto ptr_left_implication = this->add_LTLfImplication(lhs, rhs);
      auto ptr_right_implication = this->add_LTLfImplication(rhs, lhs);
      set_ltlf_formulas children({ptr_left_implication, ptr_right_implication});
      return context->makeLtlfAnd(children);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusAnd(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const {
        return context -> makeLtlfPlusAnd({lhs, rhs});
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusOr(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const {
        return context -> makeLtlfPlusOr({lhs, rhs});
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusImplication(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const {
        return context -> makeLtlfPlusOr({context->makeLtlfPlusNot(lhs), rhs});
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusEquivalence(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const {
        auto ptr_left_implication = this->add_LTLfPlusImplication(lhs, rhs);
        auto ptr_right_implication = this->add_LTLfPlusImplication(rhs, lhs);
        set_ltlf_plus_formulas children({ptr_left_implication, ptr_right_implication});
        return context->makeLtlfPlusAnd(children);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusNot(ltlf_plus_ptr& formula) const {
        return context -> makeLtlfPlusNot(formula);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusExists(ltlf_ptr& formula) {
        return context -> makeLtlfPlusExists(formula);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusForall(ltlf_ptr& formula) {
        return context -> makeLtlfPlusForall(formula);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusExistsForall(ltlf_ptr& formula) {
        return context -> makeLtlfPlusExistsForall(formula);
    }

    ltlf_plus_ptr LTLfPlusDriver::add_LTLfPlusForallExists(ltlf_ptr& formula) {
        return context -> makeLtlfPlusForallExists(formula);
    }

    std::ostream& LTLfPlusDriver::print(std::ostream& stream) const {
      stream << this->result->str() << "\n";
      return stream;
    }
}