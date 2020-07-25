#include <iostream>
#include "src/main/executor.h"
//#include "src/lexer.h"
using namespace std;


//###########################
//Interface
//###########################
const string GG_ARROW("gg >>");



//#########################
//  Run
//########################


int run(string& text){
    Lexer lexer(text);
    vector<Token>* tokens = lexer.token_maker();
    if (error_check->is_error()){
        error_check->display_msg();
        return -1;
    }
    Parser parser(*tokens);
    delete tokens;
    Node* syntax_tree = parser.parse();
    if (error_check->is_error()){
        error_check->display_msg();
        return -1;
    }
    cout << syntax_tree->dfs() << endl;
    Executor executor(syntax_tree);
    GG_Object* result = executor.execute(executor.root);
    delete syntax_tree;
    if (error_check->is_error()){
        error_check->display_msg();
        return -1;
    }

    if (result->get_type()== TT_INT){
        cout << result->get_int_val()<<endl;
    }else if (result->get_type() == TT_FLOAT){
        cout << result->get_dl_val()<<endl;
    }
    gc->incinerate();
    return 0;

}

int main() {

    cout << "gg_lang ver 1.0"<< endl;
    cout << "Author: Dexuan Luo"<< endl;
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
        string* input_txt = new string();
        string* tmp = new string(ESCAPE);
        while (tmp->size() > 0 && string({(*tmp)[tmp->size() - 1]}) == ESCAPE){
            getline(cin, (*tmp));
            (*input_txt) += (*tmp);
        }

        if ((*input_txt) == GG){
            cout << "Bye" << endl;
            return 0;
        }

        run(*input_txt);
        delete input_txt;
        delete tmp;
        input_txt = nullptr;
        tmp = nullptr;



    }
    return 0;
}


