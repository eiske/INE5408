// Copyright [2016] <Vinicius Eiske Hashimoto>
#include <cstdint>
#include <stdexcept>
namespace structures {


/**
 * @brief      Linked queue
 *
 * @tparam     T
 */
template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() {
        head = nullptr;
        tail = nullptr;
        size_ = 0u;
    }

    /**
     * @brief      Pattern destructor
     */
    ~LinkedQueue() {
        clear();
    }

    /**
     * @brief      Clear the queue
     */
    void clear() {
        Node *atual, *anterior;
        atual = head;
        head = nullptr;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        head = nullptr;
        tail = nullptr;
        size_ = 0u;
    }

    /**
     * @brief      Insert data.
     *
     * @param[in]  data  The data
     */
    void enqueue(const T& data) {
        Node *novo = new Node(data, nullptr);
        if (empty()) {
            head = novo;;
        } else {
            tail->next(novo);
        }
        tail = novo;
        ++size_;
    }

    /**
     * @brief      Pop node from the queue.
     *
     * @return     Node.
     */
    T dequeue() {
        T volta;
        Node *saiu;
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            saiu = head;
            volta = saiu->data();
            head = saiu->next();
            if (size_ == 1) {
                tail = nullptr;
            }
            --size_;
            delete saiu;
            return volta;
        }
    }

    /**
     * @brief      Return the front node.
     *
     * @return     Node
     */
    T& front() const {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            return head->data();
        }
    }

    /**
     * @brief      Return the back node.
     *
     * @return     Node
     */
    T& back() const {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            return tail->data();
        }
    }

    /**
     * @brief      Verify if de queue is empty.
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
     * @brief      Size.
     *
     * @return     size.
     */
    std::size_t size() const {
        return size_;
    }
 private :
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

 private :
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures
