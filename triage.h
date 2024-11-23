#ifndef TRIAGE_H
#define TRIAGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional> // Para hash
#include <string>
#include <fstream>    // Para manejo de archivos
#include <sstream>    // Para procesamiento de cadenas

// Convierte una hora en formato "HH:MM" a minutos desde las 00:00
int convertirHora(const std::string& hora) {
    int horas = std::stoi(hora.substr(0, 2));
    int minutos = std::stoi(hora.substr(3, 2));
    return horas * 60 + minutos;
}

// Clase Paciente
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
    bool operator()(const Paciente& a, const Paciente& b) const {
        int tiempoA = convertirHora(a.hora);
        int tiempoB = convertirHora(b.hora);

        if (tiempoA != tiempoB) {
            return tiempoA > tiempoB; // Priorizar hora más temprana
        } else {
            return a.nivelUrgencia > b.nivelUrgencia; // Priorizar mayor nivel de urgencia
        }
    }
};

// Función hash para emparejar doctores
struct DoctorHash {
    size_t operator()(const std::string& doctor) const {
        std::hash<std::string> hasher;
        return hasher(doctor);
    }
};

class ColaDePrioridad {
private:
    std::priority_queue<Paciente, std::vector<Paciente>, ComparadorPacientes> colaPacientes;
    std::unordered_map<std::string, int, DoctorHash> ocupacionDoctores;
    std::unordered_map<std::string, std::vector<Paciente>, DoctorHash> pacientesPorDoctor;
    std::vector<Paciente> listaAtendidos;

public:
    void cargarPacientes() {
        const std::string nombreArchivo = "lista_pacientes.txt"; // Ruta relativa a la carpeta superior

        std::ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo " + nombreArchivo + " segundo intento");
        } else {
            std::cout << "Archivo " << nombreArchivo << " abierto exitosamente.\n";
        }

        std::string linea;
        int contador = 0;
        while (std::getline(archivo, linea)) {
            if (linea.empty()) continue; // Saltar líneas vacías

            std::stringstream ss(linea);
            std::string item;
            Paciente paciente;

            // Variables temporales para conversión
            std::string estadoStr, nivelUrgenciaStr, edadStr;

            // Leer y asignar cada campo
            std::getline(ss, paciente.nombre, ',');
            std::getline(ss, edadStr, ',');
            std::getline(ss, estadoStr, ',');
            std::getline(ss, paciente.doctor, ',');
            std::getline(ss, nivelUrgenciaStr, ',');
            std::getline(ss, paciente.dia, ',');
            std::getline(ss, paciente.hora, ',');

            // Convertir los campos numéricos y booleanos
            try {
                paciente.edad = std::stoi(edadStr);
                paciente.estado = (estadoStr == "true" || estadoStr == "1");
                paciente.nivelUrgencia = std::stoi(nivelUrgenciaStr);
            } catch (const std::exception& e) {
                std::cerr << "Error al convertir los datos del paciente: " << paciente.nombre << "\n";
                continue; // Saltar este paciente y continuar con el siguiente
            }

            // Añadir el paciente a las estructuras de datos
            colaPacientes.push(paciente);
            ocupacionDoctores[paciente.doctor]++;
            pacientesPorDoctor[paciente.doctor].push_back(paciente);
            contador++;
        }

        std::cout << "Se han cargado " << contador << " pacientes.\n";
        archivo.close();
    }

    void reasignarPacientes() {
        std::vector<std::string> doctoresConExceso, doctoresConDeficit;

        // Identificar doctores con exceso y déficit de pacientes
        for (const auto& pair : ocupacionDoctores) {
            const std::string& doctor = pair.first;
            int ocupacion = pair.second;
            if (ocupacion > 5)
                doctoresConExceso.push_back(doctor);
            else if (ocupacion < 5)
                doctoresConDeficit.push_back(doctor);
        }

        // Reasignar pacientes
        for (const auto& doctorDeficit : doctoresConDeficit) {
            for (const auto& doctorExceso : doctoresConExceso) {
                while (ocupacionDoctores[doctorDeficit] < 5 && ocupacionDoctores[doctorExceso] > 5) {
                    if (!pacientesPorDoctor[doctorExceso].empty()) {
                        Paciente paciente = pacientesPorDoctor[doctorExceso].back();
                        pacientesPorDoctor[doctorExceso].pop_back();
                        paciente.doctor = doctorDeficit;
                        pacientesPorDoctor[doctorDeficit].push_back(paciente);
                        ocupacionDoctores[doctorDeficit]++;
                        ocupacionDoctores[doctorExceso]--;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    void atenderPacientes() {
        int orden = 1;
        while (!colaPacientes.empty()) {
            Paciente paciente = colaPacientes.top(); // Obtener el paciente con mayor prioridad
            listaAtendidos.push_back(paciente);      // Guardar en la lista de atendidos
            std::cout << "Atendido [" << orden++ << "]:\n"
                      << "  - Nombre: " << paciente.nombre << "\n"
                      << "  - Doctor: " << paciente.doctor << "\n"
                      << "  - Urgencia: " << paciente.nivelUrgencia << "\n"
                      << "  - Hora: " << paciente.hora << "\n"
                      << "----------------------------------\n";
            colaPacientes.pop(); // Remover el paciente de la cola
        }
    }

    void mostrarPacientesAtendidos() const {
        std::cout << "\nLista de pacientes atendidos:\n";
        std::cout << "==================================\n";
        for (const auto& paciente : listaAtendidos) {
            std::cout << "- Nombre: " << paciente.nombre
                      << " | Doctor: " << paciente.doctor
                      << " | Urgencia: " << paciente.nivelUrgencia
                      << " | Hora: " << paciente.hora << "\n";
        }
        std::cout << "==================================\n";
    }
};

#endif // TRIAGE_H