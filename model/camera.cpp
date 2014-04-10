//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        camera.cpp
// PURPOUSE:    Camera component.
//

#include "camera.h"

using namespace model;

Camera::Camera()
{
    setOrthographic ( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );
}

Camera::~Camera()
{
}

void Camera::setOrthographic ( const float& left, const float& right,
                               const float& top, const float& bottom,
                               const float& nearPlane, const float& farPlane )
{
    mType = CAMERA_ORTHOGRAPHIC;
    mOrthographic.left = left;
    mOrthographic.right = right;
    mOrthographic.top = top;
    mOrthographic.bottom = bottom;
    mOrthographic.nearPlane = nearPlane;
    mOrthographic.farPlane = farPlane;
    makeOrthographicMatrix ();
}

void Camera::setPerspective ( const float& fovy, const float& aspect,
                              const float& nearPlane, const float& farPlane )
{
    mType = CAMERA_PERSPECTIVE;
    mPerspective.fovy = fovy;
    mPerspective.aspect = aspect;
    mPerspective.nearPlane = nearPlane;
    mPerspective.farPlane = farPlane;
    makePerspectiveMatrix ();
}

void Camera::setCorners (const f32& left, const f32& right, const f32& top, const f32& bottom)
{
    if ( mType == CAMERA_ORTHOGRAPHIC )
    {
        mOrthographic.left = left;
        mOrthographic.right = right;
        mOrthographic.top = top;
        mOrthographic.bottom = bottom;
        makeOrthographicMatrix ();
    }
}

void Camera::setNearFar (const f32& near, const f32& far)
{
    if ( mType == CAMERA_ORTHOGRAPHIC )
    {
        mOrthographic.nearPlane = near;
        mOrthographic.farPlane = far;
        makeOrthographicMatrix ();
    }
    else
    {
        mPerspective.nearPlane = near;
        mPerspective.farPlane = far;
        makePerspectiveMatrix ();
    }
}

void Camera::setFovy (const f32& fovy)
{
    if ( mType == CAMERA_PERSPECTIVE )
    {
        mPerspective.fovy = fovy;
        makePerspectiveMatrix ();
    }
}

void Camera::setAspect (const f32& aspect)
{
    if ( mType == CAMERA_PERSPECTIVE )
    {
        mPerspective.aspect = aspect;
        makePerspectiveMatrix ();
    }
}

void Camera::makeOrthographicMatrix ()
{
    mProjection = OrthographicMatrix ( mOrthographic.left,
                                       mOrthographic.right,
                                       mOrthographic.top,
                                       mOrthographic.bottom,
                                       mOrthographic.nearPlane,
                                       mOrthographic.farPlane );
}

void Camera::makePerspectiveMatrix ()
{
    mProjection = PerspectiveMatrix ( mPerspective.aspect,
                                      mPerspective.fovy,
                                      mPerspective.nearPlane,
                                      mPerspective.farPlane );
}
