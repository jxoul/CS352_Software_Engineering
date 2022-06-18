#include "MSGlang.h"

Argument::Argument(){}

Argument::~Argument() = default;

Ar_Type Argument::get_type() 
{
    return _type;
}

void Argument::set_type_func(Ar_Type type) 
{
    _type = type;
}

