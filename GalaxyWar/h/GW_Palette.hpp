#ifndef GW_PALETTE_H
#define GW_PALETTE_H

#include "GW_GraphicsDeclarer.hpp"
#include "Typedefs.hpp"
#include <iostream>

using namespace sf;

class GW_Palette
{
    public:
        GW_Palette(void);
        ~GW_Palette(void);
        void SetID(Color* obj, CSInt32 id);
        const Color* GetID(CSInt32 i) const;

        enum Type
        {
            C1, C2, C3, C4, C5, C6
        };

    private:
        Color* palette[6];
};
#endif
