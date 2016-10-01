#ifndef GW_COLLISIONNABLEADMIN_DRAW_C
#define GW_COLLISIONNABLEADMIN_DRAW_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

#include "../h/GW_Palette.hpp"

void GW_Ennemi_A::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITEA[int(id)], this);
}

void GW_Ennemi_B::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITEB[int(id)], this);
}

void GW_Ennemi_C::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITEC[int(id)], this);
}

void GW_Ennemi_D::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITED[int(id)][0], x, y, -angle*180/M_PI+a);
    GW_Collisionnable::ClassicDraw(App, &SPRITED[int(id)][1], x, y, -angle*180/M_PI-a);
}

void GW_Ennemi_E::Draw(RenderWindow* App)
{
    int A = id/3, B = id%3;
    GW_Collisionnable::ClassicDraw(App, &SPRITEE[A][B], x, y, angle);
}

void GW_Ennemi_F::Draw(RenderWindow* App)
{
    SPRITEF[(int)id].SetPosition(x-11.5, y+9);
    App->Draw(SPRITEF[(int)id]);
    SPRITEF[(int)id].SetPosition(x+9.5, y+9);
    App->Draw(SPRITEF[(int)id]);
    Sprite* spr[3] = {&SPRITEE[(int)id][0], &SPRITEE[(int)id][1], &SPRITEE[(int)id][2]};
    GW_Collisionnable::ClassicDraw(App, spr[2], x, y, av*90);
    GW_Collisionnable::ClassicDraw(App, spr[0], x-12, y-16, av*180);
    GW_Collisionnable::ClassicDraw(App, spr[0], x+12, y-11, -av*180);
    GW_Collisionnable::ClassicDraw(App, spr[1], x-17, y+2, -av*360);
    GW_Collisionnable::ClassicDraw(App, spr[1], x+17, y+8, av*360);
}

void GW_Ennemi_G::Draw(RenderWindow* App)
{
    GW_Collisionnable::ClassicDraw(App, &SPRITEG[int(id)], this);
}

void GW_Ennemi_H::Draw(RenderWindow* App)
{
    float norme = 25;
    GW_Collisionnable::ClassicDraw(App, &SPRITEH[int(id)][0], this);

    float an = GW_FloatModulo(angle + 2.498091545+0.05, 2*M_PI);
    SPRITEH[(int)id][1].FlipY(false);
    SPRITEH[(int)id][1].SetCenter(10, 15);
    GW_Collisionnable::ClassicDraw(App, &SPRITEH[int(id)][1], x + norme*GW_Cos(an), y + norme*GW_Sin(an), -(angle+a_aile)*180/M_PI);

    an = GW_FloatModulo(angle + 3.785093762-0.05, 2*M_PI);
    SPRITEH[(int)id][1].FlipY(true);
    SPRITEH[(int)id][1].SetCenter(10, 8.5);
    GW_Collisionnable::ClassicDraw(App, &SPRITEH[int(id)][1], x + norme*GW_Cos(an), y + norme*GW_Sin(an), -(angle-a_aile)*180/M_PI);
}

void GW_Ennemi_I::Draw(RenderWindow* App)
{
    Sprite* spr[2] = {&SPRITEI[int(id)][0], &SPRITEI[int(id)][int(idDraw)]};
    if (isTeleport)
    {
        float A = angle+M_PI/2;
        if (A > 2*M_PI)
        {
            A -= 2*M_PI;
        }
        float dxmax = 1.5*GW_Cos(A)*SPRITEI[0][0].GetSize().x;
        float dymax = 1.5*GW_Sin(A)*SPRITEI[0][0].GetSize().y;
        float dx = dxmax*alpha*alpha;
        float dy = dymax*alpha*alpha;
        float a = -angle*180/M_PI;
        spr[0]->SetRotation(a);
        spr[1]->SetRotation(a);
        this->TeleporDraw(App, spr[0], 128-alpha*128, x, dx, y, dy);
        this->TeleporDraw(App, spr[1], 128-alpha*128, x, dx, y, dy);

        dx = (1-alpha);
        dy = (1-alpha);
        dx *= dx*dxmax;
        dy *= dy*dymax;
        this->TeleporDraw(App, spr[0], alpha*128, nx, dx, ny, dy);
        this->TeleporDraw(App, spr[1], alpha*128, nx, dx, ny, dy);
    }
    else
    {
        spr[0]->SetAlpha(255);
        spr[1]->SetAlpha(255);
        GW_Collisionnable::ClassicDraw(App, spr[0], this);
        GW_Collisionnable::ClassicDraw(App, spr[1], this);
    }
}

