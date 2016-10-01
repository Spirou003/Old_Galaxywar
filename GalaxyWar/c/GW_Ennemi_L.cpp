#ifndef GW_ENNEMI_L_C
#define GW_ENNEMI_L_C

#include "../h/GW_Tir.hpp"
#include "../h/GW_Ennemi_L.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Fleur.hpp"
#include "../h/GW_VolatileAdmin.hpp"

#define GW_NAMECLASS GW_Ennemi_L

GW_NAMECLASS::GW_NAMECLASS()
{
    GW_Ennemi::AddResistances(this, 0);
    PV = PV_BASE;
    sens = Random(0, 1)*2 - 1;
    dmax = size/2;
    scaleX = dmax;
    scaleY = dmax;
    angle = 0;
    t = 0;
    type = EL;
    if (rand()&1)
    {
        x = Random(size/2.f, GW_LARGEUR-(size/2.f));
        y = -size/2.f;
        vx = 0;
        vy = VITESSE;
        angle = M_PI/2;
    }
    else
    {
        float Time = 2*(Random(0, 100)<50)-1;
        angle = (1+Time)*M_PI/2;
        x = (1+Time)*GW_LARGEUR/2.f + Time*size/2.f;
        y = Random(size/2, GW_HAUTEUR/3.f);
        vx = -Time*VITESSE;
        vy = 0;
    }
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    t += dt;
    x += dt*vx;
    y += dt*vy;//x=140;y=100;
    if (angle > M_PI*2)
    {
        angle -= M_PI*2;
    }
    else if (angle < 0)
    {
        angle += M_PI*2;
    }
    vx = VITESSE*GW_Cos(angle);
    vy = VITESSE*GW_Sin(angle);
    cbool h = (x < size);
    cbool b = (x > GW_LARGEUR-size);
    cbool g = (y < size);
    cbool r = (y > GW_HAUTEUR/2-size);
    if ((h && (angle < 19*M_PI/12 && angle > 5*M_PI/12)) || (b && (angle > 17*M_PI/12 || angle < 7*M_PI/12)) || (g && (angle < M_PI/12 || angle > 11*M_PI/12)) || (r && (angle > 23*M_PI/12 || angle < 13*M_PI/12)))
    {
        angle += dt*M_PI*sens;
    }
    else
    {
        if (t > 0.2)
        {
            t -= 0.2;
            truc->VolatiList->Add(GW_Fleur::Create(GW_RandomEcart(x, vx*0.5), GW_RandomEcart(y, vy*0.5)));
            if (!(h || b || r || g) && Random(0, 10) < 1)
            {
                sens = -sens;
            }
        }
        angle += Random(0.f, float(M_PI*sens))*dt;
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
    return ((x + size*2.f < 0.f)
         || (x > GW_LARGEUR + size*2.f)
         || (y + size*2.f < 0.f)
         || (y > GW_HAUTEUR + size*2.f));
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
    return 1000;
}
#undef GW_NAMECLASS
#endif
