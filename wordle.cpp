#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    string& current,
    const string& pattern,
    string floating,
    const set<string>& dict,
    set<string>& results,
    int pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
     set<string> results;
    if(in.empty()) {
        return results;
    }
    string current = in;
    wordleHelper(current, in, floating, dict, results, 0);

    return results;

}

// Define any helper functions here
void wordleHelper(
    string& current,
    const string& pattern,
    string floating,
    const set<string>& dict,
    set<string>& results,
    int pos)
{
    int n = static_cast<int>(pattern.size());
    if(pos == n) {
        
        if(!floating.empty()) {
            return;
        }
        
        if(dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }
    int remainingSlots = n - pos;
    if(static_cast<int>(floating.size()) > remainingSlots) {
        return;
    }
    if(pattern[pos] != '-') {
        current[pos] = pattern[pos];
        wordleHelper(current, pattern, floating, dict, results, pos + 1);
        return;
    }
    for(char c = 'a'; c <= 'z'; ++c) {
        current[pos] = c;
        string newFloating = floating;
        size_t idx = newFloating.find(c);
        if(idx != string::npos) {
            newFloating.erase(idx, 1);
        }

        wordleHelper(current, pattern, newFloating, dict, results, pos + 1);
    }
}