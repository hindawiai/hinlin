<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CPUSET_H
#घोषणा _LINUX_CPUSET_H
/*
 *  cpuset पूर्णांकerface
 *
 *  Copyright (C) 2003 BULL SA
 *  Copyright (C) 2004-2006 Silicon Graphics, Inc.
 *
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/mm.h>
#समावेश <linux/jump_label.h>

#अगर_घोषित CONFIG_CPUSETS

/*
 * Static branch reग_लिखोs can happen in an arbitrary order क्रम a given
 * key. In code paths where we need to loop with पढ़ो_mems_allowed_begin() and
 * पढ़ो_mems_allowed_retry() to get a consistent view of mems_allowed, we need
 * to ensure that begin() always माला_लो rewritten beक्रमe retry() in the
 * disabled -> enabled transition. If not, then अगर local irqs are disabled
 * around the loop, we can deadlock since retry() would always be
 * comparing the latest value of the mems_allowed seqcount against 0 as
 * begin() still would see cpusets_enabled() as false. The enabled -> disabled
 * transition should happen in reverse order क्रम the same reasons (want to stop
 * looking at real value of mems_allowed.sequence in retry() first).
 */
बाह्य काष्ठा अटल_key_false cpusets_pre_enable_key;
बाह्य काष्ठा अटल_key_false cpusets_enabled_key;
अटल अंतरभूत bool cpusets_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&cpusets_enabled_key);
पूर्ण

अटल अंतरभूत व्योम cpuset_inc(व्योम)
अणु
	अटल_branch_inc_cpuslocked(&cpusets_pre_enable_key);
	अटल_branch_inc_cpuslocked(&cpusets_enabled_key);
पूर्ण

अटल अंतरभूत व्योम cpuset_dec(व्योम)
अणु
	अटल_branch_dec_cpuslocked(&cpusets_enabled_key);
	अटल_branch_dec_cpuslocked(&cpusets_pre_enable_key);
पूर्ण

बाह्य पूर्णांक cpuset_init(व्योम);
बाह्य व्योम cpuset_init_smp(व्योम);
बाह्य व्योम cpuset_क्रमce_rebuild(व्योम);
बाह्य व्योम cpuset_update_active_cpus(व्योम);
बाह्य व्योम cpuset_रुको_क्रम_hotplug(व्योम);
बाह्य व्योम cpuset_पढ़ो_lock(व्योम);
बाह्य व्योम cpuset_पढ़ो_unlock(व्योम);
बाह्य व्योम cpuset_cpus_allowed(काष्ठा task_काष्ठा *p, काष्ठा cpumask *mask);
बाह्य व्योम cpuset_cpus_allowed_fallback(काष्ठा task_काष्ठा *p);
बाह्य nodemask_t cpuset_mems_allowed(काष्ठा task_काष्ठा *p);
#घोषणा cpuset_current_mems_allowed (current->mems_allowed)
व्योम cpuset_init_current_mems_allowed(व्योम);
पूर्णांक cpuset_nodemask_valid_mems_allowed(nodemask_t *nodemask);

बाह्य bool __cpuset_node_allowed(पूर्णांक node, gfp_t gfp_mask);

अटल अंतरभूत bool cpuset_node_allowed(पूर्णांक node, gfp_t gfp_mask)
अणु
	अगर (cpusets_enabled())
		वापस __cpuset_node_allowed(node, gfp_mask);
	वापस true;
पूर्ण

अटल अंतरभूत bool __cpuset_zone_allowed(काष्ठा zone *z, gfp_t gfp_mask)
अणु
	वापस __cpuset_node_allowed(zone_to_nid(z), gfp_mask);
पूर्ण

अटल अंतरभूत bool cpuset_zone_allowed(काष्ठा zone *z, gfp_t gfp_mask)
अणु
	अगर (cpusets_enabled())
		वापस __cpuset_zone_allowed(z, gfp_mask);
	वापस true;
पूर्ण

बाह्य पूर्णांक cpuset_mems_allowed_पूर्णांकersects(स्थिर काष्ठा task_काष्ठा *tsk1,
					  स्थिर काष्ठा task_काष्ठा *tsk2);

#घोषणा cpuset_memory_pressure_bump() 				\
	करो अणु							\
		अगर (cpuset_memory_pressure_enabled)		\
			__cpuset_memory_pressure_bump();	\
	पूर्ण जबतक (0)
बाह्य पूर्णांक cpuset_memory_pressure_enabled;
बाह्य व्योम __cpuset_memory_pressure_bump(व्योम);

बाह्य व्योम cpuset_task_status_allowed(काष्ठा seq_file *m,
					काष्ठा task_काष्ठा *task);
बाह्य पूर्णांक proc_cpuset_show(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			    काष्ठा pid *pid, काष्ठा task_काष्ठा *tsk);

