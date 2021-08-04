#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "mensagem.h"
#include <iostream>
using namespace std;

class CanalTexto{
	private:
	string nome;
	vector <mensagem> mensagens;

	public:
	string get_namechanel();
	void set_namechanel(string name);
};

#endif
