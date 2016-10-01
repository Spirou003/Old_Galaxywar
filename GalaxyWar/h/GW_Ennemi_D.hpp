#ifndef GW_ENNEMI_D_H
#define GW_ENNEMI_D_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_D

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

        static CSInt32 PV_BASE = 5;
        static Sprite SPRITED[2][2];
        static CSInt32 VITESSE = 40;
        static float width, height;

    private:
        static bool exists;

        float Time, PV, acible, a, vx, vy;
        //GW_Joueur* cible;
        //GW_Tir_Y* tir;
        char sens;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
