#ifndef GW_FLEUR_C
#define GW_FLEUR_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Fleur.hpp"
#include "../h/GW_Collisionnable.hpp"

bool GW_Fleur::exists = false;
Sprite GW_Fleur::SPRITEFLEUR[2];
Image GW_Fleur::IMAGEFLEUR[2];
cfloat GW_Fleur::MINSIZE = 0.3f, GW_Fleur::MAXSIZE = 0.5f;

GW_Fleur::GW_Fleur(void): a(Random(0.f, 360.f)), s(Random(MINSIZE, MAXSIZE))
{
    type = FLEUR;
    x = 0.f;
    y = 0.f;
    c = RandomColor();
    ID = 0;
    t = 255;
    T = 0;
}

GW_Fleur::GW_Fleur(cfloat X, cfloat Y): a(Random(0.f, 360.f)), s(Random(MINSIZE, MAXSIZE))
{
    type = FLEUR;
    y = Y;
    x = X;
    c = RandomColor();
    ID = 0;
    t = 255;
    T = 0;
}

GW_Fleur::GW_Fleur(cfloat X, cfloat Y, const Color &C): a(Random(0.f, 360.f)), s(Random(MINSIZE, MAXSIZE))
{
    c = C;
    type = FLEUR;
    y = Y;
    x = X;
    ID = 0;
    t = 255;
    T = 0;
}

GW_Fleur* GW_Fleur::Create(cfloat X, cfloat Y, const Color &C)
{
    return new GW_Fleur(X, Y, C);
}

GW_Fleur* GW_Fleur::Create(cfloat X, cfloat Y)
{
    return new GW_Fleur(X, Y);
}

GW_Fleur* GW_Fleur::Create(void)
{
    return GW_Fleur::Create(0.f, 0.f);
}

GW_Fleur::~GW_Fleur(){}

bool GW_Fleur::Draw(RenderWindow* App, cfloat dt)
{
    SPRITEFLEUR[1].SetColor(c);
    T += dt;
    float scale = s;
    switch(ID)
    {
        case 0:
            if (T > 0.15)
            {
                T = 0.15;
                ID++;
            }
            scale = T*s/0.15;
            break;
        case 1:
            if (T > 1)
            {
                ID++;
            }
            break;
        case 2:
            t -= dt*255;
            if (T > 2)
            {
                return true;
            }
            break;
        default:
            break;
    }
    SPRITEFLEUR[0].SetScale(scale, scale);
    SPRITEFLEUR[1].SetScale(scale, scale);
    SPRITEFLEUR[0].SetAlpha(t);
    SPRITEFLEUR[1].SetAlpha(t);
    GW_Collisionnable::ClassicDraw(App, &SPRITEFLEUR[1], x, y, a);
    GW_Collisionnable::ClassicDraw(App, &SPRITEFLEUR[0], x, y, a);
    return false;
}

bool GW_Fleur::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    if (IMAGEFLEUR[0].LoadFromFile("img"SEPARATOR"fleur.1.png") && IMAGEFLEUR[1].LoadFromFile("img"SEPARATOR"fleur.2.png"))
    {
        exists = true;
        /*IMAGEFLEUR[0].SetSmooth(false);
        IMAGEFLEUR[1].SetSmooth(false);*/
        SPRITEFLEUR[0].SetImage(IMAGEFLEUR[0]);
        SPRITEFLEUR[1].SetImage(IMAGEFLEUR[1]);
        GW_ToCenter(SPRITEFLEUR[0]);
        GW_ToCenter(SPRITEFLEUR[1]);
        return true;
    }
    else
    {
        return false;
    }
}

void GW_Fleur::Close(void)
{
    exists = false;
}
#endif
