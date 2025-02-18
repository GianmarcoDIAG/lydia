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
#include <lydia/logic/ppltlplus/base.hpp>

namespace whitemech::lydia {

    ppltl_plus_ptr AstManager::makePpltlPlusTrue() { return ppltl_plus_true_; }
    ppltl_plus_ptr AstManager::makePpltlPlusFalse() { return ppltl_plus_false_; }

    ppltl_plus_ptr AstManager::makePpltlPlusBool(bool value) {
        return value ? ppltl_plus_true_ : ppltl_plus_false_;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusAnd(const set_ppltl_plus_formulas& args) {
        ppltl_plus_ptr (AstManager::*fun)(bool) = &AstManager::makePpltlPlusBool;
        auto tmp = and_or<const PPLTLPlusFormula, PPLTLPlusAnd, PPLTLPlusTrue, PPLTLPlusFalse, PPLTLPlusNot,
                    PPLTLPlusAnd, PPLTLPlusOr>(*this, args, false, fun);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusOr(const set_ppltl_plus_formulas& args) {
        ppltl_plus_ptr (AstManager::*fun)(bool) = &AstManager::makePpltlPlusBool;
        auto tmp = and_or<const PPLTLPlusFormula, PPLTLPlusOr, PPLTLPlusTrue, PPLTLPlusFalse, PPLTLPlusNot,
        PPLTLPlusAnd, PPLTLPlusOr>(*this, args, false, fun);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusNot(const ppltl_plus_ptr& arg) {
        auto tmp = std::make_shared<const PPLTLPlusNot>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusExists(const ppltl_ptr& arg) {
        auto tmp = std::make_shared<const PPLTLPlusExists>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusForall(const ppltl_ptr& arg) {
        auto tmp = std::make_shared<const PPLTLPlusForall>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusExistsForall(const ppltl_ptr& arg) {
        auto tmp = std::make_shared<const PPLTLPlusExistsForall>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }

    ppltl_plus_ptr AstManager::makePpltlPlusForallExists(const ppltl_ptr& arg) {
        auto tmp = std::make_shared<const PPLTLPlusForallExists>(*this, arg);
        auto result = insert_if_not_available_(tmp);
        return result;
    }
} // namespace whitemech::lydia