#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

void loadDataIntoArray(int size, int *storage, std::string line){
    for(int i = 0; i < size-1; i++){
        int nextDelimiter = line.find_first_of(' ');
        storage[i] = std::stoi(line.substr(0, nextDelimiter));
        line = line.substr(nextDelimiter+1);
    }
    storage[size-1] = std::stoi(line);
}

int main(){

    std::ifstream file("../input.txt");
    std::string line;
    int count = 0;

    while(std::getline(file, line)){

        int nReport = std::count(line.begin(), line.end(), ' ') + 1;
        int reports[nReport];

        loadDataIntoArray(nReport, reports, line);

        bool isIncreasing = reports[0] < reports[1] ? true : false;

        bool isSafe = true;
        std::string result;
        for(int i = 1; i < nReport; i++){

            if (reports[i-1] < reports[i] != isIncreasing || abs(reports[i-1] - reports[i]) > 3 || abs(reports[i-1] - reports[i]) == 0){
                isSafe = false;
                count++;
                break;
            }

        }

        result = isSafe ? "Safe" : "Unsafe";

        for(int el: reports) std::cout << el << " ";

        std::cout << ": " << result << '\n';

    }
    std::cout << '\n' << "Safe count: " << 1000 - count;

    return 0;
}