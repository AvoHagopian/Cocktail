#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

class Recipe
{
private:
    int ID;
    string name;
    vector<string> ingredientList;
    string prepStyle;
    string iceStyle;
    string garnish;
    string glass;
    string instructions;
public:
    Recipe(string name, vector<string> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions);
    Recipe(const Recipe &other);
    Recipe();
    Recipe operator= (const Recipe &other);
    int getID() {    return ID;  };
    string getName() {    return name;  };
    string getPrepStyle() {    return prepStyle;    };
    string getIceStyle() {    return iceStyle;  };
    string getGarnish() {    return garnish;    };
    string getGlass() {    return glass;    };
    string getInstructions() {    return instructions;  };
    string toString();
};

/*class Ingredient
{
    private:
        double amount;
        string unit;
        string ingredient;
    public:
        Ingredient(double amount, string unit, string ingredient);
        string outputAsString();
};*/

vector<Recipe> searchByName(string searchName, vector<Recipe> full);

int main(void)
{
    ifstream fin("Cocktails.csv", ifstream::in);
    if (!fin.is_open())
    {
        cout << "error: Couldn't open file\n";
        exit(1);
    }

    int quote = 0;
    int comma = 0;
    string temp = "";
    bool done = true;
    char c;
    
    vector<Recipe> full;
    string tempName;
    vector<string> tempIngredient;
    string tempPrepStyle;
    string tempIceStyle;
    string tempGarnish;
    string tempGlass;
    string tempInstructions;
    while (fin.peek() != EOF)
    {
        while (comma < 7)
        {
            fin.get(c);
            switch (c)
            {
            case '"':
                if (quote == 0)
                {
                    quote++;
                    break;
                }
                if (quote != 0)
                {
                    quote--;
                    break;
                }
            case ',':
                if (quote == 0)
                {
                    switch (comma)
                    {
                    case 0:
                        tempName = temp;
                        break;
                    case 1:
                        tempIngredient.push_back(temp);
                        break;
                    case 2:
                        tempPrepStyle = temp;
                        break;
                    case 3:
                        tempIceStyle = temp;
                        break;
                    case 4:
                        tempGarnish = temp;
                        break;
                    case 5:
                        tempGlass = temp;
                        break;
                    case 6:
                        tempInstructions = temp;
                        break;
                    default:
                        break;
                    }
                    temp = "";
                    comma++;
                    break;
                }
                break;
            case '\n':
                if (quote != 0)
                {
                    tempIngredient.push_back(temp);
                    temp = "";
                    break;
                }
                else
                {
                    tempInstructions = temp;
                    comma++;
                    break;
                }
            default:
                temp += c;
                break;
            }
        }
        full.push_back(Recipe(tempName, tempIngredient, tempPrepStyle, tempIceStyle, tempGarnish, tempGlass, tempInstructions));
        quote = 0;
        comma = 0;
        temp = "";
        tempIngredient.clear();
    }

    fin.close();

    /*vector<Recipe> searchBName = searchByName("Bramble", full);
    //print recipe list
    for(int i = 0; i < searchBName.size(); i++)
    {
        cout << searchBName[i].toString() << endl;
    }*/

    for(int i = 0; i < full.size(); i++)
    {
        cout << full[i].toString() << endl;
    }
    return 0;
}

int searchByIngredient(vector<string> searchIngredient, vector<string> ingredientList)
{
    int ret = 0;
    for(int i = 0; i < searchIngredient.size(); i++)
    {
        for(int j = 0; j < ingredientList.size(); j++)
        {
            if(ingredientList[j].find(searchIngredient[i]) != string::npos)
            {
                ret++;
            }
        }
    }
    return ret;
}

vector<Recipe> searchByName(string searchName, vector<Recipe> full)
{
    vector<Recipe> ret;
    Recipe temp;
    for(int i = 0; i < full.size(); i++)
    {
        if(full[i].getName().find(searchName) != string::npos)
        {
            temp = full[i];
            ret.push_back(temp);
        }
    }
    return ret;
}

Recipe::Recipe(string name, vector<string> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions)
{
    this->name = name;
    this->ingredientList = ingredientList;
    this->prepStyle = prepStyle;
    this->iceStyle = iceStyle;
    this->garnish = garnish;
    this->glass = glass;
    this->instructions = instructions;
}

Recipe::Recipe(const Recipe &other)
{
    this->name = other.name;
    this->ingredientList = other.ingredientList;
    this->prepStyle = other.prepStyle;
    this->iceStyle = other.iceStyle;
    this->garnish = other.garnish;
    this->glass = other.glass;
    this->instructions = other.instructions;
}

Recipe::Recipe()
{
    this->name = "";
    this->ingredientList.clear();
    this->prepStyle = "";
    this->iceStyle = "";
    this->garnish = "";
    this->glass = "";
    this->instructions = "";
}

Recipe Recipe::operator= (const Recipe &other)
{
    this->name = other.name;
    this->ingredientList = other.ingredientList;
    this->prepStyle = other.prepStyle;
    this->iceStyle = other.iceStyle;
    this->garnish = other.garnish;
    this->glass = other.glass;
    this->instructions = other.instructions;
    return *this;
}

string Recipe::toString()
{
    //string name, vector<string> ingredientvector, string prepStyle, string iceStyle, string garnish, string glass, string instructions
    char end = '\n';
    string ret = "";

    ret += "Name:\t\t\t\t" + name + end;

    ret += "Ingredient List:\t" + ingredientList[0] + end;
    for(int i = 1; i < ingredientList.size(); i++)
        ret += "\t\t\t\t\t" + ingredientList[i] + end;

    ret += "Prep Style:\t\t\t" + prepStyle + end;

    ret += "Ice Style:\t\t\t";
    if(iceStyle.length() != 0)
        ret += iceStyle;
    ret += end;

    ret += "Garnish:\t\t\t";
    if(garnish.length() != 0)
        ret += garnish;
    ret += end;
    
    ret += "Glass:\t\t\t\t";
    if(glass.length() != 0)
        ret += glass;
    ret += end;
    
    ret += "Instructions:\t\t";
    if(instructions.length() != 0)
        ret += instructions;
    ret += end;

    return ret;
}