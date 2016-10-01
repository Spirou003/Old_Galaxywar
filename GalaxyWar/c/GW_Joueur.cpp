#ifndef GW_ENNEMI_JOUEUR_C
#define GW_ENNEMI_JOUEUR_C

#include "../h/GW_Joueur.hpp"
#include "../h/GW_Tir_A.hpp"
#include "../h/GW_Tir_B.hpp"
#include "../h/GW_Tir_C.hpp"
#include "../h/GW_Tir_Z.hpp"
#include "../h/GW_BoomAnim.hpp"
#include "../h/GW_VolatileAdmin.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_KeySettings.hpp"

#define GW_NAMECLASS GW_Joueur

bool GW_NAMECLASS::exists = false;
cfloat GW_NAMECLASS::HFEU = 30;
char GW_NAMECLASS::nbj = 0;
float GW_NAMECLASS::GW_Joueur_INITJPOS;
bool GW_NAMECLASS::invincible;

extern int levels[4];

GW_NAMECLASS::GW_NAMECLASS(cfloat X, const GW_KeySettings &keyset)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EJO;
    IDReacteur = 0;
    x = X;
    vx = 0;
    vy = 0;
    nbj++;
    angle = 0;
    scaleX = 1;
    scaleY = 1;
    dmax = 20;
    Settings = new GW_KeySettings(keyset);
    y = GW_HAUTEUR + height;
    PV = GW_NAMECLASS::PV_BASE;
    int i = 0;
    while (i < 5)
    {
        Key[i] = false;
        i++;
    }
    i = 0;
    while (i < GW_NBARME)
    {
        Arme[i] = 0;
        t[i][0] = 0.f;
        t[i][1] = 0.f;
        t[i][2] = 0.f;
        i++;
    }
    Arme[TA] = levels[0];
    Arme[TB] = levels[1];
    Arme[TC] = levels[2];
    Arme[TZ] = levels[3];
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    /**/
    if (Type(tir) == TW)
    {
        cfloat X = tir->GetX(), Y = tir->GetY(), X2 = tir->GetVX()+X, Y2 = tir->GetVY()+Y, dx = X2-X, dy = Y2-Y, d = dy*x-dx*y+Y*X2-X*Y2;
        if (dmax*dmax*(dx*dx+dy*dy)*0.7<d*d)
        {
            return 0;
        }
    }
    /**/
    PV -= tir->Power();
    //*/cos((x - PI / 6) 1.5)² / 2 + 0.5
    if (invincible)
    {
        while (PV <= 0)
        {
            PV += PV_BASE;
        }// */
    }
    tir->End();
    return 0;
}

bool GW_NAMECLASS::Fire(GW_JeuData* truc)
{
    GW_Tir_A::Tirs_Generate(Arme[TA], x, y, t[TA], &(truc->Tirs_Joueur));
    GW_Tir_B::Tirs_Generate(Arme[TB], x, y, t[TB], &(truc->Tirs_Joueur));
    GW_Tir_C::Tirs_Generate(Arme[TC], x, y, t[TC], &(truc->Tirs_Joueur));
    GW_Tir_Z::Tirs_Generate(Arme[TZ], x, y, t[TZ], &(truc->Tirs_Joueur));
    return true;
}

void GW_NAMECLASS::SetPosition(cfloat X, cfloat Y)
{
    x=X;y=Y;
}

void GW_NAMECLASS::SetKeyUp(cbool v)
{
    if (v)
    {
        Key[GW_KeySettings::Up] = true;
    }
    else
    {
        Key[GW_KeySettings::Up] = false;
    }
    this->Actualise();
}

bool GW_NAMECLASS::SetKeySettings(GW_KeySettings* keyset)
{
    return Settings->SetKey(keyset->GetKey());
}

GW_NAMECLASS* GW_NAMECLASS::Create(cfloat X)
{
    return new GW_NAMECLASS(X, GW_KeySettings());
}

int GW_NAMECLASS::NBJoueur(void)
{
    return nbj;
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    nbj--;
    delete(Settings);
}

bool GW_NAMECLASS::IsDead(void) const
{
    return PV <= 0;
}

bool GW_NAMECLASS::IsOut(void) const
{
    return false;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    if (this->IsDead())
    {
        return;
    }
    int i = 0;
    while (i < GW_NBARME)
    {
        t[i][2] += dt;
        if (t[i][2] > 99999999)
        {
            t[i][2] = 99999999;
        }
        i++;
    }
    i = 0;
    x += vx*dt;
    y += vy*dt;
    if (y < height/3)
    {
        y = height/3;
    }
    else if (y+20 > GW_HAUTEUR-height/3 && lim)
    {
        y = GW_HAUTEUR-height/3-20;
    }
    if (x < width/3)
    {
        x = width/3;
    }
    else if (x > GW_LARGEUR-width/3)
    {
        x = GW_LARGEUR-width/3;
    }
    if (Key[GW_KeySettings::Fire])
    {
        while (i < GW_NBARME)
        {
            t[i][0] += dt;
            if (t[i][0] > 99999999)
            {
                t[i][0] = 99999999;
            }
            i++;
        }
        this->Fire(truc);
    }
    if (!Key[GW_KeySettings::Fire])
    {
        while (i < GW_NBARME)
        {
            t[i][1] += dt;
            if (t[i][1] > 99999999)
            {
                t[i][1] = 99999999;
            }
            i++;
        }
    }
}

void GW_NAMECLASS::Actualise(void)
{
    vx = 0;
    vy = 0;
    if (Key[GW_KeySettings::Up])
    {
        vy -= VITESSE;
    }
    if (Key[GW_KeySettings::Down])
    {
        vy += VITESSE;
    }
    if (Key[GW_KeySettings::Left])
    {
        vx -= VITESSE;
    }
    if (Key[GW_KeySettings::Right])
    {
        vx += VITESSE;
    }
}

int GW_NAMECLASS::Points(void) const
{
    return 0;
}

#undef GW_NAMECLASS
#endif
