<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_NUMA_BALANCING_H
#घोषणा _LINUX_SCHED_NUMA_BALANCING_H

/*
 * This is the पूर्णांकerface between the scheduler and the MM that
 * implements memory access pattern based NUMA-balancing:
 */

#समावेश <linux/sched.h>

#घोषणा TNF_MIGRATED	0x01
#घोषणा TNF_NO_GROUP	0x02
#घोषणा TNF_SHARED	0x04
#घोषणा TNF_FAULT_LOCAL	0x08
#घोषणा TNF_MIGRATE_FAIL 0x10

#अगर_घोषित CONFIG_NUMA_BALANCING
बाह्य व्योम task_numa_fault(पूर्णांक last_node, पूर्णांक node, पूर्णांक pages, पूर्णांक flags);
बाह्य pid_t task_numa_group_id(काष्ठा task_काष्ठा *p);
बाह्य व्योम set_numabalancing_state(bool enabled);
बाह्य व्योम task_numa_मुक्त(काष्ठा task_काष्ठा *p, bool final);
बाह्य bool should_numa_migrate_memory(काष्ठा task_काष्ठा *p, काष्ठा page *page,
					पूर्णांक src_nid, पूर्णांक dst_cpu);
#अन्यथा
अटल अंतरभूत व्योम task_numa_fault(पूर्णांक last_node, पूर्णांक node, पूर्णांक pages,
				   पूर्णांक flags)
अणु
पूर्ण
अटल अंतरभूत pid_t task_numa_group_id(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम set_numabalancing_state(bool enabled)
अणु
पूर्ण
अटल अंतरभूत व्योम task_numa_मुक्त(काष्ठा task_काष्ठा *p, bool final)
अणु
पूर्ण
अटल अंतरभूत bool should_numa_migrate_memory(काष्ठा task_काष्ठा *p,
				काष्ठा page *page, पूर्णांक src_nid, पूर्णांक dst_cpu)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_NUMA_BALANCING_H */
