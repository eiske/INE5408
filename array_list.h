#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>// std::size_t
#include <stdexcept>// C++ exceptions


namespace structures {

//! Uma classe de lista.
/*!
 * Uma classe contendo metodos para serem descritas com forme pedido.
 * */
template<typename T>
class ArrayList {
public:
    //! Construtor padrão.
    /*!
     * Sempre que for usado, será criada uma lista.
     * */
    ArrayList() {
        contents = new T[max_size];
        size_ = 0;
    }
    
    //! Construtor com parâmetro.
    /*!
     *  Sempre que for usado, será criada uma lista com os dados recebidos pelo parâmetro.
     * */
    ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }

    //! Destrutor
    /*!
     *  Um destrutor da classe lista
     * */
    ~ArrayList(){
        delete[] contents;
    }

    //! Funcao limpa
    /*!
     *  Assim que é chamado, a funcao limpa a lista.
     * */
    void clear(){
        size_ = 0;
    }   
    //! Funcao insere no ultimo
    /*!
     *   Metodo que insere o dado recebido pelo parametro,
     *   na ultima posicao da lista.
     
     * */
    void push_back(T data) {
        insert(data, size_);
    }
    
    //! Funcao insere no comeco
    /*!
     *  Metodo que insere o dado recebido pelo parametro,
     *  na primeira posicao da lista.
     * */
    void push_front(T data) {
        insert(data, 0);
    }

    //! Funcao insere
    /*
     *  Metodo que insere o dado na posicao passada pelo parametro.
     * */
    void insert(T data, std::size_t index) {
      if(full()) {
        throw std::out_of_range("Lista cheia.");
      } else if(index > size_ || index < 0) {
        throw std::out_of_range("Erro de posicao");
      } else {
        for (int i = size_; i > index; --i) {
            contents[i] = contents[i - 1];
        }
        ++size_;
        contents[index] = data;
      }

    }

    //! Funcao insere na ordem
    /*!
     *  Verifica se a lista esta cheia e adiciona o dado recebido pelo parametro,
     *  na ordem.
     * */
    void insert_sorted(T data) {
        int atual;
        if(full()) {
            throw std::out_of_range("Lista cheia.");
        } else {
            atual = 0;
            while(atual < size_ && (data > contents[atual])) {
                ++atual;
            }
            insert(data, atual);
            
        }

    }

    //! Funcao Desempilha
    /*!
     *  Verifica se a lista nao está vazia para a retirada de um dado na lista,
     * e retorna o dado que está na primeira posicao da lista.
     * */
    T pop(std::size_t index) {
        T valor;
        if(empty()){
            throw std::out_of_range("lista vazia.");
        } else if(size_ <= index){
            throw std::out_of_range("Erro de posicao.");
        } else {
            valor = contents[index];
            for(int i = index; i < size_; ++i){
            contents[i] = contents[i+1];
        }
        size_--;
        return valor;
      }
        
    }
    //! Funcao retira do ultimo
    /*!
     *  Verifica se a lista nao está vazia para a retirada o ultimo dado da lista e
     *  retorna o mesmo.
     * */
    T pop_back() {
        if(empty()) {
            throw std::out_of_range("Lista vazia.");
        } else {
            return pop(size_ - 1);
        }
    }

    //! Funcao retira do primeiro
    /*!
     *  Verifica se a lista nao está vazia para a retirada o primeiro dado da lista e
     *  retorna o mesmo.
     * */
    T pop_front() {
        return pop(0);
        
    }

    
    void remove(T data) {
        if(contains(data)) {
            for(int i = 0; i <= size_; ++i) {
                if(contents[i] == data) {
                    pop(i);
                }
            }
        }
    }
    
    //! Funcao cheio
    /*!
     *  Faz uma verificacao se a lista esta vazia e retorna verdadeiro ou falso.
     * */
    bool full() const {
        if(size_ == max_size_) {
            return true;
        } else {
            return false;
        }
    }

    //! Funcao limpa
    /*!
    *  Assim que é chamado, a funcao limpa a lista.
    * */
    bool empty() const {
        if(size_ == 0) {
            return true;
        } else {
            return false;
        }

    }
    /**
     * @Funcao contem
     * @Verifica se a lista esta vazia para verificar se o dado recebido pelo parametro,
     * contem na lista.
     * 
     * @param data
     * @return true or false
     */
    bool contains(const T& data) const {
        if(empty()) {
            return false;
        } else {
            for (int i = 0; i < size_; ++i) {
                if(contents[i] == data) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @Metodo encontrar
     * @Metodo para encontrar o dado recebido pelo parametro.
     * 
     * @param data
     * @return i
     */
    std::size_t find(const T& data) const {
        if(empty()) {
            throw std::out_of_range("Lista vazia.");
        } else {
            for (int i = 0; i < size_; ++i)
            {
                if(contents[i] == data) {
                    return i;
                }
            }
        }
        return max_size_;
    }

    //! Funcao tamanho
    /*!
     *  Assim que é chamado, a funcao retorna o tamanho da lista.
     * */
    std::size_t size() const {
        return size_;

    }

    //! Funcao tamanho maximo
    /*!
     *  Assim que é chamado, a funcao retorna o valor do tamanho maximo da lista.
     * */
    std::size_t max_size() const {
        return max_size_;
    }

    /**
     * @Metodo at
     * @Recebe um indice para retornar o dado no indice
     * 
     * @param index
     * @return contents[index]
     */
    T& at(std::size_t index){
        if (index > size_  || index < 0) {
            throw std::out_of_range ("Erro de posicao.");
        } else {
            return contents[index];
        }
    }

    /**
     * @brief Operador
     * @details Recebe um indice para retornar o dado do indice
     * 
     * @param index
     */
    T& operator[](std::size_t index) {
        return contents[index];
    }

    /**
     * @brief at
     * @details Recebe um indice para retornar o dado no indice
     * 
     * @param index
     * @return contents[index]
     */
    const T& at(std::size_t index) const {
        if(empty()) {
            throw std::out_of_range ("Lista vazia.");
        } else if(index > size_ || index < 0) {
            throw std::out_of_range("Erro de posicao.");
        } else {
            return contents[index];
        }
    }

    /**
     * @brief Operador
     * @details Recebe um indice para retornar o dado do indice
     * 
     * @param index
     */
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

private:
    T* contents;/*!< Ponteiro para array de T. */
    std::size_t size_;/*!< Valor da posicao do ultimo elemento da lista.*/
    std::size_t max_size_;/*!< Valor do tamanho do array. */

    const static auto DEFAULT_MAX = 10u;
};

}

#endif