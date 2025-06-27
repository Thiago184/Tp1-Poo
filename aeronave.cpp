#include "include/aeronave.h"
#include <sstream>

Aeronave::Aeronave() : capacidade(0), velocidadeMedia(0.0), autonomia(0.0) {}

Aeronave::Aeronave(const string& codigo, const string& modelo, int capacidade, double velocidadeMedia, double autonomia)
    : codigo(codigo), modelo(modelo), capacidade(capacidade), velocidadeMedia(velocidadeMedia), autonomia(autonomia) {}

string Aeronave::getCodigo() const { return codigo; }
void Aeronave::setCodigo(const string& codigo) { this->codigo = codigo; }

string Aeronave::getModelo() const { return modelo; }
void Aeronave::setModelo(const string& modelo) { this->modelo = modelo; }

int Aeronave::getCapacidade() const { return capacidade; }
void Aeronave::setCapacidade(int capacidade) { this->capacidade = capacidade; }

double Aeronave::getVelocidadeMedia() const { return velocidadeMedia; }
void Aeronave::setVelocidadeMedia(double velocidade) { this->velocidadeMedia = velocidade; }

double Aeronave::getAutonomia() const { return autonomia; }
void Aeronave::setAutonomia(double autonomia) { this->autonomia = autonomia; }

string Aeronave::toCSV() const {
    return codigo + "," + modelo + "," + to_string(capacidade) + "," +
           to_string(velocidadeMedia) + "," + to_string(autonomia);
}

Aeronave Aeronave::fromCSV(const string& linha) {
    stringstream ss(linha);
    string codigo, modelo, capacidadeStr, velocidadeStr, autonomiaStr;

    getline(ss, codigo, ',');
    getline(ss, modelo, ',');
    getline(ss, capacidadeStr, ',');
    getline(ss, velocidadeStr, ',');
    getline(ss, autonomiaStr, ',');

    return Aeronave(codigo, modelo, stoi(capacidadeStr), stod(velocidadeStr), stod(autonomiaStr));
}

