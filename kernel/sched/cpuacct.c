<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPU accounting code क्रम task groups.
 *
 * Based on the work by Paul Menage (menage@google.com) and Balbir Singh
 * (balbir@in.ibm.com).
 */
#समावेश <यंत्र/irq_regs.h>
#समावेश "sched.h"

/* Time spent by the tasks of the CPU accounting group executing in ... */
क्रमागत cpuacct_stat_index अणु
	CPUACCT_STAT_USER,	/* ... user mode */
	CPUACCT_STAT_SYSTEM,	/* ... kernel mode */

	CPUACCT_STAT_NSTATS,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpuacct_stat_desc[] = अणु
	[CPUACCT_STAT_USER] = "user",
	[CPUACCT_STAT_SYSTEM] = "system",
पूर्ण;

काष्ठा cpuacct_usage अणु
	u64	usages[CPUACCT_STAT_NSTATS];
पूर्ण;

/* track CPU usage of a group of tasks and its child groups */
काष्ठा cpuacct अणु
	काष्ठा cgroup_subsys_state	css;
	/* cpuusage holds poपूर्णांकer to a u64-type object on every CPU */
	काष्ठा cpuacct_usage __percpu	*cpuusage;
	काष्ठा kernel_cpustat __percpu	*cpustat;
पूर्ण;

अटल अंतरभूत काष्ठा cpuacct *css_ca(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा cpuacct, css) : शून्य;
पूर्ण

/* Return CPU accounting group to which this task beदीर्घs */
अटल अंतरभूत काष्ठा cpuacct *task_ca(काष्ठा task_काष्ठा *tsk)
अणु
	वापस css_ca(task_css(tsk, cpuacct_cgrp_id));
पूर्ण

अटल अंतरभूत काष्ठा cpuacct *parent_ca(काष्ठा cpuacct *ca)
अणु
	वापस css_ca(ca->css.parent);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा cpuacct_usage, root_cpuacct_cpuusage);
अटल काष्ठा cpuacct root_cpuacct = अणु
	.cpustat	= &kernel_cpustat,
	.cpuusage	= &root_cpuacct_cpuusage,
पूर्ण;

/* Create a new CPU accounting group */
अटल काष्ठा cgroup_subsys_state *
cpuacct_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा cpuacct *ca;

	अगर (!parent_css)
		वापस &root_cpuacct.css;

	ca = kzalloc(माप(*ca), GFP_KERNEL);
	अगर (!ca)
		जाओ out;

	ca->cpuusage = alloc_percpu(काष्ठा cpuacct_usage);
	अगर (!ca->cpuusage)
		जाओ out_मुक्त_ca;

	ca->cpustat = alloc_percpu(काष्ठा kernel_cpustat);
	अगर (!ca->cpustat)
		जाओ out_मुक्त_cpuusage;

	वापस &ca->css;

out_मुक्त_cpuusage:
	मुक्त_percpu(ca->cpuusage);
out_मुक्त_ca:
	kमुक्त(ca);
out:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/* Destroy an existing CPU accounting group */
अटल व्योम cpuacct_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cpuacct *ca = css_ca(css);

	मुक्त_percpu(ca->cpustat);
	मुक्त_percpu(ca->cpuusage);
	kमुक्त(ca);
पूर्ण

अटल u64 cpuacct_cpuusage_पढ़ो(काष्ठा cpuacct *ca, पूर्णांक cpu,
				 क्रमागत cpuacct_stat_index index)
अणु
	काष्ठा cpuacct_usage *cpuusage = per_cpu_ptr(ca->cpuusage, cpu);
	u64 data;

	/*
	 * We allow index == CPUACCT_STAT_NSTATS here to पढ़ो
	 * the sum of usages.
	 */
	BUG_ON(index > CPUACCT_STAT_NSTATS);

#अगर_अघोषित CONFIG_64BIT
	/*
	 * Take rq->lock to make 64-bit पढ़ो safe on 32-bit platक्रमms.
	 */
	raw_spin_lock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर

	अगर (index == CPUACCT_STAT_NSTATS) अणु
		पूर्णांक i = 0;

		data = 0;
		क्रम (i = 0; i < CPUACCT_STAT_NSTATS; i++)
			data += cpuusage->usages[i];
	पूर्ण अन्यथा अणु
		data = cpuusage->usages[index];
	पूर्ण

