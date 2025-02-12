#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct trieNode {
    trieNode* child[26];
    bool endKey;
    Value* record;
    trieNode(){
        for (int i=0;i<26;i++){
            child[i]=NULL;
        }
    }
};


struct Value
{
    string key;
    int gridx;
    int gridy;
    string color;
    int val1;
    float val2;
};

class Data
{
    public:
        Data();
        Data(int sizeIn);
        void Add(Value record);
        void Delete(string key);
        void LookUp(string key);
        void numberOfKey();
    private:
        int keyCount;
        trieNode* trieTable = new trieNode();
        void trieAdd(Value record);
        void trieDelete(string key);
        Value trieLookUp(string key);
        void trieNumberOfKey();

};

//constructor
Data::Data() 
{

}

// public
void Data::Add(Value record)
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
void Data::trieAdd(Value record)
{
    trieNode* current = trieTable;
    
    for (char c : record.key){
        if (current->child[c-'a']==NULL){
            trieNode* newNode = new trieNode();
            current->child[c-'a']==newNode;
        }
        current=current->child[c-'a'];
    }
    current->endKey=true;
    current->record=&record;
}

void Data::trieDelete(string key)
{

}

Value Data::trieLookUp(string key)
{

}

void Data::trieNumberOfKey()
{
    
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
    Value value;
    string data;
    while(getline(file, value.key, ','))
    {
        getline(file, data, ',');
        value.gridx = stoi(data);

        getline(file, data, ',');
        value.gridy = stoi(data);

        getline(file, value.color, ',');

        getline(file, data, ',');
        value.val1 = stoi(data);

        getline(file, data);
        value.val2 = stof(data);
        dataObject.Add(value);
    }
    file.close();
    dataObject.numberOfKey();

    // Action file if provided
    if (argc == 3)
    {
        file.open(argv[2]);
        string action;
      
        while(getline(file, action))
        {
            if (action == "add")
            {
                getline(file, data, ',');
                value.key = data;

                getline(file, data, ',');
                value.gridx = stoi(data);

                getline(file, data, ',');
                value.gridy = stoi(data);

                getline(file, value.color, ',');

                getline(file, data, ',');
                value.val1 = stoi(data);

                getline(file, data);
                value.val2 = stof(data);

                dataObject.Add(value);
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
