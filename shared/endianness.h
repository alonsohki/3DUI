/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        endianness.h
// PURPOSE:     Endianness detection.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

namespace {
    inline bool detectBigEndian()
    {
        static union { const unsigned short w; const unsigned char v[2]; } const u = { 1 };
        return (u.v[0] == 0);
    }
}
