/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        color.h
// PURPOSE:     Colors.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include "endianness.h"

class Color
{
public:
    static const Color WHITE, BLACK, RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN;

private:
    typedef unsigned char u8;
    typedef unsigned int u32;

private:
    union
    {
        u8  m_members[4];
        u32 m_value;
    };
    
    
public:
    Color () {}

    Color ( u8 R, u8 G, u8 B, u8 A )
    {
        Set ( R, G, B, A );
    }
    
    void Set ( u8 R, u8 G, u8 B, u8 A )
    {
        m_value = R << 24 | G << 16 | B << 8 | A;
    }
    
    // Operators
public:
    bool operator== ( const Color& other ) const
    {
        return m_value == other.m_value;
    }
    bool operator!= ( const Color& other ) const
    {
        return !operator== ( other );
    }
    
    // Accessors
public:
    u32 abgr () const
    {
        return ( ( m_value >> 24 ) & 0x000000FF )
             | ( ( m_value >> 8  ) & 0x0000FF00 )
             | ( ( m_value << 8  ) & 0x00FF0000 )
             | ( ( m_value << 24 ) & 0xFF000000 );
    }
    u32 argb () const
    {
        return ( ( m_value >> 8  ) & 0x00FFFFFF )
             | ( ( m_value << 24 ) & 0xFF000000 );
    }

    const u8& r() const { return m_members[detectBigEndian() ? 0 : 3]; }
    const u8& g() const { return m_members[detectBigEndian() ? 1 : 2]; }
    const u8& b() const { return m_members[detectBigEndian() ? 2 : 1]; }
    const u8& a() const { return m_members[detectBigEndian() ? 3 : 0]; }
    const u32& rgba() const { return m_value; }
    const u32& value() const { return m_value; }
    
    u8& r() { return m_members[detectBigEndian() ? 0 : 3]; }
    u8& g() { return m_members[detectBigEndian() ? 1 : 2]; }
    u8& b() { return m_members[detectBigEndian() ? 2 : 1]; }
    u8& a() { return m_members[detectBigEndian() ? 3 : 0]; }
    u32& rgba() { return m_value; }
    u32& value() { return m_value; }
};
