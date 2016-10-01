#ifndef GW_ENNEMI_RUBIKUBE_C
#define GW_ENNEMI_RUBIKUBE_C

#include <SFML/Graphics/Color.hpp>
#include <cmath>

#include "../h/GW_Ennemi_K.hpp"
#include "../h/GW_Palette.hpp"
#include "../h/GW_Tir_Kube.hpp"
#include "../h/GW_BoomAnim.hpp"
#include "../h/GW_VolatileAdmin.hpp"
#include "../h/GW_JeuData.hpp"

#define GW_NAMECLASS GW_Ennemi_K

bool GW_NAMECLASS::IsCollisionnable(void) const
{
    return (idrotate%5 != 0);
}

GW_NAMECLASS::GW_NAMECLASS(cbool IsBoost) : id(IsBoost)
{
    GW_Ennemi::AddResistances(this, 0);
    type = EK;
    t = 0;
    int i = 0, j = 0, k = 0;
    angle = 0;
    scaleX = 3*SizeKube/2.f;
    scaleY = scaleX;
    dmax = 40;
    idrotate = -1;
    nbdead = 0;
    Time = Random(0.f, 1.f);
    if (rand()&1)
    {
        x = -3*SizeKube/2;
        vx = VITESSE;
    }
    else
    {
        x = GW_LARGEUR + 3*SizeKube/2;
        vx = -VITESSE;
    }
    a = 0;
    vy = 0;
    y = 2*SizeKube;
    toPos = Random(2*SizeKube, GW_LARGEUR - 2*SizeKube);
    Palette = new GW_Palette();
    this->SetColor(IsBoost);
    i = 0;
    j = 0;
    k = 0;
    PV[1][1][1] = PV_BASE*(id+1);
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            k = 0;
            while (k < 3)
            {
                PV[i][j][k] = PV[1][1][1];
                k++;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < 6)
    {
        j = 0;
        while (j < 3)
        {
            k = 0;
            while (k < 3)
            {
                Face[i][j][k] = Palette->GetID(i);
                k++;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < 40)
    {
        this->Rotate(Random(0, 599)/100, rand()&1);
        i++;
    }
}

bool GW_NAMECLASS::IsDead(void) const
{
    return nbdead >= 13;
}

int GW_NAMECLASS::Degats(GW_JeuData* truc, GW_Tir* tir)
{
    if (tir->IsDead() || (Type(tir) == TB && tir->GetEnd()))
    {
        return 0;
    }
    float dx = tir->GetX()-x+SizeKube*3/2.f, dy = tir->GetY()-y+SizeKube*3/2.f, r = tir->GetRadius();
    int i = 0, j = 0;
    while (j < 3 && !(dx > -r + j*SizeKube && dx < SizeKube*(j+1) + r))
    {
        j++;
    }
    while (i < 3 && !(dy > -r + i*SizeKube && dy < SizeKube*(i+1) + r))
    {
        i++;
    }
    if (idrotate != -1)
    {
        char copy = idrotate%5;
        if ((copy & 1) == 1)
        {
            if (3-copy == i)
            {
                return 0;
            }
        }
        else
        {
            if (copy-2 == j)
            {
                return 0;
            }
        }
    }
    float vie = this->GetPV(i, j, 0);
    if (vie < 0)
    {
        return 0;
    }
    this->SetPV(i, j, 0, vie - tir->Power());
    if (vie > 0 && this->GetPV(i, j, 0) <= 0)
    {
        nbdead = this->KubesDead();
        truc->VolatiList->Add(GW_BoomAnim::Create(x+(j-1)*SizeKube, y+(i-1)*SizeKube));
    }
    tir->End();
    if (this->IsDead())
    {
        return this->Points();
    }
    else
    {
        return 0;
    }
}

int GW_NAMECLASS::Points(void) const
{
    return 5000*(4*id+1);
}

int GW_NAMECLASS::KubesDead(void) const
{
    int i = 0, j = 0, k = 0, nb = 0;
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            k = 0;
            while (k < 3)
            {
                if (PV[i][j][k] <= 0)
                {
                    nb++;
                }
                k++;
            }
            j++;
        }
        i++;
    }
    return nb;
}

