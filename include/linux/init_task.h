<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX__INIT_TASK_H
#घोषणा _LINUX__INIT_TASK_H

#समावेश <linux/rcupdate.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/utsname.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/ipc.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/securebits.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/mm_types.h>

#समावेश <यंत्र/thपढ़ो_info.h>

बाह्य काष्ठा files_काष्ठा init_files;
बाह्य काष्ठा fs_काष्ठा init_fs;
बाह्य काष्ठा nsproxy init_nsproxy;
बाह्य काष्ठा cred init_cred;

#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
#घोषणा INIT_PREV_CPUTIME(x)	.prev_cpuसमय = अणु			\
	.lock = __RAW_SPIN_LOCK_UNLOCKED(x.prev_cpuसमय.lock),		\
पूर्ण,
#अन्यथा
#घोषणा INIT_PREV_CPUTIME(x)
#पूर्ण_अगर

#घोषणा INIT_TASK_COMM "swapper"

/* Attach to the init_task data काष्ठाure क्रम proper alignment */
#अगर_घोषित CONFIG_ARCH_TASK_STRUCT_ON_STACK
#घोषणा __init_task_data __section(".data..init_task")
#अन्यथा
#घोषणा __init_task_data /**/
#पूर्ण_अगर

/* Attach to the thपढ़ो_info data काष्ठाure क्रम proper alignment */
#घोषणा __init_thपढ़ो_info __section(".data..init_thread_info")

#पूर्ण_अगर