void GW_Ennemi_J::Draw(RenderWindow* App)
{
    cfloat scale = size/SIZE_BASE, nsize = scale*SizeNoyau;
    float a;
    Sprite* spr = &SPRITEJ[int(id)][int(idDraw)];
    if (idDraw == 0)
    {
        a = 225-angle*180/M_PI;
    }
    else
    {
        a = -angle*180/M_PI;
    }
    spr->SetScale(scale, scale);
    GW_Collisionnable::ClassicDraw(App, spr, x, y, a);
    NOYAU.SetScale(scale, scale);
    GW_Collisionnable::ClassicDraw(App, &NOYAU, nx*nsize+x, ny*nsize+y, angle*180/M_PI);
    NOYAU.SetPosition(nx2*nsize+x, ny2*nsize+y);
    App->Draw(NOYAU);
}

void GW_Ennemi_K::Draw(RenderWindow* App)
{
    SPRITIKUBE.SetScale(3*SizeKube, 3*SizeKube);
    SPRITIKUBE.SetColor(Color(0,0,0,255));
    GW_Collisionnable::ClassicDraw(App, &SPRITIKUBE, this);
    SPRITIKUBE.SetScale(SizeKube-2, SizeKube-2);
    int i = 0, j = 0;
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            SPRITIKUBE.SetColor(*this->GetColor(0, i, j));
            SPRITIKUBE.SetPosition(x + (j-1)*SizeKube, y + (i-1)*SizeKube);
            App->Draw(SPRITIKUBE);
            j++;
        }
        i++;
    }
    if (idrotate != -1)
    {
        float L = GW_Cos(a), l = GW_Sin(a);
        if (idrotate/5 == 1)
        {
            float ech = l;
            l = L;
            L = ech;
        }
        int p = 0;
        i = 0;
        float px = 0;
        if (a > M_PI/2)
        {
            a = -1;
            return;
        }
        SPRITIKUBE.SetColor(Color(0,0,0,255));
        switch (idrotate%5)
        {
            case 0:
                SPRITIKUBE.SetScale(3*SizeKube, 3*SizeKube);
                SPRITIKUBE.SetPosition(x, y);
                App->Draw(SPRITIKUBE);
                if (idrotate == 5)
                {
                    SPRITIKUBE.SetRotation(90-a*180/M_PI);
                }
                else
                {
                    SPRITIKUBE.SetRotation(-90+a*180/M_PI);
                }
                App->Draw(SPRITIKUBE);
                SPRITIKUBE.SetScale(15, 15);
                i = 0, j = 0;
                while (i < 3)
                {
                    j = 0;
                    while (j < 3)
                    {
                        SPRITIKUBE.SetColor(*this->GetColor(0, i, j));
                        SPRITIKUBE.SetCenter(0.5 - (j-1)*17/15.f, 0.5 - (i-1)*17/15.f);
                        App->Draw(SPRITIKUBE);
                        j++;
                    }
                    i++;
                }
                SPRITIKUBE.SetRotation(0);
                break;
            case 1:
                p = 2;
            case 3:
                SPRITIKUBE.SetScale(3*SizeKube*(L+l), SizeKube);
                SPRITIKUBE.SetPosition(x, y + SizeKube*(p-1));
                App->Draw(SPRITIKUBE);
                SPRITIKUBE.SetCenter(0, 0.5);
                SPRITIKUBE.SetScale((SizeKube-2)*L, SizeKube-2);
                px = x - 3*SizeKube*(L+l)/2.f;
                while (i < 3)
                {
                    SPRITIKUBE.SetX(px);
                    SPRITIKUBE.SetColor(*inrotate[i]);
                    SPRITIKUBE.SetAlpha(255*(L/(l+L)));
                    px += L*SizeKube;
                    App->Draw(SPRITIKUBE);
                    i++;
                }
                SPRITIKUBE.SetScaleX((SizeKube-2)*l);
                while (i < 6)
                {
                    SPRITIKUBE.SetX(px);
                    SPRITIKUBE.SetColor(*inrotate[i]);
                    SPRITIKUBE.SetAlpha(255*(l/(l+L)));
                    px += l*SizeKube;
                    App->Draw(SPRITIKUBE);
                    i++;
                }
                break;
            case 2:
                p = 2;
            case 4:
                SPRITIKUBE.SetScale(SizeKube, 3*SizeKube*(L+l));
                SPRITIKUBE.SetPosition(x + SizeKube*(1-p), y);
                App->Draw(SPRITIKUBE);
                SPRITIKUBE.SetCenter(0.5, 0);
                SPRITIKUBE.SetScale(SizeKube-2, (SizeKube-2)*L);
                px = y - 3*SizeKube*(L+l)/2.f;
                while (i < 3)
                {
                    SPRITIKUBE.SetY(px);
                    SPRITIKUBE.SetColor(*inrotate[i]);
                    SPRITIKUBE.SetAlpha(255*(L/(l+L)));
                    px += L*SizeKube;
                    App->Draw(SPRITIKUBE);
                    i++;
                }
                SPRITIKUBE.SetScaleY((SizeKube-2)*l);
                while (i < 6)
                {
                    SPRITIKUBE.SetY(px);
                    SPRITIKUBE.SetColor(*inrotate[i]);
                    SPRITIKUBE.SetAlpha(255*(l/(l+L)));
                    App->Draw(SPRITIKUBE);
                    px += l*SizeKube;
                    i++;
                }
                break;
            default:
                break;
        }
        SPRITIKUBE.SetCenter(0.5, 0.5);
    }
}