void GW_NAMECLASS::Action(GW_JeuData* truc, cfloat dt, bool lim)
{
    Time += dt;
    t += dt;
    if (a == -1)
    {
        a = 0.000001;
        char copy = idrotate%5;
        char p = 1;
        switch(copy)
        {
            case 0:
                if (idrotate == 5)
                {
                    p = -1;
                }
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x-SizeKube, y-p*SizeKube, M_PI, *this->GetColor(0, 1-p, 0)));
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x+SizeKube, y+p*SizeKube, 0, *this->GetColor(0, 1+p, 2)));
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x+p*SizeKube, y-SizeKube, 3*M_PI/2, *this->GetColor(0, 0, 1+p)));
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x-p*SizeKube, y+SizeKube, M_PI/2, *this->GetColor(0, 2, 1-p)));
                break;
            case 1:
                p = -1;
            case 3:
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x+SizeKube, y-p*SizeKube, 0, *this->GetColor(0, 1-p, 2)));
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x-SizeKube, y-p*SizeKube, M_PI, *this->GetColor(0, 1-p, 0)));
                break;
            case 4:
                p = -1;
            case 2:
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x-p*SizeKube, y-SizeKube, 3*M_PI/2, *this->GetColor(0, 0, 1-p)));
                truc->Tirs_Ennemi.Add(new GW_Tir_Kube(1+id, x-p*SizeKube, y+SizeKube, M_PI/2, *this->GetColor(0, 2, 1-p)));
                break;
            default:
                break;
        }
        idrotate = -1;
    }
    else if (idrotate == -1)
    {
        ;
    }
    else
    {
        a += dt*3*M_PI/2;
    }
    if ((id && Time > TIMETIR/2) || (!id && Time > TIMETIR))
    {
        //nbdead=13;
        Time -= TIMETIR/(1+id);
        idrotate = Random(0, 999)/100;
        int q = (idrotate/5)*3;
        this->SetBande(q);
        this->Rotate(idrotate%5, idrotate>4);
        this->SetBande(3-q);
    }
    x += vx*dt;
    y += vy*dt;
    if (vy == 0)
    {
        if (t < 180)
        {
            this->ChangeDir(&x, &vx, &y, &vy, GW_HAUTEUR/2);
        }
    }
    else
    {
        this->ChangeDir(&y, &vy, &x, &vx, GW_LARGEUR);
    }
}

void GW_NAMECLASS::SetBande(CSInt32 q)
{
    int p = 2;
    switch(idrotate%5)
    {
        case 1:
            p = 0;
        case 3:
            p = 2-p;
            inrotate[q] = this->GetColor(0, p, 0);
            inrotate[q+1] = this->GetColor(0, p, 1);
            inrotate[q+2] = this->GetColor(0, p, 2);
            break;
        case 2:
            p = 0;
        case 4:
            inrotate[q] = this->GetColor(0, 0, p);
            inrotate[q+1] = this->GetColor(0, 1, p);
            inrotate[q+2] = this->GetColor(0, 2, p);
            break;
        default:
            break;
    }
}

void GW_NAMECLASS::ChangeDir(float* i, float* vi, float* k, float* vk, CSInt32 d)
{
    if ((*i > toPos && *vi > 0) || (*i < toPos && *vi < 0))
    {
        *vi = 0;
        *i = toPos;
        toPos = Random(2*SizeKube, d - 2*SizeKube);
        if (toPos > *k)
        {
            *vk = VITESSE;
        }
        else
        {
            *vk = -VITESSE;
        }
    }
}

void GW_NAMECLASS::rotateface(CSInt32 i, cbool dir)
{
    const Color* face;
    bool Dir = dir;
    if (i == 3 || i == 4 || i == 0)
    {
        Dir = !Dir;
    }
    if (Dir)
    {
        face = Face[i][0][1];
        Face[i][0][1] = Face[i][1][2];
        Face[i][1][2] = Face[i][2][1];
        Face[i][2][1] = Face[i][1][0];
        Face[i][1][0] = face;
        face = Face[i][0][0];
        Face[i][0][0] = Face[i][0][2];
        Face[i][0][2] = Face[i][2][2];
        Face[i][2][2] = Face[i][2][0];
        Face[i][2][0] = face;
    }
    else
    {
        face = Face[i][0][1];
        Face[i][0][1] = Face[i][1][0];
        Face[i][1][0] = Face[i][2][1];
        Face[i][2][1] = Face[i][1][2];
        Face[i][1][2] = face;
        face = Face[i][0][0];
        Face[i][0][0] = Face[i][2][0];
        Face[i][2][0] = Face[i][2][2];
        Face[i][2][2] = Face[i][0][2];
        Face[i][0][2] = face;
    }
}

