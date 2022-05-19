#include "parser.h"
#include "model.h"


template<typename T>
bool Parser::unique(vector<T> const &vec){
    map<T, int> freq;
    for (const T &i: vec) freq[i]++;
    for (auto const &pair: freq) if (pair.second > 1) return false;
    return true;
}

template bool Parser::unique(vector<QString> const &);
template bool Parser::unique(vector<QVariant> const &);
