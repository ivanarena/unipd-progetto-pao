#ifndef DATA_H
#define DATA_H

#include "model.h"

#include <utility>

using std::string;
using std::vector;

class Data
{
private:
    unsigned int rowsize; //quante colonne,
    vector<string> labels;
    vector<vector<int>> rows;
public:
    explicit Data(unsigned int n = 0, const vector<string>& = vector<string>() , const vector<vector<int>>& = vector<vector<int>>());
    void insertCol(const vector<int>&);
    void insertRow(string s, const vector<int>&);
    void removeCol();
    void removeRow();
    vector<int> readRow(unsigned int) const;
    string readLabel(unsigned int) const;
};

#endif // DATA_H
