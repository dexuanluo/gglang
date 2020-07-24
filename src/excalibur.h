//
// Created by Dexuan on 2020-07-23.
//
#include "node.h"
#ifndef GG_LANG_ERROROBSERVER_H
#define GG_LANG_ERROROBSERVER_H
class Error: public Node{
public:
    Error(){}
    virtual void err_msg(){
        cout << node_type + ": " + token.val<< endl;
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
        return error == nullptr;
    }
    void display_msg(){
        if (error != nullptr){
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





#endif //GG_LANG_ERROROBSERVER_H
