//
// Created by root on 18-9-13.
//

#ifndef DATASTOR_QOS_TASK_GROUP_H
#define DATASTOR_QOS_TASK_GROUP_H


#include <vector>
#include <json_obj.h>
#include "task.h"
#include "sysqos_interface.h"

enum task_group_stat
{
    task_group_stat_out_standing,
    task_group_stat_wait_token,
    task_group_stat_wait_grp,
    task_group_stat_wait_disk,
};

class task_group
{

public:
    bool is_failed;
    struct token_reqgrp *token;
    std::vector<task *> tasks;
    int                 task_id;
    task_group_stat     state;
    client              *cli;
    utime               begin_time;
    std::mutex          m;
    int                 wait_grp_cnt;
    int                 final_cnt;
    
    long usecs();
    
    void set_failed();
    
    bool is_final();
    
    bool is_grp_ready();
    
    void set_stat(task_group_stat new_stat);
    
    json_obj to_json_obj() const;
    
    task_group(const int task_cost, const map<server *, client *> &c_s_pairs,
               int _task_id);
    
    ~task_group();
};


#endif //DATASTOR_QOS_TASK_GROUP_H