#pragma once

#include <memory_resource>
#include <map>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

class FixedMemoryBlock: public std::pmr::memory_resource {
    private:
        size_t block_size_;
        size_t num_blocks_;
        void* memory_pool_;
        std::map<void*, size_t> allocated_blocks_;
    public:
        FixedMemoryBlock(size_t block_size, size_t num_blocks) : block_size_(block_size), 
        num_blocks_(num_blocks) {
            memory_pool_ = std::malloc(block_size_ * num_blocks_);
            if (!memory_pool_){
                throw std::bad_alloc();
            }
        }
        ~FixedMemoryBlock() override {
            std::free(memory_pool_);
        }
        void* do_allocate(size_t bytes, size_t alignment) override{
            if (bytes > block_size_){
                throw std::bad_alloc();
            }
            if (allocated_blocks_.size() > num_blocks_){
                throw std::bad_alloc();
            }
            void* ptr = nullptr;
            for (size_t i = 0; i < num_blocks_; ++i){
                void* candidate = static_cast<char*>(memory_pool_) + i * block_size_;
                if (allocated_blocks_.find(candidate) == allocated_blocks_.end()){
                    ptr = candidate;
                    break;
                }
            }
            if (!ptr){
                throw std::bad_alloc();
            }
            allocated_blocks_[ptr] = bytes;
            return ptr;
        }

        void do_deallocate(void* ptr, size_t bytes, size_t alignment) override{
            auto it = allocated_blocks_.find(ptr);
            if (it != allocated_blocks_.end()){
                allocated_blocks_.erase(it);
            }
        }

        bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
            return this == &other;
        }
};