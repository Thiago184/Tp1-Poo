#include "include/pessoa.h"
#include <sstream>

Pessoa::Pessoa() {}
Pessoa::Pessoa(const string& nome) : nome(nome) {}
string Pessoa::getNome() const { return nome; }
void Pessoa::setNome(const string& nome) { this->nome = nome; }

// ------- Piloto -------
Piloto::Piloto() : horasVoo(0.0) {}
Piloto::Piloto(const string& nome, const string& matricula, const string& breve, double horasVoo)
    : Pessoa(nome), matricula(matricula), breve(breve), horasVoo(horasVoo) {}

string Piloto::getMatricula() const { return matricula; }
void Piloto::setMatricula(const string& matricula) { this->matricula = matricula; }

string Piloto::getBreve() const { return breve; }
void Piloto::setBreve(const string& breve) { this->breve = breve; }

double Piloto::getHorasVoo() const { return horasVoo; }
void Piloto::setHorasVoo(double horas) { this->horasVoo = horas; }

string Piloto::toCSV() const {
    return "PILOTO," + nome + "," + matricula + "," + breve + "," + to_string(horasVoo);
}

Piloto Piloto::fromCSV(const string& linha) {
    stringstream ss(linha);
    string tipo, nome, matricula, breve, horasStr;

    getline(ss, tipo, ',');  // PILOTO
    getline(ss, nome, ',');
    getline(ss, matricula, ',');
    getline(ss, breve, ',');
    getline(ss, horasStr, ',');

    return Piloto(nome, matricula, breve, stod(horasStr));
}

// ------- Passageiro -------
Passageiro::Passageiro() {}
Passageiro::Passageiro(const string& nome, const string& cpf, const string& bilhete)
    : Pessoa(nome), cpf(cpf), bilhete(bilhete) {}

string Passageiro::getCPF() const { return cpf; }
void Passageiro::setCPF(const string& cpf) { this->cpf = cpf; }

string Passageiro::getBilhete() const { return bilhete; }
void Passageiro::setBilhete(const string& bilhete) { this->bilhete = bilhete; }

string Passageiro::toCSV() const {
    return "PASSAGEIRO," + nome + "," + cpf + "," + bilhete;
}

Passageiro Passageiro::fromCSV(const string& linha) {
    stringstream ss(linha);
    string tipo, nome, cpf, bilhete;

    getline(ss, tipo, ',');  // PASSAGEIRO
    getline(ss, nome, ',');
    getline(ss, cpf, ',');
    getline(ss, bilhete, ',');

    return Passageiro(nome, cpf, bilhete);
}
