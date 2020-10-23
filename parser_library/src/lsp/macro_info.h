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

#ifndef LSP_MACRO_INFO_H
#define LSP_MACRO_INFO_H

#include "context/macro.h"

namespace hlasm_plugin::parser_library::lsp {

struct variable_symbol_definition
{
    // variable symbol name
    context::id_index name;

    // flag whether is macro parameter
    bool macro_param;

    // type of SET symbol
    context::SET_t_enum type;
    // flag whether SET symbol is global
    bool global;

    // statement number in macro
    size_t def_location;
    position def_position;

    // macro parm constructor
    variable_symbol_definition(context::id_index name, size_t def_location, position def_position)
        : name(name)
        , macro_param(true)
        , def_location(def_location)
        , def_position(def_position)
    {}

    // SET symbol constructor
    variable_symbol_definition(
        context::id_index name, context::SET_t_enum type, bool global, size_t def_location, position def_position)
        : name(name)
        , macro_param(false)
        , type(type)
        , global(global)
        , def_location(def_location)
        , def_position(def_position)
    {}
};

using vardef_storage = std::unordered_map<context::id_index, variable_symbol_definition>;

struct macro_slice_t
{
    size_t begin_statement, end_statement;
    bool inner_macro;

    macro_slice_t(size_t begin_line, bool inner_macro)
        : begin_statement(begin_line)
        , end_statement(begin_line)
        , inner_macro(inner_macro)
    {}
};

struct macro_info
{
    context::macro_def_ptr macro_definition;

    std::vector<variable_symbol_definition> var_definitions;
};

using macro_info_ptr = std::shared_ptr<macro_info>;

} // namespace hlasm_plugin::parser_library::lsp

#endif