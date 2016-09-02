#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

//! Uma classe de pilha.
/*!
 * Uma classe contendo metodos para serem descritas com forme pedido.
 * */
template<typename T>
class ArrayStack {
public:

    ArrayStack();

    ArrayStack(std::size_t max);

    ~ArrayStack();

    void push(const T& data); // empilha

    T pop(); // desempilha

    T& top();

    void clear(); // limpa

    std::size_t size(); // tamanho

    std::size_t max_size();

    bool empty(); // vazia

    bool full(); // cheia

private:
    T* contents; /*!< Ponteiro para array de T. */
    int top_; /*!< Valor da posicao do ultimo elemento da pilha.*/
    std::size_t max_size_; /*!< Valor do tamanho do array. */

    const static auto DEFAULT_SIZE = 10u;
};

//! Funcao limpa
/*!
 *  Assim que é chamado, a funcao limpa a pilha.
 * */
template<typename T>
void ArrayStack<T>::clear() {
	top_ = -1;
}

//! Funcao tamanho
/*!
 *  Assim que é chamado, a funcao retorna o tamanho da pilha.
 * */
template<typename T>
std::size_t ArrayStack<T>::size() {
	return (top_ + 1);
}

//! Funcao tamanho maximo
/*!
 *  Assim que é chamado, a funcao retorna o valor do tamanho maximo da pilha.
 * */
template<typename T>
std::size_t ArrayStack<T>::max_size() {
	return max_size_;
}

//! Funcao vazia.
/*!
 *  Verifica se a pilha esta vazia e retorna verdadeiro ou falso.
 * */
template<typename T>
bool ArrayStack<T>::empty() {
	if(top_ == -1) {
		return true;
	}
	else {
		return false;
	}
}

//! Funcao cheio
/*!
 *  Faz uma verificacao se a pilha esta vazia e retorna verdadeiro ou falso.
 * */
template<typename T>
bool ArrayStack<T>::full() {
	if(top_ == max_size_ - 1) {
		return true;
	}
	else {
		return false;
	}
}

//! Construtor padrão.
/*!
 * Sempre que for usado, será criada uma pilha.
 * */
template<typename T>
ArrayStack<T>::ArrayStack() {
	contents = new T[max_size_];
	top_ = -1;
}
//! Construtor com parâmetro.
/*!
 *  Sempre que for usado, será criada uma pilha com os dados recebidos pelo parâmetro.
 * */
template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
	max_size_ = max;
	contents = new T[max];
	top_ =-1;
}

//! Destrutor
/*!
 *  Um destrutor da classe pilha
 * */
template<typename T>
ArrayStack<T>::~ArrayStack() {
	delete[] contents;
}

//! Funcao Empilha
/*! Verifica se a pilha nao está vazia e realiza a insercao de um novo dado na pilha,
 * com um retorno vazio.
 * */
template<typename T>
void ArrayStack<T>::push(const T& data) {
	if(full()) {
		throw std::out_of_range("Pilha cheia.");
	}
	else {
		top_ ++;
		contents[top_] = data;
	}
}

//! Funcao Desempilha
/*!
 *  Verifica se a pilha nao está vazia para a retirada de um dado na pilha,
 * e retorna o dado que está na primeira posicao da pilha.
 * */
template<typename T>
T ArrayStack<T>::pop() {
	if(empty()) {
		throw std::out_of_range("Pilha vazia.");
	}
	else {
		top_ --;
		return contents[top_ + 1];
	}
}

//! Funcao Topo
/*!
 * Verifica se a pilha nao está vazia para retornar o dado que está no topo da pilha.
 **/
template<typename T>
T& ArrayStack<T>::top() {
	if(empty()) {
		throw std::out_of_range("Pilha vazia.");
	}
	else {
		return contents[top_];
	}
}


}

#endif
