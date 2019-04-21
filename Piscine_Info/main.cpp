#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "allegro.h"

void Prim(Graphe &t,BITMAP *Screen_buffer);


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
        Prim(Test,Screen_buffer);
        //Test.Prim(Screen_buffer,j);
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

void Prim(Graphe &t, BITMAP*Screen_buffer)
{
    int chx; // l'utilisateur peut choisir sur quel poid il peut opérer
    float primPoids;
    std::vector<Arete> possible; //vecteur d'aretes vide où on va placer les aretes possibles créer avec le sommet utilisé
    std::vector<float> poids;
    std::vector<Arete> recuparete;
    std::vector<Sommet> recupsommet;
    std::vector<int> recupereX;
    std::vector<int> recupereY;
    std::vector<Arete> recuparete2;
    std::vector<Sommet> recupsommet2;
    std::vector<int*> affichage;

    for(size_t i=0;i<t.Gettaille();++i)
        recuparete.push_back(t.getArete(i));

    for(size_t i=0;i<t.Getm_ordre();++i)
        recupsommet.push_back(t.getSommet(i));

    for(size_t i=0;i<t.Getm_ordre();++i)
    {
        recupereX.push_back(t.getSommet(i).GetposX());
        std::cout<<"Sommet"<<recupsommet[i].GetID()<<"son x= "<<recupereX[i]<<std::endl;//test

    }


    for(size_t i=0;i<t.Getm_ordre();++i)
        recupereY.push_back(t.getSommet(i).GetposY());


    int marque[recupsommet.size()]={0}; //au lieu d'utiliser booleen(trop complique)on créer un tableau de marque
    marque[0]=1; // on marque le premier sommet
    std::vector <int> primid; //une fois un sommet marqué on le met dans prim -> arbre minimal
    primid.push_back(0);   //comme le premier sommet est marqué on le push back dans primid
    std::cout << "Definissez l'objectif (de 0 à "<< recuparete[0].GetPoidsDimension() << std::endl;
    std::cin >> chx;                                                                                  // utilisateur rentre le choix poids


    for(auto i=0; i<recupsommet.size()-1;i++) //d'après cours n-1
    {

        int variable=0; //variable à ajouter ensuite à possible
        for(auto j=0; j<recuparete.size(); j++) // 2 cas
        {

            if(marque[recuparete[j].GetSommet1()]==1 && marque[recuparete[j].GetSommet2()]!=1) //si premier s marqué et sommet 2 -> c'est une arete possible
            {
                possible.push_back(recuparete[j]);
                //std::cout<<" sommet 1 arete : "<<a[j].GetSommet1()<<"Sommet 2:"<<a[j].GetSommet2()<<std::endl;
            }
            if(marque[recuparete[j].GetSommet1()]==0 && marque[recuparete[j].GetSommet2()]!=0) //si deuxieme s marqué et sommet 1 -> c'est une arete possible
            {
                possible.push_back(recuparete[j]);
            }
        }


        //std::cout<<"a[variable].GetPoids(chx) :"<<a[variable].GetPoids(chx)<<std::endl;
        //std::cout<<"puis a[v].GetPoids(chx):"<<a[1].GetPoids(chx)<<std::endl;

        for(auto v=1; v<possible.size();v++)
        {
            if((possible[variable].GetPoids(chx))>(possible[v].GetPoids(chx)))
            {

               // v==*(affichage[i]);
                variable=v;


                // std::cout<<" rang_pmin:"<<v;
            }

           // std::cout<<" rang_pmin:"<<rang_Pmin;
        }

        primPoids=primPoids+((possible[variable]).GetPoids(chx));
       //std::cout<<"  marque[a[rang_Pmin].GetSommet1():" <<marque[a[rang_Pmin].GetSommet1()]<<std::endl;
       //std::cout<<"  marque[a[rang_Pmin].GetSommet2():" <<marque[a[rang_Pmin].GetSommet2()]<<std::endl;

        if(marque[possible[variable].GetSommet1()]==1)
        {
            marque[possible[variable].GetSommet2()]=1;
            primid.push_back(possible[variable].GetSommet2());
            //std::cout<<"  marque[a[rang_Pmin].GetSommet2() mtn:" <<marque[a[rang_Pmin].GetSommet2()]<<std::endl;

        }
        else if(marque[possible[variable].GetSommet2()]==1)
        {
            marque[possible[variable].GetSommet1()]=1;
            primid.push_back(possible[variable].GetSommet1());
        }
        possible.clear();
    }


    std::cout<<" Arbre minimal fait avec l'algorithme de Prim :"<<std::endl;

    for(auto t=0;t<recupsommet.size();t++)
    {
        std::cout<< "--> "<<primid[t];
    }
   std::cout<<" Donc poids minimal:"<<primPoids<<std::endl;

   Graphe k;
    for(auto p=0;p<recupsommet.size();p++)
    {
    recupsommet2.push_back(recupsommet[p]);
    //std::cout<<"Sommets: "<<recupsommet[p].GetID()<<std::endl;
    k.addSommet(recupsommet[p].GetID(),recupereX[p],recupereY[p]);

    }


    //std::cout<<"POS X SOMMET"<<k.getSommet(0).GetID()<<": "<<k.getSommet(0).GetposX()<<std::endl; test affichage


    for(auto j=0;j<primid.size()-1;j++)
    {
        recuparete2.push_back(Arete(primid[j],primid[j+1],recupsommet[primid[j]],recupsommet[primid[j+1]]));
        //std::cout<<"aretes: "<<recuparete2[j].GetSommet1()<<" -"<<recuparete2[j].GetSommet2()<<std::endl;
        if(primid[j]==primid[j+1]-1||primid[j]==primid[j+1]+1||primid[j]==primid[j+1]+4||primid[j]==primid[j+1]-4)
        k.AddArete(recuparete2[j].GetSommet1(),recuparete2[j].GetSommet2());

      /*  else if(primid[j]!=primid[j+1]-1&& primid[j]!=primid[j+1]+1&&primid[j]!=primid[j+1]+4&&primid[j]!=primid[j+1]-4)
        {
            int aide=0;
            std::cout<<"Probleme pour "<<primid[j+1]<<" j= "<<j+1<< std::endl;
            //std::cout<<"h < que "<<primid.size()-(primid.size()-j-1)<<std::endl;
            for (auto h=j+1;h>0;h--)
            {
            std::cout<<"h= "<<h <<"les 4 options sont: "
                     <<(primid[j+1]-1)<<" - "
                     <<(primid[j+1]+1)<<" - "
                     <<(primid[j+1]-4)<< " - "<<(primid[j+1]+4)<<std::endl;
            // int aide1=primid[j+1];
            // int aide2=(primid[j+1]+4);

            if((primid[h-1]==(primid[j+1]-1))
               ||(primid[h-1]==(primid[j+1]+1))
               ||(primid[h-1]==(primid[j+1]-4))
               ||(primid[h-1]==(primid[j+1]+4)))
            {
                std::cout<<"coucou! valeur qui change :" <<primid[h-1]<<std::endl;

                aide++;

            }


            }
            std::cout<<" aide ="<<aide;
            k.AddArete(recuparete2[j-aide].GetSommet1(),recuparete2[j].GetSommet2());
            std::cout<<"truc à remplir: "<<recuparete2[j-aide].GetSommet1()<<" - "<<recuparete2[j].GetSommet2()<<std::endl;
        }

        //std::cout<<"aretes de k: "<<k.getArete(j).GetSommet1()<<" -"<<k.getArete(j).GetSommet2()<<std::endl;


    }*/

    k.DrawGraph(Screen_buffer);

}

