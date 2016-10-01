#ifndef GW_COLLISIONNABLEADMIN_GETPOLYGON_C
#define GW_COLLISIONNABLEADMIN_GETPOLYGON_C

#include <SFML/Graphics/Shape.hpp>

#include "../h/GW_CollisionnableIncluser.hpp"

const Shape* GW_Ennemi_A::GetPolygon(void) const
{
    return &GW_Ennemi_A::polygon;
}

const Shape* GW_Ennemi_B::GetPolygon(void) const
{
    return &GW_Ennemi_B::polygon;
}

const Shape* GW_Ennemi_C::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Ennemi_D::GetPolygon(void) const
{
    return &Carre;
}

const Shape* GW_Ennemi_E::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Ennemi_F::GetPolygon(void) const
{
    return &GW_Ennemi_F::polygon;
}

const Shape* GW_Ennemi_G::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Ennemi_H::GetPolygon(void) const
{
    if (isOpen == CC)
    {
        return &GW_Ennemi_H::polygon[1];
    }
    else
    {
        return &GW_Ennemi_H::polygon[0];
    }
}

const Shape* GW_Ennemi_I::GetPolygon(void) const
{
    return &GW_Ennemi_I::polygon;
}

const Shape* GW_Ennemi_J::GetPolygon(void) const
{
    return &GW_Collisionnable::Octogon;
}

const Shape* GW_Ennemi_K::GetPolygon(void) const
{
    return &Carre;
}

const Shape* GW_Ennemi_L::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Joueur::GetPolygon(void) const
{
    return &GW_Joueur::polygon;
}

const Shape* GW_Tir_A::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Tir_B::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Tir_C::GetPolygon(void) const
{
    return &Carre;
}

const Shape* GW_Tir_Kube::GetPolygon(void) const
{
    return &Carre;
}

const Shape* GW_Tir_X::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Tir_Y::GetPolygon(void) const
{
    return &Octogon;
}

const Shape* GW_Tir_Z::GetPolygon(void) const
{
    return &Octogon;
}

#endif
