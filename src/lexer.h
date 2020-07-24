//
// Created by Dexuan on 2020-07-19.
//
#include <iostream>
#include <string>
#include <vector>
#include "ErrorObserver.h"
#include "token.h"
#ifndef GG_LANG_GG_H
#define GG_LANG_GG_H
using namespace std;


//#########################
//  Lexer
//########################

//Initializing Singleton Error Checker
Excalibur * const error_check = new Excalibur();


class Lexer{
public:
    string text;
    long int pos = -1;
    string cur_char;
    Lexer(string text_){
        text = text_;
        next();

    }

    ~Lexer(){}

    void next(){
        ++pos;
        if (pos < text.size()){

            cur_char = string({text[pos]});
        }else{
            cur_char = ENDOFTXT;
        }
    }
    bool is_digit(string& cur, const string& digits){

        for (int i = 0; i < digits.size(); ++i){
            if (cur[0] - digits[i] == 0) {
                return true;
            }
        }
        return false;
    }


    Token number_maker(){
        string tmp;
        int dot_count = 0;
        bool isdigit = is_digit(cur_char, DIGITS);
        while (cur_char != ENDOFTXT && (isdigit || cur_char == ESCAPE || cur_char == DOT)){
            if(cur_char == DOT){
                if(dot_count == 1){break;}
                ++dot_count;
                tmp += DOT;
            }else if (isdigit){
                tmp += cur_char;
            }
            next();
            isdigit = is_digit(cur_char, DIGITS);
        }

        if (dot_count == 1){return Token(TT_FLOAT, tmp);}
        return Token(TT_INT, tmp);
    }


    vector<Token>* token_maker(){
        vector<Token>* tokens = new vector<Token>();
        short int ws_count = 0;
        while (cur_char != ENDOFTXT){

            if (cur_char == WS_SPACE || cur_char == WS_TAB || cur_char == WS_NEWLINE){
                if (ws_count == 0){
                    tokens->push_back(Token(TT_WS));
                    ++ws_count;
                }
                next();
            }else if(cur_char == ESCAPE){
                tokens->push_back(Token(TT_ESCAPE));
                ws_count = 0;
                next();
            }else if(is_digit(cur_char, DIGITS)){
                ws_count = 0;
                tokens->push_back(number_maker());
            }else if(cur_char == OP_PLUS){
                tokens->push_back(Token(TT_PLUS));
                ws_count = 0;
                next();
            }else if(cur_char == OP_MINUS){
                tokens->push_back(Token(TT_MINUS));
                ws_count = 0;
                next();
            }else if(cur_char == OP_MUL){
                tokens->push_back(Token(TT_MUL));
                ws_count = 0;
                next();
            }else if(cur_char == OP_DIV){
                tokens->push_back(Token(TT_DIV));
                ws_count = 0;
                next();
            }else if(cur_char == LPAREN){
                tokens->push_back(Token(TT_LPAREN));
                ws_count = 0;
                next();
            }else if(cur_char == RPAREN){
                tokens->push_back(Token(TT_RPAREN));
                ws_count = 0;
                next();
            }else{
                error_check->err_register(new LexerError(Token(TT_ERR, "Meaningless symbol  " + cur_char + "  " + " LOL")));
                delete tokens;
                tokens = nullptr;
                return tokens;
            }
        }
        return tokens;
    }

};

//#########################
//  Run
//########################



#endif //GG_LANG_GG_H