void GW_Ennemi_L::Draw(RenderWindow* App){;}

void GW_Joueur::Draw(RenderWindow* App)
{
    if (this->IsDead())
    {
        return;
    }
    SPRITEJOUEUR[3].SetPosition(x, y);
    App->Draw(SPRITEJOUEUR[3]);
    IDReacteur = (IDReacteur + 1)%6;
    GW_Collisionnable::ClassicDraw(App, &SPRITEJOUEUR[int(IDReacteur/2)], this);
    LifeBar.SetPosition(x-SPRITEJOUEUR[3].GetSize().x/2.f, y);
    LifeBar.SetColor(Color(0, 0, 0, 255));
    LifeBar.SetScaleX(SPRITEJOUEUR[3].GetSize().x);
    App->Draw(LifeBar);
    if (PV > GW_Joueur::PV_BASE/2)
    {
        LifeBar.SetColor(Color((Uint8)(510*(1-PV/GW_Joueur::PV_BASE)),255,0,255));
    }
    else
    {
        LifeBar.SetColor(Color(255,(Uint8)(510*(PV/GW_Joueur::PV_BASE)),0,255));
    }
    LifeBar.SetPosition(x-SPRITEJOUEUR[3].GetSize().x/2.f, y);
    LifeBar.SetScaleX(SPRITEJOUEUR[3].GetSize().x*PV/GW_Joueur::PV_BASE);
    App->Draw(LifeBar);/**/
}

void GW_Tir_A::Draw(RenderWindow* App)
{
    float scale = 0.25 + 0.075*Level;
    SPRITIR.SetScale(scale, scale);
    GW_Collisionnable::ClassicDraw(App, &SPRITIR, this);
}

