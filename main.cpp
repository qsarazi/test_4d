//
// Created by qjps4 on 9/4/2020.
//

#include "Dictionary.h"

#include <algorithm>
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
    if (ac != 2) {
        cout << "Usage: " << av[0] << " dict_file" << endl;
        return 1;
    }

    try {
        string text;
        vector<string> suggestions{10};
        Dictionary dict{string(av[1])};
        ofstream out{"fautes.json"};

        out << "[" << endl;
        bool first = true;
        size_t start = 0;
        while (getline(cin, text)) {
            vector<Token> tokens = StringToToken(text);
            for (auto &&t : tokens) {

                //Skip all uppercase words
                if (all_of(t.word.begin(), t.word.end(), [](char c) {return isupper(c);}))
                    continue;


                if (dict.Verify(t.word, &suggestions))
                    continue;

                bool has_first_upper = isupper(t.word[0]);
                if (first)
                    first = false;
                else
                    out << ",";
                out << "{\n\"word\": \"" << t.word << "\",\n"
                    << "\"beginOffset\": " << t.start << ",\n"
                    << "\"endOffset\": " << t.end << ",\n"
                    << "\"suggestions\": [";
                bool first_word = true;
                for (auto s : suggestions) {
                    if (first_word)
                        first_word = false;
                    else
                        out << ", ";
                    if (has_first_upper)
                        s[0] = toupper(s[0]);
                    out << "\"" << s << "\"";
                }
                out << "]\n}\n";

                //write correct text
                cout << text.substr(start, t.start - start);
                if (has_first_upper)
                    suggestions[0][0] = toupper(suggestions[0][0]);
                cout << suggestions[0];
                start = t.end;
            }
        }
        out << "]" << endl;

    } catch (const exception &e) {
        cout << e.what() << endl;
        return 2;
    }

    return 0;
}