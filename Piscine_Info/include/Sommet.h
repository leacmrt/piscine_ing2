#include <vector>
#include <string>
#include <iostream>
#ifndef SOMMET_H
#define SOMMET_H


class Sommet
{
    public:
        Sommet();
        virtual ~Sommet();
        Sommet(std::string id, double x, double y);

        std::string GetID() { return m_ID; }
        void SetID(unsigned int val) { m_ID = val; }
        unsigned int GetposX() { return m_posX; }
        void SetposX(unsigned int val) { m_posX = val; }
        unsigned int GetposY() { return m_posY; }
        void SetposY(unsigned int val) { m_posY = val; }
        void DispSommet()
        {
            std::cout << m_ID << std::endl;
            std::cout << m_posX << std::endl;
            std::cout << m_posY << std::endl;
        }
        void AddAdja(Sommet* ID_Adja)
        {
            m_Adja.push_back(ID_Adja);
        }



        void DispAdja()
        {
            for(int i = 0; i < m_Adja.size(); i++)
            {
                (*m_Adja[i]).DispSommet();

            }
            std::cout << std::endl;
        }

    protected:

    private:
        std::string m_ID;
        double m_posX;
        double m_posY;
        std::vector<Sommet*> m_Adja;
        std::vector<int> m_Adja_ID;
};

#endif // SOMMET_H
