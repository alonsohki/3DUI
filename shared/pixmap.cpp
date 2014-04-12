/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2012
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        pixmap.cpp
// PURPOSE:     Pixel maps (pictures).
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <png.h>
#include "pixmap.h"
#include "util.h"
#include "math/util.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

#define SetError(msg, ...) ( snprintf ( m_error, sizeof(m_error), msg, ## __VA_ARGS__) == 9001 )

Pixmap::Pixmap ()
: m_width ( 0 )
, m_height ( 0 )
, m_pixels ( 0 )
{
    m_error[0] = '\0';
}

Pixmap::Pixmap ( unsigned int width, unsigned int height )
: m_width ( 0 )
, m_height ( 0 )
, m_pixels ( 0 )
{
    create ( width, height );
}

Pixmap::Pixmap ( const Pixmap& other )
: m_width ( 0 )
, m_height ( 0 )
, m_pixels ( 0 )
{
    operator= ( other );
}

Pixmap::~Pixmap ()
{
    cleanupData ();
}

void Pixmap::cleanupData ()
{
    if ( m_pixels != 0 )
        free ( m_pixels );
    m_pixels = 0;
    m_width = 0;
    m_height = 0;
    m_error[0] = '\0';
}

void Pixmap::create ( unsigned int width, unsigned int height, const Color* data )
{
    cleanupData ();
    m_width = width;
    m_height = height;
    m_pixels = (Color *)malloc ( sizeof(Color) * m_width * m_height );
    if ( data != 0 )
        memcpy ( m_pixels, data, sizeof(Color)*m_width*m_height );
}

Pixmap& Pixmap::operator= ( const Pixmap& other )
{
    cleanupData ();
    m_width = other.m_width;
    m_height = other.m_height;
    memcpy ( m_error, other.m_error, sizeof(m_error) );
    m_pixels = (Color *)malloc ( sizeof(Color) * m_width * m_height );
    memcpy ( m_pixels, other.m_pixels, sizeof(Color)*m_width*m_height );
    return *this;
}

bool Pixmap::operator== ( const Pixmap& other ) const
{
    return m_width == other.m_width &&
           m_height == other.m_height &&
           memcmp ( m_pixels, other.m_pixels, sizeof(Color)*m_width*m_height ) == 0;
}

bool Pixmap::operator!= ( const Pixmap& other ) const
{
    return !operator== ( other );
}

bool Pixmap::load ( const char* filename )
{
    std::ifstream fp;
    
    fp.open ( filename, std::ios::in | std::ios::binary );
    if ( fp.is_open() == false )
    {
        return SetError("Unable to open the file '%s'", filename);
    }
    return load ( fp );
}

bool Pixmap::load ( std::istream& stream )
{
    cleanupData ();
    
    // Check for the file type to load
    char header [ 8 ];
    stream.read ( header, 8 );
    if ( stream.gcount() != 8 )
        return SetError("Invalid file");
    
    if ( !png_sig_cmp ((png_byte*)header, 0, 8) )
        return loadPNG ( stream );
    else
        return SetError ( "Unsupported file type" );
}

static void read_from_png ( png_structp png_ptr, png_bytep data, png_size_t length )
{
    std::istream* stream = (std::istream *)png_get_io_ptr ( png_ptr );
    stream->read ( (char *)data, length );
}

static void write_to_png ( png_structp png_ptr, png_bytep data, png_size_t length )
{
    std::ostream* stream = (std::ostream *)png_get_io_ptr ( png_ptr );
    stream->write ( (char*)data, length );
}

static void flush_png ( png_structp png_ptr )
{
    std::ostream* stream = (std::ostream *)png_get_io_ptr ( png_ptr );
    stream->flush();
}

