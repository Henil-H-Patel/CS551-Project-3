# PROJECT_3 - GROUP - 2

## GROUP MEMBERS : HENIL PATEL, VISESH JAIN, SHIVAM GUPTA

#### AIM : The aim of this document to provide the steps, which are required for the perform the system call and compile process

#### In this document we mention the flow of trap system call, and similarly we can perform the same for the rest of three system calls.

### Now here the Implementation steps for MOREZONE system call

1> usr/src/minix/include/minix/ipc.h

      This is useful for the message storing purpose

      typedef struct {
	int zoneBlock;

	uint8_t data[52];
      } mess_vfs_fs_morezone;
_ASSERT_MSG_SIZE(mess_vfs_fs_morezone);

     Inside the struct union add below
      mess_vfs_fs_morezone    	m_vfs_fs_morezone;


2> usr/src/minix/include/minix/callnr.h

  #define VFS_MOREZONE		(VFS_BASE + 65)
  /* Total */
  #define NR_VFS_CALLS		66	/* highest number from base plus one */

3> usr/src/minix/servers/pm/
## We will create new file moreZone.c 
###  We provide you file in zip folder for your reference

4> usr/src/minix/servers/pm/Makefile
####   Add this filename to the Makefile
     moreZone.c \


5> usr/src/minix/servers/pm/proto.h

      In this file we define the proto type of the function, we want to perform during the system call
      This changes happened in proto.h file

      int do_morecache(void);

6> usr/src/minix/server/vfs/table.c

      Here we need add the call in this file

      CALL(VFS_MOREZONE) = do_morezone     /* do_morezone(1) */

7> usr/src/minix/minix/servers/vfs/request.c

      /*===========================================================================*
            *				req_morezone          			     *
       *===========================================================================*/
      int req_morezone(
      endpoint_t fs_e,
      int zoneBlock
      )
      {
      message m;
      int r;

      /* Fill in request message */
      m.m_type = req_morezone;
      m.m_vfs_fs_morecache.zoneBlock = zoneBlock;
      printf("req_morezone: sending message to fs");
      
       /* Send/rec request */
      r = fs_sendrec(fs_e, &m);

      return(r);
      }




8> usr/src/minix/include/minix/vfsif.h
 
#define REQ_MORECACHE	(FS_BASE + 34)
#define REQ_MOREZONE	(FS_BASE + 35)
/* Total */
#define NREQS			    36


9> usr/src/minix/lib/libfsdriver/call.c

      /* Process a MOREZONE request from VFS. */
      int
      fsdriver_morezone(const struct fsdriver * __restrict fdp,
      const message * __restrict m_in, message * __restrict m_out)
      {
            int zoneBlock;
            int r;

            zoneBlock = m_in->m_vfs_fs_morezone.zoneBlock;

            printf("fsdriver_morezone from: usr/src/minix/lib/libfsdriver/call.c \n");

            if (fdp->fdr_morezone == NULL)
                  return ENOSYS;

            if ((r = fdp->fdr_morezone(zoneBlock)) == OK)
                  printf("fsdriver_morezone: Executed Successfully \n");

            return r;
      }

10> usr/src/minix/fs/mfs/misc.c

      /*===========================================================================*
      *				fs_morezone					     *
      *===========================================================================*/
      int fs_morezone(int zoneBlock)
      {
            printf("fs_morezone: function. \n");
            int buffer = lmfs_nr_buffer();
            lmfs_buf_pool(buffer * zoneBlock);
            int inc_buffer = lmfs_nr_buffer();
            printf("fs_morezone: current buffers: %d -> %d \n", buffer, inc_buffer);
            return OK;
      }

11> usr/src/minix/lib/libminixfs/cache.c

      int lmfs_nr_buffer(void)
      {
	      return nr_buffer;
      }

12> usr/src/minix/lib/libfsdriver/fsdriver.h

      Here we defined the request function

      extern int fsdriver_morezone(const struct fsdriver * __restrict,
      const message * __restrict, message * __restrict);

13> usr/src/minix/include/minix/fsdriver.h

     int (*fdr_morezone)(int zoneBlock);

14> usr/src/minix/fs/mfs/proto.h

     int fs_morezone(int zoneBlock);

15> usr/src/minix/include/minix/libminixfs.h

     int lmfs_nr_buffer(void);

16> usr/src/minix/fs/mfs/table.c

    After .fdr_chown	= fs_chown we need to add the below,

    .fdr_morezone	= fs_morezone,

17> usr/src/minix/lib/libfsdriver/table.c

    CALL(REQ_MOREZONE)	= fsdriver_morezone



### Here I attach the .c file for calling the system call

    #include<unistd.h>
    #include<stdio.h>
    #include<lib.h>
    int main()
    {
      message m;
      memset(&m,0,sizeof(m));
      m.m_lc_vfs_morezone.zoneBlock = 5;
      int r = _syscall(VFS_PROC_NR, VFS_MOREZONE, &m);
    }

