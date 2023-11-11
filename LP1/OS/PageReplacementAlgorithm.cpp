#include <bits/stdc++.h>
using namespace std;

void FIFO(int pg[], int pn, int fn)
{
    vector <int> vec(fn,-1);
    queue <int> q;
    int hits=0;
    int faults=0;
    for(int i=0;i<pn;i++)
    {
        int inComing=pg[i];
        int cnt=0;
        for(int j=0;j<fn;j++)
        {
            if(vec[j]==-1)
            {
                q.push(inComing);
                vec[j]=inComing;
                faults++;
                break;
            }
            else if(vec[j]==inComing)
            hits++;
            else if(vec[j]!=inComing)
            cnt++;
        }
        if(cnt==fn)
        {
            int qfront=q.front();
            q.pop();
            for(int j=0;j<fn;j++)
            {
                if(vec[j]==qfront)
                {
                    vec[j]=inComing;
                    q.push(inComing);
                    faults++;
                    break;
                }
            }
        }
        for(auto it:vec)
        {
            cout<<"("<<it<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"No. of misses= "<<faults<<endl;
    cout<<"No. of hits= "<<pn-faults<<endl;
}

bool search(int key, vector <int>& fr)
{
    for(int i=0;i<fr.size();i++)
    {
        if(fr[i]==key)
        return true;
    }
    return false;
}

int predict(int pg[], vector <int>& fr, int pn, int index)
{
    int res=-1;
    int farthest=index;
    for(int i=0;i<fr.size();i++)
    {
        int j;
        for(j=index;j<pn;j++)
        {
            if(fr[i]==pg[j])
            {
                if(j>farthest)
                {
                    farthest=j;
                    res=i;
                }
                break;
            }
        }
        if(j==pn)
        return i;
    }
    return (res==-1) ? 0 : res;
}

void optimal(int pg[], int pn, int fn)
{
    vector <int> fr;
    int hits=0;
    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Frame structure of Optimal is as Follows ..."<<endl;
    for(int i=0;i<pn;i++)
    {
        if(search(pg[i],fr))
        {
            hits++;
            continue;
        }
        if(fr.size()<fn)
        fr.push_back(pg[i]);
        else
        {
            int j=predict(pg,fr,pn,i+1);
            fr[j]=pg[i];
        }
        for(auto it:fr)
        {
            cout<<"("<<it<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"No. of misses= "<<pn-hits<<endl;
    cout<<"No. of hits= "<<hits<<endl;
}

void lru(int pg[], int pn, int fn)
{
    unordered_set <int> s;
    unordered_map <int,int> indexes;
    int faults=0;
    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Frame structure of LRU is as Follows ..."<<endl;
    for(int i=0;i<pn;i++)
    {
        if(s.size()<fn)
        {
            if(s.find(pg[i])==s.end())
            {
                s.insert(pg[i]);
                faults++;
            }
            indexes[pg[i]]=i;
        }
        else
        {
            if(s.find(pg[i])==s.end())
            {
                int lru=INT_MAX,val;
                for(auto it:s)
                {
                    if(indexes[it]<lru)
                    {
                        lru=indexes[it];
                        val=it;
                    }
                }
                s.erase(val);
                s.insert(pg[i]);
                faults++;
            }
            indexes[pg[i]]=i;
        }
        for(auto it:s)
        cout<<"("<<it<<")"<<" ";
        cout<<endl;
    }
    cout<<endl;
    cout<<"No. of misses= "<<faults<<endl;
    cout<<"No. of hits= "<<pn-faults<<endl;
}

int main()
{
    int pn;
    cout<<"Enter the size of page reference string"<<endl;
    cin>>pn;
    int pg[pn];
    cout<<"Enter the pages"<<endl;
    for(int i=0;i<pn;i++)
    cin>>pg[i];
    int fn;
    cout<<"Enter the frame size"<<endl;
    cin>>fn;
    while(true)
    {
        cout<<"1. FIFO"<<endl;
        cout<<"2. Optimal"<<endl;
        cout<<"3. LRU"<<endl;
        cout<<"4. Exit"<<endl;
        int choice;
        cout<<"Enter your choice:"<<endl;
        cin>>choice;

        if(choice==1)
        FIFO(pg,pn,fn);
        else if(choice==2)
        optimal(pg,pn,fn);
        else if(choice==3)
        lru(pg,pn,fn);
        else if(choice==4)
        {
            cout<<"Thanks for using my program."<<endl;
            break;
        }
        else
        cout<<"Invalid choice. Please enter a valid number from 1 to 4."<<endl;

    }
    return 0;
}