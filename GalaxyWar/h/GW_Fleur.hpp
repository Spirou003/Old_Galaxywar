#ifndef GW_FLEUR_H
#define GW_FLEUR_H

#include "GW_Volatile.hpp"
#include <SFML/Graphics/Color.hpp>

class GW_Fleur: public GW_Volatile
{
    public:
        ~GW_Fleur();
        static GW_Fleur* Create(cfloat X, cfloat Y, const Color &C);
        static GW_Fleur* Create(cfloat X, cfloat Y);
        static GW_Fleur* Create();
        static bool Init(cbool previnit);
        static void Close(void);

        static Sprite SPRITEFLEUR[2];
        static Image IMAGEFLEUR[2];

        //herited:
            /*virtual void SetX(cfloat X);
            virtual void SetY(cfloat Y);
            virtual float GetX(void) const;
            virtual float GetY(void) const;*/
            virtual bool Draw(RenderWindow* App, cfloat dt);

    private:
        GW_Fleur(void);
        GW_Fleur(cfloat X, cfloat Y);
        GW_Fleur(cfloat X, cfloat Y, const Color &C);

        static bool exists;
        static cfloat MINSIZE, MAXSIZE;

        Color c;
        cfloat a, s;
        float t, T;
        int ID;
};
#endif
