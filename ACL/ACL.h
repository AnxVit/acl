#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>

struct Entity{
    using type_id = size_t;
    
    Entity():id(++id_g){};
    virtual ~Entity() = default;

    type_id get_id() {return id;}
    
private:
    inline static type_id id_g = 0;
    type_id id;
};

struct Resource{
    virtual ~Resource() = default;
    std::string get_name() const { return m_name;}
    std::string m_name;
};

template<class Entity, class Resource, class AccessMode = bool>
class ACL
{
public:
    using EntityId = typename Entity::type_id;

    void AddEntity(EntityId const& e, Resource const& r, AccessMode m);
    void DelEntity(EntityId const& e);
    AccessMode GetAccessMode(EntityId const& e, Resource const& r) const;
    void SetAccessMode(EntityId const& e, Resource const& r, AccessMode m);

    std::unordered_multimap<EntityId, std::pair<std::string, AccessMode>> base;
};

#include "ACL.hpp"