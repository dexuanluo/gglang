//
// Created by Dexuan on 2020-07-23.
//
#include "parser.h"
#include "gg_object.h"
#include "gg_memory.h"
#include "../utils/avalon.h"
#ifndef GG_LANG_EXECUTOR_H
#define GG_LANG_EXECUTOR_H
using namespace std;
//#########################################
//    Parsed Tree Executor
//#########################################

// A global table that store runtime variable like true, false and null.
static Cache * const root_table = new Cache("set_as_root");

static Cache * const main_table = new Cache(root_table);

class Executor{

public:
    Node* root;

    Executor(Node* root_){
        root = root_;
    }

    shared_ptr<GG_Object> execute(Node* node){
        if (node == nullptr){
            return root_table->get(NULLVAR);
        }

        if (error_check->is_error()){
            return root_table->get(NULLVAR);
        }
        if (node->node_type == NUMBER_NODE){
            return visit_number_node(node);
        }
        if (node->node_type == BINARY_OP_NODE){
            return visit_binary_op_node(node);
        }
        if (node->node_type == UNARY_OP_NODE){
            return visit_unary_op_node(node);
        }
        if (node->node_type == VARACCESS_NODE){

            return visit_var_access_node(node);
        }
        if (node->node_type == VARASSIGNMENT_NODE){
            return visit_var_assignment_node(node);
        }
        if (node->node_type == NO_OP_NODE){
            return visit_no_op_node(node);
        }
        error_check->err_register(new RuntimeError(Token(TT_ERR, "No Execution method, execution halted")));
        return root_table->get(NULLVAR);

    }

    shared_ptr<GG_Object> visit_var_access_node(Node* node){
        auto res = main_table->get(node->token.get_string_val());
        if (res->get_type() == TT_ERR){
            error_check->err_register(new RuntimeError(Token(TT_ERR, node->token.get_string_val() + " is not defined")));
        }
        return res;
    }

    shared_ptr<GG_Object> visit_var_assignment_node(Node* node){
        auto to_assign = execute(node->node);

        if (to_assign->get_type() != TT_ERR){
            to_assign->not_tmp();
            main_table->set(node->token.get_string_val(), to_assign);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Cannot assign ERROR type")));
            return to_assign;
        }

        return root_table->get(NULLVAR);
    }

    shared_ptr<GG_Object> visit_number_node(Node* node){


        return make_shared<Numeric>(Numeric(node->token));
    }

    shared_ptr<GG_Object> visit_unary_op_node(Node* node){
        auto res = execute(node->node);
        if (node->token.type == TT_MINUS){
            long int i = -1;
            auto tmp = make_shared<Numeric>(Numeric(i));
            auto tmp2 = res->multiplied_by(tmp);
//            gc->garbage_register(res);
//            gc->garbage_register(tmp);
//            gc->garbage_register(tmp2);
            return tmp2;
        }
        return res;
    }

    shared_ptr<GG_Object> visit_binary_op_node(Node* node){
        shared_ptr<GG_Object> left;
        shared_ptr<GG_Object> right;
        shared_ptr<GG_Object> res;
        if (node->left_node != nullptr){
            left = execute(node->left_node);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unkown Error NULL Object On The Left Node Of the Parsed Tree")));
            return root_table->get(NULLVAR);
        }
        if (node->right_node != nullptr){
            right = execute(node->right_node);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unkown Error NULL Object On The Right Node Of the Parsed Tree")));
            return root_table->get(NULLVAR);
        }

        if (node->token.type == TT_PLUS){
            res = left->added_to(right);
        } else if (node->token.type == TT_MINUS){
            res = left->subtracted_by(right);
        }else if (node->token.type == TT_MUL){
            res = left->multiplied_by(right);
        }else if (node->token.type == TT_DIV){
            res = left->divided_by(right);
        }else if (node->token.type == TT_POW){
            res = left->power_to(right);
        }
        if (res == nullptr){
            error_check->err_register(new RuntimeError(Token(TT_ERR, "No " + node->token.type + " operation is defined for " + left->get_type() + " and " + right->get_type())));
        }
//        gc->garbage_register(left);
//        gc->garbage_register(right);
        return res;
    }

    shared_ptr<GG_Object> visit_no_op_node(Node* node){
        auto left = execute(node->left_node);
        auto right = execute(node->right_node);
        if (right->get_type() != TT_ERR){
//            if (left != nullptr){
//                gc->garbage_register(left);
//            }

            return right;
        }
        return left;


    }
};


#endif //GG_LANG_EXECUTOR_H