bool Pixmap::loadPNG ( std::istream& stream )
{
    png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING,
                                                  0, 0, 0 );
    if ( !png_ptr )
        return SetError ( "Unable to create the PNG context" );
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if ( !info_ptr )
    {
        png_destroy_read_struct(&png_ptr, 0, 0);
        return SetError ( "Unable to create the PNG info struct" );
    }
    
    png_infop end_info = png_create_info_struct(png_ptr);
    if ( !end_info )
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0 );
        return SetError ( "Unable to create the PNG end info struct" );
    }
    
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return SetError ( "An error occured while reading the PNG file" );
    }
    
    png_set_sig_bytes ( png_ptr, 8 );
    png_set_read_fn ( png_ptr, &stream, read_from_png );
    png_read_png ( png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_GRAY_TO_RGB, 0 );
    
    //m_width = (unsigned int)info_ptr->width;
    //m_height = (unsigned int)info_ptr->height;
    int bit_depth;
    int color_type;
    png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)&m_width, (png_uint_32*)&m_height, &bit_depth, &color_type, 0, 0, 0);
    
    m_pixels = (Color *)malloc ( sizeof(Color) * m_width * m_height );
    unsigned int* pixels = (unsigned int *)m_pixels;
    png_bytep* row_pointers = png_get_rows( png_ptr, info_ptr );
    
    if ( color_type == PNG_COLOR_TYPE_RGB )
    {
        for ( unsigned int h = 0; h < m_height; ++h )
        {
            png_bytep row = row_pointers[h];

            for ( unsigned int w = 0; w < m_width; ++w )
            {
                pixels [ w + h*m_width ] = *(unsigned int *)&row[0] | 0xFF000000;
                row += 3;
            }
        }
    }
    else if ( color_type == PNG_COLOR_TYPE_RGB_ALPHA )
    {
        unsigned int* pixels = (unsigned int *)&m_pixels[0];
        for ( unsigned int h = 0; h < m_height; ++h )
        {
            png_bytep row = row_pointers[h];
            memcpy ( &pixels[h*m_width], &row[0], 4*m_width );
        }
    }
    
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info );
    
    return true;
}

bool Pixmap::savePNG ( const char* filename, unsigned int compressionLevel ) const
{
    std::ofstream fp;
    fp.open ( filename, std::ios::out | std::ios::binary );
    if ( !fp.is_open() )
        return SetError ( "Unable to open the file for writing" );
    return savePNG ( fp );
}

bool Pixmap::savePNG ( std::ostream& stream, unsigned int compressionLevel ) const
{
    png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if ( !png_ptr )
       return SetError ( "Error creating the PNG write struct" );
    
    png_byte** row_pointers = (png_byte **)png_malloc ( png_ptr, sizeof(png_byte*)*m_height );
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_free ( png_ptr, row_pointers );
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        return SetError ( "Error creating the PNG write info struct" );
    }
    
    if (setjmp(png_jmpbuf(png_ptr)))
    {
       png_free ( png_ptr, row_pointers );
       png_destroy_write_struct(&png_ptr, &info_ptr);
       return SetError ( "An error occured when writing the PNG data" );
    }
    
    png_set_IHDR(png_ptr,
                 info_ptr,
                 m_width,
                 m_height,
                 8,
                 PNG_COLOR_TYPE_RGB_ALPHA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    
    png_set_write_fn ( png_ptr, &stream, write_to_png, flush_png );
    png_set_compression_level( png_ptr, compressionLevel );
    
    for ( unsigned int i = 0; i < m_height; ++i )
        row_pointers[i] = (png_byte *)&m_pixels[i*m_width];
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, detectBigEndian() ? PNG_TRANSFORM_BGR|PNG_TRANSFORM_SWAP_ALPHA : PNG_TRANSFORM_IDENTITY, 0);     
    png_destroy_write_struct(&png_ptr, &info_ptr);

    png_free ( png_ptr, row_pointers );
    
    return true;
}

void Pixmap::resample ( unsigned int newWidth, unsigned int newHeight )
{
    if ( m_pixels != 0 )
    {
        if ( newWidth != m_width )
            resample_X ( newWidth );
        if ( newHeight != m_height )
            resample_Y ( newHeight );
    }
}

