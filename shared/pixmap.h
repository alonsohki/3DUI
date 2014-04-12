/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        pixmap.h
// PURPOSE:     Pixel maps (pictures).
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include <iostream>
#include "color.h"

class Pixmap
{
public:
                        Pixmap          ();
                        Pixmap          ( unsigned int width, unsigned int height );
                        Pixmap          ( const Pixmap& other );
                        ~Pixmap         ();
private:
    void                cleanupData     ();
    
public:
    Pixmap&             operator=       ( const Pixmap& other );
    bool                operator==      ( const Pixmap& other ) const;
    bool                operator!=      ( const Pixmap& other ) const;
    
    void                create          ( unsigned int width, unsigned int height, const Color* data = 0 );
    void                resample        ( unsigned int newWidth, unsigned int newHeight );
private:
    void                resample_X      ( unsigned int newWidth );
    void                resample_Y      ( unsigned int newHeight );
public:

    bool                load            ( const char* filename );
    bool                load            ( std::istream& stream );
    bool                savePNG         ( const char* filename, unsigned int compressionLevel = 9 ) const;
    bool                savePNG         ( std::ostream& stream, unsigned int compressionLevel = 9 ) const;

    const char*         error           () const { return m_error; }
    const unsigned int& width           () const { return m_width; }
    const unsigned int& height          () const { return m_height; }
    const Color*        pixels          () const { return m_pixels; }
    Color*              pixels          () { return m_pixels; }
    
private:
    bool                loadPNG         ( std::istream& stream );

private:
    unsigned int    m_width;
    unsigned int    m_height;
    Color*          m_pixels;
    mutable char    m_error [ 512 ];
};
