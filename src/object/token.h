//
// Created by Dexuan on 2020-07-23.
//
#include <string>
#include <sstream>
#include <unordered_set>
#ifndef GG_LANG_TOKEN_H
#define GG_LANG_TOKEN_H
using namespace std;
//#########################
//  Tokens
//########################
static const string & GG = *new const string("gg");
static const string & DIGITS = *new const string("0123456789");
static const string & TT_ERR = *new const string("ERROR");
static const string & TT_INT = *new const string("INT");
static const string & TT_FLOAT = *new const string("FLOAT");
static const string & TT_PLUS = *new const string("PLUS");
static const string & TT_MINUS = *new const string("MINUS");
static const string & TT_MUL = *new const string("MUL");
static const string & TT_DIV = *new const string("DIV");
static const string & TT_POW = *new const string("POW");
static const string & TT_SEMICOL = *new const string("SEMICOL");
static const string & TT_LPAREN = *new const string("LPAREN");
static const string & TT_RPAREN = *new const string("RPAREN");
static const string & TT_ESCAPE = *new const string("ESCAPE");
static const string & TT_IDENTIFIER = *new const string("IDENTIFIER");
static const string & TT_KEYWORD = *new const string("KEYWORD");
static const string & TT_EQUAL = *new const string("EQUAL");
static const string & TT_WS = *new const string("WS");
static const string & ENDOFTXT = *new const string("EOT");
//###################################
//        Recognized Syntax
//###################################
static const string & OP_PLUS = *new const string("+");
static const string & OP_MINUS = *new const string("-");
static const string & OP_MUL = *new const string("*");
static const string & OP_DIV = *new const string("/");
static const string & OP_POW = *new const string("^");
static const string & OP_SEMICOL = *new const string(";");
static const string & LPAREN = *new const string("(");
static const string & RPAREN = *new const string(")");
static const string & WS_NEWLINE = *new const string("\n");
static const string & ESCAPE = *new const string("\\");
static const string & WS_TAB = *new const string("\t");
static const string & WS_SPACE = *new const string(" ");
static const string & DOT = *new const string(".");
static const string & UNDERSCORE = *new const string("_");
static const string & EQUAL = *new const string("=");
static const string & VAR = *new const string("var");
static const string & NULLVAR = *new const string("null");
static const string & TRUE = *new const string("true");
static const string & FALSE = *new const string("false");
static const unordered_set<char> & LETTER = *new const unordered_set<char>({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',\
                                                                                    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',\
                                                                                    'S', 'T', 'U', 'V','W', 'X', 'Y','Z', 'a', 'b',\
                                                                                    'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' , 'k', 'l',\
                                                                                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v' ,'w',\
                                                                                    'x', 'y', 'z'});
static const unordered_set<string> & KEYWORD = *new const unordered_set<string>({"var", "gg"});
static const unordered_set<string> & RUNTIMEVAR = *new const unordered_set<string>({"null", "true", "false"});
//###################################
//     Operation Type
//###################################
static const string & NUMBER_NODE = *new const string("NUMBER_NODE");
static const string & BINARY_OP_NODE = *new const string("BINARY_OP_NODE");
static const string & UNARY_OP_NODE = *new const string("UNARY_OP_NODE");
static const string & VARASSIGNMENT_NODE = *new const string("VARASSIGNMENT_NODE");
static const string & VARACCESS_NODE = *new const string("VARACCESS_NODE");
static const string & NO_OP_NODE = *new const string("NO_OP_NODE");
//###################################
//     Error Type
//###################################
static const string & LEXER_ERR_NODE = *new const string("LEXER_ERR");
static const string & PARSER_ERR_NODE = *new const string("PARSER_ERR");
static const string & RUNTIME_ERR_NODE = *new const string("RUNTIME_ERR");
//###################################
static const string & GG_OBJECT_CLASS = *new const string("GG_OBJECT_CLASS");

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
