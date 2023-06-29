#pragma once

#include "ACL.h"


template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::AddEntity(EntityId const& e, Resource const& r, AccessMode m){
    if(base.contains(e)){
        throw std::runtime_error("The entity already exists");
    }
    else{
        base.emplace(e, std::make_pair(r.get_name(), m));
    }
}

template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::DelEntity(EntityId const& e){
    if(base.contains(e)){
        auto [first, last] = base.equal_range(e);
        base.erase(first, last);
    }
    else{
        throw std::runtime_error("The entity doesn't exists.\n");
    }
}

template<class Entity, class Resource, class AccessMode>
AccessMode ACL<Entity, Resource, AccessMode>::GetAccessMode(EntityId const& e, Resource const& r) const {
    std::string name = r.get_name();
    auto [first, last] = base.equal_range(e);
    for(auto it = first; it != last; ++it){
        if(it->second.first == name)
            return it->second.second;
    }
    throw std::runtime_error("The point access doesn't exist.\n");
}

template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::SetAccessMode(EntityId const& e, Resource const& r, AccessMode m){
    if(base.contains(e)){
        std::string name = r.get_name();
        auto [first, last] = base.equal_range(e);
        for(auto it = first; it != last; ++it){
            if(it->second.first == name){
                it->second.second = m;
            }
        }
    }
    else{
        throw std::runtime_error("Tht entity doesn't exist.\n");
    }
}