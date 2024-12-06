#include <iostream>
#include <string>
#include <fstream>

char map[130][130];
int guardPos[2];
int guardDirections[4][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
char charDirections[4] = {'^', '>', 'v', '<'};

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

void moveGuard(char map[130][130]){
    int direction = 0;
    int nextPos[] = {guardPos[0] + guardDirections[direction][0], guardPos[1] + guardDirections[direction][1]};
    char nextPoint = map[nextPos[0]][nextPos[1]];

    while(
        nextPos[0] >= 0 && nextPos[0] < 130
        && nextPos[1] >= 0 && nextPos[1] < 130
    ){
        while(nextPoint == '#'){
            direction = (direction+1)%4;
            nextPos[0] = guardPos[0] + guardDirections[direction][0];
            nextPos[1] = guardPos[1] + guardDirections[direction][1];
            nextPoint = map[nextPos[0]][nextPos[1]];
        }

        map[nextPos[0]][nextPos[1]] = charDirections[direction];
        guardPos[0] = nextPos[0];
        guardPos[1] = nextPos[1];

        nextPos[0] = guardPos[0] + guardDirections[direction][0];
        nextPos[1] = guardPos[1] + guardDirections[direction][1];
        nextPoint = map[nextPos[0]][nextPos[1]];
    }
}

int main(){

    loadMap(map);
    moveGuard(map);
    map[guardPos[0]][guardPos[1]] = 'X';
    printMap(map);
    int count = 0;
    for(int x = 0; x < 130; x++)
    for(int y = 0; y < 130; y++){
        if(map[x][y] != '.' && map[x][y] != '#') count++;
    }
    std::cout << "Count: " << count << '\n';
    std::cout << "X: " << guardPos[0] << " | Y: " << guardPos[1] << '\n';

    return 0;
}