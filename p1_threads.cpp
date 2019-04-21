#include "p1_threads.h"
#include "p1_process.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
/*
    vector<Node> *temp = (vector<Node> *)arg;
    vector<Node> arr = *temp;
*/

using namespace std;

int part = 0;
vector<Node> V;

vector<Node> merge(struct runner_struct* s){
    
    int index, theThread;
    int num_threads = s -> num_threads;
    //create arrThread based on num_thread
    int arrThread[ num_threads ];
    for(int i = 0; i < num_threads; i++){
        arrThread[i] = s[i].start;
    }
    
    vector<Node> ans;
    for(int i = 0; i < V.size(); i++){
        
        index = -1;

        for(int t = 0; t < num_threads; t++){
            if( arrThread[t] != s[t].end+1){
                index = arrThread[t];
                theThread = t;
                break;
            }
        }
        
        //final update
        for(int k = 0; k < num_threads; k++){
            if(arrThread[k] != s[k].end+1){
                if( V[arrThread[k]].grade < V[index].grade){
                    index = arrThread[k];
                    theThread = k;
                }
            }   
        }
        
        arrThread[theThread]++;
        ans.push_back( V[ index ] );
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
    
}

vector<Node> threadSort(vector<Node> array, int num_threads, string filename){
    
    V = array;
    
    struct runner_struct args[num_threads];
    args -> num_threads = num_threads;
    args -> filename = filename;
    args -> size = array.size();
    
    for(int i = 0; i < num_threads; i++){
        args[i].start = i*array.size()/num_threads ;
        args[i].end = (i+1)*array.size()/num_threads - 1;
    }
    
    pthread_t tid[num_threads];
    
    for(int i = 0; i < num_threads; i++){
        
        pthread_create(&tid[i], NULL, runner, &args[i]);
     }
    
    for(int i = 0; i < num_threads; i++){
        
        pthread_join(tid[i], NULL);
    }
    
    return merge(args);
}

void* runner(void* arg){
  
    struct runner_struct *arg_struct = 
        (struct runner_struct*) arg; 
    
    int start = arg_struct -> start;
    int end = arg_struct -> end;
    
    sort(V.begin()+start, V.begin()+end+1);
    
    pthread_exit(0);
}