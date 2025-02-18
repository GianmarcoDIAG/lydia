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

#include <lydia/parser/ppltl/driver.cpp>
#include <lydia/parser/ppltlplus/driver.hpp>

namespace whitemech::lydia::parsers::ppltlplus {

    PPLTLPlusDriver::~PPLTLPlusDriver() {
        delete (scanner);
        scanner = nullptr;
        delete (parser);
        parser = nullptr;
    }

    void PPLTLPlusDriver::parse(const char* const filename) {
      assert(filename != nullptr);
      std::ifstream in_file(filename);
      if (!in_file.good()) {
        exit(EXIT_FAILURE);
      }
      parse_helper(in_file);
    }

    void PPLTLPlusDriver::parse(std::istream& stream) {
      if (!stream.good() && stream.eof()) {
        return;
      }
      parse_helper(stream);
    }

    void PPLTLPlusDriver::parse_helper(std::istream& stream) {
      delete (scanner);
      try {
        scanner = new PPLTLPlusScanner(&stream);
      } catch (std::bad_alloc& ba) {
        std::cerr << "Failed to allocate scanner: (" << ba.what()
              << "), exiting!\n";
        exit(EXIT_FAILURE);
      }

      delete (parser);
      try {
        parser = new PPLTLPlusParser((*scanner), (*this));
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

    // PPLTL Base Formula Handling Methods
    ppltl_ptr PPLTLPlusDriver::add_PPTLTrue() const {
      return context->makePpltlTrue();
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLFalse() const {
      return context->makePpltlFalse();
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLAtom(std::string s) const {
      return context->makePpltlAtom(s);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLAnd(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
      return context->makePpltlAnd({lhs, rhs});
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLOr(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
      return context->makePpltlOr({lhs, rhs});
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLNot(ppltl_ptr& formula) const {
      return context->makePpltlNot(formula);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLYesterday(ppltl_ptr& formula) const {
      return context->makePpltlYesterday(formula);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLWeakYesterday(ppltl_ptr& formula) const {
      return context->makePpltlWeakYesterday(formula);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLOnce(ppltl_ptr& formula) const {
      return context->makePpltlOnce(formula);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLHistorically(ppltl_ptr& formula) const {
      return context->makePpltlHistorically(formula);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLSince(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
      return context->makePpltlSince(lhs, rhs);
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLImplication(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
      return context->makePpltlOr({context->makePpltlNot(lhs), rhs});
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLEquivalence(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
      auto ptr_left_implication = this->add_PPTLImplication(lhs, rhs);
      auto ptr_right_implication = this->add_PPTLImplication(rhs, lhs);
      return context->makePpltlAnd({ptr_left_implication, ptr_right_implication});
    }

    ppltl_ptr PPLTLPlusDriver::add_PPTLStart() const {
      auto ptr_true = context->makePpltlTrue();
      auto ptr_yesterday_true = context->makePpltlYesterday(ptr_true);
      return context->makePpltlNot(ptr_yesterday_true);
    }

    // PPTLPlus Formula Handling Methods
    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusAnd(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const {
        return context->makePpltlPlusAnd({lhs, rhs});
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusOr(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const {
        return context->makePpltlPlusOr({lhs, rhs});
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusImplication(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const {
        return context->makePpltlPlusOr({context->makePpltlPlusNot(lhs), rhs});
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusEquivalence(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const {
        auto ptr_left_implication = this->add_PPTLPlusImplication(lhs, rhs);
        auto ptr_right_implication = this->add_PPTLPlusImplication(rhs, lhs);
        return context->makePpltlPlusAnd({ptr_left_implication, ptr_right_implication});
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusNot(ppltl_plus_ptr& formula) const {
        return context->makePpltlPlusNot(formula);
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusExists(ppltl_ptr& formula) {
        return context->makePpltlPlusExists(formula);
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusForall(ppltl_ptr& formula) {
        return context->makePpltlPlusForall(formula);
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusExistsForall(ppltl_ptr& formula) {
        return context->makePpltlPlusExistsForall(formula);
    }

    ppltl_plus_ptr PPLTLPlusDriver::add_PPTLPlusForallExists(ppltl_ptr& formula) {
        return context->makePpltlPlusForallExists(formula);
    }

    std::ostream& PPLTLPlusDriver::print(std::ostream& stream) const {
      stream << this->result->str() << "\n";
      return stream;
    }

} // namespace whitemech::lydia::parsers::ppltlplus