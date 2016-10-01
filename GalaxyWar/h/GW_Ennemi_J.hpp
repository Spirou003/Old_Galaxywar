#ifndef GW_ENNEMI_J_H
#define GW_ENNEMI_J_H

#include "GW_Ennemi.hpp"

#define GW_NAMECLASS GW_Ennemi_J

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
        void SetSize(cfloat Size);

        static CSInt32 PV_BASE = 20;
        static Sprite SPRITEJ[2][6];
        static Sprite NOYAU;
        static CSInt32 VITESSE = 40;
        static CSInt32 SIZE_BASE = 100;
        static CSInt32 PTS_BASE = 150;
        static float SizeNoyau;

    private:
        void Deplacer(cfloat dt);

        static int nb;
        static bool exists;

        float Time, PV, nx, ny, nx2, ny2, coeff, vx, vy, ax, ay, size;
        char idDraw;
        bool isDiv, celldiv;
        int pts;
        CSInt8 id;
};
#undef GW_NAMECLASS
#endif
