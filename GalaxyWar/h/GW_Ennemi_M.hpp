#ifndef GW_ENNEMI_M_H
#define GW_ENNEMI_M_H

#include "GW_Ennemi.hpp"
class GW_Tir_W;

#define GW_NAMECLASS GW_Ennemi_M

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
        virtual     int     Points          (void) const;
        virtual const Shape* GetPolygon (void) const;

        static CSInt32 PV_BASE = 35;
        static CSInt32 VITESSE = 15;
        static CSInt32 DTMIN = 1;
        static CSInt32 DTMAX = 10;
        static Sprite SPRITEM[2];
        static Sprite ECLAT[2];
        static float size;

    private:
        void Deplacer(cfloat dt);
        bool Laser(GW_JeuData* truc);

        static bool exists;

        float t, PV, vx, vy, ax, ay;
        int ismove;
        CSInt8 id;
        GW_Tir_W* laser[2];
};
#undef GW_NAMECLASS
#endif
