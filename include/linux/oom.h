<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INCLUDE_LINUX_OOM_H
#घोषणा __INCLUDE_LINUX_OOM_H


#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/nodemask.h>
#समावेश <uapi/linux/oom.h>
#समावेश <linux/sched/coredump.h> /* MMF_* */
#समावेश <linux/mm.h> /* VM_FAULT* */

काष्ठा zonelist;
काष्ठा notअगरier_block;
काष्ठा mem_cgroup;
काष्ठा task_काष्ठा;

क्रमागत oom_स्थिरraपूर्णांक अणु
	CONSTRAINT_NONE,
	CONSTRAINT_CPUSET,
	CONSTRAINT_MEMORY_POLICY,
	CONSTRAINT_MEMCG,
पूर्ण;

/*
 * Details of the page allocation that triggered the oom समाप्तer that are used to
 * determine what should be समाप्तed.
 */
काष्ठा oom_control अणु
	/* Used to determine cpuset */
	काष्ठा zonelist *zonelist;

	/* Used to determine mempolicy */
	nodemask_t *nodemask;

	/* Memory cgroup in which oom is invoked, or शून्य क्रम global oom */
	काष्ठा mem_cgroup *memcg;

	/* Used to determine cpuset and node locality requirement */
	स्थिर gfp_t gfp_mask;

	/*
	 * order == -1 means the oom समाप्त is required by sysrq, otherwise only
	 * क्रम display purposes.
	 */
	स्थिर पूर्णांक order;

	/* Used by oom implementation, करो not set */
	अचिन्हित दीर्घ totalpages;
	काष्ठा task_काष्ठा *chosen;
	दीर्घ chosen_poपूर्णांकs;

	/* Used to prपूर्णांक the स्थिरraपूर्णांक info. */
	क्रमागत oom_स्थिरraपूर्णांक स्थिरraपूर्णांक;
पूर्ण;

बाह्य काष्ठा mutex oom_lock;
बाह्य काष्ठा mutex oom_adj_mutex;

अटल अंतरभूत व्योम set_current_oom_origin(व्योम)
अणु
	current->संकेत->oom_flag_origin = true;
पूर्ण

अटल अंतरभूत व्योम clear_current_oom_origin(व्योम)
अणु
	current->संकेत->oom_flag_origin = false;
पूर्ण

अटल अंतरभूत bool oom_task_origin(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस p->संकेत->oom_flag_origin;
पूर्ण

अटल अंतरभूत bool tsk_is_oom_victim(काष्ठा task_काष्ठा * tsk)
अणु
	वापस tsk->संकेत->oom_mm;
पूर्ण

/*
 * Use this helper अगर tsk->mm != mm and the victim mm needs a special
 * handling. This is guaranteed to stay true after once set.
 */
अटल अंतरभूत bool mm_is_oom_victim(काष्ठा mm_काष्ठा *mm)
अणु
	वापस test_bit(MMF_OOM_VICTIM, &mm->flags);
पूर्ण

/*
 * Checks whether a page fault on the given mm is still reliable.
 * This is no दीर्घer true अगर the oom reaper started to reap the
 * address space which is reflected by MMF_UNSTABLE flag set in
 * the mm. At that moment any !shared mapping would lose the content
 * and could cause a memory corruption (zero pages instead of the
 * original content).
 *
 * User should call this beक्रमe establishing a page table entry क्रम
 * a !shared mapping and under the proper page table lock.
 *
 * Return 0 when the PF is safe VM_FAULT_SIGBUS otherwise.
 */
अटल अंतरभूत vm_fault_t check_stable_address_space(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (unlikely(test_bit(MMF_UNSTABLE, &mm->flags)))
		वापस VM_FAULT_SIGBUS;
	वापस 0;
पूर्ण

bool __oom_reap_task_mm(काष्ठा mm_काष्ठा *mm);

दीर्घ oom_badness(काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ totalpages);

बाह्य bool out_of_memory(काष्ठा oom_control *oc);

बाह्य व्योम निकास_oom_victim(व्योम);

बाह्य पूर्णांक रेजिस्टर_oom_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक unरेजिस्टर_oom_notअगरier(काष्ठा notअगरier_block *nb);

बाह्य bool oom_समाप्तer_disable(चिन्हित दीर्घ समयout);
बाह्य व्योम oom_समाप्तer_enable(व्योम);

बाह्य काष्ठा task_काष्ठा *find_lock_task_mm(काष्ठा task_काष्ठा *p);

/* sysctls */
बाह्य पूर्णांक sysctl_oom_dump_tasks;
बाह्य पूर्णांक sysctl_oom_समाप्त_allocating_task;
बाह्य पूर्णांक sysctl_panic_on_oom;
#पूर्ण_अगर /* _INCLUDE_LINUX_OOM_H */
