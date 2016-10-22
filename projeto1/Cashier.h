#ifndef CASHIER_H_
#define CASHIER_H_

#include "Queue.h"
#include "Client.h"

class Cashier {
public:
	int clientesAtendidos, tempoMedioFila, faturamentoTotal, eficiencia, salario;
	LinkedQueue<Client> queue;
	char id[];
	std::string nome;
	Cashier();
 	Cashier(int eficiencia_, int salario_, char id_[]);
 	Cashier(int eficiencia_, int salario_, std::string nome_);
 	void verificaSeSai(int relogio);
 	int calculaPessoas();
 	int calculaCompras();
};
#endif /* CASHIER_H_ */
