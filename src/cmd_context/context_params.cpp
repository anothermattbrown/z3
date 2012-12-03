/*++
Copyright (c) 2011 Microsoft Corporation

Module Name:

    context_params.cpp

Abstract:

    Goodies for managing context parameters in the cmd_context and
    api_context

Author:

    Leonardo (leonardo) 2012-12-01

Notes:

--*/
#include"context_params.h"
#include"gparams.h"
#include"params.h"

context_params::context_params() {
    updt_params();
}

void context_params::set_bool(bool & opt, char const * param, char const * value) {
    if (strcmp(value, "true") == 0) {
        opt = true;
    }
    else if (strcmp(value, "false") == 0) {
        opt = false;
    }
    else {
        throw default_exception("invalid value '%s' for Boolean parameter '%s'", value, param);
    }
}

void context_params::set(char const * param, char const * value) {
    std::string p = param;
    unsigned n = p.size();
    for (unsigned i = 0; i < n; i++) {
        if (p[i] >= 'A' && p[i] <= 'Z')
            p[i] = p[i] - 'A' + 'a';
        else if (p[i] == '-')
            p[i] = '_';
    }
    if (p == "timeout") {
        long val = strtol(value, 0, 10);
        m_timeout = static_cast<unsigned>(val);
    }
    else if (p == "type_check" || p == "well_sorted_check") {
        set_bool(m_well_sorted_check, param, value);
    }
    else if (p == "auto_config") {
        set_bool(m_auto_config, param, value);
    }
    else if (p == "proof") {
        set_bool(m_proof, param, value);
    }
    else if (p == "model") {
        set_bool(m_model, param, value);
    }
    else if (p == "validate_model") {
        set_bool(m_validate_model, param, value);
    }
    else if (p == "trace") {
        set_bool(m_trace, param, value);
    }
    else if (p == "trace_file_name") {
        m_trace_file_name = value;
    }
    else if (p == "unsat_core") {
        set_bool(m_unsat_core, param, value);
    }
    else if (p == "debug_ref_count") {
        set_bool(m_debug_ref_count, param, value);
    }
    else {
        throw default_exception("unknown parameter '%s'", p.c_str());
    }
}

void context_params::updt_params() {
    updt_params(gparams::get());
}

void context_params::updt_params(params_ref const & p) {
    m_timeout           = p.get_uint("timeout", UINT_MAX);
    m_well_sorted_check = p.get_bool("type_check", p.get_bool("well_sorted_check", true));
    m_auto_config       = p.get_bool("auto_config", true);
    m_proof             = p.get_bool("proof", false);
    m_model             = p.get_bool("model", true);
    m_validate_model    = p.get_bool("validate_model", false);
    m_trace             = p.get_bool("trace", false);
    m_trace_file_name   = p.get_str("trace_file_name", "z3.log");
    m_unsat_core        = p.get_bool("unsat_core", false);
    m_debug_ref_count   = p.get_bool("debug_ref_count", false);
}

void context_params::collect_param_descrs(param_descrs & d) {
    d.insert("timeout", CPK_UINT, "default timeout (in milliseconds) used for solvers", "4294967295");
    d.insert("well_sorted_check", CPK_BOOL, "type checker", "true");
    d.insert("type_check", CPK_BOOL, "type checker (alias for well_sorted_check)", "true");
    d.insert("auto_config", CPK_BOOL, "use heuristics to automatically select solver and configure it", "true");
    d.insert("proof", CPK_BOOL, "proof generation, it must be enabled when the Z3 context is created", "false");
    d.insert("model", CPK_BOOL, "model generation for solvers, this parameter can be overwritten when creating a solver", "true");
    d.insert("validate_model", CPK_BOOL, "validate models produced by solvers", "false");
    d.insert("trace", CPK_BOOL, "trace generation for VCC", "false");
    d.insert("trace_file_name", CPK_STRING, "trace out file name (see option 'trace')", "z3.log");
    d.insert("unsat_core", CPK_BOOL, "unsat-core generation for solvers, this parameter can be overwritten when creating a solver, not every solver in Z3 supports unsat core generation", "false");
    d.insert("debug_ref_count", CPK_BOOL, "debug support for AST reference counting", "false");
}