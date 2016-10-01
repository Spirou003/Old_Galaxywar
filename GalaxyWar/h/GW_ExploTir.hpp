#ifndef GW_EXPLOTIR_H
#define GW_EXPLOTIR_H

#include "GW_Volatile.hpp"

class GW_ExploTir: public GW_Volatile
{
    public:
        ~GW_ExploTir();
        static GW_ExploTir* Create(cfloat X, cfloat Y, cfloat S, cfloat A);
        static bool Init(cbool previnit);
        static void Close(void);

        static Sprite EXPLOSHAPE[7];

        //herited:
            /*virtual void SetX(cfloat X);
            virtual void SetY(cfloat Y);
            virtual float GetX(void) const;
            virtual float GetY(void) const;*/
            virtual bool Draw(RenderWindow* App, cfloat dt);

    private:
        GW_ExploTir(cfloat X, cfloat Y, cfloat S, cfloat A);

        static bool exists;
        static float size;

        float t;
        cfloat s, a;
};

#endif
