#include "fs.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include "glo.h"
#include "fproc.h"
#include "vnode.h"

int do_morecache()
{
    register struct fproc *rfp;
    rfp = &fproc[0];
    int new_buffferBlock = 10;
    int r = req_morecache(rfp->fp_rd->v_fs_e, new_bufferBlock);
    printf("usr/src/minix/servers/pm/moreCache.c")
    if(r!=OK) printf("Kernel call failed - %d",r);
    return r;
}