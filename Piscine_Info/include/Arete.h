#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"

class Arete
{
    public:
        Arete();
        Arete(int ID_1, int ID_2, Sommet S1, Sommet S2)
        {
            m_sommets_ID = {ID_1, ID_2};
            m_sommet1 = S1;
            m_sommet2 = S2;
        }
        virtual ~Arete();

        int GetPoids(int poids_ID) { return m_Poids[poids_ID]; }
        int GetPoidsDimension() { return m_poids; }
        void Setpoids(int val) { m_poids = val; }
        void AddPoids(int poids)
        {
            m_Poids.push_back(poids);
        }
        void DispArete()
        {
            std::cout << m_sommets_ID.first << std::endl;
            std::cout << m_sommets_ID.second << std::endl;
        }

    protected:

    private:
        Sommet m_sommet1;
        Sommet m_sommet2;
        std::vector <int>m_Poids;
        std::pair <int, int> m_sommets_ID;
        int m_poids;
};

#endif // ARETE_H
