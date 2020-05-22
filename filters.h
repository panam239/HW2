#pragma once

#include "address.h"
void subfilter(std::vector<Address*>& ip_pool) {
    for(auto a:ip_pool) {
        std::cout << a << std::endl;
    }
}

void subfilter(std::vector<Address*>& v, std::vector<int>& mask){
    for(auto a:v) {
        if(a->isFiltered(mask)) {
            std::cout << a <<std::endl;
        }
    }
}

template<typename...Args>
void filter(std::vector<Address*> v, Args... a){
    std::vector<int> mask{a...};
    subfilter(v, mask);
}

template<>
void filter(std::vector<Address*> v){
    subfilter(v);
}

void filter_any(std::vector<Address*> v, int value) {
    for(auto a:v) {
        if(a->isContains(value)) {
            std::cout << a <<std::endl;
        }
    }
}
