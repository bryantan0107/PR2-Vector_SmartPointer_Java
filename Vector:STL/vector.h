#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<stdexcept>
#include<memory>
#include<initializer_list>
#include<algorithm>
#include <list>

using namespace std;
template<typename T>
class Vector{
//----------------------------------Typ-Aliase-------------------------------------
public:
    class ConstIterator;
    class Iterator;
    //using value_type = double
    using value_type = T;
    using size_type = size_t;
    using difference_type =  ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = Vector::Iterator;
    using const_iterator = Vector::ConstIterator;
//------------------------Instanzvariablen/Instance variables----------------------------------
private:
    size_type sz; //die Anzahl der Elemente
    size_type max_sz;  //Kapazität (die maximale Anzahl an Elementen)
    value_type* values;
    static constexpr size_t min_sz{5}; //inside Tipps
public:
//-----------------------------Konstruktoren/Destruktor----------------------------
    //Constructor with size_t n
    Vector(size_type n): sz{0}, max_sz{n<min_sz?min_sz:n}, values{new T[max_sz]} {}

    //Default constructor
    Vector():Vector(min_sz) {}

    //Copy Constructor
    Vector(const Vector &v) {
        sz=v.size();
        max_sz=v.capacity();
        values = new value_type[v.capacity()];

        for(size_type i{0}; i<v.size(); i++)
            values[i] = v.values[i];
    }

    //Constructor with initializer_list
    Vector(initializer_list<value_type> initlist) {
        list<value_type> newlist(initlist);
        sz = newlist.size();
        max_sz = newlist.size();
        values = new value_type[newlist.size()];
        int i{0};
        for(const auto& l: newlist){
            values[i]=l;
            i++;
        }
    }

    //Destruktor
    ~Vector() {
        delete[] values;
        //values = nullptr;
    }

//----------------------------Methoden/Member Functions-----------------------------------
    size_type size() const {
        return sz;
    }

    bool empty() const {
        if(sz==0)
            return true;
        return false;
    }

    void clear() {
        sz=0;
    }

    void reserve(size_t n) {
        if(n==0){
            n++;
        }
        if(max_sz<n){
            max_sz=n;
            value_type* newValues=new value_type[n];
            for(size_type i{0};i<(max_sz/2);i++){
                newValues[i]=values[i];
            }
            delete[] values;
            values=newValues;
        }
    }

    void shrink_to_fit() {
        max_sz=sz;
    }

    void push_back(T x) {
        if(max_sz==0){
            reserve(1);
            values[sz] = x;
            sz++;
        } else if(sz==max_sz) {
            reserve(sz*2);
            values[sz]=x;
            sz++;
        } else{
            values[sz]=x;
            sz++;
        }
    }

    void pop_back(){
        if(sz<1)
            throw runtime_error("Das Vektor ist leer.");
        else{
            values[sz]=0;
            sz--;
        }
    }

    value_type &operator[](size_type index) {
        if((index >= sz) || (index < 0))
            throw runtime_error("Invalid index");
            //throw std::invalid_argument("Invalid index");
        else
            return values[index];
    }

    const value_type &operator[](size_type index) const{
        if((index >= sz) || (index < 0))
            throw runtime_error("Invalid index");
        else
            return values[index];
    }

    size_type capacity() const {
        return max_sz;
    }

    ostream& print(ostream& o) const {
        bool first{false};
        o << '[';
        for(size_t i{0}; i<sz; i++){
            if(!first){
                first=true;
                o << values[i];
            }
            else
                o << ", " << values[i];
        }
        o << ']';
        return o;
    }
//-----------------------Erweitern von Vector/Extending the Vector---------------------------------
    iterator begin() {
    return iterator(values);
    };

    iterator end() {
        return iterator(values+sz);
    }

    const_iterator begin() const {
        return const_iterator(values);
    };

    const_iterator end() const {
        return const_iterator(values+sz);
    }

    iterator insert(const_iterator pos, const_reference val) {
        auto diff = pos-begin();
        if(diff < 0 || static_cast<size_type>(diff) > sz)
            throw runtime_error("Iterator out of bounds");

        size_type current{static_cast<size_type>(diff)};

        if(sz >= max_sz)
            reserve(max_sz*2+1);

        for(auto i {sz}; i-->current;)
            values[i+1] = values[i];

        values[current] = val;
        sz++;
        return iterator{values + current};
    }

    iterator erase(const_iterator pos) {
        auto diff = pos-begin();
        if(diff < 0 || static_cast<size_type>(diff)>=sz)
            throw runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        for(auto i{current}; i < sz-1; ++i)
            values[i]=values[i+1];
        --sz;
        return iterator{values+current};
    }
//--------------------------------------Iterator------------------------------------
    class Iterator {
    public:
        friend class Vector;
        using value_type = Vector::value_type;
        using reference = Vector::reference;
        using pointer = Vector::pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;
        //-------------------------------Instanzvariablen-----------------------------------
    private:
        pointer ptr;
        //-----------------------------Konstruktoren/Methoden-------------------------------
    public:
        //Konstruktor
        Iterator(pointer ptr = nullptr) : ptr{ptr}{};

        //Methoden
        reference operator*() {
            return *ptr;
        }

        pointer operator->() {
            return this->ptr;
        };

        bool operator==(const const_iterator& ander) const {
            return  static_cast<const_iterator>(ptr)==ander;
        };

        bool operator!=(const const_iterator& ander) const {
            return!(static_cast<const_iterator>(ptr)==ander);
        };

        iterator& operator++() {
            ptr++;
            return *this;
        };

        iterator operator++(int) {
            iterator help(ptr);
            ++(ptr);
            return help;
        };

        difference_type operator-(const const_iterator& it) const {
            const_iterator help = this->ptr;
            return help-it.ptr;
        };

        operator const_iterator() const {
            const_iterator neu_iter (ptr);
            return neu_iter;
        };
    };

//--------------------------------ConstIterator-------------------------------------
    class ConstIterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector::const_reference;
        using pointer = Vector::const_pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;
        //-------------------------------Instanzvariablen-----------------------------------
    private:
        pointer ptr;
        //---------------------------------Konstruktoren------------------------------------
    public:
        //Konstrukter
        ConstIterator(pointer ptr) : ptr{ptr} {};
        ConstIterator() : ptr{nullptr} {};

        //Methoden
        reference operator*() const {
            return  *ptr;
        };

        pointer operator->() const {
            return this->ptr;
        };

        bool operator==(const const_iterator &ander) const {
            return ptr == ander.ptr;
        };

        bool operator!=(const const_iterator &ander) const {
            return !(ptr == ander.ptr);
        };

        const_iterator &operator++() {
            (*this)++;
            return *this;
        };

        const_iterator operator++(int) {
            const_iterator help=ptr;
            ++ptr;
            return help;
        };

        difference_type operator-(const const_iterator &it) const {
            return ptr - it.ptr;
        };
    };
};

//----------------------------------Ausgabeformat-----------------------------------
template<typename T>
ostream& operator<<(ostream& o, const Vector<T>& v){
    return v.print(o);
}

#endif