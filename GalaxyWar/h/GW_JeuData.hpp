#ifndef GW_JEUDATA_H
#define GW_JEUDATA_H

#include "../t/GW_ArrayList.hpp"
class GW_Ennemi;
class GW_Joueur;
class GW_Tir;
class GW_VolatileAdmin;

struct GW_JeuData
{
    GW_Joueur *Joueur;
    GW_ArrayList<GW_Tir> Tirs_Ennemi, Tirs_Joueur;
    GW_ArrayList<GW_Ennemi> Unites;
    GW_VolatileAdmin *VolatiList;
    int Niveau;
};
#endif
