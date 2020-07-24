//
// Created by Dexuan on 2020-07-23.
//
#include "token.h"
#ifndef GG_LANG_NODE_H
#define GG_LANG_NODE_H

class Node{
public:
    Token token;
    Node* left_node;
    Node* right_node;
    Node* node;
    string node_type;

    Node(){}

    Node(Token token_){
        token = token_;
    }

    virtual ~Node(){}

    virtual string dfs(){
        return token.type +": " + token.get_string_val();
    }
};

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


#endif //GG_LANG_NODE_H
