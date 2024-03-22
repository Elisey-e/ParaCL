#pragma once

#include "ast_nodes_include.hpp"
#include <iostream>
#include <exception>

namespace AST {
    class Visitor final{
        VAL_TYPE curr_value = 0;
        astree* tree_;
    public:

        VAL_TYPE eval(base_expr_node * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_expr_type())
            {
            case base_expr_node_type::ASSIGNMENT:{
                // #ifdef DEBUG_
                // std::cout << "1\n";
                // #endif
                assignment_expr * A = static_cast<assignment_expr*>(X);
                return eval(A);
                break;}
            case base_expr_node_type::BINARY_EXPR:{
                // #ifdef DEBUG_
                // std::cout << "2\n";
                // #endif
                binary_expr * B = static_cast<binary_expr*>(X);
                return eval(B, B->get_bin_type());
                break;}
            case base_expr_node_type::NUMBER_EXPR:{
                // #ifdef DEBUG_
                // std::cout << "3\n";
                // #ifdef DEBUG_
                number_expr * C = static_cast<number_expr*>(X);
                return eval(C);
                break;}
            case base_expr_node_type::UNARY_EXPR:{
                // #ifdef DEBUG_
                // std::cout << "4\n";
                // #endif
                unary_expr * D = static_cast<unary_expr*>(X);
                return eval(D, D->get_un_type());
                break;}
            case base_expr_node_type::VAR_EXPR:{
                // #ifdef DEBUG_
                // std::cout << "5\n";
                // #endif
                variable_expr * E = static_cast<variable_expr*>(X);
                return eval(E);
                break;}
            case base_expr_node_type::READ_EXPR:{
                // #ifdef DEBUG_
                // std::cout << "6\n";
                // #endif
                read_expr * F = static_cast<read_expr*>(X);
                return eval(F);
                break;}
            case base_expr_node_type::PRINT_NODE:{
                // #ifdef DEBUG_
                // std::cout << "7\n";
                // #endif
                print_stmt * G = static_cast<print_stmt*>(X);
                return eval(G);
                break;}
            default:{
                // #ifdef DEBUG_
                // std::cout << "BADBADBAD\n";
                // #endif
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(binary_expr* X, binary_oper t){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (t)
            {
            case binary_oper::BINARY_ADD:
                return eval(X->get_lhs()) + eval(X->get_rhs());
                break;
            case binary_oper::BINARY_SUB:
                return eval(X->get_lhs()) - eval(X->get_rhs());
                break;
            case binary_oper::BINARY_MUL:
                return eval(X->get_lhs()) * eval(X->get_rhs());
                break;
            case binary_oper::BINARY_DIV:
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                else {return eval(X->get_lhs()) / eval(X->get_rhs());}
                break;
            case binary_oper::BINARY_MOD:
                if (eval(X->get_rhs()) == 0){
                    throw std::runtime_error("Division by zero!");
                }
                else {return eval(X->get_lhs()) % eval(X->get_rhs());}
                break;
            case binary_oper::BINARY_EQU:
                return eval(X->get_lhs()) == eval(X->get_rhs());
                break;
            case binary_oper::BINARY_NEQU:
                return eval(X->get_lhs()) != eval(X->get_rhs());
                break;
            case binary_oper::BINARY_GREATER:
                return eval(X->get_lhs()) > eval(X->get_rhs());
                break;
            case binary_oper::BINARY_LESS:
                return eval(X->get_lhs()) < eval(X->get_rhs());
                break;
            case binary_oper::BINARY_GREATER_EQU:
                return eval(X->get_lhs()) >= eval(X->get_rhs());
                break;
            case binary_oper::BINARY_LESS_EQU:
                return eval(X->get_lhs()) <= eval(X->get_rhs());
                break;
            case binary_oper::BINARY_OR:
                return eval(X->get_lhs()) || eval(X->get_rhs());
                break;
            case binary_oper::BINARY_AND:
                return eval(X->get_lhs()) && eval(X->get_rhs());
                break;
            default:{
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(unary_expr* X, unary_oper t){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (t)
            {
            case unary_oper::UNARY_MINUS:
                return -eval(X->get_rhs());
                break;
            case unary_oper::UNARY_NOT:
                return -eval(X->get_rhs());
                break;
            case unary_oper::UNARY_PLUS:
                return eval(X->get_rhs());
                break;
            //...
            default:{
                return 0;
                break;}
            }
        }

        VAL_TYPE eval(print_stmt* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = eval(X->out_());
            OBUF << res << '\n';
            return res;
        }

        VAL_TYPE eval(number_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = X->get_value();
            return res;
        }

        VAL_TYPE eval(assignment_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE res = eval(X->get_rhs());
            X->define(res);
            // for (auto i : *(X->get_lhs())){
            //     i->set_value(res);
            //     (i->get_scope())->set(i->name(), res);
            //     (i->get_scope())->declare(i->name());
            // }
            return res;
        }

        VAL_TYPE eval(variable_expr* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            auto var_scope = X->get_scope();
            auto var_value = var_scope->get_var_value(var->name());
            return var_value;
            // scope_node* proc_scope = X->get_scope();
            // scope_node* var_scope = nullptr;
            // if ((var_scope = (proc_scope->find_var(X->name()))) != nullptr){
            //     return var_scope->get_var_value(X->name());
            // }
            // VAL_TYPE res = X->get_value();
            // X->set_value(res);
        }

        VAL_TYPE eval(base_ast_node * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_ast_type())
            {
            case base_ast_node_type::EXPR:{
                base_expr_node * A = static_cast<base_expr_node*>(X);
                return eval(A);
                break;}
            case base_ast_node_type::STMT:{
                base_stmt_node * B = static_cast<base_stmt_node*>(X);
                return eval(B);
                break;}
            default:{
                return 0;
                break;}
            }
        }

        int eval(scope_node* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            for (auto i : *(X->get_container())){
                eval(i);
            }
            return 0;
        }

        VAL_TYPE eval(base_stmt_node* X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            switch (X->get_expr_type())
            {
            case base_stmt_node_type::IF_STMT:{
                if_stmt * A = static_cast<if_stmt*>(X);
                return eval(A);
                break;}
            case base_stmt_node_type::WHILE_STMT:{
                while_stmt * B = static_cast<while_stmt*>(X);
                return eval(B);
                break;}
            default:{
                return 0;
                break;}
            }
        }

        int eval(if_stmt* X){                       // return value изменить при анализе исключений
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            if (eval(X->get_condition())){
                eval(X->get_true_scope());
            }
            else{
                eval(X->get_else_scope());
            }
            return 0;
        }

        int eval(while_stmt* X){                       // return value изменить при анализе исключений
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            while (eval(X->get_condition())){
                eval(X->get_scope());
            }
            return 0;
        }

        VAL_TYPE eval(read_expr * X){
            if (X == nullptr){
                throw std::runtime_error("nullptr_node_arg");
            }
            VAL_TYPE inp;
            IBUF >> inp;
            X->set_input(inp);
            return inp;
        }
    };
}
