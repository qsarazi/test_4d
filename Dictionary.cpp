//
// Created by qjps4 on 9/4/2020.
//

#include "Dictionary.h"

#include <algorithm>
#include <fstream>

using namespace std;

Dictionary::Dictionary(const string &file) {
    ifstream in{file};
    string word;

    while (in >> word) {
        _dict.push_back(word.substr(0, word.find('/')));
    }
}

bool Dictionary::Verify(string word, vector<string> *suggestion) const {
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
    vector<pair<unsigned, string>> sugg;
    sugg.reserve(_dict.size());

    for (auto &&w : _dict) {
        unsigned l = LevenshteinDistance(w, word);
        if (l == 0)
            return true;
        sugg.emplace_back(l, w);
    }
    sort(sugg.begin(), sugg.end(),
         [](const pair<unsigned, string> &a, const pair<unsigned, string> &b) { return a.first < b.first; });

    for (size_t i = 0; i < suggestion->size(); ++i) {
        (*suggestion)[i] = sugg[i].second;
    }

    return false;
}

unsigned int Dictionary::LevenshteinDistance(const std::string &a, const std::string &b) {
    unsigned cost;

    unsigned mat[64][64];

    for (size_t i = 0; i < a.size(); i++)
        mat[i][0] = i;
    for (size_t i = 0; i < b.size(); i++)
        mat[0][i] = i;

    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            if (a[i] == b[j])
                cost = 0;
            else
                cost = 1;
            mat[i + 1][j + 1] = Dictionary::min(mat[i][j + 1] + 1,
                                                mat[i + 1][j] + 1,
                                                mat[i][j] + cost);
        }
    }

    return mat[a.size() - 1][b.size() - 1];
}

unsigned Dictionary::min(unsigned int a, unsigned int b, unsigned int c) {
    unsigned min;

    if (a < b)
        min = a;
    else
        min = b;
    if (c < min)
        min = c;
    return min;
}
