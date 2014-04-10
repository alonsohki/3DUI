//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        camera.h
// PURPOUSE:    Camera component.
//

#pragma once

#include "math/matrix.h"

namespace model {

class Camera {
public:
    enum CameraType
    {
        CAMERA_PERSPECTIVE,
        CAMERA_ORTHOGRAPHIC
    };
                        Camera          ();
                        ~Camera         ();
    
    void                setOrthographic ( const float& left, const float& right,
                                          const float& top,  const float& bottom,
                                          const float& near, const float& far );
    void                setPerspective  ( const float& fovy, const f32& aspect,
                                          const float& nearPlane, const float& farPlane );
    
    void                setCorners      ( const float& left, const float& right,
                                          const float& top,  const float& bottom );
    void                setNearFar      ( const float& nearPlane, const float& farPlane );
    void                setFovy         ( const float& fovy );
    void                setAspect       ( const float& aspect );
    
    const Matrix&       getProjection   () const { return mProjection; }

private:
    void                makeOrthographicMatrix  ();
    void                makePerspectiveMatrix   ();
    
private:
    Matrix      mProjection;
    CameraType  mType;

    struct
    {
        float left;
        float right;
        float top;
        float bottom;
        float nearPlane;
        float farPlane;
    } mOrthographic;
    
    struct
    {
        float fovy;
        float aspect;
        float nearPlane;
        float farPlane;
    } mPerspective;
};

}
