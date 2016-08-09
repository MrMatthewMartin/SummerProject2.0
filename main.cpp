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


/* Could replace iterator with this if wanted to use auto.. can't just use auto
 * auto iterator_using_parens( counts.find("the") );
   auto iterator_using_equal = counts.find("the");
 */
void found(std::map<std::string, int>::iterator pIt, std::map<std::string, int> pCounts){
    if (pIt == pCounts.end())
        std::cout << "\"the\": not found\n";
    else if (pIt->second == 1)
        std::cout << "\"the\": occurs " << pIt->second << " time\n";
    else
        std::cout << "\"the\": occurs " << pIt->second << " times\n";
}


int main() {
//  Can declare typedefs for clearer understanding of code
    typedef std::map<std::string, int> count_map;
    typedef std::map<std::string, int> ::iterator count_iter;
//
    count_map counts;
    std::string word{};
    std::ifstream in{"Test.txt"};
    if (not in)
        std::perror("Test.txt");
    else {
        std::string line, item;

        while (getline (in, line)) {
//            line.erase(line.find_last_not_of("\n\r")+1);
            std::stringstream ss(line); // Insert the string into a stream

            while (ss >> item){
                std::string copy{};
                for (char ch : item)
                    if (std::isalnum(ch) and ch != '.') {
                        copy.push_back(ch);
                    }
                if (not copy.empty())
                    ++counts[item];
            }

        }


        std::string::size_type longest{};
        for (auto element : counts)
            if (element.first.size() > longest)
                longest = element.first.size();

        count_iter the{counts.find("the")};

        const int count_size{10};
//      Output duplicates to a file
        std::ofstream out{"ExploreOut.txt"};
        if (not out) {
            std::perror("ExploreOut.txt");
            found(the, counts);
            for (auto element : counts)
                std::cout << std::setw(longest) << std::left << element.first
                          << std::setw(count_size) << std::right << element.second << '\n';
        }
        else
        {
            std::cout << "Written to file\n";
            found(the, counts);
            for (auto element : counts)
                out << std::setw(longest) << std::left << element.first
                    << std::setw(count_size) << std::right << element.second << '\n';
            out.close();
        }

    }
}


