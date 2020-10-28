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
std::string RACE(int inode,int block,int pc,int curTime){
    std::vector<FHash*> F;
    std::vector<PHash*> P;
    int check=0;
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
                    return "looping";
                }
            }
        }
    }
    //line 12
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
            f->inode=inode; f->start=f->end;
            f->end=block; f->lastTime=curTime;
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
            return "Looping";
        }
    }
    for (auto p : P)
    {
        if(p->fresh>threshold)
        {
            return "Sequential";
        }
    }
    return "Other";

}

int main()
{
    return 0;
}