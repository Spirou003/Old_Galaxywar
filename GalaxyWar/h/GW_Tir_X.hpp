#ifndef GW_TIR_X_H
#define GW_TIR_X_H

#include "GW_Tir.hpp"
#include <SFML/Graphics/Color.hpp>

#define GW_NAMECLASS GW_Tir_X

class GW_NAMECLASS: public GW_Tir
{
    public:
        static bool Init(cbool previnit);
        static void Close(void);
        GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle);
        virtual float Power(CSInt32 malus = 0) const;
        virtual ~GW_NAMECLASS(void);
        virtual float GetRadius(void) const;

        static CSInt32 Vitesse = 135;
        static Shape SPRITIR;

        //herited (GW_Collisionnable):
            //virtual void Paralyze(cfloat dt);
            //virtual void Carbonyze(cfloat dt);
            virtual     bool    Dead        (GW_JeuData* truc, RenderWindow* App);
            virtual     bool    IsDead      (void) const;
            //virtual     bool    IsCollisionnable      (void) const;
            //virtual     bool    IsOut       (void) const;
            virtual     void    Action      (GW_JeuData* truc, cfloat dt, bool lim = true);
            virtual     void    Draw        (RenderWindow* App);
            //virtual     int     Type        (void) const;
            virtual const Shape* GetPolygon (void) const;
            //virtual float Effet(GW_NAMECLASS* obj, float self, float other);
            //virtual float Prepare(const GW_NAMECLASS* obj) const;

    private:
        static CSInt32 NCOLOR = 8;
        static const Color CTab[NCOLOR];

        const Color *c;
        float va, a;
};
#undef GW_NAMECLASS
#endif
