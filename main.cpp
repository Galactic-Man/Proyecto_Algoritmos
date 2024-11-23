#include <iostream>
#include "triage.h"
#include <windows.h>

// Puedes usar 'using namespace std;' aquí si lo prefieres
// using namespace std;
// Profe, si llegas a tener algun problema a la hora de cargar el archivo se debe a la ubicación de este en la pc.
// Sabemos que eres un experto, pero dejamos comentada una pequeña función que enuncia desde donde estás ejecutando el programa, para que tengas una mejor idea.
int main() {
    ColaDePrioridad triage;
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::cout << "Directorio de trabajo actual: " << buffer << std::endl;
    
    try {
        triage.cargarPacientes();

        // Reasignar pacientes si es necesario
        triage.reasignarPacientes();

        // Atender pacientes
        std::cout << "\nAtención de pacientes:\n";
        triage.atenderPacientes();

        // Mostrar lista de pacientes atendidos
        triage.mostrarPacientesAtendidos();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
