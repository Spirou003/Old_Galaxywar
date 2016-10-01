#ifndef GW_JEU_C
#define GW_JEU_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_GameSet.hpp"
#include "../h/GW_Jeu.hpp"
#include "../h/GW_JeuData.hpp"
#include "../h/GW_Number.hpp"
#include "../h/GW_VolatileAdmin.hpp"
#include "../h/GW_CollisionnableAdmin.hpp"
#include "../h/GW_Tir.hpp"
#include "../h/GW_Joueur.hpp"
#include "../h/GW_Ennemi_G.hpp"
static bool exists = false;
extern float dtclock;
static Sprite SPoints;
static Image* imgpts;
bool existimage = false;

GW_Jeu::GW_Jeu(void)
{
    Score = 0;
    isDisplay = false;
    Data.Niveau = 0;
    PlaceTotale = 0;
    PlaceRestante = 0;
    PositionNiveau = 0;
    FinNiveau = 0;
    game = false;
    initanim = true;
    Data.VolatiList = new GW_VolatileAdmin();
    isInit = Data.Tirs_Ennemi.Init(Data.Tirs_Joueur.Init(Data.Unites.Init(Data.VolatiList != NULL)));
}

void GW_Jeu::Display(RenderWindow* App, GW_GameSet* gwg)
{
    if (!isDisplay)
    {
        return;
    }
    if (initanim)
    {
        if (Data.Joueur->GetY() < GW_Joueur::GW_Joueur_INITJPOS)
        {
            initanim = false;
            game = true;
            Data.Joueur->SetKeyUp(false);
        }
        Data.Joueur->Action(&Data, dtclock, false);
        Data.Joueur->Draw(App);
        return;
    }
    else if (game)
    {
        int copyscore = Score;
        this->Lists_Refresh(App);
        this->Lists_Actions(dtclock);
        this->Lists_Collisions();
        this->Lists_Draw(App);
        Data.VolatiList->DrawAll(App, dtclock);
        if (Data.Joueur->IsDeletable())
        {
            delete(Data.Joueur);
        }
        else
        {
            Data.Joueur->Action(&Data, dtclock);
            Data.Joueur->Draw(App);
        }
        if (copyscore != Score)
        {
            this->Number();
        }
        App->Draw(SPoints);
        GW_CollisionnableAdmin::AddEnnemies(&Data);
    }
    if (GW_Joueur::NBJoueur() == 0)
    {
        this->ToNull();
        isDisplay = false;
        gwg->SetEventPriority(GW_GameSet::GW_MENU);
        gwg->SetEventPriority(GW_Menu::GW_BUTTON_JOUER);
    }
}

void GW_Jeu::Lists_Draw(RenderWindow* App)
{
    int i = 0;
    while (i < Data.Tirs_Joueur.Size())
    {
        Data.Tirs_Joueur.Get(i)->Draw(App);
        i++;
    }
    i = 0;
    while (i < Data.Tirs_Ennemi.Size())
    {
        Data.Tirs_Ennemi.Get(i)->Draw(App);
        i++;
    }
    i = 0;
    while (i < Data.Unites.Size())
    {
        Data.Unites.Get(i)->Draw(App);
        i++;
    }
}

void GW_Jeu::Lists_Actions(cfloat dt)
{
    int i = 0;
    while (i < Data.Tirs_Joueur.Size())
    {
        Data.Tirs_Joueur.Get(i)->Action(&Data, dt);
        i++;
    }
    i = 0;
    while (i < Data.Unites.Size())
    {
        Data.Unites.Get(i)->Action(&Data, dt);
        i++;
    }
    i = 0;
    while (i < Data.Tirs_Ennemi.Size())
    {
        Data.Tirs_Ennemi.Get(i)->Action(&Data, dt);
        i++;
    }
}

