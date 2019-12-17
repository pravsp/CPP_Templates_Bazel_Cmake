#include "gtest/gtest.h"
#include "../include/uid_pool.h"

using namespace banking_lib_utilities;
using namespace std;
TEST(UIDShould, ReturnRandomInt){
    cerr<<"Instantiating UIDpool"<<endl;    
    UIDPool *u_pool = UIDPool::create_UIDPool("test1", INTEGER);
    //UIDPool *u_pool = new UIDPool(INTEGER);

    cerr<<"Generating first uid"<<endl;
    auto uid1 = u_pool->create_new_uid();
    cerr<<"Generating second uid"<<endl;
    auto uid2 = u_pool->create_new_uid();
    cerr<<"uid1 = "<<uid1<<endl;
    cerr<<"uid2 = "<<uid2<<endl;

    EXPECT_NE(uid1, uid2);
}