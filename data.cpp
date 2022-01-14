#include "data.h"

Data::Data(unsigned int n, const vector<string> &s,const vector<vector<int>> &v): rowsize(n), labels(s), rows(v) {}

void Data::insertRow(string s, const vector<int> &v){
    if(v.size()>rowsize){
    //che succede se aggiungiamo una riga piu grande delle altre? TODO
        return;
    }
    labels.push_back(s);
    rows.push_back(v);
    return;
}

vector<int> Data::readRow(unsigned int i) const{
    if(i>=rows.size()){
        //errore
    }
    return rows[i];
}

string Data::readLabel(unsigned int i) const{
    if(i>=rows.size()){
        //errore
    }
    return labels[i];
}

