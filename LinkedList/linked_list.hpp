#pragma once

#include <iostream>
#include <exception>
#include <stdbool.h>
#include <functional>

// TODO: MUST ADD MAP AND FOLD WITH FUNCTION POINTERS (PREORDER): SEE OLD IMPLEMENTATION
// TODO: SHOULD WE PROVIDE AN ITERATOR?
// TODO: MUST IMPLEMENT FUNCTION TO REVERSE THE LINKED LIST

namespace lasd {
    template <typename Data>
    class List {
    private:
        unsigned long size = 0;
    protected:
        struct Node {
            Data element;
            Node* next = nullptr;

            inline Node() = default;

            inline Node(const Data& data) : element(data) {};
            inline Node(Data&&) noexcept;

            inline Node(const Node& node) : element(node.element) {}; // Copy constructor
            inline Node(Node&& node) noexcept;                        // Move constructor
            
            virtual ~Node(); 

            bool operator==(const Node&) const noexcept;
            bool operator!=(const Node&) const noexcept;
        };

        Node* head = nullptr;
        Node* tail = nullptr;

    public:
        List() = default;
    
        List(const List&);     // Copy constructor
        List(List&&) noexcept; // Move constructor

        virtual ~List();

        List& operator=(const List&);     // Copy assignment
        List& operator=(List&&) noexcept; // Move assignment

        bool operator==(const List&) const noexcept;
        bool operator!=(const List&) const noexcept;

        inline bool Empty() const { return (size == 0); }

        inline virtual unsigned long Size() const noexcept { return size; }

        void InsertAtFront(const Data&);    // Copy of the value
        void InsertAtFront(Data&&);         // Move of the value
        void RemoveFromFront();             // (must throw std::length_error when empty)
        Data FrontNRemove();                // (must throw std::length_error when empty)

        void InsertAtBack(const Data&) noexcept; // Copy of the value
        void InsertAtBack(Data&&);               // Move of the value

        void Clear();

        /* ************************************************************************ */

        Data& Front() const;                   // must throw std::length_error when empty
        Data& Back() const;                    // must throw std::length_error when empty
        Data& operator[](unsigned long) const; // must throw std::out_of_range when out of range
    };
}