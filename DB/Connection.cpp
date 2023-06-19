#include "Connection.h"
#include "config.h"

PGConnection::PGConnection(){
    m_connection.reset( PQsetdbLogin(database::m_dbhost,
     database::m_dbport, 
     nullptr, 
     nullptr, 
     database::m_dbname, 
     database::m_dbuser, 
     database::m_dbpass), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
    }
}

std::shared_ptr<PGconn> PGConnection::connection() const
{
    return m_connection;
}