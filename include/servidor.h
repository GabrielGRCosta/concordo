#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>
#include "canaltexto.h"
using namespace std;

class Servidor{
	private:
	int usuarioDonoId;	
	string nome;
	string descricao;
	string codigoConvite;
	vector <CanalTexto> CanaisTexto;
	vector <int> participantesIDs; 

  public:
	
	void set_nameserver(string n);

	void set_id(int a);

	void set_descri(string b);

	void set_convite(string k);

	string get_nameserver();

	int get_donoid();

	string get_convite();

	void addpartids(int id);

	void rmpartids(int id);

	int checkidlist(int id);

	string searchlistid(vector<Usuario> usuarios);

	string searchchanels();

	int checknameCH(string name);

	void addChanels(CanalTexto Channel);

	string requestlistm(vector<Usuario> &usuarios,string canal);

	void requestsendm(string canal, string mensagem, int id);

};


#endif
