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

#include <lydia/logic/ldlf/base.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ltlfplus/base.hpp>
#include <lydia/logic/ppltlplus/base.hpp>
#include <lydia/logic/pl/base.hpp>
#include <lydia/visitor.hpp>

namespace whitemech::lydia {
void Symbol::accept(Visitor& v) const { v.visit(*this); }

void LTLfTrue::accept(Visitor& v) const { v.visit(*this); }
void LTLfFalse::accept(Visitor& v) const { v.visit(*this); }
void LTLfOr::accept(Visitor& v) const { v.visit(*this); }
void LTLfAnd::accept(Visitor& v) const { v.visit(*this); }
void LTLfAtom::accept(Visitor& v) const { v.visit(*this); }
void LTLfNot::accept(Visitor& v) const { v.visit(*this); }
void LTLfNext::accept(Visitor& v) const { v.visit(*this); }
void LTLfWeakNext::accept(Visitor& v) const { v.visit(*this); }
void LTLfUntil::accept(Visitor& v) const { v.visit(*this); }
void LTLfRelease::accept(Visitor& v) const { v.visit(*this); }
void LTLfEventually::accept(Visitor& v) const { v.visit(*this); }
void LTLfAlways::accept(Visitor& v) const { v.visit(*this); }

void PPLTLTrue::accept(Visitor& v) const { v.visit(*this); }
void PPLTLFalse::accept(Visitor& v) const { v.visit(*this); }
void PPLTLOr::accept(Visitor& v) const { v.visit(*this); }
void PPLTLAnd::accept(Visitor& v) const { v.visit(*this); }
void PPLTLAtom::accept(Visitor& v) const { v.visit(*this); }
void PPLTLNot::accept(Visitor& v) const { v.visit(*this); }
void PPLTLYesterday::accept(Visitor& v) const { v.visit(*this); }
void PPLTLWeakYesterday::accept(Visitor& v) const { v.visit(*this); }
void PPLTLSince::accept(Visitor& v) const { v.visit(*this); }
void PPLTLTriggered::accept(Visitor& v) const { v.visit(*this); }
void PPLTLOnce::accept(Visitor& v) const { v.visit(*this); }
void PPLTLHistorically::accept(Visitor& v) const { v.visit(*this); }

void LDLfTrue::accept(Visitor& v) const { v.visit(*this); }
void LDLfFalse::accept(Visitor& v) const { v.visit(*this); }
void LDLfOr::accept(Visitor& v) const { v.visit(*this); }
void LDLfAnd::accept(Visitor& v) const { v.visit(*this); }
void LDLfNot::accept(Visitor& v) const { v.visit(*this); }
void LDLfDiamond::accept(Visitor& v) const { v.visit(*this); }
void LDLfBox::accept(Visitor& v) const { v.visit(*this); }

void PropositionalRegExp::accept(Visitor& v) const { v.visit(*this); }
void TestRegExp::accept(Visitor& v) const { v.visit(*this); }
void UnionRegExp::accept(Visitor& v) const { v.visit(*this); }
void SequenceRegExp::accept(Visitor& v) const { v.visit(*this); }
void StarRegExp::accept(Visitor& v) const { v.visit(*this); }

void LTLfPlusTrue::accept(Visitor& v) const { v.visit(*this); }
void LTLfPlusFalse::accept(Visitor& v) const { v.visit(*this); }
void LTLfPlusAnd::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusOr::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusNot::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusExists::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusForall::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusExistsForall::accept(Visitor& v) const {v.visit(*this); }
void LTLfPlusForallExists::accept(Visitor& v) const {v.visit(*this); }

void PPLTLPlusTrue::accept(Visitor& v) const { v.visit(*this); }
void PPLTLPlusFalse::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusAnd::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusOr::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusNot::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusExists::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusForall::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusExistsForall::accept(Visitor &v) const { v.visit(*this); }
void PPLTLPlusForallExists::accept(Visitor &v) const { v.visit(*this); }

// TODO add other accept methods

void PropositionalTrue::accept(Visitor& v) const { v.visit(*this); }

void PropositionalFalse::accept(Visitor& v) const { v.visit(*this); }
void PropositionalAtom::accept(Visitor& v) const { v.visit(*this); }

void PropositionalAnd::accept(Visitor& v) const { v.visit(*this); }
void PropositionalOr::accept(Visitor& v) const { v.visit(*this); }
void PropositionalNot::accept(Visitor& v) const { v.visit(*this); }

void LDLfF::accept(Visitor& v) const { v.visit(*this); }
void LDLfT::accept(Visitor& v) const { v.visit(*this); }
void LDLfQ::accept(Visitor& v) const { v.visit(*this); }
void QuotedFormula::accept(Visitor& v) const { v.visit(*this); }

} // namespace whitemech::lydia
