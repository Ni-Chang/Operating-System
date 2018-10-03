//
//  main.cpp
//  PageFault
//
//  Created by xiaonizi on 2018/4/16.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

bool find_int(vector<int> arr, int x){
    int i;
    for(i=0; i<arr.size(); i++){
        if(arr[i]==x){
            return true;
        }
    }
    return false;
}

void OPT(vector<int> page_visit, int visit_num, vector<int> &frame, int new_page, int frame_num){
    vector<int> next_visit;
    int j, k;
    for(j=visit_num+1; j<100 && next_visit.size()<frame_num-1; j++){
        if(find_int(frame, page_visit[j])&&!find_int(next_visit, page_visit[j])){
            next_visit.push_back(page_visit[j]);
        }
    }
    for(k=0; k<frame_num; k++){
        if(!find_int(next_visit, frame[k])){
            frame[k]=new_page;
            break;
        }
    }
}

void LRU(vector<int> &use_time, int visit_num, vector<int> &frame, int new_page){
    vector<int>::iterator smallest=min_element(use_time.begin(), use_time.end());
    frame[distance(use_time.begin(), smallest)]=new_page;
    use_time[distance(use_time.begin(), smallest)]=visit_num;
}

void FIFO(int &FIFO_pos, vector<int> &frame, int new_page){
    frame[FIFO_pos]=new_page;
    FIFO_pos=(FIFO_pos+1)%frame.size();
}

int page_fault_num(int frame_num, vector<int> page_visit, int displace_type){
    vector<int> frame;
    int i, j, page_fault_num=0, FIFO_pos=0, flag=0;
    vector<int> use_time;
    for(j=0; j<100; j++){
        flag=0;
        for(i=0; i<frame.size(); i++){
            if(frame[i]==page_visit[j]){
                flag=1;
                use_time[i]=j;
                break;
            }
        }
        if(flag==0){
            if(frame.size()<frame_num){
                frame.push_back(page_visit[j]);
                use_time.push_back(j);
            }
            else{
                if(displace_type==1)
                    OPT(page_visit, j, frame, page_visit[j], frame_num);
                else if(displace_type==2)
                    LRU(use_time, j, frame, page_visit[j]);
                else
                    FIFO(FIFO_pos, frame, page_visit[j]);
            }
            page_fault_num++;
        }
    }
    return page_fault_num;
}

int main() {
    vector<int> page_visit;
    cout << "Input page to visit:" << endl;
    int i, type, page;
    for(i=0; i<100; i++){
        cin >> page;
        page_visit.push_back(page);
    }
    for(type=1; type<=3; type++){
        if(type==1)
            cout << "OPT results:" << endl;
        else if(type==2)
            cout << "LRU results:" << endl;
        else
            cout << "FIFO results:" << endl;
        for(i=1; i<=10; i++){
            cout << "n = " << i << ", " << "Page faults: " << page_fault_num(i, page_visit, type) << endl;
        }
        cout << endl;
    }
    return 0;
}