#अगर_अघोषित CONFIG_64BIT
	raw_spin_unlock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर

	वापस data;
पूर्ण

अटल व्योम cpuacct_cpuusage_ग_लिखो(काष्ठा cpuacct *ca, पूर्णांक cpu, u64 val)
अणु
	काष्ठा cpuacct_usage *cpuusage = per_cpu_ptr(ca->cpuusage, cpu);
	पूर्णांक i;

#अगर_अघोषित CONFIG_64BIT
	/*
	 * Take rq->lock to make 64-bit ग_लिखो safe on 32-bit platक्रमms.
	 */
	raw_spin_lock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर

	क्रम (i = 0; i < CPUACCT_STAT_NSTATS; i++)
		cpuusage->usages[i] = val;

#अगर_अघोषित CONFIG_64BIT
	raw_spin_unlock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर
पूर्ण

/* Return total CPU usage (in nanoseconds) of a group */
अटल u64 __cpuusage_पढ़ो(काष्ठा cgroup_subsys_state *css,
			   क्रमागत cpuacct_stat_index index)
अणु
	काष्ठा cpuacct *ca = css_ca(css);
	u64 totalcpuusage = 0;
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		totalcpuusage += cpuacct_cpuusage_पढ़ो(ca, i, index);

	वापस totalcpuusage;
पूर्ण

अटल u64 cpuusage_user_पढ़ो(काष्ठा cgroup_subsys_state *css,
			      काष्ठा cftype *cft)
अणु
	वापस __cpuusage_पढ़ो(css, CPUACCT_STAT_USER);
पूर्ण

अटल u64 cpuusage_sys_पढ़ो(काष्ठा cgroup_subsys_state *css,
			     काष्ठा cftype *cft)
अणु
	वापस __cpuusage_पढ़ो(css, CPUACCT_STAT_SYSTEM);
पूर्ण

