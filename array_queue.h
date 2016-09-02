#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

//! Uma classe de fila.
/*!
 *  Uma classe contendo metodos para serem descritas com forme pedido.
 * */
template<typename T>
class ArrayQueue {
public:
    ArrayQueue();

    ArrayQueue(std::size_t max);

    ~ArrayQueue();

    void enqueue(const T& data);

    T dequeue();

    T& back();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

private:
    T* contents; /*!< Ponteiro para array de T. */
    std::size_t size_; /*!< Numero do tamanho da fila.*/
    std::size_t max_size_; /*!< Valor do tamanho do array. */

    const static auto DEFAULT_SIZE = 10u;
};

//! Construtor padrão.
/*!
 * Sempre que for usado, será criada uma fila.
 * */
template<typename T>
ArrayQueue<T>::ArrayQueue() {
	contents = new T[max_size_];
	size_ = -1;
}

//! Construtor com parâmetro.
/*!
 *  Sempre que for usado, será criada uma fila com os dados recebidos pelo parâmetro.
 * */
template<typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max) {
	max_size_ = max;
	contents = new T[max];
	size_ = -1;
}

//! Destrutor
/*!
 *  Um destrutor da classe Fila
 * */
template<typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete[] contents;
}

//! Funcao enfileira
/*! Verifica se a fila nao está vazia e adiciona um novo dado na fila,
 * com um retorno vazio.
 * */
template<typename T>
void ArrayQueue<T>::enqueue(const T& data) {
	if(full()) {
		throw std::out_of_range("Fila cheia.");
	}
	else {
	    size_ ++;
	    contents[size_] = data;
	}
}

//! Funcao desenfileira
/*!
 *  Verifica se a fila nao está vazia para remover o dado que esta na primeira posicao da fila, armazenando em uma variavel auxiliar,
 *  delocando os dados posteriores para frente
 * e retorna o dado que está na primeira posicao da fila.
 * */
template<typename T>
T ArrayQueue<T>::dequeue() {
	if(empty()) {
		throw std::out_of_range("Fila vazia.");
	}
	else {
	    T aux = contents[0];
		for (int i = 0; i <= size_; i++) {
			contents[i] = contents[i+1];
		}
		size_ --;
		return aux;
	}
}

//! Funcao ultimo
/*!
 * Verifica se a fila nao está vazia para retornar o endereco do dado que está no ultimo da fila.
 * */
template<typename T>
T& ArrayQueue<T>::back() {
	if(empty()) {
		throw std::out_of_range("Fila vazia.");
	}
	else {
		return contents[size_];
	}
}

//! Funcao limpa
/*!
 *  Assim que é chamado, a funcao limpa a fila.
 * */
template<typename T>
void ArrayQueue<T>::clear() {
	size_ = -1;
}

//! Funcao tamanho
/*!
 *  Assim que é chamado, a funcao retorna o tamanho da fila.
 * */
template<typename T>
std::size_t ArrayQueue<T>::size() {
	return size_ + 1;
}

//! Funcao tamanho maximo
/*!
 *  Assim que é chamado, a funcao retorna o valor do tamanho maximo da fila.
 * */
template<typename T>
std::size_t ArrayQueue<T>::max_size() {
	return max_size_;
}

//! Funcao vazia.
/*!
 *  Verifica se a fila esta vazia e retorna verdadeiro ou falso.
 * */
template<typename T>
bool ArrayQueue<T>::empty() {
	if(size_ == -1) {
	    return true;
	}
	return false;
}

//! Funcao cheio
/*!
 *  Faz uma verificacao se a fila esta vazia e retorna verdadeiro ou falso.
 * */
template<typename T>
bool ArrayQueue<T>::full() {
	if(size_ + 1 == max_size_) {
		return true;
	}
	return false;
}

}

#endif
