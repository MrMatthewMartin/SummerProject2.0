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
void initialize_streams(std::locale native){
    std::cin.imbue(native);     // Interpret the input and output according
    std::cout.imbue(native);    // to native locale
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
/* Check line for only alphanumeric characters
 *  @param str the orignal string
 *  @param loc the locale used to test the characters
 *  @return a santized copy of the string
 * */
std::string word_extractor(std::string pItem, std::locale pNative){
    std::string copy;
    for (char ch : pItem)
        if (std::isalnum(ch, pNative))
            copy.push_back(toupper(ch, pNative));
    return copy;
}

/* Print the word and the number of counts to file if file opens or to
 * screen if opening of file fails.
 * @param map counts the map of all the counts
 * */
void output(count_map pCounts) {
//  Output duplicates to a file
    count_iter the{pCounts.find("THE")};
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
    std::locale native{""};     // Get native locale
    initialize_streams(native);
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
                std::string copy{word_extractor(item, native)};
                if (not copy.empty())
                    ++counts[copy];
            }

        }

        output(counts);

    }
}


