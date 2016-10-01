#ifndef GW_COLLISIONNABLEADMIN_GETPOLYGON_C
#define GW_COLLISIONNABLEADMIN_GETPOLYGON_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

#include "../h/GW_KeySettings.hpp"

void GW_Collisionnable::ClassicDraw(RenderWindow* App, Drawable* spr, GW_Collisionnable* obj)
{
    spr->SetPosition(obj->x, obj->y);
    spr->SetRotation(-(obj->angle)*180/M_PI);
    App->Draw(*spr);
}

void GW_Collisionnable::ClassicDraw(RenderWindow* App, Drawable* spr, cfloat x, cfloat y, cfloat angle)
{
    spr->SetPosition(x, y);
    spr->SetRotation(angle);
    App->Draw(*spr);
}

void GW_Ennemi_H::AddTir(GW_JeuData* truc, cfloat precis) const
{
    float arg = GW_FloatModulo(GW_Ennemi_H::polygon[1].GetPointPosition(1).y+angle, 2*M_PI), nor = GW_Ennemi_H::polygon[1].GetPointPosition(1).x;
    float X = x + nor*GW_Cos(arg), Y = y + nor*GW_Sin(arg);
    float dir = GW_Angle(X, truc->Joueur->GetX(), Y, truc->Joueur->GetY());
    truc->Tirs_Ennemi.Add(new GW_Tir_X(id+3, X, Y, GW_RandomEcart(dir, precis)));

    arg = GW_FloatModulo(GW_Ennemi_H::polygon[1].GetPointPosition(2).y+angle, 2*M_PI);
    nor = GW_Ennemi_H::polygon[1].GetPointPosition(2).x;
    X = x + nor*GW_Cos(arg);
    Y = y + nor*GW_Sin(arg);
    dir = GW_Angle(X, truc->Joueur->GetX(), Y, truc->Joueur->GetY());
    truc->Tirs_Ennemi.Add(new GW_Tir_X(id+3, X, Y, GW_RandomEcart(dir, precis)));
}

void GW_Ennemi_I::TeleporDraw(RenderWindow* App, Sprite* spr, cfloat a, cfloat X, cfloat dx, cfloat Y, cfloat dy)
{
    spr->SetAlpha(a);
    spr->SetPosition(X + dx, Y + dy);
    App->Draw(*spr);
    spr->SetPosition(X - dx, Y - dy);
    App->Draw(*spr);
}

void GW_Joueur::SetEvent(Event* event, GW_JeuData* truc)
{//printf("SetEvent avant: %d\n", Arme[TA]);
    bool ghr;
    switch(event->Type)
    {
        case Event::KeyReleased:
            ghr = false;
            break;
        case Event::KeyPressed:
            ghr = true;
            break;
        default:
            return;
            break;
    }
    if (event->Key.Code == Settings->GetIDKey(GW_KeySettings::Up))
    {
        Key[GW_KeySettings::Up] = ghr;
    }
    else if (event->Key.Code == Settings->GetIDKey(GW_KeySettings::Down))
    {
        Key[GW_KeySettings::Down] = ghr;
    }
    else if (event->Key.Code == Settings->GetIDKey(GW_KeySettings::Left))
    {
        Key[GW_KeySettings::Left] = ghr;
    }
    else if (event->Key.Code == Settings->GetIDKey(GW_KeySettings::Right))
    {
        Key[GW_KeySettings::Right] = ghr;
    }
    else if (event->Key.Code == Settings->GetIDKey(GW_KeySettings::Fire))
    {
        Key[GW_KeySettings::Fire] = ghr;
    }
    this->Actualise();//printf("SetEvent apres: %d\n", Arme[TA]);
}

void GW_Tir_Y::BDraw(RenderWindow* App, Sprite* spr, cfloat A, cfloat I, cfloat S)
{
    spr->SetAlpha(I);
    spr->SetScale(S, S);
    spr->SetRotation(A);//0.06
    spr->SetPosition(x, y);
    App->Draw(*spr);
}

#endif
