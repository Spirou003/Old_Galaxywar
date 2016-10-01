#ifndef GW_GAMESET_C
#define GW_GAMESET_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_GameSet.hpp"
#include "../h/GW_Menu.hpp"
#include "../h/GW_Jeu.hpp"
#include "../h/GW_BackGround.hpp"

static bool exists = false;

GW_GameSet::GW_GameSet(void)
{
    ScaleX = 1.f;
    ScaleY = 1.f;
    int i = 0;
    while (i < GW_NBEVTKEEP)
    {
        priorevent[i] = false;
        i++;
    }
    priorevent[GW_MENU] = true;
}

void GW_GameSet::InitComponent(void)
{
    BackGround.Generate();
}

bool GW_GameSet::IsInit(void) const
{
    return (Menu.IsInit() && Jeu.IsInit());
}

bool GW_GameSet::Init(void)
{
    if (exists)
    {
        return false;
    }
    if (GW_Jeu::Init(GW_BackGround::Load()))
    {
        GW_BackGround::Init();
        exists = true;
    }
    else
    {
        GW_GameSet::Close();
    }
    return exists;
}

GW_GameSet::~GW_GameSet(void)
{
    ;
}

void GW_GameSet::Close(void)
{
    GW_BackGround::Close();
    GW_Jeu::Close();
    exists = false;
}

void GW_GameSet::Display(RenderWindow* App)
{
    BackGround.Display(App);
    Menu.Display(App, this);
    Jeu.Display(App, this);
}

void GW_GameSet::SetScale(cfloat X, cfloat Y)
{
    float x = X, y = Y;
    if (y == 0.f)
    {
        y = 1000000000;
    }
    if (x == 0.f)
    {
        x = 1000000000;
    }
    if (x < y)
    {
        y = x;
    }
    else
    {
        x = y;
    }
    ScaleX = x;
    ScaleY = y;
}

float GW_GameSet::GetScaleX(void) const
{
    return ScaleX;
}

float GW_GameSet::GetScaleY(void) const
{
    return ScaleY;
}

void GW_GameSet::KeepEvent(RenderWindow* App, Event* event)
{
    if (event->Type == Event::Resized)
    {
        this->Event_Resized(App);
        return;
    }
    else if (event->Type == Event::Closed)
    {
        App->Close();
        return;
    }
    if (priorevent[GW_MENU])
    {
        Menu.SelectEvent(App, event, this);
    }
    else if (priorevent[GW_Menu::GW_BUTTON_JOUER])
    {
        Jeu.SelectEvent(App, event, this);
    }
}

void GW_GameSet::Event_Resized(RenderWindow* App)
{
    this->SetScale(App->GetWidth()*1.f/GW_LARGEUR, App->GetHeight()*1.f/GW_HAUTEUR);
    App->SetSize((UInt32)(GW_LARGEUR*ScaleX), (UInt32)(GW_HAUTEUR*ScaleY));
}

void GW_GameSet::SetEventPriority(CSInt32 id)
{
    priorevent[id] = !priorevent[id];
    switch (id)
    {
        case GW_MENU:
            if (priorevent[GW_MENU])
            {
                Menu.SetDisplay(true);
            }
            break;
        case GW_Menu::GW_BUTTON_OPTION:
            priorevent[GW_Menu::GW_BUTTON_OPTION] = false;
            this->SetEventPriority(GW_MENU);
            break;
        case GW_Menu::GW_BUTTON_HIGHSCORE:
            priorevent[GW_Menu::GW_BUTTON_HIGHSCORE] = false;
            this->SetEventPriority(GW_MENU);
            break;
        case GW_Menu::GW_BUTTON_JOUER:
            if (priorevent[GW_Menu::GW_BUTTON_JOUER])
            {
                Jeu.NewGame();
            }
            break;
        case GW_Menu::GW_BUTTON_CREDIT:
            priorevent[GW_Menu::GW_BUTTON_CREDIT] = false;
            this->SetEventPriority(GW_MENU);
            break;
        default:
            break;
    }
}
#endif
