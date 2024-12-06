#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>

char map[130][130];
int guardPos[2];
int guardDirections[4][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
char charDirections[4] = {'^', '>', 'v', '<'};
std::unordered_set<std::string> positions;

void loadMap(char map[130][130]){
    std::ifstream file("../input.txt");
    std::string line;
    int y = 0;
    while(getline(file, line)){
        int x = 0;
        for(char mapPoint: line){
            map[x][y] = mapPoint;
            if(mapPoint == '^'){
                guardPos[0] = x;
                guardPos[1] = y;
            }
            x++;
        }
        y++;
    }
}

void printMap(char map[130][130]){
    for(int y = 0; y < 130; y++){
        for(int x = 0; x < 130; x++){
            std::cout << map[x][y];
        }
        std::cout << '\n';
    }
}

void predictGuardPositions(char map[130][130], std::unordered_set<std::string> &positions){
    int direction = 0;
    int nextPos[] = {guardPos[0] + guardDirections[direction][0], guardPos[1] + guardDirections[direction][1]};
    char nextPoint = map[nextPos[0]][nextPos[1]];

    while(
        nextPos[0] >= 0 && nextPos[0] < 130
        && nextPos[1] >= 0 && nextPos[1] < 130
    ){  
        std::string strPos = std::to_string(guardPos[0]) + " " + std::to_string(guardPos[1]);
        positions.insert(strPos);
        while(nextPoint == '#'){
            direction = (direction+1)%4;
            nextPos[0] = guardPos[0] + guardDirections[direction][0];
            nextPos[1] = guardPos[1] + guardDirections[direction][1];
            nextPoint = map[nextPos[0]][nextPos[1]];
        }

        if(nextPoint == charDirections[direction]){
            loadMap(map);
            return;
        }

        map[nextPos[0]][nextPos[1]] = charDirections[direction];
        guardPos[0] = nextPos[0];
        guardPos[1] = nextPos[1];

        nextPos[0] = guardPos[0] + guardDirections[direction][0];
        nextPos[1] = guardPos[1] + guardDirections[direction][1];
        nextPoint = map[nextPos[0]][nextPos[1]];
    }
    std::string strPos = std::to_string(guardPos[0]) + " " + std::to_string(guardPos[1]);
    positions.insert(strPos);
    loadMap(map);
}

bool moveGuard(char map[130][130]){
    int direction = 0;
    int nextPos[] = {guardPos[0] + guardDirections[direction][0], guardPos[1] + guardDirections[direction][1]};
    char nextPoint = map[nextPos[0]][nextPos[1]];

    while(
        nextPos[0] >= 0 && nextPos[0] < 130
        && nextPos[1] >= 0 && nextPos[1] < 130
    ){
        while(nextPoint == '#' || nextPoint == 'O'){
            direction = (direction+1)%4;
            nextPos[0] = guardPos[0] + guardDirections[direction][0];
            nextPos[1] = guardPos[1] + guardDirections[direction][1];
            nextPoint = map[nextPos[0]][nextPos[1]];
        }

        if(nextPoint == charDirections[direction]){
            return true;
        }

        map[nextPos[0]][nextPos[1]] = charDirections[direction];
        guardPos[0] = nextPos[0];
        guardPos[1] = nextPos[1];

        nextPos[0] = guardPos[0] + guardDirections[direction][0];
        nextPos[1] = guardPos[1] + guardDirections[direction][1];
        nextPoint = map[nextPos[0]][nextPos[1]];
    }
    return false;
}

int main(){

    loadMap(map);
    predictGuardPositions(map, positions);
    int count = 0;
    positions.erase("68 95"); //We can't place an obstacle at player's initial position
    for(std::string position: positions){
        int index = position.find(" ");
        int x = std::stoi(position.substr(0,index));
        int y = std::stoi(position.substr(index+1));
        map[x][y] = 'O';
        if (moveGuard(map)){
            count++;
        }
        loadMap(map);
    }

    std::cout << "Count: " << count << '\n';

    return 0;
}