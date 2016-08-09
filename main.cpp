// Listing 14-2. Copying Integers from a Named File to a Named File
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <map>
#include <sstream>
#include <locale>

//
//  Can declare typedefs for clearer understanding of code
//
typedef std::map<std::string, int> count_map;
typedef std::map<std::string, int> ::iterator count_iter;
typedef std::string::size_type str_size;


/* Initialize the I/O streams by imbuing them with the streams with
 * the native locale. C++ initially imbues streams with the classic locale.
 * @param locale the native locale
 * */
void initialize_streams(){
    std::cin.imbue(std::locale{});     // Interpret the input and output according
    std::cout.imbue(std::locale{});    // to native locale
};

/* Could replace iterator with this if wanted to use auto.. can't just use auto
 * auto iterator_using_parens( counts.find("the") );
 * auto iterator_using_equal = counts.find("the");
 * /////////////////////////////////////////////////////////////////////////////////
 *  This function prints the number of times the word 'the' is found in the
 *  file. Note: used "->" as appose to "." to access members of iterators
 *  @param iter an iterator that contains 'the'
 *  @param pCounts used to check if 'the' contained in file
 */
void found(std::map<std::string, int>::iterator pIt, std::map<std::string, int> pCounts){
    if (pIt == pCounts.end())
        std::cout << "\"the\": not found\n";
    else if (pIt->second == 1)
        std::cout << "\"the\": occurs " << pIt->second << " time\n";
    else
        std::cout << "\"the\": occurs " << pIt->second << " times\n";
}

/*This function searchest for the longest word for to be used in output alignment
 * @param map the map to search
 * @return the size of the longest key in @p map
 * */
str_size longest_word(count_map pcounts) {
    std::string::size_type Longest{};
    for (auto element : pcounts)
        if (element.first.size() > Longest)
            Longest = element.first.size();
    return Longest;
}

/* Test for non-letter.
 * @param ch the character to test
 * @return true if @p ch is not a character that makes up a word
 */
bool non_letter(char ch) {
    return not std::isalnum(ch, std::locale());
}

/* Convert to lowercase.
 * Use canonical form by converting to uppercase first, and then
 * to lower case
 * @param ch the character to test
 * @return the character converted to lower case
 * */
char lowercase(char ch){
    return std::tolower(ch, std::locale());
}

/* Check line for only alphanumeric characters
 *  @param str the orignal string
 *  @return a santized copy of the string
 * */
std::string word_extractor(std::string pItem){
    // Remove all non-letters from the string and then erase them
    pItem.erase(std::remove_if(pItem.begin(), pItem.end(), non_letter), pItem.end());
    // Convert the remnants of the string to lower case
    std::transform(pItem.begin(), pItem.end(), pItem.begin, lowercase);
    return pItem;
}

/* Print the word and the number of counts to file if file opens or to
 * screen if opening of file fails.
 * @param map counts the map of all the counts
 * */
void output(count_map pCounts) {
//  Output duplicates to a file
    count_iter the{pCounts.find("the")};
    const int count_size{10};
    std::ofstream out{"ExploreOut.txt"};
    if (not out) {
        std::perror("ExploreOut.txt");
        found(the, pCounts);
        for (auto element : pCounts)
            std::cout << std::setw(longest_word(pCounts)) << std::left << element.first
                      << std::setw(count_size) << std::right << element.second << '\n';
    }
    else {
        std::cout << "Written to file\n";
        found(the, pCounts);
        for (auto element : pCounts)
            out << std::setw(longest_word(pCounts)) << std::left << element.first
                << std::setw(count_size) << std::right << element.second << '\n';
        out.close();
    }
}

int main() {
    std::locale::global(std::locale{""});
    initialize_streams();
    count_map counts;
    std::string word{};
    std::ifstream in{"explore15.txt"};
    if (not in)
        std::perror("explore15.txt");
    else {
        std::string line, item;
        while (getline (in, line)) {
            std::stringstream ss(line); // Insert the string into a stream
            while (ss >> item){
                std::string copy{word_extractor(item)};
                if (not copy.empty())
                    ++counts[copy];
            }

        }

        output(counts);

    }
}


