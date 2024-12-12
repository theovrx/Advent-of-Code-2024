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
    auto it = --disk.end();

    while(it != disk.begin()) {
        if(it->id == -1){
            --it;
            continue;
        }
        auto subIt = disk.begin();
        while(subIt != it){
            if(subIt->size == it->size && subIt->id == -1){
                *subIt = *it;
                it->id = -1;
                break;
            }
            if(subIt->size >= it->size && subIt->id == -1){
                subIt->size -= it->size;
                file temp = *it;
                it->id = -1;
                disk.insert(subIt, temp);
                break;
            }
            ++subIt;
        }
        
        --it;
    }

    return disk;
}

unsigned long long computeChecksum(std::list<file> disk){
    auto it = disk.begin();
    long index = 0;
    unsigned long long sum = 0;

    while(it != disk.end()){

        if(it->id == -1) {
            index += it->size;
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
