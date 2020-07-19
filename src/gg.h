//
// Created by Dexuan on 2020-07-19.
//
#include <iostream>
#include <string>

#ifndef GG_LANG_GG_H
#define GG_LANG_GG_H
using namespace std;
/*#########################  Tokens    ####################*/

string TT_INT = "TT_INT";
string TT_FLOAT = "TT_FLOAT";
string TT_PLUS = "TT_PLUS";
string TT_MINUS = "MINUS";
string TT_MUL = "MUL";
string TT_DIV = "DIV";
string TT_LPAREN = "LPAREN";
string TT_RPAREN = "RPAREN";


class Token{
    public:
        string type;
        string val;
        token(string type_, string val_){
            type = type_;
            val = val_;
        }

};
/*#########################  Tokens    ####################*/

/*#########################  Lexer    ####################*/
class lexer{
public:
    string& text = nullptr;
    unsigend long int pos = -1;
    string cur_char;

    lexer(string text_){
        text = *new string(text_);
        next();

    }

    ~lexer(){
        delete text;
    }

    next(){
        ++pos;
        if (pos < text.size()){
            cur_char = string(text[pos]);
        }else{
            cur_char = "EOF";
        }

    }
    token_maker(){

    }

};

#endif //GG_LANG_GG_H
