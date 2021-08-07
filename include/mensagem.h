 #ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

class Mensagem{
	private:
	int enviadaPor;
	string conteudo;
	string dataHora;

	public:
	Mensagem(int enviadaPor, string conteudo);
	string get_datahora();
	string get_conteudo();
	int get_enviadaPor();
	string printm(string m);
};

#endif