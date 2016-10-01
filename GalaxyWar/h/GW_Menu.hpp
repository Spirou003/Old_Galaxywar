#ifndef GW_MENU_H
#define GW_MENU_H

#include "GW_Constantes.hpp"
class GW_GameSet;
#include "GW_GraphicsDeclarer.hpp"
#include <SFML/Graphics/String.hpp>

class GW_Menu
{
    public:
        GW_Menu(void);
        ~GW_Menu(void);
        bool Init(void);
        bool IsInit(void) const;
        void Display(RenderWindow* App, GW_GameSet* gwg);
        void SetDisplay(cbool truc);
        void SetAlpha(CUInt8 a);

        char GetID(cfloat x, cfloat y) const;
        void SelectEvent(RenderWindow* App, Event* event, GW_GameSet* gwg);
        //static void Event_Resized(RenderWindow* App, GW_GameSet* gwg);
        void Event_KeyPressed(RenderWindow* App, Event* event);
        void Event_KeyReleased(RenderWindow* App, Event* event, GW_GameSet* gwg);
        void Event_MouseButtonPressed(RenderWindow* App, Event* event, GW_GameSet* gwg);
        void Event_MouseButtonReleased(RenderWindow* App, Event* event, GW_GameSet* gwg);
        void Event_MouseMoved(RenderWindow* App, Event* event, GW_GameSet* gwg);

        void RunButton(RenderWindow* App, GW_GameSet* gwg, CSInt8 IDButton);
        //void MenuAnim(RenderWindow* App, GW_GameSet* gwg, CSInt8 sens);
        void Refresh(void);

        enum GW_Bouton
        {
            GW_BUTTON_JOUER, GW_BUTTON_HIGHSCORE, GW_BUTTON_OPTION, GW_BUTTON_CREDIT, GW_BUTTON_QUITTER, GW_BUTTON_OUT, GW_BUTTON_NOTHING
        };

    private:
        String Str[GW_NBBUTTON];
        short alpha;
        bool isInit, isAffiched, isActif;
        Font font;
        char toInvisible, IDMoveButton, IDPressButton, IDMPButton, newIDButton, IDClavier, IDPressClavier, nextActif;
};
#endif
