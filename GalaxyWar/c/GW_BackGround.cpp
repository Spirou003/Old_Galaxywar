#ifndef GW_BACKGROUND_C
#define GW_BACKGROUND_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_BackGround.hpp"
#include "../h/GW_Functions.hpp"

static bool exists = false;
static Image imetoile;
static Sprite spetoile;
static Image* impla;
static Sprite* sppla;
extern Color GW_BGCOLOR;
static float r = GW_BGCOLOR.r;
static float g = GW_BGCOLOR.g;
static float b = GW_BGCOLOR.b;
static float tor = 0;
static float tog = 0;
static float tob = 0;
static UInt32 GW_NPLANET = 0;

GW_BackGround::GW_BackGround(void)
{
    x = 0;
    y = 0;
    LastID = 0;
    isAffiched = true;
}

void GW_BackGround::SetDisplay(cbool truc)
{
    isAffiched = truc;
}

bool GW_BackGround::Load(void)
{
    if (exists)
    {
        return false;
    }
    FILE* fichier = fopen("planets.txt", "r");
    if (fichier == NULL)
    {
        return false;
    }
    int t = fscanf(fichier, "%d", &GW_NPLANET);
    fclose(fichier);
    if (t != 1)
    {
        return false;
    }
    if (GW_NPLANET > 1000)
    {
        GW_NPLANET = 1000;
    }
    if (imetoile.LoadFromFile(("planets"SEPARATOR"etoile.png")))
    {
        spetoile.SetImage(imetoile);
        exists = true;
        return true;
    }
    return false;
}

float GW_BackGround::RandomSizeEtoile(void)
{
    char j = 0;
    float nb = 1.f;
    while (j < 5)
    {
        j++;
        nb *= Random(0.5f, 1.f);
    }
    return nb;
}

void GW_BackGround::Init(void)
{
    if (!exists)
    {
        return;
    }
    GW_ToCenter(spetoile);
}

GW_BackGround::~GW_BackGround(void)
{
    ;
}

void GW_BackGround::PlaneteGenerate(void)
{
    int i = Random(0, 7);
    if (i == 0)
    {
        CUInt32 ID = Random(0, GW_NPLANET-1);
        char str[] = "planets/000.png\0";
        sprintf(str, "planets"SEPARATOR"%d.png", ID);
        Image* ptr = GW_CreateFromFile(str);
        if (ptr != NULL)
        {
            Sprite* spr = new Sprite();
            if (spr != NULL)
            {
                delete(impla);
                delete(sppla);
                sppla = spr;
                impla = ptr;
                sppla->SetImage(*impla);
            }
            else
            {
                delete(ptr);
            }
        }
        s = Random(0.3f, 1.f);
        a = Random(-180.f, 180.f);
        GW_ToCenter(*sppla);
        i = int(impla->GetWidth()*s/2);
        sppla->SetRotation(a);
        sppla->SetScale(s, s);
        x = Random(-i, GW_LARGEUR+i);x=100;
        tor = Random(0.f, 50.f);
        tog = Random(0.f, 50.f);
        tob = Random(0.f, 50.f);
    }
    else
    {
        Image* ptr = new Image(imetoile);
        if (ptr != NULL)
        {
            Sprite* spr = new Sprite();
            if (spr != NULL)
            {
                delete(impla);
                delete(sppla);
                sppla = spr;
                impla = ptr;
                sppla->SetImage(*impla);
            }
            else
            {
                delete(ptr);
            }
        }
        s = 1;
        a = 0;
        x = -45;
    }
    y = Random(0, GW_HAUTEUR);
}

void GW_BackGround::Generate(void)
{
    int i = 0;
    while (i < GW_BGHAUTEUR)
    {
        xTab[i] = Random(0, GW_LARGEUR);
        yTab[i] = (i)*GW_BGVITESSE;
        Size[i] = GW_BackGround::RandomSizeEtoile();
        i++;
    }
    LastID = i-1;
    this->PlaneteGenerate();
}

void GW_BackGround::Display(RenderWindow* App)
{
    if (!isAffiched)
    {
        return;
    }
    App->Clear(GW_BGCOLOR);
    int i = 0;
    while (i < GW_BGHAUTEUR)
    {
        yTab[i] += GW_BGVITESSE/9.f;
        spetoile.SetPosition(xTab[i], yTab[i]);
        spetoile.SetScale(Size[i], Size[i]);
        App->Draw(spetoile);
        i++;
    }
    sppla->SetPosition(x, y);
    App->Draw(*sppla);
    cste++;
    if(cste%9 == 0)
    {
        LastID = (LastID-1+GW_BGHAUTEUR)%GW_BGHAUTEUR;
        xTab[LastID] = Random(0, GW_LARGEUR);
        yTab[LastID] = -GW_ETOILEHEIGHT;
        r = r*0.995 + tor*0.005;
        g = g*0.995 + tog*0.005;
        b = b*0.995 + tob*0.005;
        GW_BGCOLOR.r = r;
        GW_BGCOLOR.g = g;
        GW_BGCOLOR.b = b;
    }
    y++;
    if (y >= GW_HAUTEUR+(1.5*GW_PLANETHEIGHT))
    {
        this->PlaneteGenerate();
        y = SInt16(-1.5*GW_PLANETHEIGHT);
    }
}

void GW_BackGround::Close(void)
{
    if (!exists)
    {
        return;
    }
}
#endif
