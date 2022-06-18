#include "MSGlang.h"
#include <string>
#include <iostream>


class X{
    public:
    virtual void f (void){std::cout << "X"<<std::endl;}
};

class Y : public X{
    public:
    virtual void f (void){std::cout << "Y"<<std::endl;}
};

class Z : public Y{
    public:
    virtual void f (void){std::cout << "Z"<<std::endl;}
};

void f(X& x, Y* y, Z& z){
    x.X::f();
}

int main() {

    X x;
    Y* y = new Y();
    Z z; 


    f(x,y,z);
    

     let o1 = object[call("pame"),values lambda{},true,"hello",lambda{return 2;}];
     let o2 = object[key("x") = 1, key("y") = lambda{return 1;},func("pame"){return "lala";}];
     let o3 = object[values false , ref(o1)];
     o1["1"] = false;
    
     std::cout << o1 << std::endl;
     std::cout << o2 << std::endl;
     std::cout << o3 << std::endl;
     o2 << o1;
    return 0;
}

