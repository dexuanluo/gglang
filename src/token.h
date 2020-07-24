//
// Created by Dexuan on 2020-07-23.
//
#include <string>
#ifndef GG_LANG_TOKEN_H
#define GG_LANG_TOKEN_H
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
const string TT_ESCAPE("TT_ESCAPE");
const string TT_WS("TT_WS");
const string ENDOFTXT("EOT");
//###################################
const string OP_PLUS("+");
const string OP_MINUS("-");
const string OP_MUL("*");
const string OP_DIV("/");
const string LPAREN("(");
const string RPAREN(")");
const string WS_NEWLINE("\n");
const string ESCAPE("\\");
const string WS_TAB("\t");
const string WS_SPACE(" ");
const string DOT(".");
//###################################
const string NUMBER_NODE("NUMBER_NODE");
const string BINARY_OP_NODE("BINARY_OP_NODE");
const string UNARY_OP_NODE("UNARY_OP_NODE");
const string LEXER_ERR_NODE("LEXER_ERR");
const string PARSER_ERR_NODE("PARSER_ERR");
//###################################
class Token{
public:
    string type;
    string val;
    Token(){}
    Token(const string& type_, string val_){
        type = type_;
        val = val_;
    }
    Token(const string& type_){
        type = type_;
    }

};
#endif //GG_LANG_TOKEN_H