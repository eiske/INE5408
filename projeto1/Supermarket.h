#ifndef SUPERMARKET_H_
#define SUPERMARKET_H_
#include <vector>
#include "Client.h"
#include "CircularList.h"
#include "Cashier.h"

class Supermarket {
 public:
 	CircularList<Cashier> circList{};
 	int relogio, clientesDesistentes, valorComprasDesistentes, tempoSimulacao, tempoChegada, totalDeCaixas, tempoChegadaNovo;
 	Cashier* caixas;
 	char nome[];
 	Supermarket();
 	Supermarket(int tempoSimulacao_, int tempoChegada, Cashier* caixas_, int totalDeCaixas, char nome[]);
 	void comecaCaixas(int numeroCaixas);
 	Client geraCliente();
};




#endif
