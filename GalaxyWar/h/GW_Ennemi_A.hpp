#ifndef GW_ENNEMI_A_H
#define GW_ENNEMI_A_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_A

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

        static CSInt32 PV_BASE = 1;
        static cfloat dtmin = 1.f, dtmax = 3.f;
        static float width, height;
        static Shape polygon;
        static Sprite SPRITEA[2];
        static CSInt32 VITESSE = 100;

    private:
        static bool exists;

        float Time, PV, vx, vy, t, t2;
        char sens;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
