#ifndef GW_BOOMANIM_C
#define GW_BOOMANIM_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_BoomAnim.hpp"

bool GW_BoomAnim::exists = false;
Sprite GW_BoomAnim::BOOMSPRITE;

GW_BoomAnim::GW_BoomAnim(void)
{
    type = BOOMANIM;
    x = 0.f;
    y = 0.f;
    ID = 0;
}

GW_BoomAnim::GW_BoomAnim(cfloat X, cfloat Y)
{
    type = BOOMANIM;
    y = Y;
    x = X;
    ID = 0;
}

GW_BoomAnim* GW_BoomAnim::Create(cfloat X, cfloat Y)
{
    return new GW_BoomAnim(X, Y);
}

GW_BoomAnim* GW_BoomAnim::Create(void)
{
    return GW_BoomAnim::Create(0.f, 0.f);
}

GW_BoomAnim::~GW_BoomAnim(){}

bool GW_BoomAnim::Draw(RenderWindow* App, cfloat dt)
{
    BOOMSPRITE.SetPosition(x, y);
    BOOMSPRITE.SetAlpha(ID+255);
    ID -= 510*dt;
    if (ID <= -255)
    {
        return true;
    }
    float scale = (-ID*2/255.f)*35/64.;
    BOOMSPRITE.SetScale(scale, scale);
    App->Draw(BOOMSPRITE);
    BOOMSPRITE.SetAlpha((ID+255)/2.f);
    scale = (1-ID/510.f)*2*35/64.;
    BOOMSPRITE.SetScale(scale, scale);
    App->Draw(BOOMSPRITE);
    return false;
}

bool GW_BoomAnim::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* img = GW_CreateFromFile("img"SEPARATOR"Meteor.png");
    if (img != NULL)
    {
        GW_SetNoSmooth(img, &BOOMSPRITE);
        //BOOMSPRITE.SetImage(*img);
        BOOMSPRITE.SetCenter(BOOMSPRITE.GetSize().x/2, 10);
        exists = true;
        return true;
    }
    return false;
}

void GW_BoomAnim::Close(void)
{
    if (!exists)
    {
        return;
    }
    delete(BOOMSPRITE.GetImage());
    exists = false;
}
#endif
