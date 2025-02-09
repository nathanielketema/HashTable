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
        int size;
        vector<Value> seqData;
        vector< list<Value> > hashTable;
        int hashFunction(string key);
        void seqAdd(Value record);
        void hashAdd(Value record);
        void seqDelete(string key);
        void hashDelete(string key);
        Value seqLookUp(string key);
        Value hashLookUp(string key);
};

Data::Data() { size = 100; }

Data::Data(int sizeIn) { size = sizeIn; }

// public
void Data::Add(Value record)
{
    // seqAdd(record);
    hashAdd(record);
}

void Data::Delete(string key)
{
    // seqDelete(key);
    hashDelete(key);
}

void Data::LookUp(string key)
{
    Value record = hashLookUp(key);
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

// private
void Data::seqAdd(Value record)
{
    for (int i = 0; i < seqData.size(); i++)
    {
        if (seqData[i].key == record.key)
        {
            seqData[i] = record;
            return;
        }
    }

    seqData.push_back(record);
}


void Data::seqDelete(string key)
{
    for (auto it = seqData.begin(); it != seqData.end();)
    {
        if (key == it->key)
            it = seqData.erase(it);
        else
            it++;
    }
}

Value Data::seqLookUp(string key)
{
    for (int i = 0; i < seqData.size(); i++)
    {
        if (key == seqData[i].key)
            return seqData[i];
    }

    return {};
}

void Data::numberOfKey()
{
    cout << "Total key entry: " << seqData.size() << endl;
}

int Data::hashFunction(string key)
{
    int hash = 0;
    int len = key.length();

    for (int i = 0; i < len; i++)
        hash = (31 * hash + key[i]) % size;

    return hash;
}

void Data::hashAdd(Value record)
{
    int index = hashFunction(record.key);
    for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it)
    {
        if (it->key == record.key)
        {
            *it = record;
            return;
        }
    }

    hashTable[index].push_back(record);
}

void Data::hashDelete(string key)
{
    int index = hashFunction(key);
    for (auto it = hashTable[index].begin(); it != hashTable[index].end();)
    {
        if (it->key == key)
            it = hashTable[index].erase(it);
        else
            it++;
    }
}

Value Data::hashLookUp(string key)
{
    int index = hashFunction(key);
    for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it)
    {
        if (it->key == key)
            return *it;
    }

    return {};  
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
        while(getline(file, action, ','))
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
            else if (action == "search")
            {
                getline(file, data);
                dataObject.LookUp(data);
            }
            else if (action == "remove")
            {
                getline(file, data);
                dataObject.Delete(data);
            }
        }
        file.close();
    }

    return  0;
}
