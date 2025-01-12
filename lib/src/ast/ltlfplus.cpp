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

#include <lydia/ast/base.hpp>
#include <lydia/logic/ltlfplus/base.hpp>

namespace whitemech::lydia {

    ltlf_plus_ptr AstManager::makeLtlfPlusTrue() { return ltlf_plus_true_; }
    ltlf_plus_ptr AstManager::makeLtlfPlusFalse() { return ltlf_plus_false_; }

    ltlf_plus_ptr AstManager::makeLtlfPlusBool(bool value) {
        return value ? ltlf_plus_true_ : ltlf_plus_false_;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusAnd(const set_ltlf_plus_formulas& args) {
        ltlf_plus_ptr (AstManager::*fun)(bool) = &AstManager::makeLtlfPlusBool;
        auto tmp = and_or<const LTLfPlusFormula, LTLfPlusAnd, LTLfPlusTrue, LTLfPlusFalse, LTLfPlusNot,
                    LTLfPlusAnd, LTLfPlusOr>(*this, args, false, fun);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusOr(const set_ltlf_plus_formulas& args) {
        ltlf_plus_ptr (AstManager::*fun)(bool) = &AstManager::makeLtlfPlusBool;
        auto tmp = and_or<const LTLfPlusFormula, LTLfPlusOr, LTLfPlusTrue, LTLfPlusFalse, LTLfPlusNot,
        LTLfPlusAnd, LTLfPlusOr>(*this, args, false, fun);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusNot(const ltlf_plus_ptr& arg) {
        auto tmp = std::make_shared<const LTLfPlusNot>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusExists(const ltlf_ptr& arg) {
        auto tmp = std::make_shared<const LTLfPlusExists>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusForall(const ltlf_ptr& arg) {
        auto tmp = std::make_shared<const LTLfPlusForall>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusExistsForall(const ltlf_ptr& arg) {
        auto tmp = std::make_shared<const LTLfPlusExistsForall>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ltlf_plus_ptr AstManager::makeLtlfPlusForallExists(const ltlf_ptr& arg) {
        auto tmp = std::make_shared<const LTLfPlusForallExists>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }
} // namespace whitemech::lydia