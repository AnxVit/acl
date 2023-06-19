#pragma once

#include <memory>
#include <mutex>
#include </usr/include/postgresql/libpq-fe.h>

class PGConnection{
public:
    PGConnection();
    std::shared_ptr<PGconn> connection() const;
private:
    std::shared_ptr<PGconn> m_connection;
};