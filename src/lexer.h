//
// Created by Dexuan on 2020-07-19.
//
#include <iostream>
#include <string>
#include <vector>
#ifndef GG_LANG_GG_H
#define GG_LANG_GG_H
using namespace std;

//#########################
//  Tokens
//########################
string DIGITS = "0123456789";
string TT_ERR = "TT_ERROR";
string TT_INT = "TT_INT";
string TT_FLOAT = "TT_FLOAT";
string TT_PLUS = "TT_PLUS";
string TT_MINUS = "TT_MINUS";
string TT_MUL = "TT_MUL";
string TT_DIV = "TT_DIV";
string TT_LPAREN = "TT_LPAREN";
string TT_RPAREN = "TT_RPAREN";


class Token{
    public:
        string type;
        string val;
        Token(string type_, string val_){
            type = type_;
            val = val_;
        }

};
//#########################
//  Lexer
//########################

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
            cur_char = "EOT";
        }
    }
    bool is_digit(string& cur, string& digits){
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
        while (cur_char != "EOT" && (is_digit(cur_char, DIGITS) || cur_char == ".")){
            if(cur_char == "."){
                if(dot_count == 1){break;}
                ++dot_count;
                tmp += ".";
            }else{
                tmp += cur_char;
            }
            next();
        }
        if (dot_count == 1){return Token(TT_FLOAT, tmp);}
        return Token(TT_INT, tmp);
    }

    vector<Token> token_maker(){
        vector<Token> tokens;
        while (cur_char != "EOT"){
            if (cur_char == " " || cur_char == "\t" || cur_char == "\n" || cur_char == "\\" || cur_char == "\a"){
                next();
            }else if(is_digit(cur_char, DIGITS)){
                tokens.push_back(number_maker());
            }else if(cur_char == "+"){
                tokens.push_back(Token(TT_PLUS, "+"));
                next();
            }else if(cur_char == "-"){
                tokens.push_back(Token(TT_MINUS, "-"));
                next();
            }else if(cur_char == "*"){
                tokens.push_back(Token(TT_MUL, "*"));
                next();
            }else if(cur_char == "/"){
                tokens.push_back(Token(TT_DIV, "/"));
                next();
            }else if(cur_char == "("){
                tokens.push_back(Token(TT_LPAREN, "("));
                next();
            }else if(cur_char == ")"){
                tokens.push_back(Token(TT_RPAREN, ")"));
                next();
            }else{
                string err_msg = "DO NOT PUT MEANINGLESS THINGS LIKE  " + cur_char + "  " + " LOL";
                return vector<Token>({Token(TT_ERR, err_msg)});
            }
        }
        return tokens;
    }

};

//#########################
//  Run
//########################


vector<Token> run(string text){
    Lexer lexer(text);
    return lexer.token_maker();
}
#endif //GG_LANG_GG_H
