//
// Created by root on 18-9-13.
//

#ifndef DATASTOR_QOS_CLIENT_H
#define DATASTOR_QOS_CLIENT_H

#include <list>
#include <sysqos_token_reqgrp_manager.h>
#include "json_obj.h"
#include "task.h"
#include "task_group.h"

class complete_task_hook
{
public:
    virtual void task_completed(void ){}
    virtual void task_final(task_group *tgrp) = 0;
};

class client
{
   
    bool is_qos_open;
    string cli_name;
    std::mutex m;
    std::list<task_group *> tasks_list;
    std::list<task_group *> sure_tasks_list;//得到token直接能发送的
    std::list<task *> complete_list;
    complete_task_hook *hook;
    bool could_snd(task_group *tgrp, bool &is_back_toq);
    void retry_task(task *t);
    int grp_retry;
    int task_retry;
    bool final_task(task *t);
public:
    sysqos_applicant_ops_t ops;
    void snd_tasks(task_group *tgrp);
    client(const string &_name, bool qos_open, int _grp_retry,
           int _task_retry, complete_task_hook *_hook);
    bool run_once();
    void submit_tasks(task_group *tgrp);
    void submit_sure_tasks(task_group *tgrp);
    void complete_task(task *t);
    string name()const;
};


#endif //DATASTOR_QOS_CLIENT_H
