#include <iostream>
#include "sculptor.h"

int main() {
    Sculptor s(20, 20, 20);

    // Base vermelha
    s.setColor(1, 0, 0, 1);
    s.putBox(2, 7, 2, 7, 2, 3);

    // Esfera azul
    s.setColor(0, 0, 1, 1);
    s.putSphere(5, 5, 8, 3);

    // Elipsoide verde
    s.setColor(0, 1, 0, 1);
    s.putEllipsoid(12, 12, 8, 4, 2, 3);

    // Removendo um voxel da base
    s.cutVoxel(4, 4, 2);

    // Exportando o modelo
    s.writeOFF("modelo_final.off");

    std::cout << "Modelo exportado com sucesso!" << std::endl;

    return 0;
}