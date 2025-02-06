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
        Value LookUp(string key);
    private:
        int size;
        vector<Value> seqData;
        int hashFunction(int key);
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
    seqAdd(record);
}

/*
void Data::Delete(string key)
{
    seqDelete(key);
}

Value Data::LookUp(string key)
{
    seqLookUp(key);
}
*/

// private

/*
int Data::hashFunction(int key)
{
}
*/

void Data::seqAdd(Value record)
{
    seqData.push_back(record);
}

/*
void Data::hashAdd(Value record)
{
}

void Data::seqDelete(string key)
{
}

void Data::hashDelete(string key)
{
}

Value Data::seqLookUp(string key)
{
}

Value Data::hashLookUp(string key)
{
}
*/

int main(int argc, char *argv[])
{
    ifstream file;

    if (argc != 3)
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
            //dataObject.LookUp(data);
        }
        else if (action == "remove")
        {
            getline(file, data);
            //dataObject.Delete(data);
        }
    }
    file.close();

    return  0;
}
