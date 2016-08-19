// Listing 26-3. Demonstrating Floating-Point Output
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>

void initialize_streams(){
    std::cin.imbue(std::locale{});
    std::cout.imbue(std::locale{});
}

/** @brief Skip the rest of the input line. */
void skip_line()
{
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
}

std::string sanitize(std::string const& str){
    std::string result{};
    for (char c : str)
        if (std::isalpha(c, std::locale{}) or c == ' ' or c == '-')
            result.push_back(c);
    return result;
}

int BMICalculator(int const weight, int const height){
    return static_cast<int>(weight * 10000 / (height * height) + 0.5);
}

/// Print a floating-point number in three different formats.
/// @param precision the precision to use when printing @p value
/// @param value the floating-point number to print
void print(int precision, float value)
{
    std::cout.precision(precision);
    std::cout << std::scientific << value << '\t';

    // Set the format to general.
    std::cout.unsetf(std::ios_base::floatfield);
    std::cout << value << '\n';
}

void printHeader(){
    std::cout << std::setw(5) << "ht(cm) "
              << std::setw(5) << "Wt(kg) "
              << std::setw(4) << "Sex "
              << std::setw(4) << "BMI"
              << std::setw(5) << " Name" << std::endl;
}

void print(int const threshold, std::vector<std::string> names,
           std::vector<int> weight, std::vector<int> height,
           std::vector<char> sex, std::vector<int> BMI){
    std::cout << std::endl;
    std::cout << "Male data\n";
    printHeader();
    for (std::vector<int>::size_type i(0); i!=height.size(); ++i){
        // Add in Mean and median BMI

        if ( sex.at(i) == 'M' or sex.at(i) == 'm'){
            std::cout << std::setw(6) << height.at(i)
                      << std::setw(6) << weight.at(i)
                      << std::setw(4) << sex.at(i)
                      << std::setw(4) << BMI.at(i);
            if (BMI.at(i) >= threshold)
                std::cout << '*';
            else
                std::cout << ' ';
            std::cout << std::setw(15) << names.at(i) << '\n';
        }
    }

    std::cout << std::endl;
    std::cout << "Female data\n";
    printHeader();
    for (std::vector<int>::size_type i(0); i!=height.size(); ++i){
        // Add in Mean and median BMI

        if ( sex.at(i) == 'F' or sex.at(i) == 'f'){
            std::cout << std::setw(6) << height.at(i)
                      << std::setw(6) << weight.at(i)
                      << std::setw(4) << sex.at(i)
                      << std::setw(4) << BMI.at(i);
            if (BMI.at(i) >= threshold)
                std::cout << '*';
            else
                std::cout << ' ';
            std::cout << std::setw(15) << names.at(i) << '\n';
        }
    }
};

char checkChar(std::string const pMessage){
    std::string input{""};
    char myChar  = {0};
    while (true) {
        std::cout << pMessage;
        getline(std::cin, input);

        if (input.length() == 1 ) {
            myChar = input[0];
            break;
        }

        std::cout << "Invalid character, please try again" << std::endl;
        //skip_line();
    }
    return myChar;
}

int checkInt(std::string const pMessage){
    std::string input{};
    // How to get a number.
    int myNumber{0};
        while (true) {
            std::cout << pMessage;
            getline(std::cin, input);

            // This code converts from string to number safely.
            std::stringstream myStream(input);
            if (myStream >> myNumber)
                return myNumber;
            std::cout << "Invalid number, please try again" << std::endl;
            //skip_line();
        }
}

bool checkBool(std::string const pMessage){
    std::string input{};
    // How to get a number.
    bool myNumber{0};
    while (true) {
        std::cout << pMessage;
        getline(std::cin, input);

        // This code converts from string to number safely.
        std::stringstream myStream(input);
        if (myStream >> myNumber)
            return myNumber;
        std::cout << "Not a 1 (for yes) or 0 (for no), please try again" << std::endl;
        //skip_line();
    }

}

std::string checkString(std::string const pMessage){
    std::string input{""};

    // How to get a string/sentence with spaces
    std::cout << pMessage;
    getline(std::cin, input);

    std::string copy{sanitize(input)};
    //std::cout << "You entered: " << copy << std::endl ;

    return copy;
}

char sex(){
    char input{0};
    while (true) {
        input = checkChar("Sex (M or F): ");
        if (std::isalpha(input, std::locale{}) and (input == 'M' or input == 'm'
                                                   or input == 'F' or input == 'f'))
            return input;
        std::cout << "Invalid input. Please check your input.\n";
    }
}

///  Function to retrieve BMI details of user
/// @param pName stores names
/// @param pw & ph store weight and height respectively
/// @param ps stores sex
/// @param pBMI stores calculated BMI
/// @returns details to the vectors contained in main program
void getdetails(std::vector<std::string>& pName,
                std::vector<int>& pw, std::vector<int>& ph,
                std::vector<char>& ps, std::vector<int>& pBMI,
                int const thresh) {
    pName.push_back(checkString("Name: "));
    ph.push_back(checkInt("Height (cm): "));
    pw.push_back(checkInt("Weight (kg): "));
    ps.push_back(sex());
    //Calculate and push back BMI
    pBMI.push_back(BMICalculator(pw.back(), ph.back()));

    if (pBMI.back() >= thresh){
        std::cout << "BMI: " << pBMI.back() << std::endl;
    }
}

/// Main program.
int main()
{
    std::locale::global(std::locale{""});
    initialize_streams();

    std::vector<std::string> Names;
    std::vector<int> weight;
    std::vector<int> height;
    std::vector<char> sex;
    std::vector<int> BMI;

    // Retrieve threshold BMI
    int ThreshBMI{0};
    while (true) {
        ThreshBMI = checkInt("Enter a threshold BMI: ");
        std::cout << "You entered: " << ThreshBMI << ", is this correct?";
        if (checkBool(" Enter 1 for yes and 0 for no: "))
            break;
    }
    //skip_line();
    std::cout << std::endl;
    while (true) {
        getdetails(Names, weight, height, sex, BMI, ThreshBMI);
        std::cout << "Would you like to enter more details? ";
        if (!checkBool("Enter 1 for yes and 0 for no: "))
            break;
    }

    print(ThreshBMI, Names, weight, height, sex, BMI);

}
