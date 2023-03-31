 
            /// @file WelcomeToSujinsLinkedIn
            /// @author Sujin Lee <sujinbonnaud@gmail.com>
            /// @date Currently Available
            /// @note I pledge my word of honor that I have complied with the
            ///       Programming Integrity Policy while coding.
            /// @brief 
            /// 2022-04-20: Sujin created

            #include <iostream>
            #include <algorithm>
            #include <string>
            #include "Stack.hpp"
/// USER DEFINED FUNCTION PROTOTYPE-------------------------------------------
int search(const char A[], char value, int size);
/// --------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// --------------------------------------------------------------------------
int main(int argc, char* argv[]) {
/// VARIABLE DEFINITION-------------------------------------------------------
    int exitVal = 0;  // exit code, 1 for error, otherwise 0
    Stack<char> stack {};
    int wrong = 0;  // to hold wrong index
    int index = 0;  // to hold a index
    int size = 0;  // input size
    int idxcase = 0;  // index of case(*
    char array1[] = { '(', '[', '{', '<' };  // open braces
    char array2[] = { ')', ']', '}', '>' };  // closing braces
    string exp = {};  // to hold command argv to string
    char ch1 = {};  // exp[i]
    char ch2 = {};  // exp[i+1]
    char ch3 = {};  // exp[i-1]
/// PROCESS-------------------------------------------------------------------
    if (argc > 1) {  // right command arg
        exp = argv[1];
        size = static_cast<int>(exp.size());
        for (int i = 0; i < size && wrong == 0; i++) {
            ch1 = exp[i];
            if (search(array1, ch1, 4) > -1) {  // openning brace case
                ch2 = i+1 < size ? exp[i+1] : '\0';
                if (ch2 == '*') {
                    stack.push('$');  // '$' == '(*' in stack
                    idxcase = i;
                } else {
                    stack.push(ch1);
                }
            } else if (search(array2, ch1, 4) > -1) {  // closing brace case
                ch3 = i-1 > 0 ? exp[i-1] : ' ';
                // (**) case && idxcase + 2 prevent (*) case
                if (ch3 == '*' && i > idxcase + 2) {
                    if (stack.top() == '$') {  // '$' == '(*' in stack
                        stack.pop();
                    } else {
                        wrong = i-1;
                    }
                } else if (ch3 == '*' && i <= idxcase + 2) {
                    wrong = i-1;
                // regular closing brace case
                } else {
                    index = search(array2, ch1, 4);
                    if (!stack.empty() && stack.top() == array1[index]) {
                        // comp matching brace
                        stack.pop();
                    } else if (!stack.empty() &&
                        stack.top() != array1[index]) {
                        wrong = i;
                    }
                }
            }
        }  // eof for loop
/// OUTPUT-------------------------------------------------------------------
        if (stack.empty()) {
            std::cout << "YES" << std::endl;
        } else if (!stack.empty() && wrong == 0){
            std::cout << "NO " << size + 1 << std::endl;
        } else {
            std::cout << "NO " << wrong << std::endl;
        }
/// NO COMMAND LINE IS PROVIDED----------------------------------------------
    } else {
        std::cout << "Usage: " << argv[0] << " 'EXPRESSION'" << std::endl;
        exitVal = 1;  // assign exit to 1 for no command line argument
    }

    return exitVal;
}  // eof main
/// USER DEFINED FUNCTION DEFINITION-----------------------------------------
int search(const char A[], char value, int size) {
    bool flag1 = false;  // if item is found
    int num = -1;  // index of found item
    for (int i = 0; i < size && !flag1; i++) {
        if (A[i] == value) {
            flag1 = true;
            num = i;
        }
    }
    return num;
}