void GW_Tir_B::Draw(RenderWindow* App)
{
    if (end)
    {
        s = t-1;
        s *= s;
        cfloat S = 15*(1.01-s)*r/size;
        SPRITIR[5].SetScale(S, S);
        SPRITIR[5].SetAlpha((0.5-t)*255);
        GW_Collisionnable::ClassicDraw(App, &SPRITIR[5], this);
    }
    else
    {
        cfloat S = scaleX*s*2/size;
        SPRITIR[ID].SetScale(S, S);
        GW_Collisionnable::ClassicDraw(App, &SPRITIR[ID], this);
    }
}

void GW_Tir_C::Draw(RenderWindow* App)
{
    id = UInt32((id + int(5*t/0.05)%5)%5);
    SPRITIR[id].SetScale(s, s);
    if (ID)
    {
        SPRITIR[id].SetAlpha((0.25-t*t)*255*4);
    }
    else
    {
        SPRITIR[id].SetAlpha(255);
    }
    GW_Collisionnable::ClassicDraw(App, &SPRITIR[id], this);
}

void GW_Tir_Kube::Draw(RenderWindow* App)
{
    float L = GW_Cos(a), l = GW_Sin(a), lx = SizeKube*GW_Cos(angle), ly = SizeKube*GW_Sin(angle);
    SPRITIRKUBE.SetScale((L+l)*SizeKube, SizeKube);
    SPRITIRKUBE.SetColor(Color(0,0,0,255));
    GW_Collisionnable::ClassicDraw(App, &SPRITIRKUBE, this);
    SPRITIRKUBE.SetColor(*c);
    SPRITIRKUBE.SetScale(L*(SizeKube-2), (SizeKube-2));
    SPRITIRKUBE.SetPosition(x+(l/2)*lx, y+(l/2)*ly);
    SPRITIRKUBE.SetAlpha(255*L);
    App->Draw(SPRITIRKUBE);
    SPRITIRKUBE.SetScale(l*(SizeKube-2), (SizeKube-2));
    SPRITIRKUBE.SetPosition(x-(L/2)*lx, y-(L/2)*ly);
    SPRITIRKUBE.SetAlpha(255*l);
    App->Draw(SPRITIRKUBE);
}

void GW_Tir_X::Draw(RenderWindow* App)
{
    int i = 0;
    SPRITIR.SetPosition(x, y);
    SPRITIR.SetRotation(-a*180/M_PI);
    SPRITIR.SetPointColor(0, *c);
    while (i < 2)
    {
        SPRITIR.SetPointPosition(1, -SPRITIR.GetPointPosition(1).x, 0);
        SPRITIR.SetPointPosition(2, -SPRITIR.GetPointPosition(2).x, 0.4);
        App->Draw(SPRITIR);
        App->Draw(SPRITIR);
        SPRITIR.Rotate(180);
        App->Draw(SPRITIR);
        App->Draw(SPRITIR);
        i++;
    }

}

void GW_Tir_Y::Draw(RenderWindow* App)
{
    cfloat bidulechose = scaleX/200, A = a*sens;
    switch(ID)
    {
        case 0:
            this->BDraw(App, &SPRITIR[0], A, 255, bidulechose);
            this->BDraw(App, &SPRITIR[1], A, id*255.f, bidulechose);
            break;
        case 1:
            this->BDraw(App, &SPRITIR[1], A, 255, bidulechose);
            this->BDraw(App, &SPRITIR[2], A, id*255.f, bidulechose);
            break;
        case 2:
            this->BDraw(App, &SPRITIR[2], A, 255, bidulechose);
            this->BDraw(App, &SPRITIR[0], A, id*255.f, bidulechose);
            break;
        default:
            break;
    }
}

void GW_Tir_Z::Draw(RenderWindow* App)
{
    float scale = this->GetRadius();
    ID = !ID;
    if (ID)
    {
        OMBRE[id].SetScale(scale, scale);
        OMBRE[id].SetPosition(x, y);
        App->Draw(OMBRE[id]);
        //GW_Collisionnable::ClassicDraw(App, &OMBRE[id], this);
    }
    else
    {
        SPRITIR.SetScale(scale, scale);
        SPRITIR.SetPosition(x, y);
        App->Draw(SPRITIR);
        //GW_Collisionnable::ClassicDraw(App, &SPRITIR, this);
    }
}

#endif
