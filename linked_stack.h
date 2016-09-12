// Copyright [2016] <Vinicius Eiske Hashimoto>
#include <cstdint>
#include <stdexcept>
namespace structures {

/**
 * @brief      Linked Stack
 *
 * @tparam     T
 */
template<typename T>
class LinkedStack {
 public:
    LinkedStack() {
        top_ = nullptr;
        size_ = 0;
    }

    /**
     * @brief      Destroys the stack;
     */
    ~LinkedStack() {
        clear();
    }

    /**
     * @brief      Clear stack.
     */
    void clear() {
        Node *atual, *anterior;
        atual = top_;
        top_ = nullptr;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        size_ = 0u;
    }


    /**
     * @brief      Insert data on stack
     *
     * @param[in]  data  The data
     */
    void push(const T& data) {
        Node *novo = new Node(data, top_);
        if (novo == nullptr) {
            throw std::out_of_range("Lista cheia");
        } else {
            top_ = novo;
            ++size_;
        }
    }

    /**
     * @brief      Remove data from stack
     *
     * @return     { description_of_the_return_value }
     */
    T pop() {
        Node *saiu;
        T volta;
        if (empty()) {
            throw std::out_of_range("Lista vazia.");
        } else {
            saiu = top_;
            volta = saiu->data();
            top_ = saiu->next();
            --size_;
            delete saiu;
            return volta;
        }
    }

    /**
     * @brief      Return the Node on the top of stack.
     *
     * @return     Node
     */
    T& top() const {
        if (empty()) {
            throw std::out_of_range("Pilha vazia.");
        } else {
            return top_->data();
        }
    }

    /**
     * @brief      Checks if the stack is empty 
     *
     * @return     boolean
     */
    bool empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief      Return th size of stack.
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
     private :
        T data_;
        Node* next_;
    };
    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};
}  // namespace structures
