#pragma once

#include <string>
#include <iostream>
#include <map>
#include <any>
#include <functional>
#include <list>


#define let auto
#define object  Object()
#define values  Argument_List(LS_VALUES)=
#define key(x)  Argument_List(x,LS_KEY)
#define func(x) Argument_List(x,LS_FUNC)=[]
#define lambda  Argument_List(LS_LAMBDA)=[]
#define nl      std::endl
#define none    NONE
#define ref(x)  &x
#define call(x) Argument_List(x,LS_CALL)

class Object;

enum ListType 
{
    LS_NONE = 0,
    LS_VALUES,
    LS_KEY,
    LS_FUNC,
    LS_LAMBDA,
    LS_CALL
};

std::string num_name();

enum Ar_Type {
    INT = 0,DOUBLE,OBJECT,STRING,BOOLEAN,FUNCTION,LAMBDA,OBJECT_PTR,NONE,CALL
};


class Argument 
{
private:
    Ar_Type _type = NONE;
public:
    Argument();
    virtual ~Argument();
    template<typename T>void set_type(T val);
    Ar_Type get_type();
    void set_type_func(Ar_Type type);
    virtual std::any Downcast() = 0;
};



template<typename T>void Argument::set_type(T val){
    if(typeid(val) == typeid(int)) {
        _type = INT;
    }
    else if (typeid(val) == typeid(double)) {
        _type =DOUBLE;
    }
    else if (typeid(val) == typeid(const char*)) {
        _type =STRING;
    }
    else if (typeid(val) == typeid(bool)) {
        _type =BOOLEAN;
    }
    else if (typeid(val)== typeid(NONE)) {
        _type =NONE;
    }
    else
        _type =OBJECT;
}


template<typename T>
class Value : public Argument {
private:
    T _value;
public:
    Value(T value);
    T get_value() ;
    void set_value(T value);
    virtual std::any Downcast()
    {
        return this;
    }
};

template<typename T> Value<T>::Value(T value) : _value(value){}
template<typename T> T Value<T>::get_value(){return _value;}
template<typename T> void Value<T>::set_value(T value) {_value = value;}


template<typename T>
class Value_Func : public Argument {
private:
    T _value;
public:
    Value_Func(T value);
    T get_value();
    void set_value(T value);
    virtual std::any Downcast() {return this;}
};

template<typename T> Value_Func<T>::Value_Func(T value) : _value(value){}
template<typename T> T Value_Func<T>::get_value(){return _value;}
template<typename T> void Value_Func<T>::set_value(T value) {_value = value;}


class Argument_List{
public:
    
    std::map<std::string,Argument*>args;
    std::string _tmp;
    ListType _type = LS_NONE;
    
    
    Argument_List();
    ~Argument_List();
    Argument_List(std::string key,ListType type);
    Argument_List(ListType type);
    
    
    template<typename T> Argument_List& operator,(T val);
    Argument_List& operator,(Argument_List& val);
    Argument_List& operator=(Argument_List& val);
    template<typename T> Argument_List& operator=(T val);
    Argument_List& operator,(Object* val);
    Argument_List& operator=(Object* val);
    

};

template<typename T>Argument_List& Argument_List::operator,(T val) {
    Argument* atmp = new Value<T>(val);
    atmp->set_type(val);
    if((*this)._type == LS_VALUES) 
    {
        args[num_name()] = atmp;
    }
    return (*this);
}

template<typename T>Argument_List& Argument_List::operator=(T val)
{
    
    if((*this)._type == LS_VALUES) 
    {
        Argument* atmp = new Value<T>(val);
        atmp->set_type(val);
        args[num_name()] = atmp;
    }
    else if((*this)._type == LS_FUNC)
    {
        Argument* atmp = new Value_Func<T>(val);
        atmp->set_type_func(FUNCTION);
        args[_tmp] = atmp;
    }
    else if((*this)._type == LS_LAMBDA) 
    {
        Argument* atmp = new Value_Func<T>(val);
        atmp->set_type_func(LAMBDA);
        args["lambda"] = atmp;
    }
    else 
    {
        Argument* atmp = new Value<T>(val);
        atmp->set_type(val);
        args[_tmp] = atmp;
    }
    return (*this);
}


class Object{
public:
    Argument_List _args;
    Argument_List _args_recieved;
    bool _reciever = false;
    std::string _ToModify;
    Object();
    Object& operator[](Argument_List& args);
    friend std::ostream& operator<<(std::ostream& os, const Object& o);
    Object& operator[](std::string key);
    void operator= (Object& val);
    template<typename T> void operator= (T val);
    void operator= (Object* val);
    void operator<< (const Object &val);
};

template<typename T> void Object::operator=(T val){
    Argument* newval = new Value<T>(val);
    newval->set_type(val);
    if(typeid(val) == typeid(Argument_List)) 
    {
        Argument_List tmp = reinterpret_cast<Argument_List&>(val);
        if(tmp._type == LS_LAMBDA){
            newval->set_type_func(LAMBDA);
        }
    }
    this->_args.args.find(this->_ToModify)->second = newval;
}








