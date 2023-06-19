#pragma once
#include "DB/pgback.h"

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
    char* GetAccessMode(EntityId const& e, Resource const& r) const;
    void SetAccessMode(EntityId const& e, Resource const& r);

    inline static auto pgbackend = std::make_shared<PGBackend>();
};

#include "ACL.hpp"