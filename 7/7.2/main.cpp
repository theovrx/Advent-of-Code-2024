#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

unsigned long long results[850];
std::vector<int> numberLists[850];

void loadData(unsigned long long results[850], std::vector<int> numberLists[850]){
    std::ifstream file("../input.txt");
    std::string line;
    int index = 0;
    while(std::getline(file, line)){
        int sepIndex = line.find(':');
        results[index] = std::stoll(line.substr(0,sepIndex));
        line = line.substr(sepIndex+2);

        sepIndex = line.find(' ');
        while (sepIndex != line.npos){
            numberLists[index].push_back(std::stoi(line.substr(0, sepIndex)));
            line =  line.substr(sepIndex + 1);
            sepIndex = line.find(' ');
        }
        numberLists[index].push_back(std::stoi(line));
        index++;
    }
}

bool findSequence(unsigned long long result, std::vector<int> numbers){
    for(int sequence = 0; sequence < 1 << numbers.size()-1; sequence++){
        for(int sequence2 = 0; sequence2 < 1 << numbers.size()-1; sequence2++){
            unsigned long long count = numbers.at(0);
            // std::cout << result << ": " << numbers.at(0);
            for(int numberIndex = 0; numberIndex < numbers.size() - 1; numberIndex++){
                if((1 << numberIndex) & sequence && (1 << numberIndex) & sequence2){
                    count += numbers.at(numberIndex + 1);
                    // std::cout << " + " << numbers.at(numberIndex + 1);
                }
                else if((1 << numberIndex) & sequence){
                    count *= numbers.at(numberIndex + 1);
                    // std::cout << " * " << numbers.at(numberIndex + 1);
                }
                else if((1 << numberIndex) & sequence2){
                    count = std::stoll(std::to_string(count) + std::to_string(numbers.at(numberIndex + 1)));
                    // std::cout << " || " << numbers.at(numberIndex + 1);
                }
                else break;
                if(count > result) break;
            }
            // std::cout << " = " << count << '\n';
            if(count == result) return true;
        }
    }
    return false;
}

int main(){

    loadData(results, numberLists);

    unsigned long long count = 0;
    for(int i = 0; i < 850; i++){
        if(findSequence(results[i], numberLists[i])) count += results[i];
    }

    std::cout << "Count: " << count << '\n';

    return 0;

}