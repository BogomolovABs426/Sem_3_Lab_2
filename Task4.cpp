#include "Array.h"
#include <iostream>

using namespace std;

void sortBlocks(BlockArray& blocks) {
    for (size_t i = 0; i < blocks.size; i++) {
        for (size_t j = i + 1; j < blocks.size; j++) {
            Block a = BlockGet(blocks, i);
            Block b = BlockGet(blocks, j);
            bool shouldSwap = false;

            if (a.width == b.width) {
                if (a.height < b.height) { // при равных ширинах — по убыванию высоты
                    shouldSwap = true;
                }
            } else {
                if (a.width < b.width) { // по убыванию ширины
                    shouldSwap = true;
                }
            }

            if (shouldSwap) {
                Block temp = a;
                
                blocks.data[i] = b;
                blocks.data[j] = temp;
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    BlockArray blocks;
    for (int i = 0; i < N; i++) {
        Block b;
        cin >> b.width >> b.height;
        BlockPush(blocks, b);
    }

    sortBlocks(blocks);

    IntArray dp;
    int result = 0;

    for (size_t i = 0; i < blocks.size; i++) {
        Block current = BlockGet(blocks, i);
        int currentMax = current.height;

        for (size_t j = 0; j < i; j++) {
            Block prev = BlockGet(blocks, j);
            if (current.width < prev.width) {
                int potential = IntGet(dp, j) + current.height;
                if (potential > currentMax) {
                    currentMax = potential;
                }
            }
        }

        IntPush(dp, static_cast<int>(currentMax));
        if (currentMax > result) {
            result = currentMax;
        }
    }

    cout << result << endl;

    BlockClear(blocks);
    IntClear(dp);
    return 0;
}
