#ifndef GW_BOOMANIM_H
#define GW_BOOMANIM_H

#include "GW_Volatile.hpp"

class GW_BoomAnim: public GW_Volatile
{
    public:
        ~GW_BoomAnim();
        static GW_BoomAnim* Create(cfloat X, cfloat Y);
        static GW_BoomAnim* Create();
        static bool Init(cbool previnit);
        static void Close(void);

        static Sprite BOOMSPRITE;

        //herited:
            /*virtual void SetX(cfloat X);
            virtual void SetY(cfloat Y);
            virtual float GetX(void) const;
            virtual float GetY(void) const;*/
            virtual bool Draw(RenderWindow* App, cfloat dt);

    private:
        GW_BoomAnim(void);
        GW_BoomAnim(cfloat X, cfloat Y);

        static bool exists;

        int ID;
};
#endif
