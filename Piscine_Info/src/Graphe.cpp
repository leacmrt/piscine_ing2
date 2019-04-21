#include <algorithm>
#include "Graphe.h"
#include "Arete.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <bitset>
#include <queue>
#include <allegro.h>


void Graphe::DrawGraph(BITMAP* buffer)
{
    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));
    for(unsigned int i = 0; i < m_sommets.size(); i++)
    {
        circlefill(buffer, m_sommets[i].GetposX(), m_sommets[i].GetposY(), 10, makecol(0,0,0));
    }
    for(unsigned int i = 0; i < m_Aretes.size(); i++)
    {
        line(buffer, m_sommets[m_Aretes[i].GetSommet1()].GetposX(),m_sommets[m_Aretes[i].GetSommet1()].GetposY(),
             m_sommets[m_Aretes[i].GetSommet2()].GetposX(),m_sommets[m_Aretes[i].GetSommet2()].GetposY(),makecol(100,0,0));
    }
}

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
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
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
        std::cout << "test" << ID_Somm1 << ID_Somm2 << std::endl;
    }


    for (unsigned int i = 0; i <ordre; i++)
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


Sommet Graphe::getSommet(int i)
{
    return m_sommets[i];
}
Arete Graphe::getArete(int i)
{
    return m_Aretes[i];
}
void Graphe::Pareteo(unsigned int vect_size, BITMAP* screen_buffer)
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
    std::cout << " CXIT" << std::endl;
    std::cout << "Taille " << m_Aretes.size() << " Ordre = " << m_sommets.size() << " Solutions totales : " << bin_Vect_Good.size() << std::endl;
    if(bin_Vect_Good.size() > 1000000)
    {
        for(unsigned int i = 0; i < (bin_Vect_Good.size()/1000); i++)
        {
            if(rand()%100 < 90 )
            {
                bin_Vect_Good.erase(bin_Vect_Good.begin()+i,bin_Vect_Good.begin()+i +1000);

            }
        }
    }
    std::cout << " NEW SIZE :" << bin_Vect_Good.size() << std::endl;

    std::pair<unsigned int, unsigned int>Init_Pair;
    std::vector<std::pair<unsigned int, unsigned int>>Vect_Pair;
    std::queue<unsigned int>Somm_Queue;

    ///Test connexite : TO OPTIMIZE

    for(unsigned int i = 0; i < bin_Vect_Good.size(); i++)
    {
        unsigned int CheckedValues[m_sommets.size()] = {0};
        for(unsigned int j = 0; j < bin_Vect_Good[i].size(); j++)
        {
            if(bin_Vect_Good[i][j] == 1)
            {
                Init_Pair.first = m_Aretes[j].GetSommet1();
                Init_Pair.second = m_Aretes[j].GetSommet2();
                Vect_Pair.push_back(Init_Pair);
            }
        }
        Somm_Queue.push(Vect_Pair[0].first);

        while(Somm_Queue.empty() == false)
        {
            unsigned int s_prec = Somm_Queue.front();
            CheckedValues[s_prec] = 1;
            for(unsigned int j = 0; j < Vect_Pair.size(); j++)
            {
                if(Vect_Pair[j].first == s_prec && CheckedValues[Vect_Pair[j].second] == 0)
                {
                    Somm_Queue.push(Vect_Pair[j].second);
                    CheckedValues[Vect_Pair[j].second] = 1;
                }
                if(Vect_Pair[j].second == s_prec && CheckedValues[Vect_Pair[j].first] == 0)
                {
                    Somm_Queue.push(Vect_Pair[j].first);
                    CheckedValues[Vect_Pair[j].first] = 1;
                }
            }
            Somm_Queue.pop();
        }
        for(unsigned int j = 0; j < m_sommets.size(); j++)
        {
            if(CheckedValues[j] == 0)
            {
                bin_Vect_Good.erase(bin_Vect_Good.begin() + i);
                i--;
                j = m_sommets.size();
            }
        }
        Vect_Pair.clear();

        /*

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
        */
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

    float test_wght0 = *(max_element(weight_sum[0].begin(),weight_sum[0].end()));
    float test_wght1 = *(max_element(weight_sum[1].begin(),weight_sum[1].end()));
    float test_wghtmin0 = *(min_element(weight_sum[0].begin(),weight_sum[0].end()));
    float test_wghtmin1 = *(min_element(weight_sum[1].begin(),weight_sum[1].end()));
    std::vector<float>GeomWeightAvrg;
    std::cout << test_wght0 << " AND  " << test_wght1 << std::endl;
    for(unsigned int i = 0; i < weight_sum[0].size(); i++)
    {
        //std::cin >> chx;

        buffer = sqrt(pow(weight_sum[0][i],2)  + pow(weight_sum[1][i],2));
        GeomWeightAvrg.push_back(buffer);
     //    std::cout << weight_sum[0][i] << " " << weight_sum[1][i];
     //   std::cout <<" DISTANCE TO UNITY  : " << buffer  << std::endl;

           // vect_Gph_Processed[i].DisplayGraphe();
//            vect_Gph_Processed[i].DisplayGraphe();
            vect_Gph_Processed[i].DrawGraph(screen_buffer);
            blit(screen_buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

            //vect_Gph_Processed[i].DisplayGraphe();
//
    }

    rectfill(screen_buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));
    std::cout <<  "PARETO INBOUND !!!!" <<std::endl;
    std::cin >> buffer;
    line(screen_buffer,test_wghtmin0,0,test_wghtmin0,SCREEN_H,makecol(255,0,0));
    line(screen_buffer,0,SCREEN_H-test_wghtmin1,SCREEN_W,SCREEN_H-test_wghtmin1,makecol(255,0,0));
    for(unsigned int i = 0; i < vect_Gph_Processed.size(); i++)
    {

        circle(screen_buffer,((weight_sum[0][i]/test_wght0)*SCREEN_W) - test_wghtmin0,
               SCREEN_H*(1 - weight_sum[1][i]/test_wght1) - test_wghtmin1 + 100,2, makecol(255,0,0));
    }
    blit(screen_buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    std::cout << "Nombre de chemions connexes " << vect_Gph_Processed.size() << std::endl;

    std::cin >> buffer;
    /*
    Graphe Bfr;

    for(int j = 0; j < vect_Gph_Processed.size(); j++)
    {
        for(int i = 1; i < vect_Gph_Processed.size(); i++)
        if(GeomWeightAvrg[i] < GeomWeightAvrg[i-1])
        {
            buffer = GeomWeightAvrg[i];
            GeomWeightAvrg[i] = GeomWeightAvrg[i-1];
            GeomWeightAvrg[i-1] = buffer;

            Bfr = vect_Gph_Processed[i];
            vect_Gph_Processed[i] = vect_Gph_Processed[i-1];
            vect_Gph_Processed[i-1] = Bfr;

        }
    }*/

}

void Graphe::Partie3(unsigned int vect_size, BITMAP* screen_buffer)
{
    std::vector<short>bin_Vect;
    unsigned int buffer;
    int iteration = pow(2,m_Aretes.size());
    std::vector<std::vector<short>>bin_Vals;
    std::cout << iteration << std::endl;
      for(int i = 0; i < iteration; i++)
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
        if(buffer >= m_sommets.size())
        {
            if(bin_Vect.size() <= m_sommets.size())
            {
                bin_Vect.push_back(0);
            }
            std::reverse(bin_Vect.begin(), bin_Vect.end());
            bin_Vals.push_back(bin_Vect);
            for(unsigned int j = 0; j < bin_Vect.size(); j++)
            {
                std::cout << bin_Vect[j];
            }
            std::cout << std::endl;
        }
    }
}


