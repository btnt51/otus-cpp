#ifndef H_ALLACATOR
#define H_ALLACATOR

#include <cmath>
#include <vector>
#include <map>
#include <iostream>

#define DEBUG_MSG 1

int factorial(int num);

template<typename T, std::size_t N >
class Basic_Allocator
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using const_void_pointer = const void *;
    using reference = T &;
    using const_referenc = const T &;
    using void_pointer = void *;
    using size_type = std::size_t;

    template<typename U>
    class rebind{
    public:
        using other = Basic_Allocator<U, N>;
    };

    Basic_Allocator() {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        memoryPointer = allocate(N);
    }

    ~Basic_Allocator() {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        deallocate(memoryPointer, N);
    }

    T* allocate(std::size_t n) {
        if(!memoryPointer) {
            auto * pointer = std::malloc(sizeof(T) * N);
#ifdef DEBUG_MSG
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif     
            return reinterpret_cast<T *>(pointer);
        }

        if(n > N)
            throw std::bad_alloc();
        return memoryPointer;
    }

    void deallocate(T* pointer, std::size_t) {
        if(!pointer)
            std::free(pointer);
    }

    template<typename U, typename ...Args>
    void construct(U *pointer,Args &&...args) {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "pointer= " << pointer << std::endl;
#endif
        new(pointer) U(std::forward<Args>(args)...);
    } 

protected:
    T *memoryPointer = nullptr;
};


template <typename T, size_t N = 2>
class Extended_Allocator{
public:

    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using const_void_pointer = const void *;
    using reference = T &;
    using const_referenc = const T &;
    using void_pointer = void *;
    using size_type = std::size_t;

    template<typename U>
    class rebind{
    public:
        using other = Extended_Allocator<U, N>;
    };

    Extended_Allocator() {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        memoryPointer = allocate(N+1);
    }

    ~Extended_Allocator() {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        /* for(size_t i = 0; i < N*sizeof(T); i += sizeof(T)) {
            destroy(memoryPointer+i);
        } */
        deallocate(memoryPointer, N);
    }

    T* allocate(std::size_t n){
        if(n > N) {
            std::free(memoryPointer);
            memoryPointer = static_cast<T*>(std::malloc(sizeof(T) * (N*sizeof(T))));
            if(!memoryPointer)
                throw std::bad_alloc();
            
#ifdef DEBUG_MSG
            std::cout << __PRETTY_FUNCTION__ << "[N*n = " << (n*N)/2 << "]" << std::endl;
            std::cout << __PRETTY_FUNCTION__ << "pointer size= " << sizeof(this->memoryPointer) << std::endl;
#endif  
        }
       // std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        if(!memoryPointer)
            throw std::bad_alloc();
        
        return reinterpret_cast<T *>(memoryPointer); 
    }

    template<typename U>
    void destroy(U *pointer) {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        pointer->~U();
    }

    void deallocate(T* pointer, std::size_t) {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        if(!pointer)
            std::free(pointer);
    }

    template<typename U, typename ...Args>
    void construct(U *pointer, Args &&...args) {
#ifdef DEBUG_MSG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "pointer= " << pointer << std::endl;
#endif
        new(pointer) U(std::forward<Args>(args)...);
    } 

protected:
    T *memoryPointer = nullptr;

};


template<typename T, std::size_t NUM, bool isExtendable>
class myPool {
public:


private:
    

};

template<typename T, size_t Num = 2>
class AllocatorWithPull{
public:


private:
    static MyPool Pool;

};



#endif