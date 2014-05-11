/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        util.h
// PURPOSE:     Mathematical utilities.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include <cmath>
#include "platform.h"

namespace {

    const f32 kPi = 3.141592f;
    const f32 k2Pi = kPi * 2.0f;
    const f32 kPiOver2 = kPi / 2.0f;
    const f32 kOverPi = 1.0f / kPi;
    const f32 k1Over2Pi = 1.0f / k2Pi;

    //------------------------------------------------------------------------------
    // Transform radians to degrees
    inline f32 rad2deg(const f32 angle)
    {
        return angle * 180.0f / kPi;
    }

    //------------------------------------------------------------------------------
    // Transform degrees to radians
    inline f32 deg2rad(const f32 angle)
    {
        return angle * kPi / 180;
    }

    //------------------------------------------------------------------------------
    // Calculate simultaneously the sin and cos of a given angle
    inline void sinCos(f32* pSin, f32* pCos, f32 angle)
    {
        *pSin = sin(angle);
        *pCos = cos(angle);
    }

    //------------------------------------------------------------------------------
    // Wrap an angle in the range -pi...pi by adding the correct
    // multiple of 2 pi
    inline f32 wrapPi(f32 angle)
    {
        angle += kPi;
        angle -= floor(angle * k1Over2Pi) * k2Pi;
        angle -= kPi;
        return angle;
    }

    //------------------------------------------------------------------------------
    // Clamp a value to a range
    template<typename T>
    inline T clamp(const T& min, const T& value, const T& max) {
        return (value < min) ? min : ((value > max) ? max : value);
    }

    //------------------------------------------------------------------------------
    // Linear interpolation
    template<typename T>
    inline T lerp(const T& min, float delta, const T& max) {
        return min + (max - min) * delta;
    }

    template<typename T>
    inline float unlerp(const T& min, const T& value, const T& max) {
        return (value - min) / (float)(max - min);
    }

    //------------------------------------------------------------------------------
    // Cubic interpolation
    template < typename T >
    static inline T cubic_interpolate ( T from, T tangentFrom, float alpha, T to, T tangentTo )
    {
        float alpha2 = alpha*alpha;
        float alpha3 = alpha2*alpha;
        return (2*alpha3 - 3*alpha2 + 1.0f)*from + (alpha3 - 2*alpha2 + alpha)*tangentFrom
             + (-2*alpha3 + 3*alpha2)*to + (alpha3 - alpha2)*tangentTo;
    }


    template<typename T>
    inline T saturate(const T& value) {
        return value < 0 ? 0 : (value > 1 ? 1 : value);
    }
}
