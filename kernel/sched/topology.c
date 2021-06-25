<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Scheduler topology setup/handling methods
 */
#समावेश "sched.h"

DEFINE_MUTEX(sched_करोमुख्यs_mutex);

/* Protected by sched_करोमुख्यs_mutex: */
अटल cpumask_var_t sched_करोमुख्यs_पंचांगpmask;
अटल cpumask_var_t sched_करोमुख्यs_पंचांगpmask2;

#अगर_घोषित CONFIG_SCHED_DEBUG

अटल पूर्णांक __init sched_debug_setup(अक्षर *str)
अणु
	sched_debug_verbose = true;

	वापस 0;
पूर्ण
early_param("sched_verbose", sched_debug_setup);

अटल अंतरभूत bool sched_debug(व्योम)
अणु
	वापस sched_debug_verbose;
पूर्ण

#घोषणा SD_FLAG(_name, mflags) [__##_name] = अणु .meta_flags = mflags, .name = #_name पूर्ण,
स्थिर काष्ठा sd_flag_debug sd_flag_debug[] = अणु
#समावेश <linux/sched/sd_flags.h>
पूर्ण;
#अघोषित SD_FLAG

अटल पूर्णांक sched_करोमुख्य_debug_one(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu, पूर्णांक level,
				  काष्ठा cpumask *groupmask)
अणु
	काष्ठा sched_group *group = sd->groups;
	अचिन्हित दीर्घ flags = sd->flags;
	अचिन्हित पूर्णांक idx;

	cpumask_clear(groupmask);

	prपूर्णांकk(KERN_DEBUG "%*s domain-%d: ", level, "", level);
	prपूर्णांकk(KERN_CONT "span=%*pbl level=%s\n",
	       cpumask_pr_args(sched_करोमुख्य_span(sd)), sd->name);

	अगर (!cpumask_test_cpu(cpu, sched_करोमुख्य_span(sd))) अणु
		prपूर्णांकk(KERN_ERR "ERROR: domain->span does not contain CPU%d\n", cpu);
	पूर्ण
	अगर (group && !cpumask_test_cpu(cpu, sched_group_span(group))) अणु
		prपूर्णांकk(KERN_ERR "ERROR: domain->groups does not contain CPU%d\n", cpu);
	पूर्ण

	क्रम_each_set_bit(idx, &flags, __SD_FLAG_CNT) अणु
		अचिन्हित पूर्णांक flag = BIT(idx);
		अचिन्हित पूर्णांक meta_flags = sd_flag_debug[idx].meta_flags;

		अगर ((meta_flags & SDF_SHARED_CHILD) && sd->child &&
		    !(sd->child->flags & flag))
			prपूर्णांकk(KERN_ERR "ERROR: flag %s set here but not in child\n",
			       sd_flag_debug[idx].name);

		अगर ((meta_flags & SDF_SHARED_PARENT) && sd->parent &&
		    !(sd->parent->flags & flag))
			prपूर्णांकk(KERN_ERR "ERROR: flag %s set here but not in parent\n",
			       sd_flag_debug[idx].name);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%*s groups:", level + 1, "");
	करो अणु
		अगर (!group) अणु
			prपूर्णांकk("\n");
			prपूर्णांकk(KERN_ERR "ERROR: group is NULL\n");
			अवरोध;
		पूर्ण

		अगर (!cpumask_weight(sched_group_span(group))) अणु
			prपूर्णांकk(KERN_CONT "\n");
			prपूर्णांकk(KERN_ERR "ERROR: empty group\n");
			अवरोध;
		पूर्ण

		अगर (!(sd->flags & SD_OVERLAP) &&
		    cpumask_पूर्णांकersects(groupmask, sched_group_span(group))) अणु
			prपूर्णांकk(KERN_CONT "\n");
			prपूर्णांकk(KERN_ERR "ERROR: repeated CPUs\n");
			अवरोध;
		पूर्ण

		cpumask_or(groupmask, groupmask, sched_group_span(group));

		prपूर्णांकk(KERN_CONT " %d:{ span=%*pbl",
				group->sgc->id,
				cpumask_pr_args(sched_group_span(group)));

		अगर ((sd->flags & SD_OVERLAP) &&
		    !cpumask_equal(group_balance_mask(group), sched_group_span(group))) अणु
			prपूर्णांकk(KERN_CONT " mask=%*pbl",
				cpumask_pr_args(group_balance_mask(group)));
		पूर्ण

		अगर (group->sgc->capacity != SCHED_CAPACITY_SCALE)
			prपूर्णांकk(KERN_CONT " cap=%lu", group->sgc->capacity);

		अगर (group == sd->groups && sd->child &&
		    !cpumask_equal(sched_करोमुख्य_span(sd->child),
				   sched_group_span(group))) अणु
			prपूर्णांकk(KERN_ERR "ERROR: domain->groups does not match domain->child\n");
		पूर्ण

		prपूर्णांकk(KERN_CONT " }");

		group = group->next;

		अगर (group != sd->groups)
			prपूर्णांकk(KERN_CONT ",");

	पूर्ण जबतक (group != sd->groups);
	prपूर्णांकk(KERN_CONT "\n");

	अगर (!cpumask_equal(sched_करोमुख्य_span(sd), groupmask))
		prपूर्णांकk(KERN_ERR "ERROR: groups don't span domain->span\n");

	अगर (sd->parent &&
	    !cpumask_subset(groupmask, sched_करोमुख्य_span(sd->parent)))
		prपूर्णांकk(KERN_ERR "ERROR: parent span is not a superset of domain->span\n");
	वापस 0;
पूर्ण

अटल व्योम sched_करोमुख्य_debug(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	पूर्णांक level = 0;

	अगर (!sched_debug_verbose)
		वापस;

	अगर (!sd) अणु
		prपूर्णांकk(KERN_DEBUG "CPU%d attaching NULL sched-domain.\n", cpu);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "CPU%d attaching sched-domain(s):\n", cpu);

	क्रम (;;) अणु
		अगर (sched_करोमुख्य_debug_one(sd, cpu, level, sched_करोमुख्यs_पंचांगpmask))
			अवरोध;
		level++;
		sd = sd->parent;
		अगर (!sd)
			अवरोध;
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_SCHED_DEBUG */

# define sched_debug_verbose 0
# define sched_करोमुख्य_debug(sd, cpu) करो अणु पूर्ण जबतक (0)
अटल अंतरभूत bool sched_debug(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

/* Generate a mask of SD flags with the SDF_NEEDS_GROUPS metaflag */
#घोषणा SD_FLAG(name, mflags) (name * !!((mflags) & SDF_NEEDS_GROUPS)) |
अटल स्थिर अचिन्हित पूर्णांक SD_DEGENERATE_GROUPS_MASK =
#समावेश <linux/sched/sd_flags.h>
0;
#अघोषित SD_FLAG

अटल पूर्णांक sd_degenerate(काष्ठा sched_करोमुख्य *sd)
अणु
	अगर (cpumask_weight(sched_करोमुख्य_span(sd)) == 1)
		वापस 1;

	/* Following flags need at least 2 groups */
	अगर ((sd->flags & SD_DEGENERATE_GROUPS_MASK) &&
	    (sd->groups != sd->groups->next))
		वापस 0;

	/* Following flags करोn't use groups */
	अगर (sd->flags & (SD_WAKE_AFFINE))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक
sd_parent_degenerate(काष्ठा sched_करोमुख्य *sd, काष्ठा sched_करोमुख्य *parent)
अणु
	अचिन्हित दीर्घ cflags = sd->flags, pflags = parent->flags;

	अगर (sd_degenerate(parent))
		वापस 1;

	अगर (!cpumask_equal(sched_करोमुख्य_span(sd), sched_करोमुख्य_span(parent)))
		वापस 0;

	/* Flags needing groups करोn't count अगर only 1 group in parent */
	अगर (parent->groups == parent->groups->next)
		pflags &= ~SD_DEGENERATE_GROUPS_MASK;

	अगर (~cflags & pflags)
		वापस 0;

	वापस 1;
पूर्ण

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
DEFINE_STATIC_KEY_FALSE(sched_energy_present);
अचिन्हित पूर्णांक sysctl_sched_energy_aware = 1;
DEFINE_MUTEX(sched_energy_mutex);
bool sched_energy_update;

व्योम rebuild_sched_करोमुख्यs_energy(व्योम)
अणु
	mutex_lock(&sched_energy_mutex);
	sched_energy_update = true;
	rebuild_sched_करोमुख्यs();
	sched_energy_update = false;
	mutex_unlock(&sched_energy_mutex);
पूर्ण

#अगर_घोषित CONFIG_PROC_SYSCTL
पूर्णांक sched_energy_aware_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret, state;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!ret && ग_लिखो) अणु
		state = अटल_branch_unlikely(&sched_energy_present);
		अगर (state != sysctl_sched_energy_aware)
			rebuild_sched_करोमुख्यs_energy();
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल व्योम मुक्त_pd(काष्ठा perf_करोमुख्य *pd)
अणु
	काष्ठा perf_करोमुख्य *पंचांगp;

	जबतक (pd) अणु
		पंचांगp = pd->next;
		kमुक्त(pd);
		pd = पंचांगp;
	पूर्ण
पूर्ण

अटल काष्ठा perf_करोमुख्य *find_pd(काष्ठा perf_करोमुख्य *pd, पूर्णांक cpu)
अणु
	जबतक (pd) अणु
		अगर (cpumask_test_cpu(cpu, perf_करोमुख्य_span(pd)))
			वापस pd;
		pd = pd->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा perf_करोमुख्य *pd_init(पूर्णांक cpu)
अणु
	काष्ठा em_perf_करोमुख्य *obj = em_cpu_get(cpu);
	काष्ठा perf_करोमुख्य *pd;

	अगर (!obj) अणु
		अगर (sched_debug())
			pr_info("%s: no EM found for CPU%d\n", __func__, cpu);
		वापस शून्य;
	पूर्ण

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस शून्य;
	pd->em_pd = obj;

	वापस pd;
पूर्ण

अटल व्योम perf_करोमुख्य_debug(स्थिर काष्ठा cpumask *cpu_map,
						काष्ठा perf_करोमुख्य *pd)
अणु
	अगर (!sched_debug() || !pd)
		वापस;

	prपूर्णांकk(KERN_DEBUG "root_domain %*pbl:", cpumask_pr_args(cpu_map));

	जबतक (pd) अणु
		prपूर्णांकk(KERN_CONT " pd%d:{ cpus=%*pbl nr_pstate=%d }",
				cpumask_first(perf_करोमुख्य_span(pd)),
				cpumask_pr_args(perf_करोमुख्य_span(pd)),
				em_pd_nr_perf_states(pd->em_pd));
		pd = pd->next;
	पूर्ण

	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम destroy_perf_करोमुख्य_rcu(काष्ठा rcu_head *rp)
अणु
	काष्ठा perf_करोमुख्य *pd;

	pd = container_of(rp, काष्ठा perf_करोमुख्य, rcu);
	मुक्त_pd(pd);
पूर्ण

अटल व्योम sched_energy_set(bool has_eas)
अणु
	अगर (!has_eas && अटल_branch_unlikely(&sched_energy_present)) अणु
		अगर (sched_debug())
			pr_info("%s: stopping EAS\n", __func__);
		अटल_branch_disable_cpuslocked(&sched_energy_present);
	पूर्ण अन्यथा अगर (has_eas && !अटल_branch_unlikely(&sched_energy_present)) अणु
		अगर (sched_debug())
			pr_info("%s: starting EAS\n", __func__);
		अटल_branch_enable_cpuslocked(&sched_energy_present);
	पूर्ण
