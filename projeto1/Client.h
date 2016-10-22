#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
 public:
	int tipoDoCliente, tipoDePagamento, valorTotalDeCompras, tempoDeChegada, tempoDeSaida, totalDeCompras;
 	Client(int tempo);
 	int calculaTempo(int eficiencia);
 	void calculaTempoSaida(int eficiencia, int tempoAnterior);
 	int calculaTempoAnterior(int eficiencia);
};

#endif /* CLIENT_H_ */