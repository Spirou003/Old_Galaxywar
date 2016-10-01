#ifndef GW_COLLISIONNABLEADMIN_DRAW_C
#define GW_COLLISIONNABLEADMIN_DRAW_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

#include "../h/GW_Palette.hpp"

#include "../h/GW_BoomAnim.hpp"
#include "../h/GW_Number.hpp"
#include "../h/GW_Fleur.hpp"
#include "../h/GW_Bulle.hpp"
#include "../h/GW_VolatileAdmin.hpp"

bool GW_Ennemi_A::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_B::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_C::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_D::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_E::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_F::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    int i = 0;
    while (i < 5)
    {
        truc->Unites.Add(new GW_Ennemi_E(i/2 + id*3, x, y));
        i++;
    }
    return true;
}

bool GW_Ennemi_G::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_H::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_I::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_J::Dead(GW_JeuData* truc, RenderWindow* App)
{
    if (pts != 0)
    {
        truc->VolatiList->Add(GW_Number::RandomCreate(x, y, this->Points()));
    }
    float i = 0, j = 0;
    while (i < size)
    {
        j = Random(size/5, size/2);
        i += j/5;
        truc->VolatiList->Add(GW_Bulle::Create(x, y, j, id));
    }
    return true;
}

bool GW_Ennemi_K::Dead(GW_JeuData* truc, RenderWindow* App)
{
    if (toPos != -1)
    {
        toPos = -1;
        int i = 0, k = 7*(id+1);
        while (i < k)
        {
            truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x, y, i*2*M_PI/k, *Palette->GetID(Random(0, 599)/100)));
            i++;
        }
    }
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Ennemi_L::Dead(GW_JeuData* truc, RenderWindow* App)
{
    int i = 0;
    while (i < 12)
    {
        i++;
        truc->VolatiList->Add(GW_Fleur::Create(GW_RandomEcart(x, VITESSE), GW_RandomEcart(y, VITESSE)));
    }
    truc->VolatiList->Add(GW_Number::RandomCreate(x, y, this->Points()));
    return true;
}

bool GW_Joueur::Dead(GW_JeuData* truc, RenderWindow* App)
{
    //GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

bool GW_Tir_A::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Tir_GenericDead(this, truc, App);
    return true;
}

bool GW_Tir_B::Dead(GW_JeuData* truc, RenderWindow* App)
{
    return true;
}

bool GW_Tir_C::Dead(GW_JeuData* truc, RenderWindow* App)
{
    if (Level-15+nbdiv <= 0 || !state)
    {
        return true;
    }
    int i = 0;
    while (i < nbdiv)
    {
        i++;
        truc->Tirs_Joueur.Add(new GW_Tir_C(Level-15+nbdiv, x, y, Random(0.f, 2*M_PI), true, nbdiv - 2));
    }
    return true;
}

bool GW_Tir_Kube::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Tir_GenericDead(this, truc, App);
    return true;
}

bool GW_Tir_X::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Tir_GenericDead(this, truc, App);
    return true;
}

bool GW_Tir_Y::Dead(GW_JeuData* truc, RenderWindow* App)
{
    return true;
}

bool GW_Tir_Z::Dead(GW_JeuData* truc, RenderWindow* App)
{
    GW_CollisionnableAdmin::GW_Tir_GenericDead(this, truc, App);
    return true;
}

#endif
