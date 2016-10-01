#ifndef GW_ENNEMI_C_C
#define GW_ENNEMI_C_C

#include "../h/GW_Ennemi_C.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"

#define GW_NAMECLASS GW_Ennemi_C

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    Time = 0;
    type = EC;
    PV = PV_BASE;
    VITESSE = Random(20, 40);
    angle = 0;
    dmax = size;
    scaleX = dmax/2 - 4;
    scaleY = scaleX;
    if (IsBoost)
    {
        PV *= 5;
    }
    x = Random(size, GW_LARGEUR-size);
    y = -size/2;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time += dt;
    angle += dt*M_PI;
    y += dt*VITESSE;
    if ((id == 1 && Time > TIMETIR/1.5) || (Time > TIMETIR))
    {
        Time -= TIMETIR/(1+id*0.5);
        int i = 0;
        while (i < NBTIR)
        {
            truc->Tirs_Ennemi.Add(new GW_Tir_Z(id*2+1, x, y, angle+M_PI/8/**/+(i*2*M_PI/NBTIR)/**/, false));
            i++;
        }
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}

bool GW_NAMECLASS::IsDead(void) const
{
    return (PV <= 0);
}

bool GW_NAMECLASS::IsOut(void) const
{
    return ((y - size > GW_HAUTEUR));
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    PV-= tir->Power();
    tir->End();
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
    return 25*(5*id+1);
}
#undef GW_NAMECLASS
#endif
