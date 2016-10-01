#ifndef GW_TIR_W_C
#define GW_TIR_W_C

#include "../h/GW_Tir_W.hpp"
#include "../h/GW_GraphicsIncluser.hpp"

#define GW_NAMECLASS GW_Tir_W

bool GW_NAMECLASS::exists = false;
Sprite GW_Tir_W::SPRITIR[2];

bool GW_NAMECLASS::IsDead(void) const
{
    return stop;
}

bool GW_Tir_W::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* ptr[2];
    ptr[0] = new Image(1, 5, Color(105, 105, 229));
    if (ptr[0] == NULL)
    {
        return false;
    }
    ptr[1] = new Image(1, 5, Color(229, 105, 105));
    if (ptr[1] == NULL)
    {
        delete(ptr[0]);
        return false;
    }
    ptr[0]->SetPixel(0, 1, Color(156, 156, 216));
    ptr[0]->SetPixel(0, 3, Color(156, 156, 216));
    ptr[0]->SetPixel(0, 2, Color(180, 180, 210));
    ptr[1]->SetPixel(0, 1, Color(216, 156, 156));
    ptr[1]->SetPixel(0, 3, Color(216, 156, 156));
    ptr[1]->SetPixel(0, 2, Color(210, 180, 180));
    GW_SetNoSmooth(ptr[1], &SPRITIR[0]);
    GW_SetNoSmooth(ptr[0], &SPRITIR[1]);
    GW_ToCenter(SPRITIR[0]);
    GW_ToCenter(SPRITIR[1]);
    SPRITIR[0].SetScale((GW_HAUTEUR+GW_LARGEUR)*10, 1);
    SPRITIR[1].SetScale((GW_HAUTEUR+GW_LARGEUR)*10, 1);
    exists = true;
    return true;
}

void GW_Tir_W::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(SPRITIR[0].GetImage());
    delete(SPRITIR[1].GetImage());
    exists = false;
}

void GW_Tir_W::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITIR[int(Level)], this);
}

bool GW_Tir_W::Dead(GW_JeuData* truc, RenderWindow* App)
{
    return true;
}

const Shape* GW_Tir_W::GetPolygon(void) const
{
    return &Carre;
}

void GW_NAMECLASS::Stop(void)
{
    stop = true;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    p = dt;
}

float GW_NAMECLASS::GetRadius(void) const
{
    return 5;
}

GW_NAMECLASS::GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle)
{
    Level = level;
    scaleX = (GW_HAUTEUR+GW_LARGEUR);
    scaleY = 2;
    stop = false;
    end = false;
    type = TW;
    angle = Angle;
    x = X;
    y = Y;
    vx = cos(angle);
    vy = sin(angle);
    if (vx < M_SQRT1_2 && vx > -M_SQRT1_2)
    {
        x += vx*(GW_HAUTEUR/2 - y)/vy;//(x(A) + (h / 2 - y(A)) vx / vy, h / 2)
        y = GW_HAUTEUR/2;
        scaleX = GW_HAUTEUR*vy;
    }
    else
    {
        y += vy*(GW_LARGEUR/2 - x)/vx;//(x(A) + (h / 2 - y(A)) vx / vy, h / 2)
        x = GW_LARGEUR/2;
        scaleX = GW_LARGEUR*vx;
    }
    if (scaleX < 0)
    {
        scaleX *= -1;
    }
    dmax = scaleX;
    //printf("%d %d == %d %d == %d %d == %d\n", int(x), int(y), int(vx), int(vy), int(scaleX), int(scaleY), int(dmax));
}

float GW_NAMECLASS::Power(CSInt32 malus) const
{
    return p*(1+2*Level)*20;
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    ;
}

#undef GW_NAMECLASS
#endif