पूर्ण

/*
 * EAS can be used on a root करोमुख्य अगर it meets all the following conditions:
 *    1. an Energy Model (EM) is available;
 *    2. the SD_ASYM_CPUCAPACITY flag is set in the sched_करोमुख्य hierarchy.
 *    3. no SMT is detected.
 *    4. the EM complनिकासy is low enough to keep scheduling overheads low;
 *    5. schedutil is driving the frequency of all CPUs of the rd;
 *    6. frequency invariance support is present;
 *
 * The complनिकासy of the Energy Model is defined as:
 *
 *              C = nr_pd * (nr_cpus + nr_ps)
 *
 * with parameters defined as:
 *  - nr_pd:    the number of perक्रमmance करोमुख्यs
 *  - nr_cpus:  the number of CPUs
 *  - nr_ps:    the sum of the number of perक्रमmance states of all perक्रमmance
 *              करोमुख्यs (क्रम example, on a प्रणाली with 2 perक्रमmance करोमुख्यs,
 *              with 10 perक्रमmance states each, nr_ps = 2 * 10 = 20).
 *
 * It is generally not a good idea to use such a model in the wake-up path on
 * very complex platक्रमms because of the associated scheduling overheads. The
 * arbitrary स्थिरraपूर्णांक below prevents that. It makes EAS usable up to 16 CPUs
 * with per-CPU DVFS and less than 8 perक्रमmance states each, क्रम example.
 */
#घोषणा EM_MAX_COMPLEXITY 2048

बाह्य काष्ठा cpufreq_governor schedutil_gov;
अटल bool build_perf_करोमुख्यs(स्थिर काष्ठा cpumask *cpu_map)
अणु
	पूर्णांक i, nr_pd = 0, nr_ps = 0, nr_cpus = cpumask_weight(cpu_map);
	काष्ठा perf_करोमुख्य *pd = शून्य, *पंचांगp;
	पूर्णांक cpu = cpumask_first(cpu_map);
	काष्ठा root_करोमुख्य *rd = cpu_rq(cpu)->rd;
	काष्ठा cpufreq_policy *policy;
	काष्ठा cpufreq_governor *gov;

	अगर (!sysctl_sched_energy_aware)
		जाओ मुक्त;

	/* EAS is enabled क्रम asymmetric CPU capacity topologies. */
	अगर (!per_cpu(sd_asym_cpucapacity, cpu)) अणु
		अगर (sched_debug()) अणु
			pr_info("rd %*pbl: CPUs do not have asymmetric capacities\n",
					cpumask_pr_args(cpu_map));
		पूर्ण
		जाओ मुक्त;
	पूर्ण

	/* EAS definitely करोes *not* handle SMT */
	अगर (sched_smt_active()) अणु
		pr_warn("rd %*pbl: Disabling EAS, SMT is not supported\n",
			cpumask_pr_args(cpu_map));
		जाओ मुक्त;
	पूर्ण

	अगर (!arch_scale_freq_invariant()) अणु
		अगर (sched_debug()) अणु
			pr_warn("rd %*pbl: Disabling EAS: frequency-invariant load tracking not yet supported",
				cpumask_pr_args(cpu_map));
		पूर्ण
		जाओ मुक्त;
	पूर्ण

	क्रम_each_cpu(i, cpu_map) अणु
		/* Skip alपढ़ोy covered CPUs. */
		अगर (find_pd(pd, i))
			जारी;

		/* Do not attempt EAS अगर schedutil is not being used. */
		policy = cpufreq_cpu_get(i);
		अगर (!policy)
			जाओ मुक्त;
		gov = policy->governor;
		cpufreq_cpu_put(policy);
		अगर (gov != &schedutil_gov) अणु
			अगर (rd->pd)
				pr_warn("rd %*pbl: Disabling EAS, schedutil is mandatory\n",
						cpumask_pr_args(cpu_map));
			जाओ मुक्त;
		पूर्ण

		/* Create the new pd and add it to the local list. */
		पंचांगp = pd_init(i);
		अगर (!पंचांगp)
			जाओ मुक्त;
		पंचांगp->next = pd;
		pd = पंचांगp;

		/*
		 * Count perक्रमmance करोमुख्यs and perक्रमmance states क्रम the
		 * complनिकासy check.
		 */
		nr_pd++;
		nr_ps += em_pd_nr_perf_states(pd->em_pd);
	पूर्ण

	/* Bail out अगर the Energy Model complनिकासy is too high. */
	अगर (nr_pd * (nr_ps + nr_cpus) > EM_MAX_COMPLEXITY) अणु
		WARN(1, "rd %*pbl: Failed to start EAS, EM complexity is too high\n",
						cpumask_pr_args(cpu_map));
		जाओ मुक्त;
	पूर्ण

	perf_करोमुख्य_debug(cpu_map, pd);

	/* Attach the new list of perक्रमmance करोमुख्यs to the root करोमुख्य. */
	पंचांगp = rd->pd;
	rcu_assign_poपूर्णांकer(rd->pd, pd);
	अगर (पंचांगp)
		call_rcu(&पंचांगp->rcu, destroy_perf_करोमुख्य_rcu);

	वापस !!pd;

मुक्त:
	मुक्त_pd(pd);
	पंचांगp = rd->pd;
	rcu_assign_poपूर्णांकer(rd->pd, शून्य);
	अगर (पंचांगp)
		call_rcu(&पंचांगp->rcu, destroy_perf_करोमुख्य_rcu);

	वापस false;
पूर्ण
#अन्यथा
अटल व्योम मुक्त_pd(काष्ठा perf_करोमुख्य *pd) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ENERGY_MODEL && CONFIG_CPU_FREQ_GOV_SCHEDUTIL*/

अटल व्योम मुक्त_rootकरोमुख्य(काष्ठा rcu_head *rcu)
अणु
	काष्ठा root_करोमुख्य *rd = container_of(rcu, काष्ठा root_करोमुख्य, rcu);

	cpupri_cleanup(&rd->cpupri);
	cpudl_cleanup(&rd->cpudl);
	मुक्त_cpumask_var(rd->dlo_mask);
	मुक्त_cpumask_var(rd->rto_mask);
	मुक्त_cpumask_var(rd->online);
	मुक्त_cpumask_var(rd->span);
	मुक्त_pd(rd->pd);
	kमुक्त(rd);
पूर्ण

व्योम rq_attach_root(काष्ठा rq *rq, काष्ठा root_करोमुख्य *rd)
अणु
	काष्ठा root_करोमुख्य *old_rd = शून्य;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&rq->lock, flags);

	अगर (rq->rd) अणु
		old_rd = rq->rd;

		अगर (cpumask_test_cpu(rq->cpu, old_rd->online))
			set_rq_offline(rq);

		cpumask_clear_cpu(rq->cpu, old_rd->span);

		/*
		 * If we करोnt want to मुक्त the old_rd yet then
		 * set old_rd to शून्य to skip the मुक्तing later
		 * in this function:
		 */
		अगर (!atomic_dec_and_test(&old_rd->refcount))
			old_rd = शून्य;
	पूर्ण

	atomic_inc(&rd->refcount);
	rq->rd = rd;

	cpumask_set_cpu(rq->cpu, rd->span);
	अगर (cpumask_test_cpu(rq->cpu, cpu_active_mask))
		set_rq_online(rq);

	raw_spin_unlock_irqrestore(&rq->lock, flags);

	अगर (old_rd)
		call_rcu(&old_rd->rcu, मुक्त_rootकरोमुख्य);
पूर्ण

व्योम sched_get_rd(काष्ठा root_करोमुख्य *rd)
अणु
	atomic_inc(&rd->refcount);
पूर्ण

व्योम sched_put_rd(काष्ठा root_करोमुख्य *rd)
अणु
	अगर (!atomic_dec_and_test(&rd->refcount))
		वापस;

	call_rcu(&rd->rcu, मुक्त_rootकरोमुख्य);
पूर्ण

अटल पूर्णांक init_rootकरोमुख्य(काष्ठा root_करोमुख्य *rd)
अणु
	अगर (!zalloc_cpumask_var(&rd->span, GFP_KERNEL))
		जाओ out;
	अगर (!zalloc_cpumask_var(&rd->online, GFP_KERNEL))
		जाओ मुक्त_span;
	अगर (!zalloc_cpumask_var(&rd->dlo_mask, GFP_KERNEL))
		जाओ मुक्त_online;
	अगर (!zalloc_cpumask_var(&rd->rto_mask, GFP_KERNEL))
		जाओ मुक्त_dlo_mask;

#अगर_घोषित HAVE_RT_PUSH_IPI
	rd->rto_cpu = -1;
	raw_spin_lock_init(&rd->rto_lock);
	init_irq_work(&rd->rto_push_work, rto_push_irq_work_func);
#पूर्ण_अगर

	rd->visit_gen = 0;
	init_dl_bw(&rd->dl_bw);
	अगर (cpudl_init(&rd->cpudl) != 0)
		जाओ मुक्त_rto_mask;

	अगर (cpupri_init(&rd->cpupri) != 0)
		जाओ मुक्त_cpudl;
	वापस 0;

मुक्त_cpudl:
	cpudl_cleanup(&rd->cpudl);
मुक्त_rto_mask:
	मुक्त_cpumask_var(rd->rto_mask);
मुक्त_dlo_mask:
	मुक्त_cpumask_var(rd->dlo_mask);
मुक्त_online:
	मुक्त_cpumask_var(rd->online);
मुक्त_span:
	मुक्त_cpumask_var(rd->span);
out:
	वापस -ENOMEM;
पूर्ण

/*
 * By शेष the प्रणाली creates a single root-करोमुख्य with all CPUs as
 * members (mimicking the global state we have today).
 */
काष्ठा root_करोमुख्य def_root_करोमुख्य;

व्योम init_defrootकरोमुख्य(व्योम)
अणु
	init_rootकरोमुख्य(&def_root_करोमुख्य);

	atomic_set(&def_root_करोमुख्य.refcount, 1);
पूर्ण

