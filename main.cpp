#include <iostream>
#include <string>
#include "./src/gg.h"
using namespace std;

int main() {
    cout << "___________________________"<< endl;
    cout << "gg_lang ver 1.0"<< endl;
    cout << "Author: DL"<< endl;
    cout << "___________________________"<< endl;
    while (true){
        string input_txt;
        string tmp = " ";
        cout << "gg > ";
        getline(cin, input_txt);

        run(input_txt);

    }
    return 0;
}