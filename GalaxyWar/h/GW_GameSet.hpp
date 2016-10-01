#ifndef GW_GAMESET_H
#define GW_GAMESET_H

#include "GW_Constantes.hpp"
#include "GW_Jeu.hpp"
#include "GW_Menu.hpp"
#include "GW_BackGround.hpp"

class GW_GameSet
{
    public:
        GW_GameSet(void);
        ~GW_GameSet(void);
        static bool Init(void);
        static void Close(void);
        void InitComponent(void);
        bool IsInit(void) const;
        void Display(RenderWindow* App);
        void SetEventPriority(CSInt32 id);

        void SetScale(cfloat X, cfloat Y);
        float GetScaleX(void) const;
        float GetScaleY(void) const;
        void KeepEvent(RenderWindow* App, Event* event);
        void Event_Resized(RenderWindow* App);

        enum ObjName
        {
            GW_BUTTON_JOUER, GW_BUTTON_HIGHSCORE, GW_BUTTON_OPTION, GW_BUTTON_CREDIT, GW_MENU
        };

    private:
        bool priorevent[GW_NBEVTKEEP];
        float ScaleX, ScaleY;
        GW_BackGround BackGround;
        GW_Menu Menu;
        GW_Jeu Jeu;
};
#endif
