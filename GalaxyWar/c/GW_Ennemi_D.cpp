#ifndef GW_ENNEMI_D_C
#define GW_ENNEMI_D_C

#include "../h/GW_Ennemi_D.hpp"
#include "../h/GW_Tir.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"

#define GW_NAMECLASS GW_Ennemi_D

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = ED;
    PV = PV_BASE;
    dmax = 20;
    angle = 0;
    a = 0;
    if (rand()&1)
    {
        x = Random(0, GW_LARGEUR);
        y = -height;
        vx = 0;
        vy = VITESSE;
        angle = M_PI/2;
    }
    else
    {
        Time = 2*(Random(0, 100)<50)-1;
        angle = (1+Time)*M_PI/2;
        x = (1+Time)*GW_LARGEUR/2.f + Time*height;
        y = Random(0, GW_HAUTEUR/3);
        vx = -Time*VITESSE;
        vy = 0;
    }
    Time = 0;
    scaleX = 12;
    scaleY = 15;
    if (IsBoost)
    {
        PV *= 3;
    }
    sens = 1;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    a += dt*55*sens;
    if (a > 25)
    {
        sens = -1;
        a = 25;
    }
    else if (a < 0)
    {
        sens = 1;
        a = 0;
    }
    float timeboost = (1+0.01*Time);
    {
        float dx = x-truc->Joueur->GetX(), dy = y-truc->Joueur->GetY(), dv = dt*VITESSE*timeboost;
        if (dx*dx+dy*dy<dv*dv)
        {
            x=truc->Joueur->GetX();
            y=truc->Joueur->GetY();
            return;
        }
    }
    vx = cos(angle)*VITESSE*timeboost;
    vy = sin(angle)*VITESSE*timeboost;
    x += dt*vx;
    y += dt*vy;
    Time += dt;
    acible = GW_Angle(x, truc->Joueur->GetX(), y, truc->Joueur->GetY());
    if (acible < 0)
    {
        acible += 2*M_PI;
    }
    float bif = angle - acible;
    if (bif < 0)
    {
        bif = -bif;
    }
    if (id)
    {
        angle = acible;
    }
    else if (bif > dt*M_PI*(1+0.02*Time)/4)
    {
        float cacible = acible - angle;
        if (cacible < 0)
        {
            cacible += 2*M_PI;
        }
        if (cacible < M_PI)
        {
            angle += dt*M_PI*(1+0.02*Time)/4;
            if (angle > 2*M_PI)
            {
                angle -= 2*M_PI;
            }
        }
        else
        {
            angle -= dt*M_PI*(1+0.02*Time)/4;
            if (angle < 0)
            {
                angle += 2*M_PI;
            }
        }
    }
    else
    {
        angle = acible;
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
    return false;
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
    return 30*(4*id+1);
}
#undef GW_NAMECLASS
#endif
