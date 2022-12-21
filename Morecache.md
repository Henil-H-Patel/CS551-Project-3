# PROJECT_3 - GROUP - 2

## GROUP MEMBERS : HENIL PATEL, VISESH JAIN, SHIVAM GUPTA

#### AIM : The aim of this document to provide the steps, which are required for the perform the system call and compile process

### Now here the implementation steps for MORECACHE system call.

1> usr/src/minix/include/minix/ipc.h

      This is useful for the message storing purpose

     typedef struct {
      int bufferBlock;
      uint8_t data[52];
     } mess_vfs_fs_morecache;
     _ASSERT_MSG_SIZE(mess_vfs_fs_morecache);

     typedef struct {
      int bufferBlock;
      uint8_t data[52];
     } mess_lc_vfs_morecache;
     _ASSERT_MSG_SIZE(mess_lc_vfs_morecache);

     Inside the struct union add below
      mess_vfs_fs_morecache	         m_vfs_fs_morecache;
      mess_lc_vfs_morecache          m_lc_vfs_morecache;

2> usr/src/minix/include/minix/callnr.h

      #define VFS_MORECACHE		(VFS_BASE + 49)
      #define NR_VFS_CALLS		50

3> usr/src/minix/servers/pm/Makefile

      include moreCache.c in makefile

4> usr/src/minix/servers/pm/

      In this directory we add the moreCache.c, we put the code for the execution

5> usr/src/minix/servers/pm/proto.h

      In this file we define the proto type of the function, we want to perform during the system call
      This changes happened in proto.h file

      int do_morecache(void);

6> usr/src/minix/server/pm/table.c

      Here we need add the call in this file

      CALL(VFS_MORECACHE) = do_morecache

7> usr/src/minix/minix/servers/vfs/request.c

      /*===========================================================================*
            *				req_morecache          			     *
       *===========================================================================*/
      int req_morecache(
      endpoint_t fs_e,
      int bufferBlock
      )
      {
      message m;
      int r;

      /* Fill in request message */
      m.m_type = REQ_MORECACHE;
      m.m_vfs_fs_morecache.bufferBlock = bufferBlock;
      printf("Sending request from: usr/src/minix/minix/servers/vfs/request.c");
      
       /* Send/rec request */
      r = fs_sendrec(fs_e, &m);

      return(r);
      }

8> usr/src/minix/include/minix/vfsif.h

      #define REQ_MORECACHE	(FS_BASE + 34)
      #define NREQS			    35

9> usr/src/minix/lib/libfsdriver/call.c

      /* Process a MORECACHE request from VFS. */
      int
      fsdriver_morecache(const struct fsdriver * __restrict fdp,
      const message * __restrict m_in, message * __restrict m_out)
      {
            int bufferBlock;
            int r;

            bufferBlock = m_in->m_vfs_fs_morecache.bufferBlock;

            printf("Requested from: usr/src/minix/lib/libfsdriver/call.c \n");

            if (fdp->fdr_morecache == NULL)
                  return ENOSYS;

            if ((r = fdp->fdr_morecache(bufferBlock)) == OK)
                  printf("fsdriver_morecache: executed successfully \n");

            return r;
      }

10> usr/src/minix/fs/mfs/misc.c

      /*===========================================================================*
      *				fs_morecache					     *
      *===========================================================================*/
      int fs_morecache(int bufferBlock)
      {
            int buffer = lmfs_nr_buffer();
            lmfs_buf_pool(buffer * bufferBlock);
            int inc_buffer = lmfs_nr_buffer();
            printf("fs_morecache: current buffers: %d -> %d \n", buffer, inc_buffer);
            return OK;
      }

11> usr/src/minix/lib/libminixfs/cache.c

      int lmfs_nr_buffer(void)
      {
	      return nr_buffer;
      }

12> usr/src/minix/lib/libfsdriver/fsdriver.h

      Here we defined the request function

      extern int fsdriver_morecache(const struct fsdriver * __restrict,
      const message * __restrict, message * __restrict);

13> usr/src/minix/include/minix/fsdriver.h

     int (*fdr_morecache)(int buffsfactor);

14> usr/src/minix/fs/mfs/proto.h

     int fs_morecache(int bufferBlock);

15> usr/src/minix/include/minix/libminixfs.h

     int lmfs_nr_buffer(void);

16> usr/src/minix/fs/mfs/table.c

    After .fdr_chown	= fs_chown we need to add the below,

    .fdr_morecache	= fs_morecache,

17> usr/src/minix/lib/libfsdriver/table.c

    CALL(REQ_MORECACHE)	= fsdriver_morecache

18>  usr/src/releasetools
     
      Now we use the make hdboot in the same directory





### Here I attach the test.c file for calling the system call

    #include<unistd.h>
    #include<stdio.h>
    #include<lib.h>
    int main()
    {
      message m;
      memset(&m,0,sizeof(m));
      m.m_lc_vfs_morecache.buffsfactor = 2;
      int j = _syscall(VFS_PROC_NR, VFS_MORECACHE, &m);
    }

