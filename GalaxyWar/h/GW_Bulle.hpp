#ifndef GW_BULLE_H
#define GW_BULLE_H

#include "GW_Volatile.hpp"

class GW_Bulle: public GW_Volatile
{
    public:
        ~GW_Bulle();
        static GW_Bulle* Create(cfloat X, cfloat Y, cfloat size, CSInt8 ID);
        static bool Init(cbool previnit);
        static void Close(void);

        static Sprite SPRITEBULLE[2];

        //herited:
            /*virtual void SetX(cfloat X);
            virtual void SetY(cfloat Y);
            virtual float GetX(void) const;
            virtual float GetY(void) const;*/
            virtual bool Draw(RenderWindow* App, cfloat dt);

    private:
        GW_Bulle(cfloat X, cfloat Y, cfloat size, CSInt8 ID);

        static bool exists;

        CSInt8 id;
        cfloat vx, vy;
        float t;
};
#endif
