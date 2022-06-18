#include "MSGlang.h"

Object::Object(){}
Object& Object::operator[](Argument_List& args) 
{
    _args.args = args.args;
    return (*this);
}

void Object::operator= (Object& val)
{
    Argument* tmp = new Value(val);
    tmp->set_type(val);
    this->_args.args.find(this->_ToModify)->second = tmp;
}

Object& Object::operator[](std::string key)
{
    this->_ToModify = key;
    return *this;
}

void Object::operator= (Object* val) 
{
    Argument* newval = new Value(val);
    newval->set_type_func(OBJECT_PTR);
    this->_args.args.find(this->_ToModify)->second = newval;
}

std::ostream& operator<<(std::ostream& os, const Object& o)
{
    os << "object [ ";
    for(auto i = o._args.args.begin(); i != o._args.args.end();){
        os << "\"" << (*i).first << "\":";
            Ar_Type type = (*i).second->get_type();
            if (type == INT) {
                auto m =dynamic_cast<Value<int>* >((*i).second);
                os << m->get_value();
            }
            else if (type == DOUBLE) {
                auto m =dynamic_cast<Value<double>* >((*i).second);
                os << m->get_value();
            }
            else if (type == STRING) {
                auto m =dynamic_cast<Value<const char*>* >((*i).second);
                os << "\""<< m->get_value()<< "\"";
            }
            else  if (type == BOOLEAN){
                auto m =dynamic_cast<Value<bool>* >((*i).second);
                if(m->get_value())
                    os << "true";
                else
                    os << "false";
            }
            else  if (type == FUNCTION){
                os << "method";
            }
            else  if (type == LAMBDA){
                os << "method";
            }
            else  if (type == NONE){
                os << "none";
            }
            else  if (type == CALL){
              
            }
            else  if (type == OBJECT_PTR){
                auto m =dynamic_cast<Value<Object*>* >((*i).second);
                operator<<(os,*(m->get_value()));
            }
            else {
                auto m =dynamic_cast<Value<Object>* >((*i).second);
                operator<<(os, m->get_value());
            }
        i++;
        if( i != o._args.args.end())
            os << " , ";
    }
    os << " ]";
    return  os;
}

void Object::operator<< (const Object& val)
{
    this->_args_recieved.args = val._args.args;
    auto exist = val._args.args.count("func_to_call");
     if(!exist){
             std::cout << "Message Object must have call()" << std::endl;
              return;
     }
      auto x = val._args.args.find("func_to_call");
      auto tmp =dynamic_cast<Value<std::string>* >((*x).second);
      std::string key = tmp->get_value();


      exist = (*this)._args.args.count(key);
      if(!exist){
             std::cout << "There is no function \"" << key << "\" in the receiver Object" << std::endl;
              return;
     }
    this->_reciever = true;
}

