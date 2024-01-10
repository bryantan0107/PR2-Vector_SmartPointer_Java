#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>

class License;

using namespace std;

class Person{
    string name;
    unsigned int wealth;
    map<string,unique_ptr<License>> licenses;
public:
    Person(string name, unsigned int wealth=0);
    virtual ~Person() = default;
    void work(string guild);
    virtual void work(unsigned int) = 0;
    void increase_wealth(unsigned int i);
    string get_name() const;
    bool pay_fee(unsigned int i);
    void receive_license(unique_ptr<License> l);
    void transfer_license(string l,shared_ptr<Person> p);
    bool eligible(string l) const;
    virtual ostream& print(ostream& o) const;
    friend ostream& operator<<(ostream&, const Person&);
};

class Worker : public Person {
public:
    Worker(string, unsigned int=0);
    void work(unsigned int i);
    ostream& print(ostream& o) const;
};

class Superworker : public Person{
    unsigned int fee;
public:
    Superworker(unsigned int fee1, string, unsigned int=0);
    void work(unsigned int i);
    ostream& print(ostream& o) const;
};

#endif