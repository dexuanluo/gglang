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
        Node *res = expression();
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
            }
        }

        error_check->err_register(new ParserError(Token(TT_ERR, "Unexpected Token: " + cur->type)));
        return res;
    }

    Node *power(){
        skip_WS();
        Node* left = atom();
        if (cur != tokens.end() && cur->type == TT_POW){
            Token token = *cur;
            next();
            Node* right = atom();
            return new BinOpNode(left, token, right);
        }

        return left;
    }

    Node *factor() {
        skip_WS();
        Node* res = nullptr;
        if (cur != tokens.end()) {
            if(cur->type == TT_INT || cur->type == TT_FLOAT){
                res = power();
                return res;
            }else if (cur->type == TT_PLUS || cur->type == TT_MINUS) {
                Token token = *cur;
                next();
                res = new UnaryOpNode(token, power());
                return res;
            }
        }
        error_check->err_register(new ParserError(Token(TT_ERR, "Unexpected Token: " + cur->type)));
        return res;
    }

    Node *term() {
        Node *left = factor();
        Node *right = nullptr;
        while (cur != tokens.end() &&
               (cur->type == TT_MUL || cur->type == TT_DIV ||\
               cur->type == TT_WS || cur->type == TT_ESCAPE)) {
            if (cur->type == TT_WS || cur->type == TT_ESCAPE) {
                next();
            } else {
                Token token = *cur;
                next();
                right = factor();
                left = new BinOpNode(left, token, right);
            }

        }
        return left;
    }

    Node *expression() {
        Node *left = term();
        Node *right = nullptr;
        while (cur != tokens.end() && (cur->type == TT_PLUS || cur->type == TT_MINUS || \
                cur->type == TT_WS || cur->type == TT_ESCAPE)) {
            if (cur->type == TT_WS || cur->type == TT_ESCAPE) {
                next();
            } else {
                Token token = *cur;
                next();
                right = term();
                left = new BinOpNode(left, token, right);
            }
        }
        return left;
    }

    void skip_WS(){
        while (cur != tokens.end() && (cur->type == TT_WS || cur->type == TT_ESCAPE)) {
            next();
        }
    } // Skipping white space
};


#endif //GG_LANG_PARSER_H
