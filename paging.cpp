#include <iostream>
#include <queue>
#include <random>
#include <vector>
using namespace std;
//Ryeem Zia LAB 2 Spring 2021 
class pages{
    public:
        int number = 0;
        int framenum;
};
class frame{
    public:
        int framenum;
        int page = -1;
        int count = 0;
};
void Fifo(){

}

int main(){
    int algo;
    int fcount;
    int k = 5;
    cout << "Enter 0 for FIFO, 1 for LRU, 2 for Second Chance:\n";
    cin >> algo;
    cout << "Enter number of frames: \n";
    cin >> fcount;
    int numHits = 0;
    int numMisses = 0;
    long nums[1000];
    //int sim = 0;
    for(int i = 0; i< 1000; i ++){
        nums[i] = (random() % 100);
    }
    //cout << " \n";
    int refCount[10];
    for(int i = 0; i < 10; i++){
        refCount[i] = 0;
    }
    for(int i = 0; i < 1000; i++){
        int n = nums[i];
        if(n >= 0 && n < 1 ){
            nums[i] = 0;
           
        }
        else if(n >= 1 && n < 4){
            nums[i] = 1;
            
        }
        else if(n >= 4 && n < 9){
            nums[i] = 2;
            
        }
        else if(n >= 9 && n < 16){
            nums[i] = 3;
           
        }
        else if(n >= 16 && n < 25){
            nums[i] = 4;
           
        }
        else if(n >= 25 && n < 36){
            nums[i] = 5;
           
        }
        else if(n >= 36 && n < 49){
            nums[i] = 6;
         
        }
        else if(n >= 49 && n < 64){
            nums[i] = 7;
           
        }
        else if(n >= 64 && n < 81){
            nums[i] = 8;
           
        }
        else if(n >= 81 && n < 100){
            nums[i] = 9;
            
        }
        refCount[nums[i]] += 1; 
    }
    if(algo == 0){
        cout << "Algo is FIFO \n";
        cout << "Frames: " << k << "\n";
        int frameNum[k];
        queue<frame> frameWait;
        for(int i = 0; i< k; i ++){
            frame newFrame;
            newFrame.framenum = i;
            frameWait.push(newFrame);
        }
        ///Simulation
        int currFrame = 0;
        int currRef = 0;
        int currWait = 0;
        int numEvicts = 0;
        queue<frame> frames;
        for(int i = 0; i < 1000; i++){
            currRef = nums[i];
            if(frames.empty()){
                frame curr = frameWait.front();
                frameWait.pop();
                curr.page = currRef;
                curr.framenum = currFrame;
                frames.push(curr);
                currFrame ++;
            }
            else if(frames.front().page == currRef){
                numHits++;
            }
            else if(frames.front().page != currRef){
                numMisses++;
                if(frameWait.empty()){
                    frame curr = frames.front();
                    frames.pop();
                    curr.page = currRef;
                    frames.push(curr);
                }
                else{
                    frame curr = frameWait.front();
                    frameWait.pop();
                    curr.page = currRef;
                    curr.framenum = currFrame;
                    frames.push(curr);
                    currFrame ++;
                    numEvicts++;
                }
            }
        }
        cout << "num hits: " << numHits << "\n";
        cout << "num misses: " << numMisses;
    }
    if(algo == 1){
        cout << "Algo is LRU \n";
        cout << "Frames: " << k << "\n";
        int evicts = 0;
        
        int ref = 0;
        vector<frame> frames;
        for(int i = 0; i<k; i++){
            
            frame frameAdd;
            frames.push_back(frameAdd); 
        }
        int index = 0;
        int evict = 1;
        for(int i = 0; i < 1000; i++){
            ref = nums[i];
            if(frames[index].page == ref){ 
                numHits++;
                frames[index].count++;
            }
            else if(frames[index].page == -1){
                frames[index].page = ref;
                frames[index].count ++;
            }
            else if(frames[index].page != ref){
                numMisses++;
                int j = 0;
                int least = 1000;
                while(j< k){
                    if(frames[j].count < least){
                        least = j;
                    }
                    if(frames[j].page == ref){
                        numHits++;
                        frames[j].count++;
                        evict = 0;
                        index = j;
                    }
                    j++;
                }
                if(evict == 1){
                    index = j;
                    frames[j].page = ref;
                    frames[j].count = 1;
                    evicts++;
                }
            }
        }
        cout << "\nhits: " << numHits << "\n";
        cout << "miss: " << numMisses << "\n";
        cout << "evicts: " << evicts << "\n";

    }
    if(algo == 2){
        int kbit = 100;
        cout << "Algo is Second Chance \n";
        cout << "Frames: " << k << "\n";
        int evicts = 0;
   
        int ref = 0;
        vector<frame> frames;
        queue<frame> q;
        for(int i = 0; i<k; i++){
            
            frame frameAdd;
            frames.push_back(frameAdd); 
        }
        int index = 0;
        int evict = 1;
        for(int i = 0; i < 1000; i++){
            ref = nums[i];
            if(frames[index].page == ref){ 
                numHits++;
                frames[index].count++;
            }
            else if(frames[index].page == -1){
                frames[index].page = ref;
                frames[index].count ++;
                q.push(frames[index]);
            }
            else if(frames[index].page != ref){
                numMisses++;
                int j = 0;
                int least = 1000;
                while(j< k){
                    if(frames[j].count < least){
                        least = j;
                    }
                    if(frames[j].page == ref){
                        frames[j].count++;
                        evict = 0;
                        index = j;
                    }
                    j++;
                }
                if(evict == 1){
                    //should be removing based on queue
                }
            }
        }
    }
        
        
        cout << "num hits: " << numHits << "\n";
        cout << "num misses: " << numMisses << " \n";
    for(int i = 0; i<10; i++){
        cout<< "page number: " << i << " ref count: " << refCount[i] << "\n";
    }
}