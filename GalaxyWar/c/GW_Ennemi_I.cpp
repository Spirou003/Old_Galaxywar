#ifndef GW_ENNEMI_I_C
#define GW_ENNEMI_I_C

#include "../h/GW_Ennemi_I.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"
#include "../h/GW_TSL.hpp"

#define GW_NAMECLASS GW_Ennemi_I

bool GW_NAMECLASS::exists = false;

bool GW_NAMECLASS::IsCollisionnable(void) const
{
    return !isTeleport;
}

void GW_NAMECLASS::Teleport(void)
{
    isTeleport = true;
    nx = Random(width, GW_LARGEUR - width);
    ny = Random(height, GW_HAUTEUR/2 - height);
    if (t2 > 30)
    {
        nx = -100000*dmax;
        ny = -100000*dmax;
    }
}

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EI;
    PV = PV_BASE;
    dmax = 22;
    scaleX = 1;
    scaleY = 1;
    angle = M_PI/2;
    Time = 0;
    t = Random(0.3f, 1.f + 3.f/(id+1));
    t2 = 0;
    x = -width/2;
    y = -height/2;
    idDraw = 1;
    alpha = 0;
    /*isTeleport = true;
    nx = Random(-x, GW_LARGEUR + x);
    ny = Random(-y, GW_HAUTEUR/2 + y);*/
    this->Teleport();
    if (IsBoost)
    {
        PV *= 5;
    }
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    t2 += dt;
    if (isTeleport)
    {
        alpha += dt;
        if (alpha > 1)
        {
            alpha = 0;
            isTeleport = false;
            x = nx;
            y = ny;
        }
        return;
    }
    else
    {
        angle = GW_FloatModulo(GW_Angle(x, truc->Joueur->GetX(), y, truc->Joueur->GetY()), 2*M_PI);
        t -= dt;
        if (t < 0)
        {
            t = Random(0.3f, 1.f + 3.f/(id+1));
            truc->Tirs_Ennemi.Add(new GW_Tir_Z(id+1, x + 9*GW_Cos(angle), y + 9*GW_Sin(angle), angle));
            idDraw = 1;
        }
        else if (t < 0.07)
        {
            idDraw = 3;
        }
        else if (t < 0.15)
        {
            idDraw = 2;
        }
    }
    Time -= dt;
    if (Time < 0)
    {
        Time = Random(0.3f * (2-id), 1.f + 5.f/(id+1));
        /*isTeleport = true;
        nx = Random(width, GW_LARGEUR - width);
        ny = Random(height, GW_HAUTEUR/2 - height);*/
        this->Teleport();
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}

bool GW_NAMECLASS::IsDead(void) const
{
    return (PV <= 0.f);
}

bool GW_NAMECLASS::IsOut(void) const
{
    return ((y + dmax < 0) || (y - dmax > GW_HAUTEUR) || (x + dmax < 0) || (x - dmax > GW_HAUTEUR));
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    if (isTeleport)
    {
        return 0;
    }
    else if (rand()&1)
    {
        PV-= tir->Power();
        tir->End();
    }
    this->Teleport();
    if (this->IsDead())
    {
        return this->Points();
    }
    else
    {
        return 0;
    }
}

int GW_NAMECLASS::Points(void) const
{
    return 40*(4*id+1);
}
#undef GW_NAMECLASS
#endif
