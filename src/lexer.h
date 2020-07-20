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
const string GG("gg");
const string DIGITS("0123456789");
const string TT_ERR("TT_ERROR");
const string TT_INT("TT_INT");
const string TT_FLOAT("TT_FLOAT");
const string TT_PLUS("TT_PLUS");
const string TT_MINUS("TT_MINUS");
const string TT_MUL("TT_MUL");
const string TT_DIV ("TT_DIV");
const string TT_LPAREN("TT_LPAREN");
const string TT_RPAREN("TT_RPAREN");
const string ENDOFTXT("EOT");
const string OP_PLUS("+");
const string OP_MINUS("-");
const string OP_MUL("*");
const string OP_DIV("/");
const string LPAREN("(");
const string RPAREN(")");
const string WS_NEWLINE("\n");
const string WS_ESCAPE("\\");
const string WS_TAB("\t");
const string WS_SPACE(" ");
const string DOT(".");


class Token{
    public:
        string type;
        string val;
        Token(const string& type_, string val_){
            type = type_;
            val = val_;
        }
        Token(const string& type_){
            type = type_;
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
        while (cur_char != ENDOFTXT && (is_digit(cur_char, DIGITS) ||\
        cur_char == DOT || cur_char == WS_TAB|| cur_char == WS_ESCAPE || cur_char == WS_NEWLINE || cur_char == WS_SPACE)){
            if(cur_char == "."){
                if(dot_count == 1){break;}
                ++dot_count;
                tmp += DOT;
            }else if (is_digit(cur_char, DIGITS)){
                tmp += cur_char;
            }
            next();
        }
        if (dot_count == 1){return Token(TT_FLOAT, tmp);}
        return Token(TT_INT, tmp);
    }

    vector<Token> token_maker(){
        vector<Token> tokens;
        while (cur_char != ENDOFTXT){
            if (cur_char == WS_SPACE || cur_char == WS_TAB || cur_char == WS_NEWLINE || cur_char == WS_ESCAPE){
                next();
            }else if(is_digit(cur_char, DIGITS)){
                tokens.push_back(number_maker());
            }else if(cur_char == OP_PLUS){
                tokens.push_back(Token(TT_PLUS));
                next();
            }else if(cur_char == OP_MINUS){
                tokens.push_back(Token(TT_MINUS));
                next();
            }else if(cur_char == OP_MUL){
                tokens.push_back(Token(TT_MUL));
                next();
            }else if(cur_char == OP_DIV){
                tokens.push_back(Token(TT_DIV));
                next();
            }else if(cur_char == LPAREN){
                tokens.push_back(Token(TT_LPAREN));
                next();
            }else if(cur_char == RPAREN){
                tokens.push_back(Token(TT_RPAREN));
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


vector<Token> run(string& text){
    Lexer lexer(text);
    return lexer.token_maker();
}
#endif //GG_LANG_GG_H
