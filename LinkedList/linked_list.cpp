#include "linked_list.hpp"

namespace lasd {
    template <typename Data>
    List<Data>::Node::Node(Data&& data) noexcept {
        std::swap(element, data);
    }

    template <typename Data>
    List<Data>::Node::Node(Node&& node) noexcept {
        std::swap(element, node.element);
        std::swap(next, node.next);
    }

    template <typename Data>
    List<Data>::Node::~Node() {
        delete next;
    }

    template <typename Data>
    bool List<Data>::Node::operator==(const Node& node) const noexcept {
        return (element == node.element) \
            && ((next == nullptr && node.next == nullptr) || (next != nullptr && node.next != nullptr) && (*next == *node.next));
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& node) const noexcept { return !(*this == node); }

    template<typename Data>
    List<Data>::List(const List<Data>& other_list) {
        Node* temp_node = other_list.head;
        while(temp_node != nullptr) {
            InsertAtBack(temp_node->element);
            temp_node = temp_node->next;
        }
    }

    template<typename Data>
    List<Data>::List(List<Data>&& lista) noexcept {
        std::swap(tail, lista.tail);
        std::swap(head, lista.head);
        std::swap(this->size, lista.size);
    }

    template<typename Data>
    List<Data>::~List() {
        for (unsigned long i = 0; i < this->size; ++i) {
            RemoveFromFront();
        }
    }

    template<typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& lista) {
        List<Data>* templist = new List<Data>(lista);
        std::swap(*templist, *this);
        delete templist;
        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& lista) noexcept {
        std::swap(tail, lista.tail);
        std::swap(head, lista.head);
        std::swap(this->size, lista.size);

        return *this;
    }

    template<typename Data>
    bool List<Data>::operator==(const List<Data>& lista) const noexcept {
        if(this->size == lista.size) {
            Node* temporary1 = head;
            Node* temporary2 = lista.head;

            while(temporary1 != nullptr) {
                if(temporary1->element != temporary2->element) {
                    return false;
                }
                temporary1 = temporary1->next;
                temporary2 = temporary2->next;
            }

            return true;
        } else {
            return false;
        }
    }

    template<typename Data>
    bool List<Data>::operator!=(const List<Data>& lista) const noexcept {
        return !(*this == lista); 
    }

    template<typename Data>
    void List<Data>::InsertAtFront(const Data& data) {
        if (head == nullptr) {
            head = new Node(data);
            head->next = nullptr;
            tail = head;
            this->size = 1;
        } else {
            Node* newnode = new Node(data);
            newnode->next = head;
            head = newnode;
            this->size++;
        }
    }

    template<typename Data>
    void List<Data>::InsertAtFront(Data&& data) {
        if (head == nullptr) {
            head = new Node;
            head->element = std::move(data);
            head->next = nullptr;
            tail = head;
            this->size = 1;
        } else {
            Node* newnode = new Node;
            newnode->element = std::move(data);
            newnode->next = head;
            head = newnode;
            this->size++;
        }
    }

    template<typename Data>
    void List<Data>::RemoveFromFront() {
        if (this->Size() == 0) { throw std::length_error("Error: the list is empty!"); }

        Node* temporary_node = head; 
        head = head->next; 
        temporary_node->next = nullptr;
        delete temporary_node;
        this->size--;
    }

    template<typename Data>
    Data List<Data>::FrontNRemove() {
        if(this->Size() == 0) { throw std::length_error("Error: the list is empty!"); }
        
        Node* temp = head;
        Data to_return = temp->element;
        head = head->next;
        temp->next = nullptr;
        delete temp; 
        this->size--;

        return to_return; 
    }

    template<typename Data>
    void List<Data>::InsertAtBack(const Data& data) noexcept {
        if(head == nullptr) {
            head = new Node(data);
            head->next = nullptr;
            tail = head;
            this->size = 1;
        } else {
            Node* temp = new Node(data);
            tail->next = temp;
            tail = temp;
            this->size++;
        }
    }

    template<typename Data>
    void List<Data>::InsertAtBack(Data&& data) {
        if(head == nullptr) {
            head = new Node;
            head->element = std::move(data);
            head->next = nullptr;
            tail = head;
            this->size = 1;
        } else {
            Node* temp = new Node;
            temp->element = std::move(data);
            temp->next = nullptr;
            tail->next = temp;
            tail = temp;
            this->size++;
        }
    }

    template<typename Data>
    void List<Data>::Clear() {
        while(head != nullptr) {
            RemoveFromFront();
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    template <typename Data>
    void List<Data>::Reverse() noexcept {
        if (this->Size() <= 1) return;

        Node* current = head;
        Node* prev    = nullptr;
        Node* next    = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        // At the end, swap head and tail pointers.
        tail = head;
        head = prev;
    }

    template <typename Data>
    void List<Data>::PrintList() const noexcept {
        Node* current = head;

        std::cout << "  Here is the List: ";
        while(current != nullptr) {
            std::cout << current->element << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    /* ************************************************************************ */

    template <typename Data>
    void List<Data>::MapPreOrder(MapFunctor func, void* other) {
        Node* current = head;

        while (current != nullptr) {
            func(current->element, other);
            current = current->next;
        }
    }

    template<typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor func, const void* par, void* acc) const {
        Node* current = head;
        
        while (current != nullptr) {
            func(current->element, par, acc);
            current = current->next;
        }
    }

    /* ************************************************************************ */

    template<typename Data>
    Data& List<Data>::Front() const {
        if(this->Size() == 0)
            throw std::length_error("Error: the list is empty!");

        return head->element;
    }

    template<typename Data>
    Data& List<Data>::Back() const {
        if(this->Size() == 0)
            throw std::length_error("Error: the list is empty!");

        return tail->element;
    }

    template<typename Data>
    Data& List<Data>::operator[](unsigned long index) const {
        if( index > this->size )
            throw std::out_of_range("Error: not permitted access at index: " + std::to_string(index));
        
        Node* temporarynode = head;
            
        for (unsigned long i = 0; i < index; ++i) {
            temporarynode = temporarynode->next;
        }

        return temporarynode->element;
    }

    template class List<int>;
    template class List<float>;
    template class List<double>;
    template class List<std::string>;
}