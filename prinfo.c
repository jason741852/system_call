#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/prinfo.h>
#include <asm/uaccess.h>


asmlinkage int sys_prinfo(struct prinfo* sysinfo){
  printk("you are in kernel\n");

  // copy the whole structure from user space to get pid
  copy_from_user(sysinfo,sysinfo,sizeof(struct prinfo));

  if(sysinfo->pid==NULL || sysinfo->pid==0){
    return -22;
  }

  struct task_struct  *task = get_current();
  pid_t cur_pid = task->pid;
  while(cur_pid!=sysinfo->pid){
    task = task->parent;
    cur_pid = task->pid;
  }

  sysinfo->state = task->state;
  // priority = 20 + "nice" --> nice = priority - 20
  // priority is in the range of 0 to 139 and nice is in the range of -20 to 19
  // so need to subtract 100 from priority first
  sysinfo->nice = (task->prio) - 120;
  sysinfo->pid = task->pid;
  sysinfo->parent_pid = task->parent->pid;
  sysinfo->youngest_child_pid = list_entry(task->children.prev, struct task_struct, children)->pid;
  sysinfo->younger_sibling_pid = list_entry(task->sibling.next, struct task_struct, sibling)->pid;
  sysinfo->older_sibling_pid = list_entry(task->sibling.prev, struct task_struct, sibling)->pid;
  sysinfo->start_time = task->start_time.tv_nsec;
  sysinfo->user_time = task->utime;
  sysinfo->sys_time = task->stime;
  // sysinfo->cutime = current->signal->cutime;
  // sysinfo->cstime = current->signal->cstime;
  unsigned long cu_time = 0;
  unsigned long cs_time = 0;

  struct list_head *list;
  list_for_each(list, &task->children) {
    cu_time = cu_time + list_entry(list, struct task_struct, sibling)->utime;
    cs_time = cs_time + list_entry(list, struct task_struct, sibling)->stime;

  }
  sysinfo->cutime = cu_time;
  sysinfo->cutime = cs_time;



  sysinfo->uid = (long)task->uid;
  strncpy(sysinfo->comm,task->comm,20);


  // if(copy_to_user(sysinfo->uid,current->uid,20)){
  //   return  -EFAULT;
  // }
  printk("Back to user level...\n\n");
  copy_to_user(sysinfo,sysinfo,sizeof(struct prinfo));
  return 0;
}
