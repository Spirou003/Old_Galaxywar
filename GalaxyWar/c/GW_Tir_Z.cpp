#ifndef GW_TIR_Z_C
#define GW_TIR_Z_C

#include "../h/GW_Tir_Z.hpp"

#define GW_NAMECLASS GW_Tir_Z

bool GW_NAMECLASS::exists = false;

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

void GW_NAMECLASS::Tirs_Generate(CSInt32 level, cfloat x, cfloat y, float* t, GW_ArrayList<GW_Tir> *list)
{
    if (level <= 0)
    {
        return;
    }
    cfloat T = 1.f/(level+3);
    /*t[2] -= t[1];
    t[1] = 0;*/
    UInt32 n = t[2]/T;
    CSInt32 lev = int(level/2.5)+1;
    cfloat maxalpha = ((1.f/(level+7))*7)*M_PI/2;
    if (n > 0)
    {
        t[2] = 0;
        if (n > 100)
        {
            n = 100;
        }
        while (n > 0)
        {
            n--;
            list->Add(new GW_NAMECLASS(lev, x, y, Random(float(maxalpha+M_PI), float(2*M_PI-maxalpha)), true));
        }
    }
    /*while (t[2] >= T)
    {
        if (dt >= T)
        {
            dt -= T;

        }*/
        /*float dt = t[0] - t[1];
        while (dt > T)
        {
            dt = T;
            t[0] = 0;
        }
        t[1] = 0;*/
    //}
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += vx*dt*(1+id*0.5f);
    y += vy*dt*(1+id*0.5f);
}

float GW_NAMECLASS::GetRadius(void) const
{
    return (1 + 0.3*(Level/2.f-0.5f))*3;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle, cbool IsPlayer) : id(IsPlayer)
{
    Level = level;
    ID = 255;
    end = false;
    type = TZ;
    x = X;
    y = Y;
    angle = GW_FloatModulo(Angle, 2*M_PI);
    vx = GW_Cos(angle) * Vitesse;
    vy = GW_Sin(angle) * Vitesse;
    if (IsPlayer)
    {
        vx *= 3;
        vy *= 3;
    }
    PV = ((Level*(Level+1))/2);
    scaleX = (1 + 0.3*(Level/2.f-0.5f))*3;
    scaleY = scaleX;
    dmax = scaleX;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if (id)
    {
        return PV;
    }
    if (Level < malus)
    {
        return 1.f/(1 << (malus-Level));
    }
    return (1 << (Level-malus));
}

GW_NAMECLASS::~GW_NAMECLASS(void){;}
#undef GW_NAMECLASS
#endif
