//
// Created by qjps4 on 9/4/2020.
//

#ifndef TEST_4D_DICTIONARY_H
#define TEST_4D_DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {
public:
    explicit Dictionary(const std::string &file);

    bool Verify(const std::string &word, std::vector<std::string> *suggestion) const;

private:
    std::vector<std::string> _dict;
};


#endif //TEST_4D_DICTIONARY_H
