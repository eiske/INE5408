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
int tempoSimulacao, tempoChegada, numeroCaixas;
char nomeMercado[50];

void verificaSeCriaCliente(){
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
			superMarket.valorComprasDesistentes = superMarket.valorComprasDesistentes + novo.valorTotalDeCompras * 3;
			++superMarket.clientesDesistentes;
			superMarket.tempoChegada = superMarket.tempoChegada + superMarket.tempoChegadaNovo;
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
		if (superMarket.circList.at(caixa).queue.size() > 9) {
			superMarket.valorComprasDesistentes = superMarket.valorComprasDesistentes + novo.valorTotalDeCompras * 3;
			++superMarket.clientesDesistentes;
			superMarket.tempoChegada = superMarket.tempoChegada + superMarket.tempoChegadaNovo;
			return;
		}
		//calcula tempo de saida
		int tempoAnterior = 0;
		for(int i = 0; i < superMarket.circList.at(caixa).queue.size(); ++i){
			tempoAnterior = tempoAnterior + superMarket.circList.at(caixa).queue.at(i).calculaTempoAnterior(
				superMarket.circList.at(caixa).eficiencia);
		}
		novo.calculaTempoSaida(superMarket.circList.at(caixa).eficiencia, tempoAnterior);
		superMarket.circList.at(caixa).queue.enqueue(novo);
		superMarket.tempoChegada = superMarket.tempoChegada + superMarket.tempoChegadaNovo;
	}
}

void calculaDados(){
	int faturamentoMercado = 0;
	int faturamentoMedio = 0;
	for(int i = 0; i < superMarket.circList.size(); ++i){
		faturamentoMercado = faturamentoMercado + superMarket.circList.at(i).faturamentoTotal;
	}
	faturamentoMedio = faturamentoMercado / numeroCaixas;

	printf("Faturamento total: %d\n", faturamentoMercado);
	printf("Faturamento médio por caixa: %d\n", faturamentoMedio);
	for(int i = 0; i < numeroCaixas; ++i) {
		printf("Faturamento real do caixa %d: " "%d\n", i, superMarket.circList.at(i).faturamentoTotal);
	}
	for(int i = 0; i < numeroCaixas; ++i) {
		printf("Lucro do caixa %d: " "%d\n", i, superMarket.circList.at(i).faturamentoTotal - 
			superMarket.circList.at(i).salario * superMarket.tempoSimulacao/3600);
	}
	int tempoFila = 0;
	for (int i = 0; i < numeroCaixas; ++i) {
		tempoFila = tempoFila + superMarket.circList.at(i).tempoMedioFila;
	}
	printf("Tempo médio na fila: %d\n", tempoFila/numeroCaixas);
	printf("Clientes desistentes: %d\n", superMarket.clientesDesistentes);
	printf("Faturamento perdido: %d\n", superMarket.valorComprasDesistentes);
	printf("\nDesenvolvido por Vinicius Macelai e Vinicius Eiske\n");
}

void leituraInfo() {
	char linha[100], nomeMercado[50], *sub, nomeCaixa[80];
	int eficiencia, salario;
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
	cout << "Tempo de Simulacao: " << tempoSimulacao << " horas"<<endl;
	cout << "Tempo medio de chegada de clientes: " << tempoChegada << " segundos"<< endl;
	cout << "Numero de caixas: " << numeroCaixas << "\n" << endl;

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
		superMarket = Supermarket(tempoSimulacao, tempoChegada, numeroCaixas, nomeMercado);
		Cashier c(eficiencia, salario, nomeCaixa);
		array[i] = c;
	}
	for(int i = 0; i < numeroCaixas; ++i) {
		superMarket.circList.push_front(array[i]);
	}
}

void mensagemExecucao() {
	cout << "Selecione a forma de entrada da simulacao:\n";
	cout << "----- 1: Atraves de arquivo salvo.\n";			
	cout << "----- 0: Digitar dados.\n";
}

bool execucao() {
	std::string formaExecucaoStr;
	int formaExecucaoInt;
	bool arquivo, verdade = true;

	while (verdade) {
		std::cin >> formaExecucaoStr;
		std::cin.ignore();
		formaExecucaoInt = stoi(formaExecucaoStr);

		if (formaExecucaoInt < 0 || formaExecucaoInt > 1) {
			std::cout << "Opcao invalido.";
		}
		verdade = false;
	}

	if (formaExecucaoInt == 1) {
		arquivo = true;
	} else {
		arquivo = false;
	}
	return arquivo;
}

int totalCaixa() {
	string totalCaixaStr;
	int totalCaixaInt;
	bool verdade = true;
	cout << "Digite a quantidade de caixa.\n";
	while(verdade) {
		getline(std::cin, totalCaixaStr);
		totalCaixaInt = stoul(totalCaixaStr);
		if (totalCaixaInt <= 0) {
			std::cout << "Quantidade insuficiente.";
			verdade = true;
			break;
		} else {
			verdade = false;
		}
	}
	return totalCaixaInt;
}

