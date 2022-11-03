#ifndef H_ALLACATOR
#define H_ALLACATOR

#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <array>
#include <map>

#define DEBUG_MSG 1

long factorial(long num);



template<class T, std::size_t Num = 10, bool isExtendable = false>
class ownAllocator
{
private:
    T *_pointer = nullptr;
    T *_pointer_head = nullptr;

public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using const_void_pointer = const void *;
    using reference = T &;
    using const_referenc = const T &;
    using void_pointer = void *;
    using size_type = std::size_t;

    ownAllocator() noexcept {
        if (Num)
            allocate(Num);
    }

    explicit ownAllocator(int) noexcept {}

    template<typename X>
    explicit ownAllocator(const ownAllocator<X> ) noexcept {}

    ~ownAllocator() {
        if(!_pointer)
            ::operator delete(_pointer);
        _pointer = nullptr;
    } 

    T *allocate(std::size_t n) {
        if (!_pointer_head) {
            if(n > Num && !isExtendable)
                throw std::bad_alloc();
            _pointer = reinterpret_cast<T *>(::operator new(n * sizeof(T)));
            if (!_pointer)
                throw std::bad_alloc();
            _pointer_head = _pointer;
            return _pointer;
        } else {
            return _pointer++;
        }
    }

    void reserve(std::size_t size) {
        if (size)
            allocate(size);
    }

    template<class U>
    struct rebind {
        using other = ownAllocator<U, Num, isExtendable>;
    };

    void deallocate(T *pointer, std::size_t) {
        if (pointer == _pointer_head) {// if there's not a pool, nothing to do
            ::operator delete(_pointer_head);
            _pointer_head = nullptr;
        }
    }

    template<typename U, typename ... Args>
    void construct(U *pointer, Args &&... args) {
        new(pointer) U(std::forward<Args>(args)...);
    }

    void destroy(T *pointer) {
        pointer->~T();
    }
};


#endif