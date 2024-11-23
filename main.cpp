#include "ColaDePrioridad.h"

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
