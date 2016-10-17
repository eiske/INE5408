#include "Supermarket.h"
#include "Cashier.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <stdexcept>

void verificaSeCriaCliente(Supermarket superMarket){
	if(superMarket.relogio == superMarket.tempoChegada){
		Client novo = superMarket.geraCliente();
		//verifica se não há fila com menos de 10
		int aux;
		for(int i = 0; i < superMarket.circList.size(); ++i){
			if(superMarket.circList.at(i).calculaPessoas() > 9){
				++aux;
			}
		}
		if(aux == superMarket.circList.size()){
			superMarket.valorComprasDesistentes = novo.valorTotalDeCompras * 3;
			++superMarket.clientesDesistentes;
			return;
		}
		//verifica qual caixa deve ir
		int caixa;
		if(novo.tipoDoCliente == 0) {
			int compras = 500;
			for(int i = 0; i < superMarket.circList.size(); ++i){
				if(superMarket.circList.at(i).calculaCompras() < compras){
					compras = superMarket.circList.at(i).calculaCompras();
					caixa = i;
				}
			}
		}
		else {
			int pessoas = 500;
			for(int i = 0; i < superMarket.circList.size(); ++i){
				if(superMarket.circList.at(i).calculaPessoas() < pessoas) {
					pessoas = superMarket.circList.at(i).calculaPessoas();
					caixa = i;
				}
			}
	}
	//calcula tempo de saida
	int tempoAnterior = 0;
	for(int i = 0; i < superMarket.circList.at(caixa).queue.size(); ++i){
		tempoAnterior += superMarket.circList.at(caixa).queue.at(i).tempoDeSaida;
	}
	novo.calculaTempoSaida(superMarket.circList.at(caixa).eficiencia, tempoAnterior);
	superMarket.circList.at(caixa).queue.enqueue(novo);
	superMarket.tempoChegada=+superMarket.tempoChegada;
	}
}

void file() {
	std::ifstream file;
	file.open("./market.dat");
	char linha[50];

	if (file.is_open()) {
		while (!file.eof()) {
			file.getline(linha, 50);  // Le uma linha inteira
		}
		std::string nomeMercado;
		int tempoSimulacao;
		int tempoChegada;
		std::vector <numeroCaixas>;

		nomeMercado = linha;
		file >> tempoSimulacao;
		file >> tempoChegada;
		file >> numeroCaixas;
		// Supermarket(int tempoSimulacao_, int tempoChegada_, std::vector<Cashier> caixas_, char nome_[])
		Supermarket market = (new Supermarket(tempoSimulacao, tempoChegada, numeroCaixas, nomeMercado));


	} else {
		std::cout << "Não foi possível abrir.";
	}
}

int main(int argc, char **argv) {
		char nomeMercado[] = "mercado";
		std::vector<Cashier> vector;
		Supermarket sp(600, 10, vector, 2, nomeMercado);
		while(sp.relogio <= sp.tempoSimulacao) {
			for(int i = 0; i < sp.circList.size(); ++i){
				sp.circList.at(i).verificaSeSai(sp.relogio);
			}
			verificaSeCriaCliente(sp);
			++sp.relogio;
		}
	return 0;
}