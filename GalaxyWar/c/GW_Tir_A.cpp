#ifndef GW_TIR_A_C
#define GW_TIR_A_C

#include "../h/GW_Tir_A.hpp"

#define GW_NAMECLASS GW_Tir_A

bool GW_NAMECLASS::exists = false;

bool GW_NAMECLASS::IsDead(void) const
{
    return end;
}

/*float GW_NAMECLASS::Delai(CSInt32 level)
{
    return 0.25f;
}*/

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += vx*dt;
    y -= vy*dt;
}

float GW_NAMECLASS::GetRadius(void) const
{
    return (0.25 + 0.075*Level)*size/3.f;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle)
{
    Level = level;
    scaleX = (0.25 + 0.075*Level)*size/3.f;
    scaleY = scaleX;
    dmax = scaleX;
    end = false;
    type = TA;
    angle = Angle;
    x = X;
    y = Y;
    float vty = cos(Angle);
    vx = sin(Angle) * VITESSE;
    vy = vty*vty*vty * VITESSE;
    angle += 3*M_PI/2;
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    if (Level < malus)
    {
        return 0.f;
    }
    return Level-malus;
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}

void GW_NAMECLASS::Tirs_Generate(CSInt32 level, cfloat x, cfloat y, float* t, GW_ArrayList<GW_Tir> *list)
{
    //printf("ee%dee", level);
    if (level <= 0)
    {
        return;
    }
    /*if (t[1] < 0.25 && t[1] != 0)
    {
        t[0] = 0;
        return;
    }*/
    //float dt = *t - *lt;
    //printf("b %.3f %.3f %.3f\n", *t, *lt, dt);
    if (t[2] >= 0.25)
    {
        t[2] = 0;
        float maxalpha = (1 - (1.f/(level+6))*7)*M_PI/4, da = maxalpha*2/level;
        int i = 0;
        maxalpha -= da/2;
        if (level&1)
        {
            while (i <= level/2)
            {
                i++;
                list->Add(new GW_NAMECLASS(i, x, y, maxalpha));
                maxalpha -= da;
            }
            while (i > 1)
            {
                i--;
                list->Add(new GW_NAMECLASS(i, x, y, maxalpha));
                maxalpha -= da;
            }
        }
        else
        {
            while (i < level/2)
            {
                i++;
                list->Add(new GW_NAMECLASS(i, x, y, maxalpha));
                maxalpha -= da;
            }
            while (i > 0)
            {
                list->Add(new GW_NAMECLASS(i, x, y, maxalpha));
                maxalpha -= da;
                i--;
            }
        }
    }
}
#undef GW_NAMECLASS
#endif
