#include <cstdio>
#include <string>
std::string Race(int inode,int block,int pc,int curTime);
#include <iostream>
#include <string>
#include<list>
#include <algorithm>

struct Fdata{
public:

    int inode;
    int lastTime;
    int block;
    int start;
    int end;
    int period;

};
struct Pdata{
public:

    int PC;
    int fresh;
    int reused;
    int period;
    int inode;
    int block;
    int curTime;

};


class FHash
{
    int BUCKET;    // No. of buckets

    std::list<Fdata*> *table{};
public:
    explicit FHash(int b);

    void insertItem(Fdata* data);

    void deleteItem(Fdata* Value) ;

    int hashFunction(Fdata* x) const {
        return (x->lastTime % BUCKET);
    }

    bool searchItem(Fdata* key);
    void displayHash();

    bool findInode(int inode);
    int getInode(int inode);
    bool verify(int block, int i);
    int getStart(int i);
    int getPeriod(int i);
    int getLastTime(int i);
    void setPeriod(int i, int value);
};

FHash::FHash(int b)
{
    this->BUCKET = b;
    table = new std::list<Fdata*>[BUCKET];
}

void FHash::insertItem(Fdata* data)
{
    int index = hashFunction(data);
    table[index].push_back(data);
}

void FHash::deleteItem(Fdata* Value)
{
    // get the hash index of key
    int index = hashFunction(Value);

    // find the key in (index)th list
    std::list <Fdata*> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == Value)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

// function to display hash table
void FHash::displayHash()  {
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i])
            std::cout << " --> " << x;
        std::cout << std::endl;
    }
}

bool FHash::searchItem(Fdata* key)
{
    int index = hashFunction(key);
    std::list <Fdata*> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key)
            break;
        else
            return false;
    }
    if (i != table[index].end())
        return true;
    return false;
}
bool FHash::findInode(int inode)  {
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i]) {
            if (x->inode == inode) { return true; }
        }
    }
    return false;
}
int FHash::getInode(int inode){
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i]) {
            if (x->inode == inode) { return i; }
        }
    }
    return -1;
}

bool FHash::verify(int block, int i){
    for(auto x : table[i]) {
            if (x->start <= block && x->end >= block) { return true; }
        }
    return false;
}
int FHash::getStart(int i){
    for (auto x : table[i]) {
         return x->start;
    }
    return -1;
}
void FHash::setPeriod(int i, int value){
    for (auto x : table[i]) {
        x->period = value;
    }
}
int FHash::getPeriod(int i){
    for (auto x : table[i]) {
        return x->period;
    }
    return -1;
}
int FHash::getLastTime(int i){
    for (auto x : table[i]) {
        return x->lastTime;
    }
    return -1;
}


class PHash
{
    int BUCKET;    // No. of buckets

    std::list<Pdata*> *table{};
public:
    explicit PHash(int b);
    void insertItem(Pdata* data);
    void deleteItem(Pdata* Value) ;

    int hashFunction(Pdata* x) const {
        return (x->PC % BUCKET);
    }

    bool searchItem(Pdata* key);
    void displayHash();

    bool findInode(int inode);
    int getInode(int inode);
    int getPeriod(int i);
    void setPeriod(int i, int value);
};
PHash::PHash(int b)
{
    this->BUCKET = b;
    table = new std::list<Pdata*>[BUCKET];
}

void PHash::insertItem(Pdata* data)
{
    int index = hashFunction(data);
    table[index].push_back(data);
}

void PHash::deleteItem(Pdata* Value)
{
    // get the hash index of key
    int index = hashFunction(Value);

    // find the key in (index)th list
    std::list <Pdata*> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == Value)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

// function to display hash table
void PHash::displayHash()  {
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i])
            std::cout << " --> " << x;
        std::cout << std::endl;
    }
}

bool PHash::searchItem(Pdata* key)
{
    int index = hashFunction(key);
    std::list <Pdata*> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key)
            break;
        else
            return false;
    }
    if (i != table[index].end())
        return true;
    return false;
}
bool PHash::findInode(int inode)  {
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i]) {
            if (x->inode == inode) { return true; }
        }
    }
    return false;
}
int PHash::getInode(int inode){
    for (int i = 0; i < BUCKET; i++) {
        std::cout << i;
        for (auto x : table[i]) {
            if (x->inode == inode) { return i; }
        }
    }
    return -1;
}


void PHash::setPeriod(int i, int value){
    for (auto x : table[i]) {
        x->period = value;
    }
}
int PHash::getPeriod(int i){
    for (auto x : table[i]) {
        return x->period;
    }
    return -1;
}


std::string Race(int inode,int block,int pc,int curTime)
{
    FHash F(5);
    PHash P(5);
    Pdata D{};
    D.PC=pc;
    D.block=block;
    D.curTime=curTime;
    D.inode=inode;
    if(!P.searchItem(&D))   {   P.insertItem(&D);   }
    int lastTime;
    if(F.findInode(inode)&& F.verify(block,F.getInode(inode)))
    {
        int i=F.getInode(inode);
        lastTime=curTime - (block - F.getStart(i));
        //let us say α=a in our code be 0.5
        double a= 0.5;
        int setVal=a*F.getPeriod(i)+(1-a)*(lastTime-F.getLastTime(i) ) ;
        F.setPeriod(i,setVal);
    }
}

int main ()
{

}