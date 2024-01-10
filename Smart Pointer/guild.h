#ifndef GUILD_H
#define GUILD_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>

class Person;
class License;


using namespace std;

class Guild{
    string name;
    unsigned int fee;
    unsigned int salary;
    map<string,shared_ptr<Person>> members;
public:
    Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>>& members1 = {});
    bool add_member(shared_ptr<Person> p);
    bool remove_member(string n);
    void grant_license(string n);
    bool offer_job(shared_ptr<Person> p) const;
    ostream& print(ostream& o) const;
};

ostream& operator<<(ostream&, const Guild&);

#endif

