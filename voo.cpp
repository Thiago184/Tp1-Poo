#include "include/Voo.h"
#include <sstream>
#include <cmath>
#include <iostream>

Voo::Voo() : distancia(0), aeronave(nullptr), comandante(nullptr), primeiroOficial(nullptr), numeroEscalas(0), tempoEstimado(0.0) {}

Voo::Voo(const string& codigo, const string& origem, const string& destino, double distancia, const string& horaSaida,
         Aeronave* aeronave, Piloto* comandante, Piloto* primeiroOficial)
    : codigo(codigo), origem(origem), destino(destino), distancia(distancia), horaSaida(horaSaida),
      aeronave(aeronave), comandante(comandante), primeiroOficial(primeiroOficial) {
    calcularEscalasETempo();
}

string Voo::getCodigo() const { return codigo; }
void Voo::setCodigo(const string& codigo) { this->codigo = codigo; }

string Voo::getOrigem() const { return origem; }
void Voo::setOrigem(const string& origem) { this->origem = origem; }

string Voo::getDestino() const { return destino; }
void Voo::setDestino(const string& destino) { this->destino = destino; }

double Voo::getDistancia() const { return distancia; }
void Voo::setDistancia(double distancia) { this->distancia = distancia; }

string Voo::getHoraSaida() const { return horaSaida; }
void Voo::setHoraSaida(const string& hora) { this->horaSaida = hora; }

int Voo::getNumeroEscalas() const { return numeroEscalas; }
double Voo::getTempoEstimado() const { return tempoEstimado; }

Aeronave* Voo::getAeronave() const { return aeronave; }
void Voo::setAeronave(Aeronave* aeronave) { this->aeronave = aeronave; }

Piloto* Voo::getComandante() const { return comandante; }
void Voo::setComandante(Piloto* comandante) { this->comandante = comandante; }

Piloto* Voo::getPrimeiroOficial() const { return primeiroOficial; }
void Voo::setPrimeiroOficial(Piloto* oficial) { this->primeiroOficial = oficial; }

const vector<Passageiro*>& Voo::getPassageiros() const { return passageiros; }

bool Voo::adicionarPassageiro(Passageiro* passageiro) {
    if ((int)passageiros.size() < aeronave->getCapacidade()) {
        passageiros.push_back(passageiro);
        return true;
    }
    return false;
}

void Voo::calcularEscalasETempo() {
    if (aeronave != nullptr) {
        numeroEscalas = ceil(distancia / aeronave->getAutonomia()) - 1;
        if (numeroEscalas < 0) numeroEscalas = 0;
        tempoEstimado = (distancia / aeronave->getVelocidadeMedia()) + numeroEscalas * 1.0;
    }
}

// CSV: codigo,origem,destino,distancia,hora,aeronaveCodigo,comandanteMatricula,primeiroOficialMatricula
string Voo::toCSV() const {
    return codigo + "," + origem + "," + destino + "," + to_string(distancia) + "," + horaSaida + "," +
           aeronave->getCodigo() + "," + comandante->getMatricula() + "," + primeiroOficial->getMatricula();
}

void Voo::listarPassageiros() const {
    cout << "=== Passageiros do Voo " << codigo << " ===\n";
    for (const auto& p : passageiros) {
        cout << p->getNome() << " | CPF: " << p->getCPF() << " | Bilhete: " << p->getBilhete() << endl;
    }
}
