#ifndef GW_BOOMANIM_C
#define GW_BOOMANIM_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_ExploTir.hpp"
#include "../h/GW_Collisionnable.hpp"

bool GW_ExploTir::exists = false;
Sprite GW_ExploTir::EXPLOSHAPE[7];
float GW_ExploTir::size = 1;

GW_ExploTir::GW_ExploTir(cfloat X, cfloat Y, cfloat S, cfloat A): s(S*10/size), a(A)
{
    type = EXPLOTIR;
    y = Y;
    x = X;
    t = 0;//printf("%.3f %.3f\n", s, a);
}

GW_ExploTir* GW_ExploTir::Create(cfloat X, cfloat Y, cfloat S, cfloat A)
{
    return new GW_ExploTir(X, Y, S, A);
}

GW_ExploTir::~GW_ExploTir(){}

bool GW_ExploTir::Draw(RenderWindow* App, cfloat dt)
{
    t += dt;
    if (t > 0.21)
    {
        return true;
    }
    CSInt32 id = t/0.03;
    EXPLOSHAPE[id].SetScale(s, s);
    /*EXPLOSHAPE[id].SetPosition(x, y);
    EXPLOSHAPE[id].SetRotation(-a*180/M_PI);
    App->Draw(EXPLOSHAPE[id]);*/
    GW_Collisionnable::ClassicDraw(App, &EXPLOSHAPE[id], x, y, -a*180/M_PI);
    return false;
}

bool GW_ExploTir::Init(cbool previnit)
{
    if (!previnit)
    {
        return false;
    }
    Image* ptr[7];
    if (GW_MassLoadImages(ptr, 7, 0, 15, "img"SEPARATOR"e.", ".png"))
    {
        int i = 0;
        while (i < 7)
        {
            GW_SetNoSmooth(ptr[i], &EXPLOSHAPE[i]);
            GW_ToCenter(EXPLOSHAPE[i]);
            EXPLOSHAPE[i].SetAlpha(120);
            i++;
        }
        size = EXPLOSHAPE[0].GetSize().x;
        exists = true;
        return true;
    }
    else
    {
        return false;
    }
}

void GW_ExploTir::Close(void)
{
    if (exists)
    {
        return;
    }
    exists = false;
    int i = 0;
    while (i < 7)
    {
        delete(EXPLOSHAPE[i].GetImage());
        i++;
    }
}
#endif
