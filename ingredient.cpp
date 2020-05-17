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

//set value of Ingredient object to that of string ingredient
//return 0 if valid ingredient or 1 if invalid
int Ingredient::setString(const string &stringIngredient)
{
    double tempAmount = 0;
    string tempUnit = "NULL";
    string tempIngredient = "";
    int x = 0;
    string::size_type st = 0; //ingredient.length() - st = length of rest of string without amount

    if((stringIngredient[0] >= '0' && stringIngredient[0] <= '9') || (stringIngredient[0] == '.'))
        tempAmount = stod(stringIngredient, &st);
    else
        return 1;
    
    st++;

    for(int i = st; i < stringIngredient.length(); i++)
    {
        if(stringIngredient[i] == ' ')
        {
            x = i;
            i = stringIngredient.length();
        }
    }
    tempUnit = stringIngredient.substr(st, x - st);
    x++;
    tempIngredient = stringIngredient.substr(x, stringIngredient.length() - x);
    this->amount = tempAmount;
    this->unit = tempUnit;
    this->ingredient = tempIngredient;

    return 0;
}
