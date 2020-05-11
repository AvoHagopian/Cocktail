#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

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
    Recipe(int ID, string name, vector<string> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions);
    Recipe(const Recipe &other);
    Recipe();
    Recipe operator= (const Recipe &other);
    bool operator< (const Recipe &other);

    int getID() {    return ID;  };
    string getName() {    return name;  };
    vector<string> getIngredientList() {return ingredientList;  };
    string getPrepStyle() {    return prepStyle;    };
    string getIceStyle() {    return iceStyle;  };
    string getGarnish() {    return garnish;    };
    string getGlass() {    return glass;    };
    string getInstructions() {    return instructions;  };
    
    void setName(string name) { this->name = name;  };
    void setIngredientList(vector<string> ingredientList) { this->ingredientList = ingredientList;  };
    void setPrepStyle(string prepStyle) {   this->prepStyle = prepStyle;    };
    void setIceStyle(string iceStyle) { this->iceStyle = iceStyle;  };
    void setGarnish(string garnish) {   this->garnish = garnish;    };
    void setGlass(string glass) {   this->glass = glass;    };
    void setInstructions(string instructions) { this->instructions = instructions;  };

    //string toString();
};

class Ingredient
{
private:
    double amount;
    string unit;
    string ingredient;
public:
    Ingredient();
    Ingredient(double amount, string unit, string ingredient);
    Ingredient(const Ingredient &other);
    Ingredient operator=(const Ingredient &other);

    double getAmount(){ return amount;  };
    string getUnit(){   return unit;    };
    string getIngredient(){ return ingredient;  };

    void setAmount(double amount){  this->amount = amount;  }
    void setUnit(string unit){  this->unit = unit;  }
    void setIngredient(string ingredient){  this->ingredient = ingredient;  }

    string toString();
};

void loadRecipe(vector<Recipe> &full, string filename);
vector<Recipe> searchRecipe(string searchWord, vector<Recipe> full, int option);
void editRecipe(vector<Recipe> full, int ID);
void saveRecipe(vector<Recipe> full, string filename);
void printRecipe(Recipe full);
string toLower(string s);

int main(void)
{
    string filename = "Cooler Cocktails.csv";
    vector<Recipe> full;
    loadRecipe(full, filename);
    //printRecipe(searchRecipe("collins", full, 3));
    //saveRecipe();
    //editRecipe(full, 69);
    for(int i = 0; i < full.size(); i++)
        printRecipe(full[i]);
    return 0;
}

//loads all recipes from file filename into vector full
void loadRecipe(vector<Recipe> & full, string filename)
{
    ifstream fin(filename, ifstream::in);
    if (!fin.is_open())
    {
        cout << "error: Couldn't open file\n";
        exit(1);
    }

    int quote = 0;
    int comma = 0;
    string temp = "";
    char c;
    
    full.clear();
    int tempID;
    string tempName;
    vector<string> tempIngredient;
    string tempPrepStyle;
    string tempIceStyle;
    string tempGarnish;
    string tempGlass;
    string tempInstructions;

    while (fin.peek() != EOF)
    {
        fin >> tempID;
        fin.get(c);
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
        full.push_back(Recipe(tempID, tempName, tempIngredient, tempPrepStyle, tempIceStyle, tempGarnish, tempGlass, tempInstructions));
        quote = 0;
        comma = 0;
        temp = "";
        tempIngredient.clear();
    }

    fin.close();
}

