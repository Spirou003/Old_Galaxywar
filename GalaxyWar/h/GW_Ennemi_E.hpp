#ifndef GW_ENNEMI_E_H
#define GW_ENNEMI_E_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_E

class GW_NAMECLASS: public GW_Ennemi
{
    public:
                            GW_NAMECLASS    (void);
                            GW_NAMECLASS    (CSInt8 Id, cfloat X = 0, cfloat Y = 0);
        virtual             ~GW_NAMECLASS   (void);

        virtual     void    Action          (GW_JeuData* truc, cfloat dt, bool lim = true);
        static      void    Close           (void);
        virtual     bool    Dead            (GW_JeuData* truc, RenderWindow* App);
        virtual     int     Degats          (GW_JeuData* truc, GW_Tir* tir);
        virtual     void    Draw            (RenderWindow* App);
        static      bool    Init            (cbool previnit);
        virtual     bool    IsDead          (void) const;
        //virtual     bool    IsOut           (void) const;
        //virtual     bool    IsCollisionnable      (void) const;
        virtual     int     Points          (void) const;
        virtual     void    RandomDir       (void);
        virtual const Shape* GetPolygon (void) const;

/*
        static CSInt32 PV_BASE[3] = {10, 4, 7};
        static CSInt32 POINTS[3] = {100, 55, 65};
        static Sprite SPRITEE[2][3];
        static CSInt32 NBTIR[3] = {3, 2, 5};
        static CSInt8 LEVELTIR[3] = {2, 1, 2};
        static cfloat TIMETIR[3] = {0.3f, 0.1f, 0.2f};
        static cfloat TIMEDEP[3] = {0.6f, 0.3f, 1.0f};
*/
        static CSInt32 PV_BASE[3];
        static CSInt32 POINTS[3];
        static Sprite SPRITEE[2][3];
        static CSInt32 NBTIR[3];
        static CSInt32 NBDEP[3];
        static CSInt8 LEVELTIR[3];
        static cfloat TIMETIR[3];
        static cfloat TIMEDEP[3];
        static float size[3];

    protected:
        static bool exists;

        float Time, PV, vx, vy, ax, ay, toX, toY, av;
        char nb, ID;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
