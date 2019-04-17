#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "allegro.h"


int main()
{
    allegro_init();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP* Screen_buffer = create_bitmap(800,600);
    int chx;
    std::string nomfichier;
    std::cout << "Please input filename" << std::endl;
    std::cin >> nomfichier;
    Graphe Test = Graphe(nomfichier);
    std::cout << "Choisissez l'option que vous voulez part'nair" << std::endl;
    std::cout << "1) Primm (Phase 0 : Introduction)" << std::endl;
    std::cout << "2) Pareto (Phase 1 : T    his was a mistake)" << std::endl;
    std::cout << "3) Dijkstra (Phase 2 : 1-800-ENDME" <<std::endl;
    std::cin >> chx;
    switch(chx)
    {

    case(1) :
        std::cout << "DIDNT DO IT SORRY" << std::endl;
        break;

    case(2) :
        Test.Pareteo(Test.Getm_ordre(),Screen_buffer);
        break;
    case(3) :
        std::cout << "DIDNT DO IT SORRY GUYZ" << std::endl;
        break;
    }

    std::cout << "QUIT?  (Y/N)";
    std::cin >> chx;

}END_OF_MAIN();
