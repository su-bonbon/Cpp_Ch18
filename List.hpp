/// @file List.hpp
/// @author Sujin Lee
/// @date 4/020/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief source file(function definitions)
/// @note 40hr
/// 2022-03-30: Sujin created
/// 2022-04-04: Sujin copied Kevin's code

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <cassert>
#include <initializer_list>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

template <class T>
class List {
private:
    struct Node {
        T     data{};  ///< value stored in the Node
        Node* prev{};  ///< pointer to the previous Node
        Node* next{};  ///< pointer to the next Node
    };     // insert definition of Node from above

public:
    class Iterator {
        public:
            // member types
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = Node*;
            using reference         = value_type&;

            Iterator(pointer ptr = nullptr)
            : current(ptr)
            {}

            reference operator*() const {
                if (current == nullptr) {
                    throw std::logic_error("error: dereferencing nullptr");
                }
                return current->data;
            }

            pointer operator->() {
                return current;
            }

            Iterator& operator++() {
                if (current == nullptr) {
                    throw std::logic_error("error: dereferencing nullptr");
                }
                current = current->next;
                return *this;
            }

            Iterator operator++(int) {
                if (current == nullptr) {
                    throw std::logic_error("error: dereferencing nullptr");
                }
                Iterator tmp = *this;
                current = current->next;
                return tmp;
            }

            Iterator& operator--() {
                if (current == nullptr) {
                    throw std::logic_error("error: dereferencing nullptr");
                }
                current = current->prev;
                return *this;
            }

            Iterator operator--(int) {
                if (current == nullptr) {
                    throw std::logic_error("error: dereferencing nullptr");
                }
                Iterator tmp = *this;
                current = current->prev;
                return tmp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
                return lhs.current == rhs.current;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
                return lhs.current != rhs.current;
            }

        private:
            pointer current{};
    };

    // Member types
    using value_type = T;
    using size_type  = std::size_t;
    using reference  = value_type&;
    using iterator   = Iterator;

    List() = default;
    List(const List& other);
    List(List&& other);
    List(const std::initializer_list<value_type>& ilist);
    virtual ~List();
    List& operator=(const List& rhs);
    List& operator=(List&& rhs);
    reference front();
    reference back();
    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(); }
    bool empty() const { return begin() == end(); }
    size_type size() const { return count; }
    void clear();
    iterator insert(iterator pos, const value_type& value);
    iterator erase(iterator pos);
    void swap(List& other);

protected:
    Node*     head{};   ///< pointer to the head node
    Node*     tail{};   ///< pointer to the tail node
    size_type count{};  ///< number of nodes in list
};

/** NON-MEMBER TEMPLATE FUNCTIONS **/
template <class T>
bool operator==(const List<T>& lhs, const List<T>& rhs);

template <class T>
bool operator!=(const List<T>& lhs, const List<T>& rhs);

template <class T>
std::ostream& operator<<(std::ostream& output, const List<T>& list);
/// -------------------------------------------------------------
/// DEFINITION---------------------------------------------------
/// -------------------------------------------------------------
//  default ctor-------------------------------------------------
//template <class T>
//List<T>::List() {
//    head = nullptr;
//    tail = nullptr;
//    count = 0;
//}
/// -------------------------------------------------------------
//  copy ctor----------------------------------------------------
template <class T>
List<T>::List(const List& other) {
    *this = other;
}
/// -------------------------------------------------------------
//  move copy ctor-----------------------------------------------
template <class T>
List<T>::List(List&& other)
: head(std::exchange(other.head, nullptr)),
  tail(std::exchange(other.tail, nullptr)),
  count(std::exchange(other.count, 0)){
}
/// -------------------------------------------------------------
//  init ctor----------------------------------------------------
template <class T>
List<T>::List(const std::initializer_list<value_type>& ilist) {
    for (auto& item : ilist) {
        insert(end(), item);
    }
}
/// -------------------------------------------------------------
//  destructor---------------------------------------------------
template <class T>
List<T>::~List() {
    clear();
}
/// -------------------------------------------------------------
//  assignment operator overload---------------------------------
template <class T>
List<T>& List<T>::operator=(const List& rhs) {
    if (this != &rhs) {
        clear();

        for (auto& item : rhs) {
            insert(end(), item);
        }
    }
    return *this;
}
/// -------------------------------------------------------------
//  move assignment operator overload----------------------------
template <class T>
List<T>& List<T>::operator=(List&& rhs) {
    if (this != &rhs) {
        clear();
        head = std::exchange(rhs.head, nullptr);
        tail = std::exchange(rhs.tail, nullptr);
        count = std::exchange(rhs.count, 0);
    }
    return *this;
}
/// -------------------------------------------------------------
//  return first element in doubly linked list-------------------
template <class T>
typename List<T>::reference List<T>::front() {
    return !empty() ? head->data : throw std::logic_error("empty list");
}
/// -------------------------------------------------------------
//  return last element in doubly linked list--------------------
template <class T>
typename List<T>::reference List<T>::back() {
    if (empty()) {
        throw std::logic_error("empty");
    }
    else {
        return tail->data;
    }
}
/// -------------------------------------------------------------
//  clear--------------------------------------------------------
template <class T>
void List<T>::clear() {
    while (!empty()) {
        erase(begin());
    }
}
/// -------------------------------------------------------------
//  insert-------------------------------------------------------
template <class T>
typename List<T>::iterator List<T>::insert(iterator pos,
    const value_type& value) {
    Node* const node = new Node{ value };
    if (empty()) {
        // case1
        head = tail = node;
    } else if (pos == begin()) {
        // case2
        node->next = head;
        node->prev = node;
        head = node;
    } else if (pos == end()) {
        // case3
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        node->next = pos->prev->next;
        node->prev = pos->prev;
        pos->prev->next = node;
        pos->prev = node;
    }
    ++count;
    return iterator(node);
}
/// -------------------------------------------------------------
//  erase--------------------------------------------------------
template <class T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    auto following = List<T>::iterator();

    if (!empty() && pos != end()) {
        if (pos == begin()) {
            // case1
            head = head->next;

            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else {
            // case2
            pos->prev->next = pos->next;
            if (pos->next != nullptr) {
                pos->next->prev = pos->prev;
            }
            if (pos == tail) {
                tail = pos->prev;
            }
        }
        following = pos->next;
        delete pos.operator->();
        --count;
    }
    return following;
}
/// -------------------------------------------------------------
//  swap---------------------------------------------------------
template <class T>
void List<T>::swap(List& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(count, other.count);
}
/// -------------------------------------------------------------
/** NON-MEMBER TEMPLATE FUNCTIONS **/
/// -------------------------------------------------------------
//  operator==---------------------------------------------------
template <class T>
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    return &lhs == &rhs
           || std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
/// -------------------------------------------------------------
//  operator!=---------------------------------------------------
template <class T>
bool operator!=(const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}
/// -------------------------------------------------------------
//  operator<<---------------------------------------------------
template <class T>
std::ostream& operator<<(std::ostream& output, const List<T>& list) {
    char separator[2] {};
    output << '{';

    for (auto& item : list) {
        output << separator << item;
        *separator = ',';
    }
    return output << '}';
}
#endif /* LIST_HPP */

/* EOF */
