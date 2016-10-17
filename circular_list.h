// Copyright [2016] <Vinicius Eiske Hashimoto>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

/**
 * @brief      List of circular list.
 *
 * @tparam     T
 */
template<typename T>
class CircularList {
 public:
    CircularList() {
        size_ = 0;
        head = new Node((T)0, nullptr);
        head->next(head);
    }
    /**
     * @brief      Destrutor da classe circular list
     */
    ~CircularList() {
        clear();
    }
    /**
     * @brief      Limpa lista
     * 
     * Função para limpar a lista.
     * 
     */
    void clear() {
        size_t a = size_;
        for (int i = 0; i < a; ++i) {
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
        } else {
            Node *prev = head->next();
            for (int i = 0; i < size_-1; ++i) {
                prev = prev->next();
            }
            prev->next(new Node(data, head));
            ++size_;
        }
    }
    /**
     * @brief      Pushes a front.
     *
     * @param[in]  data
     * 
     * Insere dado na primeira posição.
     */
    void push_front(const T& data) {
        head->next(new Node(data, head->next()));
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
        } else if (index == 0) {
            push_front(data);
        } else if (index == size_) {
            return push_back(data);
        } else {
            Node *prev = head->next();
            for (int i = 0; i < index-1; ++i) {
                prev = prev->next();
            }
            prev->next(new Node(data, prev->next()));
            ++size_;
        }
    }
    /**
     * @brief      insert_sorted
     *
     * @param[in]  data  The data
     * 
     * Insert the data in order.
     */
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        } else {
            Node* curr = head->next();
            int i = 0;
            while (i < size_ && data > curr->data()) {
                curr = curr->next();
                ++i;
            }
            insert(data, i);
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
        if (index > size_) {
            throw std::out_of_range("Erro de posicao.");
        } else if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            Node *curr = head->next();
            for (int i = 0; i < index; ++i) {
                curr = curr->next();
            }
            return curr->data();
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
        Node *curr = head->next();
        for (int i = 0; i < index; ++i) {
            curr = curr->next();
        }
        return curr->data();
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
        Node *prev, *del;
        T back;
        if (index >= size_) {
            throw std::out_of_range("Erro de posicao.");
        }
        if (empty()) {
            throw std::out_of_range("Empty.");
        }
        if (index == 0) {
            pop_front();
        }
        prev = head->next();
        for (int i = 0; i < index-1; ++i) {
            prev = prev->next();
        }
        del = prev->next();
        back = del->data();
        prev->next(del->next());
        --size_;
        delete del;
        return back;
        }
    /**
     * @brief      Pop back
     *
     * @return     Node
     * 
     * Remove the node in last position.
     */
    T pop_back() {
        if (size_ == 1) {
            return pop_front();
        } else {
            return pop(size_-1);
        }
    }
    /**
     * @brief      Pop front
     *
     * @return     Node
     * 
     * Remove the node in first position.
     */
    T pop_front() {
        T volta;
        Node *aux;
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            volta = head->next()->data();
            aux = head->next()->next();
            head->next(aux);
            --size_;
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
        } else if (find(data) == size_) {
            return false;
        } else {
            return true;
        }
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
        } else {
            Node *curr = head->next();
            for (int i = 0; i < size_; ++i) {
                if (curr->data() == data) {
                    return i;
                }
                curr = curr->next();
            }
            return size_;
        }
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

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
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
        Node* next_{nullptr};
    };
    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
