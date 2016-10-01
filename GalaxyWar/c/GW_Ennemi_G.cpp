#ifndef GW_ENNEMI_G_C
#define GW_ENNEMI_G_C

#include "../h/GW_Ennemi_G.hpp"
#include "../h/GW_Tir.hpp"

#define GW_NAMECLASS GW_Ennemi_G

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EG;
    if (rand()&1)
    {
        x = Random(size/2.f, GW_LARGEUR-(size/2.f));
        y = -size/2.f;
        da = GW_RandomEcart(M_PI/2, M_PI/3);
    }
    else
    {
        da = 2*(Random(0, 100)<50)-1;
        x = (1+da)*GW_LARGEUR/2.f + da*size/2.f;
        y = Random(size/2, GW_HAUTEUR/3.f);
        da = GW_FloatModulo(GW_RandomEcart((1+da)*M_PI/2, M_PI/3), 2*M_PI);
    }
    va = Random(float(M_PI*2), -float(M_PI*2));
    PV = PV_BASE;
    VITESSE = Random(60, 80);
    vx = GW_Cos(da)*VITESSE;
    vy = GW_Sin(da)*VITESSE;
    angle = 0;
    t = 0;
    dmax = size/2;
    scaleX = dmax;
    scaleY = dmax;
    if (IsBoost)
    {
        PV *= 5;
    }
}

bool GW_NAMECLASS::IsOut(void) const
{
    return ((y + dmax < 0) || (y - dmax > GW_HAUTEUR) || (x + dmax < 0) || (x - dmax > GW_HAUTEUR));
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += dt*vx;
    y += dt*vy;
    t += dt;
    angle += dt*va;
    if (angle < 0)
    {
        angle += 2*M_PI;
    }
    else if (angle > 2*M_PI)
    {
        angle -= M_PI*2;
    }
    if (t > 20)
    {
        return;
    }
    float cda = da;
    if (((!(da < M_PI/2 || da > 3*M_PI/2)) && x < dmax) || ((!(da > M_PI/2 && da < 3*M_PI/2)) && x > GW_LARGEUR-dmax))
    {
        cfloat Truc = GW_FloatModulo(M_PI-da + va*0.05, 2*M_PI);
        if (((Truc < M_PI/2 || Truc > 3*M_PI/2) && x < dmax) || (Truc > M_PI/2 && Truc < 3*M_PI/2 && x > GW_LARGEUR-dmax))
        {
            da = Truc;
        }
        else
        {
            da = GW_FloatModulo(M_PI-da, 2*M_PI);
        }
    }
    if ((y < dmax && da > M_PI) || (da < M_PI && y > GW_HAUTEUR-dmax))
    {
        cfloat Truc = GW_FloatModulo(-da + va*0.05, 2*M_PI);
        if ((y < dmax && Truc < M_PI) || (Truc > M_PI && y > GW_HAUTEUR-dmax))
        {
            da = Truc;
        }
        else
        {
            da = GW_FloatModulo(-da, 2*M_PI);
        }
    }
    if (cda != da)
    {
        vx = GW_Cos(da)*VITESSE;
        vy = GW_Sin(da)*VITESSE;
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

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    if (tir->IsDead())
    {
        return 0;
    }
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
    return 50*(5*id+1);
}
#undef GW_NAMECLASS
#endif
