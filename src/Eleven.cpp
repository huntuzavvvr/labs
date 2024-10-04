#include "../include/Eleven.h"
#include <string>
#include <iostream>
#include <cmath>
#include <exception>

void check_num(unsigned char& num){
    if (!((num >= '0' && num <= '9') || num == 'A')){
        throw std::invalid_argument("Invalid symbol");
    }
}

void check_size(const size_t& s){
    if (s == 0){
        throw std::invalid_argument("Invalid size");
    }
}

unsigned char* memory_alloc(size_t size){
    unsigned char* data = new unsigned char[size]{0};
    return data;
}

void Eleven::delete_zero(){
    bool flag = 0;
    for (size_t i{0}; i < size; ++i){
        if (data[i] != '0'){
            size -= i;
            unsigned char* data_result = new unsigned char[size];
            std::copy(data + i, data + i + size, data_result);
            flag = 1;
            delete [] data;
            data = data_result;
            break;
        }
    }
    if (!flag){
        data[0] = '0';
        size = 1;
    }
}

Eleven::Eleven() : size{1}, data{nullptr} {
    data = memory_alloc(size);
    data[0] = '0';
    delete_zero();
};

Eleven::Eleven(const size_t& n, unsigned char num) : size{n}, data{nullptr} {
    check_num(num);
    check_size(size);
    data = memory_alloc(size);  
    std::fill(data, data + size, num);
    delete_zero();
}

Eleven::Eleven(const std::initializer_list<unsigned char> &num) : size(num.size()){
    check_size(size);
    for (unsigned char i : num){
        check_num(i);
    }
    data = memory_alloc(size);
    std::copy(num.begin(), num.end(), data);
    delete_zero();
}

Eleven::Eleven(const std::string &str) : size(str.size()){
    check_size(size);
    for (unsigned char i : str){
        check_num(i);
    }
    data = memory_alloc(size);
    std::copy(str.begin(), str.end(), data);
    delete_zero();
}

Eleven::Eleven(const Eleven& other) : size(other.get_size()) {
    data = memory_alloc(size);
    std::copy(other.get_data(), other.get_data() + other.get_size(), data);
}

Eleven::Eleven(Eleven&& other) noexcept : size{other.get_size()}{
    data = other.data;
    other.size = 0;
    other.data = nullptr;
}

Eleven::~Eleven(){
    delete [] data;
    data = nullptr;
    size = 0;
}

size_t Eleven::get_size() const{
    return size;
}

unsigned char* Eleven::get_data() const{
    return data;
}

Eleven& Eleven::operator+=(const Eleven& other){
    size_t size_max = std::max(size, other.get_size()) + 1;
    unsigned char* data_result = new unsigned char[size_max];
    int sum = 0;
    for (size_t i = 0; i < size_max; ++i){
        if (i < size){
            if (data[size - i - 1] == 'A'){
                sum += 10;
            }
            else{
                sum += data[size - i - 1] - '0';
            }
        }
        if (i < other.get_size()){
            if (other.get_data()[other.get_size() - i - 1] == 'A'){
                sum += 10;
            }
            else{
                sum += other.get_data()[other.get_size() - i - 1] - '0';
            }

        }

        if (sum % 11 == 10){
            data_result[size_max - i - 1] = 'A';
        }
        else{
            data_result[size_max - i - 1] = (sum % 11) + '0';
        }
        sum /= 11;
    }
    size = size_max;
    delete []data;
    data = data_result;
    delete_zero();
    return *this;
}

Eleven& Eleven::operator-=(const Eleven& other){
    size_t size_max = std::max(size, other.get_size());
    unsigned char* data_result = new unsigned char[size_max];
    int sum = 0;
    for (size_t i{0}; i < size_max; ++i){
        if (i < size){
            if (data[size - i - 1] == 'A'){
                sum += 10;
            }
            else{
                sum += data[size - i - 1] - '0';
            }
        }
        if (i < other.get_size()){
            if (other.get_data()[other.get_size() - i - 1] == 'A'){
                sum -= 10;
            }
            else{
                sum -= other.get_data()[other.get_size() - i - 1] - '0';
            }
        }
        if (sum < 0){
            sum += 11;
            if (sum == 10) data_result[size - i - 1] = 'A';
            else data_result[size - i - 1] = abs(sum) + '0';
            sum = -1;
        }
        else{
            if (sum == 10) data_result[size - i - 1] = 'A';
            else data_result[size - i - 1] = sum + '0';
            sum = 0;
        }
    }
    
    size = size_max;
    delete []data;
    data = data_result;
    delete_zero();
    return *this;
}

Eleven& Eleven::operator=(const Eleven& other){
    size = other.get_size();
    data = memory_alloc(size);
    std::copy(other.get_data(), other.get_data() + size, data);
    return *this;
}

bool Eleven::operator>(const Eleven& other) const {
    if (size > other.get_size()){
        return true;
    }
    else if (size < other.get_size()){
        return false;
    }
    else{
        for (size_t i{0}; i < size; ++i){
            if ((data[i] > other.get_data()[i])){
                return true;
            }
            else if((data[i] <= other.get_data()[i])){
                return false;
            }
        }
    }
}

bool Eleven::operator<(const Eleven& other) const {
    if (size < other.get_size()){
        return true;
    }
    else if (size > other.get_size()){

        return false;
    }
    else{
        for (int i{0}; i < size; ++i){
            if ((data[i] < other.get_data()[i])){
                return true;
            }
            else if((data[i] > other.get_data()[i])){
                return false;
            }
        }
    }
    return false;
}

bool Eleven::operator==(const Eleven& other) const{
    if (size != other.get_size()){
        return false;
    }
    for (size_t i{0}; i < size; ++i){
        if (data[i] != other.get_data()[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& ost, const Eleven& num){
    for (size_t i = 0; i < num.get_size(); ++i){
        ost << num.get_data()[i];
    }
    return ost;
}