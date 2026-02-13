#include "Array.h"
#include <iostream>
#include <stdexcept>

void IntPush(IntArray& arr, int value) {
    if (arr.size >= arr.capacity) {
        size_t newCap = arr.capacity ? arr.capacity * 2 : 4;
        int* newData = new int[newCap];
        for (size_t i = 0; i < arr.size; i++) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
    arr.data[arr.size] = value;
    arr.size++;
}

int IntGet(const IntArray& arr, int index) {
    if (index < 0 || static_cast<size_t>(index) >= arr.size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return arr.data[index];
}

void IntClear(IntArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = arr.capacity = 0;
}

void BlockPush(BlockArray& arr, const Block& block) {
    if (arr.size >= arr.capacity) {
        size_t newCap = arr.capacity ? arr.capacity * 2 : 4;
        Block* newData = new Block[newCap];
        for (size_t i = 0; i < arr.size; i++) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
    arr.data[arr.size] = block;
    arr.size++;
}

Block BlockGet(const BlockArray& arr, int index) {
    if (index < 0 || static_cast<size_t>(index) >= arr.size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return arr.data[index];
}

void BlockClear(BlockArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = arr.capacity = 0;
}
