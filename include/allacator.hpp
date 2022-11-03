#ifndef H_ALLACATOR
#define H_ALLACATOR

#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <array>
#include <map>

#define DEBUG_MSG 1

int factorial(int num);



template<class T, std::size_t Num = 10, bool isExtendable = false>
class ownAllocator
{
private:
    T *ptr = nullptr;
    T *ptr_head = nullptr;

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

    explicit ownAllocator(int ) noexcept {}

    template<typename X>
    explicit ownAllocator(const ownAllocator<X> ) noexcept {}

    ~ownAllocator() {
        if(!ptr)
            ::operator delete(ptr);
        ptr = nullptr;
    } 

    T *allocate(std::size_t n) {
        if (!ptr_head) {
            if(n > Num && !isExtendable)
                throw std::bad_alloc();
            ptr = reinterpret_cast<T *>(::operator new(n * sizeof(T)));
            if (!ptr)
                throw std::bad_alloc();
            ptr_head = ptr;
            return ptr;
        } else {
            return ptr++;
        }
    }

    void reserve(std::size_t size) {
        if (size)
            allocate(size);
    }

    template<class U>
    struct rebind {
        typedef ownAllocator<U> other;
    };

    void deallocate(T *p, std::size_t) {
        if (p == ptr_head) {// if there's not a pool, nothing to do
            ::operator delete(ptr_head);
            ptr_head = nullptr;
        }
    }

    template<typename U, typename ... Args>
    void construct(U *p, Args &&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }
};


#endif