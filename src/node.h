//
// Created by Dexuan on 2020-07-23.
//
#include "token.h"
#ifndef GG_LANG_NODE_H
#define GG_LANG_NODE_H

class Node{
public:
    Token token;
    string node_type;
    Node(){}
    Node(Token token_){
        token = token_;
    }
    virtual ~Node(){}
    virtual string dfs(){
        return token.type +": " + token.val;
    }
};
#endif //GG_LANG_NODE_H
