//
// Created by Dexuan on 2020-07-25.
//
#include "object/gg_object.h"
#ifndef GG_LANG_GG_MEMORY_H
#define GG_LANG_GG_MEMORY_H
class Cache{
public:

    Cache(){
        unordered_map<string, GG_Object*> table;
        parent = nullptr;
    }

    Cache(Cache* parent_){
        unordered_map<string, GG_Object*> table;
        parent = parent_;
    }

    GG_Object* get(string key){
        auto iter = table.find(key);
        if ( iter != table.end()){
            if (iter->second->get_type() == TT_INT || iter->second->get_type() == TT_FLOAT){
                return new Numeric(iter->second);
            }
            return new Undefined();
        }else if(parent != nullptr){
            return parent->get(key);
        }
        return new Undefined();
    }

    void set(string key, GG_Object* val){
        try{
            table[key] = val;
        }catch(std::exception& e){
            cout << e.what() <<endl;
            error_check->err_register(new RuntimeError(Token(TT_ERR, "Unknown: Failed to Change Variable Value")));
        }

    }

    bool del(string key){
        auto iter = table.find(key);
        if ( iter != table.end()){
            delete iter->second;
            iter->second = nullptr;
            table.erase(iter);
            return true;
        }
        error_check->err_register(new RuntimeError(Token(TT_ERR, key + " is not defined")));
        return false;
    }

private:
    unordered_map<string, GG_Object*> table;
    Cache* parent;

};
#endif //GG_LANG_GG_MEMORY_H
