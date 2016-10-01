#ifndef GW_ENNEMI_M_C
#define GW_ENNEMI_M_C

#include "../h/GW_Ennemi_M.hpp"
#include "../h/GW_Tir_W.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Joueur.hpp"
#include "../h/GW_TSL.hpp"
#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_BoomAnim.hpp"
#include "../h/GW_VolatileAdmin.hpp"

#define GW_NAMECLASS GW_Ennemi_M

bool GW_NAMECLASS::exists = false;
float GW_Ennemi_M::size = 1;
Sprite GW_Ennemi_M::SPRITEM[2];
Sprite GW_Ennemi_M::ECLAT[2];

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EM;
    ismove = 0;
    PV = PV_BASE;
    dmax = size/2;
    scaleX = dmax;
    scaleY = dmax;
    if (rand()&1)
    {
        x = Random(size/4.f, GW_LARGEUR-(size/4.f));
        angle = GW_RandomEcart(M_PI/2, M_PI/4);
        y = -size;
    }
    else
    {
        t = 2*(rand()&1)-1;
        x = (1+t)*GW_LARGEUR/2.f + t*size/2;
        y = Random(size/4, GW_HAUTEUR/3.f);
        angle = GW_FloatModulo(GW_RandomEcart((t+1)*M_PI/2, M_PI/4), 2*M_PI);
    }
    ax = 0;
    ay = 0;
    t = Random(float(DTMIN), DTMAX/float(id+1));
    vx = GW_Cos(angle)*VITESSE;
    vy = GW_Sin(angle)*VITESSE;
    angle = 0;
    if (IsBoost)
    {
        PV *= 5;
    }
    laser[0] = NULL;
    laser[1] = NULL;
}

bool GW_Ennemi_M::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* ptr[4];
    if (GW_MassLoadImages(ptr, 4, 0, 15, "img"SEPARATOR"13.", ".png"))
    {
        GW_SetNoSmooth(ptr[0], &SPRITEM[0]);
        GW_SetNoSmooth(ptr[1], &SPRITEM[1]);
        ECLAT[0].SetImage(*ptr[2]);
        ECLAT[1].SetImage(*ptr[3]);
        GW_ToCenter(SPRITEM[0]);
        GW_ToCenter(SPRITEM[1]);
        GW_ToCenter(ECLAT[0]);
        GW_ToCenter(ECLAT[1]);
        size = (ptr[0]->GetWidth()-8);
        exists = true;
        return true;
    }
    return false;
}

void GW_Ennemi_M::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITEM[int(id)], this);
    int i = 0;
    float a;
    cfloat b = 2 + size/2;
    if (ismove == 3)
    {
        if (t > 0.5 || int(t/0.05)&1)
        {
            a = angle;
            while (i < 4)
            {
                a += M_PI/2;
                if (a > 2*M_PI)
                {
                    a -= 2*M_PI;
                }
                ECLAT[int(id)].SetPosition(x+b*GW_Cos(a), y+b*GW_Sin(a));
                App->Draw(ECLAT[int(id)]);
                i++;
            }
        }
    }
    else if (ismove == 4)
    {
        a = angle;
        while (i < 4)
        {
            a += M_PI/2;
            if (a > 2*M_PI)
            {
                a -= 2*M_PI;
            }
            ECLAT[int(id)].SetPosition(x+b*GW_Cos(a), y+b*GW_Sin(a));
            App->Draw(ECLAT[int(id)]);
            i++;
        }
    }
}

void GW_Ennemi_M::Close(void)
{
    if (!exists)
    {
        return;
    }
    else
    {
        exists = false;
        delete(SPRITEM[0].GetImage());
        delete(SPRITEM[0].GetImage());
        delete(ECLAT[0].GetImage());
        delete(ECLAT[1].GetImage());
    }
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    cfloat Dt = dt*(1-t);
    switch (ismove)
    {
        case 0:
            this->Deplacer(dt);
            angle += dt;
            if (angle > 2*M_PI)
            {
                angle -= 2*M_PI;
            }
            t -= dt;
            if (t < 0)
            {
                t = 0;
                ismove++;
            }
            break;
        case 1:
            this->Deplacer(Dt);
            angle += Dt;
            if (angle > 2*M_PI)
            {
                angle -= 2*M_PI;
            }
            t += dt;
            if (t > 1)
            {
                ismove++;
                t = 0;
            }
            break;
        case 2:
            t += dt;
            y += dt*15;
            if (t > 1/3.)
            {
                t = 0;
                ismove++;
            }
            break;
        case 3:
            t += dt;
            if (t > 1)
            {
                ismove = 4;
                t = 0;
                if (!this->Laser(truc))
                {
                    ismove++;
                }
            }
            break;
        case 4:
            t += dt;
            if (t > 1.5)
            {
                ismove++;
                t = 0;
                laser[0]->Stop();
                laser[1]->Stop();
            }
            break;
        case 5:
            t += dt;
            if (t > 0.2)
            {
                t = 0;
                ismove++;
            }
            break;
        case 6:
            t += dt;
            y -= dt*15;
            if (t > 1/3.)
            {
                vx = 0;
                vy = 0;
                t = 0;
                ismove++;
            }
            break;
        case 7:
            angle += dt*t;
            if (angle > 2*M_PI)
            {
                angle -= 2*M_PI;
            }
            this->Deplacer(dt*t);
            t += dt;
            if (t > 1)
            {
                ismove = 0;
                t = Random(float(DTMIN), DTMAX/float(1+id));
            }
    }
}

bool GW_NAMECLASS::Laser(GW_JeuData* truc)
{
    float truk;
    laser[0] = new GW_Tir_W(id, x, y, angle);
    if (laser[0] != NULL)
    {
        if (angle < M_PI)
        {
            truk = angle + M_PI/2;
        }
        else
        {
            truk = angle - M_PI/2;
        }
        laser[1] = new GW_Tir_W(id, x, y, truk);
        if (laser[1] != NULL)
        {
            if (truc->Tirs_Ennemi.Add(laser[0]))
            {
                if (truc->Tirs_Ennemi.Add(laser[1]))
                {
                    return true;
                }
                else
                {
                    delete(truc->Tirs_Ennemi.Delete(truc->Tirs_Ennemi.Size()-1));
                    delete(laser[1]);
                }
            }
            else
            {
                delete(laser[0]);
                delete(laser[1]);
            }
        }
        else
        {
            delete(laser[0]);
        }
    }
    return false;
}

const Shape* GW_Ennemi_M::GetPolygon(void) const
{
    return &Octogon;
}

bool GW_Ennemi_M::Dead(GW_JeuData* truc, RenderWindow* App)
{
    if (ismove == 4)
    {
        laser[0]->Stop();
        laser[1]->Stop();
    }
    GW_CollisionnableAdmin::GW_Ennemi_GenericDead(this, truc, App);
    return true;
}

void GW_NAMECLASS::Deplacer(cfloat dt)
{
    x += dt*(vx + ax*dt/2);
    y += dt*(vy + ay*dt/2);
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
    if (x < 50+size/2 && ax < 2.5)
    {
        ax = Random(4.5, 6);
    }
    else if (x > GW_LARGEUR-50-size/2 && ax > -2.5)
    {
        ax = -Random(4.5, 6);
    }
    if (y < 50+size/2 && ay < 2.5)
    {
        ay = Random(4.5, 6);
    }
    else if (y > GW_HAUTEUR/3 && ay > -2.5)
    {
        ay = -Random(4.5, 6);
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void){;}

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
    return 1000*(4*id+1);
}

#undef GW_NAMECLASS
#endif
