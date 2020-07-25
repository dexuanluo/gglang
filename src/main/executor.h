//
// Created by Dexuan on 2020-07-23.
//
#include "parser.h"
#include "gg_object.h"
#include "gg_memory.h"
#ifndef GG_LANG_EXECUTOR_H
#define GG_LANG_EXECUTOR_H
using namespace std;
//#########################################
//    Parsed Tree Executor
//#########################################

static Cache * const root_table = new Cache();

class Executor{

public:
    Node* root;

    Executor(Node* root_){
        root = root_;
    }

    GG_Object* execute(Node* node){

        if (error_check->is_error()){
            return new Undefined();
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

        error_check->err_register(new RuntimeError(Token(TT_ERR, "No Execution method, execution halted")));
        return new Undefined();

    }

    GG_Object* visit_var_access_node(Node* node){
        GG_Object* res = root_table->get(node->token.get_string_val());
        if (res->get_type() == TT_ERR){
            error_check->err_register(new RuntimeError(Token(TT_ERR, node->token.get_string_val() + " is not defined")));
        }
        return res;
    }

    GG_Object* visit_var_assignment_node(Node* node){
        GG_Object* to_assign = execute(node->node);
        root_table->set(node->token.get_string_val(), to_assign);
        return new Undefined();
    }

    GG_Object* visit_number_node(Node* node){

        return new Numeric(node->token);
    }

    GG_Object* visit_unary_op_node(Node* node){
        GG_Object* res = execute(node->node);
        if (node->token.type == TT_MINUS){
            long int i = -1;
            GG_Object* tmp = new Numeric(i);
            GG_Object* tmp2 = res->multiplied_by(tmp);
            delete res;
            delete tmp;
            return tmp2;
        }
        return res;
    }

    GG_Object* visit_binary_op_node(Node* node){
        GG_Object* left = nullptr;
        GG_Object* right = nullptr;
        GG_Object* res = nullptr;
        if (node->left_node != nullptr){
            left = execute(node->left_node);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unkown Error NULL Object On The Left Node Of the Parsed Tree")));
            return new Undefined();
        }
        if (node->right_node != nullptr){
            right = execute(node->right_node);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unkown Error NULL Object On The Right Node Of the Parsed Tree")));
            return new Undefined();
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

        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
        return res;
    }
};


#endif //GG_LANG_EXECUTOR_H
