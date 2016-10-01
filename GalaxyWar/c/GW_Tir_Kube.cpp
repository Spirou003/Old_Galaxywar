#ifndef GW_TIR_KUBE_C
#define GW_TIR_KUBE_C

#include <SFML/Graphics/Color.hpp>

#include "../h/GW_Tir_Kube.hpp"

#define GW_NAMECLASS GW_Tir_Kube

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += vx*dt;
    y += vy*dt;
    a += dt*3*M_PI;
    if (a > M_PI/2)
    {
        a = 0;
    }
}

float GW_NAMECLASS::GetRadius(void) const
{
    return (SizeKube+2)/2;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle, const Color &couleur)
{
    Level = level;
    a = 0.f;
    scaleX = SizeKube/2;
    scaleY = SizeKube/2;
    dmax = SizeKube*1.4;
    end = false;
    type = TKU;
    x = X;
    y = Y;
    angle = GW_FloatModulo(Angle, 2*M_PI);
    c = new Color(couleur);
    vx = GW_Cos(angle) * Vitesse;
    vy = GW_Sin(angle) * Vitesse;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    return Level*30;
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    delete(c);
}

#undef GW_NAMECLASS
#endif
