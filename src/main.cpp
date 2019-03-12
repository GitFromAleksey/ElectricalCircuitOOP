/*
 * main.cpp
 *
 *  Created on: 28 февр. 2019 г.
 *      Author: user1
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class Element
{
public:
    Element(){}
    Element(string name, size_t number)
    {
        this->name = name;
        this->number = number;
    }
    ~Element()
    {
        cout << "Element " << name << " destructor" << endl;
    }

    void setName(string name){ this->name = name; }

    string getName()const { return name; }

    void setNumber(size_t number) { this->number = number; }

    size_t getNumber()const { return number; }

protected:
    string name;
    size_t number;
};

class Connection : public Element
{
public:
    Connection():Element(){}
    Connection(string name, size_t number, Element *whoseMePtr):
        Element(name, number)
    {
        this->whoseMePtr = whoseMePtr;
    }
    ~Connection(){  }

    // присоединить к другому Connection-су
    bool Connect(Connection *cnct)
    {
        if(cnct == nullptr) return false;

        if( std::find(cnctPtrs.begin(), cnctPtrs.end(), cnct) == cnctPtrs.end() )
        {
            // добавляем контакт в список присоединенных контактов
            std::cout << "Conn add " << cnct->getName() << " to " << this->name << std::endl;
            cnctPtrs.push_back(cnct);
            // добавляем себя в список контактов другого контакта
            cnct->Connect(this);
            // теперь оба контакта знают, что подключены друг к другу

            return true;
        }
        return false;
    }

    void PrintAllConnections()const
    {
        if(cnctPtrs.size() == 0)
        {
            std::cout << "Print all connections: \n\tno connections" << std::endl;
            return;
        }

        std::cout << "Print all connections:" << std::endl;

        for(size_t i = 0; i < cnctPtrs.size(); i++)
        {
            std::cout << cnctPtrs[i]->getName() << std::endl;
        }
    }

    Element *WhoseAreYou()
    {
        return whoseMePtr;
    }

private:
    vector<Connection*> cnctPtrs; // список присоединённых соединений
    Element *whoseMePtr;
};


class Resistor : public Element
{
public:
    Resistor():Element("", 0)
    {
        string tmp = name + ".con1";
        this->connections.push_back( new Connection(tmp, 1, this) );
        tmp = name + ".con2";
        this->connections.push_back( new Connection(tmp, 2, this) );
        this->value = 0;
    }
    Resistor(string name, size_t number):Element(name, number)
    {
        string tmp = name + ".con1";
        this->connections.push_back( new Connection(tmp, 1, this) );
        tmp = name + ".con2";
        this->connections.push_back( new Connection(tmp, 2, this) );
        this->value = 0;
    }
    Resistor(string name, size_t number, size_t value):Element(name, number)
    {
        string tmp = name + ".con1";
        this->connections.push_back( new Connection(tmp, 1, this) );
        tmp = name + ".con2";
        this->connections.push_back( new Connection(tmp, 2, this) );
        this->value = 0;
        this->setValue(value);
    }
    ~Resistor()
    {
        for(size_t i = 0; i < connections.size(); i++)
        {
            delete connections[i];
        }
    }

    void setValue(size_t value)
        { this->value = value; }
    size_t getValue()const
        { return value; }

    bool ConnectToCon1(Connection *con)
    {
        if(con == nullptr) { return false; }

        return connections[0]->Connect(con);
    }

    void ConnectToCon2(Connection *con)
    { connections[1]->Connect(con); }

    vector<Connection*> getAllConnections()const
    {
        return connections;
    }

private:
    static const size_t sumConnections = 2; // количество контактов
    std::vector<Connection*> connections; // список указателей контактов
    size_t value; // сопротивление резистора
};




int main()
{
    cout << "Begin program..\n" << endl;

    // создаём резисторы
    Resistor res1("R1", 1, 5);
    Resistor res2("R2", 2, 78);

    std::cout << "res1.getCon1() = " << res1.getName() << std::endl;
    std::cout << "res1.getNumber() = " << res1.getNumber() << std::endl;
    std::cout << "res1.getValue() = " << res1.getValue() << std::endl;

    Connection *conRes1 = res1.getAllConnections()[0];
    Connection *conRes2 = res2.getAllConnections()[0];

    conRes1->PrintAllConnections();
    conRes2->PrintAllConnections();

    conRes1->Connect(conRes2);

    conRes1->PrintAllConnections();
    conRes2->PrintAllConnections();

    cout << "\nEnd program.." << endl;
}
