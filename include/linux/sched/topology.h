<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_TOPOLOGY_H
#घोषणा _LINUX_SCHED_TOPOLOGY_H

#समावेश <linux/topology.h>

#समावेश <linux/sched/idle.h>

/*
 * sched-करोमुख्यs (multiprocessor balancing) declarations:
 */
#अगर_घोषित CONFIG_SMP

/* Generate SD flag indexes */
#घोषणा SD_FLAG(name, mflags) __##name,
क्रमागत अणु
	#समावेश <linux/sched/sd_flags.h>
	__SD_FLAG_CNT,
पूर्ण;
#अघोषित SD_FLAG
/* Generate SD flag bits */
#घोषणा SD_FLAG(name, mflags) name = 1 << __##name,
क्रमागत अणु
	#समावेश <linux/sched/sd_flags.h>
पूर्ण;
#अघोषित SD_FLAG

#अगर_घोषित CONFIG_SCHED_DEBUG

काष्ठा sd_flag_debug अणु
	अचिन्हित पूर्णांक meta_flags;
	अक्षर *name;
पूर्ण;
बाह्य स्थिर काष्ठा sd_flag_debug sd_flag_debug[];

#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_SMT
अटल अंतरभूत पूर्णांक cpu_smt_flags(व्योम)
अणु
	वापस SD_SHARE_CPUCAPACITY | SD_SHARE_PKG_RESOURCES;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_MC
अटल अंतरभूत पूर्णांक cpu_core_flags(व्योम)
अणु
	वापस SD_SHARE_PKG_RESOURCES;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत पूर्णांक cpu_numa_flags(व्योम)
अणु
	वापस SD_NUMA;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक arch_asym_cpu_priority(पूर्णांक cpu);

काष्ठा sched_करोमुख्य_attr अणु
	पूर्णांक relax_करोमुख्य_level;
पूर्ण;

#घोषणा SD_ATTR_INIT	(काष्ठा sched_करोमुख्य_attr) अणु	\
	.relax_करोमुख्य_level = -1,			\
पूर्ण

बाह्य पूर्णांक sched_करोमुख्य_level_max;

काष्ठा sched_group;

काष्ठा sched_करोमुख्य_shared अणु
	atomic_t	ref;
	atomic_t	nr_busy_cpus;
	पूर्णांक		has_idle_cores;
पूर्ण;

काष्ठा sched_करोमुख्य अणु
	/* These fields must be setup */
	काष्ठा sched_करोमुख्य __rcu *parent;	/* top करोमुख्य must be null terminated */
	काष्ठा sched_करोमुख्य __rcu *child;	/* bottom करोमुख्य must be null terminated */
	काष्ठा sched_group *groups;	/* the balancing groups of the करोमुख्य */
	अचिन्हित दीर्घ min_पूर्णांकerval;	/* Minimum balance पूर्णांकerval ms */
	अचिन्हित दीर्घ max_पूर्णांकerval;	/* Maximum balance पूर्णांकerval ms */
	अचिन्हित पूर्णांक busy_factor;	/* less balancing by factor अगर busy */
	अचिन्हित पूर्णांक imbalance_pct;	/* No balance until over watermark */
	अचिन्हित पूर्णांक cache_nice_tries;	/* Leave cache hot tasks क्रम # tries */

	पूर्णांक nohz_idle;			/* NOHZ IDLE status */
	पूर्णांक flags;			/* See SD_* */
	पूर्णांक level;

	/* Runसमय fields. */
	अचिन्हित दीर्घ last_balance;	/* init to jअगरfies. units in jअगरfies */
	अचिन्हित पूर्णांक balance_पूर्णांकerval;	/* initialise to 1. units in ms. */
	अचिन्हित पूर्णांक nr_balance_failed; /* initialise to 0 */

	/* idle_balance() stats */
	u64 max_newidle_lb_cost;
	अचिन्हित दीर्घ next_decay_max_lb_cost;

	u64 avg_scan_cost;		/* select_idle_sibling */

