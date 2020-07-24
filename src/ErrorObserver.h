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
    Error* error = nullptr;
    Excalibur(){}
    void err_register(Error* error_){
        if (error != nullptr){
            delete error;
        }
        error = error_;
    }

    void display_msg(){
        if (error != nullptr){
            error->err_msg();
            delete error;
            error = nullptr;
        }else{
            cout << "No Error Found" << endl;
        }
    }
};





#endif //GG_LANG_ERROROBSERVER_H
