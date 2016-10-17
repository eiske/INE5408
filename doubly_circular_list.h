// Copyright [2016] <Vinicius Eiske Hashimoto>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief      List of doubly circulars.
 *
 * @tparam     T
 */
template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList() {
        size_ = 0;
        head = nullptr;
    }
    /**
     * @brief      Destrutor da classe doubly circular list
     */
    ~DoublyCircularList() {
        clear();
    }
    /**
     * @brief      Limpa lista
     * 
     * Função para limpar a lista.
     * 
     */
    void clear() {
        while (size_ != 0) {
            pop_front();
        }
    }
    /**
     * @brief      push_back
     *
     * @param[in]  data  The data
     * 
     * Insere o dado na ultima posição.
     */
    void push_back(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        Node *aux = head;
        for (int i = 0; i < size_-1; ++i) {
            aux = aux -> next();
        }
        Node *novo = new Node(data, aux->next(), aux);
        aux->next(novo);
        ++size_;
    }
    /**
     * @brief      Pushes a front.
     *
     * @param[in]  data
     * 
     * Insere dado na primeira posição.
     */
    void push_front(const T& data) {
        Node *novo = new Node(data);
        novo->next(head);
        Node *aux = head;
        for (int i = 0; i < size_; ++i) {
            aux = aux->next();
        }
        novo->prev(aux);
        head = novo;
        ++size_;
    }
    /**
     * @brief      Insert
     *
     * @param[in]  data   The data
     * @param[in]  index  The index
     * 
     * Isert the data on de specific position.
     */
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Erro de posicao.");
        }
        if (index == 0) {
            return push_front(data);
        }
        Node *ante = head;
        for (int i = 0; i < index-1; ++i) {
            ante = ante->next();
        }
        Node *novo = new Node(data, ante->next());
        ante->next()->prev(novo);
        ante->next(novo);
        ++size_;
    }
    /**
     * @brief      insert_sorted
     *
     * @param[in]  data  The data
     * 
     * Insert the data in order.
     */
    void insert_sorted(const T& data) {
        if (empty())
            return push_front(data);

        Node* atual = head;
        int index = 0;
        while (index < size_ && data > atual->data()) {
            atual = atual->next();
            ++index;
        }
        if (index == size_) {
            return push_back(data);
        }
        return insert(data, index);
    }
    /**
     * @brief      Pop
     *
     * @param[in]  index  The index
     *
     * @return     Node
     * 
     * Remove the Node in position which is recived as  parameter.
     */
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erro de posicao.");
        }
        if (empty()) {
            throw std::out_of_range("Empty.");
        }
        if (index == 0) {
            return pop_front();
        }
        Node *del, *preve;
        T ret;
        preve = head;
        for (int i = 0; i < index-1; ++i) {
            preve = preve->next();
        }
        del = preve->next();
        ret = del->data();
        preve->next(del->next());
        --size_;
        delete del;
        return ret;
    }
    /**
     * @brief      Pop back
     *
     * @return     Node
     * 
     * Remove the node in last position.
     */
    T pop_back() {
        return pop(size_-1);
    }
    /**
     * @brief      Pop front
     *
     * @return     Node
     * 
     * Remove the node in first position.
     */
    T pop_front() {
        Node *saiu = head;
        T volta;
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            volta = saiu->data();
            head = saiu->next();
            --size_;
            delete saiu;
            return volta;
        }
    }
    /**
     * @brief      Remove
     *
     * @param[in]  data  The data
     * 
     * Remove the specific node in the list.
     */
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            pop(find(data));
        }
    }
    /**
     * @brief      Empty
     *
     * @return     boolean
     * 
     * Verify the list if is empty or not.
     */
    bool empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * @brief      Contains
     *
     * @param[in]  data  The data
     *
     * @return     boolean
     * 
     * Verify the list if contains the specific data in list.
     */
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Empty.");
        }
        if (find(data) == size_) {
            return false;
        } else {
            return true;
        }
    }
    /**
     * @brief      At
     *
     * @param[in]  index  The index
     *
     * @return     address of index.
     * 
     * Verify the list if the position is valid.
     */
    T& at(std::size_t index) {
        Node *atual = head;
        if (index > size_) {
            throw std::out_of_range("Erro de posicao.");
        } else if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            for (int i = 0; i < index; ++i) {
                atual = atual->next();
            }
            return atual->data();
        }
    }
    /**
     * @brief      At
     *
     * @param[in]  index  The index
     *
     * @return     address of index.
     * 
     * Verify the list if the position is valid without cheks.
     */
    const T& at(std::size_t index) const {
        Node *atual = head;
        for (int i = 0; i < index; ++i) {
            atual->atual->next();
        }
        return atual->data();
    }
    /**
     * @brief      Searches for the first match.
     *
     * @param[in]  data  The data
     *
     * @return     Position
     */
    std::size_t find(const T& data) const {
        if (empty()) {
           throw std::out_of_range("Empty.");
        }
        Node *curr = head;
        for (int i = 0; i < size_; ++i) {
            if (curr->data() == data) {
                return i;
            }
            curr = curr->next();
        }
        return size_;
    }
    /**
     * @brief      Return the size of list.
     *
     * @return     size.
     */
    std::size_t size() const {
        return size_;
    }

 private:
     class Node {
      public:
         explicit Node(const T& data):
             data_{data}
         {}

         Node(const T& data, Node* next):
             data_{data},
             next_{next}
         {}

         Node(const T& data, Node* next, Node* prev):
             data_{data},
             next_{next},
             prev_{prev}
         {}

         T& data() {
             return data_;
         }

         const T& data() const {
             return data_;
         }

         Node* prev() {
             return prev_;
         }

         const Node* prev() const {
             return prev_;
         }

         void prev(Node* node) {
             prev_ = node;
         }

         Node* next() {
             return next_;
         }

         const Node* next() const {
             return next_;
         }

         void next(Node* node) {
             next_ = node;
         }

      private:
         T data_;
         Node* next_;
         Node* prev_;
     };

     Node* head;
     std::size_t size_;
};

}  // namespace structures

#endif
