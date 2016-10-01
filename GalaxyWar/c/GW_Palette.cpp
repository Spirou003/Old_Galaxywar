#ifndef GW_PALETTE_C
#define GW_PALETTE_C

#include <SFML/Graphics/Color.hpp>
#include "../h/GW_Palette.hpp"

GW_Palette::~GW_Palette(void)
{
    int i = 0;
    while (i < 6)
    {
        delete(palette[i]);
        i++;
    }
}

GW_Palette::GW_Palette(void)
{
    int i = 0;
    while (i < 6)
    {
        this->SetID(NULL, i);
        i++;
    }
}

void GW_Palette::SetID(Color* obj, CSInt32 id)
{
    palette[id] = obj;
}

const Color* GW_Palette::GetID(CSInt32 id) const
{
    return palette[id];
}

#endif
