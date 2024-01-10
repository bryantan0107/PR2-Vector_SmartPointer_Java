#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include<map>
#include "guild.h"
#include "license.h"
#include "person.h"

using namespace std;

Guild::Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>>& members1): name{name}, fee{fee}, salary{sal} {
    if(name.empty())
        throw runtime_error("Name darf nicht leer sein.");

    if(fee<=0)
        throw runtime_error("Fee muss groesser als 0 sein.");

    if(salary<=0)
        throw runtime_error("Salary muss groesser als 0 sein.");

    for(unsigned long i{0}; i<members1.size();i++)
        for(unsigned long j{i+1}; j<members1.size();j++)
            if(members1.at(i)==members1.at(j))
                throw runtime_error("Keine Person vorkommt mehr als einmal in members");

    for(const auto& m : members1)
        members[m->get_name()]=move(m);
}

bool Guild::add_member(shared_ptr<Person> p){
    for(const auto& m : members)
        if(m.second==p)
            return false;
    members[p->get_name()]=move(p);
    return true;
}

bool Guild::remove_member(string n){
    for(const auto& m : members)
        if(m.first==n){
            members.erase(n);
            return true;
        }
    return false;
}

void Guild::grant_license(string n){
    int check{0};

    for(const auto& m : members)
        if(m.first==n)
            if(m.second->pay_fee(fee)){
                License l{name,salary};
                m.second->receive_license(make_unique<License>(l));
                check++;
            }

    if(check==0)
        throw runtime_error("Die Person mit Namen n ist kein Gildenmitglied, oder sich koennen die Gebuehr nicht leisten.");
}

bool Guild::offer_job(shared_ptr<Person> p) const{
    if (members.count(p->get_name()) > 0) {
        p->work(salary * 2);
        return true;
    } else if (p->eligible(name)) {
        p->work(name);
        return true;
    } else {
        return false;

    }
}

//[name, License fee: fee, Job salary: salary, {member_name0, member_name1, ..., member_namen}]
ostream& Guild::print(ostream& o) const{
    o << '[' << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";

    bool check{false};
    for(const auto& m : members){
        if(check==false)
            check=true;
        else
            o << ", ";
        o << m.first;
    }

    return o << "}]";
}

ostream& operator<<(ostream& o, const Guild& g){
    return g.print(o);
}