अटल काष्ठा root_करोमुख्य *alloc_rootकरोमुख्य(व्योम)
अणु
	काष्ठा root_करोमुख्य *rd;

	rd = kzalloc(माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस शून्य;

	अगर (init_rootकरोमुख्य(rd) != 0) अणु
		kमुक्त(rd);
		वापस शून्य;
	पूर्ण

	वापस rd;
पूर्ण

अटल व्योम मुक्त_sched_groups(काष्ठा sched_group *sg, पूर्णांक मुक्त_sgc)
अणु
	काष्ठा sched_group *पंचांगp, *first;

	अगर (!sg)
		वापस;

	first = sg;
	करो अणु
		पंचांगp = sg->next;

		अगर (मुक्त_sgc && atomic_dec_and_test(&sg->sgc->ref))
			kमुक्त(sg->sgc);

		अगर (atomic_dec_and_test(&sg->ref))
			kमुक्त(sg);
		sg = पंचांगp;
	पूर्ण जबतक (sg != first);
पूर्ण

अटल व्योम destroy_sched_करोमुख्य(काष्ठा sched_करोमुख्य *sd)
अणु
	/*
	 * A normal sched करोमुख्य may have multiple group references, an
	 * overlapping करोमुख्य, having निजी groups, only one.  Iterate,
	 * dropping group/capacity references, मुक्तing where none reमुख्य.
	 */
	मुक्त_sched_groups(sd->groups, 1);

	अगर (sd->shared && atomic_dec_and_test(&sd->shared->ref))
		kमुक्त(sd->shared);
	kमुक्त(sd);
पूर्ण

अटल व्योम destroy_sched_करोमुख्यs_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा sched_करोमुख्य *sd = container_of(rcu, काष्ठा sched_करोमुख्य, rcu);

	जबतक (sd) अणु
		काष्ठा sched_करोमुख्य *parent = sd->parent;
		destroy_sched_करोमुख्य(sd);
		sd = parent;
	पूर्ण
पूर्ण

अटल व्योम destroy_sched_करोमुख्यs(काष्ठा sched_करोमुख्य *sd)
अणु
	अगर (sd)
		call_rcu(&sd->rcu, destroy_sched_करोमुख्यs_rcu);
पूर्ण

/*
 * Keep a special poपूर्णांकer to the highest sched_करोमुख्य that has
 * SD_SHARE_PKG_RESOURCE set (Last Level Cache Doमुख्य) क्रम this
 * allows us to aव्योम some poपूर्णांकer chasing select_idle_sibling().
 *
 * Also keep a unique ID per करोमुख्य (we use the first CPU number in
 * the cpumask of the करोमुख्य), this allows us to quickly tell अगर
 * two CPUs are in the same cache करोमुख्य, see cpus_share_cache().
 */
DEFINE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_llc);
DEFINE_PER_CPU(पूर्णांक, sd_llc_size);
DEFINE_PER_CPU(पूर्णांक, sd_llc_id);
DEFINE_PER_CPU(काष्ठा sched_करोमुख्य_shared __rcu *, sd_llc_shared);
DEFINE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_numa);
DEFINE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_asym_packing);
DEFINE_PER_CPU(काष्ठा sched_करोमुख्य __rcu *, sd_asym_cpucapacity);
DEFINE_STATIC_KEY_FALSE(sched_asym_cpucapacity);

अटल व्योम update_top_cache_करोमुख्य(पूर्णांक cpu)
अणु
	काष्ठा sched_करोमुख्य_shared *sds = शून्य;
	काष्ठा sched_करोमुख्य *sd;
	पूर्णांक id = cpu;
	पूर्णांक size = 1;

	sd = highest_flag_करोमुख्य(cpu, SD_SHARE_PKG_RESOURCES);
	अगर (sd) अणु
		id = cpumask_first(sched_करोमुख्य_span(sd));
		size = cpumask_weight(sched_करोमुख्य_span(sd));
		sds = sd->shared;
	पूर्ण

	rcu_assign_poपूर्णांकer(per_cpu(sd_llc, cpu), sd);
	per_cpu(sd_llc_size, cpu) = size;
	per_cpu(sd_llc_id, cpu) = id;
	rcu_assign_poपूर्णांकer(per_cpu(sd_llc_shared, cpu), sds);

	sd = lowest_flag_करोमुख्य(cpu, SD_NUMA);
	rcu_assign_poपूर्णांकer(per_cpu(sd_numa, cpu), sd);

	sd = highest_flag_करोमुख्य(cpu, SD_ASYM_PACKING);
	rcu_assign_poपूर्णांकer(per_cpu(sd_asym_packing, cpu), sd);

	sd = lowest_flag_करोमुख्य(cpu, SD_ASYM_CPUCAPACITY);
	rcu_assign_poपूर्णांकer(per_cpu(sd_asym_cpucapacity, cpu), sd);
पूर्ण

/*
 * Attach the करोमुख्य 'sd' to 'cpu' as its base करोमुख्य. Callers must
 * hold the hotplug lock.
 */
