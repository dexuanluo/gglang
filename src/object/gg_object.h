//
// Created by Dexuan on 2020-07-24.
//
#include "token.h"
#include <unordered_map>
#include <cmath>
#ifndef GG_LANG_GG_OBJECT_H
#define GG_LANG_GG_OBJECT_H

class GG_Object{
public:

    GG_Object(){
        type = GG_OBJECT_CLASS;
    }

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

    virtual GG_Object* power_to(GG_Object* other){
        return other;
    }

    virtual long int get_int_val(){
        long int i;
        return i;
    }

    virtual string get_type(){
        return type;
    }

    virtual double get_dl_val(){
        return 0.0;
    }
private:
    string type;
};

class Undefined: public GG_Object{
public:

    Undefined(){
        type = TT_ERR;
    }

    string get_type() override{
        return type;
    }

private:
    string type;
};

class Numeric: public GG_Object{
public:

    Numeric(GG_Object* copy){
        type = copy->get_type();
        dl_val = copy->get_dl_val();
        int_val = copy->get_int_val();
    }

    Numeric(double dl_val_){
        type = TT_FLOAT;
        dl_val = dl_val_;
    }

    Numeric(long int int_val_){
        type = TT_INT;
        int_val = int_val_;
    }

    Numeric(Token& token){
        type = token.type;
        if (token.type == TT_INT){
            try {
                int_val = stoi(token.get_string_val());
            } catch (const std::exception& e) {
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Integer Overflow at " + token.get_string_val())));
            }

        }
        if (token.type == TT_FLOAT){
            try {
                dl_val = stod(token.get_string_val());
            } catch (const std::exception& e) {
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Floating Point Overflow at " + token.get_string_val())));
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
                return new Undefined();
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() + other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() + other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() + other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Addition Caused Overflow")));
                return new Undefined();
            }


        }
        error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "No defined '+' operation between " + get_type() + " and " + other->get_type())));
        return new Undefined();
    }

    GG_Object* subtracted_by(GG_Object* other) override {

        if (type == TT_INT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_int_val() - other->get_int_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() - other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() - other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() - other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Subtraction Caused Overflow")));
                return new Undefined();
            }


        }
        error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "No defined '-' operation between " + get_type() + " and " + other->get_type())));
        return new Undefined();
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
        error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "No defined '*' operation between " + get_type() + " and " + other->get_type())));
        return new Undefined();
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
                return new Undefined();
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_int_val() / other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(this->get_dl_val() / other->get_dl_val());

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(this->get_dl_val() / other->get_int_val());
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Division by 0 or Number Overflow")));
                return new Undefined();
            }


        }
        error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "No defined '/' operation between " + get_type() + " and " + other->get_type())));
        return new Undefined();
    }

    GG_Object* power_to(GG_Object* other) override{

        if (type == TT_INT && other->get_type() == TT_INT){

            try{

                return new Numeric(pow(this->get_int_val(), other->get_int_val()));


            }catch(const std::exception& e){
                cout << e.what() << endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Power Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_INT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(pow(this->get_int_val(), other->get_dl_val()));

            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Power Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_FLOAT){

            try{
                return new Numeric(pow(this->get_dl_val(), other->get_dl_val()));

            }catch(const std::exception& e){
                cout << e.what() << endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Power Caused Overflow")));
                return new Undefined();
            }


        }else if (type == TT_FLOAT && other->get_type() == TT_INT){

            try{
                return new Numeric(pow(this->get_dl_val(), other->get_int_val()));
            }catch(const std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "Power Caused Overflow")));
                return new Undefined();
            }


        }
        error_check->err_register(new RuntimeError(Token(RUNTIME_ERR_NODE, "No defined '^' operation between " + get_type() + " and " + other->get_type())));
        return new Undefined();
    }


private:
    long int int_val;
    double dl_val;
    string type;
};





#endif //GG_LANG_GG_OBJECT_H
