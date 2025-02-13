#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
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
    trieNode() : endKey(false), record(nullptr) {
        for (int i=0;i<26;i++){
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
        trieNode* trieTable = new trieNode();
        void trieAdd(Value* record);
        void trieDelete(string key);
        Value trieLookUp(string key);
        void trieNumberOfKey();

};

//constructor
Data::Data() 
{

}

// public
void Data::Add(Value* record)
{
    // seqAdd(record);
    trieAdd(record);
}

void Data::Delete(string key)
{
    // seqDelete(key);
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
    // seqNumberOfKey();
    trieNumberOfKey();
}

// private
void Data::trieAdd(Value* record)
{
    trieNode* current = trieTable;
    for (char c : record->key){
        if (current->child[c-'a']==nullptr){
            trieNode* newNode = new trieNode();
            current->child[c-'a']=newNode;
        }
        current=current->child[c-'a'];
    }
    if (current->endKey==true){
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
    cout << key << endl;
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
    dataObject.numberOfKey();

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
