#include "ingredient.h"

//variable specified constructor
Ingredient::Ingredient(double amount, string unit, string ingredient)
{
    this->amount = amount;
    this->unit = unit;
    this->ingredient = ingredient;
}

//object specified constructor
Ingredient::Ingredient(const Ingredient &other)
{
    this->amount = other.amount;
    this->unit = other.unit;
    this->ingredient = other.ingredient;
}

//default constructor
Ingredient::Ingredient()
{
    this->amount = 0;
    this->unit = "NULL";
    this->ingredient = "";
}

//equal operator overload
Ingredient Ingredient::operator=(const Ingredient &other)
{
    this->amount = other.amount;
    this->unit = other.unit;
    this->ingredient = other.ingredient;
    return *this;
}

//returns object Ingredient as a string
string Ingredient::toString()
{
    string s = "";
    if(amount > 0)
        s += to_string(amount);
    if(unit.compare("NULL") != 0)
        s += unit;
    s += ingredient;
    return s;
}