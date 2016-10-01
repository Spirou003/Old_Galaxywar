#ifndef GW_ENNEMI_H_C
#define GW_ENNEMI_H_C

#include "../h/GW_Ennemi_H.hpp"
#include "../h/GW_Tir_X.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"
#include "../h/GW_TSL.hpp"

#define GW_NAMECLASS GW_Ennemi_H

bool GW_NAMECLASS::exists = false;

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EH;
    a_aile = 0;
    PV = PV_BASE;
    isOpen = CC;
    vOpen = 1;
    angle = M_PI/2;
    vx = 0;
    vy = MOVITESSE;
    ax = 0;
    ay = 0;
    dmax = 65;
    scaleX = 1;
    scaleY = 1;
    if (IsBoost)
    {
        PV *= 5;
    }
    t = 0;
    t2 = 0;
    ID = 0;
    sens = (Random(0, 100)<50)*2 - 1;
    x = GW_LARGEUR/2;
    y = -width/2;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    x += dt*vx;
    y += dt*vy;
    t2 += dt;
    this->Ailes(dt);
    switch(ID)
    {
        case 0:
            if (y > GW_HAUTEUR-100)
            {
                ID++;
            }
            break;
        case 1:
            angle += dt*sens*M_PI;
            if (angle < 0)
            {
                angle += M_PI*2;
            }
            if (vy < 0)
            {
                if (sens == 1)
                {
                    angle = M_PI;
                }
                else
                {
                    angle = 2*M_PI;
                }
                ID++;
            }
            vx = GW_Cos(angle)*MOVITESSE;
            vy = GW_Sin(angle)*MOVITESSE;
            break;
        case 2:
            if (sens == 1 && x < 50)
            {
                ID++;
            }
            else if (sens == -1 && x > GW_LARGEUR-50)
            {
                ID++;
            }
            break;
        case 3:
            angle += dt*sens*M_PI;
            if (3*M_PI/2 - dt < angle && angle < 3*M_PI/2 + dt)
            {
                angle = 3*M_PI/2;
                ID++;
            }
            vx = GW_Cos(angle)*MOVITESSE;
            vy = GW_Sin(angle)*MOVITESSE;
            break;
        case 4:
            if (y < 150)
            {
                ID++;
            }
            break;
        case 5:
            angle += dt*sens*M_PI;
            if (vy > 0)
            {
                if (sens == 1)
                {
                    angle = 0;
                }
                else
                {
                    angle = M_PI;
                }
                ax = vx;
                ay = vy;
                this->Change();
                ID++;
            }
            vx = GW_Cos(angle)*MOVITESSE;
            vy = GW_Sin(angle)*MOVITESSE;
            break;
        case 6:
            angle += dt*sens*1.2*M_PI*(1-t);
            t += dt;
            vx = (1-t) * ax;
            vy = (1-t) * ay;
            if (t > 1)
            {
                ID++;
                vx = Random(0.f, float(2*M_PI));
                ax = VITESSE*GW_Cos(vx);
                ay = VITESSE*GW_Sin(vx);
                vx = 0;
                vy = 0;
                vOpen = 4;
                nbtir = 0;
            }
            break;
        default:
            if (ID == 7)
            {
                t += dt;
                if (t > 1)
                {
                    t = 0;
                    ID = Random(9, 11);
                }
                if (t2 > 90)
                {
                    ID = 12;
                    t = 0;
                    return;
                }
            }
            else
            {
                this->Attaque(truc, dt);
            }
            this->Move(dt);
            break;
    }
}