void GW_NAMECLASS::Rotate(CSInt8 T, cbool sens) //carrement degueu horrible
{
    const Color* face;
    int i = 0;
    int X = 0;
    switch(T)
    {
        case 0:
            if (sens)
            {
                while (i < 3)
                {
                    face = Face[1][0][i];
                    Face[1][0][i] = Face[4][2][2-i];
                    Face[4][2][2-i] = Face[3][2][2-i];
                    Face[3][2][2-i] = Face[2][0][i];
                    Face[2][0][i] = face;
                    i++;
                }
                this->PermutePV(0,1,0, 1,2,0, 2,1,0, 1,0,0);
            }
            else
            {
                while (i < 3)
                {
                    face = Face[1][0][i];
                    Face[1][0][i] = Face[2][0][i];
                    Face[2][0][i] = Face[3][2][2-i];
                    Face[3][2][2-i] = Face[4][2][2-i];
                    Face[4][2][2-i] = face;
                    i++;
                }
                this->PermutePV(0,1,0, 1,0,0, 2,1,0, 1,2,0);
            }
            this->RepareCoin(0,2,0, 2,2,0, 2,0,0, 0,0,0);
            break;
        case 1:
            X = 2;
        case 3:
            if (sens)
            {
                while (i < 3)
                {
                    face = Face[0][X][i];
                    Face[0][X][i] = Face[4][2-i][X];
                    Face[4][2-i][X] = Face[5][2-X][2-i];
                    Face[5][2-X][2-i] = Face[2][2-i][X];
                    Face[2][2-i][X] = face;
                    i++;
                }
                this->PermutePV(X,0,1, X,1,2, X,2,1, X,1,0);
            }
            else
            {
                while (i < 3)
                {
                    face = Face[0][X][i];
                    Face[0][X][i] = Face[2][2-i][X];
                    Face[2][2-i][X] = Face[5][2-X][2-i];
                    Face[5][2-X][2-i] = Face[4][2-i][X];
                    Face[4][2-i][X] = face;
                    i++;
                }
                this->PermutePV(X,0,1, X,1,0, X,2,1, X,1,2);
            }
            this->RepareCoin(X,0,2, X,2,2, X,2,0, X,0,0);
            break;
        case 4:
            X = 2;
        case 2:
            if (sens)
            {
                while (i < 3)
                {
                    face = Face[0][i][X];
                    Face[0][i][X] = Face[1][i][X];
                    Face[1][i][X] = Face[5][i][X];
                    Face[5][i][X] = Face[3][i][X];
                    Face[3][i][X] = face;
                    i++;
                }
                this->PermutePV(0,X,1, 1,X,2, 2,X,1, 1,X,0);
            }
            else
            {
                while (i < 3)
                {
                    face = Face[0][i][X];
                    Face[0][i][X] = Face[3][i][X];
                    Face[3][i][X] = Face[5][i][X];
                    Face[5][i][X] = Face[1][i][X];
                    Face[1][i][X] = face;
                    i++;
                }
                this->PermutePV(0,X,1, 1,X,0, 2,X,1, 1,X,2);
            }
            this->RepareCoin(0,X,2, 2,X,2, 2,X,0, 0,X,0);
            break;
        default:
            return;
            break;
    }
    this->rotateface((int)T, sens);
}

void GW_NAMECLASS::PermutePV(CSInt32 a1, CSInt32 b1, CSInt32 c1, CSInt32 a2, CSInt32 b2, CSInt32 c2, CSInt32 a3, CSInt32 b3, CSInt32 c3, CSInt32 a4, CSInt32 b4, CSInt32 c4)
{
    cfloat vie = PV[a1][b1][c1];
    PV[a1][b1][c1] = PV[a2][b2][c2];
    PV[a2][b2][c2] = PV[a3][b3][c3];
    PV[a3][b3][c3] = PV[a4][b4][c4];
    PV[a4][b4][c4] = vie;
}

void GW_NAMECLASS::RepareCoin(CSInt32 a1, CSInt32 b1, CSInt32 c1, CSInt32 a2, CSInt32 b2, CSInt32 c2, CSInt32 a3, CSInt32 b3, CSInt32 c3, CSInt32 a4, CSInt32 b4, CSInt32 c4)
{
    PV[a1][b1][c1] = PV[1][1][1];
    PV[a2][b2][c2] = PV[1][1][1];
    PV[a3][b3][c3] = PV[1][1][1];
    PV[a4][b4][c4] = PV[1][1][1];
}

void GW_NAMECLASS::SetColor(bool isboost)
{
    int i = 0;
    if (isboost)
    {
        char r = (char)Random(0, 255), g = (char)Random(0, 255), b = (char)Random(0, 255);
        while (i < 6)
        {
            Palette->SetID(new Color(r, g, b, 255), i);
            i++;
        }
    }
    else
    {
        while (i < 6)
        {
            Palette->SetID(new Color(Random(0, 255), Random(0, 255), Random(0, 255), 255), i);
            i++;
        }
    }
}

GW_NAMECLASS::~GW_NAMECLASS(void)
{
    delete(Palette);
}

const Color* GW_NAMECLASS::GetColor(CSInt32 X, CSInt32 Y, CSInt32 z) const
{
    return Face[X][Y][z];
}

float GW_NAMECLASS::GetPV(CSInt32 X, CSInt32 Y, CSInt32 z) const
{
    return PV[X][Y][z];
}

void GW_NAMECLASS::SetPV(CSInt32 X, CSInt32 Y, CSInt32 z, cfloat pv)
{
    PV[X][Y][z] = pv;
}

#undef GW_NAMECLASS
#endif
