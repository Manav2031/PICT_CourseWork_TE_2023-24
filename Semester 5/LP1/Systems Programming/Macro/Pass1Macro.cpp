#include<bits/stdc++.h>
using namespace std;

int main(){

    ifstream fin;
    fin.open("source.txt");

    ofstream mntout,kpdtout,pntout,mdtout,fout;
    mntout.open("MNT.txt");
    mdtout.open("MDT.txt");
    kpdtout.open("KPDTAB.txt"); 
    pntout.open("PNTAB.txt");
    fout.open("output.txt");

    vector<array<string,5>> mnt;
    vector<pair<string,string>> kpdt;
    map<string,int> pnt;

    int mdtptr = 1;
    bool macroStart = false,started = false;
    string line,word;

    while(getline(fin,line)){
        stringstream ss(line);

        ss >> word;

        if(word == "MACRO"){
            macroStart = true;
            continue;
        }

        if(macroStart){
            array<string,5> temp;
            mnt.push_back(temp);
            int i = mnt.size() - 1;

            mnt[i][0] = word;
            mnt[i][3] = to_string(mdtptr);

            pntout << "PNTAB for " << word << "\n";

            int pp = 0,kp = 0;
            while(ss >> word){
                word = word.substr(1);
                if(word[word.size() - 1] == ',')
                    word = word.substr(0,word.size()-1);

                int kpidx = -1;
                for(int i = 0;i < word.size();i++){
                    if(word[i] == '='){
                        kpidx = i;
                        break;
                    }
                } 

                if(kpidx != -1){
                    kp++;
                    pair<string,string> pr = {word.substr(0,kpidx),word.substr(kpidx + 1)};
                    kpdt.push_back(pr);

                    pnt[pr.first] = pnt.size() + 1;
                    pntout << pnt[pr.first] << "\t" << pr.first << "\n";
                }
                else{
                    pp++;

                    pnt[word] = pnt.size() + 1;
                    pntout << pnt[word] << "\t" << word << "\n";
                }       
            }

            mnt[i][1] = to_string(pp);
            mnt[i][2] = to_string(kp);
            if(kp > 0) mnt[i][4] = to_string(kpdt.size() - kp + 1);

            macroStart = false;
            continue;
        }

        if(word == "MEND"){
            mdtout << "MEND" << "\n";
            pnt.clear();
        }
        else{
            mdtout << word << " ";
            
            bool first = true;
            while(ss >> word){
                if(!first){
                    mdtout << ", ";
                }

                if(word[0] == '&'){
                    word = word.substr(1);
                    if(word[word.size() - 1] == ',')
                        word = word.substr(0,word.size()-1);

                    mdtout << "(P," << pnt[word]  << ")";
                }
                else{
                    if(word[word.size() - 1] == ',')
                        word = word.substr(0,word.size()-1);
                    mdtout << word << " ";
                }
                first = false;   
            }
            mdtout << "\n";
        }

        mdtptr++;
        
    }

    for(int i = 0;i < mnt.size();i++){
        for(int j = 0;j < 5;j++){
            cout << mnt[i][j] << " ";
            mntout << mnt[i][j] << " ";
        }
        cout << "\n";
        mntout << "\n";
    }

    for(int i = 0;i < kpdt.size();i++){
        kpdtout << kpdt[i].first << " " << kpdt[i].second << "\n";
    }


    return 0;
}