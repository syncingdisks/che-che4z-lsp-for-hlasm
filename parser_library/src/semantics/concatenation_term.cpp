/*
 * Copyright (c) 2019 Broadcom.
 * The term "Broadcom" refers to Broadcom Inc. and/or its subsidiaries.
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Broadcom, Inc. - initial API and implementation
 */

#include "concatenation_term.h"

namespace hlasm_plugin {
namespace parser_library {
namespace semantics {

char_str_conc::char_str_conc(std::string value)
    : concatenation_point(concat_type::STR)
    , value(std::move(value))
{ }

std::string char_str_conc::evaluate(expressions::evaluation_context&) const { return value; }

var_sym_conc::var_sym_conc(vs_ptr symbol)
    : concatenation_point(concat_type::VAR)
    , symbol(std::move(symbol))
{ }

std::string var_sym_conc::evaluate(expressions::evaluation_context& eval_ctx) const
{
    auto value = symbol->evaluate(eval_ctx);

    switch (value.type)
    {
        case context::SET_t_enum::A_TYPE:
            return std::to_string(std::abs(value.access_a()));
        case context::SET_t_enum::B_TYPE:
            return value.access_b() ? "1" : "0";
        case context::SET_t_enum::C_TYPE:
            return std::move(value.access_c());
        default:
            assert(false);
            return "";
    }
}

dot_conc::dot_conc()
    : concatenation_point(concat_type::DOT)
{ }

std::string dot_conc::evaluate(expressions::evaluation_context&) const { return "."; }

equals_conc::equals_conc()
    : concatenation_point(concat_type::EQU)
{ }

std::string equals_conc::evaluate(expressions::evaluation_context&) const { return "="; }

sublist_conc::sublist_conc(std::vector<concat_chain> list)
    : concatenation_point(concat_type::SUB)
    , list(std::move(list))
{ }

std::string sublist_conc::evaluate(expressions::evaluation_context& eval_ctx) const
{
    std::string ret;
    for (const auto& chain : list)
        ret.append(concatenation_point::evaluate(chain, eval_ctx));
    return ret;
}

} // namespace semantics
} // namespace parser_library
} // namespace hlasm_plugin