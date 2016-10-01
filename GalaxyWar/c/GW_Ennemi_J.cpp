#ifndef GW_ENNEMI_J_C
#define GW_ENNEMI_J_C

#include "../h/GW_Ennemi_J.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"
#include "../h/GW_TSL.hpp"

#define GW_NAMECLASS GW_Ennemi_J

bool GW_NAMECLASS::exists = false;
int GW_NAMECLASS::nb = 0;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EJ;
    nx = 0;
    ny = 0;
    nx2 = 0;
    ny2 = 0;
    isDiv = false;
    celldiv = false;
    idDraw = 0;
    coeff = 1;
    pts = PTS_BASE;
    PV = PV_BASE;
    this->SetSize(SIZE_BASE*(1-Random(0.6f, 1.f)*Random(0.6f, 1.f)*Random(0.6f, 1.f)));
    if (rand()&1)
    {
        x = Random(size/4.f, GW_LARGEUR-(size/4.f));
        angle = GW_RandomEcart(M_PI/2, M_PI/4);
        y = -size;
    }
    else
    {
        Time = 2*(rand()&1)-1;
        x = (1+Time)*GW_LARGEUR/2.f + Time*size/2;
        y = Random(size/4, GW_HAUTEUR/3.f);
        angle = GW_FloatModulo(GW_RandomEcart((Time+1)*M_PI/2, M_PI/4), 2*M_PI);
    }
    ax = 0;
    ay = 0;
    Time = 2;
    vx = GW_Cos(angle)*VITESSE;
    vy = GW_Sin(angle)*VITESSE;
    nb++;
    if (IsBoost)
    {
        PV *= 5;
    }
}

void GW_NAMECLASS::SetSize(cfloat Size)
{
    if (Size < 20)
    {
        return;
    }
    size = Size;
    dmax = size/2;
    scaleX = dmax;
    scaleY = dmax;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    this->Deplacer(dt);
    angle = GW_Angle(x, x+vx, y, y+vy);
    if (angle > 2*M_PI)
    {
        angle -= 2*M_PI;
    }
    else if (angle < 0)
    {
        angle += 2*M_PI;
    }
    float vcos = GW_Cos(angle)/(VITESSE*1.5), vsin = GW_Sin(angle)/(VITESSE*1.5);
    nx = vcos*vx*coeff;
    ny = vsin*vy*coeff;
    if (vcos < 0)
    {
        nx = -vcos*vx*coeff;
    }
    if (vsin < 0)
    {
        ny = -vsin*vy*coeff;
    }
    nx2 = nx;
    ny2 = ny;
    if (isDiv)
    {
        Time += dt;
        nx = vcos*(coeff+Time)*VITESSE;
        ny = vsin*(coeff+Time)*VITESSE;
        nx2 = -nx;
        ny2 = -ny;
        if (Time > 0.5)
        {
            idDraw = 0;
            isDiv = false;
            GW_NAMECLASS* ptr = new GW_NAMECLASS(id);
            if (ptr != NULL)
            {
                this->SetSize(size*0.9);
                pts /= 2;
                PV = (PV + PV_BASE)/2;
                cfloat cste = SizeNoyau*size/SIZE_BASE;
                ptr->PV = PV;
                ptr->pts = pts;
                ptr->x = x + nx2*cste;
                ptr->y = y + ny2*cste;
                ptr->vx = vx*nx2;
                ptr->vy = vy*ny2;
                if (vcos < 0)
                {
                    ptr->vx = -ptr->vx;
                    vx *= -nx;
                }
                else
                {
                    vx *= nx;
                }
                if (vsin < 0)
                {
                    ptr->vy = -ptr->vy;
                    vy *= -ny;
                }
                else
                {
                    vy *= ny;
                }
                ptr->SetSize(size);
                if (!truc->Unites.Add(ptr))
                {
                    delete(ptr);
                }
                x += nx*cste;
                y += ny*cste;
            }
        }
        else
        {
            idDraw = Time*10 + 1;
        }
    }
    else if (celldiv)
    {
        cfloat dx = nx-nx2, dy = ny-ny2, d = dx*dx + dy*dy;
        if (d < 0.00000001 && coeff > 0)
        {
            coeff -= dt;
            if (coeff < 0)
            {
                coeff = -1;
            }
        }
        else
        {
            coeff += dt;
            if (coeff > 0)
            {
                coeff = 1;
                celldiv = false;
                isDiv = true;
                Time = 0;
            }
            nx = vcos*(coeff+1)*VITESSE;
            ny = vsin*(coeff+1)*VITESSE;
            nx2 = -nx;
            ny2 = -ny;
        }
    }
    else
    {
        Time -= dt;
        if (Time < 0)
        {
            Time = 2;
            if (Random(0, 4/(id+1)) == 1 && nb < 100)
            {
                celldiv = true;
            }
        }
    }
}

void GW_NAMECLASS::Deplacer(cfloat dt)
{
    if (Random(0, 10)<1)
    {
        ax = Random(-16, 16);
        ay = Random(-16, 16);
    }
    if (celldiv)
    {
        if (coeff > 0)
        {
            x += dt*(vx + ax*dt/2)*coeff;
            y += dt*(vy + ay*dt/2)*coeff;
            vx += ax*dt*coeff;
            vy += ay*dt*coeff;
        }
    }
    else if (isDiv)
    {
        return;
    }
    else
    {
        x += dt*(vx + ax*dt/2);
        y += dt*(vy + ay*dt/2);
        vx += ax*dt;
        vy += ay*dt;
    }
    if (vx > VITESSE)
    {
        vx = VITESSE;
    }
    else if (vx < -VITESSE)
    {
        vx = -VITESSE;
    }
    if (vy > VITESSE)
    {
        vy = VITESSE;
    }
    else if (vy < -VITESSE)
    {
        vy = -VITESSE;
    }
    if (x < 50+size/2 && ax < 6)
    {
        ax = Random(12, 16);
    }
    else if (x > GW_LARGEUR-50-size/2 && ax > -6)
    {
        ax = -Random(12, 16);
    }
    if (y < 50+size/2 && ay < 6)
    {
        ay = Random(12, 16);
    }
    else if (y > GW_HAUTEUR/3 && ay > -6)
    {
        ay = -Random(12, 16);
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    nb--;
}

bool GW_NAMECLASS::IsDead(void) const
{
    return (PV <= 0.f);
}

bool GW_NAMECLASS::IsOut(void) const
{
    return ((x+size < 0) || (y+size < 0) || (y - size > GW_HAUTEUR) || (x - size > GW_LARGEUR));
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    if (idDraw >= 5)
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
    return pts*(4*id+1);
}

#undef GW_NAMECLASS
#endif
