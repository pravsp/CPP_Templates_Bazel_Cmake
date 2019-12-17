#include<iostream>
//#include<stdlib>
#include<map>
#include<iterator>
#include <sstream>
#include "../include/uid_pool.h"
#include "../include/uid_type.h"

using namespace std;

namespace banking_lib_utilities{
    
    map<string, UIDPool*> UIDPool::pools;

    UIDPool::UIDPool(enum uid_type type)
    :m_allocated_id()
    {
        cout<<"new UIDPool instance"<<endl;
        this->type = type;
        this->length = DEFAULT_ALPHANUMERIC_UID_LENGTH;
    }
    
    
    UIDPool* UIDPool::create_UIDPool(string pool_name, enum uid_type type){
        cout<<"create UIDPool for pool_name: "<<pool_name<<endl;
        UIDPool* pool = UIDPool::get_uid_pool(pool_name); 
        if ( pool == NULL) {
            pool = new UIDPool(type);
            UIDPool::pools.insert(make_pair(pool_name, pool));    
        }
        return pool;
    }
  
    
    UIDPool* UIDPool::get_uid_pool(string pool_name){
        auto itr = UIDPool::pools.find(pool_name);
        if (itr == UIDPool::pools.end()){
            return NULL;
        }
        return itr->second;
    }
   
    
    bool UIDPool::uid_exists(int64_t uid){
        cout<<"inside uid exists"<<endl;
        auto itr = find(this->m_allocated_id.begin(),
                        this->m_allocated_id.end(),
                        uid);
        if (itr == this->m_allocated_id.end()) {
            return false;
        }
        cout<<"uid already exists"<<endl;
        return true;

    }
   
    int64_t UIDPool::create_new_uid(){
        int64_t uid;
        cout<<"inside create new uid"<<endl;
        do {
            uid = this->random_uid();
        }while(this->uid_exists(uid));
        cout<<"uid created: "<<uid<<endl;
        this->m_allocated_id.push_back(uid);
        return uid;
        
    }
    
    bool UIDPool::release_uid(int64_t uid){
        if (this->uid_exists(uid)){
            this->m_allocated_id.remove(uid);
            return true;
        } else {
            cout<<"The entry didnt exists"<<endl;
            return false;
        }

    }

    int64_t UIDPool::random_uid(){
        auto randchar_int = []() -> char
        {
            const char charset[] =
            "0123456789";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        auto randchar_str = []() -> char
        {
            const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        
        string str(length,0);
        
        
        if (this->type == INTEGER){
            generate_n( str.begin(), length, randchar_int);
        }else {
            generate_n( str.begin(), length, randchar_str);
        }
        cout <<"Randon id generated ="<<str<<endl;
        stringstream convert(str);
        int64_t value;
        convert >> value;
        return value;
    }
    
    
}