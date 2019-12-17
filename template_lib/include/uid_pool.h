#ifndef UID_POOL_H
#define UID_POOL_H
#include<iostream>
#include<map>
#include<list>

#include "uid_type.h"
using namespace std;

namespace banking_lib_utilities{
    #define DEFAULT_ALPHANUMERIC_UID_LENGTH 10
    
    class UIDPool{
        /*
         * This class is used to generate unique id. The unique id can be
         * integer or alphanumeric.
         */
        list <int64_t> m_allocated_id;
        static map<string, UIDPool*> pools;
        enum uid_type type;
        int length;
        
        
        UIDPool(enum uid_type type);
        public:
        
        bool uid_exists(int64_t uid);
        int64_t create_new_uid();
        bool release_uid(int64_t uid);
        
        int64_t random_uid();
        static UIDPool* create_UIDPool(string pool_name, enum uid_type type);
        static UIDPool* get_uid_pool(string pool_name);
    };
}

#endif //UID_POOL_H