//elidana@gmail.com
#include "Baron.h"
#include <iostream>
using namespace std;
Baron:: Baron() :Role() {
    
    srole="Baron";}

Baron:: ~Baron(){}

bool Baron:: invest() {
    
    coins+=3;
    return true;
}

void Baron::putSanction(){
    isBanned=true;
    coins++;
}
