#include <iostream>
#include "sculptor.h"

int main() {
    Sculptor rosa(32, 32, 40);

    // caule
    rosa.setColor(0.1, 0.45, 0.1, 1);
    rosa.putBox(15, 16, 15, 16, 4, 25);

    // folha esquerda
    rosa.setColor(0.1, 0.6, 0.15, 1);
    rosa.putEllipsoid(12, 15, 13, 4, 2, 1);

    // folha direita
    rosa.putEllipsoid(19, 15, 18, 4, 2, 1);

    // petalas externas
    rosa.setColor(0.8, 0.02, 0.08, 1);
    rosa.putEllipsoid(12, 15, 27, 3, 3, 2);
    rosa.putEllipsoid(18, 15, 27, 3, 3, 2);
    rosa.putEllipsoid(15, 12, 27, 3, 3, 2);
    rosa.putEllipsoid(15, 18, 27, 3, 3, 2);

    // petalas internas
    rosa.setColor(1, 0.05, 0.15, 1);
    rosa.putEllipsoid(13, 14, 29, 3, 2, 2);
    rosa.putEllipsoid(17, 14, 29, 3, 2, 2);
    rosa.putEllipsoid(15, 17, 29, 3, 3, 2);

    // centro da rosa
    rosa.setColor(0.45, 0, 0.03, 1);
    rosa.putSphere(15, 15, 29, 2);

    rosa.writeOFF("rosa.off");

    std::cout << "Rosa criada com sucesso!" << std::endl;

    return 0;
}