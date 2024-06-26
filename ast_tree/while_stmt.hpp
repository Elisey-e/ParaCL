#pragma once

#include "base_ast_node.hpp"
#include "scope_node.hpp"

namespace AST {
    class while_stmt : public base_stmt_node {
        base_expr_node* condition = nullptr;
        scope_node* scope = nullptr;
    public:
        explicit while_stmt(base_expr_node* cond_ = nullptr, scope_node* scope_ = nullptr) : base_stmt_node(base_stmt_node_type::WHILE_STMT),
            condition(cond_), scope(scope_) {}

        base_expr_node* get_condition() const noexcept { return condition; }

        scope_node* get_scope() const noexcept { return scope; }

        virtual ~while_stmt() {}
    };
}