void GW_Jeu::Lists_Collisions(void)
{
    int i = 0, j = 0;
    while (i < Data.Tirs_Joueur.Size())
    {
        j = 0;
        while (j < Data.Unites.Size())
        {
            if (!Data.Tirs_Joueur.Get(i)->IsDead() && !Data.Unites.Get(j)->IsDead() && GW_Collisionnable::Collision(Data.Unites.Get(j), Data.Tirs_Joueur.Get(i)))
            {
                Score += Data.Unites.Get(j)->Degats(&Data, Data.Tirs_Joueur.Get(i));
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < Data.Tirs_Ennemi.Size())
    {
        if (!Data.Tirs_Ennemi.Get(i)->IsDead() && GW_Collisionnable::Collision(Data.Joueur, Data.Tirs_Ennemi.Get(i)))
        {
            Data.Joueur->Degats(&Data, Data.Tirs_Ennemi.Get(i));
        }
        i++;
    }
}

void GW_Jeu::Lists_Refresh(RenderWindow* App)
{
    int i = 0;
    while (i < Data.Tirs_Ennemi.Size())
    {
        while (i < Data.Tirs_Ennemi.Size() && (Data.Tirs_Ennemi.Get(i)->IsDeletable()))
        {
            if (Data.Tirs_Ennemi.Get(i)->IsDead())
            {
                Data.Tirs_Ennemi.Get(i)->Dead(&Data, App);
            }
            delete(Data.Tirs_Ennemi.Delete(i));
        }
        i++;
    }
    i = 0;
    while (i < Data.Tirs_Joueur.Size())
    {
        while (i < Data.Tirs_Joueur.Size() && (Data.Tirs_Joueur.Get(i)->IsDeletable()))
        {
            if (Data.Tirs_Joueur.Get(i)->IsDead())
            {
                Data.Tirs_Joueur.Get(i)->Dead(&Data, App);
            }
            delete(Data.Tirs_Joueur.Delete(i));
        }
        i++;
    }
    i = 0;
    while (i < Data.Unites.Size())
    {
        while (i < Data.Unites.Size() && (Data.Unites.Get(i)->IsDeletable()))
        {
            if (Data.Unites.Get(i)->IsDead())
            {
                Data.Unites.Get(i)->Dead(&Data, App);
            }
            delete(Data.Unites.Delete(i));
        }
        i++;
    }
}

bool GW_Jeu::NewGame(void)
{
    isDisplay = true;
    FinNiveau = 0;
    bool truc = true;
    Image* ptr = GW_Number::IntegerToImage(0, 0, 0, 0);
    if (ptr == NULL)
    {
        return false;
    }
    existimage = true;
    imgpts = ptr;
    SPoints.SetImage(*imgpts);
    GW_ToCenter(SPoints);
    SPoints.SetScale(0.5f, 0.5f);
    SPoints.SetPosition(GW_LARGEUR - SPoints.GetSize().x*0.5 - 5, GW_HAUTEUR - SPoints.GetSize().y*0.5 - 5);
    Data.Joueur = GW_Joueur::Create(GW_LARGEUR/2);
    if (Data.Joueur == NULL)
    {
        truc = false;
    }
    else
    {
        Data.Joueur->SetKeyUp(true);
    }
    if (!truc)
    {
        delete(imgpts);
        return false;
    }
    return true;
}

bool GW_Jeu::Number(void)
{
    Image* ptr = GW_Number::IntegerToImage(Score, 0, 0, 0);
    if (ptr == NULL)
    {
        return false;
    }
    delete(imgpts);
    imgpts = ptr;
    SPoints.SetImage(*imgpts);
    GW_ToCenter(SPoints);
    SPoints.SetScale(0.5f, 0.5f);
    SPoints.SetPosition(GW_LARGEUR - SPoints.GetSize().x*0.75 - 5, GW_HAUTEUR - SPoints.GetSize().y*0.75 - 5);
    return true;
}

bool GW_Jeu::IsInit(void) const
{
    return isInit;
}

bool GW_Jeu::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    if (GW_CollisionnableAdmin::Init(GW_VolatileAdmin::Init(true)))
    {
        exists = true;
        return true;
    }
    GW_Jeu::Close();
    return false;
}

void GW_Jeu::SetDisplay(bool truc)
{
    isDisplay = truc;
}

void GW_Jeu::Close(void)
{
    GW_CollisionnableAdmin::Close();
    GW_VolatileAdmin::Close();
}

GW_Jeu::~GW_Jeu(void)
{
    this->ToNull();
    Data.Tirs_Ennemi.Close();
    Data.Tirs_Joueur.Close();
    Data.Unites.Close();
    delete(Data.VolatiList);
}

void GW_Jeu::ToNull(void)
{
    printf("%d\n", Score);
    Score = 0;
    Data.Niveau = 0;
    PlaceTotale = 0;
    PlaceRestante = 0;
    PositionNiveau = 0;
    FinNiveau = 0;
    game = false;
    if (existimage)
    {
        delete(imgpts);
        existimage = false;
    }
    initanim = true;
    GW_ArrayList<GW_Tir>::ToEmpty(&(Data.Tirs_Ennemi));
    GW_ArrayList<GW_Tir>::ToEmpty(&(Data.Tirs_Joueur));
    GW_ArrayList<GW_Ennemi>::ToEmpty(&(Data.Unites));
    Data.VolatiList->RemoveAll();
    if (GW_Joueur::NBJoueur() == 1)
    {
        delete(Data.Joueur);
    }
}

bool GW_Jeu::AddTir(GW_Tir* tir)
{
    return Data.Tirs_Ennemi.Add(tir);
}

void GW_Jeu::Event_KeyPressed(RenderWindow* App, Event* event)
{
    if (game)
    {
        Data.Joueur->SetEvent(event, &Data);
    }
}

void GW_Jeu::Event_KeyReleased(RenderWindow* App, Event* event)
{
    if (game)
    {
        Data.Joueur->SetEvent(event, &Data);
    }
}

void GW_Jeu::SelectEvent(RenderWindow* App, Event* event, GW_GameSet* gwg)
{
    switch(event->Type)
    {
        case Event::KeyPressed:
            this->Event_KeyPressed(App, event);
            break;
        case Event::KeyReleased:
            this->Event_KeyReleased(App, event);
            break;
        /*/
        case Event::Closed:
            App->Close();
            break;
        case Event::Resized:
            this->Event_Resized(App, gwg);
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
        //*/
        default:
            break;
    }
}
#endif
