#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <string>
using namespace std;

class Usuario{
	private:
		int id=0;
		string nome;
		string email;
		string senha;

	public:
		Usuario(string nome, string email , string senha);

		string get_name();

		string get_email();

		string get_senha();

		int get_id();

		void set_id(int a);


};

#endif
