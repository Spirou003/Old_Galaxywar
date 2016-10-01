#ifndef GW_TIR_Y_C
#define GW_TIR_Y_C

#include "../h/GW_Tir_Y.hpp"
#include "../h/GW_TSL.hpp"
#include "../h/GW_Functions.hpp"

#define GW_NAMECLASS GW_Tir_Y

bool GW_NAMECLASS::exists = false;

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += vx*dt;
    y += vy*dt;
    id += dt;
    a+= dt*135;
    if (id > 1)
    {
        id -= 1;
        ID = (ID+1)%3;
    }
}

float GW_NAMECLASS::GetRadius(void) const
{
    return scaleX;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle)
{
    Level = level;
    ID = Random(0, 2);
    sens = 1;
    if (Random(0, 100)<50)
    {
        sens = -sens;
    }
    id=0;
    a = 0;
    end = false;
    type = TY;
    x = X;
    y = Y;
    angle = GW_FloatModulo(Angle, 2*M_PI);
    vx = GW_Cos(angle) * Vitesse;
    vy = GW_Sin(angle) * Vitesse;
    angle = 0;
    scaleX = 10+2*Level;
    scaleY = scaleX;
    dmax = scaleX;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if (Level < malus)
    {
        return 4.f/(1 << (malus-Level));
    }
    return (4 << (Level-malus));
}

GW_NAMECLASS::~GW_NAMECLASS(void){;}

#undef GW_NAMECLASS
#endif
