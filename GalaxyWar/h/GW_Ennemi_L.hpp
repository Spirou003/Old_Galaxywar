#ifndef GW_ENNEMI_L_H
#define GW_ENNEMI_L_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_L

class GW_NAMECLASS: public GW_Ennemi
{
    public:
                            GW_NAMECLASS    ();
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

        static CSInt32 PV_BASE = 10;
        static float size;
        static CSInt32 VITESSE = 30;

    private:
        float PV, vx, vy, t;
        char sens;
};

#undef GW_NAMECLASS
#endif
