<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2007
 *
 *  Author: Eric Biederman <ebiederm@xmision.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/ipc.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/msg.h>
#समावेश "util.h"

अटल व्योम *get_ipc(काष्ठा ctl_table *table)
अणु
	अक्षर *which = table->data;
	काष्ठा ipc_namespace *ipc_ns = current->nsproxy->ipc_ns;
	which = (which - (अक्षर *)&init_ipc_ns) + (अक्षर *)ipc_ns;
	वापस which;
पूर्ण

#अगर_घोषित CONFIG_PROC_SYSCTL
अटल पूर्णांक proc_ipc_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table ipc_table;

	स_नकल(&ipc_table, table, माप(ipc_table));
	ipc_table.data = get_ipc(table);

	वापस proc_करोपूर्णांकvec(&ipc_table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक proc_ipc_करोपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table ipc_table;

	स_नकल(&ipc_table, table, माप(ipc_table));
	ipc_table.data = get_ipc(table);

	वापस proc_करोपूर्णांकvec_minmax(&ipc_table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक proc_ipc_करोपूर्णांकvec_minmax_orphans(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ipc_namespace *ns = current->nsproxy->ipc_ns;
	पूर्णांक err = proc_ipc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (err < 0)
		वापस err;
	अगर (ns->shm_rmid_क्रमced)
		shm_destroy_orphaned(ns);
	वापस err;
पूर्ण

अटल पूर्णांक proc_ipc_करोuदीर्घvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table ipc_table;
	स_नकल(&ipc_table, table, माप(ipc_table));
	ipc_table.data = get_ipc(table);

	वापस proc_करोuदीर्घvec_minmax(&ipc_table, ग_लिखो, buffer,
					lenp, ppos);
पूर्ण

अटल पूर्णांक proc_ipc_स्वतः_msgmni(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table ipc_table;
	पूर्णांक dummy = 0;

	स_नकल(&ipc_table, table, माप(ipc_table));
	ipc_table.data = &dummy;

	अगर (ग_लिखो)
		pr_info_once("writing to auto_msgmni has no effect");

	वापस proc_करोपूर्णांकvec_minmax(&ipc_table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक proc_ipc_sem_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
	व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret, semmni;
	काष्ठा ipc_namespace *ns = current->nsproxy->ipc_ns;

	semmni = ns->sem_ctls[3];
	ret = proc_ipc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर (!ret)
		ret = sem_check_semmni(current->nsproxy->ipc_ns);

	/*
	 * Reset the semmni value अगर an error happens.
	 */
	अगर (ret)
		ns->sem_ctls[3] = semmni;
	वापस ret;
पूर्ण

#अन्यथा
#घोषणा proc_ipc_करोuदीर्घvec_minmax शून्य
#घोषणा proc_ipc_करोपूर्णांकvec	   शून्य
#घोषणा proc_ipc_करोपूर्णांकvec_minmax   शून्य
#घोषणा proc_ipc_करोपूर्णांकvec_minmax_orphans   शून्य
#घोषणा proc_ipc_स्वतः_msgmni	   शून्य
#घोषणा proc_ipc_sem_करोपूर्णांकvec	   शून्य
#पूर्ण_अगर

पूर्णांक ipc_mni = IPCMNI;
पूर्णांक ipc_mni_shअगरt = IPCMNI_SHIFT;
पूर्णांक ipc_min_cycle = RADIX_TREE_MAP_SIZE;

अटल काष्ठा ctl_table ipc_kern_table[] = अणु
	अणु
		.procname	= "shmmax",
		.data		= &init_ipc_ns.shm_ctlmax,
		.maxlen		= माप(init_ipc_ns.shm_ctlmax),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "shmall",
		.data		= &init_ipc_ns.shm_ctlall,
		.maxlen		= माप(init_ipc_ns.shm_ctlall),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "shmmni",
		.data		= &init_ipc_ns.shm_ctlmni,
		.maxlen		= माप(init_ipc_ns.shm_ctlmni),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &ipc_mni,
	पूर्ण,
	अणु
		.procname	= "shm_rmid_forced",
		.data		= &init_ipc_ns.shm_rmid_क्रमced,
		.maxlen		= माप(init_ipc_ns.shm_rmid_क्रमced),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax_orphans,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "msgmax",
		.data		= &init_ipc_ns.msg_ctlmax,
		.maxlen		= माप(init_ipc_ns.msg_ctlmax),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "msgmni",
		.data		= &init_ipc_ns.msg_ctlmni,
		.maxlen		= माप(init_ipc_ns.msg_ctlmni),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &ipc_mni,
	पूर्ण,
	अणु
		.procname	= "auto_msgmni",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_ipc_स्वतः_msgmni,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	=  "msgmnb",
		.data		= &init_ipc_ns.msg_ctlmnb,
		.maxlen		= माप(init_ipc_ns.msg_ctlmnb),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "sem",
		.data		= &init_ipc_ns.sem_ctls,
		.maxlen		= 4*माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_ipc_sem_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	अणु
		.procname	= "sem_next_id",
		.data		= &init_ipc_ns.ids[IPC_SEM_IDS].next_id,
		.maxlen		= माप(init_ipc_ns.ids[IPC_SEM_IDS].next_id),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "msg_next_id",
		.data		= &init_ipc_ns.ids[IPC_MSG_IDS].next_id,
		.maxlen		= माप(init_ipc_ns.ids[IPC_MSG_IDS].next_id),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "shm_next_id",
		.data		= &init_ipc_ns.ids[IPC_SHM_IDS].next_id,
		.maxlen		= माप(init_ipc_ns.ids[IPC_SHM_IDS].next_id),
		.mode		= 0644,
		.proc_handler	= proc_ipc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table ipc_root_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= ipc_kern_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init ipc_sysctl_init(व्योम)
अणु
	रेजिस्टर_sysctl_table(ipc_root_table);
	वापस 0;
पूर्ण

device_initcall(ipc_sysctl_init);

अटल पूर्णांक __init ipc_mni_extend(अक्षर *str)
अणु
	ipc_mni = IPCMNI_EXTEND;
	ipc_mni_shअगरt = IPCMNI_EXTEND_SHIFT;
	ipc_min_cycle = IPCMNI_EXTEND_MIN_CYCLE;
	pr_info("IPCMNI extended to %d.\n", ipc_mni);
	वापस 0;
पूर्ण
early_param("ipcmni_extend", ipc_mni_extend);
