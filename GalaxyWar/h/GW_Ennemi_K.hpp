#ifndef GW_ENNEMI_RUBIKUBE_H
#define GW_ENNEMI_RUBIKUBE_H

#include "GW_Ennemi.hpp"
class GW_Palette;

#define GW_NAMECLASS GW_Ennemi_K

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
        //virtual     bool    IsOut           (void) const;
        virtual     bool    IsCollisionnable      (void) const;
                    int     KubesDead       (void) const;
        virtual     int     Points          (void) const;
        virtual const Shape* GetPolygon (void) const;

        void Rotate(CSInt8 t, cbool sens);
        float GetPV(CSInt32 X, CSInt32 Y, CSInt32 z) const;
        void SetPV(CSInt32 X, CSInt32 Y, CSInt32 z, cfloat pv);
        const Color* GetColor(CSInt32 X, CSInt32 Y, CSInt32 z) const;
        void ChangeDir(float* i, float* vi, float* k, float* vk, CSInt32 d);

        static CSInt32 PV_BASE = 10;
        static cfloat TIMETIR = 2.0f;
        static CSInt32 SizeKube = 17;
        static Sprite SPRITIKUBE;
        static CSInt32 VITESSE = 85;

    private:
        void rotateface(CSInt32 nb, cbool dir);
        void SetColor(cbool isboost);
        void SetBande(CSInt32 q);
        void RepareCoin(CSInt32 a1, CSInt32 b1, CSInt32 c1, CSInt32 a2, CSInt32 b2, CSInt32 c, CSInt32 a3, CSInt32 b3, CSInt32 c3, CSInt32 a4, CSInt32 b4, CSInt32 c4);
        void PermutePV(CSInt32 a1, CSInt32 b1, CSInt32 c1, CSInt32 a2, CSInt32 b2, CSInt32 c, CSInt32 a3, CSInt32 b3, CSInt32 c3, CSInt32 a4, CSInt32 b4, CSInt32 c4);

        const Color* Face[6][3][3];
        const Color* inrotate[6];
        float PV[3][3][3];
        float toPos, Time, vx, vy, a, t;
        char nbdead, idrotate;
        CSInt8 id;
        GW_Palette *Palette;
};
#undef GW_NAMECLASS
#endif
