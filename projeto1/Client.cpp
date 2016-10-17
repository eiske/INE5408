#include "Client.h"
#include <stdlib.h>
#include <time.h>

Client::Client(int tempo) {
	srand (time(0));
	tipoDoCliente = rand() % 2;
	tipoDePagamento = (rand() % 10) + 1;
	totalDeCompras = (rand() % 100) + 2;
	compras = new int[totalDeCompras];
	for (int i = 0; i < totalDeCompras-1; ++i) {
		compras[i] = (rand() % 90) + 1;
	}
	for (int i = 0; i < totalDeCompras-1; ++i){
		valorTotalDeCompras =+ compras[i];
	}
	tempoDeChegada = tempo;
	tempoDeSaida = 0;
}

int Client::calculaTempo(int eficiencia) {
	int auxEfi = 0;
	int total = 0;
	bool cheque = false;
	int adicionalCheque = 0;
	if (eficiencia == 1) auxEfi = 1;
	if (eficiencia == 2) auxEfi = 2;
	if (eficiencia == 3) auxEfi = 4;
	if (tipoDePagamento <= 2){ cheque = true;}
	if (eficiencia == 1 && cheque) adicionalCheque = 10;
	if (eficiencia == 2 && cheque) adicionalCheque = 25;
	if (eficiencia == 3 && cheque) adicionalCheque = 40;
	total = (totalDeCompras * auxEfi) + adicionalCheque;
	return total;
}

void Client::calculaTempoSaida(int eficiencia, int tempoAnterior) {
	tempoDeSaida = tempoDeChegada + calculaTempo(eficiencia) + tempoAnterior;
}