#include "include/list.hpp"
#include "include/allocator.hpp"
#include <iostream>
#include <memory_resource>

struct my_struct {
    int age;
    double weight;
};

int main() {
    FixedMemoryBlock mem_resource(128, 10);
    std::pmr::polymorphic_allocator<int> int_alloc(&mem_resource);
    List<int> int_list(int_alloc);
    int_list.PushBack(100);
    int_list.PushBack(111);

    for (auto value : int_list) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;
    std::pmr::polymorphic_allocator<my_struct> struct_alloc(&mem_resource);
    List<my_struct> struct_list(struct_alloc);
    struct_list.PushBack(my_struct{10, 35});
    struct_list.PushBack(my_struct{30, 88});

    for (auto& item : struct_list) {
        std::cout << "age: " << item.age << ", weight: " << item.weight << std::endl;
    }

    return 0;
}