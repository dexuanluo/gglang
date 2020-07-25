//
// Created by Dexuan on 2020-07-25.
//
#include "../gg_object.h"
#include "vector"
#ifndef GG_LANG_AVALON_H
#define GG_LANG_AVALON_H

//#####################################
//     Garbage Collector
//#####################################

class Avalon{
public:
    vector<GG_Object*> garbage;
    Avalon(){}
    void garbage_register(GG_Object* trash){
        garbage.push_back(trash);
    }
    void incinerate(){
        while (garbage.size() > 0){
            if (garbage.back()->is_tmp()){
                delete garbage.back();
            }
            garbage.pop_back();
        }
    }
};

//Initializing Singleton Garbage Collector
static Avalon * const gc = new Avalon();


#endif //GG_LANG_AVALON_H
