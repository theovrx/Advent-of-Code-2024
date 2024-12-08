#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>

#define MAP_HEIGHT 50
#define MAP_WIDTH 50

std::string map[MAP_HEIGHT];
std::unordered_set<char> frequencies;
std::unordered_set<std::string> antinodes;

struct position{
    int x;
    int y;
};


void loadMap(std::string map[MAP_HEIGHT]){
    std::ifstream file("../input.txt");
    std::string line;

    int index = 0;
    while(getline(file, line)){
        map[index] = line;
        index++;
    }
}

void getDifferentFrequencies(std::unordered_set<char> set){
    for(std::string line: map)
    for(char frequency: line){
        if(frequency != '.') frequencies.insert(frequency);
    }

}

std::vector<position> getFrequencyPositions(char frequency, std::string map[MAP_HEIGHT]){
    std::vector<position> positions;

    for(int y = 0; y < MAP_HEIGHT; y++)
    for(int x = 0; x < map[0].length(); x++){
        if (map[y][x] == frequency){
            position temp;
            temp.x = x;
            temp.y = y;
            positions.push_back(temp);
        }
    }
    return positions;
}

void findAntinodes(std::vector<position> positions){
    for(int index1 = 0; index1 < positions.size(); index1++)
    for(int index2 = index1 + 1; index2 < positions.size(); index2++){
        position pos1 = positions.at(index1);
        position pos2 = positions.at(index2);

        int dx = pos2.x - pos1.x;
        int dy = pos2.y - pos1.y;

        position antinode;
        antinode.x = pos1.x - dx;
        antinode.y = pos1.y - dy;
        if(
            0 <= antinode.x 
            && antinode.x < MAP_WIDTH 
            && 0 <= antinode.y 
            && antinode.y < MAP_HEIGHT
        ){
            if(map[antinode.y][antinode.x] == '.') map[antinode.y][antinode.x] == '#';
            antinodes.insert(std::to_string(antinode.x)+" "+std::to_string(antinode.y));
        }

        antinode.x = pos2.x + dx;
        antinode.y = pos2.y + dy;
        if(
            0 <= antinode.x 
            && antinode.x < MAP_WIDTH 
            && 0 <= antinode.y 
            && antinode.y < MAP_HEIGHT
        ){
            if(map[antinode.y][antinode.x] == '.') map[antinode.y][antinode.x] = '#';
            antinodes.insert(std::to_string(antinode.x)+" "+std::to_string(antinode.y));
        }
    }
}

int main(){

    loadMap(map);
    getDifferentFrequencies(frequencies);

    for(char frequency: frequencies){
        std::vector<position> fPos = getFrequencyPositions(frequency, map);
        findAntinodes(fPos);
    }

    for(std::string line: map) std::cout << line << '\n';
    std::cout << "Count: " << antinodes.size() << '\n';
    return 0;
    
}