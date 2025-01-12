#pragma once
/*
 * This file is part of Nike.
 *
 * Nike is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nike is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nike.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <stdexcept>
#include <lydia/basic.hpp>
#include <lydia/logic/pl/base.hpp>
#include <lydia/logic/symbol.hpp>
#include <lydia/utils/compare.hpp>
#include <utility>

namespace whitemech::lydia {

    class InvalidLTLfPlusInput : public std::runtime_error {
        public:
            explicit InvalidLTLfPlusInput(const std::string& message): 
                std::runtime_error(message) {} 
    };

    class LTLfPlusFormula : public Ast {
        public:
            explicit LTLfPlusFormula(AstManager& c) : Ast(c) {}
            virtual ltlf_plus_ptr logical_not() const = 0;
            /**
             * 
             *  \brief return LTLf arg of LTLf+ formula
             *  returns InvalidLTLfPlusInput runtime_error if LTLf+ has no LTLf arg
             */
            virtual ltlf_ptr ltlf_arg() const = 0;
    };

    class LTLfPlusTrue : public LTLfPlusFormula {
        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusTrue;
            explicit LTLfPlusTrue(AstManager& c) : LTLfPlusFormula(c) {
                type_code_ = type_code_id;
            };
            void accept(Visitor &v) const override;
            hash_t compute_hash_() const override;
            virtual vec_ltlf_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_plus_ptr logical_not() const override;
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusFalse : public LTLfPlusFormula {
        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusFalse;
            explicit LTLfPlusFalse(AstManager& c) : LTLfPlusFormula(c) {
                type_code_ = type_code_id;
            };
            void accept(Visitor &v) const override;
            hash_t compute_hash_() const override;
            virtual vec_ltlf_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_plus_ptr logical_not() const override;
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusAnd : public LTLfPlusFormula {
        private:
            const set_ltlf_plus_formulas container_;

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusAnd;
            void accept(Visitor& v) const override;
            explicit LTLfPlusAnd(AstManager& c, const set_ltlf_plus_formulas& s);
            bool is_canonical(const set_ltlf_plus_formulas& container_) const;
            hash_t compute_hash_() const override;
            virtual vec_ltlf_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ltlf_plus_formulas& get_container() const;
            ltlf_plus_ptr logical_not() const override;
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusOr : public LTLfPlusFormula {
        private:
            const set_ltlf_plus_formulas container_;

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusOr;
            void accept(Visitor& v) const override;
            explicit LTLfPlusOr(AstManager& c, const set_ltlf_plus_formulas& s);
            bool is_canonical(const set_ltlf_plus_formulas& container_) const;
            hash_t compute_hash_() const override;
            virtual vec_ltlf_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ltlf_plus_formulas& get_container() const;
            ltlf_plus_ptr logical_not() const override;
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusNot : public LTLfPlusFormula {
        private:
            const ltlf_plus_ptr arg_;

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusNot;
            void accept(Visitor& v) const override;
            explicit LTLfPlusNot(AstManager& c, const ltlf_plus_ptr& s);
            bool is_canonical(const LTLfPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const; // TODO (Gianmarco). Needed?
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ltlf_plus_formulas& get_container() const;
            ltlf_plus_ptr get_arg() const; 
            ltlf_plus_ptr logical_not() const override;
            ltlf_ptr ltlf_arg() const override;

    };

    class LTLfPlusExists : public LTLfPlusFormula {
        private: 
            const ltlf_ptr arg_; // arg of Exists is an LTLf formula

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusExists;
            void accept(Visitor& v) const override;
            explicit LTLfPlusExists(AstManager& c, const ltlf_ptr& in);
            bool is_canonical(const LTLfPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_ptr get_arg() const; // arg of Exists LTLf+ is LTLf formula
            ltlf_plus_ptr logical_not() const; // !E(\phi) = A(!phi)
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusForall : public LTLfPlusFormula {
        private: 
            const ltlf_ptr arg_; // arg of Forall is an LTLf formula

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusForall;
            void accept(Visitor& v) const override;
            explicit LTLfPlusForall(AstManager& c, const ltlf_ptr& in);
            bool is_canonical(const LTLfPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_ptr get_arg() const; // arg of Forall LTLf+ is LTLf formula
            ltlf_plus_ptr logical_not() const; // !A(\phi) = E(!phi)
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusExistsForall : public LTLfPlusFormula {
        private: 
            const ltlf_ptr arg_; // arg of ExistsForall is an LTLf formula

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusExistsForall;
            void accept(Visitor& v) const override;
            explicit LTLfPlusExistsForall(AstManager& c, const ltlf_ptr& in);
            bool is_canonical(const LTLfPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_ptr get_arg() const; // arg of ExistsForall LTLf+ is LTLf formula
            ltlf_plus_ptr logical_not() const; // !EA(\phi) = AE(!\phi)
            ltlf_ptr ltlf_arg() const override;
    };

    class LTLfPlusForallExists : public LTLfPlusFormula {
        private: 
            const ltlf_ptr arg_; // arg of ForallExists is an LTLf formula

        public:
            const static TypeID type_code_id = TypeID::t_LTLfPlusForallExists;
            void accept(Visitor& v) const override;
            explicit LTLfPlusForallExists(AstManager& c, const ltlf_ptr& in);
            bool is_canonical(const LTLfPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ltlf_ptr get_arg() const; // arg of ForallExists LTLf+ is LTLf formula
            ltlf_plus_ptr logical_not() const;
            ltlf_ptr ltlf_arg() const override;
    };
} // namespace whitemech::lydia

