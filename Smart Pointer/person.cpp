#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "person.h"
#include "license.h"

using namespace std;

Person::Person(string name, unsigned int wealth): name{name}, wealth{wealth} {
    if(name.empty())
        throw runtime_error("Name darf nicht leer sein.");
}

void Person::work(string guild){
    int count{0};

    for(const auto& l : licenses)
        if(l.first==guild)
            if(l.second->valid()){
                l.second->use();
                int s = l.second->get_salary();
                work(s);
                count++;
            }

    if(count==0)
        throw runtime_error("Keine Lizenz ist vorhanden, oder nicht mehr benutzbar");
}

void Person::increase_wealth(unsigned int i){
    wealth+=i;
}

string Person::get_name() const{
    return name;
}

bool Person::pay_fee(unsigned int i){
    if(wealth<i || i==0)
        return false;
    else{
        wealth-=i;
        return true;
    }
}

void Person::receive_license(unique_ptr<License> l){
    int count{0};

    for(const auto& lcs: licenses)
        if(lcs.first==l->get_guildname())
            count++;

    if(count>0)
        licenses.erase(l->get_guildname());

    licenses[l->get_guildname()]=move(l);
}

void Person::transfer_license(string l,shared_ptr<Person> p){
    int check{0};
    for(const auto& lic : licenses)
        if(lic.second->get_guildname()==l)
            check++;

    if(check==0)
        throw runtime_error("keine Lizenz mit dem Namen l besitzen");

    for(auto& lic : licenses)
        if(lic.first == l){
            //p->receive_license(lic.second);
            p->licenses[l] = (move(lic.second));
            licenses.erase(l);
            break;
        }
}

bool Person::eligible(string l) const{
    for(const auto& lic : licenses)
        if(lic.first == l && lic.second->valid())
            return true;
    return false;
}

//name, wealth Coins, {license_0, license_1, ..., license_n}]
ostream& Person::print(ostream& o) const{
    o << name << ", " << wealth << " Coins, {";
    bool check{false};
    for(const auto& l : licenses){
        if(check == false)
            check = true;
        else
            o << ',';
        l.second->print(o);
    }
    return cout << "}]";
}

ostream& operator<<(ostream& o, const Person& p){
    return p.print(o);
}

//------------------------------------------------------------------
Worker::Worker(string name, unsigned int wealth): Person{name, wealth} {}

void Worker::work(unsigned int i){
    Person::increase_wealth(i);
}

//[Worker Person::print(o)  
ostream& Worker::print(ostream& o) const{
    o << "[Worker ";
    Person::print(o);
    return o;
}

//------------------------------------------------------------------
Superworker::Superworker(unsigned int fee1, string name, unsigned int wealth): Person{name, wealth} {
    fee=fee1;
}

void Superworker::work(unsigned int i){
    Person::increase_wealth(i+fee);
}

//[Superworker: Person::print(o)
ostream& Superworker::print(ostream& o) const{
    o << "[Superworker ";
    Person::print(o);
    return o;
}