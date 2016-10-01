#ifndef GW_ENNEMI_E_C
#define GW_ENNEMI_E_C

#include "../h/GW_Ennemi_E.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"

#define GW_NAMECLASS GW_Ennemi_E

bool GW_NAMECLASS::exists = false;

CSInt32 GW_NAMECLASS::PV_BASE[3] = {10, 4, 7};
CSInt32 GW_NAMECLASS::POINTS[3] = {100, 55, 65};
CSInt32 GW_NAMECLASS::NBTIR[3] = {3, 2, 5};
CSInt32 GW_NAMECLASS::NBDEP[3] = {20, 40, 12};
CSInt8 GW_NAMECLASS::LEVELTIR[3] = {2, 1, 2};
cfloat GW_NAMECLASS::TIMETIR[3] = {0.3f, 0.1f, 0.2f};
cfloat GW_NAMECLASS::TIMEDEP[3] = {0.6f, 0.3f, 1.0f};

GW_NAMECLASS::GW_NAMECLASS(void) : id(0)
{
    Time=0;angle=0;PV=0;vx=0;vy=0;ax=0;ay=0;toX=0;toY=0;av=0;nb=0;ID=0;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt8 Id, cfloat X, cfloat Y) : id(Id)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EE;
    int kid = Id%3;
    scaleX = size[kid]/2;
    scaleY = scaleX;
    dmax = scaleX;
    PV = PV_BASE[kid];
    angle = 0;
    if (rand()&1)
    {
        x = Random(size[kid]/2.f, GW_LARGEUR-(size[kid]/2.f));
        y = -size[kid]/2.f;
    }
    else
    {
        Time = 2*Random(0, 1)-1;
        x = (1+Time)*GW_LARGEUR/2.f + Time*size[kid]/2.f;
        y = Random(size[kid]/2, GW_HAUTEUR/3.f);
    }
    if (X != 0 || Y != 0)
    {
        x = X;
        y = Y;
    }
    if (Id >= 3)
    {
        PV *= 5;
    }
    ID = 0;
    this->RandomDir();
    Time = 0;
    nb = 0;
}

void GW_NAMECLASS::RandomDir(void)
{
    int kid = id%3;
    toX = Random(size[kid], GW_LARGEUR - size[kid]/2.f);
    toY = Random(size[kid], GW_HAUTEUR/2 - size[kid]/2.f);
    if (ID > NBDEP[(int)(id%3)])
    {
        toY = -size[kid]*2;
    }
    float t = TIMEDEP[id%3];
    vx = 2*(toX-x)/t;
    vy = 2*(toY-y)/t;
    ax = -vx/t;
    ay = -vy/t;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time += dt;
    angle += dt*270;
    if (angle > 360)
    {
        angle -= 360;
    }
    int mach = id%3;
    switch(ID%4)
    {
        case 0:
            x += dt*(vx + ax*dt/2);
            vx += ax*dt;
            y += dt*(vy + ay*dt/2);
            vy += ay*dt;
            if (Time > TIMEDEP[id%3])
            {
                x = toX;
                y = toY;
                ID++;
                Time = 0;
            }
            break;
        case 1:
            if (Time > TIMEDEP[id%3])
            {
                Time = 0;
                ID++;
                av = GW_Angle(x, truc->Joueur->GetX(), y, truc->Joueur->GetY());
            }
            break;
        case 2:
            if ((id >= 3 && Time > TIMETIR[mach]/2) || (Time > TIMETIR[mach]))
            {
                truc->Tirs_Ennemi.Add(new GW_Tir_Z(LEVELTIR[mach]+id/3, x, y, GW_RandomEcart(av, M_PI/4)));
                Time = 0;
                nb++;
            }
            if ((id >= 3 && nb >= NBTIR[mach]*3) || (id < 3 && nb >= NBTIR[mach]))
            {
                ID++;
                nb = 0;
            }
            break;
        case 3:
            if (Time > TIMEDEP[id%3])
            {
                Time = 0;
                ID++;
                this->RandomDir();
            }
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
    return POINTS[(int)(id%3)]*((id/3)*4+1);
}
#undef GW_NAMECLASS
#endif
