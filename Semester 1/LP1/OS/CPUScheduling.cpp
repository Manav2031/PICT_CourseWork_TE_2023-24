#include<iostream>
#include<bits/stdc++.h>
#define long long ll
using namespace std;

class processScheduling;
class job{
public:
    int id;
    int at,bt,pri,ct,wt,tat,rt;
    friend class processScheduling;
    job(){
        id=at=bt=pri=ct=wt=tat=rt=0;
    }
};
bool cmp(job a,job b){
    return a.at<b.at;
}

struct priCheck{
    bool operator()(const job& a, const job& b){
        return a.pri>b.pri;
    }
};
class processScheduling{
    vector<job> input1;
    int pros;
    public:
    processScheduling()
       {
          cout<<"Enter no of Process."<<endl;
          cin>>pros;
           vector<job> input(pros);
         //takin inout from the usert ;
          for(int i=0;i<pros;i++){
            input[i].id=i+1;
            // cout<<"Enter the arl of "<<i+1<<"th";cin>>input[i].id;
            cout<<"Enter the arrival of "<<i+1<<"th";cin>>input[i].at;
            cout<<"Enter the burst time of "<<i+1<<"th";cin>>input[i].bt;
            cout<<"Enter the priority of "<<i+1<<"th";cin>>input[i].pri;
            
            input[i].rt=input[i].bt;  // remaing time must be the burst time 
          }
          input1=input;
          
       }
       void sjfPremeptive(){
           int done=0;
           int time=0;
           vector<job> jobInput=input1;
           while(done<pros){
                
                int shortestburst=-1;
                for(int i=0;i<pros;i++){
                    if(jobInput[i].at<=time && jobInput[i].rt>0){
                        if( shortestburst==-1 || jobInput[i].rt<jobInput[shortestburst].rt){
                            shortestburst=i; // change tht  new samllet busrt process
                           //premptive :- even thought the process 
                           //is not current shortest but bt is less then its taken 
                        }
                    }
                }

                if(shortestburst==-1){
                    time++;
                    continue;  // if no process in ready queue only increment time and next iteration
                }
                
                jobInput[shortestburst].rt--;//decrease the reamianig time 
                time++;

                if( jobInput[shortestburst].rt==0){
                    done++;
                    jobInput[shortestburst].ct=time;
                }

                cout<<"|P"<<jobInput[shortestburst].id<<" ";

           }

           cout<<"\nAt\tBT\tCt\tWt\tTAt\t"<<endl;
           
           float avgtat,avgwt;
           avgtat=0;avgwt=0;

           for(int i=0;i<jobInput.size();i++){
            jobInput[i].tat=jobInput[i].ct-jobInput[i].at;
            jobInput[i].wt=jobInput[i].tat-jobInput[i].bt;
              avgtat+=jobInput[i].tat;   
              avgwt+=jobInput[i].wt;   
              cout<<jobInput[i].at<<"\t"<<jobInput[i].bt<<"\t"<<jobInput[i].ct<<"\t"<<jobInput[i].tat<<"\t"<<jobInput[i].wt<<"\n";
           }
		   avgtat=avgtat/pros;
		   avgwt=avgwt/pros;

           cout<<"avg: "<<avgtat<<" "<<avgwt;

       }
       void fcfs(){
                   vector<job> jobInput=input1;
                
                sort(jobInput.begin(),jobInput.end(),cmp);
           jobInput[0].ct=jobInput[0].at+jobInput[0].bt;
           jobInput[0].tat=jobInput[0].ct-jobInput[0].at;
           jobInput[0].wt=jobInput[0].tat-jobInput[0].bt;
        //    cout<<"|P"<<jobInput[0].id<<" ";
        cout<<jobInput[0].at<<"\t"<<jobInput[0].bt<<"\t"<<jobInput[0].ct<<"\t"<<jobInput[0].tat<<"\t"<<jobInput[0].wt<<"\n";
           float avgtat,avgwt;
           avgtat=0;avgwt=0;
           avgtat+=jobInput[0].tat;
           avgwt+=jobInput[0].wt;
           for(int i=1;i<jobInput.size();i++){
                  int maxi=max(jobInput[i].at,jobInput[i-1].ct);
                //   cout<<"|P"<<jobInput[i].id<<" ";
                  jobInput[i].ct=maxi+jobInput[i].bt;
                  jobInput[i].tat=jobInput[i].ct-jobInput[i].at;
                  jobInput[i].wt=jobInput[i].tat-jobInput[i].bt;
              avgtat+=jobInput[i].tat;   
              avgwt+=jobInput[i].wt;   
              cout<<jobInput[i].at<<"\t"<<jobInput[i].bt<<"\t"<<jobInput[i].ct<<"\t"<<jobInput[i].tat<<"\t"<<jobInput[i].wt<<"\n";
          
           }
           avgtat=avgtat/pros;
            avgwt=avgwt/pros;
           cout<<"avg: "<<avgtat<<" "<<avgwt; 

       }

