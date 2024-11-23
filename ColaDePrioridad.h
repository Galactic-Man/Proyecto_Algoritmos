#ifndef COLA_DE_PRIORIDAD_H
#define COLA_DE_PRIORIDAD_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <string>

// Convierte una hora en formato "HH:MM" a minutos desde las 00:00
int convertirHora(const std::string& hora);

// Estructura Paciente
struct Paciente {
    std::string nombre;
    int edad;
    bool estado;
    std::string doctor;
    int nivelUrgencia;
    std::string dia;
    std::string hora;
};

// Comparador personalizado para la priority_queue
struct ComparadorPacientes {
    bool operator()(const Paciente& a, const Paciente& b) const;
};

// Función hash para emparejar doctores
struct DoctorHash {
    size_t operator()(const std::string& doctor) const;
};

class ColaDePrioridad {
public:
    void cargarPacientes();
    void reasignarPacientes();
    void construirColaPacientes();
    void atenderPacientes();
    void mostrarPacientesAtendidos() const;

private:
    std::priority_queue<Paciente, std::vector<Paciente>, ComparadorPacientes> colaPacientes;
    std::unordered_map<std::string, int, DoctorHash> ocupacionDoctores;
    std::unordered_map<std::string, std::vector<Paciente>, DoctorHash> pacientesPorDoctor;
    std::vector<Paciente> listaAtendidos;
};

#endif // COLA_DE_PRIORIDAD_H