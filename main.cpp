#include "ColaDePrioridad.h"

/*/ Convierte una hora en formato "HH:MM" a minutos desde las 00:00
int convertirHora(const string& hora) {
    int horas = stoi(hora.substr(0, 2));
    int minutos = stoi(hora.substr(3, 2));
    return horas * 60 + minutos;
}

// Estructura Paciente
struct Paciente {
    string nombre;
    int edad;
    bool estado;
    string doctor;
    int nivelUrgencia;
    string dia;
    string hora;
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
    size_t operator()(const string& doctor) const {
        return hash<string>()(doctor);
    }
};

class ColaDePrioridad {
private:
    priority_queue<Paciente, vector<Paciente>, ComparadorPacientes> colaPacientes;
    unordered_map<string, int, DoctorHash> ocupacionDoctores;
    unordered_map<string, vector<Paciente>, DoctorHash> pacientesPorDoctor;
    vector<Paciente> listaAtendidos;

public:
    void cargarPacientes() {
        vector<Paciente> pacientes = {
            {"Pedro", 36, true, "Hernandez", 1, "25/11/2024", "14:00"},
            {"Mariana", 9, true, "Torres", 1, "25/11/2024", "16:00"},
            {"Carlos", 36, true, "Carvajal", 1, "25/11/2024", "08:00"},
            {"Daniela", 36, true, "Hernandez", 2, "25/11/2024", "14:00"},
            {"Luis", 18, true, "Torres", 2, "25/11/2024", "16:00"},
            {"Andrea", 29, true, "Carvajal", 2, "25/11/2024", "08:00"},
            {"Mauricio", 45, true, "Hernandez", 3, "25/11/2024", "12:00"},
            {"Roberto", 52, true, "Torres", 3, "25/11/2024", "14:00"},
            {"Jonathan", 25, true, "Torres", 3, "25/11/2024", "13:00"},
            {"Isabel", 19, true, "Carvajal", 3, "25/11/2024", "11:30"},
            {"Valeria", 31, true, "Hernandez", 2, "25/11/2024", "11:30"},
            {"Laura", 6, true, "Hernandez", 4, "25/11/2024", "11:00"},
            {"Ana", 33, true, "Torres", 4, "25/11/2024", "10:00"},
            {"Miguel", 50, true, "Carvajal", 4, "25/11/2024", "13:00"},
            {"Tomas", 36, true, "Hernandez", 5, "25/11/2024", "09:00"},
            {"Sara", 12, true, "Torres", 5, "25/11/2024", "09:30"},
            {"Carmen", 40, true, "Carvajal", 5, "25/11/2024", "14:00"}
        };

        for (auto& paciente : pacientes) {
            ocupacionDoctores[paciente.doctor]++;
            pacientesPorDoctor[paciente.doctor].push_back(paciente);
        }
    }

    // Reasigna pacientes entre doctores para equilibrar la carga.
    void reasignarPacientes() {
        vector<string> doctoresConExceso, doctoresConDeficit;

        // Identificar doctores con exceso y déficit de pacientes
        for (const auto& pair : ocupacionDoctores) {
            const string& doctor = pair.first;
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

    // Construye la cola de pacientes después de reasignar
    void construirColaPacientes() {
        for (const auto& pair : pacientesPorDoctor) {
            const vector<Paciente>& pacientes = pair.second;
            for (const Paciente& paciente : pacientes) {
                colaPacientes.push(paciente);
            }
        }
    }

    // Atiende a los pacientes en orden de prioridad hasta que la cola esté vacía.
    void atenderPacientes() {
        int orden = 1;
        while (!colaPacientes.empty()) {
            Paciente paciente = colaPacientes.top(); // Obtener el paciente con mayor prioridad
            listaAtendidos.push_back(paciente);      // Guardar en la lista de atendidos
            cout << "Atendido [" << orden++ << "]:\n"
                 << "  - Nombre: " << paciente.nombre << "\n"
                 << "  - Doctor: " << paciente.doctor << "\n"
                 << "  - Urgencia: " << paciente.nivelUrgencia << "\n"
                 << "  - Hora: " << paciente.hora << "\n"
                 << "----------------------------------\n";
            colaPacientes.pop(); // Remover el paciente de la cola
        }
    }

    // Muestra la lista de pacientes atendidos después de vaciar la cola.
    void mostrarPacientesAtendidos() const {
        cout << "\nLista de pacientes atendidos:\n";
        cout << "==================================\n";
        for (const auto& paciente : listaAtendidos) {
            cout << "- Nombre: " << paciente.nombre
                 << " | Doctor: " << paciente.doctor
                 << " | Urgencia: " << paciente.nivelUrgencia
                 << " | Hora: " << paciente.hora << "\n";
        }
        cout << "==================================\n";
    }
};*/

int main() {
    ColaDePrioridad triage;

    try {
        triage.cargarPacientes();
        triage.reasignarPacientes();
        triage.construirColaPacientes();

        std::cout << "\nAtención de pacientes:\n";
        std::cout << "==================================\n";
        triage.atenderPacientes();

        triage.mostrarPacientesAtendidos();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}