//search Recipe vector full for searchWord using option 0 for name, 1 for ingredients, 2 for garnish, or 3 for glass
vector<Recipe> searchRecipe(string searchWord, vector<Recipe> full, int option)
{
    //Recipe(tempID, tempName, tempIngredient, tempPrepStyle, tempIceStyle, tempGarnish, tempGlass, tempInstructions));
    vector<Recipe> ret;
    Recipe temp;
    bool check = false;

    switch(option)
    {
        case 0:
            //search by name
            for(int i = 0; i < full.size(); i++)
            {
                if(toLower(full[i].getName()).find(toLower(searchWord)) != string::npos)
                {
                    temp = full[i];
                    ret.push_back(temp);
                }
            }
            break;
        case 1:
            //search by ingredient
            for(int i = 0; i < full.size(); i++)
            {
                vector<string> tempList = full[i].getIngredientList();
                for(int j = 0; j < tempList.size(); j++)
                {
                    if(toLower(tempList[j]).find(toLower(searchWord)) != string::npos)
                    {
                        check = true;
                    }
                }
                if(check)
                {
                    temp = full[i];
                    ret.push_back(temp);
                    check = false;
                }
            }
            break;
        case 2:
            //search by garnish
            for(int i = 0; i < full.size(); i++)
            {
                if(toLower(full[i].getGarnish()).find(toLower(searchWord)) != string::npos)
                {
                    temp = full[i];
                    ret.push_back(temp);
                }
            }
            break;
        case 3:
            //search by glass
            for(int i = 0; i < full.size(); i++)
            {
                if(toLower(full[i].getGlass()).find(toLower(searchWord)) != string::npos)
                {
                    temp = full[i];
                    ret.push_back(temp);
                }
            }
            break;
        default:
            break;
    }
    return ret;
}

//edit Recipe by each variable
void editRecipe(vector<Recipe> full, int ID)
{
    //shits super fucked yo
    string s = "";
    Recipe temp = full[ID];

    string tempName;
    vector<string> tempIngredient = temp.getIngredientList();
    string tempPrepStyle;
    string tempIceStyle;
    string tempGarnish;
    string tempGlass;
    string tempInstructions;

    int option = 1;
    int list = 1;

    while(option != 0)
    {
        printRecipe(temp);
        cout << "What would you like to edit? (Type the corresponding number and hit enter or 0 to quit)\n";
        cout << "(1)\tName\n";
        cout << "(2)\tIngredient List\n";
        cout << "(3)\tPreperation Style\n";
        cout << "(4)\tIce Style\n";
        cout << "(5)\tGarnish\n";
        cout << "(6)\tGlass\n";
        cout << "(7)\tInstructions\n";
        cin >> option;

        switch (option)
        {
            case 0:
                //quit
                break;
            case 1:
                //edit name
                cout << "Current Name:\t\t" << temp.getName() << endl;
                cout << "Change to:";
                cin >> tempName;
                temp.setName(tempName);
                break;
            case 2:
                //edit ingredient list
                while(list != 0)
                {
                    cout << "Current Ingredient List:\n";
                    for(int i = 0; i < tempIngredient.size(); i++)
                        cout << "(" << i + 1 << ")\t" << tempIngredient[i] << endl;

                    cout << "If you wish to change a specific ingredient, type the number before the ingredient.\n";
                    cout << "If you wish to add an ingredient, type " << tempIngredient.size() + 1 << endl;
                    cout << "(If you wish to quit, type 0)\n";
                    cin >> list;
                    cin.ignore(1, '\n');
                    if(list < 0 || list > tempIngredient.size() + 1)
                        cout << "Invalid option. Please choose again.\n";
                    else
                    {
                        if(list != 0)
                        {
                            if(list == tempIngredient.size() + 1)
                            {
                                cout << "Enter the value, unit, and ingredient you would like to add and press enter.\n";
                                getline(cin, s);
                                tempIngredient.push_back(s);
                            }
                            else
                            {
                                cout << "Enter the value, unit, and ingredient you would like to change to and press enter.\n";
                                getline(cin, tempIngredient[list - 1]);
                            }
                            temp.setIngredientList(tempIngredient);
                        }
                    }
                }
                break;
            case 3:
                //edit prep style
                cout << "Current Preperation Style:\t\t" << temp.getPrepStyle() << endl;
                cout << "Change to:";
                cin >> tempPrepStyle;
                temp.setPrepStyle(tempPrepStyle);
                break;
            case 4:
                //edit ice style
                cout << "Current Ice Style:\t\t" << temp.getIceStyle() << endl;
                cout << "Change to:";
                cin >> tempIceStyle;
                temp.setIceStyle(tempIceStyle);
                break;
            case 5:
                //edit garnish
                cout << "Current Garnish:\t\t" << temp.getGarnish() << endl;
                cout << "Change to:";
                cin >> tempGarnish;
                temp.setGarnish(tempGarnish);
                break;
            case 6:
                //edit glass
                cout << "Current Glass:\t\t" << temp.getGlass() << endl;
                cout << "Change to:";
                cin >> tempGlass;
                temp.setGlass(tempGlass);
                break;
            case 7:
                //edit instructions
                cout << "Current Instructions:\t\t" << temp.getInstructions() << endl;
                cout << "Change to:";
                cin >> tempInstructions;
                temp.setInstructions(tempInstructions);
                break;
            default:
                break;
        }
    }
}

