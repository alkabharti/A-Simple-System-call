//http://tuxthink.blogspot.in/2012/07/module-to-find-task-from-its-pid.html
//http://ytliu.info/notes/linux/file_ops_in_kernel.html
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/file.h>
#include<linux/fcntl.h>
#include<linux/syscalls.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/proc_fs.h>
#include<linux/pid.h>
#include<linux/pid_namespace.h>

asmlinkage long sys_demo(int pid,char *alpha)
{
struct pid *p;
struct task_struct *task;
p=find_get_pid(pid);
task= pid_task(p,PIDTYPE_PID);
printk("%d",task->pid);
printk("%s",task->comm);
printk("%ld",task->state);
printk("%d",task->prio);
printk("%d",task->static_prio);
printk("%d",task->normal_prio);
printk("%d",task->on_cpu);
printk("%d",task->wake_cpu);
printk("%u",task->rt_priority);
printk("%d",task->tgid);
printk("%u",task->se.on_rq);
printk("%lu",task->thread.sp0);
printk("%lu",task->thread.sp);
printk("%lu",task->thread.usersp);
printk("%lu",task->thread.fs);
printk("%lu",task->thread.gs);
printk("%lu",task->thread.debugreg6);
printk("%lu",task->thread.ptrace_dr7);
printk("%lu",task->thread.cr2);
printk("%lu",task->thread.trap_nr);
printk("%lu",task->thread.error_code);
printk("%lu",task->thread.iopl);
printk("%d",task->signal->nr_threads);
printk("%d",task->signal->group_exit_code);
printk("%d",task->signal->notify_count);
printk("%d",task->signal->group_stop_count);
printk("%u",task->signal->flags);
printk("%d",task->sighand->count);
printk("%d",task->blocked);
printk("%d",task->real_blocked);
char buffer[2048];
sprintf(buffer,"%d %s %ld %d %d %d %d %d %u %d %u %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %d %d %u %d %d %d",task->pid,task->comm,task->state,task->prio,task->static_prio,task->normal_prio,task->on_cpu,task->wake_cpu,task->rt_priority,task->tgid,task->se.on_rq,task->thread.sp0,task->thread.sp,task->thread.usersp,task->thread.fs,task->thread.gs,task->thread.debugreg6,task->thread.ptrace_dr7,task->thread.cr2,task->thread.trap_nr,task->thread.error_code,task->thread.iopl,task->signal->nr_threads,task->signal->group_exit_code,task->signal->notify_count,task->signal->group_stop_count,task->signal->flags,task->sighand->count,task->blocked,task->real_blocked);
struct file *file;
loff_t pos = 0;
int fd;
mm_segment_t old_fs = get_fs();
set_fs(KERNEL_DS);
fd = sys_open(alpha, O_WRONLY|O_CREAT, 0644);
if (fd >= 0) 
{
	sys_write(fd,buffer, strlen(buffer));
	file = fget(fd);
	if (file) 
	{
		vfs_write(file,buffer,strlen(buffer),&pos);
		fput(file);
	}
	sys_close(fd);
}
set_fs(old_fs);
return 0;
}
