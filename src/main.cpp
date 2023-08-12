#include "spell_checker.h"
#include <iostream>
#include <chrono>

int main() {
    SpellChecker spellChecker;
    spellChecker.loadDictionary("data/dict.txt", "data/freq.txt");

    cout << "Enter a Paragraph" << endl << "-----------------" << endl;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string inputString;
    getline(cin, inputString);
    int inputLength = inputString.length();

    cout << endl;
    cout << "Corrected paragraph is: " << endl << "-----------------" << endl;

    auto start = chrono::high_resolution_clock::now();

    string word = "";

    for(int i=0; i < inputLength; i++){
        if(inputString[i] == ' ' || inputString[i] == ',' || inputString[i] == '.'){
            if (word != "") {
                string correctWord = spellChecker.spell_correct(word);
                cout << correctWord << ' ';
                word = "";
            }
        }
        else{
            if(inputString[i] >= 'A' && inputString[i] <= 'Z') {
                inputString[i] += 32;
            }
            word.push_back(inputString[i]);
        }
    }
    string correctWord = spellChecker.spell_correct(word);
    cout << correctWord << ' ';


    cout << endl;
    cout << endl;
    cout << "--------------------------------" << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout<<"Execution Time: "<<duration.count()/1000.0<<" milliseconds"<<endl;
    return 0;
}
