#include "Sommet.h"

Sommet::Sommet(std::string id, double x, double y)
{
    m_posX = x;
    m_posY = y;
    m_ID = id;
}

Sommet::Sommet()
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}
