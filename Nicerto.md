
#   PROJECT_3 - GROUP - 2
##  GROUP MEMBERS : HENIL PATEL, VISESH JAIN, SHIVAM GUPTA

####   AIM : The aim of this document to provide the steps, which are required for the perform the system call and compile process.

#####   REFERENCE : For implementing the system call, and compile purpose, we have taken the reference
#####   1) Adding the new system call in kernel ( https://wiki.minix3.org/doku.php?id=developersguide:newkernelcall)

###   Now here the Implementation steps for the NICERTO() system call.


1> usr/src/minix/include/minix/ipc.h

#####   This is for storing the required values

      typedef struct {
             pid_t pid;

            uint8_t padding[52];
      } mess_lc_pm_nicerto;
      _ASSERT_MSG_SIZE(mess_lc_pm_nicerto);

      typedef struct {
            endpoint_t endpt;
      
            uint8_t padding[52];
      } mess_lsys_krn_sys_nicerto;
      _ASSERT_MSG_SIZE(mess_lsys_krn_sys_nicerto);

      Add the below in struct union:
      
      mess_lc_pm_nicerto                m_lc_pm_nicerto;
      mess_lsys_krn_sys_nicerto     m_lsys_krn_sys_nicerto;



2> usr/src/minix/include/minix/com.h

#####   Add the kernel call (here we refer the minix documentation and earlier project 2 system calls) 

      #define SYS_NICERTO ( KERNEL_CALL + 58 )     /* sys_nicerto() */
      /* Total */
      #define NR_SYS_CALLS          59    


3> usr/src/minix/kernel/system.c

      map(SYS_NICERTO, do_nicerto);	/* nicerto will change the priority of process */

4> usr/src/minix/kernel/config.h
 
      #define USE_NICERTO            1                /* nicerto call */


5> usr/src/minix/kernel/system.h

      int do_nicerto(struct proc *caller, message *m_ptr);
      #if ! USE_NICERTO
      #define do_nicerto NULL
      #endif

6> usr/src/minix/include/minix/syslib.h
#####  The below is the sys_nicerto declaration for system call

      int sys_nicerto(endpoint_t proc_ep, endpoint_t proc_nicer);


7> usr/src/minix/kernel/system
## We will create new file do_nicerto.c 
###  We provide you file in zip folder for your reference 
   

8> usr/src/minix/kernel/system/Makefile.inc
## We include the do_nicerto.c file in the Makefile.inc   
      do_nicerto.c \

9> usr/src/minix/lib/libsys/
## We will create new file sys_nicerto.c 
###  We provide you file in zip folder for your reference
10> usr/src/minix/lib/libsys/Makefile
## We include the sys_nicerto.c file in the Makefile.inc
      sys_nicerto.c \



#####   NOW THE PRIVILEGED SYSTEM SERVER CHANGE

11> usr/src/minix/include/minix/callnr.h

      #define PM_NICERTO	          ( PM_BASE + 48 )
      /* Total */
     #define NR_PM_CALLS                  49

12> usr/src/minix/servers/pm
## We will create new file nicerto.c 
###  We provide you file in zip folder for your reference


13> usr/src/minix/servers/pm/Makefile
####   Add this filename to the Makefile
      nicerto.c \

14> usr/src/minix/servers/pm/proto.h

#####  In this file we define the proto type of the function, we want to perform during the system call

      int do_nicerto(void);

15> usr/src/minix/server/pm

#####   Here we need add the call into the table.c file 

      CALL(PM_NICERTO) = do_nicerto

16> usr/src/minix/commands/minix-service/parse.c

      system_tab[ ]=
      {
      …
      { "NICERTO",             SYS_NICERTO },
      { NULL,      	   0 }
      };
17>  usr/src/releasetools
     
      Now we use the make hdboot in the same directory

### Here I attach the test.c file for calling the system call

      #include<unistd.h>
      #include<stdio.h>
      #include<lib.h>
      int main()
      {
      message m;
      memset(&m,0,sizeof(m));
      m.m_lc_pm_nicerto.pid = getpid();
      int k = syscall(PM_PROC_NR,PM_NICERTO, &m);
      }
