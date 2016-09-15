// Copyright [2016] <Vinicius Eiske Hashimoto>

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief      List of doubly linkeds.
 *
 * @tparam     T
 */
template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList() {
        head = nullptr;
        size_ = 0u;
    }
    /**
     * @brief      Destrutor da classe DoublyLinkedList
     */
    ~DoublyLinkedList() {
        clear();
    }
    /**
     * @brief      Destrutor da classe DoublyLinkedList
     */
    void clear() {
        Node *atual, *anterior;
        atual = head;
        head = nullptr;
        while ( atual != nullptr ) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        size_ = 0u;
    }
    /**
     * @brief      push_back
     *
     * @param[in]  data  The data
     * 
     * Insere o dado na ultima posição.
     */
    void push_back(const T& data) {
        insert(data, size_);
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
        if (novo == nullptr) {
            throw std::out_of_range("full list.");
        } else {
            novo->next(head);
            novo->prev(nullptr);
            head = novo;
            if (novo->next() != nullptr) {
                novo->next()->prev(novo);
            }
            ++size_;
        }
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
        Node *anterior, *novo;
        if (index > size_) {
          throw std::out_of_range("position error.");
        } else if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("full");
            } else {
                anterior = head;
                for (int i = 0; i < index - 1; ++i) {
                    anterior = anterior->next();
                }
                novo->next(anterior->next());
                if (novo->next() != nullptr) {
                    novo->next()->prev(novo);
                }
                anterior->next(novo);
                ++size_;
            }
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
        Node *atual;
        int posicao;
        if (empty()) {
            return push_front(data);
        } else {
            atual = head;
            posicao = 0;
            while (atual->next() != nullptr && data > atual->data()) {
                atual = atual->next();
                ++posicao;
            }
            if (data > atual->data()) {
                return(insert(data, posicao+1));
            } else {
                return(insert(data, posicao));
            }
        }
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
            throw std::out_of_range("Index out of bounds");
        } else if (empty()) {
            throw std::out_of_range("Empty pop");
        } else if (index == 0) {
            return pop_front();
        } else {
            Node *anterior, *eliminar;
            T volta;
            anterior = head;
            for (int i = 0; i < index-1; ++i) {
                anterior = anterior->next();
            }
            eliminar = anterior->next();
            volta = eliminar->data();
            anterior->next(eliminar->next());
            if (eliminar->next() != nullptr)
                eliminar->next()->prev(anterior);

            --size_;
            delete eliminar;
            return volta;
        }
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
        Node *saiu;
        T volta;
        if (empty()) {
            throw std::out_of_range("empty list.");
        } else {
            saiu = head;
            volta = saiu->data();
            head = saiu->next();
            if (head != nullptr) {
                head->prev(nullptr);
            }
            --size_;
            delete saiu;
            return volta;
        }
    }
    /**
     * @brief      remove
     *
     * @param[in]  data
     */
    void remove(const T& data) {
        pop(find(data));
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
        Node *aux = head;
        while (aux != nullptr) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
        return false;
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
            throw std::out_of_range("position error.");
        } else if (empty()) {
            throw std::out_of_range("empty.");
        } else {
            Node *aux = head;
            for (int i = 0; i < index; ++i) {
                if (aux->next() == nullptr) {
                    throw std::out_of_range("Erro de posicao.");
                }
                aux = aux->next();
            }
            return aux->data();
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
    const T& at(std::size_t index) const {
        Node *aux = head;
        for (int i = 0; i < index; ++i) {
            if (aux->next() == nullptr) {
                throw std::out_of_range("Erro de posicao.");
            }
            aux = aux->next();
        }
        return aux->data();
    }
    /**
     * @brief      Searches for the first match.
     *
     * @param[in]  data  The data
     *
     * @return     Position
     */
    std::size_t find(const T& data) const {
        Node *caixa = head;
        std::size_t pos;
        if (empty()) {
            return (-1);
        } else {
            pos = 0;
            while (caixa->data() != data) {
                caixa = caixa->next();
                ++pos;
                if (caixa == nullptr) {
                    break;
                }
            }
            return pos;
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

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
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
        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }
     private :
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures
