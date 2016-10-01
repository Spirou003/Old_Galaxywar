#ifndef GW_ENNEMI_B_C
#define GW_ENNEMI_B_C

#include "../h/GW_Ennemi_B.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"

#define GW_NAMECLASS GW_Ennemi_B

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EB;
    Time = 0;
    PV = PV_BASE;
    angle = M_PI/2;
    dmax = 20;
    scaleX = 1;
    scaleY = 1;
    ID = 0;
    if (IsBoost)
    {
        PV *= 5;
    }
    x = Random(width, GW_LARGEUR-width);
    y = -height/2;
    cx = 0;
    cy = 0;
    toY = Random(GW_HAUTEUR/8, GW_HAUTEUR/2);
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time += dt;
    switch(ID)
    {
        case 0:
            y += dt*VITESSE;
            if (y > toY)
            {
                y = toY;
                ID++;
            }
            break;
        case 1:
            if (Time > BEFORE)
            {
                if (cx == 0)
                {
                    a = GW_Angle(x, truc->Joueur->GetX(), y, truc->Joueur->GetY());
                    toY = 0;
                    cx++;
                }
                else if ((id == 1 && Time > BEFORE+TIMETIR/3 && toY < NBTIR*3) || (Time > BEFORE+TIMETIR && toY < NBTIR))
                {
                    truc->Tirs_Ennemi.Add(new GW_Tir_Z(id*2+1, x, y, GW_RandomEcart(a, M_PI/4)));
                    Time = BEFORE;
                    toY++;
                }
            }
            if (Time > 2*BEFORE)
            {
                ID++;
                toY = (Random(0, 100)<50)*2 - 1;
            }
            break;
        case 2:
            if (toY == 1 && angle < 3*M_PI/2)
            {
                angle += 2*dt*M_PI;
            }
            else if (toY == -1 && (angle > 3*M_PI/2 || angle < M_PI))
            {
                angle -= 2*dt*M_PI;
                if (angle < 0)
                {
                    angle += 2*M_PI;
                }
            }
            else
            {
                angle = 3*M_PI/2;
            }
            cx = GW_Cos(angle)*VITESSE;
            cy = GW_Sin(angle)*VITESSE;
            x += cx*dt;
            y += cy*dt;
            break;
        default:
            break;
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
    return ((y + height < 0) || (x + width/2.f < 0) || (x - width/2.f > GW_LARGEUR));
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
    return 20*(4*id+1);
}
#undef GW_NAMECLASS
#endif
