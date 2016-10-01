#ifndef GW_COLLISIONNABLEADMIN_C
#define GW_COLLISIONNABLEADMIN_C

#include "../h/GW_GraphicsIncluser.hpp"

#include "../h/GW_CollisionnableAdmin.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

#include "../h/GW_VolatileAdmin.hpp"
#include "../h/GW_VolatileIncluser.hpp"

static bool exists;

extern int nbennemis;
extern int probennemi[GW_Collisionnable::NBENN];

bool GW_CollisionnableAdmin::AddEnnemies(GW_JeuData* Data)
{
    bool truc = true;
    //printf("%d\n", Data->Unites.Size());
    if (Data->Unites.Size() < nbennemis)
    {//printf("%d", GW_Collisionnable::EM-GW_Collisionnable::EA);
        int bidule = Random(0, probennemi[GW_Collisionnable::EM-GW_Collisionnable::EA]-1);
        //bidule=probennemi[GW_Collisionnable::EM-GW_Collisionnable::EA]-1;
        UInt32 i = GW_Collisionnable::EM-GW_Collisionnable::EA;
        while (i > 0  && bidule < probennemi[i-1])
        {
            i--;
        }
        if (bidule >= probennemi[GW_Collisionnable::EM-GW_Collisionnable::EA])
        {
            i = GW_Collisionnable::EM-GW_Collisionnable::EA;
        }
        //printf("%d %d %d\n", i, bidule, probennemi[GW_Collisionnable::EM-GW_Collisionnable::EA-1]);
        switch(i)
        {
            case GW_Collisionnable::EA-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_A(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EB-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_B(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EC-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_C(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::ED-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_D(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EE-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_E(
                                            Random(0, 2)+
                                            3/**/*(Random(0, 10)/10)
                                            ));
                break;
            case GW_Collisionnable::EF-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_F(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EG-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_G(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EH-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_H(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EI-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_I(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EJ-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_J(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EK-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_K(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));
                break;
            case GW_Collisionnable::EL-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_L());//printf("%d %d\n", bidule, i);
                break;
            case GW_Collisionnable::EM-GW_Collisionnable::EA:
                truc = Data->Unites.Add(new GW_Ennemi_M(/*/false && /**/(/*/true || /**/Random(0, 10)<1)));//printf("%d m\n", bidule);
                break;
            default:
                break;
        }
    }
    return truc;
}

bool GW_CollisionnableAdmin::GW_Ennemi_GenericDead(GW_Ennemi* unite, GW_JeuData* truc, RenderWindow* App)
{
    ////truc->VolatiList->Add(GW_Fleur::Create(unite->GetX(), unite->GetY()));
    truc->VolatiList->Add(GW_BoomAnim::Create(unite->GetX(), unite->GetY()));
    truc->VolatiList->Add(GW_Number::RandomCreate(unite->GetX(), unite->GetY(), unite->Points()));
    return true;
}

bool GW_CollisionnableAdmin::GW_Tir_GenericDead(GW_Tir* unite, GW_JeuData* truc, RenderWindow* App)
{
    ////truc->VolatiList->Add(GW_Fleur::Create(unite->GetX(), unite->GetY()));
    truc->VolatiList->Add(GW_ExploTir::Create(unite->GetX(), unite->GetY(), unite->GetRadius()/2, unite->GetAngle()));
    return true;
}

bool GW_CollisionnableAdmin::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    if (GW_Joueur::Init(
        GW_Ennemi_A::Init(
        GW_Ennemi_B::Init(
        GW_Ennemi_C::Init(
        GW_Ennemi_D::Init(
        GW_Ennemi_E::Init(
        GW_Ennemi_F::Init(
        GW_Ennemi_G::Init(
        GW_Ennemi_H::Init(
        GW_Ennemi_I::Init(
        GW_Ennemi_J::Init(
        GW_Ennemi_K::Init(
        GW_Ennemi_L::Init(
        GW_Ennemi_M::Init(
        GW_Tir_A::Init(
        GW_Tir_B::Init(
        GW_Tir_C::Init(
        GW_Tir_Kube::Init(
        GW_Tir_W::Init(
        GW_Tir_Y::Init(
        GW_Tir_X::Init(
        GW_Tir_Z::Init(true)))))))))))))))))))))))
    {
        exists = true;
        return true;
    }
    return false;
}

void GW_CollisionnableAdmin::Close(void)
{
    if (!exists)
    {
        return;
    }
    GW_Joueur::Close();
    GW_Ennemi_A::Close();
    GW_Ennemi_B::Close();
    GW_Ennemi_C::Close();
    GW_Ennemi_D::Close();
    GW_Ennemi_E::Close();
    GW_Ennemi_F::Close();
    GW_Ennemi_G::Close();
    GW_Ennemi_H::Close();
    GW_Ennemi_I::Close();
    GW_Ennemi_J::Close();
    GW_Ennemi_K::Close();
    GW_Ennemi_L::Close();
    GW_Ennemi_M::Close();
    GW_Tir_A::Close();
    GW_Tir_B::Close();
    GW_Tir_C::Close();
    GW_Tir_Kube::Close();
    GW_Tir_W::Close();
    GW_Tir_X::Close();
    GW_Tir_Y::Close();
    GW_Tir_Z::Close();
    exists = false;
}

#endif
