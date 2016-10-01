#ifndef GALAXYWAR_C
#define GALAXYWAR_C

#include <SFML/System/Clock.hpp>
#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Constantes.hpp"
#include "../h/GW_GameSet.hpp"
#include "../h/GW_Collisionnable.hpp"
#include "../h/GW_Joueur.hpp"

const char *GW_MenuStr[] = {"Jouer", "HighScores", "Options", "Crédits", "Quitter"};
//const char *GW_MenuStr[] = {"Jouer", "Meilleurs Scores", "Options", "Crédits", "Quitter"};
//const char *GW_MenuStr[] = {"Play", "HighScores", "Settings", "Credits", "Quit"};
//hassan@assabban.be
Color GW_BGCOLOR = Color(1, 3, 47, 255);
Color SfWhite = Color(255, 255, 255, 255);
Color SfRed = Color(255, 0, 0, 255);
Color SfYellow = Color(255, 255, 0, 255);
Color SfGreen = Color(0, 255, 0, 255);
float dtclock = 0;
Shape GW_Collisionnable::Octogon;
Shape GW_Collisionnable::Carre;

int levels[4];
int nbennemis;
int probennemi[GW_Collisionnable::NBENN];

int main(int argc, char *argv[])
{//printf("%s\n",argv[0]);
    float moy = 1;
    bool invincibility = false;
    {
        FILE * azerty = fopen("cheat", "r");
        if (azerty != NULL)
        {
            fclose(azerty);
            invincibility = true;
        }
    }
    GW_Joueur::invincible = invincibility;
    FILE* fichier = fopen("armes.txt", "r");
    if (fichier == NULL)
    {
        return 0;
    }
    float dtmultiply;
    int i = fscanf(fichier, "%d %d %d %d %d %f", &levels[0], &levels[1], &levels[2], &levels[3], &nbennemis, &dtmultiply);
    if (i != 6)
    {
        fclose(fichier);
        return 0;
    }
    i = 0;
    while (i < GW_Collisionnable::EM-GW_Collisionnable::EA+1 && moy == 1)
    {
        moy = fscanf(fichier, " %d", &probennemi[i]);//printf("%d %.0f %d %d\n", i, moy, probennemi[i], GW_Collisionnable::EA-GW_Collisionnable::EM);
        i++;
    }
    i = 1;
    while (i < GW_Collisionnable::EM-GW_Collisionnable::EA+1 && moy == 1)
    {
        probennemi[i] += probennemi[i-1];
        i++;
    }
    fclose(fichier);
    if (moy != 1)
    {
        return 0;
    }
    i = 0;
    Clock clock;
    Image Icon;
    GW_GameSet gwg;
    if (!Icon.LoadFromFile("img\\Icon.png"))
    {
        return EXIT_FAILURE;
    }
    if (!gwg.IsInit())
    {
        return EXIT_FAILURE;
    }
    if (!GW_GameSet::Init())
    {
        return EXIT_FAILURE;
    }
    RenderWindow App(VideoMode(GW_LARGEUR, GW_HAUTEUR, 32), "GalaxyWar", Style::Resize|Style::Close);
    Event event;
    App.SetIcon(Icon.GetWidth(), Icon.GetHeight(), (Uint8*)Icon.GetPixelsPtr());
    App.UseVerticalSync(true);
    App.EnableKeyRepeat(false);
    gwg.InitComponent();
    while (i < 8)
    {
        //GW_Collisionnable::Octogon.AddPoint(1.f, float(i*M_PI/4));
        GW_Collisionnable::Octogon.AddPoint(cos(i*M_PI/4), sin(i*M_PI/4));
        i++;
    }
    i = 0;
    //while (i < 4)
    {
        //GW_Collisionnable::Carre.AddPoint(1.f, float((2*i+1)*M_PI/4));
        GW_Collisionnable::Carre.AddPoint(1, 1);
        GW_Collisionnable::Carre.AddPoint(-1, 1);
        GW_Collisionnable::Carre.AddPoint(-1, -1);
        GW_Collisionnable::Carre.AddPoint(1, -1);
        i++;
    }
    App.Clear(GW_BGCOLOR);
    App.Display();
    clock.Reset();
    App.Display();
    moy = clock.GetElapsedTime();
    while (App.IsOpened())
    {
        dtclock = clock.GetElapsedTime();
        if (dtclock > 2*moy || dtclock < moy/2)
        {
            dtclock = moy;
        }
        else
        {
            moy = (9*moy + dtclock)/10;
        }
        dtclock *= dtmultiply;
        clock.Reset();
        while (App.GetEvent(event))
        {
            gwg.KeepEvent(&App, &event);
        }
        gwg.Display(&App);
        App.Display();
    }
    GW_GameSet::Close();
    return 0;
}
#endif
