#include <iostream>
#include <string>
#include <fstream>

void loadData(std::string matrix[140]){
    std::ifstream file("../input.txt");
    std::string line;

    int index = 0;
    while(std::getline(file, line)){
        matrix[index] = line;
        index++;
    }

    return;
}

int countXMAS(std::string matrix[140]){

    int directions[2]{-1, 1};
    int count = 0;
    int lineLength = matrix[0].length();

    for(int y = 0; y < 140; y++)
    for(int x = 0; x < lineLength; x++){

        if(matrix[y][x] == 'A'){ //Look for every Xs 0 : 123 is weird
            for(int direction: directions){
                if( // facing left or right
                    0 < y && y < 139
                    && 0 < x && x < lineLength-1
                    && matrix[y + 1][x + direction] == 'S'
                    && matrix[y - 1][x + direction] == 'S'
                    && matrix[y + 1][x - direction] == 'M'
                    && matrix[y - 1][x - direction] == 'M'
                ) count++;
                if( // facing up or down
                    0 < y && y < 139
                    && 0 < x && x < lineLength-1
                    && matrix[y + direction][x + 1] == 'M'
                    && matrix[y + direction][x - 1] == 'M'
                    && matrix[y - direction][x + 1] == 'S'
                    && matrix[y - direction][x - 1] == 'S'
                ) count++;
            }
        }

    }

    return count;
}

int main(){

    std::string matrix[140];
    loadData(matrix);
    int count = countXMAS(matrix);
    std::cout << "Occurences: " << count << '\n';

    return 0;
}