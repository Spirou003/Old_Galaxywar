#ifndef GW_MENU_C
#define GW_MENU_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Menu.hpp"
#include "../h/GW_GameSet.hpp"

extern Color GW_BGCOLOR;
extern Color SfWhite;
extern Color SfRed;
extern Color SfYellow;
extern Color SfGreen;
extern const char *GW_MenuStr[];

GW_Menu::GW_Menu(void)
{
    IDMoveButton = GW_BUTTON_OUT;
    IDPressButton = GW_BUTTON_OUT;
    IDMPButton = GW_BUTTON_OUT;
    alpha = 255;
    isActif = true;
    toInvisible = 5;
    IDClavier = 0;
    newIDButton = GW_BUTTON_NOTHING;
    IDPressClavier = GW_BUTTON_OUT;
    isInit = this->Init();
    isAffiched = true;
}

void GW_Menu::SetAlpha(CUInt8 a)
{
    alpha = a;
}

void GW_Menu::Refresh(void)
{
    int i = 0;
    while (i < GW_NBBUTTON)
    {
        Str[i].SetAlpha(alpha);
        i++;
    }
}

void GW_Menu::SetDisplay(cbool truc)
{
    isAffiched = truc;
}

bool GW_Menu::IsInit(void) const
{
    return isInit;
}

GW_Menu::~GW_Menu(void)
{
    ;
}

bool GW_Menu::Init(void)
{
    if (!font.LoadFromFile("img\\police.ttf"))
    {
        return false;
    }
    int i = 0;
    while (i < GW_NBBUTTON)
    {
        Str[i].SetFont(font);
        Str[i].SetText(GW_MenuStr[i]);
        Str[i].SetCenter(Str[i].GetRect().Right/2, 0);
        Str[i].SetPosition(GW_LARGEUR/2, (GW_HAUTEUR+(2*i-GW_NBBUTTON)*GW_FONTSIZE)/2);
        i++;
    }
    return true;
}

void GW_Menu::Display(RenderWindow* App, GW_GameSet* gwg)
{
    if (!isAffiched)
    {
        return;
    }
    if (!isActif)
    {
        this->Refresh();
        alpha -= toInvisible;
    }
    int i = 0;
    while (i < GW_NBBUTTON)
    {
        App->Draw(Str[i]);
        i++;
    }
    if (alpha < 0)
    {
        alpha = 0;
        toInvisible = -toInvisible;
        isAffiched = false;
        gwg->SetEventPriority(GW_GameSet::GW_MENU);
        gwg->SetEventPriority(nextActif);
    }
    else if(alpha > 255)
    {
        alpha = 255;
        toInvisible = -toInvisible;
        isActif = true;
    }
}

char GW_Menu::GetID(cfloat x, cfloat y) const
{
    int i = 0;
    while (i < GW_NBBUTTON)
    {
        if (Str[i].GetRect().Top < y && Str[i].GetRect().Top+GW_FONTSIZE > y && Str[i].GetRect().Left < x && x < Str[i].GetRect().Right)
        {
            return i;
        }
        i++;
    }
    return i;
}

void GW_Menu::SelectEvent(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    switch(event->Type)
    {
        /*/
        case Event::Closed:
            App->Close();
            break;
        case Event::Resized:
            this->Event_Resized(App, gwg);
            break;
        //*/
        case Event::KeyPressed:
            this->Event_KeyPressed(App, event);
            break;
        case Event::KeyReleased:
            this->Event_KeyReleased(App, event, gwg);
            break;
        case Event::MouseMoved:
            this->Event_MouseMoved(App, event, gwg);
            break;
        case Event::MouseButtonPressed:
            this->Event_MouseButtonPressed(App, event, gwg);
            break;
        case Event::MouseButtonReleased:
            this->Event_MouseButtonReleased(App, event, gwg);
            break;
        default:
            break;
    }
}

/*/
void GW_Menu::Event_Resized(RenderWindow* App, GW_GameSet* gwg)
{
    gwg->SetScale(App->GetWidth()*1.f/GW_LARGEUR, App->GetHeight()*1.f/GW_HAUTEUR);
    App->SetSize((UInt32)(GW_LARGEUR*gwg->GetScaleX()), (UInt32)(GW_HAUTEUR*gwg->GetScaleY()));
}
//*/