अटल u64 cpuusage_पढ़ो(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	वापस __cpuusage_पढ़ो(css, CPUACCT_STAT_NSTATS);
पूर्ण

अटल पूर्णांक cpuusage_ग_लिखो(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			  u64 val)
अणु
	काष्ठा cpuacct *ca = css_ca(css);
	पूर्णांक cpu;

	/*
	 * Only allow '0' here to करो a reset.
	 */
	अगर (val)
		वापस -EINVAL;

	क्रम_each_possible_cpu(cpu)
		cpuacct_cpuusage_ग_लिखो(ca, cpu, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __cpuacct_percpu_seq_show(काष्ठा seq_file *m,
				     क्रमागत cpuacct_stat_index index)
अणु
	काष्ठा cpuacct *ca = css_ca(seq_css(m));
	u64 percpu;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		percpu = cpuacct_cpuusage_पढ़ो(ca, i, index);
		seq_म_लिखो(m, "%llu ", (अचिन्हित दीर्घ दीर्घ) percpu);
	पूर्ण
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक cpuacct_percpu_user_seq_show(काष्ठा seq_file *m, व्योम *V)
अणु
	वापस __cpuacct_percpu_seq_show(m, CPUACCT_STAT_USER);
पूर्ण

अटल पूर्णांक cpuacct_percpu_sys_seq_show(काष्ठा seq_file *m, व्योम *V)
अणु
	वापस __cpuacct_percpu_seq_show(m, CPUACCT_STAT_SYSTEM);
पूर्ण

अटल पूर्णांक cpuacct_percpu_seq_show(काष्ठा seq_file *m, व्योम *V)
अणु
	वापस __cpuacct_percpu_seq_show(m, CPUACCT_STAT_NSTATS);
पूर्ण

अटल पूर्णांक cpuacct_all_seq_show(काष्ठा seq_file *m, व्योम *V)
अणु
	काष्ठा cpuacct *ca = css_ca(seq_css(m));
	पूर्णांक index;
	पूर्णांक cpu;

	seq_माला_दो(m, "cpu");
	क्रम (index = 0; index < CPUACCT_STAT_NSTATS; index++)
		seq_म_लिखो(m, " %s", cpuacct_stat_desc[index]);
	seq_माला_दो(m, "\n");

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpuacct_usage *cpuusage = per_cpu_ptr(ca->cpuusage, cpu);

		seq_म_लिखो(m, "%d", cpu);

		क्रम (index = 0; index < CPUACCT_STAT_NSTATS; index++) अणु
#अगर_अघोषित CONFIG_64BIT
			/*
			 * Take rq->lock to make 64-bit पढ़ो safe on 32-bit
			 * platक्रमms.
			 */
			raw_spin_lock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर

			seq_म_लिखो(m, " %llu", cpuusage->usages[index]);

#अगर_अघोषित CONFIG_64BIT
			raw_spin_unlock_irq(&cpu_rq(cpu)->lock);
#पूर्ण_अगर
		पूर्ण
		seq_माला_दो(m, "\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cpuacct_stats_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा cpuacct *ca = css_ca(seq_css(sf));
	s64 val[CPUACCT_STAT_NSTATS];
	पूर्णांक cpu;
	पूर्णांक stat;

	स_रखो(val, 0, माप(val));
	क्रम_each_possible_cpu(cpu) अणु
		u64 *cpustat = per_cpu_ptr(ca->cpustat, cpu)->cpustat;

		val[CPUACCT_STAT_USER]   += cpustat[CPUTIME_USER];
		val[CPUACCT_STAT_USER]   += cpustat[CPUTIME_NICE];
		val[CPUACCT_STAT_SYSTEM] += cpustat[CPUTIME_SYSTEM];
		val[CPUACCT_STAT_SYSTEM] += cpustat[CPUTIME_IRQ];
		val[CPUACCT_STAT_SYSTEM] += cpustat[CPUTIME_SOFTIRQ];
	पूर्ण

	क्रम (stat = 0; stat < CPUACCT_STAT_NSTATS; stat++) अणु
		seq_म_लिखो(sf, "%s %lld\n",
			   cpuacct_stat_desc[stat],
			   (दीर्घ दीर्घ)nsec_to_घड़ी_प्रकार(val[stat]));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cftype files[] = अणु
	अणु
		.name = "usage",
		.पढ़ो_u64 = cpuusage_पढ़ो,
		.ग_लिखो_u64 = cpuusage_ग_लिखो,
	पूर्ण,
	अणु
		.name = "usage_user",
		.पढ़ो_u64 = cpuusage_user_पढ़ो,
	पूर्ण,
	अणु
		.name = "usage_sys",
		.पढ़ो_u64 = cpuusage_sys_पढ़ो,
	पूर्ण,
	अणु
		.name = "usage_percpu",
		.seq_show = cpuacct_percpu_seq_show,
	पूर्ण,
	अणु
		.name = "usage_percpu_user",
		.seq_show = cpuacct_percpu_user_seq_show,
	पूर्ण,
	अणु
		.name = "usage_percpu_sys",
		.seq_show = cpuacct_percpu_sys_seq_show,
	पूर्ण,
	अणु
		.name = "usage_all",
		.seq_show = cpuacct_all_seq_show,
	पूर्ण,
	अणु
		.name = "stat",
		.seq_show = cpuacct_stats_show,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

/*
 * अक्षरge this task's execution समय to its accounting group.
 *
 * called with rq->lock held.
 */
व्योम cpuacct_अक्षरge(काष्ठा task_काष्ठा *tsk, u64 cpuसमय)
अणु
	काष्ठा cpuacct *ca;
	पूर्णांक index = CPUACCT_STAT_SYSTEM;
	काष्ठा pt_regs *regs = get_irq_regs() ? : task_pt_regs(tsk);

	अगर (regs && user_mode(regs))
		index = CPUACCT_STAT_USER;

	rcu_पढ़ो_lock();

	क्रम (ca = task_ca(tsk); ca; ca = parent_ca(ca))
		__this_cpu_add(ca->cpuusage->usages[index], cpuसमय);

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Add user/प्रणाली समय to cpuacct.
 *
 * Note: it's the caller that updates the account of the root cgroup.
 */
व्योम cpuacct_account_field(काष्ठा task_काष्ठा *tsk, पूर्णांक index, u64 val)
अणु
	काष्ठा cpuacct *ca;

	rcu_पढ़ो_lock();
	क्रम (ca = task_ca(tsk); ca != &root_cpuacct; ca = parent_ca(ca))
		__this_cpu_add(ca->cpustat->cpustat[index], val);
	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा cgroup_subsys cpuacct_cgrp_subsys = अणु
	.css_alloc	= cpuacct_css_alloc,
	.css_मुक्त	= cpuacct_css_मुक्त,
	.legacy_cftypes	= files,
	.early_init	= true,
पूर्ण;
