#ifndef GW_ENNEMI_F_H
#define GW_ENNEMI_F_H

#include "GW_Ennemi_E.hpp"

#define GW_NAMECLASS GW_Ennemi_F

class GW_NAMECLASS: public GW_Ennemi_E
{
    public:
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
        virtual const Shape* GetPolygon (void) const;

        static CSInt32 PVBASE = 100;
        static Sprite SPRITEF[2];
        static cfloat TIMETIRE = 0.25;
        static Shape polygon;
        static float width, height;

    protected:
        static bool exists;
        void Deplacer(cfloat dt);

        float Time, PV, vx, vy, ax, ay, toX, toY, av, t, t2;
        char nb, ID;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
