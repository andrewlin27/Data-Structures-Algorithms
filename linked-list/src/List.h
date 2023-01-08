#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() : node{nullptr} {};
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            return node->data;
        }

        pointer operator->() const {
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            node = node->next;
            return *this;
        }
        
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            basic_iterator temp = basic_iterator(node);
            node = node->next;
            return temp;
        }

        // Prefix Decrement: --a
        basic_iterator& operator--() {
            node = node->prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            basic_iterator temp = basic_iterator(node);
            node = node->prev;
            return temp;
        }

        bool operator==(const basic_iterator& other) const noexcept {
            return (node == other.node);
        }

        bool operator!=(const basic_iterator& other) const noexcept {
            return (node != other.node);
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head{0}, tail{0}, _size{0} {
        head.next = &tail;
        tail.prev = &head;
    }

    List( size_type count, const T& value ) : _size{0} {
        head.next = &tail;
        tail.prev = &head;
        for (size_type i = 0; i < count; i++) {
            insert(cbegin(), value);
        }
    }
    
    explicit List( size_type count ) : _size{0} {
        head.next = &tail;
        tail.prev = &head;
        for (size_type i = 0; i < count; i++) {
            insert(cbegin(), T());
        }
    }

    List( const List& other ) : head{0}, tail{0}, _size{0} {
        head.next = &tail;
        tail.prev = &head;
        Node* curr = other.head.next;
        while (curr != &(other.tail)) {
            this->push_back(curr->data);
            curr = curr->next;
        }
    }

    List( List&& other ) : head{0}, tail{0}, _size{other._size} {
        head.next = other.head.next;
        tail.prev = other.tail.prev;
        other.head.next->prev = &head;
        other.tail.prev->next = &tail;
        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        other._size = 0;
    }

    ~List() {
        clear();
    }

    List& operator=( const List& other ) {
        if (this == &other) {
            return *this;
        }
        clear();
        Node* curr = other.head.next;
        while (curr != &(other.tail)) {
            this->push_back(curr->data);
            curr = curr->next;
        }
        return *this;
    }

    List& operator=( List&& other ) noexcept {
        if (this == &other) {
            return *this;
        }
        clear();
        head.next = other.head.next;
        tail.prev = other.tail.prev;
        other.head.next->prev = &head;
        other.tail.prev->next = &tail;
        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        _size = other._size;
        other._size = 0;
        return *this;
    }

    reference front() {
        return reference(head.next->data);
    }

    const_reference front() const {
        return const_reference(head.next->data);
    }
	
    reference back() {
        return reference(tail.prev->data);
    }

    const_reference back() const {
        return const_reference(tail.prev->data);
    }
	
    iterator begin() noexcept {
        return iterator(head.next);
    }

    const_iterator begin() const noexcept {
        return const_iterator(head.next);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(head.next);
    }

    iterator end() noexcept {
        return iterator(&tail);
    }

    const_iterator end() const noexcept {
        return const_iterator(&tail);
    }

    const_iterator cend() const noexcept {
        return const_iterator(&tail);
    }

    bool empty() const noexcept {
        return head.next == &tail;
    }

    size_type size() const noexcept {
        return _size;
    }

    void clear() noexcept {
        while (!(this->empty())) {
            this->pop_front();
        }
    }

    iterator insert( const_iterator pos, const T& value ) {
        Node* newNode = new Node(value, pos.node->prev, pos.node);
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;
        _size++;
        return iterator(newNode);
    }

    iterator insert( const_iterator pos, T&& value ) {
        Node* newNode = new Node(std::move(value), pos.node->prev, pos.node);
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;
        _size++;
        return iterator(newNode);
    }

    iterator erase( const_iterator pos ) {
        pos.node->prev->next = pos.node->next;
        pos.node->next->prev = pos.node->prev;
        iterator returnVal = iterator(pos.node->next);
        delete pos.node;
        _size = _size - 1;
        return returnVal;
    }

    void push_back( const T& value ) {
        insert(const_iterator(&tail), value);
    }

    void push_back( T&& value ) {
        insert(const_iterator(&tail), std::move(value));
    }

    void pop_back() {
        erase(const_iterator(tail.prev));
    }
	
    void push_front( const T& value ) {
        insert(const_iterator(head.next), value);
    }

	void push_front( T&& value ) {
        insert(const_iterator(head.next), std::move(value));
    }

    void pop_front() {
        erase(const_iterator(head.next));
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}