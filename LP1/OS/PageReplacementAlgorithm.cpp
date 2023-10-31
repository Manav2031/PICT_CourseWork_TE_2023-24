#include<bits/stdc++.h>
using namespace std;

void FIFO(int pg[] ,int pn ,int  fn){

    // vector<vector<int>>vec(fn ,vector<int> (fn ,-1));
    vector<int>vec(fn,-1);
    queue<int>q;

    int faults=0;
    int hit=0;

    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Frame structure of FIFO is as Follows ..."<<endl;
    for(int i=0;i<pn;i++){

        int inComing= pg[i];
        int cnt=0;

        for(int j=0;j<fn;j++){
            if(vec[j]==-1){
                q.push(inComing);
                vec[j]=inComing;
                faults++;
                break;
            }
            else if(vec[j]==inComing){
                hit++;
            }
            else if(inComing != vec[j]){
                cnt++;
            }
        }

        if(cnt==fn){
            int qfront = q.front();q.pop();

            for(int j=0;j<fn;j++){
                if(vec[j] == qfront){
                    vec[j] = inComing;
                    q.push(inComing);
                    faults++;
                    break;
                }
            }
        }

        for(auto it:vec){
            cout<<"("<<it<<")"<<" ";
        }
        cout<<endl;
        
    }
    cout<<endl;
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
    
}


bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(int pg[], vector<int>& fr, int pn, int index)
{
    
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
 
       
        if (j == pn)

        return i;
    }
    
    return (res == -1) ? 0 : res;
}

void optimal(int pg[] ,int pn ,int  fn){

    vector<int> fr;
 
    
    int hit = 0;
    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Frame structure of Optimal is as Follows ..."<<endl;
    for (int i = 0; i < pn; i++) {
 
        if (search(pg[i], fr)) {
            hit++;
            continue;
        }
 
   
        if (fr.size() < fn)
            fr.push_back(pg[i]);
 
        
        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }

        for(auto it:fr){
            cout<<"("<<it<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;


}

void lru(int pg[], int pn, int fn) 
{ 
   
    unordered_set<int> s; 
    unordered_map<int, int> indexes; 
  
    
    int page_faults = 0; 
    cout<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Frame structure of LRU is as Follows ..."<<endl;
    for (int i=0; i<pn; i++) 
    { 

        if (s.size() < fn) 
        { 
            
            if (s.find(pg[i])==s.end()) 
            { 
                s.insert(pg[i]); 
  
                page_faults++; 
            } 
  
            indexes[pg[i]] = i; 
        } 
        else
        { 
         
            if (s.find(pg[i]) == s.end()) 
            { 
                 
                int lru = INT_MAX, val; 
                for (auto it:s) 
                { 
                    if (indexes[it] < lru) 
                    { 
                        lru = indexes[it]; 
                        val = it; 
                    } 
                } 
  
                s.erase(val); 
    
                s.insert(pg[i]); 
  
                page_faults++; 
            } 
  
          
            indexes[pg[i]] = i; 
        } 

        for(auto it:s){
            cout<<"("<<it<<")"<<" ";
        }
        cout<<endl;
    } 
    cout<<endl;
    cout << "No. of hits = " << pn-page_faults << endl;
    cout << "No. of misses = " << page_faults << endl;
    cout<<endl;
} 

int main(){

    int pg[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int pn = 20; 
    int fn = 3 ; 
    FIFO(pg,pn, fn);
    optimal(pg,pn, fn);
    lru(pg,pn, fn);

    return 0;
}