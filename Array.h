#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>  // для size_t

struct Block {
    int width;
    int height;
};

struct IntArray {
    int* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;  // меняем uint64_t на size_t
};

struct BlockArray {
    Block* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;  // меняем uint64_t на size_t
};

void IntPush(IntArray& arr, int value);
int IntGet(const IntArray& arr, int index);
void IntClear(IntArray& arr);

void BlockPush(BlockArray& arr, const Block& block);
Block BlockGet(const BlockArray& arr, int index);
void BlockClear(BlockArray& arr);

#endif
