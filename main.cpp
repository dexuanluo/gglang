#include <iostream>
#include <string>
using namespace std;
int main() {

    cout << "___________________________"<< endl;
    cout << "gg_lang ver 1.0"<< endl;
    cout << "Author: DL"<< endl;
    cout << "___________________________"<< endl;
    while (true){
        string input_txt;
        cout << "gg > ";
        cin >> input_txt;
        cout << input_txt + "\t"<<endl;
    }
    return 0;
}