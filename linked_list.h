// Vinicius Eiske Hashimoto -- 2016.2

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>
#include <iostream>

namespace structures {

template<typename T>
class LinkedList {
public:

    /**
     * @brief      Construtor padrão.
     */
    LinkedList() {
        head = nullptr;
        size_ = 0;
    }
    
    /**
     * @brief      Destrutor da classe LinkedList
     */
    ~LinkedList() {
        clear();
    }
    
    /**
     * @brief      Limpa lista
     * 
     * Função para limpar a lista.
     * 
     */
    void clear() {
        Node *atual, *anterior;
        atual = head;
        head = nullptr;
        while(atual != nullptr) {
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
        Node *novo = new Node(data, head);
        if(novo == nullptr) {
            throw std::out_of_range("Lista cheia");
        } else {
            head = novo;
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
        if(index > size_) {
            throw std::out_of_range ("Erro de posicao.");
        }else if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);
            if(novo == nullptr) {
                throw std::out_of_range ("Lista cheia");
            } else {
                anterior = head;
                for(int i = 0; i < index - 1; ++i) {
                    anterior = anterior->next();
                }
                //novo->next() = anterior->next();
                //"novo.next(anterior.next())"
                novo->next(anterior->next());
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
        if(empty()) {
            return push_front(data);
        } else {
            atual = head;
            posicao = 0;
            while(atual->next() != nullptr && data > atual->data()) {
                atual = atual->next();
                ++posicao;
            } 

            if(data > atual->data()) {
                return(insert(data,posicao+1));
            } else {
                return(insert(data,posicao));
            }
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
        if(index < 0) {
            throw std::out_of_range("erro");
        }
        Node *aux = head;
        for (int i = 0; i < index; ++i) {
            if (aux->next() == nullptr) {
                throw std::out_of_range ("Erro de posicao.");
            }
            aux = aux->next();
        }
        return aux->data();
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
        if (empty()) {
            throw std::out_of_range ("Vazio.");
        }
        Node *anterior, *elimina;
        T volta;
        if(index > size_-1) {
            throw std::out_of_range("Erro posicao.");
        } else if (index == 0){
            return(pop_front());
        } else {
            anterior = head;
            for (int i = 0; i < index-1; ++i) {
                anterior = anterior->next();
                //std::cout << anterior->next()->data() << std::endl;

            }
            elimina = anterior->next();
            //std::cout << elimina->data() << std::endl;
            volta = elimina->data();
            anterior->next(elimina->next());
            --size_;
            delete elimina;
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
        return pop(size_ - 1);
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
        if(empty()) {
            throw std::out_of_range("Lista vazia.");
        } else {
            saiu = head;
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
        if(size_ == 0) {
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
        while(aux != nullptr) {
            if(aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
        return false;
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
        if(empty()) {
            return (-1);
        } else {
            pos = 0;
            while(caixa->data() != data) {
                caixa = caixa->next();
                ++pos;
                if(caixa == nullptr) {
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

private:
	// Elemento
    class Node {
    public:
        Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        // getter: dado
        T& data() {
            return data_;
        }

        // getter const: dado
        const T& data() const {
            return data_;
        }

        // getter: próximo
        Node* next() {
            return next_;
        }

        // getter const: próximo
        const Node* next() const {
            return next_;
        }
 		// setter: próximo
        void next(Node* node) {
            next_ = node;
        }

    private:
        T data_;//_info
        Node* next_{nullptr};//_proximo
    };

    Node* end() { // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
		}
        return it;
    }

    Node* head{nullptr};//_dados
    std::size_t size_{0u};//_tamanho
};

}

#endif