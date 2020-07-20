#include <iostream>
#include <string>
#include "src/lexer.h"
using namespace std;
string& input_txt = *new string();
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
        cout << "gg > ";
        getline(cin, input_txt);
        auto tokens = run(input_txt);
        if (input_txt == "gg"){
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
        cout <<endl;

    }
    return 0;
}


