#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::range_error

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity;
    size_t _size;

    // You may want to write a function that grows the vector
    void grow() {
        _capacity *= 2;
        if (_capacity == 0) {
            _capacity = 1;
        }
        T* newArray = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            newArray[i] = std::move(array[i]);
        }
        delete[] array;
        array = newArray;
    }

public:
    Vector() noexcept : array{nullptr}, _capacity{0}, _size{0} {}
    
    Vector(size_t count, const T& value) 
        : array{new T[count]}, _capacity{count}, _size{count} {
            for (size_t i = 0; i < count; i++) {
                array[i] = value;
            }
    }

    explicit Vector(size_t count) 
        : array{new T[count]}, _capacity{count}, _size{count} {
            for (size_t i = 0; i < count; i++) {
                array[i] = T();
            }
    }

    Vector(const Vector& other) //copy constructor
        : array{new T[other._size]}, _capacity{other._capacity}, _size{other._size} { //deep copy
            for (size_t i = 0; i < _size; i++) {
                array[i] = other.array[i];
            }
     }

    Vector(Vector&& other) noexcept //move constructor
        : array{other.array}, _capacity{other._capacity}, _size{other._size} { //shallow copy
            other._capacity = 0;
            other._size = 0;
            other.array = nullptr;
    }

    ~Vector() {
        delete[] array;
        array = nullptr;
        _size = 0;
        _capacity = 0;
    }

    Vector& operator=(const Vector& other) { //copy assignment operator
        if (this == &other) { 
            return *this;
        }
        _size = other._size;
        _capacity = other._capacity;
        delete[] array;
        T* p = new T[_size];
        for (size_t i = 0; i < _size; i++) {
            p[i] = other.array[i];
        }
        array = p;
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] array;

        _size = other._size;
        _capacity = other._capacity;
        array = other.array;

        other._capacity = 0;
        other._size = 0;
        other.array = nullptr;

        return *this;
    }

    iterator begin() noexcept {
        return iterator(&array[0]);
    }

    iterator end() noexcept {
        return iterator(&array[_size]);
    }

    [[nodiscard]] bool empty() const noexcept {
        return (_size == 0);
    }

    size_t size() const noexcept {
        return _size;
    }

    size_t capacity() const noexcept {
        return _capacity;
    }

    T& at(size_t pos) {
        if (!(pos < _size)) {
            throw std::out_of_range("at: out of range");
        }
        return ((*this)[pos]);
    }

    const T& at(size_t pos) const {
        if (!(pos < _size)) {
            throw std::out_of_range("at: out of range");
        }
        return ((*this)[pos]);
    }

    T& operator[](size_t pos) {
        return array[pos];
    }

    const T& operator[](size_t pos) const {
        return array[pos];
    }

    T& front() {
        return array[0];
    }

    const T& front() const {
        return array[0];
    }

    T& back() {
        return array[_size - 1];
    }

    const T& back() const {
        return array[_size - 1];
    }

    void push_back(const T& value) {
        if (_size + 1 > _capacity) {
            this->grow();
        }
        array[_size] = value;
        _size += 1;
    }

    void push_back(T&& value) {
        if (_size + 1 > _capacity) {
            this->grow();
        }
        array[_size] = std::move(value);
        _size += 1;
    }

    void pop_back() {
        array[_size - 1] = T();
        _size -= 1;
    }

    iterator insert(iterator pos, const T& value) {
        size_t index = pos - begin();
        if (_size + 1 > _capacity) {
            this->grow();
        }
        for (size_t i = _size; i > index; i--) {
            array[i] = std::move(array[i - 1]);
        }
        array[index] = value;
        _size++;
        return iterator(&(array[index]));
    }

    iterator insert(iterator pos, T&& value) {
        size_t index = pos - begin();
        if (_size + 1 > _capacity) {
            this->grow();
        }
        for (size_t i = _size; i > index; i--) {
            array[i] = std::move(array[i - 1]);
        }
        array[index] = std::move(value);
        _size++;
        return iterator(&(array[index]));
    }

    iterator insert(iterator pos, size_t count, const T& value) {
        if (count == 0) {
            return pos;
        }
        size_t index = pos - begin();
        while (_size + count > _capacity) {
            this->grow();
        }
        for (size_t i = _size + count - 1; i >= index + count; i--) {
            array[i] = std::move(array[i - count]);
        }
        for (size_t i = 0; i < count; i++) {
            array[index + i] = value;
        }
        _size += count;
        return iterator(&(array[index]));


    }

    iterator erase(iterator pos) {
        size_t index = pos - begin();
        for (size_t i = index; i < _size - 1; i++) {
            array[i] = std::move(array[i + 1]);
        }
        _size--;
        return iterator(&(array[index]));
    }

    iterator erase(iterator first, iterator last) { /* TODO */ }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
        pointer ptr;
    public:
        iterator() : ptr{nullptr} {}
        // Add any constructors that you may need

        iterator(pointer address) : ptr(address) {}

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { 
            return *ptr;
        }

        [[nodiscard]] pointer operator->() const noexcept { 
            return ptr;
         }

        // Prefix Increment: ++a
        iterator& operator++() noexcept {
            ++ptr;
            return *this;
        }

        // Postfix Increment: a++
        iterator operator++(int) noexcept {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Prefix Decrement: --a
        iterator& operator--() noexcept {
            --ptr;
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        iterator& operator+=(difference_type offset) noexcept {
            ptr += offset;
            return *this;
        }

        [[nodiscard]] iterator operator+(difference_type offset) const noexcept {
            iterator copy = *this;
            return copy += offset;
        }
        
        iterator& operator-=(difference_type offset) noexcept {
            ptr -= offset;
            return *this;
        }

        [[nodiscard]] iterator operator-(difference_type offset) const noexcept {
            iterator copy = *this;
            return copy -= offset;
        }
        
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept {
            return ptr - rhs.ptr;
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept {
            return *(ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept {
            return (ptr == rhs.ptr);
        }

        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept {
            return (ptr != rhs.ptr); 
        }

        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept {
            return (ptr < rhs.ptr);
        }

        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept {
            return (ptr > rhs.ptr);
        }

        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept {
            return (ptr <= rhs.ptr);
        }

        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept {
            return (ptr >= rhs.ptr);
        }
    };


    void clear() noexcept {
        _size = 0;
        array = nullptr;
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept { /* TODO */ }

#endif