बाह्य पूर्णांक cpuset_mem_spपढ़ो_node(व्योम);
बाह्य पूर्णांक cpuset_slab_spपढ़ो_node(व्योम);

अटल अंतरभूत पूर्णांक cpuset_करो_page_mem_spपढ़ो(व्योम)
अणु
	वापस task_spपढ़ो_page(current);
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_करो_slab_mem_spपढ़ो(व्योम)
अणु
	वापस task_spपढ़ो_slab(current);
पूर्ण

बाह्य bool current_cpuset_is_being_rebound(व्योम);

बाह्य व्योम rebuild_sched_करोमुख्यs(व्योम);

बाह्य व्योम cpuset_prपूर्णांक_current_mems_allowed(व्योम);

/*
 * पढ़ो_mems_allowed_begin is required when making decisions involving
 * mems_allowed such as during page allocation. mems_allowed can be updated in
 * parallel and depending on the new value an operation can fail potentially
 * causing process failure. A retry loop with पढ़ो_mems_allowed_begin and
 * पढ़ो_mems_allowed_retry prevents these artअगरicial failures.
 */
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_mems_allowed_begin(व्योम)
अणु
	अगर (!अटल_branch_unlikely(&cpusets_pre_enable_key))
		वापस 0;

	वापस पढ़ो_seqcount_begin(&current->mems_allowed_seq);
पूर्ण

/*
 * If this वापसs true, the operation that took place after
 * पढ़ो_mems_allowed_begin may have failed artअगरicially due to a concurrent
 * update of mems_allowed. It is up to the caller to retry the operation अगर
 * appropriate.
 */
अटल अंतरभूत bool पढ़ो_mems_allowed_retry(अचिन्हित पूर्णांक seq)
अणु
	अगर (!अटल_branch_unlikely(&cpusets_enabled_key))
		वापस false;

	वापस पढ़ो_seqcount_retry(&current->mems_allowed_seq, seq);
पूर्ण

अटल अंतरभूत व्योम set_mems_allowed(nodemask_t nodemask)
अणु
	अचिन्हित दीर्घ flags;

	task_lock(current);
	local_irq_save(flags);
	ग_लिखो_seqcount_begin(&current->mems_allowed_seq);
	current->mems_allowed = nodemask;
	ग_लिखो_seqcount_end(&current->mems_allowed_seq);
	local_irq_restore(flags);
	task_unlock(current);
पूर्ण

#अन्यथा /* !CONFIG_CPUSETS */

अटल अंतरभूत bool cpusets_enabled(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक cpuset_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cpuset_init_smp(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम cpuset_क्रमce_rebuild(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम cpuset_update_active_cpus(व्योम)
अणु
	partition_sched_करोमुख्यs(1, शून्य, शून्य);
पूर्ण

अटल अंतरभूत व्योम cpuset_रुको_क्रम_hotplug(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम cpuset_पढ़ो_lock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpuset_पढ़ो_unlock(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम cpuset_cpus_allowed(काष्ठा task_काष्ठा *p,
				       काष्ठा cpumask *mask)
अणु
	cpumask_copy(mask, cpu_possible_mask);
पूर्ण

अटल अंतरभूत व्योम cpuset_cpus_allowed_fallback(काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत nodemask_t cpuset_mems_allowed(काष्ठा task_काष्ठा *p)
अणु
	वापस node_possible_map;
पूर्ण

#घोषणा cpuset_current_mems_allowed (node_states[N_MEMORY])
अटल अंतरभूत व्योम cpuset_init_current_mems_allowed(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक cpuset_nodemask_valid_mems_allowed(nodemask_t *nodemask)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत bool cpuset_node_allowed(पूर्णांक node, gfp_t gfp_mask)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool __cpuset_zone_allowed(काष्ठा zone *z, gfp_t gfp_mask)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool cpuset_zone_allowed(काष्ठा zone *z, gfp_t gfp_mask)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_mems_allowed_पूर्णांकersects(स्थिर काष्ठा task_काष्ठा *tsk1,
						 स्थिर काष्ठा task_काष्ठा *tsk2)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम cpuset_memory_pressure_bump(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम cpuset_task_status_allowed(काष्ठा seq_file *m,
						काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_mem_spपढ़ो_node(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_slab_spपढ़ो_node(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_करो_page_mem_spपढ़ो(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpuset_करो_slab_mem_spपढ़ो(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool current_cpuset_is_being_rebound(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम rebuild_sched_करोमुख्यs(व्योम)
अणु
	partition_sched_करोमुख्यs(1, शून्य, शून्य);
पूर्ण

अटल अंतरभूत व्योम cpuset_prपूर्णांक_current_mems_allowed(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम set_mems_allowed(nodemask_t nodemask)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_mems_allowed_begin(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool पढ़ो_mems_allowed_retry(अचिन्हित पूर्णांक seq)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* !CONFIG_CPUSETS */

#पूर्ण_अगर /* _LINUX_CPUSET_H */
