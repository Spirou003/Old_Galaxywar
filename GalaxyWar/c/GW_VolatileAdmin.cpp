#ifndef GW_VOLATILEADMIN_C
#define GW_VOLATILEADMIN_C

#include "../h/GW_VolatileAdmin.hpp"
#include "../h/GW_VolatileIncluser.hpp"

static bool exists = false;

GW_VolatileAdmin::GW_VolatileAdmin()
{
    int i = 0;
    while (i < GW_Volatile::NBTYPES)
    {
        list[i].Init(true);
        i++;
    }
}

bool GW_VolatileAdmin::Init(cbool previnit)
{
    if (exists || ! previnit)
    {
        return false;
    }
    if (GW_BoomAnim::Init(GW_Number::Init(GW_Fleur::Init(GW_Bulle::Init(GW_ExploTir::Init(true))))))
    {
        exists = true;
        return true;
    }
    return false;
}

void GW_VolatileAdmin::Close(void)
{
    if (!exists)
    {
        return;
    }
    exists = false;
    GW_BoomAnim::Close();
    GW_Number::Close();
    GW_Fleur::Close();
    GW_Bulle::Close();
    GW_ExploTir::Close();
}

GW_VolatileAdmin::~GW_VolatileAdmin()
{
    this->RemoveAll();
    int i = 0;
    while (i < GW_Volatile::NBTYPES)
    {
        list[i].Close();
        i++;
    }
}

void GW_VolatileAdmin::RemoveAll(void)
{
    int i = 0;
    while (i < GW_Volatile::NBTYPES)
    {
        GW_ArrayList<GW_Volatile>::ToEmpty(&list[i]);
        i++;
    }
}

void GW_VolatileAdmin::DrawAll(RenderWindow* App, cfloat dt)
{
    int i = 0, j = 0;
    while (j < GW_Volatile::NBTYPES)
    {
        i = 0;
        while (i < list[j].Size())
        {
            while (i < list[j].Size() && list[j].Get(i)->Draw(App, dt))
            {
                delete(list[j].Delete(i));
            }
            i++;
        }
        j++;
    }
}

bool GW_VolatileAdmin::Add(GW_Volatile* obj)
{
    if (obj == NULL)
    {
        return false;
    }
    return list[int(obj->Type())].Add(obj);
}

#endif
