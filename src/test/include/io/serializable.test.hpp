#pragma once
#include "serializable.hpp"
#include "up11.h"

class MockSerializable: public Serializable
{
    public:
        MockSerializable(){};
        MockSerializable(string nom, string prenom):nom(nom),prenom(prenom){};
        vector<string> getProperties()  const override
        {
            return {"Nom","Prenom"};
        }
        ExchangeItem to_exchangeItem() const override
        {
            ExchangeItem e(this->getProperties());
            e["Nom"]=this->nom;
            e["Prenom"]=this->prenom;
            return e;
        }
        void from_exchangeItem(ExchangeItem& item) override
        {
            this->nom = item["Nom"];
            this->prenom = item["Prenom"];
        }
        string getPrenom(){return this->prenom;}
        string getNom(){return this->nom;}
    private:
        string nom;
        string prenom;
};