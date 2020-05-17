#ifndef RECIPE_H
#define RECIPE_H

#include <iostream>
#include <string>
#include <vector>
#include "ingredient.h"

using namespace std;

class Recipe
{
private:
    int ID;
    string name;
    vector<Ingredient> ingredientList;
    string prepStyle;
    string iceStyle;
    string garnish;
    string glass;
    string instructions;
public:
    Recipe(int ID, string name, vector<Ingredient> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions);
    Recipe(const Recipe &other);
    Recipe();
    Recipe operator= (const Recipe &other);
    bool operator< (const Recipe &other);

    int getID() {    return ID;  };
    string getName() {    return name;  };
    vector<Ingredient> getIngredientList() {return ingredientList;  };
    string getPrepStyle() {    return prepStyle;    };
    string getIceStyle() {    return iceStyle;  };
    string getGarnish() {    return garnish;    };
    string getGlass() {    return glass;    };
    string getInstructions() {    return instructions;  };
    
    void setName(string name) { this->name = name;  };
    void setIngredientList(vector<Ingredient> ingredientList) { this->ingredientList = ingredientList;  };
    void setPrepStyle(string prepStyle) {   this->prepStyle = prepStyle;    };
    void setIceStyle(string iceStyle) { this->iceStyle = iceStyle;  };
    void setGarnish(string garnish) {   this->garnish = garnish;    };
    void setGlass(string glass) {   this->glass = glass;    };
    void setInstructions(string instructions) { this->instructions = instructions;  };
};
#endif