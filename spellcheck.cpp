#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

unordered_map<string, long long int> wordList;
unordered_map<string, string> corrections;

int edit_distance(string, string);
string spell_correct(string &);

int main() {
    fstream dictFile;
    fstream freqFile;
    dictFile.open("dict.txt", ios::in);
    freqFile.open("freq.txt", ios::in);

    if(dictFile.is_open() && freqFile.is_open()){
        string s1,s2;
        while(getline(dictFile,s1) and getline(freqFile,s2)){
            long long int currentFreq=stoll(s2);
            wordList[s1]=currentFreq;
        }
        dictFile.close();
        freqFile.close();
    }
    else {
        cout << "Cannot Find Required Files, Please try again" << endl;
        return 0;
    }


    cout << "Enter a Paragraph" << endl << "-----------------" << endl;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string inputString;
    getline(cin, inputString);
    int inputLength = inputString.length();

    cout << endl;
    cout << "Corrected paragraph is: " << endl << "-----------------" << endl;

    auto start1 = chrono::high_resolution_clock::now();

    string word = "";

    for(int i=0; i < inputLength; i++){
        if(inputString[i] == ' ' || inputString[i] == ',' || inputString[i] == '.'){
            if (word != "") {
                string correctWord = spell_correct(word);
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
    string correctWord = spell_correct(word);
    cout << correctWord << ' ';


    cout << endl;
    cout << endl;
    cout << "--------------------------------" << endl;
    auto stop1 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop1 - start1);

    cout<<"Execution Time: "<<duration.count()/1000.0<<" milliseconds"<<endl;
    return 0;


}

int edit_distance(string s, string t){
    int n = s.length();
    int m = t.length();

    vector<vector<int>> dp(n+1, vector<int>(m+1,0));
    s = '.' + s;
    t = '.' + t;

    for(int i=n; i>0; i--){
        for(int j=m; j>0; j--){
            if(i==n || j==m) {
                if(s[i] == t[j]){
                    dp[i][j] = max(n-i, m-j);
                }
                else {
                    dp[i][j] = 1 + max(n-i, m-j);
                }
            }
            else {
                if (s[i] != t[j]){
                    dp[i][j] = 1 + min(dp[i][j+1], min(dp[i+1][j+1], dp[i+1][j]));
                }
                else {
                    dp[i][j] = dp[i+1][j+1];
                }
            }
        }
    }
    return dp[1][1];
}

string spell_correct(string &word) {
    if(wordList.find(word) != wordList.end()){
        return word;
    }
    if (corrections.find(word)!=corrections.end()){
        return corrections[word];
    }

    map<int, vector<string>> dist;
    for (auto freq : wordList){
        int x = edit_distance(freq.first, word);
        dist[x].push_back(freq.first);
    }

    auto lowestDist = dist.begin();
    pair<string, long long int> mostProbableWord = {"", -1};

    for(string &s : lowestDist -> second){
        long long int s_freq = wordList[s];
        if (s_freq > mostProbableWord.second) {
            mostProbableWord = {s, s_freq};
        }
    }

    corrections[word] = mostProbableWord.first;
    return mostProbableWord.first;
}