string idCaixa() {
	string id;
	bool verdade = true;
	std::cout << "Digite o identificador do caixa.";

	while (verdade) {
		getline(std::cin, id);
		if (id == "") {
			std::cout << "Identificador invalido.";
			break;
		} else {
			verdade = false;
		}
	}
	return id;
}

int salarioCaixa() {
	std::string salarioStr;
	int salarioInt;
	bool verdade = true;
	std::cout << "Digite o salario do caixa.";

	while (verdade) {
		getline(std::cin, salarioStr);
		salarioInt = stoi(salarioStr);
		if (salarioInt == 0) {
			std::cout << "Salario invalido.";
			break;
		} else {
			verdade = false;
		}
	}
	return salarioInt;
}

int eficienciaCaixa() {
	std::string eficienciaStr;
	int eficienciaInt;
	bool verdade = true;
	std::cout << "Digite a eficiência do caixa:\n";
	std::cout << "\t1, 2 ou 3\n";

	while (verdade) {
		getline(std::cin, eficienciaStr);
		eficienciaInt = stoul(eficienciaStr);
		if (eficienciaInt < 1 || eficienciaInt > 3) {
			std::cout << "Eficiencia invalida.";
			break;
		} else {
			verdade = false;
		}
	}
	return eficienciaInt;
}

string mercado() {
 	string nomeMercado;
 	bool verdade = true;
 	cout << "Digite o nome do Supermercado.\n";
 	while (verdade) {
 		getline(std::cin, nomeMercado);
 		if (nomeMercado == "") {
 			std::cout << "Nome inválido.\n";
 			break;
 		} else {
 			verdade = false;
 		}
 	}
 	return nomeMercado;
 }

int simulacao() {
 	std::string tempoSimulacaoStr;
 	int tempoSimulacaoInt;
 	bool verdade = true;
 	std::cout << "Digite o tempo de simulacao.\n";

 	while (verdade) {
 		getline(std::cin, tempoSimulacaoStr);
 		tempoSimulacaoInt = std::stoi(tempoSimulacaoStr);
 		if (tempoSimulacaoInt < 0) {
 			std::cout << "Tempo inválido.\n";
 			break;
 		} else {
 			verdade = false;
 		}
 	}
 	return tempoSimulacaoInt;
 }

int tempoMedioChegada() {
	std::string tempoMedioChegadaStr;
	int tempoMedioChegadaInt;
	bool verdade = true;
	cout << "Digite o tempo medio de chegada de clientes.\n";

	while (verdade) {
		getline(std::cin, tempoMedioChegadaStr);
		tempoMedioChegadaInt = std::stoi(tempoMedioChegadaStr);
		if (tempoMedioChegadaInt < 0) {
			std::cout << "Tempo invalido.\n";
			break;
		} else {
			verdade = false;
		}
	}
	return tempoMedioChegadaInt;
}

int main(int argc, char **argv) {
	int numCaixa, sim, tempoMedio;
	string nome;
	mensagemExecucao();
	if (execucao()) {
		leituraInfo();
	} else {
		nome = mercado();
		sim = simulacao();
		tempoMedio = tempoMedioChegada();
		numCaixa = totalCaixa();
		cout << "Nome do Supermercado: \n" << nome;
		cout << "Tempo de Simulacao: " << sim << " horas\n";
		cout << "Tempo medio de chegada de clientes: " << tempoMedio << " segundo\n";
		cout << "Numero de caixas: " << numCaixa << "\n";

		Cashier* array;
		array = new Cashier[numCaixa];
		for (int i = 0; i < numCaixa; i++) {
			string nomeCaixa = idCaixa();
			int eficiencia = eficienciaCaixa();
			int salario = salarioCaixa();

			cout << "Nome: " << nomeCaixa << endl;
			cout << "Eficiencia: " << eficiencia << endl;
			cout << "Salario: " << salario << "\n" << endl;
			superMarket = Supermarket(sim, tempoMedio, numCaixa, nome);
			Cashier c(eficiencia, salario, nomeCaixa);
			array[i] = c;
		}
		for (int i = 0; i < numCaixa; ++i) {
			superMarket.circList.push_front(array[i]);
		}
	}

	srand (time(NULL));
	while(superMarket.relogio < superMarket.tempoSimulacao) {
		for(int i = 0; i < superMarket.circList.size(); ++i){
			superMarket.circList.at(i).verificaSeSai(superMarket.relogio);
		}
		verificaSeCriaCliente();
		++superMarket.relogio;
	}
	calculaDados();
	return 0;
}