#अगर_घोषित CONFIG_SCHEDSTATS
	/* load_balance() stats */
	अचिन्हित पूर्णांक lb_count[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_failed[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_balanced[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_imbalance[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_gained[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_hot_gained[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_nobusyg[CPU_MAX_IDLE_TYPES];
	अचिन्हित पूर्णांक lb_nobusyq[CPU_MAX_IDLE_TYPES];

	/* Active load balancing */
	अचिन्हित पूर्णांक alb_count;
	अचिन्हित पूर्णांक alb_failed;
	अचिन्हित पूर्णांक alb_pushed;

	/* SD_BALANCE_EXEC stats */
	अचिन्हित पूर्णांक sbe_count;
	अचिन्हित पूर्णांक sbe_balanced;
	अचिन्हित पूर्णांक sbe_pushed;

	/* SD_BALANCE_FORK stats */
	अचिन्हित पूर्णांक sbf_count;
	अचिन्हित पूर्णांक sbf_balanced;
	अचिन्हित पूर्णांक sbf_pushed;

	/* try_to_wake_up() stats */
	अचिन्हित पूर्णांक ttwu_wake_remote;
	अचिन्हित पूर्णांक ttwu_move_affine;
	अचिन्हित पूर्णांक ttwu_move_balance;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_DEBUG
	अक्षर *name;
#पूर्ण_अगर
	जोड़ अणु
		व्योम *निजी;		/* used during स्थिरruction */
		काष्ठा rcu_head rcu;	/* used during deकाष्ठाion */
	पूर्ण;
	काष्ठा sched_करोमुख्य_shared *shared;

	अचिन्हित पूर्णांक span_weight;
	/*
	 * Span of all CPUs in this करोमुख्य.
	 *
	 * NOTE: this field is variable length. (Allocated dynamically
	 * by attaching extra space to the end of the काष्ठाure,
	 * depending on how many CPUs the kernel has booted up with)
	 */
	अचिन्हित दीर्घ span[];
पूर्ण;

अटल अंतरभूत काष्ठा cpumask *sched_करोमुख्य_span(काष्ठा sched_करोमुख्य *sd)
अणु
	वापस to_cpumask(sd->span);
पूर्ण

बाह्य व्योम partition_sched_करोमुख्यs_locked(पूर्णांक nकरोms_new,
					   cpumask_var_t करोms_new[],
					   काष्ठा sched_करोमुख्य_attr *dattr_new);

बाह्य व्योम partition_sched_करोमुख्यs(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
				    काष्ठा sched_करोमुख्य_attr *dattr_new);

/* Allocate an array of sched करोमुख्यs, क्रम partition_sched_करोमुख्यs(). */
cpumask_var_t *alloc_sched_करोमुख्यs(अचिन्हित पूर्णांक nकरोms);
व्योम मुक्त_sched_करोमुख्यs(cpumask_var_t करोms[], अचिन्हित पूर्णांक nकरोms);

bool cpus_share_cache(पूर्णांक this_cpu, पूर्णांक that_cpu);

प्रकार स्थिर काष्ठा cpumask *(*sched_करोमुख्य_mask_f)(पूर्णांक cpu);
प्रकार पूर्णांक (*sched_करोमुख्य_flags_f)(व्योम);

#घोषणा SDTL_OVERLAP	0x01

काष्ठा sd_data अणु
	काष्ठा sched_करोमुख्य *__percpu *sd;
	काष्ठा sched_करोमुख्य_shared *__percpu *sds;
	काष्ठा sched_group *__percpu *sg;
	काष्ठा sched_group_capacity *__percpu *sgc;
पूर्ण;

काष्ठा sched_करोमुख्य_topology_level अणु
	sched_करोमुख्य_mask_f mask;
	sched_करोमुख्य_flags_f sd_flags;
	पूर्णांक		    flags;
	पूर्णांक		    numa_level;
	काष्ठा sd_data      data;
#अगर_घोषित CONFIG_SCHED_DEBUG
	अक्षर                *name;
#पूर्ण_अगर
पूर्ण;

बाह्य व्योम set_sched_topology(काष्ठा sched_करोमुख्य_topology_level *tl);

#अगर_घोषित CONFIG_SCHED_DEBUG
# define SD_INIT_NAME(type)		.name = #type
#अन्यथा
# define SD_INIT_NAME(type)
#पूर्ण_अगर

#अन्यथा /* CONFIG_SMP */

काष्ठा sched_करोमुख्य_attr;

अटल अंतरभूत व्योम
partition_sched_करोमुख्यs_locked(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
			       काष्ठा sched_करोमुख्य_attr *dattr_new)
अणु
पूर्ण

अटल अंतरभूत व्योम
partition_sched_करोमुख्यs(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
			काष्ठा sched_करोमुख्य_attr *dattr_new)
अणु
पूर्ण

अटल अंतरभूत bool cpus_share_cache(पूर्णांक this_cpu, पूर्णांक that_cpu)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर	/* !CONFIG_SMP */

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
बाह्य व्योम rebuild_sched_करोमुख्यs_energy(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rebuild_sched_करोमुख्यs_energy(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_scale_cpu_capacity
/**
 * arch_scale_cpu_capacity - get the capacity scale factor of a given CPU.
 * @cpu: the CPU in question.
 *
 * Return: the CPU scale factor normalized against SCHED_CAPACITY_SCALE, i.e.
 *
 *             max_perf(cpu)
 *      ----------------------------- * SCHED_CAPACITY_SCALE
 *      max(max_perf(c) : c \in CPUs)
 */
अटल __always_अंतरभूत
अचिन्हित दीर्घ arch_scale_cpu_capacity(पूर्णांक cpu)
अणु
	वापस SCHED_CAPACITY_SCALE;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_scale_thermal_pressure
अटल __always_अंतरभूत
अचिन्हित दीर्घ arch_scale_thermal_pressure(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_set_thermal_pressure
अटल __always_अंतरभूत
व्योम arch_set_thermal_pressure(स्थिर काष्ठा cpumask *cpus,
			       अचिन्हित दीर्घ th_pressure)
अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक task_node(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस cpu_to_node(task_cpu(p));
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_TOPOLOGY_H */