void Pixmap::resample_X ( unsigned int newWidth )
{
    Color* newPixels = (Color *)malloc ( sizeof(Color) * newWidth * m_height );
    
    if ( newWidth < m_width )
    {
        float ratio = m_width / (float)newWidth;
        for ( unsigned int h = 0; h < m_height; ++h )
        {
            unsigned int w = 0;
            for ( float x = 0.0f; w < newWidth; x += ratio, ++w )
            {
                float from = x;
                float to = std::min((float)m_width, x + ratio);

                unsigned int absoluteValue = (unsigned int)floor(from);
                float fractionaryPart = from-absoluteValue;
                float pixelAccum [ 4 ] = { 0.0f, 0.0f, 0.0f, 0.0f };

                if ( fractionaryPart > 0.000001f )
                {
                    float factor = 1.0f - fractionaryPart;
                    Color& color = m_pixels [ m_width*h + absoluteValue ];
                    pixelAccum[0] += ( color.r() / 255.0f ) * factor;
                    pixelAccum[1] += ( color.g() / 255.0f ) * factor;
                    pixelAccum[2] += ( color.b() / 255.0f ) * factor;
                    pixelAccum[3] += ( color.a() / 255.0f ) * factor;
                    from = static_cast<float>(absoluteValue + 1);
                }
                from = floor(from);
                
                while ( to-from > 1.0f )
                {
                    Color& color = m_pixels [ m_width*h + (unsigned int)from ];
                    pixelAccum[0] += color.r() / 255.0f;
                    pixelAccum[1] += color.g() / 255.0f;
                    pixelAccum[2] += color.b() / 255.0f;
                    pixelAccum[3] += color.a() / 255.0f;
                    ++from;
                }
                
                if ( fabs(to-from) > 0.000001f )
                {
                    float factor = fabs(to-from);
                    Color& color = m_pixels [ m_width*h + (unsigned int)from ];
                    pixelAccum[0] += (color.r() / 255.0f) * factor;
                    pixelAccum[1] += (color.g() / 255.0f) * factor;
                    pixelAccum[2] += (color.b() / 255.0f) * factor;
                    pixelAccum[3] += (color.a() / 255.0f) * factor;
                }
                
                newPixels [ newWidth*h + w ] = Color ( static_cast<unsigned char>(pixelAccum[0] / ratio * 255.0f),
                                                       static_cast<unsigned char>(pixelAccum[1] / ratio * 255.0f),
                                                       static_cast<unsigned char>(pixelAccum[2] / ratio * 255.0f),
                                                       static_cast<unsigned char>(pixelAccum[3] / ratio * 255.0f) );
            }
        }
    }
    else if ( newWidth > m_width )
    {
        float ratio = m_width / (float)newWidth;
        for ( unsigned int h = 0; h < m_height; ++h )
        {
            for ( unsigned int w = 0; w < newWidth; ++w )
            {
                unsigned int left = (unsigned int)floor(w * ratio);
                unsigned int right = std::min(m_width-1, left+1);
                unsigned int leftPrev = left > 0 ? left-1 : 0;
                unsigned int rightNext = std::min(m_width-1, right+1);
                
                Color& l = m_pixels [ h*m_width + left ];
                Color& r = m_pixels [ h*m_width + right ];
                Color& lp = m_pixels [ h*m_width + leftPrev ];
                Color& rn = m_pixels [ h*m_width + rightNext ];
                
                float colorValues [ 4 ][ 4 ] =
                {
                    { l.r() / 255.0f,  l.g() / 255.0f,  l.b() / 255.0f,  l.a() / 255.0f },
                    { r.r() / 255.0f,  r.g() / 255.0f,  r.b() / 255.0f,  r.a() / 255.0f },
                    { lp.r() / 255.0f, lp.g() / 255.0f, lp.b() / 255.0f, lp.a() / 255.0f },
                    { rn.r() / 255.0f, rn.g() / 255.0f, rn.b() / 255.0f, rn.a() / 255.0f }
                };
                float tangents [ 2 ][ 4 ] =
                {
                    { colorValues[1][0]-colorValues[2][0], colorValues[1][1]-colorValues[2][1], colorValues[1][2]-colorValues[2][2], colorValues[1][3]-colorValues[2][3] },
                    { colorValues[3][0]-colorValues[0][0], colorValues[3][1]-colorValues[0][1], colorValues[3][2]-colorValues[0][2], colorValues[3][3]-colorValues[0][3] }
                };
                
                float interpolatedValues [ 4 ];
                float alpha = w*ratio;
                alpha = alpha - floor(alpha);
                
                interpolatedValues[0] = clamp(0.0f, cubic_interpolate(colorValues[0][0], tangents[0][0], alpha, colorValues[1][0], tangents[1][0]), 1.0f);
                interpolatedValues[1] = clamp(0.0f, cubic_interpolate(colorValues[0][1], tangents[0][1], alpha, colorValues[1][1], tangents[1][1]), 1.0f);
                interpolatedValues[2] = clamp(0.0f, cubic_interpolate(colorValues[0][2], tangents[0][2], alpha, colorValues[1][2], tangents[1][2]), 1.0f);
                interpolatedValues[3] = clamp(0.0f, cubic_interpolate(colorValues[0][3], tangents[0][3], alpha, colorValues[1][3], tangents[1][3]), 1.0f);
                newPixels [ h*newWidth + w ] = Color ( static_cast<unsigned char>(interpolatedValues[0] * 255.0f),
                                                       static_cast<unsigned char>(interpolatedValues[1] * 255.0f),
                                                       static_cast<unsigned char>(interpolatedValues[2] * 255.0f),
                                                       static_cast<unsigned char>(interpolatedValues[3] * 255.0f) );
            }
        }
    }
    
    free ( m_pixels );
    m_pixels = newPixels;
    m_width = newWidth;
}

