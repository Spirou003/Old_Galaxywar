#ifndef GW_ENNEMI_F_C
#define GW_ENNEMI_F_C

#include "../h/GW_Ennemi_F.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"

#define GW_NAMECLASS GW_Ennemi_F

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(CSInt8 Id, cfloat X, cfloat Y) : id(Id!=0)
{
    angle=0;vx=0;vy=0;ax=0;ay=0;av=0;nb=0;ID=0;scaleX = 1;scaleY = 1;dmax = 40;
    GW_Ennemi::AddResistances(this, 0);
    type = EF;
    t2 = 0;
    PV = PVBASE;
    if (rand()&1)
    {
        x = Random(width/2.f, GW_LARGEUR-(width/2.f));
        y = -30;
    }
    else
    {
        Time = 2*Random(0, 1)-1;
        x = (1+Time)*GW_LARGEUR/2.f + Time*30;
        y = Random(height/2, GW_HAUTEUR/3.f);
    }
    if (Id != 0)
    {
        PV *= 5;
    }
    ax = Random(-300, 300);
    ay = Random(-250, 250);
    Time=0;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time += dt;
    t2 += dt;
    av += dt;
    if (av > 4)
    {
        av -= 4;
    }
    this->Deplacer(dt);
    if (Time > TIMETIRE)
    {
        Time -= TIMETIRE;
        nb = 1-nb;
        float cx;
        if (nb)
        {
            cx = x-11.5;
        }
        else
        {
            cx = x+9.5;
        }
        truc->Tirs_Ennemi.Add(new GW_Tir_Z(4+id, cx, y+9, GW_RandomEcart(GW_Angle(cx, truc->Joueur->GetX(), y+9, truc->Joueur->GetY()), M_PI/8)));
    }
}

void GW_NAMECLASS::Deplacer(cfloat dt)
{
    if (Random(0, 10)<1)
    {
        ax = Random(-200, 200);
        ay = Random(-200, 200);
    }
    x += dt*(vx + ax*dt/2);
    vx += ax*dt;
    y += dt*(vy + ay*dt/2);
    vy += ay*dt;
    if (vx > 180)
    {
        vx = 180;
    }
    else if (vx < -180)
    {
        vx = -180;
    }
    if (vy > 120)
    {
        vy = 120;
    }
    else if (vy < -120)
    {
        vy = -120;
    }
    if (t2 > 60)
    {
        return;
    }
    if (x < GW_LARGEUR/2 && ax < 110)
    {
        ax = Random(220, 260);
    }
    else if (x > GW_LARGEUR/2 && ax > -110)
    {
        ax = -Random(220, 260);
    }
    if (y < GW_HAUTEUR/4 && ay < 90)
    {
        ay = Random(180, 220);
    }
    else if (y > GW_HAUTEUR/3 && ay > -90)
    {
        ay = -Random(180, 220);
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
    return 3000*(4*id+1);
}
#undef GW_NAMECLASS
#endif
