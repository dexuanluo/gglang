//
// Created by Dexuan on 2020-07-23.
//
#include "../token.h"
#ifndef GG_LANG_ERROROBSERVER_H
#define GG_LANG_ERROROBSERVER_H
class Error{
public:
    string node_type;
    Token token;
    Error(){}
    virtual void err_msg(){
        cout << node_type + ": " + token.get_string_val() << endl;
    }
};

class LexerError:public Error{
public:

    LexerError(Token token_){
        token = token_;
        node_type = LEXER_ERR_NODE;
    }

};


class ParserError:public Error{
public:

    ParserError(Token token_){
        token = token_;
        node_type = PARSER_ERR_NODE;
    }

};

class RuntimeError: public Error{
public:

    RuntimeError(Token token_){
        token = token_;
        node_type = RUNTIME_ERR_NODE;
    }

};


class Excalibur{
public:

    Excalibur(){}

    void err_register(Error* error_){
        if (error != nullptr){
            delete error;
        }
        error = error_;
    }

    bool is_error(){
        return error != nullptr;
    }

    void display_msg(){
        if (is_error()){
            error->err_msg();
            release_error();
        }else{
            cout << no_err << endl;
        }
    }

    void release_error(){
        delete error;
        error = nullptr;
    }

private:
    Error* error = nullptr;
    string no_err = "No Error Found";
};

//Initializing Singleton Error Checker
static Excalibur * const error_check = new Excalibur();



#endif //GG_LANG_ERROROBSERVER_H
