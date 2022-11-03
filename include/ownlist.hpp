#ifndef H_OWNLIST
#define H_OWNLIST

#include <memory>


class Iterator;


template<typename T>
class Node{
public:
    explicit Node() : _next(nullptr){}

    explicit Node(T const &data) : _data(data), _next(nullptr) {}

    Node * _next;

    T _data;

};


template<typename T, class Allocator = std::allocator<Node<T> > >
class ownList{
private:
    Allocator _alloc;

    Node<T> * _head = nullptr;
    Node<T> * _tail = nullptr; 

    std::size_t _size;

    class Iterator {
        private:
            Node<T> *_node{ };
        
        public:
            explicit Iterator(Node<T>* node) : _node(node) { }

            bool operator==(Iterator const &other) {
                return this == &other || this->_node == other._node;
            }

            bool operator!=(Iterator const &other) {
                return !operator==(other);
            }

            void operator++(){
                if(this->_node)
                    this->_node = _node->_next;
            }

            T operator*() {
                if(this->_node)
                    return _node->_data;
                return T();
            }

    };

public:
    using value_type = T;
    using allocator_type = Allocator;
    /* using pointer = std::allocator_traits<Allocator>::pointer;
    using const_pointer = std::allocator_traits<Allocator>::const_pointer; */
    using reference = T &;
    using const_referenc = const T &;
    using size_type = std::size_t;

    ownList() : _head(nullptr) {}

    ~ownList() {
        while (_head){
            this->clear();
        }
    }

    allocator_type get_allocator() {
        return _alloc;
    }

    void emplace(const T &value) {
        if(auto node = this->_alloc.allocate(1)) {
            this->_size++;
            this->_alloc.construct(node, value);
            if(_head) {
                _tail->_next = node;
            } else {
                _head = node;
                node->_next = nullptr;
            }
            _tail = node;
        }
    }

    void assign(size_type count, const T& value) {
        this->clear();
        for(size_type i = 0; i < count; ++i)
            this->emplace(value);
    }

    void clear() {
        if(this->_head) {
            auto next = this->_head->_next;
            
            this->_alloc.destroy(_head);
            
            this->_alloc.deallocate(_head, 1);
            _head = next;
        }
        this->_size = 0;
    }

    Iterator begin() const {
        return Iterator(_head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

};


#endif