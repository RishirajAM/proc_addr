#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

#define CODE_PRINT	"PID: %d,\tCode Seg. Start: 0x%lx,\tCode Seg. End: 0x%lx\n***\n"
#define DATA_PRINT	"PID: %d,\tData Seg. Start: 0x%lx,\tData Seg. End: 0x%lx\n***\n"
#define HEAP_PRINT	"PID: %d,\tHeap Seg. Start: 0x%lx,\tHeap Seg. End: 0x%lx\n***\n"
#define VMA_PRINT	"VMA %d starts at 0x%lx, ends at 0x%lx\n"

int pid_mem = 1;

void print_mem(struct task_struct *task)
{
	struct mm_struct *mm = NULL;
	struct vm_area_struct *vma = NULL;
	int count;

	mm = task->mm;

	printk(KERN_ALERT "***\nCode Segment Address Range:\n");
	printk(KERN_ALERT 
		CODE_PRINT,
		task->pid,
		mm->start_code,
		mm->end_code);

	printk(KERN_ALERT "***\nData Segment Address Range:\n");
	printk(KERN_ALERT 
		DATA_PRINT,
		task->pid,
		mm->start_data,
		mm->end_data);

	printk(KERN_ALERT "***\nHeap Segment Address Range:\n");
	printk(KERN_ALERT 
		HEAP_PRINT,
		task->pid,
		mm->start_brk,
		mm->brk);

	printk(KERN_ALERT "***\nPID: %d,\tStack segment starts : 0x%lx\n***",
			task->pid,
			mm->start_stack);

	printk(KERN_ALERT "***VMAs***\n");
	for(vma = mm->mmap, count = 0; vma; vma=vma->vm_next, count++)
	{
		printk(KERN_ALERT 
			VMA_PRINT,
			count,
			vma->vm_start,
			vma->vm_end);
	}

	printk(KERN_ALERT "************\n");
	printk(KERN_ALERT "Total Pages: %ld\n",mm->total_vm);

	printk(KERN_ALERT "************\n");
	printk(KERN_ALERT "Page-table pages: %ld\n",mm->nr_ptes);

}

static int __init init_method(void)
{
	struct task_struct *task = NULL;
	printk(KERN_ALERT "Process ID is %d...\n", pid_mem);
	for_each_process(task)
	{
		if(task->pid == pid_mem)
		{
			printk(KERN_ALERT "Process: %s [%d] :\n",
					task->comm,
					task->pid);

			print_mem(task);
		}
	}
	
	return 0;
}

void __exit exit_method(void)
{
	printk(KERN_ALERT "\nBye bye...\n");
}

module_init(init_method);
module_exit(exit_method);
module_param(pid_mem, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(pid_mem, "PID of the process");

MODULE_AUTHOR("Rishiraj Manwatkar manwatkar@outlook.com");
MODULE_DESCRIPTION("Shows the code, data, heap, stack memory regions of a process");
MODULE_LICENSE("GPL");