void GW_NAMECLASS::Attaque(GW_JeuData* truc, cfloat dt)
{
    switch(ID)
    {
        case 8:
            if (isOpen == CC)
            {
                ID = 7;
                t = 0;
                nbtir = 0;
            }
            break;
        case 9:
            if (isOpen == CC)
            {
                this->Change();
            }
            else if (isOpen == OO)
            {
                this->AddTir(truc);
                this->Change();
                ID = 8;
            }
            break;
        case 10:
            if (isOpen == CC)
            {
                this->Change();
            }
            else if (isOpen == OO && nbtir != -1)
            {
                t += dt;
                if (t > 0.4)
                {
                    t -= 0.4;
                    this->AddTir(truc);
                    nbtir++;
                    if (Random(0, 100) < 5*nbtir)
                    {
                        nbtir = -1;
                        t = 0;
                    }
                }
            }
            else if (nbtir == -1 && isOpen == OO)
            {
                t += dt;
                if (t > 0.6)
                {
                    this->Change();
                    ID = 8;
                }
            }
            break;
        case 11:
            if (isOpen == CC)
            {
                this->Change();
            }
            else if (isOpen == OO && t > 1.5)
            {
                t += dt;
                while (t > 0.05 + 1.5 && nbtir < 12)
                {
                    t -= 0.05;
                    this->AddTir(truc, M_PI/10);
                    nbtir++;
                }
                if (nbtir == 12)
                {
                    ID = 8;
                    this->Change();
                }
            }
            else if (isOpen == OO)
            {
                t += dt;
            }
            break;
        case 12:
            angle += dt*sens*M_PI;
            if (angle < 0)
            {
                angle += 2*M_PI;
            }
            else if (angle > 2*M_PI)
            {
                angle -= 2*M_PI;
            }
            t += dt;
            vx = GW_Cos(angle)*MOVITESSE*t;
            vy = GW_Sin(angle)*MOVITESSE*t;
            break;
        default:
            break;
    }
}

void GW_NAMECLASS::Change(void)
{
    if (isOpen == OO || isOpen == CO)
    {
        isOpen = OC;
    }
    else
    {
        isOpen = CO;
    }
}

void GW_NAMECLASS::Ailes(cfloat dt)
{
    if (isOpen == CC || isOpen == OO)
    {
        return;
    }
    if (isOpen == CO)
    {
        a_aile += dt*vOpen*M_PI/9;
        if (a_aile > M_PI/9)
        {
            a_aile = M_PI/9;
            isOpen = OO;
        }
    }
    else
    {
        a_aile -= dt*vOpen*M_PI/9;
        if (a_aile < 0)
        {
            a_aile = 0;
            isOpen = CC;
        }
    }
}

void GW_NAMECLASS::Move(cfloat dt)
{
    if (ID == 12)
    {
        return;
    }
    angle += Random(0.f, dt/2)*sens;
    if (angle > 2*M_PI/3)
    {
        angle = 2*M_PI/3;
        sens = -sens;
    }
    else if (angle < M_PI/3)
    {
        angle = M_PI/3;
        sens = -sens;
    }
    if (Random(1, 55) == 1)
    {
        sens = -sens;
    }
    vx += ax*dt;
    vy += ay*dt;
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
    float a = 0;
    int var = 0;
    if (x < 50)
    {
        a = Random(0.f, float(M_PI/2)) - M_PI/4;
        if (a < 0)
        {
            a += M_PI*2;
        }
        ax = VITESSE*GW_Cos(a);
        ay = VITESSE*GW_Sin(a);
        var = 1;
    }
    else if (x > GW_LARGEUR-50)
    {
        a = Random(0.f, float(M_PI/2)) + 3*M_PI/4;
        ax = VITESSE*GW_Cos(a);
        ay = VITESSE*GW_Sin(a);
        var = -1;
    }
    if (y < 50)
    {
        if (var == 0)
        {
            a = Random(0.f, float(M_PI/2)) + M_PI/4;
            ax = VITESSE*GW_Cos(a);
            ay = VITESSE*GW_Sin(a);
        }
        else
        {
            ax = VITESSE*var;
            ay = VITESSE;
        }
    }
    else if (y > GW_HAUTEUR/2 - 50)
    {
        if (a == 0)
        {
            a = Random(0.f, float(M_PI/2)) + 5*M_PI/4;
            ax = VITESSE*GW_Cos(a);
            ay = VITESSE*GW_Sin(a);
        }
        else
        {
            ax = VITESSE*var;
            ay = -VITESSE;
        }
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
    return ((y + dmax*2 < 0) || (y - dmax*2 > GW_HAUTEUR) || (x + dmax*2 < 0) || (x - dmax*2 > GW_HAUTEUR));
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    if (isOpen != CC)
    {
        PV-= tir->Power();
    }
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
    return 6100*(4*id+1);
}
#undef GW_NAMECLASS
#endif
