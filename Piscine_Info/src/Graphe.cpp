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
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
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

    for(int i = 0; i < taille; i++)
    {
        m_Aretes[i].DispArete();
    }
    for(int i = 0; i < ordre; i++)
    {
        std::cout << "adjacent pour sommet : " << i << std::endl;

        m_sommets[i].DispAdja();
    }
    /*
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
    */

}
