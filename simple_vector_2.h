#include <cstdint>
#include <iostream>
#include <iterator>
using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }
    void PushBack(T value);

    // При необходимости перегрузите
    // существующие публичные методы

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : data_(new T[size]),size_(size), capacity_(size)
{
}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] data_;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{
//    if (index > size_)
//        throw out_of_range("index is out of range");
//    else
        return data_[index];
}

template <typename T>
T* SimpleVector<T>::begin()
{
    return data_;
}

template <typename T>
T* SimpleVector<T>::end()
{
    return data_ + size_;
}

template <typename T>
void SimpleVector<T>::PushBack(T value)
{
    if (size_>=capacity_)
    {
        auto new_cap = capacity_ == 0 ? 1 : 2 * capacity_;
        auto new_data = new T[new_cap];
        move(begin(), end(), new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }
    data_[size_++] = move(value);
}
