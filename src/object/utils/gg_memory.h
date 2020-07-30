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
        unordered_map<string, shared_ptr<GG_Object>> table;
        parent = parent_;
        is_root = false;
    }

    // A way to initialize the table root table to store runtime variable
    Cache(string set_as_root){

        long int t = 1;
        long int f = 0;

        table[NULLVAR] = make_shared<Undefined>(Undefined());
        table[NULLVAR]->not_tmp();
        table[TRUE] = make_shared<Numeric>(Numeric(t));
        table[TRUE]->not_tmp();
        table[FALSE] = make_shared<Numeric>(Numeric(f));
        table[FALSE]->not_tmp();
        is_root = true;
    }

    bool is_root_table(){
        return is_root;
    }

    shared_ptr<GG_Object> get(string key){
        if (!is_root_table()){
            auto iter = table.find(key);
            if ( iter != table.end()) {
                return iter->second;
            }else if(parent != nullptr){
                return parent->get(key);
            }
            return parent->get(NULLVAR);
        }
        auto iter = table.find(key);
        if ( iter != table.end()) {
            return iter->second;
        }
        return table[NULLVAR];

    }

    void set(string key, shared_ptr<GG_Object> val){
        if (RUNTIMEVAR.find(key) != RUNTIMEVAR.end()){
            error_check->err_register(new RuntimeError(Token(TT_ERR, "You cannot modify a runtime variable")));
            return;
        }
        if (!is_root_table()){
            try{
                table[key] = val;
                return;
            }catch(std::exception& e){
                cout << e.what() <<endl;
                error_check->err_register(new RuntimeError(Token(TT_ERR, "Unknown: Failed to Change Variable Value")));
                return;
            }

        }
        error_check->err_register(new RuntimeError(Token(TT_ERR, "You cannot modify a runtime variable")));
        return;


    }

    bool del(string key){
        if (!is_root_table()){
            auto iter = table.find(key);
            if ( iter != table.end()){
                table.erase(iter);
                return true;
            }
            if (parent != nullptr){
                return parent->del(key);
            }

        }
        error_check->err_register(new RuntimeError(Token(TT_ERR, key + " is not defined or the variable you are trying to delete is a constant runtime variable")));
        return false;
    }

private:
    unordered_map<string, shared_ptr<GG_Object>> table;
    Cache* parent;
    bool is_root;

};
#endif //GG_LANG_GG_MEMORY_H
