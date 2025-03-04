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

 #include <lydia/logic/ltlf/duality.hpp>
 #include <lydia/logic/ppltl/duality.hpp>
 #include <lydia/logic/ynf.hpp>

 namespace whitemech::lydia {
    void YNFTransformer::visit(const PPLTLTrue& x) {
        ynf_result = x.ctx().makePPLTLTrue();
      }

    void YNFTransformer::visit(const PPLTLFalse& x) {
        ynf_result = x.ctx().makePPLTLFalse();
    }

    void YNFTransformer::visit(const PPLTLAtom& x) {
        // ynf_result = std::make_shared<PPLTLFormula>(x);
        ynf_result = x.ctx().makePPLTLAtom(x.symbol);
        atoms.insert(ynf_result);
    }

    void YNFTransformer::visit(const PPLTLAnd& x) {
        auto container = x.get_container();
        set_ppltl_formulas new_container;
        for (auto& a : container) new_container.insert(apply(*a));
        ynf_result = x.ctx().makePPLTLAnd(new_container);
    }

    void YNFTransformer::visit(const PPLTLOr& x) {
        auto container = x.get_container();
        set_ppltl_formulas new_container;
        for (auto& a : container) new_container.insert(apply(*a));
        ynf_result = x.ctx().makePPLTLOr(new_container);
    }

    void YNFTransformer::visit(const PPLTLYesterday& x) {
        auto arg = apply(*x.get_arg());
        ynf_result = x.ctx().makePPLTLYesterday(x.get_arg());
        y_sub.insert(ynf_result);
    }

    void YNFTransformer::visit(const PPLTLWeakYesterday& x) {
        auto arg = apply(*x.get_arg());
        ynf_result = x.ctx().makePPLTLWeakYesterday(x.get_arg());
        wy_sub.insert(ynf_result);    
    }

    // YNF(f1 S f2) = YNF(f2) || (YNF(f1) && Y(f1 S f2))
    void YNFTransformer::visit(const PPLTLSince& x) {
        auto arg1 = apply(*x.get_args()[0]); // YNF(f1)
        auto arg2 = apply(*x.get_args()[1]); // YNF(f2)
        auto c = x.get_args(); // {f1, f2}
        auto s = x.ctx().makePPLTLSince(c[0], c[1]); // f1 S f2
        auto yd = x.ctx().makePPLTLYesterday(s); // Y(f1 S f2)
        y_sub.insert(yd);
        auto d = x.ctx().makePPLTLAnd({arg1, yd}); // (YNF(f1) && Y(f1 S f2))
        ynf_result = x.ctx().makePPLTLOr({arg2, d}); // YNF(f2) || (YNF(f1) && Y(f1 S f2))
    }

    // YNF(f1 T f2) = YNF(f1) && (YNF(f1) || WY(f1 T f2))
    void YNFTransformer::visit(const PPLTLTriggered& x) {
        auto arg1 = apply(*x.get_args()[0]); // YNF(f1)
        auto arg2 = apply(*x.get_args()[1]); // YNF(f2)
        auto c = x.get_args(); // {f1, f2}
        auto s = x.ctx().makePPLTLTriggered(c[0], c[1]); // f1 T f2
        auto yd = x.ctx().makePPLTLWeakYesterday(s); // WY(f1 T f2)
        wy_sub.insert(yd);
        auto d = x.ctx().makePPLTLOr({arg1, yd}); // (YNF(f1) || WY(f1 T f2))
        ynf_result = x.ctx().makePPLTLAnd({arg2, d}); // YNF(f1) && (YNF(f1) || WY(f1 T f2))
    }

    // YNF(O f) = YNF(f) || Y(O(f))
    void YNFTransformer::visit(const PPLTLOnce& x) {
        auto arg = apply(*x.get_arg()); // YNF(f)
        auto o = x.ctx().makePPLTLOnce(x.get_arg()); // O(f)
        auto yo = x.ctx().makePPLTLYesterday(o); // Y(O(f))
        y_sub.insert(yo);
        ynf_result = x.ctx().makePPLTLOr({arg, yo}); // YNF(f) || Y(O(f))
    }    

    // YNF(H f) = YNF(f) && WY(H(f))
    void YNFTransformer::visit(const PPLTLHistorically& x) {
        auto arg = apply(*x.get_arg()); // YNF(f)
        auto h = x.ctx().makePPLTLHistorically(x.get_arg()); // H(f)
        auto wyh = x.ctx().makePPLTLWeakYesterday(h); // W(H(f))
        wy_sub.insert(wyh);
        ynf_result = x.ctx().makePPLTLAnd({arg, wyh}); // YNF(f) && WY(H(f))
    }

    // YNF(!f) = !YNF(f)
    void YNFTransformer::visit(const PPLTLNot& x) {
        ynf_result = x.ctx().makePPLTLNot(apply(*x.get_arg()));
    }

    std::unordered_set<ppltl_ptr> YNFTransformer::get_y_sub() const {
        return y_sub;
    }

    std::unordered_set<ppltl_ptr> YNFTransformer::get_wy_sub() const {
        return wy_sub;
    }

    std::unordered_set<ppltl_ptr> YNFTransformer::get_atoms() const {
        return atoms;
    }


    ppltl_ptr YNFTransformer::apply(const PPLTLFormula& b) {
        b.accept(*this);
        return ynf_result;
    }
 }