//
// Created by Dexuan on 2020-07-23.
//
#include <string>
#include <sstream>
#ifndef GG_LANG_TOKEN_H
#define GG_LANG_TOKEN_H
using namespace std;
//#########################
//  Tokens
//########################
static const string const & GG = *new const string("gg");
static const string const & DIGITS = *new const string("0123456789");
static const string const & TT_ERR = *new const string("ERROR");
static const string const & TT_INT = *new const string("INT");
static const string const & TT_FLOAT = *new const string("FLOAT");
static const string const & TT_PLUS = *new const string("PLUS");
static const string const & TT_MINUS = *new const string("MINUS");
static const string const & TT_MUL = *new const string("MUL");
static const string const & TT_DIV = *new const string("DIV");
static const string const & TT_POW = *new const string("POW");
static const string const & TT_LPAREN = *new const string("LPAREN");
static const string const & TT_RPAREN = *new const string("RPAREN");
static const string const & TT_ESCAPE = *new const string("ESCAPE");
static const string const & TT_WS = *new const string("WS");
static const string const & ENDOFTXT = *new const string("EOT");
//###################################
static const string const & OP_PLUS = *new const string("+");
static const string const & OP_MINUS = *new const string("-");
static const string const & OP_MUL = *new const string("*");
static const string const & OP_DIV = *new const string("/");
static const string const & OP_POW = *new const string("^");
static const string const & LPAREN = *new const string("(");
static const string const & RPAREN = *new const string(")");
static const string const & WS_NEWLINE = *new const string("\n");
static const string const & ESCAPE = *new const string("\\");
static const string const & WS_TAB = *new const string("\t");
static const string const & WS_SPACE = *new const string(" ");
static const string const & DOT = *new const string(".");
//###################################
static const string const & NUMBER_NODE = *new const string("NUMBER_NODE");
static const string const & BINARY_OP_NODE = *new const string("BINARY_OP_NODE");
static const string const & UNARY_OP_NODE = *new const string("UNARY_OP_NODE");
static const string const & LEXER_ERR_NODE = *new const string("LEXER_ERR");
static const string const & PARSER_ERR_NODE = *new const string("PARSER_ERR");
static const string const & RUNTIME_ERR_NODE = *new const string("RUNTIME_ERR");
//###################################
static const string const & GG_OBJECT_CLASS = *new const string("GG_OBJECT_CLASS");

class Token{
public:
    string type;

    Token(){}

    Token(const string& type_, string val_){
        type = type_;
        val = val_;
    }

    Token(const string& type_){
        type = type_;
    }

    string get_string_val(){
        return val;
    }
private:
    string val;
};


template<typename T>
string any_to_str(T val){
    stringstream s;
    s << val;
    return s.str();
}


#endif //GG_LANG_TOKEN_H
