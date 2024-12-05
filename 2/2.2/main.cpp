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

        bool isIncreasing = reports[0] < reports[nReport-1] ? true : false;

        bool isJokerUsable = true;
        bool isSafe = true;
        std::string result;
        for(int i = 1; i < nReport; i++){

            if (reports[i-1] < reports[i] != isIncreasing || abs(reports[i-1] - reports[i]) > 3 || abs(reports[i-1] - reports[i]) == 0){

                if (isJokerUsable){
                    isJokerUsable = false;

                    //Is the problem the value at index i?
                    if (nReport-1==i || !(reports[i-1] < reports[i+1] != isIncreasing || abs(reports[i-1] - reports[i+1]) > 3 || abs(reports[i-1] - reports[i+1]) == 0)){
                         reports[i] = reports[i-1];
                         continue;
                    }

                    //Or is it the value at index i-1?
                    else if(i<2 || !(reports[i-2] < reports[i] != isIncreasing || abs(reports[i-2] - reports[i]) > 3 || abs(reports[i-2] - reports[i]) == 0)){
                        reports[i-1] = reports[i]; //Doesn't affect the verification but heh
                        continue;
                    }

                    //Or are they both a problem?
                    isSafe = false;
                    count++;
                    break;
                }
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