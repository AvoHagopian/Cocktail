#include "ingredient.h"

//returns object Ingredient as a string
string Ingredient::toString()
{
    string s = "";
    if(amount > 0)
        s += to_string(amount);
    if(unit.compare("NA") != 0)
        s += unit;
    s += ingredient;
    return s;
}