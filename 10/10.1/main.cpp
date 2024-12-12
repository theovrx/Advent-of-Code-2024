#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>

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

std::unordered_set<std::string> findTrack(int currentHeight, position currentPos){
    std::unordered_set<std::string> result;

    if(map[currentPos.y][currentPos.x] == 9){
        result.insert(std::to_string(currentPos.x) + " " + std::to_string(currentPos.y));
        return result;
    }
    
    if(currentPos.x + 1 < MAP_WIDTH && map[currentPos.y][currentPos.x + 1] == currentHeight + 1){
        position newPos = currentPos;
        newPos.x++;
        for(std::string point:findTrack(currentHeight+1, newPos)) result.insert(point);
    }
    if(currentPos.x - 1 >= 0 && map[currentPos.y][currentPos.x - 1] == currentHeight + 1){
        position newPos = currentPos;
        newPos.x--;
        for(std::string point:findTrack(currentHeight+1, newPos)) result.insert(point);
    }
    if(currentPos.y + 1 < MAP_HEIGHT && map[currentPos.y + 1][currentPos.x] == currentHeight + 1){
        position newPos = currentPos;
        newPos.y++;
        for(std::string point:findTrack(currentHeight+1, newPos)) result.insert(point);
    }
    if(currentPos.y - 1 >= 0 && map[currentPos.y - 1][currentPos.x] == currentHeight + 1){
        position newPos = currentPos;
        newPos.y--;
        for(std::string point:findTrack(currentHeight+1, newPos)) result.insert(point);
    }
    return result;
}

int main(){
    loadMap(map);
    printMap(map);
    int finalScore = 0;
    std::vector<position> history;
    for(position start: starts) finalScore += findTrack(0, start).size();
    std::cout << "Final score: " << finalScore << '\n';
    return 0;
}