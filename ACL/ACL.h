#pragma once

#include <unordered_map>
#include <utility>

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
    virtual std::string get_name() const = 0;
};

template<class Entity, class Resource, class AccessMode = bool>
class ACL
{
public:
    using EntityId = typename Entity::type_id;

    void AddEntity(EntityId const& e, Resource const& r, AccessMode m);
    void DelEntity(EntityId const& e);
    AccessMode GetAccessMode(EntityId const& e, Resource const& r) const;
    void SetAccessMode(EntityId const& e, Resource const& r);
    std::vector<Resource> GetResources(EntityId const& e);

    std::unordered_map<std::pair<EntityId, Resource>, AccessMode> base;
};

#include "ACL.hpp"