#include <iostream>
#include <string>
#include "src/lexer.h"
using namespace std;
//###########################
//Interface
//###########################
const string GG_ARROW("gg >");
const string GG_TMP_ARROW("> ");
int main() {

    cout << "gg_lang ver 1.0"<< endl;
    cout << "Author: DL"<< endl;
    cout << endl;
    cout << "         $$$$$$$" << endl;
    cout << "         $$    $$" << endl;
    cout << "         $$    $$" << endl;
    cout << "         $$    $$" << endl;
    cout << "         $$    $$" << endl;
    cout << "         $$    $$$$$$$" << endl;
    cout << "   $$$$$$$$    $$    $$" << endl;
    cout << " $$$$$   $$    $$    $$$$$$" << endl;
    cout << "$$$ $$   $$    $$    $$   $$" << endl;
    cout << "$$  $$   $$    $$    $$$   $$" << endl;
    cout << "$$  $$   $$    $$    $     $$" << endl;
    cout << "$$   $$$  $$$$  $$$$   $  $$" << endl;
    cout << "$$                        $$" << endl;
    cout << " $$                       $$" << endl;
    cout << "   $$$                 $$" << endl;
    cout << endl;

    while (true){
        cout << GG_ARROW;
        string input_txt;
        string tmp(WS_ESCAPE);
        while (tmp.size() > 0 && string({tmp[tmp.size() - 1]}) == WS_ESCAPE){
            getline(cin, tmp);
            input_txt += tmp;
            cout << GG_TMP_ARROW;
        }
        auto tokens = run(input_txt);
        if (input_txt == GG){
            cout << "Bye" << endl;
            return 0;
        }
        for(auto iter = tokens.begin(); iter != tokens.end(); ++iter){

            if (iter->val.size() > 0){
                cout << "[" + iter->type + "," + iter->val + "] ";
            }else{
                cout << "[" + iter->type + "] ";
            }

        }
        cout << endl;

    }
    return 0;
}


