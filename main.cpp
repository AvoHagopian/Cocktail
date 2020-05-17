#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "recipe.h"

using namespace std;

void loadRecipe(vector<Recipe> &full, string filename);
void searchRecipe(vector<Recipe> full);
void editRecipe(Recipe & R);
void saveRecipe(vector<Recipe> full, string filename);
void printRecipe(Recipe R);
void printRecipeList(vector<Recipe> full);
string toLower(string s);

int main(void)
{
    cout << "\n \\       /	Cocktail Guide\n  \\     /\n   \\   /\n    \\ /\n     |\n     |\n     |\n     |\n  _ _|_ _\n" << endl;

    string inFilename = "";
    string outFilename = "";
    cout << "Welcome to your Cocktail Guide!" << endl;
    cout << "Please type the name of the file you would like to read from:" << endl;
    getline(cin, inFilename);

    vector<Recipe> full;
    loadRecipe(full, inFilename);

    int choice = -1;
    int id = 0;
    while(choice != 0)
    {
        cout << "What would you like to do? (Type the corresponding value)" << endl;
        cout << "(1) Print recipe list." << endl;
        cout << "(2) Search recipe list." << endl;
        cout << "(3) Edit recipe." << endl;
        cout << "(4) Save changes." << endl;
        cout << "(0) Quit" << endl;

        cin >> choice;

        switch (choice)
        {
            case 1:
                printRecipeList(full);
                break;
            case 2:
                searchRecipe(full);
                break;
            case 3:
                cout << "Please enter the ID of the recipe you wish to edit:" << endl;
                cin >> id;
                if(id < 1 || id > full.size())
                    cout << "You fucked up boy" << endl;
                else
                    editRecipe(full[id - 1]);
                break;
            case 4:
                cout << "Please type the name of the file you would like to save to:" << endl;
                cin.ignore(1, '\n');
                getline(cin, outFilename);
                saveRecipe(full, outFilename);
                break;
            case 0:
                break;
            default:
                cout << "Please enter a valid response fuckboy" << endl;
                break;
        }

    }
    return 0;
}

//loads all recipes from file filename into vector full
void loadRecipe(vector<Recipe> & full, string filename)
{
    ifstream fin(filename, ifstream::in);
    if (!fin.is_open())
    {
        cout << "error: Couldn't open file" << filename << endl;
        exit(1);
    }

    int quote = 0;
    int comma = 0;
    string temp = "";
    char c;
    int oops = 0;
    
    full.clear();
    int tempID;
    string tempName;
    string tempPrepStyle;
    string tempIceStyle;
    string tempGarnish;
    string tempGlass;
    string tempInstructions;
    vector<Ingredient> tempIngredientList;
    Ingredient tempIngredientObject;

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
                        oops += tempIngredientObject.setString(temp);
                        tempIngredientList.push_back(tempIngredientObject);
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
                    oops += tempIngredientObject.setString(temp);
                    tempIngredientList.push_back(tempIngredientObject);
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
        if(oops != 0)
        {
            cout << "Recipe " << tempID << ": " << tempName << " has " << oops << " problem(s) with its ingredients. It has not been loaded." << endl;
            oops = 0;
        }
        else
            full.push_back(Recipe(tempID, tempName, tempIngredientList, tempPrepStyle, tempIceStyle, tempGarnish, tempGlass, tempInstructions));
        
        quote = 0;
        comma = 0;
        temp = "";
        tempIngredientList.clear();
    }

    fin.close();
}

//search Recipe vector full for searchWord using option 1 for name, 2 for ingredients, 3 for garnish, or 4 for glass then prints narrowed list
void searchRecipe(vector<Recipe> full)
{
    vector<Recipe> narrow;
    vector<Ingredient> tempIngredientList;
    Recipe temp;
    bool check = false;
    int option = 0;
    int pre = 0;
    string searchWord = "";

    cout << "What would you like to search by? (Type the corresponding value)" << endl;
    cout << "(1) Name" << endl;
    cout << "(2) Ingredients" << endl;
    cout << "(3) Garnish" << endl;
    cout << "(4) Glass" << endl;

    cin >> option;
    if(option < 1 || option > 4)
        cout << "Invalid search option, returning to main menu" << endl;
    else
    {
        if(option != '2')
        {
            cout << "Type in search phrase and hit enter:";
            cin.ignore(1, '\n');
            getline(cin, searchWord);
        }

        switch(option)
        {
            case 1:
                //search by name
                for(int i = 0; i < full.size(); i++)
                {
                    if(toLower(full[i].getName()).find(toLower(searchWord)) != string::npos)
                    {
                        temp = full[i];
                        narrow.push_back(temp);
                    }
                }
                break;
            case 2:
                //search by ingredient
                {
                    //take in search word as a vector of strings
                    vector<string> searchWords;
                    int count = 0;
                    cout << "Type in each ingredient you would like to search for seperated by a space and hit enter." << endl;
                    cin.ignore(1, '\n');
                    getline(cin, searchWord);
                    for(int i = 0; i < searchWord.length(); i++)
                    {
                        if(searchWord[i] == ' ')
                        {
                            searchWords.push_back(searchWord.substr(pre, i - pre));
                            i++;
                            pre = i;
                        }
                        searchWords.push_back(searchWord.substr(pre, searchWord.length() - pre));
                    }

                    //search each recipe for vector of strings
                    for(int i = 0; i < full.size(); i++)
                    {
                        tempIngredientList = full[i].getIngredientList();
                        for(int j = 0; j < tempIngredientList.size(); j++)
                        {
                            for(int k = 0; k < searchWords.size(); k++)
                            {
                                if(toLower(tempIngredientList[j].toString()).find(toLower(searchWords[k])) != string::npos)
                                {
                                    count++;
                                    k = searchWords.size();
                                }
                            }
                        }
                        if(count == tempIngredientList.size())
                        {
                            temp = full[i];
                            narrow.push_back(temp);
                            count = 0;
                            tempIngredientList.clear();
                        }
                    }
                    break;
                }
            case 3:
                //search by garnish
                for(int i = 0; i < full.size(); i++)
                {
                    if(toLower(full[i].getGarnish()).find(toLower(searchWord)) != string::npos)
                    {
                        temp = full[i];
                        narrow.push_back(temp);
                    }
                }
                break;
            case 4:
                //search by glass
                for(int i = 0; i < full.size(); i++)
                {
                    if(toLower(full[i].getGlass()).find(toLower(searchWord)) != string::npos)
                    {
                        temp = full[i];
                        narrow.push_back(temp);
                    }
                }
                break;
            default:
                cout << option << " is not a valid search option." << endl;
                break;
        }
        printRecipeList(narrow);
    }
}

