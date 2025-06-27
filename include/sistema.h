#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "Aeronave.h"
#include "Pessoa.h"
#include "Voo.h"
using namespace std;


class Sistema {
private:
    vector<Aeronave> aeronaves;
    vector<Piloto> pilotos;
    vector<Passageiro> passageiros;
    vector<Voo> voos;

public:
    Sistema();

    // Cadastro
    void cadastrarAeronave(const Aeronave& aeronave);
    void cadastrarPiloto(const Piloto& piloto);
    void cadastrarPassageiro(const Passageiro& passageiro);
    void criarVoo(const Voo& voo);

    // Associações
    bool embarcarPassageiro(const string& codigoVoo, const string& cpf);

    // Listagens
    void listarVoos() const;
    void listarPassageirosDoVoo(const string& codigoVoo) const;

    // Persistência
    void salvarDados() const;
    void carregarDados();

    // Buscas internas
    Aeronave* buscarAeronave(const string& codigo);
    Piloto* buscarPiloto(const string& matricula);
    Passageiro* buscarPassageiro(const string& cpf);
    Voo* buscarVoo(const string& codigo);
};


void cadastrarAeronave(vector<Aeronave>&);
void cadastrarPiloto(vector<shared_ptr<Pessoa>>&);
void cadastrarPassageiro(vector<shared_ptr<Pessoa>>&);
void cadastrarVoo(vector<Aeronave>&, vector<shared_ptr<Pessoa>>&);
void listarAeronaves(const vector<Aeronave>&);
void listarPessoas(const vector<shared_ptr<Pessoa>>&);
void listarVoos();
void associarPassageiroAoVoo(vector<shared_ptr<Pessoa>>&);
void listarPassageirosDoVoo();
void salvarAeronaves(const vector<Aeronave>&, const string&);
void salvarPessoas(const vector<shared_ptr<Pessoa>>&, const string&);
void salvarVoosCSV();


#endif
