#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

struct Block {
    int id;
    int start;
    int size;
};

int main() {
    string layout;
    int64_t checksum = 0;
    list<Block> blocksToProcess;
    list<Block> freeSpace;
    list<Block> finalBlocks;
    
    cin >> layout;

    for(int offset{}; auto [i, lch] : layout | views::enumerate) {
        int size = lch - '0';
        if(i % 2)
            freeSpace.push_back({-1, offset, size});
        else
            blocksToProcess.push_back({(int) i / 2, offset, size});
        offset += size;
    }

    while(!blocksToProcess.empty()) {
        Block block = blocksToProcess.back();
        blocksToProcess.pop_back();

        auto firstFree = find_if(
            freeSpace.begin(), 
            freeSpace.end(), 
            [&block](Block& free){
                return free.size >= block.size 
                    && free.start < block.start;
            }
        );

        // No adequate free space found, keep the file where it is  
        if(firstFree == freeSpace.end()) {
            finalBlocks.push_back(block);
            continue;
        }

        finalBlocks.push_back({block.id, firstFree->start, block.size});

        // Remove or shrink free block after moving the file
        if(block.size == firstFree->size) {
            freeSpace.erase(firstFree);
        } 
        else {
            firstFree->start += block.size;
            firstFree->size -= block.size;
        }
    }

    for(Block& block : finalBlocks) {
        for(int offset = 0; offset < block.size; offset++) {
            checksum += (int64_t) block.id * (block.start + offset);
        }
    }

    cout << checksum << endl;
    return 0;
}