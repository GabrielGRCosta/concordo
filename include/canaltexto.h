#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "mensagem.h"
#include "usuario.h"
#include <iostream>
using namespace std;

class CanalTexto{
	private:
	string nome;
	vector <Mensagem> mensagens;

	public:
	string get_namechanel();
	void set_namechanel(string name);
	void addmensage(Mensagem mensage);
	string listm(vector <Usuario> &usuarios);
	void sendm(string mensagem, int id);
};

#endif
