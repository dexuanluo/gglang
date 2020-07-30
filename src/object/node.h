//
// Created by Dexuan on 2020-07-23.
//

#include "token.h"
#include <memory>
#ifndef GG_LANG_NODE_H
#define GG_LANG_NODE_H

//#########################
//  Abstract Syntax Tree
//########################

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

    string dfs() override {
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

    string dfs() override {
        return "(" + token.type + " ,"+ node->dfs() + ")" ;
    }
};

class VarAssignmentNode: public Node{
public:
    VarAssignmentNode(Token token_, Node* val_){
        node_type = VARASSIGNMENT_NODE;
        token = token_;
        node = val_;
    }

    string dfs() override {
        return "(" + token.type + " ,"+ node->dfs() + ")" ;
    }
    ~VarAssignmentNode(){
        if (node != nullptr){
            delete node;
        }
    }



    
};

class VarAccessNode: public Node{
public:

    VarAccessNode(Token token_){
        node_type = VARACCESS_NODE;
        token = token_;
    }

    string dfs() override {
        return "(" + token.type + " ," + token.get_string_val() + ")" ;
    }


};

class ComparisionNode: public Node{
public:
    ComparisionNode(){
        node_type = COMPARISION_NODE;
    }

    ComparisionNode(Node* left, Token token_, Node* right){
        left_node = left;
        token = token_;
        right_node = right;
        node_type = COMPARISION_NODE;
    };

    ~ComparisionNode(){

        if (left_node != nullptr){
            delete left_node;
            left_node = nullptr;
        }
        if (right_node != nullptr){
            delete right_node;
            right_node = nullptr;
        }
    }

    string dfs() override {
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


class NoOpNode: public Node{
public:

    NoOpNode(Node* left, Token token_, Node* right){
        node_type =NO_OP_NODE;
        left_node = left;
        right_node= right;
        token = token_;

    }

    ~NoOpNode(){

        if (left_node != nullptr){
            delete left_node;
            left_node = nullptr;
        }
        if (right_node != nullptr){
            delete right_node;
            right_node = nullptr;
        }
    }

    string dfs() override {
        string left;
        string right;
        if (left_node != nullptr){
            left = left_node->dfs();
        }
        if (right_node != nullptr){
            right = right_node->dfs();
        }
        return "(" + left + "," + token.type + " ,"+ right + ")" ;
    }
};

#endif //GG_LANG_NODE_H