void GW_Menu::Event_KeyReleased(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    Str[(int)IDClavier].SetStyle(String::Regular);
    switch(event->Key.Code)
    {
        case Key::Up:
        case Key::Numpad8:
            IDClavier--;
            if (IDClavier <= 0)
            {
                IDClavier = 0;
            }
            break;
        case Key::Down:
        case Key::Numpad2:
            IDClavier++;
            if (IDClavier >= GW_BUTTON_OUT)
            {
                IDClavier = GW_BUTTON_OUT-1;
            }
            break;
        case Key::Space:
        case Key::Return:
            Str[(int)IDPressClavier].SetColor(SfWhite);
            if (IDClavier == IDPressClavier)
            {
                this->RunButton(App, gwg, IDClavier);
            }
            IDPressClavier = GW_BUTTON_OUT;
            break;
        case Key::Escape:
            App->Close();
            break;
        default:
            break;
    }
    Str[(int)IDClavier].SetStyle(String::Italic);
}

void GW_Menu::Event_KeyPressed(RenderWindow* App, Event* event)
{
    Str[(int)IDClavier].SetStyle(String::Italic);
    switch(event->Key.Code)
    {
        case Key::Space:
        case Key::Return:
            IDPressClavier = IDClavier;
            Str[(int)IDPressClavier].SetColor(SfGreen);
            break;
        default:
            break;
    }
}

void GW_Menu::Event_MouseMoved(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    newIDButton = this->GetID(event->MouseMove.X/gwg->GetScaleX(), event->MouseMove.Y/gwg->GetScaleY());
    if (IDPressButton == GW_BUTTON_OUT)
    {
        if (IDMoveButton != GW_BUTTON_OUT)
        {
            Str[(int)IDMoveButton].SetColor(SfWhite);
        }
        if (newIDButton != GW_BUTTON_OUT)
        {
            IDMoveButton = newIDButton;
            Str[(int)IDMoveButton].SetColor(SfYellow);
        }
    }
    else
    {
        if (IDMPButton != GW_BUTTON_OUT)
        {
            Str[(int)IDMPButton].SetColor(SfWhite);
        }
        if (IDMoveButton != GW_BUTTON_OUT)
        {
            Str[(int)IDMoveButton].SetColor(SfYellow);
        }
        if (newIDButton != GW_BUTTON_OUT)
        {
            IDMPButton = newIDButton;
            Str[(int)IDMPButton].SetColor(SfRed);
        }
    }
    if (IDPressClavier != GW_BUTTON_OUT)
    {
        Str[(int)IDPressClavier].SetColor(SfGreen);
    }
}

void GW_Menu::Event_MouseButtonPressed(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    newIDButton = this->GetID(event->MouseButton.X/gwg->GetScaleX(), event->MouseButton.Y/gwg->GetScaleY());
    if (newIDButton != GW_BUTTON_OUT)
    {
        IDPressButton = newIDButton;
        Str[(int)IDPressButton].SetColor(SfRed);
    }
    if (IDPressClavier != GW_BUTTON_OUT)
    {
        Str[(int)IDPressClavier].SetColor(SfGreen);
    }
}

void GW_Menu::Event_MouseButtonReleased(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    if (IDPressButton != GW_BUTTON_OUT)
    {
        Str[(int)IDPressButton].SetColor(SfWhite);
    }
    if (newIDButton != GW_BUTTON_OUT && newIDButton != GW_BUTTON_NOTHING)
    {
        Str[(int)newIDButton].SetColor(SfYellow);
    }
    if (this->GetID(event->MouseButton.X/gwg->GetScaleX(), event->MouseButton.Y/gwg->GetScaleY()) == IDPressButton)
    {
        this->RunButton(App, gwg, IDPressButton);
        IDMoveButton = GW_BUTTON_OUT;
        IDMPButton = GW_BUTTON_OUT;
    }
    IDPressButton = GW_BUTTON_OUT;
    if (IDPressClavier != GW_BUTTON_OUT)
    {
        Str[(int)IDPressClavier].SetColor(SfGreen);
    }
}

void GW_Menu::RunButton(RenderWindow* App, GW_GameSet* gwg, CSInt8 IDButton)
{
    if (!isActif)
    {
        return;
    }
    nextActif = IDButton;
    if (IDButton == GW_BUTTON_QUITTER)
    {
        App->Close();
        return;
    }
    else if (IDButton == GW_BUTTON_OUT)
    {
        return;
    }
    isActif = false;
}
#endif