void Graphe::Prim(BITMAP* buffer ,Graphe j) // ici flemme donc on part pas d'un sommet au hasard mais du premier directement pour eviter de se compliquer la vie
{

    int chx; // l'utilisateur peut choisir sur quel poid il peut op�rer
    float primPoids;
    std::vector<Arete> possible; //vecteur d'aretes vide o� on va placer les aretes possibles cr�er avec le sommet utilis�
    std::vector<float> poids;
    std::vector<int*> affichage;
    int marque[m_sommets.size()]={0}; //au lieu d'utiliser booleen(trop complique)on cr�er un tableau de marque
    marque[0]=1; // on marque le premier sommet
    std::vector <int> primid; //une fois un sommet marqu� on le met dans prim -> arbre minimal
    primid.push_back(0);   //comme le premier sommet est marqu� on le push back dans primid
    std::cout << "Definissez l'objectif (de 0 � "<< m_Aretes[0].GetPoidsDimension() << std::endl;
    std::cin >> chx;                                                                                  // utilisateur rentre le choix poids


    for(auto i=0; i<m_sommets.size()-1;i++) //d'apr�s cours n-1
    {

        int variable=0; //variable � ajouter ensuite � possible
        for(auto j=0; j<m_Aretes.size(); j++) // 2 cas
        {

            if(marque[m_Aretes[j].GetSommet1()]==1 && marque[m_Aretes[j].GetSommet2()]!=1) //si premier s marqu� et sommet 2 -> c'est une arete possible
            {
                possible.push_back(m_Aretes[j]);
                //std::cout<<" sommet 1 arete : "<<a[j].GetSommet1()<<"Sommet 2:"<<a[j].GetSommet2()<<std::endl;
            }
            if(marque[m_Aretes[j].GetSommet1()]==0 && marque[m_Aretes[j].GetSommet2()]!=0) //si deuxieme s marqu� et sommet 1 -> c'est une arete possible
            {
                possible.push_back(m_Aretes[j]);
            }
        }


        //std::cout<<"a[variable].GetPoids(chx) :"<<a[variable].GetPoids(chx)<<std::endl;
        //std::cout<<"puis a[v].GetPoids(chx):"<<a[1].GetPoids(chx)<<std::endl;

        for(auto v=1; v<possible.size();v++)
        {
            if((possible[variable].GetPoids(chx))>(possible[v].GetPoids(chx)))
            {

               // v==*(affichage[i]);
                variable=v;


                // std::cout<<" rang_pmin:"<<v;
            }

           // std::cout<<" rang_pmin:"<<rang_Pmin;
        }

        primPoids=primPoids+((possible[variable]).GetPoids(chx));
       //std::cout<<"  marque[a[rang_Pmin].GetSommet1():" <<marque[a[rang_Pmin].GetSommet1()]<<std::endl;
       //std::cout<<"  marque[a[rang_Pmin].GetSommet2():" <<marque[a[rang_Pmin].GetSommet2()]<<std::endl;

        if(marque[possible[variable].GetSommet1()]==1)
        {
            marque[possible[variable].GetSommet2()]=1;
            primid.push_back(possible[variable].GetSommet2());
            //std::cout<<"  marque[a[rang_Pmin].GetSommet2() mtn:" <<marque[a[rang_Pmin].GetSommet2()]<<std::endl;

        }
        else if(marque[possible[variable].GetSommet2()]==1)
        {
            marque[possible[variable].GetSommet1()]=1;
            primid.push_back(possible[variable].GetSommet1());
        }
        possible.clear();
    }



    //Graphe(primid[]) //on cr� un nouveau graphe


    //maintenant affichage de l'arbre minimal
rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255)); // on affiche tout les sommets
    for(unsigned int i = 0; i < m_sommets.size(); i++)
    {
        circlefill(buffer, m_sommets[i].GetposX(), m_sommets[i].GetposY(), 10, makecol(0,0,0));
    }

