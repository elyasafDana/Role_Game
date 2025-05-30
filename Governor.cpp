//elidana@gmail.com
#include "Governor.h"

#include <iostream>

Governor::Governor():Role(){
    srole="Governor";
}

Governor::~Governor(){

}

bool Governor ::tax(){
    if (!isBanned){
        coins += 3;
        std::cout<<"add 3 int tax"<<endl;
        return true;
    }else{
        cout<<"you are banned cant do this action"<<endl;
        return false;
    }
}
