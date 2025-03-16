#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cerr << "Error: " << word1 << " -> " << word2 << ": " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int lenStr1 = str1.size();
    int lenStr2 = str2.size();

    if (abs(lenStr1 - lenStr2) > 1)
        return false;

    int countDiff = 0;

    if (lenStr1 - lenStr2 == 0) {
        for (int i = 0; i < lenStr1; ++i) {
            if (str1[i] != str2[i])
                countDiff++;
        }
    } else {
        int i = 0;
        int j = 0;

        const string& shortStr = (lenStr1 < lenStr2) ? str1 : str2;
        const string& longStr = (lenStr2 < lenStr1) ? str1 : str2;

        while (i < shortStr.size() && j < longStr.size()) {
            if (shortStr[i] != longStr[j]) {
                ++countDiff;
                if (countDiff > d)
                    return false;
            } else {
                ++i;
                ++j;
            }
        }
        if (longStr.size() > j)
            ++countDiff;
    }
    
    return countDiff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream inFile(file_name);
    string word;
    while (inFile >> word)
        word_list.insert(word);
    inFile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }

    std::cout << "Word ladder found: ";
    for (const string& word : ladder) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

#define my_assert(condition) { cout << ((condition) ? " Passed" : " Failed") << endl; }

void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
