/// @file Stack.hpp
/// @author Sujin Lee
/// @date 4/20/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief source file(stack)
/// @note 20hr
/// 2022-04-20: Sujin created

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "List.hpp"
#include <string>

template <class T>
class Stack : protected List<T> {
public:
    // member types
    using value_type = T;
    using reference  = T&;

    reference top() {
        return List<T>::front();
    }
    bool empty() {
        return List<T>::empty();
    }
    void push(const value_type& value) {
        List<T>::insert(List<T>::begin(), value);
    }
    void pop() {
        List<T>::erase(List<T>::begin());
    }
};

#endif /* STACK_HPP */

/* EOF */
