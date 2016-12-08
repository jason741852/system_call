include <stdio.h>
#include<linux/unistd.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<stdlib.h>

#define _cmpt300_TEST_ 327
#define _cmpt300_prinfo_ 328



int main(int argc, char *argv[])
{
        struct prinfo {
          long state; /* current state of process */
          long nice; /* process nice value */
          pid_t pid; /* process id (input) */
          pid_t parent_pid; /* process id of parent */
          pid_t youngest_child_pid; /* process id of youngest child */
          pid_t younger_sibling_pid; /* pid of the oldest among younger siblings
          */
          pid_t older_sibling_pid; /* pid of the youngest among older siblings */
          unsigned long start_time; /* process start time */
          long
          user_time; /* CPU time spent in user mode */
          long sys_time; /* CPU time spent in system mode */
          long cutime; /* total user time of children */
          long cstime; /* total system time of children */
          long uid; /* user id of process owner */
          char comm[16]; /* name of
          program executed */
        };
        printf("\nDiving to kernel level\n\n");
        syscall(_cmpt300_TEST_,300);
        printf("\nRising to user level \n\n");
        struct prinfo* sysinfo = malloc(sizeof(struct prinfo));
        sysinfo->nice = 200;
        sysinfo->pid = getpid();
        printf("user space sysinfo->uid = %d\n\n",sysinfo->uid);
        printf("before sysinfo->pid = %d\n",sysinfo->pid);
        syscall(_cmpt300_prinfo_,sysinfo);
        printf("\n-------\nstate = %d\n",sysinfo->state);
        printf("nice = %d\n",sysinfo->nice);
        printf("pid = %d\n",sysinfo->pid);
        printf("parent_pid = %d\n",sysinfo->parent_pid);
        printf("uid = %d\n",sysinfo->uid);
        printf("youngest_child_pid = %d\n",sysinfo->youngest_child_pid);
        printf("younger_sibling_pid = %d\n",sysinfo->younger_sibling_pid);
        printf("older_sibling_pid = %d\n",sysinfo->older_sibling_pid);
        printf("start_time = %lu\n",sysinfo->start_time);
        printf("user_time = %lu\n",sysinfo->user_time);
        printf("sys_time = %lu\n",sysinfo->sys_time);
        printf("cutime = %lu\n",sysinfo->cutime);
        printf("cstime = %lu\n",sysinfo->cstime);
        printf("uid = %d\n",sysinfo->uid);
        printf("youngest_child_pid = %d\n",sysinfo->youngest_child_pid);
        printf("younger_sibling_pid = %d\n",sysinfo->younger_sibling_pid);
        printf("older_sibling_pid = %d\n",sysinfo->older_sibling_pid);
        printf("start_time = %lu\n",sysinfo->start_time);
        printf("user_time = %lu\n",sysinfo->user_time);
        printf("sys_time = %lu\n",sysinfo->sys_time);
        printf("cutime = %lu\n",sysinfo->cutime);
        printf("cstime = %lu\n",sysinfo->cstime);
        printf("uid = %d\n",sysinfo->uid);
        printf("comm = %s\n",sysinfo->comm);
        return 0;
}
