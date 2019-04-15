#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"
#include "Poids.h"

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

        float GetPoids(int poids_ID) { return m_Poids[poids_ID]; }
        int GetPoidsDimension() { return m_Poids.size(); }

        void AddPoids(float poids)
        {
            m_Poids.push_back(poids);
        }
        void DispArete()
        {
            std::cout << m_sommets_ID.first << std::endl;
            std::cout << m_sommets_ID.second << std::endl;
            for(int i = 0; i < m_Poids.size(); i++)
            {
               std::cout <<  m_Poids[i] << "  " << std::endl;
            }
            std::cout << std::endl;
        }

        bool pred(Arete *a1, Arete *a2)
        {
            return a1->m_Poids[0] > a2->m_Poids[0];
        }

    protected:

    private:
        Sommet m_sommet1;
        Sommet m_sommet2;
        std::vector <float>m_Poids;
        std::pair <int, int> m_sommets_ID;
};

#endif // ARETE_H