//saves list of all vectors full in file filename
void saveRecipe(vector<Recipe> full, string filename)
{
    vector<string> temp;
    ofstream fout(filename, ofstream::out);
    
    for(int i = 0; i < full.size(); i++)
    {
        temp = full[i].getIngredientList();
        fout << to_string(full[i].getID()) + ',';
        fout << full[i].getName() + ',';

        fout << '"';
        if(temp[0][0] == ' ')
            fout << temp[0].substr(1);
        else
        {
            if(temp[0][0] == '.')
                fout << "0" + temp[0];
            else
                fout << temp[0];
        }
        for(int j = 1; j < temp.size(); j++)
        {
            if(temp[j][0] == ' ')
                fout << "\n" + temp[j].substr(1);
            else
            {
                if(temp[j][0] == '.')
                    fout << "\n0" + temp[j];
                else
                    fout << "\n" + temp[j];
            }
        }
        fout << "\",";

        fout << full[i].getPrepStyle() + ',';
        fout << full[i].getIceStyle() + ',';
        fout << full[i].getGarnish() + ',';
        fout << full[i].getGlass() + ',';
        fout << full[i].getInstructions() + '\n';
    }
    fout.close();
}

//prints list of all recipes in vector full
void printRecipe(Recipe R)
{
    vector<string> temp = R.getIngredientList();

    cout << left << setw(24) << "ID:";
    cout << to_string(R.getID()) << endl;

    cout << left << setw(24) << "Name:";
    cout << R.getName() << endl;

    cout << left << setw(24) << "Ingredient List:";
    cout << temp[0] << endl;
    for(int i = 1; i < temp.size(); i++)
    {
        cout << left << setw(24) << "";
        cout << temp[i] << endl;
    }

    cout << left << setw(24) << "Preperation Style:";
    cout << R.getPrepStyle() << endl;

    cout << left << setw(24) << "Ice Style:";
    if(R.getIceStyle().length() != 0)
        cout << R.getIceStyle();
    cout << endl;

    cout << left << setw(24) << "Garnish:";
    if(R.getGarnish().length() != 0)
        cout << R.getGarnish();
    cout << endl;

    cout << left << setw(24) << "Glass:";
    if(R.getGlass().length() != 0)
        cout << R.getGlass();
    cout << endl;

    cout << left << setw(24) << "Instructions:";
    if(R.getInstructions().length() != 0)
        cout << R.getInstructions();
    cout << endl << endl;
}

//variable specified constructor
Recipe::Recipe(int ID, string name, vector<string> ingredientList, string prepStyle, string iceStyle, string garnish, string glass, string instructions)
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

//returns lowercase version of string s
string toLower(string s)
{
    string ret;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
            ret += s[i] + 32;
        else
            ret += s[i];
        
    }
    return ret;
}
