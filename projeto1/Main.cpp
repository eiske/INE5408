#include "Supermarket.h"
#include "Cashier.h"
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

Supermarket superMarket;

void verificaSeCriaCliente(){
	if(superMarket.relogio == superMarket.tempoChegada){
		printf("a\n");
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
	superMarket.tempoChegada = superMarket.tempoChegada + superMarket.tempoChegadaNovo;
	}
}


int main(int argc, char **argv) {
	char linha[100], nomeMercado[50], *sub, nomeCaixa[80];
	int tempoSimulacao, tempoChegada, numeroCaixas, eficiencia, salario;
	ifstream arquivo("market.dat");
	
	arquivo.getline(linha, 200);
	strncpy(nomeMercado, linha, 50);
	
	arquivo.getline(linha, 200);
	tempoSimulacao = atoi(linha);

	arquivo.getline(linha, 200);
	tempoChegada = atoi(linha);

	arquivo.getline(linha, 200);
	numeroCaixas = atoi(linha);

	cout << "Nome do Supermercado: " << nomeMercado << endl;
	cout << "Tempo de Simulacao: " << tempoSimulacao << endl;
	cout << "Tempo medio de chegada de clientes: " << tempoChegada << " segundos."<< endl;
	cout << "Numero de caixas: " << numeroCaixas << "\n" << endl;

	//arquivo.getline(linha,200);

	Cashier* array;
	array = new Cashier[numeroCaixas];
	for (int i = 0; i < numeroCaixas; ++i) {
		arquivo.getline(linha, 200);
		strcpy(nomeCaixa, linha);

		arquivo.getline(linha, 200);
		eficiencia = atoi(linha);

		arquivo.getline(linha, 200);
		salario = atoi(linha);

		cout << "Nome: " << nomeCaixa << endl;
		cout << "Eficiencia: " << eficiencia << endl;
		cout << "Salario: " << salario << "\n" << endl;
		
		Cashier c(eficiencia, salario, nomeCaixa);
		array[i] = c;
	}

	/*Cashier c1(1, 800, nomeMercado);
	array[0] = c1;
	array[1] = c1;
	array[2] = c1;*/
	superMarket = Supermarket(tempoSimulacao, tempoChegada, array, numeroCaixas, nomeMercado);

	superMarket.circList.push_front(array[0]);
	while(superMarket.relogio < superMarket.tempoSimulacao) {
		for(int i = 0; i < superMarket.circList.size(); ++i){
			superMarket.circList.at(i).verificaSeSai(superMarket.relogio);
		}
		verificaSeCriaCliente();
		++superMarket.relogio;
	}
	printf("%d\n", superMarket.circList.at(0).clientesAtendidos);
	return 0;
}
