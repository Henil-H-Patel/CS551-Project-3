#include "syslib.h"

int sys_nicerto(endpoint_t proc_ep, endpoint_t proc_tonice)
{
    printf("sys_nicerto from: usr/src/minix/lib/libsys/sys_nicerto.c\n");
    message m;
    m.m_lsys_krn_sys_nicerto.endpt = proc_tonice;
    printf("Sys_nicerto : %d",proc_tonice);
    int r = _kernel_call(SYS_NICERTO, &m);
    if(r != OK) printf("Kernel call failed\n");
    return r;
}