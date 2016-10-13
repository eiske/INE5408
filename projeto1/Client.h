/*
 * Client.h
 *
 *  Created on: 10 de out de 2016
 *      Author: macelai
 */

#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
 public:
	int tipoDoCliente, tipoDePagamento, valorTotalDeCompras, tempoDeChegada, tempoDeSaida, totalDeCompras;
	int* compras;
 	Client(int tempo);
 	int calculaTempo(int eficiencia);
 	void calculaTempoSaida(int eficiencia, int tempoAnterior);
};

#endif /* CLIENT_H_ */
