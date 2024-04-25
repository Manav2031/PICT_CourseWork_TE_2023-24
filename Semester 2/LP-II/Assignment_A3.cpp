#include <bits/stdc++.h> 
using namespace std; 

void printArray(vector<int>&arr) 
{ 
    int i; 
    for (i = 0; i < arr.size(); i++) { 
        cout << arr[i] << " "; 
        
    } cout << endl;
}

  
void selectionSort(vector<int>&arr, int n) 
{ 
    int i, j, min_idx; 
    for (i = 0; i < n - 1; i++) { 

        min_idx = i; 
        for (j = i + 1; j < n; j++) { 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
        } 
 
        if (min_idx != i) 
            swap(arr[min_idx], arr[i]); 

        cout<<"Queue after "<<i+1<<" step"<<endl;
        printArray(arr);
    }
}


int main() 
{   
    int n;
    cout <<"Enter Number of Books at the store :"<<endl;
    cin>>n;
    cout<<"Enter prices of books available in store :"<<endl;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout << "Original queue of books :"<<endl; 
    printArray(arr); 

    selectionSort(arr, n); 
    
    cout << "Queue acording to the Lowest first price :"<<endl; 
    printArray(arr); 
    return 0; 
} 
  
