//
// Created by Dexuan on 2020-07-21.
//
#include "lexer.h"
#include "../object/node.h"
#ifndef GG_LANG_PARSER_H
#define GG_LANG_PARSER_H


class Parser {

public:
    vector<Token> tokens;
    vector<Token>::iterator cur;
    long int token_idx;

    Parser(vector<Token> tokens_) {
        tokens = tokens_;
        token_idx = 0;
        cur = tokens.begin();
        for (auto i = tokens.begin(); i != tokens.end(); ++i) {
            cout << "[" + i->get_string_val() + ", " + i->type + "]";
        }
        cout << endl;
    }

    void next() {
        if (cur != tokens.end()) {
            ++token_idx;
            ++cur;
        }
    }

    Node *parse() {
        Node *res = scope();
        if (cur != tokens.end()){

            delete res;
            res = nullptr;
            error_check->err_register(new ParserError(Token(TT_ERR, "Unexpected Token: " + cur->type)));
        }
        return res;
    }

    Node *atom(){
        skip_WS();
        Node* res = nullptr;
        if (cur != tokens.end()){
            if (cur->type == TT_FLOAT || cur->type == TT_INT) {
                res = new NumberNode(*cur);
                next();
                return res;
            } else if (cur->type == TT_LPAREN) {
                next();
                res = expression();
                if (cur == tokens.end() || cur->type != TT_RPAREN) {
                    delete res;
                    res = nullptr;
                    error_check->err_register(new ParserError(Token(TT_ERR, "Expecting ')'")));
                }
                next();
                return res;
            }else if (cur->type == TT_IDENTIFIER){
                res = new VarAccessNode(*cur);
                next();
                return res;
            }
        }


        return res;
    }

    Node *power(){
        skip_WS();
        Node* res = atom();
        if (cur != tokens.end() && res != nullptr && cur->type == TT_POW){
            Token token = *cur;
            next();
            return new BinOpNode(res, token, atom());
        }

        return res;
    }

    Node *factor() {
        skip_WS();
        Node* res = power();
        if (cur != tokens.end() && res == nullptr && (cur->type == TT_PLUS || cur->type == TT_MINUS)) {
                Token token = *cur;
                next();
                res = new UnaryOpNode(token, power());
                return res;
        }

        return res;
    }

    Node *term() {
        Node *res = factor();
        skip_WS();
        if (cur != tokens.end() && (cur->type == TT_MUL || cur->type == TT_DIV) ){
            Token token = *cur;
            next();
            res = new BinOpNode(res, token, factor());
        }


        return res;
    }

    Node *expression() {
        Node *res = term();
        skip_WS();
        if (cur != tokens.end() && cur->type == TT_KEYWORD && cur->get_string_val() == VAR){
            next();
            skip_WS();
            if (cur != tokens.end() && cur->type == TT_IDENTIFIER){
                Token token = *cur;
                next();
                skip_WS();
                if (cur != tokens.end() && cur->type == TT_EQUAL){
                    next();
                    skip_WS();
                    Node* expr = expression();

                        if (expr != nullptr){
                            return new VarAssignmentNode(token, expr);
                        }

                    error_check->err_register(new ParserError(Token(TT_ERR, "Expecting a number to be assigned ")));
                }else{
                    error_check->err_register(new ParserError(Token(TT_ERR, "Expecting = ")));
                }
            }else{
                error_check->err_register(new ParserError(Token(TT_ERR, "Expecting an IDENTIFIER ")));
            }
        }




        if (cur != tokens.end() && (cur->type == TT_PLUS || cur->type == TT_MINUS) ){

            Token token = *cur;
            next();
            res = new BinOpNode(res, token, expression());
        }


        if (res == nullptr && cur != tokens.end()){
            if (!error_check->is_error()){

                error_check->err_register(new ParserError(Token(TT_ERR, "Unexpected Token: " + cur->type)));
            }
        }

        return res;
    }

    Node * scope(){
        Node* left = expression();
        skip_WS();

        if (cur != tokens.end()){
            if (cur->type != TT_SEMICOL){
                error_check->err_register(new ParserError(Token(TT_ERR, "Expecting ';' ")));
                return left;

            }else {
                Token token = *cur;
                next();
                skip_WS();
                return new NoOpNode(left, token, scope());
            }
        }
        return new NoOpNode(left, Token(ENDOFTXT), nullptr);


    }
    void skip_WS(){
        while (cur != tokens.end() && (cur->type == TT_WS || cur->type == TT_ESCAPE)) {
            next();
        }
    } // Skipping white space
};


#endif //GG_LANG_PARSER_H
