#ifndef SUPERMARKET_H_
#define SUPERMARKET_H_
#include <vector>
#include "Client.h"
#include "CircularList.h"
#include "Cashier.h"

class Supermarket {
 public:
 	CircularList<Cashier> circList{};
 	int relogio, clientesDesistentes, valorComprasDesistentes, tempoSimulacao, tempoChegada, totalDeCaixas;
 	std::vector<Cashier> caixas;
 	char nome[];
 	Supermarket(int tempoSimulacao_, int tempoChegada, std::vector<Cashier> caixas_, int totalDeCaixas, char nome[]);
 	Supermarket(int tempoSimulacao_, int tempoChegada_, std::vector<Cashier> caixas_, char nome_[]);
 	void comecaCaixas();
 	Client geraCliente();
 	void 
};




#endif
