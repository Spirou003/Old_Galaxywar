#ifndef GW_ENNEMI_JOUEUR_H
#define GW_ENNEMI_JOUEUR_H

#include "GW_Ennemi.hpp"
class GW_KeySettings;

#define GW_NAMECLASS GW_Joueur

class GW_NAMECLASS: public GW_Ennemi
{
    public:
                            GW_NAMECLASS        (cfloat X, const GW_KeySettings &keyset);
        virtual             ~GW_NAMECLASS       (void);

        virtual     void    Action              (GW_JeuData* truc, cfloat dt, bool lim = true);
        static      void    Close               (void);
        virtual     bool    Dead                (GW_JeuData* truc, RenderWindow* App);
        virtual     int     Degats              (GW_JeuData* truc, GW_Tir* tir);
        virtual     void    Draw                (RenderWindow* App);
        static      bool    Init                (cbool previnit);
        virtual     bool    IsDead              (void) const;
        virtual     bool    IsOut               (void) const;
        //virtual     bool    IsCollisionnable      (void) const;
        virtual     int     Points              (void) const;
        virtual const Shape* GetPolygon (void) const;
        void SetPosition(cfloat X, cfloat Y);

                    void    Actualise           (void);
                    bool    Fire                (GW_JeuData* truc);
                    void    SetEvent            (Event* event, GW_JeuData* truc);
                    bool    SetKeySettings      (GW_KeySettings* keyset);
                    void    SetKeyUp            (cbool v);

        static GW_NAMECLASS* Create(cfloat X);
        static      int     NBJoueur            (void);

        static CSInt32 PV_BASE = 20;
        static Shape polygon;
        static float GW_Joueur_INITJPOS;
        static Sprite SPRITEJOUEUR[4];
        static Sprite LifeBar;
        static CSInt32 VITESSE = 100;
        static char nbj;
        static cfloat HFEU;
        static bool exists;
        static float width, height;
        static bool invincible;

    private:
        float PV;
        float t[GW_NBARME][3];
        int Arme[GW_NBARME];
        int vx, vy;
        bool Key[5];
        char IDReacteur;
        GW_KeySettings *Settings;
};
#undef GW_NAMECLASS
#endif
