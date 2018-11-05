#pragma once

#include "TypeRegister.hpp"


namespace property {


enum class Demo
{
    Id,
};


}

DECLARE_PROPERTY_TYPE( property::Demo, property::Demo::Id, int )
