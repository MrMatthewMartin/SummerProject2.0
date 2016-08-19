// Listing 26-3. Demonstrating Floating-Point Output
#include <iostream>
#include <sstream>
#include <vector>

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

int checkInt(){
    std::string input{};
    // How to get a number.
    int myNumber{0};
        while (true) {
            std::cout << "Please enter a number: ";
            getline(std::cin, input);

            // This code converts from string to number safely.
            std::stringstream myStream(input);
            if (myStream >> myNumber)
                return myNumber;
            std::cout << "Invalid number, please try again" << std::endl;
        }
}

bool checkBool(){
    std::string input{};
    // How to get a number.
    bool myNumber{0};
    while (true) {
        std::cout << "Please enter 1 or 0: ";
        getline(std::cin, input);

        // This code converts from string to number safely.
        std::stringstream myStream(input);
        if (myStream >> myNumber)
            return myNumber;
        std::cout << "Not a 1 (for yes) or 0 (for no), please try again" << std::endl;
    }

}

std::string checkString(){
    std::string input = "";

    // How to get a string/sentence with spaces
    std::cout << "Please enter a name (with spaces):\n>";
    getline(std::cin, input);

    std::cout << "You entered: " << input ;
}

int BMICalculator(int const pw, int const ph){
    return pw/(ph*ph);
}

///  Function to retrieve BMI details of user
/// @param pName stores names
/// @param pw & ph store weight and height respectively
/// @param ps stores sex
/// @param pBMI stores calculated BMI
/// @returns details to the vectors contained in main program
void getdetails(std::vector<std::string>& pName,
                std::vector<int>& pw, std::vector<int>& ph,
                std::vector<char>& ps, std::vector<int>& pBMI) {




}

/// Main program.
int main()
{
    std::vector<std::string> Names;
    std::vector<int> weight;
    std::vector<int> height;
    std::vector<char> sex;
    std::vector<int> BMI;

    // Retrieve threshold BMI
    int ThreshBMI{0};
    std::cout << "First enter a threshold BMI. ";
    while (true) {
        ThreshBMI = checkInt();
        std::cout << "You entered: " << ThreshBMI << ", is this correct?" << std::endl;
        if (checkBool())
            break;
    }

    while (true) {
        getdetails(Names, weight, height, sex, BMI, ThreshBMI);
        std::cout << "Would you like to enter more details? ";
        if (checkBool())
            break;
    }




    print(6, 123456.789f);
}
