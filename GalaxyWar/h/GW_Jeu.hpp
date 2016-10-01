#ifndef GW_JEU_H
#define GW_JEU_H

#include "GW_Constantes.hpp"
class GW_GameSet;
#include "GW_JeuData.hpp"
class GW_Tir;
#include "GW_GraphicsDeclarer.hpp"

class GW_Jeu
{
    public:
        GW_Jeu(void);
        ~GW_Jeu(void);
        //bool InitComponent(void);
        bool IsInit(void) const;
        void CloseComponent(void);
        void ToNull(void);
        static bool Init(cbool previnit);
        static void Close(void);
        void Display(RenderWindow* App, GW_GameSet* gwg);
        void SetDisplay(cbool previnit);
        bool AddTir(GW_Tir* tir);

        void Lists_Refresh (RenderWindow* App);
        void Lists_Collisions(void);
        void Lists_Actions(cfloat dt);
        void Lists_Draw(RenderWindow* App);

        bool NewGame(void);
        bool Number(void);

        void SelectEvent(RenderWindow* App, Event* event, GW_GameSet* gwg);
        //static void Event_Resized(RenderWindow* App, GW_GameSet* gwg);
        void Event_KeyPressed(RenderWindow* App, Event* event);
        void Event_KeyReleased(RenderWindow* App, Event* event);
        void Event_MouseButtonPressed(RenderWindow* App, Event* event, GW_GameSet* gwg);
        void Event_MouseButtonReleased(RenderWindow* App, Event* event, GW_GameSet* gwg);
        void Event_MouseMoved(RenderWindow* App, Event* event, GW_GameSet* gwg);


        GW_JeuData Data;
        //int nbJoueur;

    private:
        //friend class GW_Joueur;

        int Score, PlaceTotale, PlaceRestante, PositionNiveau, FinNiveau;
        bool isInit, game, intergame, initanim, isDisplay;

};
#endif
