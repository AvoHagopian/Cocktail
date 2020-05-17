#include "recipe.h"

//variable specified constructor
Recipe::Recipe(int ID, string name, vector<Ingredient> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions)
{
    this->ID = ID;
    this->name = name;
    this->ingredientList = ingredientList;
    this->prepStyle = prepStyle;
    this->iceStyle = iceStyle;
    this->garnish = garnish;
    this->glass = glass;
    this->instructions = instructions;
}

//object specified constructor
Recipe::Recipe(const Recipe &other)
{
    this->ID = other.ID;
    this->name = other.name;
    this->ingredientList = other.ingredientList;
    this->prepStyle = other.prepStyle;
    this->iceStyle = other.iceStyle;
    this->garnish = other.garnish;
    this->glass = other.glass;
    this->instructions = other.instructions;
}

//default constructor
Recipe::Recipe()
{
    this->ID = 0;
    this->name = "";
    this->ingredientList.clear();
    this->prepStyle = "";
    this->iceStyle = "";
    this->garnish = "";
    this->glass = "";
    this->instructions = "";
}

//equal operator overload
Recipe Recipe::operator= (const Recipe &other)
{
    this->ID = other.ID;
    this->name = other.name;
    this->ingredientList = other.ingredientList;
    this->prepStyle = other.prepStyle;
    this->iceStyle = other.iceStyle;
    this->garnish = other.garnish;
    this->glass = other.glass;
    this->instructions = other.instructions;
    return *this;
}

//less than operator overload
bool Recipe::operator< (const Recipe &other)
{
    if(this->name.compare(other.name) <= 0)
        return false;
    else
        return true;
}