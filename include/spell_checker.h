#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class SpellChecker {
    public:
        SpellChecker();
        void loadDictionary(const string& dictFilename, const string& freqFilename);
        string spell_correct(string& input);
        
    private:
        int edit_distance(string s, string t);
        
        unordered_map<string, long long int> wordList;
        unordered_map<string, string> corrections;
};

#endif
