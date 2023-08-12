#include "spell_checker.h"
#include <fstream>
#include <iostream>

SpellChecker::SpellChecker() {}

void SpellChecker::loadDictionary(const string& dictFilename, const string& freqFilename) {
    fstream dictFile(dictFilename, ios::in);
    fstream freqFile(freqFilename, ios::in);

    if (dictFile.is_open() && freqFile.is_open()) {
        string s1, s2;
        while (getline(dictFile, s1) && getline(freqFile, s2)) {
            long long int currentFreq = stoll(s2);
            wordList[s1] = currentFreq;
        }
        dictFile.close();
        freqFile.close();
    } else {
        cout << "Cannot Find Required Files, Please try again" << endl;
        return;
    }
}

string SpellChecker::spell_correct(string &word) {
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

int SpellChecker::edit_distance(string s,string t) {
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
