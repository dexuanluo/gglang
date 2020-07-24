//
// Created by Dexuan on 2020-07-19.
//
#include <iostream>
#include <string>
#include <vector>
#include "../object/utils/excalibur.h"
#include "../object/token.h"
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
    short int ws_count;
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

    short int handle_WS(vector<Token>* tokens){
        if (cur_char == WS_SPACE || cur_char == WS_TAB || cur_char == WS_NEWLINE){
            if (ws_count == 0){
                tokens->push_back(Token(TT_WS));
                ++ws_count;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_ESCAPE(vector<Token>* tokens){
        if(cur_char == ESCAPE){
            tokens->push_back(Token(TT_ESCAPE));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_DIGIT(vector<Token>* tokens){
        if(is_digit(cur_char, DIGITS)){
            if (ws_count != 0){
                ws_count = 0;
            }
            Token token = number_maker();
            if (token.type != TT_ERR){
                tokens->push_back(token);
                return 1;
            }else{
                error_check->err_register(new LexerError(token));
                return 0;
            }

        }
        return 0;
    }

    short int handle_OP_PLUS(vector<Token>* tokens){
        if(cur_char == OP_PLUS){
            tokens->push_back(Token(TT_PLUS));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_OP_MINUS(vector<Token>* tokens){
        if(cur_char == OP_MINUS){
            tokens->push_back(Token(TT_MINUS));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_OP_MUL(vector<Token>* tokens){
        if(cur_char == OP_MUL){
            tokens->push_back(Token(TT_MUL));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int  handle_OP_DIV(vector<Token>* tokens){
        if(cur_char == OP_DIV){
            tokens->push_back(Token(TT_DIV));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_LPAREN(vector<Token>* tokens){
        if(cur_char == LPAREN){
            tokens->push_back(Token(TT_LPAREN));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    short int handle_RPAREN(vector<Token>* tokens){
        if(cur_char == RPAREN){
            tokens->push_back(Token(TT_RPAREN));
            if (ws_count != 0){
                ws_count = 0;
            }
            next();
            return 1;
        }
        return 0;
    }

    vector<Token>* token_maker(){
        vector<Token>* tokens = new vector<Token>();

        while (pos < text.size()){

            if (handle_WS(tokens)){

            }else if(handle_ESCAPE(tokens)){

            }else if(handle_DIGIT(tokens)){

            }else if(handle_OP_PLUS(tokens)){

            }else if(handle_OP_MINUS(tokens)){

            }else if(handle_OP_MUL(tokens)){

            }else if(handle_OP_DIV(tokens)){

            }else if(handle_LPAREN(tokens)){

            }else if(handle_RPAREN(tokens)){

            }else if(error_check->is_error()){
                delete tokens;
                tokens = nullptr;
                return tokens;
            }else {
                error_check->err_register(new LexerError(Token(TT_ERR, "Meaningless symbol  " + cur_char + "  " + " LOL")));
                delete tokens;
                tokens = nullptr;
                return tokens;
            }

        }
        return tokens;
    }
};





#endif //GG_LANG_GG_H
