#include <iostream>
#include <string>
#include <fstream>
#include <list>

struct file{
    int id;
    int size;
};

std::string data;

void loadData(){
    std::ifstream file("../input.txt");
    getline(file, data);
}

int ctoi(char number){
    if(int(number) < int('0') || int('9') < int(number)){
        std::cout << "ERROR! Entry is not a number.\n";
        return 0;
    }
    return int(number) - int('0');
}

std::list<file> computeDisk(){
    std::list<file> list;

    file firstFile; firstFile.id = 0; firstFile.size = ctoi(data[0]);
    list.push_back(firstFile);

    for(int i = 0; i < (data.length()-1)/2; i++){
        file empty; empty.id = -1; empty.size = ctoi(data[2*i+1]);
        list.push_back(empty);

        file newFile; newFile.id = i+1; newFile.size = ctoi(data[2*i+2]);
        list.push_back(newFile);
    }
    return list;
}

void printDisk(std::list<file> disk){
    for(file file: disk){
        for(int i = 0; i <= file.size - 1; ++i){
            if(file.id == -1) std::cout << '.';
            else std::cout << file.id;
        }
    }
    std::cout << "\n\n";
}

std::list<file> arrangeStorage(std::list<file> disk){
    auto it = disk.begin();

    while(it != disk.end()) {
        if (it->id == -1) {
            auto subIt = --disk.end();
            while(subIt != it){
                if(subIt->size == it->size && subIt->id != -1){
                    *it = *subIt;
                    subIt->id = -1;
                    break;
                }
                if(subIt->size <= it->size && subIt->id != -1){
                    it->size -= subIt->size;
                    disk.insert(it, *subIt);
                    subIt->id = -1;
                    break;
                }
                --subIt;
                if(subIt == it){
                    it++;
                    break;
                }
            }

            while (!disk.empty() && disk.back().id == -1) disk.pop_back();
            auto previous = disk.begin();
            for(auto subIt = (++disk.begin()); subIt != disk.end(); ++subIt){
                if(subIt->id == -1 && previous->id == -1){
                    subIt->size += previous->size;
                    disk.erase(previous);
                }
                previous = subIt;
            }

        } 

        else ++it;
    }

    return disk;
}

unsigned long long computeChecksum(std::list<file> disk){
    auto it = disk.begin();
    long index = 0;
    unsigned long long sum = 0;

    while(it != disk.end()){

        if(it->id == -1) {
            ++it;
            continue;
        }
        for(int i = 0; i < it->size; i++){
            sum += index*it->id;
            index++;
        }

        ++it;
    } 

    return sum;
}


int main(){
    std::list<file> disk;
    loadData();
    disk = computeDisk();
    printDisk(disk);
    disk = arrangeStorage(disk);
    printDisk(disk);
    std::cout << "Count: " << computeChecksum(disk) << '\n';
    return 0;
}