#pragma once

#include <string>
#include <vector>

#include "Property.h"
#include "TypeRegister.hpp"


DECLARE_PROPERTY_TYPE( property::Label, property::Label::Size, int )
DECLARE_PROPERTY_TYPE( property::Label, property::Label::Text, std::string )
DECLARE_PROPERTY_TYPE( property::Label, property::Label::Weight, double )

DECLARE_PROPERTY_TYPE( property::List, property::List::Items, std::vector<std::string> )
DECLARE_PROPERTY_TYPE( property::List, property::List::Letter, unsigned char )
