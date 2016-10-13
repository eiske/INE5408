/*
 * Cashier.h
 *
 *  Created on: 10 de out de 2016
 *      Author: macelai
 */

#ifndef CASHIER_H_
#define CASHIER_H_

#include "Queue.h"
#include "Client.h"

class Cashier {
public:
	int clientesAtendidos, tempoMedioFila, faturamentoTotal, eficiencia, salario;
	LinkedQueue<Client> queue;
	char id[];
	Cashier();
 	Cashier(int eficiencia_, int salario_, char id_[]);
 	void verificaSeSai(int relogio);
 	int calculaPessoas();
 	int calculaCompras();
};
#endif /* CASHIER_H_ */