void Pixmap::resample_Y ( unsigned int newHeight )
{
    Color* newPixels = (Color *)malloc ( sizeof(Color) * m_width * newHeight );
    
    if ( newHeight < m_height )
    {
        float ratio = m_height / (float)newHeight;
        for ( unsigned int w = 0; w < m_width; ++w )
        {
            unsigned int h = 0;
            for ( float y = 0.0f; h < newHeight; y += ratio, ++h )
            {
                float from = y;
                float to = std::min((float)m_height, y + ratio);

                unsigned int absoluteValue = (unsigned int)floor(from);
                float fractionaryPart = from-absoluteValue;
                float pixelAccum [ 4 ] = { 0.0f, 0.0f, 0.0f, 0.0f };

                if ( fractionaryPart > 0.000001f )
                {
                    float factor = 1.0f - fractionaryPart;
                    Color& color = m_pixels [ m_width*absoluteValue + w ];
                    pixelAccum[0] += ( color.r() / 255.0f ) * factor;
                    pixelAccum[1] += ( color.g() / 255.0f ) * factor;
                    pixelAccum[2] += ( color.b() / 255.0f ) * factor;
                    pixelAccum[3] += ( color.a() / 255.0f ) * factor;
                    from = static_cast<float>(absoluteValue + 1);
                }
                from = floor(from);
                
                while ( to-from > 1.0f )
                {
                    Color& color = m_pixels [ m_width*(unsigned int)from + w ];
                    pixelAccum[0] += color.r() / 255.0f;
                    pixelAccum[1] += color.g() / 255.0f;
                    pixelAccum[2] += color.b() / 255.0f;
                    pixelAccum[3] += color.a() / 255.0f;
                    ++from;
                }
                
                if ( fabs(to-from) > 0.000001f )
                {
                    float factor = fabs(to-from);
                    Color& color = m_pixels [ m_width*(unsigned int)from + w ];
                    pixelAccum[0] += (color.r() / 255.0f) * factor;
                    pixelAccum[1] += (color.g() / 255.0f) * factor;
                    pixelAccum[2] += (color.b() / 255.0f) * factor;
                    pixelAccum[3] += (color.a() / 255.0f) * factor;
                }
                
                newPixels [ m_width*h + w ] = Color ( static_cast<unsigned char>(pixelAccum[0] / ratio * 255.0f),
                                                      static_cast<unsigned char>(pixelAccum[1] / ratio * 255.0f),
                                                      static_cast<unsigned char>(pixelAccum[2] / ratio * 255.0f),
                                                      static_cast<unsigned char>(pixelAccum[3] / ratio * 255.0f) );
            }
        }
    }
    else if ( newHeight > m_height )
    {
        float ratio = m_height / (float)newHeight;
        for ( unsigned int w = 0; w < m_width; ++w )
        {
            for ( unsigned int h = 0; h < newHeight; ++h )
            {
                unsigned int up = (unsigned int)floor(h * ratio);
                unsigned int down = std::min(m_height-1, up+1);
                unsigned int upPrev = up > 0 ? up-1 : 0;
                unsigned int downNext = std::min(m_height-1, down+1);
                
                Color& u = m_pixels [ up*m_width + w ];
                Color& d = m_pixels [ down*m_width + w ];
                Color& u_ = m_pixels [ upPrev*m_width + w ];
                Color& dn = m_pixels [ downNext*m_width + w ];
                
                float colorValues [ 4 ][ 4 ] =
                {
                    { u.r() / 255.0f,  u.g() / 255.0f,  u.b() / 255.0f,  u.a() / 255.0f },
                    { d.r() / 255.0f,  d.g() / 255.0f,  d.b() / 255.0f,  d.a() / 255.0f },
                    { u_.r() / 255.0f, u_.g() / 255.0f, u_.b() / 255.0f, u_.a() / 255.0f },
                    { dn.r() / 255.0f, dn.g() / 255.0f, dn.b() / 255.0f, dn.a() / 255.0f }
                };
                float tangents [ 2 ][ 4 ] =
                {
                    { colorValues[1][0]-colorValues[2][0], colorValues[1][1]-colorValues[2][1], colorValues[1][2]-colorValues[2][2], colorValues[1][3]-colorValues[2][3] },
                    { colorValues[3][0]-colorValues[0][0], colorValues[3][1]-colorValues[0][1], colorValues[3][2]-colorValues[0][2], colorValues[3][3]-colorValues[0][3] }
                };
                
                float interpolatedValues [ 4 ];
                float alpha = h*ratio;
                alpha = alpha - floor(alpha);
                
                interpolatedValues[0] = clamp(0.0f, cubic_interpolate(colorValues[0][0], tangents[0][0], alpha, colorValues[1][0], tangents[1][0]), 1.0f);
                interpolatedValues[1] = clamp(0.0f, cubic_interpolate(colorValues[0][1], tangents[0][1], alpha, colorValues[1][1], tangents[1][1]), 1.0f);
                interpolatedValues[2] = clamp(0.0f, cubic_interpolate(colorValues[0][2], tangents[0][2], alpha, colorValues[1][2], tangents[1][2]), 1.0f);
                interpolatedValues[3] = clamp(0.0f, cubic_interpolate(colorValues[0][3], tangents[0][3], alpha, colorValues[1][3], tangents[1][3]), 1.0f);
                newPixels [ h*m_width + w ] = Color ( static_cast<unsigned char>(interpolatedValues[0] * 255.0f),
                                                      static_cast<unsigned char>(interpolatedValues[1] * 255.0f),
                                                      static_cast<unsigned char>(interpolatedValues[2] * 255.0f),
                                                      static_cast<unsigned char>(interpolatedValues[3] * 255.0f) );
            }
        }
    }
    
    free ( m_pixels );
    m_pixels = newPixels;
    m_height = newHeight;
}
