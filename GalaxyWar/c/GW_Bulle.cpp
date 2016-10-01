#ifndef GW_BULLE_C
#define GW_BULLE_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Bulle.hpp"
#include "../h/GW_Ennemi_J.hpp"
#include "../h/GW_TSL.hpp"

bool GW_Bulle::exists = false;
Sprite GW_Bulle::SPRITEBULLE[2];
extern CSInt32 GW_Ennemi_J::SIZE_BASE;

GW_Bulle::GW_Bulle(cfloat X, cfloat Y, cfloat size, CSInt8 ID): id(ID != 0), vx(Random(-GW_Ennemi_J::VITESSE, GW_Ennemi_J::VITESSE)), vy(Random(-GW_Ennemi_J::VITESSE, GW_Ennemi_J::VITESSE))
{
    type = BULLE;
    t = size/GW_Ennemi_J::SIZE_BASE;
    y = Y+vy*t/2;
    x = X+vx*t/2;
}

GW_Bulle* GW_Bulle::Create(cfloat X, cfloat Y, cfloat size, CSInt8 ID)
{
    return new GW_Bulle(X, Y, size, ID);
}

GW_Bulle::~GW_Bulle(){}

bool GW_Bulle::Draw(RenderWindow* App, cfloat dt)
{
    t -= dt;
    if (t > 0)
    {
        x += dt*vx;
        y += dt*vy;
        SPRITEBULLE[int(id)].SetPosition(x, y);
        SPRITEBULLE[int(id)].SetScale(t*5, t*5);
        App->Draw(SPRITEBULLE[int(id)]);
        return false;
    }
    else
    {
        return true;
    }
}

bool GW_Bulle::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* ptr[2] = {NULL};
    ptr[0] = GW_CreateFromFile(FILENAME("bulle"));
    if (ptr[0] != NULL)
    {
        ptr[1] = new Image(*ptr[0]);
        if (ptr[1] != NULL)
        {
            GW_TSL(ptr[1], 680, 40, 35);
            GW_SetNoSmooth(ptr[0], &SPRITEBULLE[0]);
            GW_SetNoSmooth(ptr[1], &SPRITEBULLE[1]);
            GW_ToCenter(SPRITEBULLE[0]);
            GW_ToCenter(SPRITEBULLE[1]);
            exists = true;
            return true;
        }
        delete(ptr[0]);
    }
    return false;
}

void GW_Bulle::Close(void)
{
    exists = false;
}
#endif
