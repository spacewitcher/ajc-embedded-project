#pragma once
#include "common.hpp"
#include <vector>
#include <map>

class ExchangeItem
{
    public:
        ExchangeItem(){};
        ExchangeItem(const vector<string>& properties);
        void setProperties(const vector<string>& properties);
        vector<string> getValues();
        string& operator[](string key);
    private:
        map<string,string> data;
        vector<string> properties;
};