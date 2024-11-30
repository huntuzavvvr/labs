#pragma once

#include <memory_resource>
#include <iterator>
#include <initializer_list>
#include <concepts>
#include <memory>

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
    requires std::is_default_constructible_v<T> && std::is_same_v<Allocator, std::pmr::polymorphic_allocator<T>>
class List {
private:
    struct Node {
        T value_;
        Node* prev_;
        Node* next_;

        explicit Node(const T& value) : value_(value), prev_(nullptr), next_(nullptr) {}
    };

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        ListIterator& operator++() {
            node_ = node_->next_;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() const {
            return node_->value_;
        }

        pointer operator->() const {
            return &node_->value_;
        }

        bool operator==(const ListIterator& other) const {
            return node_ == other.node_;
        }

        bool operator!=(const ListIterator& other) const {
            return node_ != other.node_;
        }

    private:
        Node* node_;
        explicit ListIterator(Node* node) : node_(node) {}

        friend class List;
    };

    List(Allocator alloc = Allocator{}) 
        : alloc_(alloc), head_(nullptr), tail_(nullptr), sz_(0) {}

    List(size_t sz, Allocator alloc = Allocator{}) 
        : List(alloc) {
        for (size_t i = 0; i < sz; ++i) {
            PushBack(T());
        }
    }

    List(const std::initializer_list<T>& items, Allocator alloc = Allocator{}) 
        : List(alloc) {
        for (const auto& item : items) {
            PushBack(item);
        }
    }

    List(const List& other) 
        : List(other.alloc_) {
        for (const auto& item : other) {
            PushBack(item);
        }
    }

    List(List&& other) noexcept 
        : alloc_(std::move(other.alloc_)), head_(other.head_), tail_(other.tail_), sz_(other.sz_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.sz_ = 0;
    }

    ~List() {
        clear();
    }

    ListIterator begin() const noexcept {
        return ListIterator(head_);
    }

    ListIterator end() const noexcept {
        return ListIterator(nullptr);
    }

    T& Front() const {
        return head_->value_;
    }

    T& Back() const {
        return tail_->value_;
    }

    bool IsEmpty() const noexcept {
        return head_ == nullptr;
    }

    size_t Size() const noexcept {
        return sz_;
    }

    ListIterator Find(const T& value) const {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return end();
    }

    void Erase(ListIterator pos) {
        Node* cur_node = pos.node_;
        if (cur_node == head_) {
            PopFront();
        } else if (cur_node == tail_) {
            PopBack();
        } else {
            Node* prev = cur_node->prev_;
            Node* next = cur_node->next_;
            prev->next_ = next;
            next->prev_ = prev;
            destroyNode(cur_node);
            --sz_;
        }
    }

    void Insert(ListIterator pos, const T& value) {
        Node* cur_node = pos.node_;
        if (cur_node == head_) {
            PushFront(value);
        } else {
            Node* new_node = createNode(value);
            Node* prev = cur_node->prev_;
            new_node->prev_ = prev;
            new_node->next_ = cur_node;
            prev->next_ = new_node;
            cur_node->prev_ = new_node;
            ++sz_;
        }
    }

    void PushBack(const T& value) {
        Node* new_node = createNode(value);
        if (tail_) {
            tail_->next_ = new_node;
            new_node->prev_ = tail_;
            tail_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++sz_;
    }

    void PushFront(const T& value) {
        Node* new_node = createNode(value);
        if (head_) {
            head_->prev_ = new_node;
            new_node->next_ = head_;
            head_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++sz_;
    }

    void PopBack() {
        if (!tail_) return;
        if (head_ == tail_) {
            destroyNode(tail_);
            head_ = tail_ = nullptr;
        } else {
            Node* tmp = tail_->prev_;
            tmp->next_ = nullptr;
            destroyNode(tail_);
            tail_ = tmp;
        }
        --sz_;
    }

    void PopFront() {
        if (!head_) return;
        if (head_ == tail_) {
            destroyNode(head_);
            head_ = tail_ = nullptr;
        } else {
            Node* tmp = head_->next_;
            tmp->prev_ = nullptr;
            destroyNode(head_);
            head_ = tmp;
        }
        --sz_;
    }

    void clear() {
        while (head_) {
            PopFront();
        }
    }

private:
    NodeAllocator alloc_;
    Node* head_;
    Node* tail_;
    size_t sz_;

    Node* createNode(const T& value) {
        Node* node = NodeAllocatorTraits::allocate(alloc_, 1);
        NodeAllocatorTraits::construct(alloc_, node, value);
        return node;
    }

    void destroyNode(Node* node) {
        NodeAllocatorTraits::destroy(alloc_, node);
        NodeAllocatorTraits::deallocate(alloc_, node, 1);
    }
};