#include "Graphe.h"
#include <fstream>
#include <iostream>
Graphe::Graphe()
{
    //ctor
}

Graphe::~Graphe()
{
    //dtor
}
Graphe::Graphe(std::string filename)    ///Code TP2 : R.Fercoq / ECE / 2019
{
    std::string suffix = "_weights_0";
    std::ifstream ifs{filename};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + filename );
    int ordre;
    int taille;
    int ID_Somm1;
    int ID_Somm2;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.push_back(Sommet(id,x,y));


    }

    ifs >> taille;
    for(int i = 0; i < taille; i++)
    {
        ifs >> id; ///Recyclage de valeur oblioge
        ifs >> ID_Somm1;
        ifs >> ID_Somm2;
        m_Aretes.push_back(Arete(ID_Somm1, ID_Somm2, m_sommets[ID_Somm1], m_sommets[ID_Somm2]));
        m_sommets[ID_Somm1].AddAdja(&m_sommets[ID_Somm2]);
        m_sommets[ID_Somm2].AddAdja(&m_sommets[ID_Somm1]);
        std::cout << "test fuck" << ID_Somm1 << ID_Somm2 << std::endl;
    }


    for (int i = 0; i <ordre; i++)
    {
        m_sommets[i].DispSommet();

    }


    std::cout << "Choisissez le fichier de pond�ration" << std::endl;
    std::cin >> filename;

    std::ifstream ifs1{filename};
    {
        int taille, g_poids;
        float p_val;
        ifs1 >> taille;
        if(taille == m_Aretes.size())
        {
            ifs1 >> g_poids;
            for(int i = 0; i < taille; i++)
            {
                ifs1>> id;
                for(int j = 0; j < g_poids; j++)
                {
                    ifs1 >> p_val;
                                   m_Aretes[i].AddPoids(p_val);
                }
            }
        }
        else std::cout << "Erreur : Incompatibilite des aretes";

    }
    for(int i = 0; i < m_Aretes.size(); i++)
    {
        std::cout << "Arete numero : " << i << std::endl;
        m_Aretes[i].DispArete();
    }
    for(int i = 0; i < m_sommets.size(); i++)
    {
        std::cout << "adjacent pour sommet : " << i << std::endl;

        m_sommets[i].DispAdja();
    }

}


void Graphe::KruskalAlgo()
{
    int chx;
    int ptdepart;
    std::cout << "Definissez l'objectif (de 0 � " << std::cout m_Aretes[0].GetPoidsDimension() << std::endl:
    std::cin >> chx;
    std::cout << "Definissez le point de depart (de 0 � " << std::cout m_sommets.size() << std::endl:
    std::cin >> ptdepart;



}
