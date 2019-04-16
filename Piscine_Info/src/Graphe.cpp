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

Graphe::Graphe(std::vector<Sommet>sommetVector, std::vector<Arete>areteVector)
{
    m_Aretes = areteVector;
    m_sommets = sommetVector;
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
    unsigned int ordre;
    unsigned int taille;
    int ID_Somm1;
    int ID_Somm2;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;
    //lecture des sommets
    for (unsigned int i=0; i<ordre; ++i)
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
    for(unsigned int i = 0; i < taille; i++)
    {
        ifs >> id; ///Recyclage de valeur oblioge
        ifs >> ID_Somm1;
        ifs >> ID_Somm2;
        m_Aretes.push_back(Arete(ID_Somm1, ID_Somm2, m_sommets[ID_Somm1], m_sommets[ID_Somm2]));
        m_sommets[ID_Somm1].AddAdja(&m_sommets[ID_Somm2]);
        m_sommets[ID_Somm2].AddAdja(&m_sommets[ID_Somm1]);
        std::cout << "test fuck" << ID_Somm1 << ID_Somm2 << std::endl;
    }


    for (unsigned int i = 0; i <ordre; i++)
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
    for(unsigned int i = 0; i < m_Aretes.size(); i++)
    {
        std::cout << "Arete numero : " << i << std::endl;
        m_Aretes[i].DispArete();
    }
    for(unsigned int i = 0; i < m_sommets.size(); i++)
    {
        std::cout << "adjacent pour sommet : " << i << std::endl;

        m_sommets[i].DispAdja();
    }

}

void Graphe::Pareteo(unsigned int vect_size)
{
    std::cout << vect_size << std::endl << std::endl;
    std::vector<short>bin_Vect;
    std::vector<std::vector<short>>bin_Vect_Good;
    std::vector<int>ID_Test;
    std::vector<std::vector<float>>weight_sum;
    std::vector<float>weigh_sum_local;
    std::vector<Arete>vect_Aret;
    std::vector<Graphe>vect_Gph_Processed;
    int NmbreTotalEssais = pow(2,m_Aretes.size());
    unsigned int buffer;
    float Sigma = 0;

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
        for(unsigned int j = 0; j < bin_Vect.size(); j++)
        {
            buffer = buffer + bin_Vect[j];
        }
        // std::cout << buffer << "  " << vect_size << std::endl;
        if(buffer == (m_sommets.size() - 1))
        {
            if(bin_Vect.size() <= vect_size)
            {
                bin_Vect.push_back(0);
            }
            std::reverse(bin_Vect.begin(), bin_Vect.end());
            bin_Vect_Good.push_back(bin_Vect);
        }
    };


    ///Test connexite : TO OPTIMIZE

    for(unsigned int i = 0; i < bin_Vect_Good.size(); i++)
    {
        for(unsigned int j = 0; j < bin_Vect_Good[i].size(); j++)
        {
            if(bin_Vect_Good[i][j] == 1)
            {
                if(std::find(ID_Test.begin(), ID_Test.end(), m_Aretes[j].GetSommet1())==ID_Test.end())
                {
                    ID_Test.push_back(m_Aretes[j].GetSommet1());
                }
                if(std::find(ID_Test.begin(), ID_Test.end(), m_Aretes[j].GetSommet2())==ID_Test.end())
                {
                    ID_Test.push_back(m_Aretes[j].GetSommet2());
                }
            }
        }

        if(ID_Test.size() < m_sommets.size())
        {
            bin_Vect_Good.erase(bin_Vect_Good.begin()+i);
        }
        ID_Test.clear();
    }
    bin_Vect_Good.erase(bin_Vect_Good.begin());

    std::cout << bin_Vect_Good.size() << "  " << m_Aretes.size() << " ///: " << bin_Vect_Good[0].size() << std::endl;

    for(unsigned int i = 0 ; i < bin_Vect_Good.size(); i++)
    {
        for(unsigned int j = 0; j < bin_Vect_Good[i].size() ; j++)
        {
            if(bin_Vect_Good[i][j] == 1)
            {
                vect_Aret.push_back(m_Aretes[j]);
            }
        }
        vect_Gph_Processed.push_back(Graphe(m_sommets,vect_Aret));
        vect_Aret.clear();
    }

    for(unsigned int i = 0; i < 2; i++)
    {
        for(unsigned int j = 0; j < bin_Vect_Good.size(); j++)
        {
            for(unsigned int k = 0; k < bin_Vect_Good[j].size(); k++)
            {
                if(bin_Vect_Good[j][k] == 1)
                {
                    Sigma = Sigma + m_Aretes[k].GetPoids(i);
                }
            }
            weigh_sum_local.push_back(Sigma);
            Sigma = 0;
        }
        weight_sum.push_back(weigh_sum_local);
        weigh_sum_local.clear();
    }
    buffer = 0;
    for(unsigned int i = 0; i < weight_sum[0].size(); i++)
    {

        buffer = sqrt(pow(weight_sum[0][i],2)  + pow(weight_sum[1][i],2));
        std::cout << weight_sum[0][i] << " " << weight_sum[1][i];
        std::cout <<" DISTANCE TO UNITY  : " << buffer  << std::endl;

            vect_Gph_Processed[i].DisplayGraphe();
    }
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