/*

        for(auto p=0;p<primid.size()-1;++p)
        {
            for(auto i = 0; i < m_Aretes.size(); ++i)  // si 2 id de primid forment une arete alors on dessine cette arete
        {
       if((primid[p]==m_Aretes[i].GetSommet1())&&( primid[p+1]==m_Aretes[i].GetSommet2()))
        {

        line(buffer, m_sommets[m_Aretes[i].GetSommet1()].GetposX(),m_sommets[m_Aretes[i].GetSommet1()].GetposY(),
             m_sommets[m_Aretes[i].GetSommet2()].GetposX(),m_sommets[m_Aretes[i].GetSommet2()].GetposY(),makecol(100,0,0));
             break;

        }

       else if ((primid[p+1]==m_Aretes[i].GetSommet1())&&( primid[p]==m_Aretes[i].GetSommet2()))
       {
            line(buffer, m_sommets[m_Aretes[i].GetSommet1()].GetposX(),m_sommets[m_Aretes[i].GetSommet1()].GetposY(),
             m_sommets[m_Aretes[i].GetSommet2()].GetposX(),m_sommets[m_Aretes[i].GetSommet2()].GetposY(),makecol(100,0,0));
             break;

       }

       else if ((primid[p]==m_Aretes[i].GetSommet1())&&( primid[p-1]==m_Aretes[i].GetSommet2()))
       {
            line(buffer, m_sommets[m_Aretes[i].GetSommet1()].GetposX(),m_sommets[m_Aretes[i].GetSommet1()].GetposY(),
             m_sommets[m_Aretes[i].GetSommet2()].GetposX(),m_sommets[m_Aretes[i].GetSommet2()].GetposY(),makecol(100,0,0));
             break;
       }
       else // si dans prim id l'arete n'existe pas
        {
            line(buffer, m_sommets[primid[p]].GetposX(),m_sommets[primid[p]].GetposY(),
             m_sommets[primid[p+1]].GetposX(),m_sommets[primid[p+1]].GetposY(),makecol(100,0,0));
        }

}
} */// probleme des fois il faut revenir en ariere pour form� l'arete donc toutes aretes ne se forment pas dans l'abre minimal

 std::cout<<" Arbre minimal fait avec l'algorithme de Prim :"<<std::endl;

    for(auto t=0;t<m_sommets.size();t++)
    {
        std::cout<< "--> "<<primid[t];
    }

    Graphe k;
    for(auto p=0;p<m_sommets.size();p++)
    {
    k.m_sommets.push_back(m_sommets[p]);
    std::cout<<"Sommets: "<<k.m_sommets[p].GetID()<<std::endl;

    }

    for(auto j=0;j<primid.size()-1;j++)
    {
        k.m_Aretes.push_back(Arete(primid[j],primid[j+1],k.m_sommets[primid[j]],k.m_sommets[primid[j+1]]));
        std::cout<<"aretes: "<<k.m_Aretes[j].GetSommet1()<<" -"<<k.m_Aretes[j].GetSommet2()<<std::endl;
    }

    k.DrawGraph(buffer);

   std::cout<<" Donc poids minimal:"<<primPoids<<std::endl;

/*for (auto y=0;y<primid.size()-1;y++)
{
    std::cout<<"les aretes de primid :"<<primid[y]<<"- "<<primid[y+1]<<std::endl;

            line(buffer, m_sommets[primid[y]].GetposX(),m_sommets[primid[y]].GetposY(),
             m_sommets[primid[y+1]].GetposX(),m_sommets[primid[y+1]].GetposY(),makecol(100,0,0));
}*/


//Tu peux utiliser le constructeur de graphe
//En utilisant le vecteur d'Id avec ton vecteur de sommets pour cr�er un vecteur de sommets
//Et ensuite utiliser le vecteur d'ar�tes

}

