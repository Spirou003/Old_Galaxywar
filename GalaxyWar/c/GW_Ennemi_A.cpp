#ifndef GW_ENNEMI_A_C
#define GW_ENNEMI_A_C

#include "../h/GW_Ennemi_A.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"

#define GW_NAMECLASS GW_Ennemi_A

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    PV = PV_BASE;
    t = 0;
    t2 = 0;
    sens = Random(0, 1)*2 - 1;
    dmax = 25;
    scaleX = 1;
    scaleY = 1;
    angle = 0;
    type = EA;
    if (rand()&1)
    {
        x = Random(width/2.f, GW_LARGEUR-(width/2.f));
        y = -height/2.f;
        vx = 0;
        vy = VITESSE;
        angle = M_PI/2;
    }
    else
    {
        Time = 2*(Random(0, 100)<50)-1;
        angle = (1+Time)*M_PI/2;
        x = (1+Time)*GW_LARGEUR/2.f + Time*width/2.f;
        y = Random(height/2, GW_HAUTEUR/3.f);
        vx = -Time*VITESSE;
        vy = 0;
    }
    Time = Random(dtmin, dtmax);
    if (IsBoost)
    {
        Time /= 2;
        PV *= 5;
    }
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time -= dt;
    t += dt;
    t2 += dt;
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
    if (t2 > 30)
    {
        return;
    }
    cbool h = (x < width);
    cbool b = (x > GW_LARGEUR-width);
    cbool g = (y < height);
    cbool r = (y > GW_HAUTEUR/2-height);
    if ((h && (angle < 19*M_PI/12 && angle > 5*M_PI/12)) || (b && (angle > 17*M_PI/12 || angle < 7*M_PI/12)) || (g && (angle < M_PI/12 || angle > 11*M_PI/12)) || (r && (angle > 23*M_PI/12 || angle < 13*M_PI/12)))
    {
        angle += dt*M_PI*sens;
    }
    else
    {
        if (t > 0.1)
        {
            t -= 0.1;
            if (!(h || b || r || g) && Random(0, 20) < 1)
            {
                sens = -sens;
            }
        }
        angle += Random(0.f, float(M_PI*sens))*dt;
    }
    if (Time < 0)
    {
        float cx = truc->Joueur->GetX();
        float cy = truc->Joueur->GetY();
        truc->Tirs_Ennemi.Add(new GW_Tir_Z(id+1, x, y, GW_RandomEcart(GW_Angle(x, cx, y, cy), (float)(M_PI/4)), false));
        Time += Random(dtmin, dtmax);
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
    return ((x + width*2.f < 0.f)
         || (x > GW_LARGEUR + width*2.f)
         || (y + height*2.f < 0.f)
         || (y > GW_HAUTEUR + height*2.f));
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
    return 5*(3*id+1);
}
#undef GW_NAMECLASS
#endif
