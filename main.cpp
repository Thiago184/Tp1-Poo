#include <iostream>
#include <vector>
#include <memory>
#include "include/aeronave.h"
#include "include/pessoa.h"
#include "include/utils.h"
#include "sistema.h"

// Funções já implementadas nos arquivos de cadastro
using namespace std;

int main() {
    vector<Aeronave> aeronaves = carregarAeronaves("aeronaves.csv");
    vector<shared_ptr<Pessoa>> pessoas = carregarPessoas("pessoas.csv");

    int opcao;
    do {
        cout << "\n======= SISTEMA DE CONTROLE DE VOOS =======\n";
        cout << "1. Cadastrar aeronave\n";
        cout << "2. Cadastrar piloto\n";
        cout << "3. Cadastrar passageiro\n";
        cout << "4. Criar voo\n";
        cout << "5. Embarcar passageiro em voo\n";
        cout << "6. Listar voos\n";
        cout << "7. Listar passageiros de um voo\n";
        cout << "8. Gerar relatórios e estatísticas\n";
        cout << "9. Sair\n";
        cout << "==========================================\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                cadastrarAeronave(aeronaves);
                salvarAeronaves(aeronaves, "aeronaves.csv");
                break;
            case 2:
                cadastrarPiloto(pessoas);
                salvarPessoas(pessoas, "pessoas.csv");
                break;
            case 3:
                cadastrarPassageiro(pessoas);
                salvarPessoas(pessoas, "pessoas.csv");
                break;
            case 4:
                cadastrarVoo(aeronaves, pessoas);
                salvarVoosCSV();
                break;
            case 5:
                associarPassageiroAoVoo(pessoas);
                break;
            case 6:
                listarVoos();
                break;
            case 7:
                listarPassageirosDoVoo();
                break;
            case 8:
                cout << "Funcionalidade de relatórios ainda não implementada.\n";
                break;
            case 9:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }
    } while (opcao != 9);

    return 0;
}