//
// Created by qjps4 on 9/4/2020.
//

#include "Dictionary.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

struct Token {
    string word;
    size_t start;
    size_t end;
};

vector<Token> StringToToken(const std::string &text) {
    size_t start = 0;
    size_t end;
    vector<Token> tokens;

    while (!isalpha(text[start]))
        start += 1;

    while (start < text.size()) {
        end = start + 1;
        while (isalpha(text[end]))
            end += 1;
        tokens.push_back({text.substr(start, end - start), start, end});
        start = end + 1;
        while (!isalpha(text[start]))
            start += 1;
    }
    return tokens;
}

int main(int ac, char **av) {
    if (ac != 3) {
        cout << "Usage: " << av[0] << " dict_file" << endl;
        return 1;
    }

    try {
        string text;
        vector<string> suggestions{10};
        Dictionary dict{string(av[1])};
        ifstream in{av[2]};

        while (getline(in, text)) {
            cout << text << endl;
            vector<Token> tokens = StringToToken(text);
            for (auto &&t : tokens) {
                if (!dict.Verify(t.word, &suggestions)) {
                    //add to json
                }
            }
        }

    } catch (const exception &e) {
        cout << e.what() << endl;
        return 2;
    }

    //print the json
    return 0;
}