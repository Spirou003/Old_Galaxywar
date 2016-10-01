#ifndef GW_ENNEMI_B_H
#define GW_ENNEMI_B_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_B

class GW_NAMECLASS: public GW_Ennemi
{
    public:
                            GW_NAMECLASS    (cbool IsBoost);
        virtual             ~GW_NAMECLASS   (void);

        virtual     void    Action          (GW_JeuData* truc, cfloat dt, bool lim = true);
        static      void    Close           (void);
        virtual     bool    Dead            (GW_JeuData* truc, RenderWindow* App);
        virtual     int     Degats          (GW_JeuData* truc, GW_Tir* tir);
        virtual     void    Draw            (RenderWindow* App);
        static      bool    Init            (cbool previnit);
        virtual     bool    IsDead          (void) const;
        virtual     bool    IsOut           (void) const;
        //virtual     bool    IsCollisionnable      (void) const;
        virtual     int     Points          (void) const;
        virtual const Shape* GetPolygon (void) const;

        static CSInt32 PV_BASE = 3;
        static CSInt32 NBTIR = 3;
        static cfloat TIMETIR = 0.33f;
        static cfloat BEFORE = 3.f;
        static Shape polygon;
        static CSInt32 VITESSE = 180;
        static Sprite SPRITEB[2];
        static float width, height;

    private:
        static bool exists;

        float Time, PV, toY, cx, cy, a;
        int ID;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
