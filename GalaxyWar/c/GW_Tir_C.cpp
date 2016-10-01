#ifndef GW_TIR_C_C
#define GW_TIR_C_C

#include "../h/GW_Tir_C.hpp"

#define GW_NAMECLASS GW_Tir_C

bool GW_NAMECLASS::exists = false;

void GW_NAMECLASS::End(void)
{
    state = true;
    end = true;
}

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

bool GW_NAMECLASS::IsCollisionnable(void) const
{
    return (!ID || (ID && t > 0.15));
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    t += dt;
    if (ID)
    {
        if (t > 0.5)
        {
            t = 0.5;
            end = true;
        }
        //id = int(5*t/0.05)%5;
        x += vx*dt*(0.5-t);
        y += vy*dt*(0.5-t);
    }
    else
    {
        while (t > 0.25)
        {
            t -= 0.25;
        }
        //id = int(5*t/0.05)%5;
        x += vx*dt;
        y += vy*dt;
    }
}

float GW_NAMECLASS::GetRadius(void) const
{
    return 30+2*Level;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle, cbool isdecalled, CSInt32 Ndiv): ID(isdecalled)
{
    end = false;
    state = false;
    Level = level;
    scaleX = this->GetRadius()/2;
    scaleY = scaleX*height/width;
    dmax = scaleX;
    type = TC;
    angle = Angle;
    x = X;
    y = Y;
    t = 0;
    id = Random(0, 4);
    s = scaleX*2/width;
    vx = GW_Cos(angle)*VITESSE;
    vy = GW_Sin(angle)*VITESSE;
    nbdiv = Ndiv;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if ((ID && t < 0.15) || end)
    {
        return 0;
    }
    else if (ID)
    {
        return Level/3.;
    }
    else
    {
        return Level;
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}

void GW_NAMECLASS::Tirs_Generate(CSInt32 level, cfloat x, cfloat y, float* t, GW_ArrayList<GW_Tir> *list)
{
    if (level <= 0)
    {
        return;
    }
    if (t[2] > 1/3.)
    {
        list->Add(new GW_NAMECLASS(level, x, y, 3*M_PI/2));
        t[2] = 0;
    }
}
#undef GW_NAMECLASS
#endif
