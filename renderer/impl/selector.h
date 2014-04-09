//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        impl/selector.h
// PURPOUSE:    Selector of the renderer implementation.
//

#pragma once

#define USE_OPENGL3

#if defined(USE_OPENGL3)
#   include "opengl3/opengl3.h"
#endif
