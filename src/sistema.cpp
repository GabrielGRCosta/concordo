#include "../include/sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "../include/usuario.h"
#include <string.h>
#include <string>
using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

void Sistema::adduser(Usuario a){
	usuarios.push_back(a);
	a.set_id(usuarios.size());
}

std::vector <Usuario> Sistema::get_usuarios(){
	return usuarios;
}

string Sistema::create_user (const string email, const string senha, const string nome) {
	Usuario user;
	user.set_name(nome);
	user.set_email(email);
	user.set_senha(senha);
	for(auto &u : usuarios){
		if( u.get_email() == email ){
			return "Usuário já existe";
		} 
	}
  adduser(user);
  return "Usuário criado";
}


string Sistema::login(const string email, const string senha) {
	string x;
	//for(int i=0; i<usuarios.size() ; i++){
		for(auto &u : usuarios){ 
			if( u.get_email() == email && u.get_senha() == senha && usuariosLogados.count(u.get_id())==0){
				x = email;
				usuariosLogados[u.get_id()] = make_pair("","");
				return "Logado como " +x;
			}
		}
		for(auto &h : usuarios){
			if(usuariosLogados.count(h.get_id())==1){
				return "Usuário já está logado";
			}	
		}	
  return "Senha ou usuário inválidos!";
}

string Sistema::disconnect(int id) {
	string m;
	for(auto &y : usuarios){
		if( usuariosLogados.count(id) != 0){
			usuariosLogados.erase(id);
			m = y.get_email();
			return "Desconectando usuário " +m;
		}
	}
  return "O usuário não está conectado";  
}

string Sistema::create_server(int id, const string nome) {
	Servidor server;
	server.set_nameserver(nome);
	for(auto &g : servidores){
		if(g.get_nameserver() == nome){
			return "Servidor com esse nome já existe";
		}
	}
	server.set_id(id);
	servidores.push_back(server);
  return "Servidor criado";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	for(auto &l : servidores){
		if(l.get_nameserver() == nome && l.get_donoid() == id){
			l.set_descri(descricao);
			//"Comando precisa ser precedido de um id [" + to_string(id) + "]";
			return "Descrição modificada no servidor " + nome;
		}
		if(l.get_nameserver() == nome && l.get_donoid() != id){
			return "Você não pode alterar a descrição de um servidor que não foi criado por você";
		}
	}
	return "Não existe o servidor " + nome;
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	for(auto &t : servidores){
		if(t.get_donoid() == id && t.get_nameserver() == nome){
			t.set_convite(codigo);
			if(codigo != ""){
				return "Código de convite modificado do servidor " + nome;
			}
			else{
				return "Código de convite removido do servidor " + nome;
			}
		}
	}
	return "O usuário não é dono do servidor ou o servidor não existe";
}

string Sistema::list_servers(int id) {
	stringstream stream;
	for(auto &i : usuarios){
		if(i.get_id() != id ){
			return "Usuário não está cadastrado no sistema";
		}
	}
	if(usuariosLogados.count(id) == 0){
		return "Usuário não está logado";
	}
	int count = 0;
	for(auto &r : servidores){
		stream<<r.get_nameserver();
		if (servidores.begin()+count != servidores.end()-1) {
			stream<<endl;
		}
		count++;
	}	
	return stream.str();
}

string Sistema::remove_server(int id, const string nome) {
	string h;
	int count = 0;
	for(auto &q : servidores){
		if (usuariosLogados.count(id) == 0) {
			return "Usuario não está logado";
		}
		if(q.get_nameserver() == nome && q.get_donoid() == id){
			servidores.erase(servidores.begin()+count);
			return "Removido o servidor " +nome;
		}
		if(q.get_nameserver() == nome && q.get_donoid() != id){
			return "Você não é o dono do servidor " +nome;
		}
		++count;
	}
	return "Não foi encontrado o servidor " + nome;
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	if (usuariosLogados.count(id) == 0) {
		return "Usuario não está logado";
	}
	for(auto &b : servidores){
		if(b.get_nameserver() == nome && b.get_convite() == ""){
			b.addpartids(id);
			usuariosLogados[id].first = nome;
			return "Entrou no servidor com sucesso";
		}
		else if(b.get_nameserver() == nome && b.get_convite() != ""){
			if(b.get_convite() == codigo || b.get_donoid() == id){
				b.addpartids(id);
				usuariosLogados[id].first = nome;
				return "Entrou no servidor com sucesso";
			}
			return "Servidor requer código de convite";
		}
	}
  return "Servidor Não foi encontrado";
}

string Sistema::leave_server(int id, const string nome) {
	if (usuariosLogados.count(id) == 0) {
		return "Usuario não está logado";
	}
	for(auto &w : servidores){
		if(w.get_nameserver() == nome){
			w.rmpartids(id);
			return "Saindo do servidor " + nome;
		}
		if(w.checkidlist(id) == 0){
			return "Você não está no servidor " + nome;
		}
	}
  return "Você não está em qualquer servidor";
}

string Sistema::list_participants(int id) {
	if (usuariosLogados.count(id) == 0) {
		return "Usuario não está logado";
	}
	for(auto &q : servidores){
		if(usuariosLogados[id].first == q.get_nameserver()){
			return q.searchlistid(get_usuarios());
		}
	}
  return "Não há pessoas no servidor procurado";
}

string Sistema::list_channels(int id) {
	if (usuariosLogados.count(id) == 0) {
		return "Usuario não está logado";
	}
	for(auto &v : servidores){
		if(usuariosLogados[id].first == v.get_nameserver()){
			return v.searchchanels();
		}
	}
  return "Não existe canais no servidor";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
