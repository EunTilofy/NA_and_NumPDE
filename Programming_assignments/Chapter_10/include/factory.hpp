#ifndef _FACTORY_
#define _FACTORY_

#include <bits/stdc++.h>
using namespace std;
template <class T>
class Factory
{
    map<string, shared_ptr<T>> _map;
	Factory () = default;
	Factory (const Factory &) = default;
	Factory& operator = (const Factory &) = default;
    ~Factory () = default;

public:
    static Factory &CreateFactory() { static Factory _; return _; }
    bool insert (const string& id, shared_ptr<T> p) { return _map.insert({id, p}).second; }
    int count (const string& id) const { return _map.count(id); }
    bool erase (const string& id)
    {
        if (count(id)) { _map.erase(id); return 1; }
        return 0;
    }
    shared_ptr<T> at (const string& id)
    {
        if (count(id)) return _map.at(id);
        throw invalid_argument("id: \""s+id+"\" not exists in this factory."s);
    }
    shared_ptr<T>& operator [] (const string& id)
    {
        if (count(id)) return _map[id];
        throw invalid_argument("id: \""s+id+"\" not exists in this factory."s);
    }
    auto begin() const -> decltype(_map.begin()) {
        return _map.begin();
    }
    auto begin() -> decltype(_map.begin()) {
        return _map.begin();
    }
    auto end() const -> decltype(_map.end()) {
        return _map.end();
    }
    auto end() -> decltype(_map.end()) {
        return _map.end();
    }
};

#endif