अटल व्योम
cpu_attach_करोमुख्य(काष्ठा sched_करोमुख्य *sd, काष्ठा root_करोमुख्य *rd, पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा sched_करोमुख्य *पंचांगp;
	पूर्णांक numa_distance = 0;

	/* Remove the sched करोमुख्यs which करो not contribute to scheduling. */
	क्रम (पंचांगp = sd; पंचांगp; ) अणु
		काष्ठा sched_करोमुख्य *parent = पंचांगp->parent;
		अगर (!parent)
			अवरोध;

		अगर (sd_parent_degenerate(पंचांगp, parent)) अणु
			पंचांगp->parent = parent->parent;
			अगर (parent->parent)
				parent->parent->child = पंचांगp;
			/*
			 * Transfer SD_PREFER_SIBLING करोwn in हाल of a
			 * degenerate parent; the spans match क्रम this
			 * so the property transfers.
			 */
			अगर (parent->flags & SD_PREFER_SIBLING)
				पंचांगp->flags |= SD_PREFER_SIBLING;
			destroy_sched_करोमुख्य(parent);
		पूर्ण अन्यथा
			पंचांगp = पंचांगp->parent;
	पूर्ण

	अगर (sd && sd_degenerate(sd)) अणु
		पंचांगp = sd;
		sd = sd->parent;
		destroy_sched_करोमुख्य(पंचांगp);
		अगर (sd)
			sd->child = शून्य;
	पूर्ण

	क्रम (पंचांगp = sd; पंचांगp; पंचांगp = पंचांगp->parent)
		numa_distance += !!(पंचांगp->flags & SD_NUMA);

	sched_करोमुख्य_debug(sd, cpu);

	rq_attach_root(rq, rd);
	पंचांगp = rq->sd;
	rcu_assign_poपूर्णांकer(rq->sd, sd);
	dirty_sched_करोमुख्य_sysctl(cpu);
	destroy_sched_करोमुख्यs(पंचांगp);

	update_top_cache_करोमुख्य(cpu);
पूर्ण

काष्ठा s_data अणु
	काष्ठा sched_करोमुख्य * __percpu *sd;
	काष्ठा root_करोमुख्य	*rd;
पूर्ण;

क्रमागत s_alloc अणु
	sa_rootकरोमुख्य,
	sa_sd,
	sa_sd_storage,
	sa_none,
पूर्ण;

/*
 * Return the canonical balance CPU क्रम this group, this is the first CPU
 * of this group that's also in the balance mask.
 *
 * The balance mask are all those CPUs that could actually end up at this
 * group. See build_balance_mask().
 *
 * Also see should_we_balance().
 */
पूर्णांक group_balance_cpu(काष्ठा sched_group *sg)
अणु
	वापस cpumask_first(group_balance_mask(sg));
पूर्ण


/*
 * NUMA topology (first पढ़ो the regular topology blurb below)
 *
 * Given a node-distance table, क्रम example:
 *
 *   node   0   1   2   3
 *     0:  10  20  30  20
 *     1:  20  10  20  30
 *     2:  30  20  10  20
 *     3:  20  30  20  10
 *
 * which represents a 4 node ring topology like:
 *
 *   0 ----- 1
 *   |       |
 *   |       |
 *   |       |
 *   3 ----- 2
 *
 * We want to स्थिरruct करोमुख्यs and groups to represent this. The way we go
 * about करोing this is to build the करोमुख्यs on 'hops'. For each NUMA level we
 * स्थिरruct the mask of all nodes reachable in @level hops.
 *
 * For the above NUMA topology that gives 3 levels:
 *
 * NUMA-2	0-3		0-3		0-3		0-3
 *  groups:	अणु0-1,3पूर्ण,अणु1-3पूर्ण	अणु0-2पूर्ण,अणु0,2-3पूर्ण	अणु1-3पूर्ण,अणु0-1,3पूर्ण	अणु0,2-3पूर्ण,अणु0-2पूर्ण
 *
 * NUMA-1	0-1,3		0-2		1-3		0,2-3
 *  groups:	अणु0पूर्ण,अणु1पूर्ण,अणु3पूर्ण	अणु0पूर्ण,अणु1पूर्ण,अणु2पूर्ण	अणु1पूर्ण,अणु2पूर्ण,अणु3पूर्ण	अणु0पूर्ण,अणु2पूर्ण,अणु3पूर्ण
 *
 * NUMA-0	0		1		2		3
 *
 *
 * As can be seen; things करोn't nicely line up as with the regular topology.
 * When we iterate a करोमुख्य in child करोमुख्य chunks some nodes can be
 * represented multiple बार -- hence the "overlap" naming क्रम this part of
 * the topology.
 *
 * In order to minimize this overlap, we only build enough groups to cover the
 * करोमुख्य. For instance Node-0 NUMA-2 would only get groups: 0-1,3 and 1-3.
 *
 * Because:
 *
 *  - the first group of each करोमुख्य is its child करोमुख्य; this
 *    माला_लो us the first 0-1,3
 *  - the only uncovered node is 2, who's child करोमुख्य is 1-3.
 *
 * However, because of the overlap, computing a unique CPU क्रम each group is
 * more complicated. Consider क्रम instance the groups of NODE-1 NUMA-2, both
 * groups include the CPUs of Node-0, जबतक those CPUs would not in fact ever
 * end up at those groups (they would end up in group: 0-1,3).
 *
 * To correct this we have to पूर्णांकroduce the group balance mask. This mask
 * will contain those CPUs in the group that can reach this group given the
 * (child) करोमुख्य tree.
 *
 * With this we can once again compute balance_cpu and sched_group_capacity
 * relations.
 *
 * XXX include words on how balance_cpu is unique and thereक्रमe can be
 * used क्रम sched_group_capacity links.
 *
 *
 * Another 'interesting' topology is:
 *
 *   node   0   1   2   3
 *     0:  10  20  20  30
 *     1:  20  10  20  20
 *     2:  20  20  10  20
 *     3:  30  20  20  10
 *
 * Which looks a little like:
 *
 *   0 ----- 1
 *   |     / |
 *   |   /   |
 *   | /     |
 *   2 ----- 3
 *
 * This topology is asymmetric, nodes 1,2 are fully connected, but nodes 0,3
 * are not.
 *
 * This leads to a few particularly weird हालs where the sched_करोमुख्य's are
 * not of the same number क्रम each CPU. Consider:
 *
 * NUMA-2	0-3						0-3
 *  groups:	अणु0-2पूर्ण,अणु1-3पूर्ण					अणु1-3पूर्ण,अणु0-2पूर्ण
 *
 * NUMA-1	0-2		0-3		0-3		1-3
 *
 * NUMA-0	0		1		2		3
 *
 */


/*
 * Build the balance mask; it contains only those CPUs that can arrive at this
 * group and should be considered to जारी balancing.
 *
 * We करो this during the group creation pass, thereक्रमe the group inक्रमmation
 * isn't complete yet, however since each group represents a (child) करोमुख्य we
 * can fully स्थिरruct this using the sched_करोमुख्य bits (which are alपढ़ोy
 * complete).
 */
अटल व्योम
build_balance_mask(काष्ठा sched_करोमुख्य *sd, काष्ठा sched_group *sg, काष्ठा cpumask *mask)
अणु
	स्थिर काष्ठा cpumask *sg_span = sched_group_span(sg);
	काष्ठा sd_data *sdd = sd->निजी;
	काष्ठा sched_करोमुख्य *sibling;
	पूर्णांक i;

	cpumask_clear(mask);

	क्रम_each_cpu(i, sg_span) अणु
		sibling = *per_cpu_ptr(sdd->sd, i);

		/*
		 * Can happen in the asymmetric हाल, where these siblings are
		 * unused. The mask will not be empty because those CPUs that
		 * करो have the top करोमुख्य _should_ span the करोमुख्य.
		 */
		अगर (!sibling->child)
			जारी;

		/* If we would not end up here, we can't जारी from here */
		अगर (!cpumask_equal(sg_span, sched_करोमुख्य_span(sibling->child)))
			जारी;

		cpumask_set_cpu(i, mask);
	पूर्ण

	/* We must not have empty masks here */
	WARN_ON_ONCE(cpumask_empty(mask));
पूर्ण

/*
 * XXX: This creates per-node group entries; since the load-balancer will
 * immediately access remote memory to स्थिरruct this group's load-balance
 * statistics having the groups node local is of dubious benefit.
 */
अटल काष्ठा sched_group *
build_group_from_child_sched_करोमुख्य(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	काष्ठा sched_group *sg;
	काष्ठा cpumask *sg_span;

	sg = kzalloc_node(माप(काष्ठा sched_group) + cpumask_size(),
			GFP_KERNEL, cpu_to_node(cpu));

	अगर (!sg)
		वापस शून्य;

	sg_span = sched_group_span(sg);
	अगर (sd->child)
		cpumask_copy(sg_span, sched_करोमुख्य_span(sd->child));
	अन्यथा
		cpumask_copy(sg_span, sched_करोमुख्य_span(sd));

	atomic_inc(&sg->ref);
	वापस sg;
पूर्ण

अटल व्योम init_overlap_sched_group(काष्ठा sched_करोमुख्य *sd,
				     काष्ठा sched_group *sg)
अणु
	काष्ठा cpumask *mask = sched_करोमुख्यs_पंचांगpmask2;
	काष्ठा sd_data *sdd = sd->निजी;
	काष्ठा cpumask *sg_span;
	पूर्णांक cpu;

	build_balance_mask(sd, sg, mask);
	cpu = cpumask_first(mask);

	sg->sgc = *per_cpu_ptr(sdd->sgc, cpu);
	अगर (atomic_inc_वापस(&sg->sgc->ref) == 1)
		cpumask_copy(group_balance_mask(sg), mask);
	अन्यथा
		WARN_ON_ONCE(!cpumask_equal(group_balance_mask(sg), mask));

	/*
	 * Initialize sgc->capacity such that even अगर we mess up the
	 * करोमुख्यs and no possible iteration will get us here, we won't
	 * die on a /0 trap.
	 */
	sg_span = sched_group_span(sg);
	sg->sgc->capacity = SCHED_CAPACITY_SCALE * cpumask_weight(sg_span);
	sg->sgc->min_capacity = SCHED_CAPACITY_SCALE;
	sg->sgc->max_capacity = SCHED_CAPACITY_SCALE;
पूर्ण

अटल काष्ठा sched_करोमुख्य *
find_descended_sibling(काष्ठा sched_करोमुख्य *sd, काष्ठा sched_करोमुख्य *sibling)
अणु
	/*
	 * The proper descendant would be the one whose child won't span out
	 * of sd
	 */
	जबतक (sibling->child &&
	       !cpumask_subset(sched_करोमुख्य_span(sibling->child),
			       sched_करोमुख्य_span(sd)))
		sibling = sibling->child;

	/*
	 * As we are referencing sgc across dअगरferent topology level, we need
	 * to go करोwn to skip those sched_करोमुख्यs which करोn't contribute to
	 * scheduling because they will be degenerated in cpu_attach_करोमुख्य
	 */
	जबतक (sibling->child &&
	       cpumask_equal(sched_करोमुख्य_span(sibling->child),
			     sched_करोमुख्य_span(sibling)))
		sibling = sibling->child;

	वापस sibling;
पूर्ण

अटल पूर्णांक
build_overlap_sched_groups(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	काष्ठा sched_group *first = शून्य, *last = शून्य, *sg;
	स्थिर काष्ठा cpumask *span = sched_करोमुख्य_span(sd);
	काष्ठा cpumask *covered = sched_करोमुख्यs_पंचांगpmask;
	काष्ठा sd_data *sdd = sd->निजी;
	काष्ठा sched_करोमुख्य *sibling;
	पूर्णांक i;

	cpumask_clear(covered);

	क्रम_each_cpu_wrap(i, span, cpu) अणु
		काष्ठा cpumask *sg_span;

		अगर (cpumask_test_cpu(i, covered))
			जारी;

		sibling = *per_cpu_ptr(sdd->sd, i);

		/*
		 * Asymmetric node setups can result in situations where the
		 * करोमुख्य tree is of unequal depth, make sure to skip करोमुख्यs
		 * that alपढ़ोy cover the entire range.
		 *
		 * In that हाल build_sched_करोमुख्यs() will have terminated the
		 * iteration early and our sibling sd spans will be empty.
		 * Doमुख्यs should always include the CPU they're built on, so
		 * check that.
		 */
		अगर (!cpumask_test_cpu(i, sched_करोमुख्य_span(sibling)))
			जारी;

		/*
		 * Usually we build sched_group by sibling's child sched_करोमुख्य
		 * But क्रम machines whose NUMA diameter are 3 or above, we move
		 * to build sched_group by sibling's proper descendant's child
		 * करोमुख्य because sibling's child sched_करोमुख्य will span out of
		 * the sched_करोमुख्य being built as below.
		 *
		 * Smallest diameter=3 topology is:
		 *
		 *   node   0   1   2   3
		 *     0:  10  20  30  40
		 *     1:  20  10  20  30
		 *     2:  30  20  10  20
		 *     3:  40  30  20  10
		 *
		 *   0 --- 1 --- 2 --- 3
		 *
		 * NUMA-3       0-3             N/A             N/A             0-3
		 *  groups:     अणु0-2पूर्ण,अणु1-3पूर्ण                                     अणु1-3पूर्ण,अणु0-2पूर्ण
		 *
		 * NUMA-2       0-2             0-3             0-3             1-3
		 *  groups:     अणु0-1पूर्ण,अणु1-3पूर्ण     अणु0-2पूर्ण,अणु2-3पूर्ण     अणु1-3पूर्ण,अणु0-1पूर्ण     अणु2-3पूर्ण,अणु0-2पूर्ण
		 *
		 * NUMA-1       0-1             0-2             1-3             2-3
		 *  groups:     अणु0पूर्ण,अणु1पूर्ण         अणु1पूर्ण,अणु2पूर्ण,अणु0पूर्ण     अणु2पूर्ण,अणु3पूर्ण,अणु1पूर्ण     अणु3पूर्ण,अणु2पूर्ण
		 *
		 * NUMA-0       0               1               2               3
		 *
		 * The NUMA-2 groups क्रम nodes 0 and 3 are obviously buggered, as the
		 * group span isn't a subset of the करोमुख्य span.
		 */
		अगर (sibling->child &&
		    !cpumask_subset(sched_करोमुख्य_span(sibling->child), span))
			sibling = find_descended_sibling(sd, sibling);

		sg = build_group_from_child_sched_करोमुख्य(sibling, cpu);
		अगर (!sg)
			जाओ fail;

		sg_span = sched_group_span(sg);
		cpumask_or(covered, covered, sg_span);

		init_overlap_sched_group(sibling, sg);

		अगर (!first)
			first = sg;
		अगर (last)
			last->next = sg;
		last = sg;
		last->next = first;
	पूर्ण
	sd->groups = first;

	वापस 0;

fail:
	मुक्त_sched_groups(first, 0);

	वापस -ENOMEM;
पूर्ण


/*
 * Package topology (also see the load-balance blurb in fair.c)
 *
 * The scheduler builds a tree काष्ठाure to represent a number of important
 * topology features. By शेष (शेष_topology[]) these include:
 *
 *  - Simultaneous multithपढ़ोing (SMT)
 *  - Multi-Core Cache (MC)
 *  - Package (DIE)
 *
 * Where the last one more or less denotes everything up to a NUMA node.
 *
 * The tree consists of 3 primary data काष्ठाures:
 *
 *	sched_करोमुख्य -> sched_group -> sched_group_capacity
 *	    ^ ^             ^ ^
 *          `-'             `-'
 *
 * The sched_करोमुख्यs are per-CPU and have a two way link (parent & child) and
 * denote the ever growing mask of CPUs beदीर्घing to that level of topology.
 *
 * Each sched_करोमुख्य has a circular (द्विगुन) linked list of sched_group's, each
 * denoting the करोमुख्यs of the level below (or inभागidual CPUs in हाल of the
 * first करोमुख्य level). The sched_group linked by a sched_करोमुख्य includes the
 * CPU of that sched_करोमुख्य [*].
 *
 * Take क्रम instance a 2 thपढ़ोed, 2 core, 2 cache cluster part:
 *
 * CPU   0   1   2   3   4   5   6   7
 *
 * DIE  [                             ]
 * MC   [             ] [             ]
 * SMT  [     ] [     ] [     ] [     ]
 *
 *  - or -
 *
 * DIE  0-7 0-7 0-7 0-7 0-7 0-7 0-7 0-7
 * MC	0-3 0-3 0-3 0-3 4-7 4-7 4-7 4-7
 * SMT  0-1 0-1 2-3 2-3 4-5 4-5 6-7 6-7
 *
 * CPU   0   1   2   3   4   5   6   7
 *
 * One way to think about it is: sched_करोमुख्य moves you up and करोwn among these
 * topology levels, जबतक sched_group moves you sideways through it, at child
 * करोमुख्य granularity.
 *
 * sched_group_capacity ensures each unique sched_group has shared storage.
 *
 * There are two related स्थिरruction problems, both require a CPU that
 * uniquely identअगरy each group (क्रम a given करोमुख्य):
 *
 *  - The first is the balance_cpu (see should_we_balance() and the
 *    load-balance blub in fair.c); क्रम each group we only want 1 CPU to
 *    जारी balancing at a higher करोमुख्य.
 *
 *  - The second is the sched_group_capacity; we want all identical groups
 *    to share a single sched_group_capacity.
 *
 * Since these topologies are exclusive by स्थिरruction. That is, its
 * impossible क्रम an SMT thपढ़ो to beदीर्घ to multiple cores, and cores to
 * be part of multiple caches. There is a very clear and unique location
 * क्रम each CPU in the hierarchy.
 *
 * Thereक्रमe computing a unique CPU क्रम each group is trivial (the iteration
 * mask is redundant and set all 1s; all CPUs in a group will end up at _that_
 * group), we can simply pick the first CPU in each group.
 *
 *
 * [*] in other words, the first group of each करोमुख्य is its child करोमुख्य.
 */

अटल काष्ठा sched_group *get_group(पूर्णांक cpu, काष्ठा sd_data *sdd)
अणु
	काष्ठा sched_करोमुख्य *sd = *per_cpu_ptr(sdd->sd, cpu);
	काष्ठा sched_करोमुख्य *child = sd->child;
	काष्ठा sched_group *sg;
	bool alपढ़ोy_visited;

	अगर (child)
		cpu = cpumask_first(sched_करोमुख्य_span(child));

	sg = *per_cpu_ptr(sdd->sg, cpu);
	sg->sgc = *per_cpu_ptr(sdd->sgc, cpu);

	/* Increase refcounts क्रम claim_allocations: */
	alपढ़ोy_visited = atomic_inc_वापस(&sg->ref) > 1;
	/* sgc visits should follow a similar trend as sg */
	WARN_ON(alपढ़ोy_visited != (atomic_inc_वापस(&sg->sgc->ref) > 1));

	/* If we have alपढ़ोy visited that group, it's alपढ़ोy initialized. */
	अगर (alपढ़ोy_visited)
		वापस sg;

	अगर (child) अणु
		cpumask_copy(sched_group_span(sg), sched_करोमुख्य_span(child));
		cpumask_copy(group_balance_mask(sg), sched_group_span(sg));
	पूर्ण अन्यथा अणु
		cpumask_set_cpu(cpu, sched_group_span(sg));
		cpumask_set_cpu(cpu, group_balance_mask(sg));
	पूर्ण

	sg->sgc->capacity = SCHED_CAPACITY_SCALE * cpumask_weight(sched_group_span(sg));
	sg->sgc->min_capacity = SCHED_CAPACITY_SCALE;
	sg->sgc->max_capacity = SCHED_CAPACITY_SCALE;

	वापस sg;
पूर्ण

/*
 * build_sched_groups will build a circular linked list of the groups
 * covered by the given span, will set each group's ->cpumask correctly,
 * and will initialize their ->sgc.
 *
 * Assumes the sched_करोमुख्य tree is fully स्थिरructed
 */
अटल पूर्णांक
build_sched_groups(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	काष्ठा sched_group *first = शून्य, *last = शून्य;
	काष्ठा sd_data *sdd = sd->निजी;
	स्थिर काष्ठा cpumask *span = sched_करोमुख्य_span(sd);
	काष्ठा cpumask *covered;
	पूर्णांक i;

	lockdep_निश्चित_held(&sched_करोमुख्यs_mutex);
	covered = sched_करोमुख्यs_पंचांगpmask;

	cpumask_clear(covered);

	क्रम_each_cpu_wrap(i, span, cpu) अणु
		काष्ठा sched_group *sg;

		अगर (cpumask_test_cpu(i, covered))
			जारी;

		sg = get_group(i, sdd);

		cpumask_or(covered, covered, sched_group_span(sg));

		अगर (!first)
			first = sg;
		अगर (last)
			last->next = sg;
		last = sg;
	पूर्ण
	last->next = first;
	sd->groups = first;

	वापस 0;
पूर्ण

/*
 * Initialize sched groups cpu_capacity.
 *
 * cpu_capacity indicates the capacity of sched group, which is used जबतक
 * distributing the load between dअगरferent sched groups in a sched करोमुख्य.
 * Typically cpu_capacity क्रम all the groups in a sched करोमुख्य will be same
 * unless there are asymmetries in the topology. If there are asymmetries,
 * group having more cpu_capacity will pickup more load compared to the
 * group having less cpu_capacity.
 */
अटल व्योम init_sched_groups_capacity(पूर्णांक cpu, काष्ठा sched_करोमुख्य *sd)
अणु
	काष्ठा sched_group *sg = sd->groups;

	WARN_ON(!sg);

	करो अणु
		पूर्णांक cpu, max_cpu = -1;

		sg->group_weight = cpumask_weight(sched_group_span(sg));

		अगर (!(sd->flags & SD_ASYM_PACKING))
			जाओ next;

		क्रम_each_cpu(cpu, sched_group_span(sg)) अणु
			अगर (max_cpu < 0)
				max_cpu = cpu;
			अन्यथा अगर (sched_asym_prefer(cpu, max_cpu))
				max_cpu = cpu;
		पूर्ण
		sg->asym_prefer_cpu = max_cpu;

next:
		sg = sg->next;
	पूर्ण जबतक (sg != sd->groups);

	अगर (cpu != group_balance_cpu(sg))
		वापस;

	update_group_capacity(sd, cpu);
पूर्ण

/*
 * Initializers क्रम schedule करोमुख्यs
 * Non-अंतरभूतd to reduce accumulated stack pressure in build_sched_करोमुख्यs()
 */

अटल पूर्णांक शेष_relax_करोमुख्य_level = -1;
पूर्णांक sched_करोमुख्य_level_max;

अटल पूर्णांक __init setup_relax_करोमुख्य_level(अक्षर *str)
अणु
	अगर (kstrtoपूर्णांक(str, 0, &शेष_relax_करोमुख्य_level))
		pr_warn("Unable to set relax_domain_level\n");

	वापस 1;
पूर्ण
__setup("relax_domain_level=", setup_relax_करोमुख्य_level);

अटल व्योम set_करोमुख्य_attribute(काष्ठा sched_करोमुख्य *sd,
				 काष्ठा sched_करोमुख्य_attr *attr)
अणु
	पूर्णांक request;

	अगर (!attr || attr->relax_करोमुख्य_level < 0) अणु
		अगर (शेष_relax_करोमुख्य_level < 0)
			वापस;
		request = शेष_relax_करोमुख्य_level;
	पूर्ण अन्यथा
		request = attr->relax_करोमुख्य_level;

	अगर (sd->level > request) अणु
		/* Turn off idle balance on this करोमुख्य: */
		sd->flags &= ~(SD_BALANCE_WAKE|SD_BALANCE_NEWIDLE);
	पूर्ण
पूर्ण

अटल व्योम __sdt_मुक्त(स्थिर काष्ठा cpumask *cpu_map);
अटल पूर्णांक __sdt_alloc(स्थिर काष्ठा cpumask *cpu_map);

अटल व्योम __मुक्त_करोमुख्य_allocs(काष्ठा s_data *d, क्रमागत s_alloc what,
				 स्थिर काष्ठा cpumask *cpu_map)
अणु
	चयन (what) अणु
	हाल sa_rootकरोमुख्य:
		अगर (!atomic_पढ़ो(&d->rd->refcount))
			मुक्त_rootकरोमुख्य(&d->rd->rcu);
		fallthrough;
	हाल sa_sd:
		मुक्त_percpu(d->sd);
		fallthrough;
	हाल sa_sd_storage:
		__sdt_मुक्त(cpu_map);
		fallthrough;
	हाल sa_none:
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत s_alloc
__visit_करोमुख्य_allocation_hell(काष्ठा s_data *d, स्थिर काष्ठा cpumask *cpu_map)
अणु
	स_रखो(d, 0, माप(*d));

	अगर (__sdt_alloc(cpu_map))
		वापस sa_sd_storage;
	d->sd = alloc_percpu(काष्ठा sched_करोमुख्य *);
	अगर (!d->sd)
		वापस sa_sd_storage;
	d->rd = alloc_rootकरोमुख्य();
	अगर (!d->rd)
		वापस sa_sd;

	वापस sa_rootकरोमुख्य;
पूर्ण

/*
 * शून्य the sd_data elements we've used to build the sched_करोमुख्य and
 * sched_group काष्ठाure so that the subsequent __मुक्त_करोमुख्य_allocs()
 * will not मुक्त the data we're using.
 */
अटल व्योम claim_allocations(पूर्णांक cpu, काष्ठा sched_करोमुख्य *sd)
अणु
	काष्ठा sd_data *sdd = sd->निजी;

	WARN_ON_ONCE(*per_cpu_ptr(sdd->sd, cpu) != sd);
	*per_cpu_ptr(sdd->sd, cpu) = शून्य;

	अगर (atomic_पढ़ो(&(*per_cpu_ptr(sdd->sds, cpu))->ref))
		*per_cpu_ptr(sdd->sds, cpu) = शून्य;

	अगर (atomic_पढ़ो(&(*per_cpu_ptr(sdd->sg, cpu))->ref))
		*per_cpu_ptr(sdd->sg, cpu) = शून्य;

	अगर (atomic_पढ़ो(&(*per_cpu_ptr(sdd->sgc, cpu))->ref))
		*per_cpu_ptr(sdd->sgc, cpu) = शून्य;
पूर्ण

#अगर_घोषित CONFIG_NUMA
क्रमागत numa_topology_type sched_numa_topology_type;

अटल पूर्णांक			sched_करोमुख्यs_numa_levels;
अटल पूर्णांक			sched_करोमुख्यs_curr_level;

पूर्णांक				sched_max_numa_distance;
अटल पूर्णांक			*sched_करोमुख्यs_numa_distance;
अटल काष्ठा cpumask		***sched_करोमुख्यs_numa_masks;
पूर्णांक __पढ़ो_mostly		node_reclaim_distance = RECLAIM_DISTANCE;
#पूर्ण_अगर

/*
 * SD_flags allowed in topology descriptions.
 *
 * These flags are purely descriptive of the topology and करो not prescribe
 * behaviour. Behaviour is artअगरicial and mapped in the below sd_init()
 * function:
 *
 *   SD_SHARE_CPUCAPACITY   - describes SMT topologies
 *   SD_SHARE_PKG_RESOURCES - describes shared caches
 *   SD_NUMA                - describes NUMA topologies
 *
 * Odd one out, which beside describing the topology has a quirk also
 * prescribes the desired behaviour that goes aदीर्घ with it:
 *
 *   SD_ASYM_PACKING        - describes SMT quirks
 */
#घोषणा TOPOLOGY_SD_FLAGS		\
	(SD_SHARE_CPUCAPACITY	|	\
	 SD_SHARE_PKG_RESOURCES |	\
	 SD_NUMA		|	\
	 SD_ASYM_PACKING)

अटल काष्ठा sched_करोमुख्य *
sd_init(काष्ठा sched_करोमुख्य_topology_level *tl,
	स्थिर काष्ठा cpumask *cpu_map,
	काष्ठा sched_करोमुख्य *child, पूर्णांक dflags, पूर्णांक cpu)
अणु
	काष्ठा sd_data *sdd = &tl->data;
	काष्ठा sched_करोमुख्य *sd = *per_cpu_ptr(sdd->sd, cpu);
	पूर्णांक sd_id, sd_weight, sd_flags = 0;

#अगर_घोषित CONFIG_NUMA
	/*
	 * Ugly hack to pass state to sd_numa_mask()...
	 */
	sched_करोमुख्यs_curr_level = tl->numa_level;
#पूर्ण_अगर

	sd_weight = cpumask_weight(tl->mask(cpu));

	अगर (tl->sd_flags)
		sd_flags = (*tl->sd_flags)();
	अगर (WARN_ONCE(sd_flags & ~TOPOLOGY_SD_FLAGS,
			"wrong sd_flags in topology description\n"))
		sd_flags &= TOPOLOGY_SD_FLAGS;

	/* Apply detected topology flags */
	sd_flags |= dflags;

	*sd = (काष्ठा sched_करोमुख्य)अणु
		.min_पूर्णांकerval		= sd_weight,
		.max_पूर्णांकerval		= 2*sd_weight,
		.busy_factor		= 16,
		.imbalance_pct		= 117,

		.cache_nice_tries	= 0,

		.flags			= 1*SD_BALANCE_NEWIDLE
					| 1*SD_BALANCE_EXEC
					| 1*SD_BALANCE_FORK
					| 0*SD_BALANCE_WAKE
					| 1*SD_WAKE_AFFINE
					| 0*SD_SHARE_CPUCAPACITY
					| 0*SD_SHARE_PKG_RESOURCES
					| 0*SD_SERIALIZE
					| 1*SD_PREFER_SIBLING
					| 0*SD_NUMA
					| sd_flags
					,

		.last_balance		= jअगरfies,
		.balance_पूर्णांकerval	= sd_weight,
		.max_newidle_lb_cost	= 0,
		.next_decay_max_lb_cost	= jअगरfies,
		.child			= child,
#अगर_घोषित CONFIG_SCHED_DEBUG
		.name			= tl->name,
#पूर्ण_अगर
	पूर्ण;

	cpumask_and(sched_करोमुख्य_span(sd), cpu_map, tl->mask(cpu));
	sd_id = cpumask_first(sched_करोमुख्य_span(sd));

	/*
	 * Convert topological properties पूर्णांकo behaviour.
	 */

	/* Don't attempt to spपढ़ो across CPUs of dअगरferent capacities. */
	अगर ((sd->flags & SD_ASYM_CPUCAPACITY) && sd->child)
		sd->child->flags &= ~SD_PREFER_SIBLING;

	अगर (sd->flags & SD_SHARE_CPUCAPACITY) अणु
		sd->imbalance_pct = 110;

	पूर्ण अन्यथा अगर (sd->flags & SD_SHARE_PKG_RESOURCES) अणु
		sd->imbalance_pct = 117;
		sd->cache_nice_tries = 1;

#अगर_घोषित CONFIG_NUMA
	पूर्ण अन्यथा अगर (sd->flags & SD_NUMA) अणु
		sd->cache_nice_tries = 2;

		sd->flags &= ~SD_PREFER_SIBLING;
		sd->flags |= SD_SERIALIZE;
		अगर (sched_करोमुख्यs_numa_distance[tl->numa_level] > node_reclaim_distance) अणु
			sd->flags &= ~(SD_BALANCE_EXEC |
				       SD_BALANCE_FORK |
				       SD_WAKE_AFFINE);
		पूर्ण

#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		sd->cache_nice_tries = 1;
	पूर्ण

	/*
	 * For all levels sharing cache; connect a sched_करोमुख्य_shared
	 * instance.
	 */
	अगर (sd->flags & SD_SHARE_PKG_RESOURCES) अणु
		sd->shared = *per_cpu_ptr(sdd->sds, sd_id);
		atomic_inc(&sd->shared->ref);
		atomic_set(&sd->shared->nr_busy_cpus, sd_weight);
	पूर्ण

	sd->निजी = sdd;

	वापस sd;
पूर्ण

/*
 * Topology list, bottom-up.
 */
अटल काष्ठा sched_करोमुख्य_topology_level शेष_topology[] = अणु
#अगर_घोषित CONFIG_SCHED_SMT
	अणु cpu_smt_mask, cpu_smt_flags, SD_INIT_NAME(SMT) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_MC
	अणु cpu_coregroup_mask, cpu_core_flags, SD_INIT_NAME(MC) पूर्ण,
#पूर्ण_अगर
	अणु cpu_cpu_mask, SD_INIT_NAME(DIE) पूर्ण,
	अणु शून्य, पूर्ण,
पूर्ण;

अटल काष्ठा sched_करोमुख्य_topology_level *sched_करोमुख्य_topology =
	शेष_topology;

#घोषणा क्रम_each_sd_topology(tl)			\
	क्रम (tl = sched_करोमुख्य_topology; tl->mask; tl++)

व्योम set_sched_topology(काष्ठा sched_करोमुख्य_topology_level *tl)
अणु
	अगर (WARN_ON_ONCE(sched_smp_initialized))
		वापस;

	sched_करोमुख्य_topology = tl;
पूर्ण

#अगर_घोषित CONFIG_NUMA

अटल स्थिर काष्ठा cpumask *sd_numa_mask(पूर्णांक cpu)
अणु
	वापस sched_करोमुख्यs_numa_masks[sched_करोमुख्यs_curr_level][cpu_to_node(cpu)];
पूर्ण

अटल व्योम sched_numa_warn(स्थिर अक्षर *str)
अणु
	अटल पूर्णांक करोne = false;
	पूर्णांक i,j;

	अगर (करोne)
		वापस;

	करोne = true;

	prपूर्णांकk(KERN_WARNING "ERROR: %s\n\n", str);

	क्रम (i = 0; i < nr_node_ids; i++) अणु
		prपूर्णांकk(KERN_WARNING "  ");
		क्रम (j = 0; j < nr_node_ids; j++)
			prपूर्णांकk(KERN_CONT "%02d ", node_distance(i,j));
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	prपूर्णांकk(KERN_WARNING "\n");
पूर्ण

bool find_numa_distance(पूर्णांक distance)
अणु
	पूर्णांक i;

	अगर (distance == node_distance(0, 0))
		वापस true;

	क्रम (i = 0; i < sched_करोमुख्यs_numa_levels; i++) अणु
		अगर (sched_करोमुख्यs_numa_distance[i] == distance)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * A प्रणाली can have three types of NUMA topology:
 * NUMA_सूचीECT: all nodes are directly connected, or not a NUMA प्रणाली
 * NUMA_GLUELESS_MESH: some nodes reachable through पूर्णांकermediary nodes
 * NUMA_BACKPLANE: nodes can reach other nodes through a backplane
 *
 * The dअगरference between a glueless mesh topology and a backplane
 * topology lies in whether communication between not directly
 * connected nodes goes through पूर्णांकermediary nodes (where programs
 * could run), or through backplane controllers. This affects
 * placement of programs.
 *
 * The type of topology can be discerned with the following tests:
 * - If the maximum distance between any nodes is 1 hop, the प्रणाली
 *   is directly connected.
 * - If क्रम two nodes A and B, located N > 1 hops away from each other,
 *   there is an पूर्णांकermediary node C, which is < N hops away from both
 *   nodes A and B, the प्रणाली is a glueless mesh.
 */
अटल व्योम init_numa_topology_type(व्योम)
अणु
	पूर्णांक a, b, c, n;

	n = sched_max_numa_distance;

	अगर (sched_करोमुख्यs_numa_levels <= 2) अणु
		sched_numa_topology_type = NUMA_सूचीECT;
		वापस;
	पूर्ण

	क्रम_each_online_node(a) अणु
		क्रम_each_online_node(b) अणु
			/* Find two nodes furthest हटाओd from each other. */
			अगर (node_distance(a, b) < n)
				जारी;

			/* Is there an पूर्णांकermediary node between a and b? */
			क्रम_each_online_node(c) अणु
				अगर (node_distance(a, c) < n &&
				    node_distance(b, c) < n) अणु
					sched_numa_topology_type =
							NUMA_GLUELESS_MESH;
					वापस;
				पूर्ण
			पूर्ण

			sched_numa_topology_type = NUMA_BACKPLANE;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


#घोषणा NR_DISTANCE_VALUES (1 << DISTANCE_BITS)

व्योम sched_init_numa(व्योम)
अणु
	काष्ठा sched_करोमुख्य_topology_level *tl;
	अचिन्हित दीर्घ *distance_map;
	पूर्णांक nr_levels = 0;
	पूर्णांक i, j;

	/*
	 * O(nr_nodes^2) deduplicating selection sort -- in order to find the
	 * unique distances in the node_distance() table.
	 */
	distance_map = biपंचांगap_alloc(NR_DISTANCE_VALUES, GFP_KERNEL);
	अगर (!distance_map)
		वापस;

	biपंचांगap_zero(distance_map, NR_DISTANCE_VALUES);
	क्रम (i = 0; i < nr_node_ids; i++) अणु
		क्रम (j = 0; j < nr_node_ids; j++) अणु
			पूर्णांक distance = node_distance(i, j);

			अगर (distance < LOCAL_DISTANCE || distance >= NR_DISTANCE_VALUES) अणु
				sched_numa_warn("Invalid distance value range");
				वापस;
			पूर्ण

			biपंचांगap_set(distance_map, distance, 1);
		पूर्ण
	पूर्ण
	/*
	 * We can now figure out how many unique distance values there are and
	 * allocate memory accordingly.
	 */
	nr_levels = biपंचांगap_weight(distance_map, NR_DISTANCE_VALUES);

	sched_करोमुख्यs_numa_distance = kसुस्मृति(nr_levels, माप(पूर्णांक), GFP_KERNEL);
	अगर (!sched_करोमुख्यs_numa_distance) अणु
		biपंचांगap_मुक्त(distance_map);
		वापस;
	पूर्ण

	क्रम (i = 0, j = 0; i < nr_levels; i++, j++) अणु
		j = find_next_bit(distance_map, NR_DISTANCE_VALUES, j);
		sched_करोमुख्यs_numa_distance[i] = j;
	पूर्ण

	biपंचांगap_मुक्त(distance_map);

	/*
	 * 'nr_levels' contains the number of unique distances
	 *
	 * The sched_करोमुख्यs_numa_distance[] array includes the actual distance
	 * numbers.
	 */

	/*
	 * Here, we should temporarily reset sched_करोमुख्यs_numa_levels to 0.
	 * If it fails to allocate memory क्रम array sched_करोमुख्यs_numa_masks[][],
	 * the array will contain less then 'nr_levels' members. This could be
	 * dangerous when we use it to iterate array sched_करोमुख्यs_numa_masks[][]
	 * in other functions.
	 *
	 * We reset it to 'nr_levels' at the end of this function.
	 */
	sched_करोमुख्यs_numa_levels = 0;

	sched_करोमुख्यs_numa_masks = kzalloc(माप(व्योम *) * nr_levels, GFP_KERNEL);
	अगर (!sched_करोमुख्यs_numa_masks)
		वापस;

	/*
	 * Now क्रम each level, स्थिरruct a mask per node which contains all
	 * CPUs of nodes that are that many hops away from us.
	 */
	क्रम (i = 0; i < nr_levels; i++) अणु
		sched_करोमुख्यs_numa_masks[i] =
			kzalloc(nr_node_ids * माप(व्योम *), GFP_KERNEL);
		अगर (!sched_करोमुख्यs_numa_masks[i])
			वापस;

		क्रम (j = 0; j < nr_node_ids; j++) अणु
			काष्ठा cpumask *mask = kzalloc(cpumask_size(), GFP_KERNEL);
			पूर्णांक k;

			अगर (!mask)
				वापस;

			sched_करोमुख्यs_numa_masks[i][j] = mask;

			क्रम_each_node(k) अणु
				अगर (sched_debug() && (node_distance(j, k) != node_distance(k, j)))
					sched_numa_warn("Node-distance not symmetric");

				अगर (node_distance(j, k) > sched_करोमुख्यs_numa_distance[i])
					जारी;

				cpumask_or(mask, mask, cpumask_of_node(k));
			पूर्ण
		पूर्ण
	पूर्ण

	/* Compute शेष topology size */
	क्रम (i = 0; sched_करोमुख्य_topology[i].mask; i++);

	tl = kzalloc((i + nr_levels + 1) *
			माप(काष्ठा sched_करोमुख्य_topology_level), GFP_KERNEL);
	अगर (!tl)
		वापस;

	/*
	 * Copy the शेष topology bits..
	 */
	क्रम (i = 0; sched_करोमुख्य_topology[i].mask; i++)
		tl[i] = sched_करोमुख्य_topology[i];

	/*
	 * Add the NUMA identity distance, aka single NODE.
	 */
	tl[i++] = (काष्ठा sched_करोमुख्य_topology_level)अणु
		.mask = sd_numa_mask,
		.numa_level = 0,
		SD_INIT_NAME(NODE)
	पूर्ण;

	/*
	 * .. and append 'j' levels of NUMA goodness.
	 */
	क्रम (j = 1; j < nr_levels; i++, j++) अणु
		tl[i] = (काष्ठा sched_करोमुख्य_topology_level)अणु
			.mask = sd_numa_mask,
			.sd_flags = cpu_numa_flags,
			.flags = SDTL_OVERLAP,
			.numa_level = j,
			SD_INIT_NAME(NUMA)
		पूर्ण;
	पूर्ण

	sched_करोमुख्य_topology = tl;

	sched_करोमुख्यs_numa_levels = nr_levels;
	sched_max_numa_distance = sched_करोमुख्यs_numa_distance[nr_levels - 1];

	init_numa_topology_type();
पूर्ण

व्योम sched_करोमुख्यs_numa_masks_set(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक node = cpu_to_node(cpu);
	पूर्णांक i, j;

	क्रम (i = 0; i < sched_करोमुख्यs_numa_levels; i++) अणु
		क्रम (j = 0; j < nr_node_ids; j++) अणु
			अगर (node_distance(j, node) <= sched_करोमुख्यs_numa_distance[i])
				cpumask_set_cpu(cpu, sched_करोमुख्यs_numa_masks[i][j]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम sched_करोमुख्यs_numa_masks_clear(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < sched_करोमुख्यs_numa_levels; i++) अणु
		क्रम (j = 0; j < nr_node_ids; j++)
			cpumask_clear_cpu(cpu, sched_करोमुख्यs_numa_masks[i][j]);
	पूर्ण
पूर्ण

/*
 * sched_numa_find_बंदst() - given the NUMA topology, find the cpu
 *                             बंदst to @cpu from @cpumask.
 * cpumask: cpumask to find a cpu from
 * cpu: cpu to be बंद to
 *
 * वापसs: cpu, or nr_cpu_ids when nothing found.
 */
पूर्णांक sched_numa_find_बंदst(स्थिर काष्ठा cpumask *cpus, पूर्णांक cpu)
अणु
	पूर्णांक i, j = cpu_to_node(cpu);

	क्रम (i = 0; i < sched_करोमुख्यs_numa_levels; i++) अणु
		cpu = cpumask_any_and(cpus, sched_करोमुख्यs_numa_masks[i][j]);
		अगर (cpu < nr_cpu_ids)
			वापस cpu;
	पूर्ण
	वापस nr_cpu_ids;
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA */

अटल पूर्णांक __sdt_alloc(स्थिर काष्ठा cpumask *cpu_map)
अणु
	काष्ठा sched_करोमुख्य_topology_level *tl;
	पूर्णांक j;

	क्रम_each_sd_topology(tl) अणु
		काष्ठा sd_data *sdd = &tl->data;

		sdd->sd = alloc_percpu(काष्ठा sched_करोमुख्य *);
		अगर (!sdd->sd)
			वापस -ENOMEM;

		sdd->sds = alloc_percpu(काष्ठा sched_करोमुख्य_shared *);
		अगर (!sdd->sds)
			वापस -ENOMEM;

		sdd->sg = alloc_percpu(काष्ठा sched_group *);
		अगर (!sdd->sg)
			वापस -ENOMEM;

		sdd->sgc = alloc_percpu(काष्ठा sched_group_capacity *);
		अगर (!sdd->sgc)
			वापस -ENOMEM;

		क्रम_each_cpu(j, cpu_map) अणु
			काष्ठा sched_करोमुख्य *sd;
			काष्ठा sched_करोमुख्य_shared *sds;
			काष्ठा sched_group *sg;
			काष्ठा sched_group_capacity *sgc;

			sd = kzalloc_node(माप(काष्ठा sched_करोमुख्य) + cpumask_size(),
					GFP_KERNEL, cpu_to_node(j));
			अगर (!sd)
				वापस -ENOMEM;

			*per_cpu_ptr(sdd->sd, j) = sd;

			sds = kzalloc_node(माप(काष्ठा sched_करोमुख्य_shared),
					GFP_KERNEL, cpu_to_node(j));
			अगर (!sds)
				वापस -ENOMEM;

			*per_cpu_ptr(sdd->sds, j) = sds;

			sg = kzalloc_node(माप(काष्ठा sched_group) + cpumask_size(),
					GFP_KERNEL, cpu_to_node(j));
			अगर (!sg)
				वापस -ENOMEM;

			sg->next = sg;

			*per_cpu_ptr(sdd->sg, j) = sg;

			sgc = kzalloc_node(माप(काष्ठा sched_group_capacity) + cpumask_size(),
					GFP_KERNEL, cpu_to_node(j));
			अगर (!sgc)
				वापस -ENOMEM;

#अगर_घोषित CONFIG_SCHED_DEBUG
			sgc->id = j;
#पूर्ण_अगर

			*per_cpu_ptr(sdd->sgc, j) = sgc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __sdt_मुक्त(स्थिर काष्ठा cpumask *cpu_map)
अणु
	काष्ठा sched_करोमुख्य_topology_level *tl;
	पूर्णांक j;

	क्रम_each_sd_topology(tl) अणु
		काष्ठा sd_data *sdd = &tl->data;

		क्रम_each_cpu(j, cpu_map) अणु
			काष्ठा sched_करोमुख्य *sd;

			अगर (sdd->sd) अणु
				sd = *per_cpu_ptr(sdd->sd, j);
				अगर (sd && (sd->flags & SD_OVERLAP))
					मुक्त_sched_groups(sd->groups, 0);
				kमुक्त(*per_cpu_ptr(sdd->sd, j));
			पूर्ण

			अगर (sdd->sds)
				kमुक्त(*per_cpu_ptr(sdd->sds, j));
			अगर (sdd->sg)
				kमुक्त(*per_cpu_ptr(sdd->sg, j));
			अगर (sdd->sgc)
				kमुक्त(*per_cpu_ptr(sdd->sgc, j));
		पूर्ण
		मुक्त_percpu(sdd->sd);
		sdd->sd = शून्य;
		मुक्त_percpu(sdd->sds);
		sdd->sds = शून्य;
		मुक्त_percpu(sdd->sg);
		sdd->sg = शून्य;
		मुक्त_percpu(sdd->sgc);
		sdd->sgc = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा sched_करोमुख्य *build_sched_करोमुख्य(काष्ठा sched_करोमुख्य_topology_level *tl,
		स्थिर काष्ठा cpumask *cpu_map, काष्ठा sched_करोमुख्य_attr *attr,
		काष्ठा sched_करोमुख्य *child, पूर्णांक dflags, पूर्णांक cpu)
अणु
	काष्ठा sched_करोमुख्य *sd = sd_init(tl, cpu_map, child, dflags, cpu);

	अगर (child) अणु
		sd->level = child->level + 1;
		sched_करोमुख्य_level_max = max(sched_करोमुख्य_level_max, sd->level);
		child->parent = sd;

		अगर (!cpumask_subset(sched_करोमुख्य_span(child),
				    sched_करोमुख्य_span(sd))) अणु
			pr_err("BUG: arch topology borken\n");
#अगर_घोषित CONFIG_SCHED_DEBUG
			pr_err("     the %s domain not a subset of the %s domain\n",
					child->name, sd->name);
#पूर्ण_अगर
			/* Fixup, ensure @sd has at least @child CPUs. */
			cpumask_or(sched_करोमुख्य_span(sd),
				   sched_करोमुख्य_span(sd),
				   sched_करोमुख्य_span(child));
		पूर्ण

	पूर्ण
	set_करोमुख्य_attribute(sd, attr);

	वापस sd;
पूर्ण

/*
 * Ensure topology masks are sane, i.e. there are no conflicts (overlaps) क्रम
 * any two given CPUs at this (non-NUMA) topology level.
 */
अटल bool topology_span_sane(काष्ठा sched_करोमुख्य_topology_level *tl,
			      स्थिर काष्ठा cpumask *cpu_map, पूर्णांक cpu)
अणु
	पूर्णांक i;

	/* NUMA levels are allowed to overlap */
	अगर (tl->flags & SDTL_OVERLAP)
		वापस true;

	/*
	 * Non-NUMA levels cannot partially overlap - they must be either
	 * completely equal or completely disjoपूर्णांक. Otherwise we can end up
	 * अवरोधing the sched_group lists - i.e. a later get_group() pass
	 * अवरोधs the linking करोne क्रम an earlier span.
	 */
	क्रम_each_cpu(i, cpu_map) अणु
		अगर (i == cpu)
			जारी;
		/*
		 * We should 'and' all those masks with 'cpu_map' to exactly
		 * match the topology we're about to build, but that can only
		 * हटाओ CPUs, which only lessens our ability to detect
		 * overlaps
		 */
		अगर (!cpumask_equal(tl->mask(cpu), tl->mask(i)) &&
		    cpumask_पूर्णांकersects(tl->mask(cpu), tl->mask(i)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Find the sched_करोमुख्य_topology_level where all CPU capacities are visible
 * क्रम all CPUs.
 */
अटल काष्ठा sched_करोमुख्य_topology_level
*asym_cpu_capacity_level(स्थिर काष्ठा cpumask *cpu_map)
अणु
	पूर्णांक i, j, asym_level = 0;
	bool asym = false;
	काष्ठा sched_करोमुख्य_topology_level *tl, *asym_tl = शून्य;
	अचिन्हित दीर्घ cap;

	/* Is there any asymmetry? */
	cap = arch_scale_cpu_capacity(cpumask_first(cpu_map));

	क्रम_each_cpu(i, cpu_map) अणु
		अगर (arch_scale_cpu_capacity(i) != cap) अणु
			asym = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!asym)
		वापस शून्य;

	/*
	 * Examine topology from all CPU's poपूर्णांक of views to detect the lowest
	 * sched_करोमुख्य_topology_level where a highest capacity CPU is visible
	 * to everyone.
	 */
	क्रम_each_cpu(i, cpu_map) अणु
		अचिन्हित दीर्घ max_capacity = arch_scale_cpu_capacity(i);
		पूर्णांक tl_id = 0;

		क्रम_each_sd_topology(tl) अणु
			अगर (tl_id < asym_level)
				जाओ next_level;

			क्रम_each_cpu_and(j, tl->mask(i), cpu_map) अणु
				अचिन्हित दीर्घ capacity;

				capacity = arch_scale_cpu_capacity(j);

				अगर (capacity <= max_capacity)
					जारी;

				max_capacity = capacity;
				asym_level = tl_id;
				asym_tl = tl;
			पूर्ण
next_level:
			tl_id++;
		पूर्ण
	पूर्ण

	वापस asym_tl;
पूर्ण


/*
 * Build sched करोमुख्यs क्रम a given set of CPUs and attach the sched करोमुख्यs
 * to the inभागidual CPUs
 */
अटल पूर्णांक
build_sched_करोमुख्यs(स्थिर काष्ठा cpumask *cpu_map, काष्ठा sched_करोमुख्य_attr *attr)
अणु
	क्रमागत s_alloc alloc_state = sa_none;
	काष्ठा sched_करोमुख्य *sd;
	काष्ठा s_data d;
	काष्ठा rq *rq = शून्य;
	पूर्णांक i, ret = -ENOMEM;
	काष्ठा sched_करोमुख्य_topology_level *tl_asym;
	bool has_asym = false;

	अगर (WARN_ON(cpumask_empty(cpu_map)))
		जाओ error;

	alloc_state = __visit_करोमुख्य_allocation_hell(&d, cpu_map);
	अगर (alloc_state != sa_rootकरोमुख्य)
		जाओ error;

	tl_asym = asym_cpu_capacity_level(cpu_map);

	/* Set up करोमुख्यs क्रम CPUs specअगरied by the cpu_map: */
	क्रम_each_cpu(i, cpu_map) अणु
		काष्ठा sched_करोमुख्य_topology_level *tl;
		पूर्णांक dflags = 0;

		sd = शून्य;
		क्रम_each_sd_topology(tl) अणु
			अगर (tl == tl_asym) अणु
				dflags |= SD_ASYM_CPUCAPACITY;
				has_asym = true;
			पूर्ण

			अगर (WARN_ON(!topology_span_sane(tl, cpu_map, i)))
				जाओ error;

			sd = build_sched_करोमुख्य(tl, cpu_map, attr, sd, dflags, i);

			अगर (tl == sched_करोमुख्य_topology)
				*per_cpu_ptr(d.sd, i) = sd;
			अगर (tl->flags & SDTL_OVERLAP)
				sd->flags |= SD_OVERLAP;
			अगर (cpumask_equal(cpu_map, sched_करोमुख्य_span(sd)))
				अवरोध;
		पूर्ण
	पूर्ण

	/* Build the groups क्रम the करोमुख्यs */
	क्रम_each_cpu(i, cpu_map) अणु
		क्रम (sd = *per_cpu_ptr(d.sd, i); sd; sd = sd->parent) अणु
			sd->span_weight = cpumask_weight(sched_करोमुख्य_span(sd));
			अगर (sd->flags & SD_OVERLAP) अणु
				अगर (build_overlap_sched_groups(sd, i))
					जाओ error;
			पूर्ण अन्यथा अणु
				अगर (build_sched_groups(sd, i))
					जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Calculate CPU capacity क्रम physical packages and nodes */
	क्रम (i = nr_cpumask_bits-1; i >= 0; i--) अणु
		अगर (!cpumask_test_cpu(i, cpu_map))
			जारी;

		क्रम (sd = *per_cpu_ptr(d.sd, i); sd; sd = sd->parent) अणु
			claim_allocations(i, sd);
			init_sched_groups_capacity(i, sd);
		पूर्ण
	पूर्ण

	/* Attach the करोमुख्यs */
	rcu_पढ़ो_lock();
	क्रम_each_cpu(i, cpu_map) अणु
		rq = cpu_rq(i);
		sd = *per_cpu_ptr(d.sd, i);

		/* Use READ_ONCE()/WRITE_ONCE() to aव्योम load/store tearing: */
		अगर (rq->cpu_capacity_orig > READ_ONCE(d.rd->max_cpu_capacity))
			WRITE_ONCE(d.rd->max_cpu_capacity, rq->cpu_capacity_orig);

		cpu_attach_करोमुख्य(sd, d.rd, i);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (has_asym)
		अटल_branch_inc_cpuslocked(&sched_asym_cpucapacity);

	अगर (rq && sched_debug_verbose) अणु
		pr_info("root domain span: %*pbl (max cpu_capacity = %lu)\n",
			cpumask_pr_args(cpu_map), rq->rd->max_cpu_capacity);
	पूर्ण

	ret = 0;
error:
	__मुक्त_करोमुख्य_allocs(&d, alloc_state, cpu_map);

	वापस ret;
पूर्ण

/* Current sched करोमुख्यs: */
अटल cpumask_var_t			*करोms_cur;

/* Number of sched करोमुख्यs in 'doms_cur': */
अटल पूर्णांक				nकरोms_cur;

/* Attributes of custom करोमुख्यs in 'doms_cur' */
अटल काष्ठा sched_करोमुख्य_attr		*dattr_cur;

/*
 * Special हाल: If a kदो_स्मृति() of a करोms_cur partition (array of
 * cpumask) fails, then fallback to a single sched करोमुख्य,
 * as determined by the single cpumask fallback_करोms.
 */
अटल cpumask_var_t			fallback_करोms;

/*
 * arch_update_cpu_topology lets भवized architectures update the
 * CPU core maps. It is supposed to वापस 1 अगर the topology changed
 * or 0 अगर it stayed the same.
 */
पूर्णांक __weak arch_update_cpu_topology(व्योम)
अणु
	वापस 0;
पूर्ण

cpumask_var_t *alloc_sched_करोमुख्यs(अचिन्हित पूर्णांक nकरोms)
अणु
	पूर्णांक i;
	cpumask_var_t *करोms;

	करोms = kदो_स्मृति_array(nकरोms, माप(*करोms), GFP_KERNEL);
	अगर (!करोms)
		वापस शून्य;
	क्रम (i = 0; i < nकरोms; i++) अणु
		अगर (!alloc_cpumask_var(&करोms[i], GFP_KERNEL)) अणु
			मुक्त_sched_करोमुख्यs(करोms, i);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस करोms;
पूर्ण

व्योम मुक्त_sched_करोमुख्यs(cpumask_var_t करोms[], अचिन्हित पूर्णांक nकरोms)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < nकरोms; i++)
		मुक्त_cpumask_var(करोms[i]);
	kमुक्त(करोms);
पूर्ण

/*
 * Set up scheduler करोमुख्यs and groups.  For now this just excludes isolated
 * CPUs, but could be used to exclude other special हालs in the future.
 */
पूर्णांक sched_init_करोमुख्यs(स्थिर काष्ठा cpumask *cpu_map)
अणु
	पूर्णांक err;

	zalloc_cpumask_var(&sched_करोमुख्यs_पंचांगpmask, GFP_KERNEL);
	zalloc_cpumask_var(&sched_करोमुख्यs_पंचांगpmask2, GFP_KERNEL);
	zalloc_cpumask_var(&fallback_करोms, GFP_KERNEL);

	arch_update_cpu_topology();
	nकरोms_cur = 1;
	करोms_cur = alloc_sched_करोमुख्यs(nकरोms_cur);
	अगर (!करोms_cur)
		करोms_cur = &fallback_करोms;
	cpumask_and(करोms_cur[0], cpu_map, housekeeping_cpumask(HK_FLAG_DOMAIN));
	err = build_sched_करोमुख्यs(करोms_cur[0], शून्य);

	वापस err;
पूर्ण

/*
 * Detach sched करोमुख्यs from a group of CPUs specअगरied in cpu_map
 * These CPUs will now be attached to the शून्य करोमुख्य
 */
अटल व्योम detach_destroy_करोमुख्यs(स्थिर काष्ठा cpumask *cpu_map)
अणु
	अचिन्हित पूर्णांक cpu = cpumask_any(cpu_map);
	पूर्णांक i;

	अगर (rcu_access_poपूर्णांकer(per_cpu(sd_asym_cpucapacity, cpu)))
		अटल_branch_dec_cpuslocked(&sched_asym_cpucapacity);

	rcu_पढ़ो_lock();
	क्रम_each_cpu(i, cpu_map)
		cpu_attach_करोमुख्य(शून्य, &def_root_करोमुख्य, i);
	rcu_पढ़ो_unlock();
पूर्ण

/* handle null as "default" */
अटल पूर्णांक dattrs_equal(काष्ठा sched_करोमुख्य_attr *cur, पूर्णांक idx_cur,
			काष्ठा sched_करोमुख्य_attr *new, पूर्णांक idx_new)
अणु
	काष्ठा sched_करोमुख्य_attr पंचांगp;

	/* Fast path: */
	अगर (!new && !cur)
		वापस 1;

	पंचांगp = SD_ATTR_INIT;

	वापस !स_भेद(cur ? (cur + idx_cur) : &पंचांगp,
			new ? (new + idx_new) : &पंचांगp,
			माप(काष्ठा sched_करोमुख्य_attr));
पूर्ण

/*
 * Partition sched करोमुख्यs as specअगरied by the 'ndoms_new'
 * cpumasks in the array करोms_new[] of cpumasks. This compares
 * करोms_new[] to the current sched करोमुख्य partitioning, करोms_cur[].
 * It destroys each deleted करोमुख्य and builds each new करोमुख्य.
 *
 * 'doms_new' is an array of cpumask_var_t's of length 'ndoms_new'.
 * The masks करोn't intersect (don't overlap.) We should setup one
 * sched करोमुख्य क्रम each mask. CPUs not in any of the cpumasks will
 * not be load balanced. If the same cpumask appears both in the
 * current 'doms_cur' domains and in the new 'doms_new', we can leave
 * it as it is.
 *
 * The passed in 'doms_new' should be allocated using
 * alloc_sched_करोमुख्यs.  This routine takes ownership of it and will
 * मुक्त_sched_करोमुख्यs it when करोne with it. If the caller failed the
 * alloc call, then it can pass in करोms_new == शून्य && nकरोms_new == 1,
 * and partition_sched_करोमुख्यs() will fallback to the single partition
 * 'fallback_doms', it also क्रमces the करोमुख्यs to be rebuilt.
 *
 * If करोms_new == शून्य it will be replaced with cpu_online_mask.
 * nकरोms_new == 0 is a special हाल क्रम destroying existing करोमुख्यs,
 * and it will not create the शेष करोमुख्य.
 *
 * Call with hotplug lock and sched_करोमुख्यs_mutex held
 */
व्योम partition_sched_करोमुख्यs_locked(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
				    काष्ठा sched_करोमुख्य_attr *dattr_new)
अणु
	bool __maybe_unused has_eas = false;
	पूर्णांक i, j, n;
	पूर्णांक new_topology;

	lockdep_निश्चित_held(&sched_करोमुख्यs_mutex);

	/* Let the architecture update CPU core mappings: */
	new_topology = arch_update_cpu_topology();

	अगर (!करोms_new) अणु
		WARN_ON_ONCE(dattr_new);
		n = 0;
		करोms_new = alloc_sched_करोमुख्यs(1);
		अगर (करोms_new) अणु
			n = 1;
			cpumask_and(करोms_new[0], cpu_active_mask,
				    housekeeping_cpumask(HK_FLAG_DOMAIN));
		पूर्ण
	पूर्ण अन्यथा अणु
		n = nकरोms_new;
	पूर्ण

	/* Destroy deleted करोमुख्यs: */
	क्रम (i = 0; i < nकरोms_cur; i++) अणु
		क्रम (j = 0; j < n && !new_topology; j++) अणु
			अगर (cpumask_equal(करोms_cur[i], करोms_new[j]) &&
			    dattrs_equal(dattr_cur, i, dattr_new, j)) अणु
				काष्ठा root_करोमुख्य *rd;

				/*
				 * This करोमुख्य won't be destroyed and as such
				 * its dl_bw->total_bw needs to be cleared.  It
				 * will be recomputed in function
				 * update_tasks_root_करोमुख्य().
				 */
				rd = cpu_rq(cpumask_any(करोms_cur[i]))->rd;
				dl_clear_root_करोमुख्य(rd);
				जाओ match1;
			पूर्ण
		पूर्ण
		/* No match - a current sched करोमुख्य not in new करोms_new[] */
		detach_destroy_करोमुख्यs(करोms_cur[i]);
match1:
		;
	पूर्ण

	n = nकरोms_cur;
	अगर (!करोms_new) अणु
		n = 0;
		करोms_new = &fallback_करोms;
		cpumask_and(करोms_new[0], cpu_active_mask,
			    housekeeping_cpumask(HK_FLAG_DOMAIN));
	पूर्ण

	/* Build new करोमुख्यs: */
	क्रम (i = 0; i < nकरोms_new; i++) अणु
		क्रम (j = 0; j < n && !new_topology; j++) अणु
			अगर (cpumask_equal(करोms_new[i], करोms_cur[j]) &&
			    dattrs_equal(dattr_new, i, dattr_cur, j))
				जाओ match2;
		पूर्ण
		/* No match - add a new करोms_new */
		build_sched_करोमुख्यs(करोms_new[i], dattr_new ? dattr_new + i : शून्य);
match2:
		;
	पूर्ण

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
	/* Build perf. करोमुख्यs: */
	क्रम (i = 0; i < nकरोms_new; i++) अणु
		क्रम (j = 0; j < n && !sched_energy_update; j++) अणु
			अगर (cpumask_equal(करोms_new[i], करोms_cur[j]) &&
			    cpu_rq(cpumask_first(करोms_cur[j]))->rd->pd) अणु
				has_eas = true;
				जाओ match3;
			पूर्ण
		पूर्ण
		/* No match - add perf. करोमुख्यs क्रम a new rd */
		has_eas |= build_perf_करोमुख्यs(करोms_new[i]);
match3:
		;
	पूर्ण
	sched_energy_set(has_eas);
#पूर्ण_अगर

	/* Remember the new sched करोमुख्यs: */
	अगर (करोms_cur != &fallback_करोms)
		मुक्त_sched_करोमुख्यs(करोms_cur, nकरोms_cur);

	kमुक्त(dattr_cur);
	करोms_cur = करोms_new;
	dattr_cur = dattr_new;
	nकरोms_cur = nकरोms_new;

	update_sched_करोमुख्य_debugfs();
पूर्ण

/*
 * Call with hotplug lock held
 */
व्योम partition_sched_करोमुख्यs(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
			     काष्ठा sched_करोमुख्य_attr *dattr_new)
अणु
	mutex_lock(&sched_करोमुख्यs_mutex);
	partition_sched_करोमुख्यs_locked(nकरोms_new, करोms_new, dattr_new);
	mutex_unlock(&sched_करोमुख्यs_mutex);
पूर्ण
