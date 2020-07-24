//
// Created by Dexuan on 2020-07-23.
//
#include "parser.h"
#ifndef GG_LANG_EXECUTOR_H
#define GG_LANG_EXECUTOR_H

//#########################################
//    Parsed Tree Executor
//#########################################

class GG_Object{
public:

    virtual GG_Object* added_to(GG_Object* other){
        return other;
    }

    virtual GG_Object* subtracted_by(GG_Object* other){
        return other;
    }

    virtual GG_Object* multiplied_by(GG_Object* other){
        return other;
    }

    virtual GG_Object* divided_by(GG_Object* other){
        return other;
    }

    virtual long int get_int_val(){
        long int i;
        return i;
    }

    virtual string get_type(){
        return "0.0";
    }

    virtual double get_dl_val(){
        return 0.0;
    }

};

class Numeric: public GG_Object{
public:

    Numeric(double dl_val_){
        type = TT_FLOAT;
        dl_val = dl_val_;
    }

    Numeric(long int int_val_){
        type = TT_INT;
        int_val = int_val_;
    }

    Numeric(Node* node){
        type = node->token.type;
        if (node->token.type == TT_INT){
            try {
                int_val = stoi(node->token.get_string_val());
            } catch (const std::exception& e) {
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Integer Overflow at " + node->token.get_string_val())));
            }

        }
        if (node->token.type == TT_FLOAT){
            try {
                dl_val = stod(node->token.get_string_val());
            } catch (const std::exception& e) {
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Floating Point Overflow at " + node->token.get_string_val())));
            }
        }
    }

    long int get_int_val() override{
        return int_val;
    }

    double get_dl_val() override{
        return dl_val;
    }

    string get_type() override{
        return type;
    }

    GG_Object* added_to(GG_Object* other) override {

        if (type == TT_INT && other->get_type() == TT_INT){

            try{

                return new Numeric(this->get_int_val() + other->get_int_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() + other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() + other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() + other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Numeric(0.0);
            }


        }
    }

    GG_Object* subtracted_by(GG_Object* other) override {

        if (type == TT_INT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_int_val() - other->get_int_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() - other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() - other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() - other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Numeric(0.0);
            }


        }
    }

    GG_Object* multiplied_by(GG_Object* other) override{

        if (type == TT_INT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_int_val() * other->get_int_val());

            }catch(const std::exception& e){
                cout << e.what() << endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Multiplication Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() * other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Multiplication Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() * other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Multiplication Caused Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() * other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Multiplication Caused Overflow")));
                return new Numeric(0.0);
            }


        }
    }

    GG_Object* divided_by(GG_Object* other) override{

        if (type == TT_INT && other->get_type() == TT_INT){

            try{
                if (other->get_int_val() == 0){
                    return new Numeric(this->get_int_val() / 0.0);
                }
                return new Numeric(this->get_int_val() / other->get_int_val());


            }catch(const std::exception& e){
                cout << e.what() << endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() / other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() / other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Numeric(0.0);
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() / other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Numeric(0.0);
            }


        }
    }


private:
    long int int_val;
    double dl_val;
    string type;
};



class Executor{

public:
    Node* root;
    Executor(Node* root_){
        root = root_;
    }

    GG_Object* execute(Node* node){

        if (error_check->is_error()){
            return new Numeric(0.0);
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
        error_check->err_register(new RuntimeError(Token(TT_ERR, "No Execution method, execution halted")));
        return new Numeric(0.0);

    }

    GG_Object* visit_number_node(Node* node){

        return new Numeric(node);
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
            return new Numeric(0.0);
        }
        if (node->right_node != nullptr){
            right = execute(node->right_node);
        }else{
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unkown Error NULL Object On The Right Node Of the Parsed Tree")));
            return new Numeric(0.0);
        }

        if (node->token.type == TT_PLUS){
            res = left->added_to(right);
        } else if (node->token.type == TT_MINUS){
            res = left->subtracted_by(right);
        }else if (node->token.type == TT_MUL){
            res = left->multiplied_by(right);
        }else if (node->token.type == TT_DIV){
            res = left->divided_by(right);
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
