#pragma once

#include "ACL.h"

void check(std::shared_ptr<PGConnection> conn){
    while ( auto res_ = PQgetResult(conn->connection().get())) {
       if(PQresultStatus(res_) == PGRES_FATAL_ERROR)
            std::cout << PQresultErrorMessage(res_) <<std::endl;
       PQclear(res_);
    }
}

template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::AddEntity(EntityId const& e, Resource const& r, AccessMode m){
    auto conn = pgbackend->connection();

    const char* params[3];
    params[0] = std::to_string(e).c_str();
    params[1] = r.get_name().c_str();
    params[2] = m.c_str();

    const char* query1 =
        "INSERT INTO Entity (id) "
        " VALUES ($1);";
    const char* query2 =
        "INSERT INTO Resources (resour) "
        " VALUES ($1)"
        " ON CONFLICT (resour) "
        " DO NOTHING;";
    const char* query3 =
        "INSERT INTO Acl (id_en, res, access) "
        " VALUES ($1, $2, $3);";

    PQsendQueryParams(conn->connection().get(), query1, 1, NULL, params,
                        NULL, NULL, 0);

    check(conn);

    PQsendQueryParams(conn->connection().get(), query2, 1, NULL, params + 1,
                        NULL, NULL, 0);

    check(conn);

    PQsendQueryParams(conn->connection().get(), query3, 3, NULL, params,
                        NULL, NULL, 0);

    check(conn);
}

template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::DelEntity(EntityId const& e){
    auto conn = pgbackend->connection();
    const char* param[1];
    param[0] = std::to_string(e).c_str();
    const char* del = "DELETE FROM entity WHERE id = $1;";
    PQsendQueryParams(conn->connection().get(), del, 1, NULL, param,
                        NULL, NULL, 0);

    check(conn);
}

template<class Entity, class Resource, class AccessMode>
char* ACL<Entity, Resource, AccessMode>::GetAccessMode(EntityId const& e, Resource const& r) const {
    auto conn = pgbackend->connection();
    const char* params[2];
    params[0] = std::to_string(e).c_str();
    params[1] = r.get_name().c_str();

    const char* query = "SELECT access FROM Acl WHERE id_en = $1 AND res = $2; " ;
    PQsendQueryParams(conn->connection().get(), query, 2, NULL, params,
                        NULL, NULL, 0);

    char* accessmode;

    while ( auto res_ = PQgetResult(conn->connection().get())) {
       if (PQresultStatus(res_) == PGRES_TUPLES_OK && PQntuples(res_)) {
           accessmode = PQgetvalue (res_ ,0, 0);
       }
       if (PQresultStatus(res_) == PGRES_FATAL_ERROR){
           std::cout<< PQresultErrorMessage(res_) <<std::endl;
           std::cout << "GetAccessMode " << std::endl;
       }
       PQclear(res_);
    }

    pgbackend->freeConnection(conn);

    return accessmode;
}

template<class Entity, class Resource, class AccessMode>
void ACL<Entity, Resource, AccessMode>::SetAccessMode(EntityId const& e, Resource const& r){
    auto conn = pgbackend->connection();
    const char* params[3];
    params[0] = std::to_string(e).c_str();
    params[1] = r.get_name().c_str();
    params[2] = std::to_string(AccessMode()).c_str();

    const char* query =
        "INSERT INTO Resources (resour) "
        " VALUES ($2)"
        " ON CONFLICT (name) "
        " DO NOTHING;"
        "INSERT INTO Acl (id_en, res, access) "
        " VALUES ($1, $2, $3)";

    PQsendQueryParams(conn->connection().get(), query, 1, NULL, params + 1,
                        NULL, NULL, 0);
    check(conn);

    PQsendQueryParams(conn->connection().get(), query, 3, NULL, params,
                        NULL, NULL, 0);
    check(conn);
}