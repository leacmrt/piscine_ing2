#include <unordered_map>
#include <iostream>
#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <Sommet.h>
#include <Arete.h>

class Graphe
{
    public:
        Graphe();
        Graphe(std::vector<Sommet>sommetVector, std::vector<Arete>areteVector);

        Graphe(std::string filename);
        virtual ~Graphe();

        void KruskalAlgo();
        void TrierGraphe(int ID_Pds);
        std::string Getn_name() { return m_name; }
        void Setn_name(std::string val) { m_name = val; }
        unsigned int Getm_ordre() { return m_sommets.size(); }
        void Setm_ordre(unsigned int val) { m_ordre = val; }
        unsigned int Gettaille() { return m_Aretes.size(); }
        void Settaille(unsigned int val) { m_taille = val; }
        void AddArete(int id_1, int id_2)
        {
            m_Aretes.push_back(Arete());
        }
        void DisplaySommet(int ID)
        {
            m_sommets[ID].DispSommet();
        }
        void DisplayArete(int ID)
        {
            m_Aretes[ID].DispArete();
        }
        void DisplayGraphe()
        {
            std::cout << " ARETES  " << m_Aretes.size() << std::endl;

            for(unsigned int i = 0; i < m_Aretes.size(); i++)
            {
                std::cout << m_Aretes[i].GetSommet1() << " = " << m_Aretes[i].GetSommet2();
                std::cout <<  "weight : " << m_Aretes[i].GetPoids(0) << std::endl;
            }
        }
        void AddAdja(int ID_Somm_1, int ID_Somm_2)
        {
            m_sommets[ID_Somm_1].AddAdja(&(m_sommets[ID_Somm_2])); ///Ajouter l'adjansense
        }
        std::vector<Sommet*> getAdja(int ID)
        {
            return m_sommets[ID].getAdja();
        }
        void SortArete(int critere);
        void Pareteo(const unsigned int vect_size);


    protected:

    private:
        std::string m_name;
        unsigned int m_ordre;
        unsigned int m_taille;
        std::vector<Sommet> m_sommets;
        std::vector<Arete> m_Aretes;

};

#endif // GRAPHE_H
