#include <iostream>
#include "ACL/ACL.h"

class Person: public Entity{
public:
    Person(): m_name("Unnamed"){}
    Person(std::string name): m_name(name) {}
    std::string m_name;
};

class Document: public Resource{
public:
    Document(std::string name){
        m_name = name;
    }
};

int main(){
    Document file{"Arenda"};
    Person Ivan{"Ivan"};
    ACL<Person, Document, std::string> acl;

    acl.AddEntity(Ivan.get_id(), file, "owner");

    std::cout << acl.GetAccessMode(Ivan.get_id(), file);
    return 0;
}