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
      Test.DrawGraph(Screen_buffer);
      blit(Screen_buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);// affichage console
    std::cout << "Choisissez l'option " << std::endl;
    std::cout << "1) Primm " << std::endl;
    std::cout << "2) Pareto" << std::endl;
    std::cout << "3) Dijkstra " <<std::endl;
    std::cin >> chx;
    switch(chx)
    {

    case(1) :
        //std::cout << "Work In Progress" << std::endl;
        {

        Graphe j;
        Test.Prim(Screen_buffer,j);
       // j.DrawGraph(Screen_buffer);
        blit(Screen_buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        break;
        }

    case(2) :
        Test.Pareteo(Test.Getm_ordre(),Screen_buffer);
        break;
    case(3) :
        std::cout << "Work In Progress" << std::endl;
        Test.Partie3(Test.Getm_ordre(),Screen_buffer);
        break;
    }

    std::cout << "QUIT?  (Y/N)";
    std::cin >> chx;

}END_OF_MAIN();
