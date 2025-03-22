#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Value
{
    string key;
    int gridx;
    int gridy;
    string color;
    int val1;
    float val2;
};

struct trieNode {
    trieNode* child[26];
    bool endKey;
    Value* record;
    trieNode() : endKey(false), record(nullptr) { //constructor for the function
        for (int i=0;i<26;i++){                   //everytime it makes a new trieNode, this code happens
            child[i]=nullptr;
        }
    }
};

class Data
{
    public:
        Data();
        Data(int sizeIn);
        void Add(Value* record);
        void Delete(string key);
        void LookUp(string key);
        void numberOfKey();
    private:
        int keyCount;
        trieNode* trieTable;
        void trieAdd(Value* record);
        void trieDelete(string key);
        Value trieLookUp(string key);
        void trieNumberOfKey();

};

//constructor
Data::Data() 
{
    keyCount=0;
    trieTable = new trieNode();
}

// public
void Data::Add(Value* record)
{
    trieAdd(record);
}

void Data::Delete(string key)
{
    trieDelete(key);
}

void Data::LookUp(string key)
{
    Value record = trieLookUp(key);
    if (!record.key.empty())
    {
        cout << "Key (" << key <<") found!" << endl;
        cout << "    gridx: " << record.gridx << endl;
        cout << "    gridy: " << record.gridy << endl;
        cout << "    color: " << record.color << endl;
        cout << "    val1: " << record.val1 << endl;
        cout << "    val2: " << record.val2 << endl;
    }
    else
        cout << "Key (" << key <<") not found!" << endl;
}

void Data::numberOfKey()
{
    trieNumberOfKey();
}

// private
void Data::trieAdd(Value* record)
{
    trieNode* current = trieTable;
    for (char c : record->key){
        if (current->child[c-'a']==nullptr){ //"c" is the character, - 'a' gets you the askii values.
            trieNode* newNode = new trieNode();
            current->child[c-'a']=newNode;
        }
        current=current->child[c-'a'];
    }
    if (current->endKey==true){ //if a record already exists
        current->record=record;
    } else {
        current->record=record;
        keyCount++;
        current->endKey=true;
    }
    
}

void Data::trieDelete(string key)
{
    trieNode* current = trieTable;
    int i=0;
    for (char c : key){
        if (current->child[c-'a']==nullptr){
            cout << "Key ("<< key << ") not found in list" << endl;
            return;
        }
        current=current->child[c-'a'];
    }
    if (current->endKey==false){
        cout << "Key ("<< key << ") not found in list" << endl;
    } else {
        cout << "Key (" << key << ") removed from list" << endl;
        current->endKey=false;
        delete current->record;
        current->record=nullptr;
        keyCount--;
    }
}

Value Data::trieLookUp(string key)
{
    trieNode* current = trieTable;
    for (char c : key){
        if (current->child[c-'a']==nullptr){
            return {};
        }
        current=current->child[c-'a'];
    }
    if (current->endKey==true){
        return *current->record;
    } else {
        return {};
    }


}

void Data::trieNumberOfKey()
{
    cout << "Total key entry: " << keyCount << endl;
}

int main(int argc, char *argv[])
{
    ifstream file;

    if (argc < 2)
    {
        cout << "Error: file not provided!" << endl;
        return 1;
    }
    file.open(argv[1]);

    Data dataObject;
    string key;
    string data;
    while(getline(file, key, ','))
    {
        Value* newValue = new Value();
        newValue->key=key;
        getline(file, data, ',');
        newValue->gridx = stoi(data);

        getline(file, data, ',');
        newValue->gridy = stoi(data);

        getline(file, newValue->color, ',');

        getline(file, data, ',');
        newValue->val1 = stoi(data);

        getline(file, data);
        newValue->val2 = stof(data);
        dataObject.Add(newValue);
    }
    file.close();

    // Action file if provided
    if (argc == 3)
    {
        file.open(argv[2]);
        string action;
      
        while(getline(file, action, ' '))
        {
            Value* newValue = new Value();
            if (action == "add")
            {
                getline(file, data, ',');
                newValue->key = data;

                getline(file, data, ',');
                newValue->gridx = stoi(data);

                getline(file, data, ',');
                newValue->gridy = stoi(data);

                getline(file, newValue->color, ',');

                getline(file, data, ',');
                newValue->val1 = stoi(data);

                getline(file, data);
                newValue->val2 = stof(data);

                dataObject.Add(newValue);
            }
            else if (action == "lookup")
            {
                getline(file, data);
                dataObject.LookUp(data);
            }
            else if (action == "delete")
            {
                getline(file, data);
                dataObject.Delete(data);
            }
        }
        file.close();
        dataObject.numberOfKey();
    }

    return  0;
}
