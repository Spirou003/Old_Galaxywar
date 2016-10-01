#ifndef GW_ENNEMI_H_H
#define GW_ENNEMI_H_H

#include "GW_Ennemi.hpp"
#define GW_NAMECLASS GW_Ennemi_H

class GW_NAMECLASS: public GW_Ennemi
{
    public:
                            GW_NAMECLASS    (cbool IsBoost);
        virtual             ~GW_NAMECLASS   (void);

        virtual     void    Action          (GW_JeuData* truc, cfloat dt, bool lim = true) noconst;
        static      void    Close           (void);
        virtual     bool    Dead            (GW_JeuData* truc, RenderWindow* App) noconst;
        virtual     int     Degats          (GW_JeuData* truc, GW_Tir* tir) noconst;
        virtual     void    Draw            (RenderWindow* App) noconst;
        static      bool    Init            (cbool previnit);
        virtual     bool    IsDead          (void) const;
        virtual     bool    IsOut           (void) const;
        //virtual     bool    IsCollisionnable      (void) const;
        virtual     int     Points          (void) const;
        virtual const Shape* GetPolygon (void) const;

        static CSInt32 PV_BASE = 150;
        static Shape polygon[2];
        static CSInt32 MOVITESSE = 300;
        static CSInt32 VITESSE = 45;
        static Sprite SPRITEH[2][2];
        static bool exists;

        enum TypeOpen
        {
            OO, OC, CO, CC
        };

    private:
        void Move(cfloat dt) noconst;
        void Change(void) noconst;
        void Ailes(cfloat dt) noconst;
        void Attaque(GW_JeuData* truc, cfloat dt) noconst;
        void AddTir(GW_JeuData* truc, cfloat precis = M_PI/8) const;
        static float width, height;

        float PV, vx, vy, ax, ay, t, t2, a_aile, vOpen;
        int ID, sens, nbtir;
        char isOpen;
        CSInt32 id;
};
#undef GW_NAMECLASS
#endif
