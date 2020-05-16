#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Ingredient
{
private:
    double amount;
    string unit;
    string ingredient;
public:
    Ingredient(double amount, string unit, string ingredient);
    Ingredient(const Ingredient &other);
    Ingredient();
    Ingredient operator=(const Ingredient &other);

    double getAmount(){ return amount;  };
    string getUnit(){   return unit;    };
    string getIngredient(){ return ingredient;  };

    void setAmount(double amount){  this->amount = amount;  }
    void setUnit(string unit){  this->unit = unit;  }
    void setIngredient(string ingredient){  this->ingredient = ingredient;  }

    string toString();
};

#endif