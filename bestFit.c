//
//  main.c
//  BestFit
//
//  Created by xiaonizi on 2018/4/6.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <limits.h>

struct job_type{
    int flag;
    int arrive_time;
    int running_time;
    int memory_use;
    int memory_add;
};

int table[32] = {0};

void initialize(){
    int i;
    for(i=0; i<5; i++)
        table[i]=1;
    for(i=0; i<6; i++)
        table[i+8]=1;
    for(i=0; i<4; i++)
        table[i+14]=1;
    for(i=0; i<6; i++)
        table[i+20]=1;
    for(i=0; i<3; i++)
        table[i+26]=1;
}

int is_finished(struct job_type job[], int n) {
    for(int i = 0; i < n; i++){
        if(job[i].flag == 0)
            return 0;
    }
    return 1;
}

int distribute(struct job_type job) {
    int size = 0, min_size = INT_MAX, flag = 0, i, start_add;
    for(i = 0; i < 32; i++) {
        if(table[i] == 0) {
            size++;
        }
        else{
            if(min_size > size && size >= job.memory_use){
                min_size = size;
                flag = 1;
                start_add = i-size;
            }
            size = 0;
        }
    }
    if(flag == 1){
        for(i = start_add; i < start_add+job.memory_use; i++) {
            table[i] = 1;
        }
        return start_add;
    }
    else
        return -1;
}

void release(struct job_type job) {
    for(int i = job.memory_add; i < job.memory_add + job.memory_use; i++) {
        table[i] = 0;
    }
}

void job_processing(struct job_type job[], int n) {
    int time=0;
    while(is_finished(job, n) == 0) {
        for(int i = 0; i < n; i++) {
            if(job[i].arrive_time == time){
                job[i].memory_add = distribute(job[i]);
                if(job[i].memory_add != -1) {
                    job[i].flag = 1;
                    printf("作业%d:分配时间%d,分配内存起始地址%d\n", i, time, job[i].memory_add);
                }
                else
                    job[i].arrive_time++;
            }
            if(job[i].arrive_time + job[i].running_time == time){
                release(job[i]);
            }
        }
        time++;
    }
}


int main() {
    initialize();
    int job_num;
    printf("请输入作业数量：\n");
    scanf("%d", &job_num);
    struct job_type job[job_num];
    printf("请顺序输入作业到达时间、运行时间、内存需求：\n");
    for(int i=0; i<job_num; i++)
    {
        scanf("%d %d %d", &job[i].arrive_time, &job[i].running_time, &job[i].memory_use);
        job[i].flag = 0;
        job[i].memory_add = -1;
    }
    job_processing(job, job_num);
}
