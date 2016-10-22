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
 	char nome[];
 	std::string name;
 	Supermarket();
 	Supermarket(int tempoSimulacao_, int tempoChegada, int totalDeCaixas, std::string name_);
 	Supermarket(int tempoSimulacao_, int tempoChegada, int totalDeCaixas, char nome[]);
 	Client geraCliente();
};




#endif
