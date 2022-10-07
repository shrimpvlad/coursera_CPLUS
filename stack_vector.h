#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : size(a_size)
    {
        if (size > N)
            throw invalid_argument("too much");
    }

    T& operator[](size_t index)
    {
        return arr[index];
    }
    const T& operator[](size_t index) const
    {
        return arr[index];
    }
    T* begin()
    {
        return arr.begin();
    }
    T* end()
    {
        return arr.begin() + size;
    }
    const T* begin() const
    {
        return arr.begin();
    }
    const T* end() const
    {
        return arr.begin() + size;
    }

    size_t Size() const
    {
        return size;
    }
    size_t Capacity() const
    {
        return N;
    }

    void PushBack(const T& value)
    {
        if (size == N)
            throw overflow_error("full array");
        arr[size++] = value;
    }
    T PopBack()
    {
        if (size == 0)
            throw underflow_error("empty");
        --size;
        return arr[size];
    }

private:
    size_t size;
    array<T, N> arr;
};

