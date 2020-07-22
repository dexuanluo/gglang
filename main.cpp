#include <iostream>
#include <string>
#include "src/parser.h"
//#include "src/lexer.h"
using namespace std;


//###########################
//Interface
//###########################
const string GG_ARROW("gg >>>");
const string GG_TMP_ARROW("> ");



Node* run(string& text){
    Lexer lexer(text);
    vector<Token> tokens = lexer.token_maker();
    Parser parser(tokens);
    return parser.parse();
}

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
        string tmp(ESCAPE);
        while (tmp.size() > 0 && string({tmp[tmp.size() - 1]}) == ESCAPE){
            getline(cin, tmp);
            input_txt += tmp;
            cout << GG_TMP_ARROW;
        }

        if (input_txt == GG){
            cout << "Bye" << endl;
            return 0;
        }

        Node* syntax_tree = run(input_txt);
        if (syntax_tree == nullptr){
            cout << "Parser Error"<<endl;

        }else{
            cout << syntax_tree->dfs()<<endl;
        }




    }
    return 0;
}


