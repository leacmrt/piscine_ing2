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
        Graphe(std::string filename);
        virtual ~Graphe();

        std::string Getn_name() { return m_name; }
        void Setn_name(std::string val) { m_name = val; }
        unsigned int Getm_ordre() { return m_ordre; }
        void Setm_ordre(unsigned int val) { m_ordre = val; }
        unsigned int Gettaille() { return m_taille; }
        void Settaille(unsigned int val) { m_taille = val; }
        void AddArete(int id_1, int id_2)
        {
            m_Aretes.push_back(Arete());
        }
        void DisplaySommet(int ID)
        {
            m_sommets[ID].DispSommet();
        }
        void AddAdja(int ID_Somm_1, int ID_Somm_2)
        {
            m_sommets[ID_Somm_1].AddAdja(&(m_sommets[ID_Somm_2])); ///Ajouter l'adjansense
        }

    protected:

    private:
        std::string m_name;
        unsigned int m_ordre;
        unsigned int m_taille;
        std::vector<Sommet> m_sommets;
        std::vector<Arete> m_Aretes;

};

#endif // GRAPHE_H
