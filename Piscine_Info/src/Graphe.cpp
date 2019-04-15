#include <algorithm>
#include "Graphe.h"
#include "Arete.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <bitset>
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
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
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


    std::cout << "Choisissez le fichier de pondération" << std::endl;
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
        else
            std::cout << "Erreur : Incompatibilite des aretes";

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

void Graphe::Pareteo(int vect_size)
{
    std::cout << vect_size << std::endl << std::endl;
    std::vector<short>bin_Vect;
    std::vector<std::vector<short>>bin_Vect_Good;

    int NmbreTotalEssais = pow(2,vect_size);
    int buffer;
    for(int i = 0; i < NmbreTotalEssais; i++)
    {
        bin_Vect.clear();
        buffer = i;
        for(int j = 0; buffer > 0  ; j++)
        {
            bin_Vect.push_back(buffer%2);
            buffer = buffer / 2;
        }


        buffer = 0;
        for(int j = 0; j < bin_Vect.size(); j++)
        {
            buffer = buffer + bin_Vect[j];
        }
       // std::cout << buffer << "  " << vect_size << std::endl;
        if(buffer == (vect_size - 2))
        {
            if(bin_Vect.size() == vect_size - 1)
            {
                bin_Vect.push_back(0);
            }
                bin_Vect_Good.push_back(bin_Vect);
        }
    }
    std::cout << "GOOD VALUES" << std::endl;
    for(int i = 0; i < bin_Vect_Good.size() ; i++)
    {
        for(int j= 0; j < bin_Vect_Good[i].size(); j++)
        {
            std::cout << bin_Vect_Good[i][j];
        }
        std::cout << std::endl;
    }
    ///Test connexite : TODO!!


}

void Graphe::KruskalAlgo()
{
    std::vector<Sommet>AdjaVect;
    int chx;
    int ptdepart;
    std::cout << "Definissez l'objectif (de 0 à " << m_Aretes[0].GetPoidsDimension() << std::endl;
    std::cin >> chx;
    std::cout << "Definissez le point de depart (de 0 à " << m_sommets.size() << std::endl;
    std::cin >> ptdepart;


}

