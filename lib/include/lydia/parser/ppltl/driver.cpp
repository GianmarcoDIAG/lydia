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

#include <lydia/parser/ppltl/driver.hpp>

namespace whitemech::lydia::parsers::ppltl {

PPLTLDriver::~PPLTLDriver() {
  delete (scanner);
  scanner = nullptr;
  delete (parser);
  parser = nullptr;
}

void PPLTLDriver::parse(const char* const filename) {
  assert(filename != nullptr);
  std::ifstream in_file(filename);
  if (!in_file.good()) {
    exit(EXIT_FAILURE);
  }
  parse_helper(in_file);
}

void PPLTLDriver::parse(std::istream& stream) {
  if (!stream.good() && stream.eof()) {
    return;
  }
  parse_helper(stream);
}

void PPLTLDriver::parse_helper(std::istream& stream) {
  delete (scanner);
  try {
    scanner = new PPLTLScanner(&stream);
  } catch (std::bad_alloc& ba) {
    std::cerr << "Failed to allocate scanner: (" << ba.what()
              << "), exiting!\n";
    exit(EXIT_FAILURE);
  }

  delete (parser);
  try {
    parser = new PPLTLDriver((*scanner), (*this));
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

ppltl_ptr PPLTLDriver::add_PPLTLTrue() const {
  return context->makePpltlTrue();
}

ppltl_ptr PPLTLDriver::add_PPLTLFalse() const {
  return context->makePpltlFalse();
}

ppltl_ptr PPLTLDriver::add_PPLTLAtom(std::string s) const {
  return context->makePpltlAtom(s);
}

ppltl_ptr PPLTLDriver::add_PPLTLAnd(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
  return context->makePpltlAnd({lhs, rhs});
}

ppltl_ptr PPLTLDriver::add_PPLTLOr(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
  return context->makePpltlOr({lhs, rhs});
}

ppltl_ptr PPLTLDriver::add_PPLTLNot(ppltl_ptr& formula) const {
  return context->makePpltlNot(formula);
}

ppltl_ptr PPLTLDriver::add_PPLTLYesterday(ppltl_ptr& formula) const {
  return context->makePpltlYesterday(formula);
}

ppltl_ptr PPLTLDriver::add_PPLTLWeakYesterday(ppltl_ptr& formula) const {
  return context->makePpltlWeakYesterday(formula);
}

ppltl_ptr PPLTLDriver::add_PPLTLOnce(ppltl_ptr& formula) const {
  return context->makePpltlOnce(formula);
}

ppltl_ptr PPLTLDriver::add_PPLTLHistorically(ppltl_ptr& formula) const {
  return context->makePpltlHistorically(formula);
}

ppltl_ptr PPLTLDriver::add_PPLTLSince(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
  return context->makePpltlSince(lhs, rhs);
}

ppltl_ptr PPLTLDriver::add_PPLTLImplication(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
  // Implication a → b is equivalent to ¬a ∨ b
  auto ptr_not_lhs = context->makePpltlNot(lhs);
  return context->makePpltlOr({ptr_not_lhs, rhs});
}

ppltl_ptr PPLTLDriver::add_PPLTLEquivalence(ppltl_ptr& lhs, ppltl_ptr& rhs) const {
  // Equivalence a ↔ b is equivalent to (a → b) ∧ (b → a)
  auto ptr_left_implication = this->add_PPLTLImplication(lhs, rhs);
  auto ptr_right_implication = this->add_PPLTLImplication(rhs, lhs);
  return context->makePpltlAnd({ptr_left_implication, ptr_right_implication});
}

ppltl_ptr PPLTLDriver::add_PPLTLStart() const {
  // start ≡ ¬Y(true)
  auto ptr_true = context->makePpltlTrue();
  auto ptr_yesterday_true = context->makePpltlYesterday(ptr_true);
  return context->makePpltlNot(ptr_yesterday_true);
}

std::ostream& PPLTLDriver::print(std::ostream& stream) const {
  stream << this->result->str() << "\n";
  return (stream);
}

} // namespace whitemech::lydia::parsers::ppltl