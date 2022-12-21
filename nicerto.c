#include "pm.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include "glo.h"
#include "mproc.h"

int do_nicerto(int proc_id)
{
    int proc_n;
    register struct mproc *rmp, *rmp_tonice;
    rmp = &mproc[proc_n];
    if ((rmp_tonice = find_proc(m_in.m_lc_pm_nicerto.pid)) == NULL)
	    return(ESRCH);
    int r = sys_nicerto(rmp->mp_endpoint, rmp_tonice->mp_endpoint);
    printf("Success from: usr/src/minix/servers/pm");
    if(r != OK) printf("Kernel call failed");
    return r;
}