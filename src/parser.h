//
// Created by Dexuan on 2020-07-21.
//
#include "lexer.h"
#include "node.h"
#ifndef GG_LANG_PARSER_H
#define GG_LANG_PARSER_H
class NumberNode: public Node{
public:
    NumberNode(){
        node_type = NUMBER_NODE;
    }
    NumberNode(Token& token_){
        node_type = NUMBER_NODE;
        token = token_;
    }

};

class BinOpNode: public Node{
public:
    Node* left_node;
    Node* right_node;
    BinOpNode(){
        node_type = BINARY_OP_NODE;
    }
    BinOpNode(Node* left, Token token_, Node* right){
        left_node = left;
        token = token_;
        right_node = right;
        node_type = BINARY_OP_NODE;
    };
    ~BinOpNode(){
        if (left_node != nullptr){
            delete left_node;
            left_node = nullptr;
        }
        if (right_node != nullptr){
            delete right_node;
            right_node = nullptr;
        }
    }
    string dfs(){
        string left;
        string right;
        if (left_node != nullptr){
            left = left_node->dfs();
        }
        if (right_node != nullptr){
            right = right_node->dfs();
        }
        return LPAREN + left + ", " + token.type + ", " + right + RPAREN;
    }

};

class UnaryOpNode: public Node {
public:
    Node *node;
    UnaryOpNode() {
        node_type = UNARY_OP_NODE;
    }
    UnaryOpNode(Token token_, Node *node_) {
        node = node_;
        token = token_;
        node_type = UNARY_OP_NODE;
    }

    ~UnaryOpNode() {
        if (node != nullptr) {
            delete node;
            node = nullptr;
        }

    }
    string dfs(){
        return "(" + token.type + " ,"+ node->dfs() + ")" ;
    }
};

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
            cout << "[" + i->val + ", " + i->type + "]";
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

    Node *factor() {
        while (cur != tokens.end() && (cur->type == TT_WS || cur->type == TT_ESCAPE)) {
            next();
        }
        Node* res = nullptr;
        if (cur != tokens.end()) {
            if (cur->type == TT_PLUS || cur->type == TT_MINUS) {
                Token token = *cur;
                next();
                res = new UnaryOpNode(token, factor());
                return res;
            } else if (cur->type == TT_FLOAT || cur->type == TT_INT) {
                Node *res = new NumberNode(*cur);
                next();
                return res;
            } else if (cur->type == TT_LPAREN) {
                next();
                Node *res = expression();
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

    Node *term() {
        Node *left = factor();
        Node *right = nullptr;
        while (cur != tokens.end() &&
               (cur->type == TT_MUL || cur->type == TT_DIV || cur->type == TT_WS || cur->type == TT_ESCAPE)) {
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
};


#endif //GG_LANG_PARSER_H
