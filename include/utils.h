#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <string>
#include "Aeronave.h"
#include "Pessoa.h"

using namespace std;

// Funções para aeronaves
vector<Aeronave> carregarAeronaves(const string& nomeArquivo);
void salvarAeronaves(const vector<Aeronave>& lista, const string& nomeArquivo);

// Funções para pessoas (pilotos e passageiros)
vector<shared_ptr<Pessoa>> carregarPessoas(const string& nomeArquivo);
void salvarPessoas(const vector<shared_ptr<Pessoa>>& lista, const string& nomeArquivo);

#endif
