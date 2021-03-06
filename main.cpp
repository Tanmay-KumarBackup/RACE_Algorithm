#include <cstdio>
#include <iostream>
#include <vector>
#define INFINITE 9999
#define a 0.5
struct FHash{
    int inode,start,end,lastTime,period;
    bool ghostRef= false;
};
struct PHash{
    int pc,fresh,reused,period;
};
struct DoubleReturn{
    std::string stringValue;
    int intValue=0;
};
int threshold=0;
struct Input{
    int inode , block , pc , curTime;
};


std::vector<FHash*> F;
std::vector<PHash*> P;
//here Race is going to act as a partition allocator
int findsP( PHash p){
    int i=0;
    for(auto x : P)
    {
        if(x==&p)
        {
            return i;
        }
        i++;
    }
    return -1;
}
int *lastCalled= nullptr;
DoubleReturn RACE(int inode,int block,int pc,int curTime, int &countForGhost){

    if(F.empty())
    {
        FHash *f = new FHash;
        f->start=block;
        f->end=block;
        f->lastTime=curTime;
        f->inode=inode;
        f->period=INFINITE;
        F.push_back(f);
    }

    if(P.empty())
    {
        PHash *temp=new PHash;
        temp->pc=pc;
        temp->fresh=0;
        temp->reused=0;
        temp->period=INFINITE;
        P.push_back(temp);
        DoubleReturn rr;
        rr.intValue=-1;
        rr.stringValue="Add more Values";
        return rr;
    }

    int check=0;
    DoubleReturn Return;
    //line 3
    for (auto i : P)
    {
        if(pc==i->pc){
            check =1;
            break;
        }
    }
    //now inserting PC
    if(check==0)
    {
        PHash *temp=new PHash;
        temp->pc=pc,temp->fresh=0,temp->reused=0,temp->period=INFINITE;
        P.push_back(temp);
    }
    //line 4

    int lastTime;
    for (auto f : F) {
        if (f->inode == inode && f->start <= block <= f->end && !f->ghostRef) {
            lastTime = curTime - (block - f->start);
            if(countForGhost==0)
            {
                f->ghostRef = true;
                countForGhost++;
                break;
            }
            //{consider "ghost" reference time of the 1st block}

            f->period = a * f->period + (1 - a) * (lastTime - f->lastTime);//exponential average
            for (auto p : P) {
                if (p->pc == pc) {
                    p->reused++;
                    p->fresh--;
                    p->period = a * f->period + (1 - a) * p->period;//exponential average
                    //updating last reference time of the 1st block;
                    int index1=findsP(*p);
                    if (index1<*lastCalled)//access direction is reversed
                    {
                        f->lastTime = lastTime;
                    }
                    Return.stringValue= "looping";
                    Return.intValue=f->period;
                    int index=findsP(*p);
                    lastCalled=&index;
                    return Return;
                }
            }
        }
    }

    for(auto f : F)
    {
        if(f->inode==inode && f->end==block-1 && !f->ghostRef)
        {
            f->end=block;
            for (auto p : P)
            {
                if(p->pc==pc)
                {
                    p->fresh++;
                    break;
                }
            }
        }
        else {
            FHash *f1=new FHash;
            f1->inode=inode; f1->start=block;
            f1->end=block; f1->lastTime=curTime;
            f1->period=INFINITE;
            F.push_back(f1);
            for (auto p : P)
            {
                if(p->pc==pc)
                {
                    p->fresh++;
                    break;
                }
            }
            break;
        }
    }
    for (auto p : P)
    {
        if(p->pc==pc && p->reused>=p->fresh)
        {
            Return.stringValue= "looping";
            Return.intValue= p->period;
            return Return;
        }
    }
    for (auto p : P)
    {//line number 21
        if(p->pc==pc && p->fresh>threshold)//threshold is not defined
        {
            Return.stringValue= "Sequential";
            Return.intValue= 0;
            return Return;
        }
    }
    Return.stringValue="Other";
    Return.intValue=0;
    return Return;
}

int main()
{
    float bufferCache;
    printf("Enter the size of Buffer cache:\t");
    scanf("%f",&bufferCache);

    int response;
    printf("press 1 to enter values press 2 to exit : ");
    scanf("%d",&response);
    int countLoop=0;
    int countSequence=0;
    int countOther = 0;
    while(response==1) {
        std::vector<Input *> inputArray;
        printf("Inode  |  Block  |  PC  |  current time  |\n");
        Input temp{};
        scanf("%d %d %d %d", &temp.inode, &temp.block, &temp.pc, &temp.curTime);
        inputArray.push_back(&temp);

        int blockCount = 0;

        for (auto Inp : inputArray) {
            DoubleReturn rr;
            rr = RACE(Inp->inode, Inp->block, Inp->pc, Inp->curTime, blockCount);
            if(rr.stringValue=="Add more Values")
            {
                printf(" Add more Values...\n");

            }
            else if(rr.stringValue=="looping")
            {
                printf(" Reference detected is: Looping");
                printf("\n Period is %d\n",rr.intValue);
                countLoop++;
            }
            else if (rr.stringValue=="Sequential")
            {
                printf(" Reference detected is: Sequential");
                printf("\n Period is %d\n",rr.intValue);
                countSequence++;
            }
            else if (rr.stringValue=="Other")
            {
                printf(" Reference detected is: Other");
                countOther++;
            }
        }
        printf("press 1 to enter values press 2 to exit : ");
        scanf("%d",&response);
    }
    int total =countLoop+countOther+countSequence;
    printf("Partition of cache for Loop reference:  %2f\n "
           "for Sequence reference: %2f\n"
           "for Others: %2f\n",bufferCache*countLoop/total,
           bufferCache*countSequence/total,
           bufferCache*countOther/total);

    printf("Exiting...\n");

    return 0;
}