// Listing 22-5. Testing for Palindromes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>

/** Determine whether @p str is a palindrome.
 * Only letter characters are tested. Spaces and punctuation don't count.
 * Empty strings are not palindromes because that's just too easy.
 * @param str the string to test
 * @return true if @p str is the same forward and backward
 */
bool is_palindrome(std::string str)

{
    auto is_same_char = [](char a, char b)
    {
        auto lowercase = [](char ch){
            return std::tolower(ch, std::locale());
        };
        return lowercase(a) == lowercase(b);
    };

    auto non_letter = [](char a){
        return not std::isalpha(a, std::locale());
    };

    std::string::iterator end{std::remove_if(str.begin(), str.end(), non_letter)};
    std::string rev{str.begin(), end};
    std::reverse(rev.begin(), rev.end());
    return not rev.empty() and std::equal(str.begin(), end, rev.begin(), is_same_char);
}

int main()
{
    std::locale::global(std::locale{""});
    std::cin.imbue(std::locale{});
    std::cout.imbue(std::locale{});

    std::string line{};
    while (std::getline(std::cin, line))
        if (is_palindrome(line))
            std::cout << line << '\n';
}