//edit Recipe by each variable
void editRecipe(Recipe & R)
{
    string s = "";
    vector<Ingredient> tempIngredientList = R.getIngredientList();
    Ingredient tempIngredientObject;

    int option = 1;
    int list = 1;

    int oops = 0;

    while(option != 0)
    {
        printRecipe(R);
        cout << "What would you like to edit? (Type the corresponding number and hit enter)\n";
        cout << "(1) Name\n";
        cout << "(2) Ingredient List\n";
        cout << "(3) Preperation Style\n";
        cout << "(4) Ice Style\n";
        cout << "(5) Garnish\n";
        cout << "(6) Glass\n";
        cout << "(7) Instructions\n";
        cout << "(0) Quit\n";
        cin >> option;

        switch (option)
        {
            case 0:
                //quit
                break;
            case 1:
                //edit name
                cout << "Current Name:\t\t" << R.getName() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setName(s);
                break;
            case 2:
                //edit ingredient list
                while(list != 0)
                {
                    cout << "Current Ingredient List:\n";
                    for(int i = 0; i < tempIngredientList.size(); i++)
                        cout << "(" << i + 1 << ")\t" << tempIngredientList[i].toString() << endl;

                    cout << "If you wish to change a specific ingredient, type the number before the ingredient.\n";
                    cout << "If you wish to add an ingredient, type " << tempIngredientList.size() + 1 << endl;
                    cout << "(If you wish to quit, type 0)\n";
                    cin >> list;
                    cin.ignore(1, '\n');
                    if(list < 0 || list > tempIngredientList.size() + 1)
                        cout << "Invalid option. Please choose again.\n";
                    else
                    {
                        if(list != 0)
                        {
                            if(list == tempIngredientList.size() + 1)
                            {
                                cout << "Enter the value, unit, and ingredient you would like to add and press enter.\n";
                                getline(cin, s);
                                oops = tempIngredientObject.setString(s);
                                if(oops != 0)
                                {
                                    cout << "Invalid ingredient entry" << endl;
                                    break;
                                }
                                else
                                    tempIngredientList.push_back(tempIngredientObject);
                            }
                            else
                            {
                                cout << "Enter the value, unit, and ingredient you would like to change to and press enter.\n";
                                getline(cin, s);
                                oops = tempIngredientObject.setString(s);
                                if(oops != 0)
                                {
                                    cout << "Invalid ingredient entry" << endl;
                                    break;
                                }
                                else
                                    tempIngredientList[list - 1] = tempIngredientObject;
                            }
                            R.setIngredientList(tempIngredientList);
                        }
                    }
                }
                break;
            case 3:
                //edit prep style
                cout << "Current Preperation Style:\t\t" << R.getPrepStyle() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setPrepStyle(s);
                break;
            case 4:
                //edit ice style
                cout << "Current Ice Style:\t\t" << R.getIceStyle() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setIceStyle(s);
                break;
            case 5:
                //edit garnish
                cout << "Current Garnish:\t\t" << R.getGarnish() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setGarnish(s);
                break;
            case 6:
                //edit glass
                cout << "Current Glass:\t\t" << R.getGlass() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setGlass(s);
                break;
            case 7:
                //edit instructions
                cout << "Current Instructions:\t\t" << R.getInstructions() << endl;
                cout << "Change to:";
                cin.ignore(1, '\n');
                getline(cin, s);
                R.setInstructions(s);
                break;
            default:
                cout << "You fucked up try again" << endl;
                break;
        }
        s = "";
    }
}

//saves list of all vectors full in file filename
void saveRecipe(vector<Recipe> full, string filename)
{
    vector<Ingredient> temp;
    ofstream fout(filename, ofstream::out);
    
    for(int i = 0; i < full.size(); i++)
    {
        temp = full[i].getIngredientList();
        fout << to_string(full[i].getID()) + ',';
        fout << full[i].getName() + ',';

        fout << '"';
        fout << temp[0].toString();
        for(int j = 1; i < temp.size(); i++)
        {
            fout << '\n';
            fout << temp[j].toString();
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

//prints recipe R to output stream
void printRecipe(Recipe R)
{
    vector<Ingredient> temp = R.getIngredientList();

    cout << left << setw(24) << "ID:";
    cout << to_string(R.getID()) << endl;

    cout << left << setw(24) << "Name:";
    cout << R.getName() << endl;

    cout << left << setw(24) << "Ingredient List:";
    cout << temp[0].toString() << endl;
    for(int i = 1; i < temp.size(); i++)
    {
        cout << left << setw(24) << "";
        cout << temp[i].toString() << endl;
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

//prints list of recipes in vector full to output stream
void printRecipeList(vector<Recipe> full)
{
    for(int i = 0; i < full.size(); i++)
        printRecipe(full[i]);
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
