#ifndef GW_TIR_X_C
#define GW_TIR_X_C

#include "../h/GW_Tir_X.hpp"

#define GW_NAMECLASS GW_Tir_X

const Color GW_NAMECLASS::CTab[NCOLOR] =
{
Color(255, 0, 0, 255),
Color(255, 128, 0, 255),
Color(255, 255, 0, 255),
Color(0, 255, 0, 255),
Color(0, 255, 255, 255),
Color(0, 0, 255, 255),
Color(255, 0, 255, 255),
Color(255, 255, 255, 255)
};

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += vx*dt;
    y += vy*dt;
    a += dt*va;
    if (a > 2*M_PI)
    {
        a -= 2*M_PI;
    }
    else if (a < 0)
    {
        a += 2*M_PI;
    }
}

float GW_NAMECLASS::GetRadius(void) const
{
    return (1 + 0.3*(Level/2.f-0.5f))*3;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle)
{
    Level = level;
    end = false;
    c = &CTab[Random(0, NCOLOR-1)];
    type = TX;
    x = X;
    y = Y;
    angle = GW_FloatModulo(Angle, 2*M_PI);
    vx = GW_Cos(angle) * Vitesse;
    vy = GW_Sin(angle) * Vitesse;
    if (Random(0, 100)<50)
    {
        va = Random(float(M_PI), 1.5f)*2;
    }
    else
    {
        va = Random(-1.5f, float(-M_PI))*2;
    }
    a = 0;
    scaleX = 8;
    scaleY = 5;
    dmax = scaleX;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if (Level < malus)
    {
        return 1.f/(1 << (malus-Level));
    }
    return (1 << (Level-malus));
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}
#undef GW_NAMECLASS
#endif
