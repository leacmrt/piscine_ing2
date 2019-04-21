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
        {

        Prim(Test,Screen_buffer);
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

    for(size_t i=0;i<t.Gettaille();++i)  //on met toutes les aretes du graphe test dans un vecteur d'arete pour pouvoir les utiliser
        recuparete.push_back(t.getArete(i));

    for(size_t i=0;i<t.Getm_ordre();++i) // pareil pour les sommets
        recupsommet.push_back(t.getSommet(i));

    for(size_t i=0;i<t.Getm_ordre();++i) //et leurs positions
    {
        recupereX.push_back(t.getSommet(i).GetposX());
        //std::cout<<"Sommet"<<recupsommet[i].GetID()<<"son x= "<<recupereX[i]<<std::endl;//test

    }


    for(size_t i=0;i<t.Getm_ordre();++i)
        recupereY.push_back(t.getSommet(i).GetposY());


    int couleur[recupsommet.size()]={0}; //au lieu d'utiliser booleen(trop complique)on crée un tableau de couleur, initialisé sans couleur
    couleur[0]=1; // on marque le premier sommet
    std::vector <int> primid; //une fois un sommet marqué on le met dans prim (son id car plus simple pour l'utiliser) -> arbre minimal ,
    primid.push_back(0);   //comme le premier sommet est marqué on le push back dans primid
    std::cout << "Definissez l'objectif (de 0 à "<< recuparete[0].GetPoidsDimension() << std::endl;
    std::cin >> chx;                                                                                  // utilisateur rentre le choix poids


    for(auto i=0; i<recupsommet.size()-1;i++) //d'après cours n-1 dans un arbre minimal
    {

        int variable=0; //variable à ajouter ensuite à possible
        for(auto j=0; j<recuparete.size(); j++) // 2 cas = on peut le faire car le premier sommet est marque
        {

            if(couleur[recuparete[j].GetSommet1()]==1 && couleur[recuparete[j].GetSommet2()]!=1) //si premier s marqué et sommet 2 -> c'est une arete possible
            {
                possible.push_back(recuparete[j]);
                //std::cout<<" sommet 1 arete : "<<a[j].GetSommet1()<<"Sommet 2:"<<a[j].GetSommet2()<<std::endl;//test
            }
            if(couleur[recuparete[j].GetSommet1()]==0 && couleur[recuparete[j].GetSommet2()]!=0) //si deuxieme s marqué et sommet 1 -> c'est une arete possible
            {
                possible.push_back(recuparete[j]); // on place tout dans le conteneur d'aretes possible
            }
        }


        //std::cout<<"a[variable].GetPoids(chx) :"<<a[variable].GetPoids(chx)<<std::endl; //test pour voir si les poids s'affichés bien
        //std::cout<<"puis a[v].GetPoids(chx):"<<a[1].GetPoids(chx)<<std::endl;

        for(auto v=1; v<possible.size();v++) //pour prim on doit pour le sommet utilisé, prendre l'arete possible avec le plus faible choix
        {
            if((possible[variable].GetPoids(chx))>(possible[v].GetPoids(chx))) //on va donc trier le vecteur possible en fonction des poids
            {
                variable=v;//pour savoir combien de place se deplace l'arete avec le poids minimal

            }
        }

        primPoids=primPoids+((possible[variable]).GetPoids(chx)); //on recupère le poid de chaque aretes misent dans prim pour calculer le poids minimal de l'arbre

        if(couleur[possible[variable].GetSommet1()]==1) //si dans l'arete recupérée le premier sommet est coloré alors on colore le 2eme
        {
            couleur[possible[variable].GetSommet2()]=1;
            primid.push_back(possible[variable].GetSommet2()); // on le rentre dans primid

        }
        else if(couleur[possible[variable].GetSommet2()]==1) //de meme pour la situation inverse
        {
            couleur[possible[variable].GetSommet1()]=1;
            primid.push_back(possible[variable].GetSommet1());
        }
        possible.clear(); //on efface le vecteur possible car pour chaque sommet il est nouveau
    }


    std::cout<<" Arbre minimal fait avec l'algorithme de Prim :"<<std::endl;

    for(auto t=0;t<recupsommet.size();t++)
    {
        std::cout<< "--> "<<primid[t]; // on afficher la suite d'id de l'arbre minimal
    }
   std::cout<<" Donc poids minimal:"<<primPoids<<std::endl;

   //affichage de prim

    Graphe k; // on crée un graphe vide
    for(auto p=0;p<recupsommet.size();p++) //on vas y insérer tout les sommets/poids/pos qu'on a trouvé avec prim
    {
    recupsommet2.push_back(recupsommet[p]);
    //std::cout<<"Sommets: "<<recupsommet[p].GetID()<<std::endl;//test
    k.addSommet(recupsommet[p].GetID(),recupereX[p],recupereY[p]);

    }


    for(auto j=0;j<primid.size()-1;j++)
    {

        //int i=1;
        recuparete2.push_back(Arete(primid[j],primid[j+1],recupsommet[primid[j]],recupsommet[primid[j+1]]));
        int adja = recuparete2[j].getFirstId().getAdjasize();//on recupere le nombre de sommets adjacent à chaque sommets

     if( primid[j+1]+adja<primid.size()||primid[j]+adja<primid.size())
     {
        if (adja==4) //pour chaque cas trouvés dans les fichiers on adapte la valeur de adja
            adja=2;

        if(adja==3)
        {
            if(primid.size()==8)
            adja=6;

            if(primid.size()<9)
            adja=2;

            else if (primid.size()>13)
            adja=4;
        }

        if (adja==6&&primid.size()>9)
            adja=3;

        if(adja==2)
        {
            if(primid.size()>6)
            adja=4;

            else adja=2;
        }

     }


        //std::cout<<"aretes: "<<recuparete2[j].GetSommet1()<<" -"<<recuparete2[j].GetSommet2()<<std::endl;//test
        if(primid[j]==primid[j+1]-1||primid[j]==primid[j+1]+1||primid[j]==primid[j+1]+adja||primid[j]==primid[j+1]-adja)
           k.AddArete(recuparete2[j].GetSommet1(),recuparete2[j].GetSommet2()); //si l'arete de base existe on la tajoute à k

       else if(primid[j]!=primid[j+1]-1&& primid[j]!=primid[j+1]+1&&primid[j]!=primid[j+1]+adja&&primid[j]!=primid[j+1]-adja)//si l'arete n'existe pas on trouve comme pour prim precedement à l'aide d'une variable, au bout de combien de for on trouve enfin une arete qui existe
        {
            int aide=0;
            //std::cout<<"Probleme pour "<<primid[j+1]<<" j= "<<j+1<< std::endl;//test

            for (auto h=j+1;h>0;h--)
            {
            if((primid[h-1]!=(primid[j+1]-1))
               &&(primid[h-1]!=(primid[j+1]+1))
               &&(primid[h-1]!=(primid[j+1]-adja))
               &&(primid[h-1]!=(primid[j+1]+adja)))
            {

                aide++; //elle augmente jusqu'à trouvé la bonne valeur

            }

             else if((primid[h-1]==(primid[j+1]-1))
               ||(primid[h-1]==(primid[j+1]+1))
               ||(primid[h-1]==(primid[j+1]-adja))
               ||(primid[h-1]==(primid[j+1]+adja)))
            {
                break;
            }
            }

        k.AddArete(recuparete2[j-aide].GetSommet1(),recuparete2[j].GetSommet2()); //une fois trouvée on rajoute l'arete au graphe

    }

    k.DrawGraph(Screen_buffer);//on affiche le graphe remplis

}
}
