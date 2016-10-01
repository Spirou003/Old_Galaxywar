#ifndef GW_COLLISIONNABLEADMIN_DRAW_C
#define GW_COLLISIONNABLEADMIN_DRAW_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

void GW_Ennemi_A::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEA[0].GetImage());
    delete(SPRITEA[1].GetImage());
    exists = false;
}

void GW_Ennemi_B::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEB[0].GetImage());
    delete(SPRITEB[1].GetImage());
    exists = false;
}

void GW_Ennemi_C::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEC[0].GetImage());
    delete(SPRITEC[1].GetImage());
    exists = false;
}

void GW_Ennemi_D::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITED[0][0].GetImage());
    delete(SPRITED[1][0].GetImage());
    delete(SPRITED[0][1].GetImage());
    delete(SPRITED[1][1].GetImage());
    exists = false;
}

void GW_Ennemi_E::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEE[0][0].GetImage());
    delete(SPRITEE[0][1].GetImage());
    delete(SPRITEE[0][2].GetImage());
    delete(SPRITEE[1][0].GetImage());
    delete(SPRITEE[1][1].GetImage());
    delete(SPRITEE[1][2].GetImage());
    exists = false;
}

void GW_Ennemi_F::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEF[0].GetImage());
    delete(SPRITEF[1].GetImage());
    exists = false;
}

void GW_Ennemi_G::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEG[0].GetImage());
    delete(SPRITEG[1].GetImage());
    exists = false;
}

void GW_Ennemi_H::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITEH[0][0].GetImage());
    delete(SPRITEH[0][1].GetImage());
    delete(SPRITEH[1][0].GetImage());
    delete(SPRITEH[1][1].GetImage());
    exists = false;
}

void GW_Ennemi_I::Close(void)
{
    if (!exists)
    {
        return;
    }
    int i = 0;
    while (i < 4)
    {
        delete(SPRITEI[0][i].GetImage());
        delete(SPRITEI[1][i].GetImage());
        i++;
    }
    exists = false;
}

void GW_Ennemi_J::Close(void)
{
    if (!exists)
    {
        return;
    }
    int i = 0;
    while (i < 6)
    {
        delete(SPRITEJ[0][i].GetImage());
        delete(SPRITEJ[1][i].GetImage());
        i++;
    }
    delete(NOYAU.GetImage());
    exists = false;
}

void GW_Ennemi_K::Close(void){;}

void GW_Ennemi_L::Close(void){;}

void GW_Joueur::Close(void)
{
    if (!exists)
    {
        return;
    }
    int i = 0;
    while (i < 4)
    {
        delete(SPRITEJOUEUR[i].GetImage());
        i++;
    }
}

void GW_Tir_A::Close(void)
{
    if (exists)
    {
        delete(SPRITIR.GetImage());
        exists = false;
    }
}

void GW_Tir_B::Close(void)
{
    if (!exists)
    {
        return;
    }
    int i = 0;
    while (i < 6)
    {
        delete(SPRITIR[i].GetImage());
        i++;
    }
    exists = false;
}

void GW_Tir_C::Close(void)
{
    if (!exists)
    {
        return;
    }
    int i = 0;
    while (i < 5)
    {
        delete(SPRITIR[i].GetImage());
        i++;
    }
    exists = false;
}

void GW_Tir_Kube::Close(void)   {;}

void GW_Tir_X::Close(void)      {;}

void GW_Tir_Y::Close(void)
{
    if (exists)
    {
        return;
    }
    delete(GW_Tir_Y::SPRITIR[0].GetImage());
    delete(GW_Tir_Y::SPRITIR[1].GetImage());
    delete(GW_Tir_Y::SPRITIR[2].GetImage());
    exists = false;
}

void GW_Tir_Z::Close(void)      {;}

#endif
