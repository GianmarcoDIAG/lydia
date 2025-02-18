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

    class InvalidPPLTLPlusInput : public std::runtime_error {
        public:
            explicit InvalidPPLTLPlusInput(const std::string& message): 
                std::runtime_error(message) {} 
    };

    class PPLTLPlusFormula : public Ast {
        public:
            explicit PPLTLPlusFormula(AstManager& c) : Ast(c) {}
            virtual ppltl_plus_ptr logical_not() const = 0;
            /**
             * 
             *  \brief return PPLTL arg of PPLTL+ formula
             *  returns InvalidPPLTLPlusInput runtime_error if PPLTL+ has no PPLTL arg
             */
            virtual ppltl_ptr ppltl_arg() const = 0;
    };

    class PPLTLPlusTrue : public PPLTLPlusFormula {
        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusTrue;
            explicit PPLTLPlusTrue(AstManager& c) : PPLTLPlusFormula(c) {
                type_code_ = type_code_id;
            };
            void accept(Visitor &v) const override;
            hash_t compute_hash_() const override;
            virtual vec_ppltl_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_plus_ptr logical_not() const override;
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusFalse : public PPLTLPlusFormula {
        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusFalse;
            explicit PPLTLPlusFalse(AstManager& c) : PPLTLPlusFormula(c) {
                type_code_ = type_code_id;
            };
            void accept(Visitor &v) const override;
            hash_t compute_hash_() const override;
            virtual vec_ppltl_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_plus_ptr logical_not() const override;
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusAnd : public PPLTLPlusFormula {
        private:
            const set_ppltl_plus_formulas container_;

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusAnd;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusAnd(AstManager& c, const set_ppltl_plus_formulas& s);
            bool is_canonical(const set_ppltl_plus_formulas& container_) const;
            hash_t compute_hash_() const override;
            virtual vec_ppltl_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ppltl_plus_formulas& get_container() const;
            ppltl_plus_ptr logical_not() const override;
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusOr : public PPLTLPlusFormula {
        private:
            const set_ppltl_plus_formulas container_;

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusOr;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusOr(AstManager& c, const set_ppltl_plus_formulas& s);
            bool is_canonical(const set_ppltl_plus_formulas& container_) const;
            hash_t compute_hash_() const override;
            virtual vec_ppltl_plus_formulas get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ppltl_plus_formulas& get_container() const;
            ppltl_plus_ptr logical_not() const override;
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusNot : public PPLTLPlusFormula {
        private:
            const ppltl_plus_ptr arg_;

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusNot;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusNot(AstManager& c, const ppltl_plus_ptr& s);
            bool is_canonical(const PPLTLPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const; // TODO (Gianmarco). Needed?
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            const set_ppltl_plus_formulas& get_container() const;
            ppltl_plus_ptr get_arg() const; 
            ppltl_plus_ptr logical_not() const override;
            ppltl_ptr ppltl_arg() const override;

    };

    class PPLTLPlusExists : public PPLTLPlusFormula {
        private: 
            const ppltl_ptr arg_; // arg of Exists is an PPLTL formula

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusExists;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusExists(AstManager& c, const ppltl_ptr& in);
            bool is_canonical(const PPLTLPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_ptr get_arg() const; // arg of Exists PPLTL+ is PPLTL formula
            ppltl_plus_ptr logical_not() const; // !E(\phi) = A(!phi)
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusForall : public PPLTLPlusFormula {
        private: 
            const ppltl_ptr arg_; // arg of Forall is an PPLTL formula

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusForall;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusForall(AstManager& c, const ppltl_ptr& in);
            bool is_canonical(const PPLTLPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_ptr get_arg() const; // arg of Forall PPLTL+ is PPLTL formula
            ppltl_plus_ptr logical_not() const; // !A(\phi) = E(!phi)
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusExistsForall : public PPLTLPlusFormula {
        private: 
            const ppltl_ptr arg_; // arg of ExistsForall is an PPLTL formula

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusExistsForall;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusExistsForall(AstManager& c, const ppltl_ptr& in);
            bool is_canonical(const PPLTLPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_ptr get_arg() const; // arg of ExistsForall PPLTL+ is PPLTL formula
            ppltl_plus_ptr logical_not() const; // !EA(\phi) = AE(!\phi)
            ppltl_ptr ppltl_arg() const override;
    };

    class PPLTLPlusForallExists : public PPLTLPlusFormula {
        private: 
            const ppltl_ptr arg_; // arg of ForallExists is an PPLTL formula

        public:
            const static TypeID type_code_id = TypeID::t_PPLTLPlusForallExists;
            void accept(Visitor& v) const override;
            explicit PPLTLPlusForallExists(AstManager& c, const ppltl_ptr& in);
            bool is_canonical(const PPLTLPlusFormula& s) const;
            hash_t compute_hash_() const override;
            virtual vec_basic get_args() const;
            bool is_equal(const Basic& o) const override;
            int compare_(const Basic& o) const override;
            ppltl_ptr get_arg() const; // arg of ForallExists PPLTL+ is PPLTL formula
            ppltl_plus_ptr logical_not() const;
            ppltl_ptr ppltl_arg() const override;
    };
} // namespace whitemech::lydia

