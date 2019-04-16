#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"

using namespace std;

int main()
{
    int chx;
    string nomfichier;
    std::cout << "Please input filename" << std::endl;
    std::cin >> nomfichier;
    Graphe Test = Graphe(nomfichier);
    std::cout << "Choisissez l'option que vous voulez part'nair" << std::endl;
    std::cout << "1) Primm (Phase 0 : Introduction)" << std::endl;
    std::cout << "2) Pareto (Phase 1 : This was a mistake)" << std::endl;
    std::cout << "3) Dijkstra (Phase 2 : 1-800-ENDME" <<std::endl;
    std::cin >> chx;
    switch(chx)
    {

    case(1) :
        std::cout << "DIDNT DO IT SORRY" << std::endl;
        break;

    case(2) :
        Test.Pareteo(Test.Getm_ordre());
        break;
    case(3) :
        std::cout << "DIDNT DO IT SORRY GUYZ" << std::endl;
        break;
    }

}
