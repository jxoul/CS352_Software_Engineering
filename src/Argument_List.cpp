#include "MSGlang.h"


static unsigned int counter = 0;

Argument_List::Argument_List(){}

Argument_List::~Argument_List(){}

Argument_List::Argument_List(std::string key,ListType type) : _tmp(key),_type(type)
{
    if(_type == LS_CALL) 
    {
        Argument* nval = new Value(key);
        nval->set_type_func(CALL);
        args["func_to_call"] = nval;
    }
}

Argument_List::Argument_List(ListType type) :_type(type)
{
    if(type == LS_VALUES)
        counter = 0;
}

Argument_List& Argument_List::operator,(Argument_List& val)
{
    if(this->_type == LS_CALL) 
    {
        val.args.merge(this->args);
        return val;
    }

    if(this->_type == LS_VALUES) 
    {
        auto node = val.args.extract("lambda");
        #undef key
        node.key() = num_name();
        #define key(x)  Argument_List(x,LS_KEY)
        val.args.insert(std::move(node));
    }

    (*this).args.merge(val.args);

    return (*this);
}

Argument_List& Argument_List::operator=(Argument_List& val)
{
    if(this->_type == LS_VALUES)
        (*this).args[num_name()] = val.args.begin()->second;
    else
        (*this).args[_tmp] = val.args.begin()->second;
    
    return (*this);
}

std::string num_name()
{
    return std::to_string(counter++);
}

Argument_List& Argument_List::operator,(Object* val)
{
    Argument* atmp = new Value(val);
    atmp->set_type_func(OBJECT_PTR);

    if((*this)._type == LS_VALUES) 
    {
        args[num_name()] = atmp;
    }

    return (*this);
}

Argument_List& Argument_List::operator=(Object* val)
{
    Argument* atmp = new Value(val);
    atmp->set_type_func(OBJECT_PTR);
    args[num_name()] = atmp;
    return *this;
}



