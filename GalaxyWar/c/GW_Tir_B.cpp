#ifndef GW_TIR_B_C
#define GW_TIR_B_C

#include "../h/GW_Tir_B.hpp"

#define GW_NAMECLASS GW_Tir_B

bool GW_NAMECLASS::exists = false;

bool GW_NAMECLASS::IsDead(void) const
{
    return state;
}

void GW_NAMECLASS::End(void)
{
    if (end)
    {
        return;
    }
    end = true;
    t = 0;
    s = 0;
    ID = 0;
    dmax = 30*r/6;
    scaleX = dmax;
    scaleY = scaleX;
}

bool GW_NAMECLASS::IsCollisionnable(void) const
{
    return ((!end) || (p != 0 && ID));
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    t += dt;
    if (!end)
    {
        angle += dt;
        if (angle > 2*M_PI)
        {
            angle -= 2*M_PI;
        }
        x += vx*dt;
        y += vy*dt;
        while (t > 0.7)
        {
            t -= 0.7;
        }
        ID = int(5*t/0.7);
    }
    else
    {
        if (t > 0.5)
        {
            t = 0.5;
            state = true;
            return;
        }
        else if (ID && p != 0)
        {
            p = 0;
        }
        else if (t > 0.25)
        {
            ID = 1;
        }
    }
}

float GW_NAMECLASS::GetRadius(void) const
{
    if (end)
    {
        return scaleX;
    }
    else
    {
        return r;
    }
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle, cbool isdecalled): r(6+level/2.f)
{
    end = false;
    Level = level;
    scaleX = r;
    scaleY = scaleX;
    dmax = scaleX;
    type = TB;
    ID = Random(0, 4);
    angle = Angle;
    x = X;
    y = Y;
    state = false;
    t = 0;
    s = 1;
    vx = GW_Cos(angle)*VITESSE;
    vy = GW_Sin(angle)*VITESSE;
    if (isdecalled)
    {
        vx *= 0.7;
        vy *= 0.7;
    }
    angle = 0;
    p = level*0.5;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if (end && t < 0.25)
    {
        return 0;
    }
    else
    {
        return p;
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
    if (t[2] > 0.3)
    {
        list->Add(new GW_NAMECLASS(level, x, y, 3*M_PI/2));
        t[2] = 0;
    }
    if (t[0] > 0.1 && Random(0, 100) < int(50*(1 - 20.f/((level + 19)))))
    {
        list->Add(new GW_NAMECLASS(level/2, x, y, GW_RandomEcart(3*M_PI/2, M_PI/12), true));
        t[0] = 0;
    }
}
#undef GW_NAMECLASS
#endif
