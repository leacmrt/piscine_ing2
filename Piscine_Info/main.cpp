#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"

using namespace std;

int main()
{
    string nomfichier;
    std::cout << "Please input filename" << std::endl;
    std::cin >> nomfichier;
    Graphe Test = Graphe(nomfichier);
}
