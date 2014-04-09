//
// Copyright © 2014 - Alberto Alonso
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/ 
// for more details.
//
// FILE:        materialFactory.h
// PURPOUSE:    Material factory
//

#pragma once

#include "model/material.h"

namespace renderer {
namespace impl {

class MaterialFactory {
public:
    static model::Material*     getDefault      ();
};

}
}