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

    int directions[4][2]{
        {1,0},
        {0,1},
        {1,1},
        {1,-1}
    };
    int count = 0;
    int lineLength = matrix[0].length();

    for(int y = 0; y < 140; y++)
    for(int x = 0; x < lineLength; x++){

        if(matrix[y][x] == 'X'){ //Look for every Xs 0 : 123 is weird
            for(auto& direction: directions){
                if(
                    0 <= y + 3*direction[1] && y + 3*direction[1] < 140
                    && 0 <= x + 3*direction[0] && x + 3*direction[0] < lineLength
                    && matrix[y + direction[1]][x + direction[0]] == 'M'
                    && matrix[y + 2*direction[1]][x + 2*direction[0]] == 'A'
                    && matrix[y + 3*direction[1]][x + 3*direction[0]] == 'S'
                ) count++;
                if(
                    0 <= y - 3*direction[1] && y - 3*direction[1] < 140
                    && 0 <= x - 3*direction[0] && x - 3*direction[0] < lineLength
                    && matrix[y - direction[1]][x - direction[0]] == 'M'
                    && matrix[y - 2*direction[1]][x - 2*direction[0]] == 'A'
                    && matrix[y - 3*direction[1]][x - 3*direction[0]] == 'S'
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