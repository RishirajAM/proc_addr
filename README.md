# proc_addr

This project contains:-

1) Kernel space module - proc_addr.c

- Use "make -C <KSRC> M=`pwd` modules" for building the kernel space module. (<KSRC> = source of the currently running kernel)
- For loading the module proc_addr.ko, use "insmod proc_addr.ko pid_mem=<pid>". (<pid> = PID of the process whose memory segments you want to see)
- Once that is loaded, you can check the output by using "dmesg".
- For unloading the module, use "rmmod proc_addr.ko".

2) Application space module - addr.c

- Not much about this code.
- This code is quite evident.
- This code is there for demonstration.