#include "test.h"

#include "../ACL/ACL.h"
#include "iostream"

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

void run_test(){
    try{
        test_set_access();
    }
    catch(const std::runtime_error& ex){
        std::cerr << ex.what();
    }
}

void test_add(){
    Document file1("file1");
    Document file2("file2");

    Person man1("man1");
    Person man2("man2");

    ACL<Person, Document, std::string> acl;
    
    acl.AddEntity(man1.get_id(), file1, "owner");
    acl.AddEntity(man2.get_id(), file1, "user");
    acl.AddEntity(man1.get_id(), file2, "owner");
}

void test_del(){
    Document file1("file1");
    Document file2("file2");

    Person man1("man1");
    Person man2("man2");

    ACL<Person, Document, std::string> acl;

    acl.AddEntity(man1.get_id(), file1, "owner");
    acl.DelEntity(man2.get_id());
}

void test_get_access(){
    Document file1("file1");
    Document file2("file2");

    Person man1("man1");
    Person man2("man2");

    ACL<Person, Document, std::string> acl;
    
    acl.AddEntity(man1.get_id(), file1, "owner");
    acl.AddEntity(man2.get_id(), file1, "user");
    std::cout << acl.GetAccessMode(man1.get_id(), file1) << std::endl;
    std::cout << acl.GetAccessMode(man2.get_id(), file1) << std::endl;
    std::cout << acl.GetAccessMode(man2.get_id(), file2) << std::endl;

}

void test_set_access(){
    Document file1("file1");
    Document file2("file2");

    Person man1("man1");
    Person man2("man2");

    ACL<Person, Document, std::string> acl;
    
    acl.AddEntity(man1.get_id(), file1, "owner");
    std::cout << "man1: " << acl.GetAccessMode(man1.get_id(), file1) << std::endl;

    acl.SetAccessMode(man1.get_id(), file1, "user");
    std::cout << "man1: " << acl.GetAccessMode(man1.get_id(), file1) << std::endl;
}