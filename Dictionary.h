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

    bool Verify(std::string word, std::vector<std::string> *suggestion) const;
private:
    static unsigned int LevenshteinDistance(const std::string &a, const std::string &b);
    static unsigned min(unsigned int a, unsigned int b, unsigned int c);

    std::vector<std::string> _dict;
    std::vector<unsigned int> _l_distances;
};


#endif //TEST_4D_DICTIONARY_H
