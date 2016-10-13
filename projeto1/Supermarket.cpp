/*
 * Supermarket.cpp
 *
 *  Created on: 10 de out de 2016
 *      Author: macelai
 */

#include "Supermarket.h"
#include <string.h>


Supermarket::Supermarket(int tempoSimulacao_, int tempoChegada_, std::vector<Cashier> caixas_, int totalDeCaixas_, char nome_[]) {
	relogio = 0;
	clientesDesistentes = 0;
	valorComprasDesistentes = 0;
	tempoSimulacao = tempoSimulacao_;
	tempoChegada = tempoChegada_;
	caixas = caixas_;
	totalDeCaixas = totalDeCaixas_;
	strcpy(nome_,nome);
}

void Supermarket::comecaCaixas() {
	for(int i = 0; i >= caixas.size(); ++i) {
		circList.insert(caixas.at(i), i);
	}
}

Client Supermarket::geraCliente() {
	return Client(relogio);
}