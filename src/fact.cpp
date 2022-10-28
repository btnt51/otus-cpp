#include "../include/allacator.hpp"


int factorial(int num) {
    if(num == 0)
        return 1;
    return num * factorial(num-1);
}