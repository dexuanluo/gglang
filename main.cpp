#include <iostream>
#include <string>
#include "src/lexer.h"
using namespace std;

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
        string input_txt;
        cout << "gg > ";
        getline(cin, input_txt);
        auto tokens = run(input_txt);
        for(auto iter = tokens.begin(); iter != tokens.end(); ++iter){
            cout << "[" + iter->type + "," + iter->val + "] ";
        }
        cout <<endl;

    }
    return 0;
}


