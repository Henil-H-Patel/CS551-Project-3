/* The kernel call implemented in this file:
 *   m_type:	SYS_NICERTO
 */
#include "kernel/system.h"
#include <minix/endpoint.h>

#if USE_NICERTO

/**
 * do_nicerto
*/

int do_nicerto(struct proc *caller, message *m_ptr) {

    endpoint_t endpt = m_ptr->m_lsys_krn_sys_nicerto.endpt;
    printf("do_nicerto from: usr/src/minix/kernel/system/do_nicerto.c\n");
    register struct proc *p;
    int proc_nr, priority, quantum, cpu, niced;

    printf("Value retrieving from do_nicerto: %d\n", int(endpt));
    if (!isokendpt(endpt, &proc_nr)) return EINVAL;

    if (iskerneln(proc_nr)) return(EPERM);

    p = proc_addr(proc_nr);
    priority = TASK_Q;
    quantum = -1;
    cpu = -1;
    niced = FALSE;
    return sched_proc(p, priority, quantum, cpu, niced);
}

#endif /* USE_NICERTO */