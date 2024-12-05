#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int resolveMatch(std::string exp, bool& isEnabled){

    if (exp == "do()"){
        isEnabled = true;
        return 0;
    }

    else if(exp == "don't()"){
        isEnabled = false;
        return 0;
    }

    if (!isEnabled){
        return 0;
    }

    int sizeInt1 = exp.find(",") - 4;
    int sizeInt2 = exp.length() - sizeInt1 - 6;

    int int1 = std::stoi(exp.substr(4, sizeInt1));
    int int2 = std::stoi(exp.substr(5 + sizeInt1, sizeInt2));

    return int1*int2;
}

int main(){

    std::ifstream file("../input.txt");
    std::string line;
    std::regex pattern("(do\\(\\))|don't\\(\\)|(mul\\([0-9]*,[0-9]*\\))");

    unsigned long result = 0;
    bool isEnabled = true;

    while(getline(file, line)){

        //Create regex iterator
        auto it = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();

        while(it != end){
            std::string match = it->str();
            //std::cout<<match<<'\n';
            result += resolveMatch(match, isEnabled);
            it++;
        }
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}