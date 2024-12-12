#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define MAP_WIDTH 54
#define MAP_HEIGHT 54

struct position{
    int x;
    int y;
};

int map[MAP_HEIGHT][MAP_WIDTH];
std::vector<position> starts;

void loadMap(int map[MAP_HEIGHT][MAP_WIDTH]){
    std::ifstream file("../input.txt");
    std::string line;
    int y = 0;
    while(std::getline(file, line)){
        for(int x = 0; x < line.length(); x++){
            map[y][x] = line[x] - int('0');
            if(line[x] == '0'){
                position start; start.x = x; start.y = y;
                starts.push_back(start);
            }
        }
        y++;
    }
}

void printMap(int map[MAP_HEIGHT][MAP_WIDTH]){
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++) std::cout << map[i][j];
        std::cout << '\n';
    }
}

int findTrack(int currentHeight, position currentPos){

    if(map[currentPos.y][currentPos.x] == 9) return 1;
    
    int rating = 0;

    if(currentPos.x + 1 < MAP_WIDTH && map[currentPos.y][currentPos.x + 1] == currentHeight + 1){
        position newPos = currentPos;
        newPos.x++;
        rating += findTrack(currentHeight+1, newPos);
    }
    if(currentPos.x - 1 >= 0 && map[currentPos.y][currentPos.x - 1] == currentHeight + 1){
        position newPos = currentPos;
        newPos.x--;
        rating += findTrack(currentHeight+1, newPos);
    }
    if(currentPos.y + 1 < MAP_HEIGHT && map[currentPos.y + 1][currentPos.x] == currentHeight + 1){
        position newPos = currentPos;
        newPos.y++;
        rating += findTrack(currentHeight+1, newPos);
    }
    if(currentPos.y - 1 >= 0 && map[currentPos.y - 1][currentPos.x] == currentHeight + 1){
        position newPos = currentPos;
        newPos.y--;
        rating += findTrack(currentHeight+1, newPos);
    }
    return rating;
}

int main(){
    loadMap(map);
    printMap(map);
    int finalRating = 0;
    std::vector<position> history;
    for(position start: starts) finalRating += findTrack(0, start);
    std::cout << "Final rating: " << finalRating << '\n';
    return 0;
}