       void rr(int qt){
            vector<job> jobInput=input1;
            sort(jobInput.begin(),jobInput.end(),cmp); // sort on the basis of arrival time ;
            
            int time=0;
            vector<job> temp;
            queue<job> q;
            while(!q.empty() || !jobInput.empty()){
                //cond for if process in input or in ready queue.

                while(!jobInput.empty() && jobInput.front().at<=time){
                    //cond for if any process is arrived when the execution in 1 qt is going on.
                    q.push(jobInput.front());
                    jobInput.erase(jobInput.begin());
                    //enqueue in readyQueue.
                }

                if(!q.empty()){
                    // if any process in ready queue or not 
                    job cur=q.front();//get the first ready process
                    q.pop();

                    int executiontime=min(qt,cur.rt);
                    time+=executiontime;
                    cur.rt-=executiontime;
                    cout<<"|P "<<cur.id<<"\t";

                    //for the process arived during curents execution:
                    while(!jobInput.empty() && jobInput.front().at<=time){
                        q.push(jobInput.front());
                        jobInput.erase(jobInput.begin());
                    }

                    if(cur.rt>0){
                        q.push(cur);
                    }
                    else{
                        cur.ct=time;
                        temp.push_back(cur);
                    }
                }
                else{
                    time++;
                }
            }
            jobInput=temp;

            cout<<"\nAt\tBT\tCt\tWt\tTAt\t"<<endl;
           
           float avgtat,avgwt;
           avgtat=0;avgwt=0;

           for(int i=0;i<jobInput.size();i++){
            jobInput[i].tat=jobInput[i].ct-jobInput[i].at;
            jobInput[i].wt=jobInput[i].tat-jobInput[i].bt;
              avgtat+=jobInput[i].tat;   
              avgwt+=jobInput[i].wt;   
              cout<<jobInput[i].at<<"\t"<<jobInput[i].bt<<"\t"<<jobInput[i].ct<<"\t"<<jobInput[i].tat<<"\t"<<jobInput[i].wt<<"\n";
           }
            avgtat=avgtat/pros;
            avgwt=avgwt/pros;
           cout<<"avg: "<<avgtat<<" "<<avgwt; 

       }
       
       void pri(){
            vector<job> jobInput=input1;
            vector<job> temp;
            sort(jobInput.begin(), jobInput.end(),cmp);
            priority_queue<job,vector<job>, priCheck > q;
            int time=0;  
            while(!q.empty() || !jobInput.empty()){
                //cond for if process in input or in ready queue.

                while(!jobInput.empty() && jobInput.front().at<=time){
                    //cond for if any process is arrived when the execution in 1 qt is going on.
                    q.push(jobInput.front());  
                    jobInput.erase(jobInput.begin());
                    //enqueue in readyQueue.
                }

                if(!q.empty()){
                    // if any process in ready queue or not 
                    job cur=q.top();//get the first ready process
                    q.pop();

                    time+=cur.bt;
                    cout<<"|P "<<cur.id<<"\t";

                    //for the process arived during curents execution:
                    while(!jobInput.empty() && jobInput.front().at<=time){
                        q.push(jobInput.front());
                        jobInput.erase(jobInput.begin());
                    }

                        cur.ct=time;
                        temp.push_back(cur);
                    
                }
                else{
                    time++;
                }
            }
            jobInput=temp;
             cout<<"\nAt\tBT\tCt\tWt\tTAt\t"<<endl;
           
           float avgtat,avgwt;
           avgtat=0;avgwt=0;

           for(int i=0;i<jobInput.size();i++){
            jobInput[i].tat=jobInput[i].ct-jobInput[i].at;
            jobInput[i].wt=jobInput[i].tat-jobInput[i].bt;
              avgtat+=jobInput[i].tat;   
              avgwt+=jobInput[i].wt;   
              cout<<jobInput[i].at<<"\t"<<jobInput[i].bt<<"\t"<<jobInput[i].ct<<"\t"<<jobInput[i].tat<<"\t"<<jobInput[i].wt<<"\n";
           }
            avgtat=avgtat/pros;
            avgwt=avgwt/pros;
           cout<<"avg: "<<avgtat<<" "<<avgwt; 

       }

};
int main()
{  
    processScheduling p1;
    p1.sjfPremeptive();
    p1.rr(2);
    p1.fcfs();
    p1.pri();

    return 0;
}