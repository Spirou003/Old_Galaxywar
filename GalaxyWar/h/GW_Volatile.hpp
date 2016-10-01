#ifndef GW_VOLATILE_H
#define GW_VOLATILE_H

#include "GW_Constantes.hpp"
#include "GW_Functions.hpp"

class GW_Volatile
{
    public:
        GW_Volatile();
        virtual ~GW_Volatile();
        virtual void SetX(cfloat X);
        virtual void SetY(cfloat Y);
        virtual float GetX(void) const;
        virtual float GetY(void) const;
        virtual bool Draw(RenderWindow* App, cfloat dt) = 0;
        char Type(void) const;

        enum Type
        {
            FLEUR, BULLE, EXPLOTIR, BOOMANIM, NUMBER, NBTYPES
        };

    protected:
        float x, y;
        char type;
};
#endif
