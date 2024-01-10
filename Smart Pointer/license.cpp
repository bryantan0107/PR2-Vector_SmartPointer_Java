#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "license.h"

using namespace std;

License::License(string name, unsigned int salary): name{name}, salary{salary}, counter{0} {
    if(name.empty())
        throw runtime_error("Name darf nicht leer sein.");

    if(salary<=0)
        throw runtime_error("Salary muss groesser als 0 sein.");
}

string License::get_guildname() const{
    return name;
}

unsigned int License::get_salary() const{
    return salary;
}

bool License::valid() const{
    if(counter<=3)
        return true;
    return false;
}

bool License::use(){
    if(valid()){
        counter+=1;
        return true;
    }
    return false;
}

//[License for name, Salary: salary, Used: counter]
ostream& License::print(ostream& o) const{
    return o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << ']';
}

ostream& operator<<(ostream& o, const License& l){
    return l.print(o);
}