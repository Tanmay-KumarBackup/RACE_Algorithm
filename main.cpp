#include <cstdio>
#include <iostream>
#include <vector>
#define INFINITE 9999
#define a 0.5
struct FHash{
    int inode,start,end,lastTime,period;
};
struct PHash{
    int pc,fresh,reused,period;
};
struct DoubleReturn{
    std::string stringValue;
    int intValue=0;
};
int threshold;
struct Input{
    int inode , block , pc , curTime;
};

//here Race is going to act as a partition allocator
DoubleReturn RACE(int inode,int block,int pc,int curTime){
    std::vector<FHash*> F;
    std::vector<PHash*> P;
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
        PHash temp{};
        temp.pc=pc,temp.fresh=0,temp.reused=0,temp.period=INFINITE;
        P.push_back(&temp);
    }
    //line 4
    int lastTime;
    for (auto f : F) {
        if (f->inode == inode && f->start <= block <= f->end) {
            lastTime = curTime - (block - f->start);//{consider "ghost" reference time of the 1st block}
            f->period = a * f->period + (1 - a) * (lastTime - f->lastTime);//exponential average
            for (auto p : P) {
                if (p->pc == pc) {
                    p->reused++;
                    p->fresh--;
                    p->period = a * f->period + (1 - a) * p->period;//exponential average
                    //update last reference time of the 1st block;

                    if ()//access direction is reversed
                    {
                        f->lastTime = lastTime;
                    }
                    Return.stringValue= "looping";
                    Return.intValue=f->period;
                    return Return;
                }
            }
        }
    }

    for(auto f : F)
    {
        if(f->inode==inode && f->end==block-1)
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
            FHash *f1;
            f1->inode=inode; f1->start=f->end;
            f1->end=block; f1->lastTime=curTime;
            f->period=INFINITE;
            F.push_back(f);
            for (auto p : P)
            {
                if(p->pc==pc)
                {
                    p->fresh++;
                    break;
                }
            }
        }
    }
    for (auto p : P)
    {
        if(p->reused>=p->fresh)
        {
            Return.stringValue= "Looping";
            Return.intValue= p->period;
            return Return;
        }
    }
    for (auto p : P)
    {//line number 21
        if(p->fresh>threshold)//threshold is not defined
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
    int bufferCache;
    printf("Enter the size of Buffer cache:\t");
    scanf("%d",&bufferCache);

    int blockNum;
    printf("Enter total number of blocks that you wish to enter: ");
    scanf("%d",&blockNum);
    std::vector<Input*> inputArray;
    printf("Inode  |  Block  |  PC  |  curTime  |\n");
    for(int i=0;i<blockNum;i++)
    {
        Input temp{};
        scanf("%d %d %d %d",&temp.inode,&temp.block,&temp.pc,&temp.curTime);
        inputArray.push_back(&temp);
    }
    for(auto Inp : inputArray)
    {
        DoubleReturn rr;
        rr =RACE(Inp->inode,Inp->block,Inp->pc,Inp->curTime);
    }
    return 0;
}
/*Yifeng Zhu, et.al.[25] proposed a Robust
Adaptive buffer Cache management scheme
(RACE). In this scheme cache is partitioned by
using marginal gain function to allocate blocks
according to its access pattern. To know block
access pattern it keeps track of references to a
block by using file hash table and PC hash table.
File hash table uses attributes such as inode, start
and end block number, the last access made to the
first block, looping period, last access to the
referenced block, last accessed block and a PC
hash table uses attributes such as fresh counter,
reuse counter. After pattern detection block is
allocated into cache if free space is available or
replacement is done with the existing replacement
policy which is best suitable for the detected
access pattern.
 */