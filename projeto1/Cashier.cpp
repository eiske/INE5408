#include "Cashier.h"

#include <string>
#include <stdio.h>
#include <cstring>

Cashier::Cashier(int eficiencia_, int salario_, char id_[]) {
	clientesAtendidos = 0;
	faturamentoTotal = 0;
	eficiencia = eficiencia_;
	salario = salario_;
	strcpy(id_,id);
	tempoMedioFila = 0;
}

Cashier::Cashier() {
	char a[] = "a";
	id[0] = a[0];
	clientesAtendidos = 0;
	faturamentoTotal = 0;
	eficiencia = 0;
	salario = 0;
	tempoMedioFila = 0;
}

void Cashier::verificaSeSai(int relogio) {
	if(relogio == queue.front().tempoDeSaida){
		faturamentoTotal =+ queue.front().valorTotalDeCompras;
		++clientesAtendidos;
		tempoMedioFila = (queue.front().tempoDeSaida - queue.front().tempoDeChegada + tempoMedioFila) / clientesAtendidos;
		queue.dequeue();
	}
}

int Cashier::calculaPessoas() {
	return queue.size();
}

int Cashier::calculaCompras() {
	int total = 0;
	for(int i = 0; i < queue.size(); ++i){
		total += queue.at(i).totalDeCompras;
	}
	return total;
}