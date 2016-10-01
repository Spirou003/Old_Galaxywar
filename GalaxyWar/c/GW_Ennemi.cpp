#ifndef GW_ENNEMI_C
#define GW_ENNEMI_C

#include "../h/GW_Ennemi.hpp"

GW_Ennemi::GW_Ennemi    (void)      {}
GW_Ennemi::~GW_Ennemi   (void)      {}

void GW_Ennemi::AddResistances(GW_Ennemi* obj, CSInt32 Niv)
{
    int i = 0;
    while (i < GW_NBARME)
    {
        obj->Resistances[i] = 0;
        i++;
    }
}

#endif
