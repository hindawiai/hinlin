<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/sched/debug.c
 *
 * Prपूर्णांक the CFS rbtree and other debugging details
 *
 * Copyright(C) 2007, Red Hat, Inc., Ingo Molnar
 */
#समावेश "sched.h"

/*
 * This allows prपूर्णांकing both to /proc/sched_debug and
 * to the console
 */
#घोषणा SEQ_म_लिखो(m, x...)			\
 करो अणु						\
	अगर (m)					\
		seq_म_लिखो(m, x);		\
	अन्यथा					\
		pr_cont(x);			\
 पूर्ण जबतक (0)

/*
 * Ease the prपूर्णांकing of nsec fields:
 */
अटल दीर्घ दीर्घ nsec_high(अचिन्हित दीर्घ दीर्घ nsec)
अणु
	अगर ((दीर्घ दीर्घ)nsec < 0) अणु
		nsec = -nsec;
		करो_भाग(nsec, 1000000);
		वापस -nsec;
	पूर्ण
	करो_भाग(nsec, 1000000);

	वापस nsec;
पूर्ण

अटल अचिन्हित दीर्घ nsec_low(अचिन्हित दीर्घ दीर्घ nsec)
अणु
	अगर ((दीर्घ दीर्घ)nsec < 0)
		nsec = -nsec;

	वापस करो_भाग(nsec, 1000000);
पूर्ण

#घोषणा SPLIT_NS(x) nsec_high(x), nsec_low(x)

#घोषणा SCHED_FEAT(name, enabled)	\
	#name ,

अटल स्थिर अक्षर * स्थिर sched_feat_names[] = अणु
#समावेश "features.h"
पूर्ण;

#अघोषित SCHED_FEAT

अटल पूर्णांक sched_feat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __SCHED_FEAT_NR; i++) अणु
		अगर (!(sysctl_sched_features & (1UL << i)))
			seq_माला_दो(m, "NO_");
		seq_म_लिखो(m, "%s ", sched_feat_names[i]);
	पूर्ण
	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_JUMP_LABEL

#घोषणा jump_label_key__true  STATIC_KEY_INIT_TRUE
#घोषणा jump_label_key__false STATIC_KEY_INIT_FALSE

#घोषणा SCHED_FEAT(name, enabled)	\
	jump_label_key__##enabled ,

काष्ठा अटल_key sched_feat_keys[__SCHED_FEAT_NR] = अणु
#समावेश "features.h"
पूर्ण;

#अघोषित SCHED_FEAT

अटल व्योम sched_feat_disable(पूर्णांक i)
अणु
	अटल_key_disable_cpuslocked(&sched_feat_keys[i]);
पूर्ण

अटल व्योम sched_feat_enable(पूर्णांक i)
अणु
	अटल_key_enable_cpuslocked(&sched_feat_keys[i]);
पूर्ण
#अन्यथा
अटल व्योम sched_feat_disable(पूर्णांक i) अणु पूर्ण;
अटल व्योम sched_feat_enable(पूर्णांक i) अणु पूर्ण;
#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

अटल पूर्णांक sched_feat_set(अक्षर *cmp)
अणु
	पूर्णांक i;
	पूर्णांक neg = 0;

	अगर (म_भेदन(cmp, "NO_", 3) == 0) अणु
		neg = 1;
		cmp += 3;
	पूर्ण

	i = match_string(sched_feat_names, __SCHED_FEAT_NR, cmp);
	अगर (i < 0)
		वापस i;

	अगर (neg) अणु
		sysctl_sched_features &= ~(1UL << i);
		sched_feat_disable(i);
	पूर्ण अन्यथा अणु
		sysctl_sched_features |= (1UL << i);
		sched_feat_enable(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
sched_feat_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];
	अक्षर *cmp;
	पूर्णांक ret;
	काष्ठा inode *inode;

	अगर (cnt > 63)
		cnt = 63;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;
	cmp = म_मालाip(buf);

	/* Ensure the अटल_key reमुख्यs in a consistent state */
	inode = file_inode(filp);
	cpus_पढ़ो_lock();
	inode_lock(inode);
	ret = sched_feat_set(cmp);
	inode_unlock(inode);
	cpus_पढ़ो_unlock();
	अगर (ret < 0)
		वापस ret;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल पूर्णांक sched_feat_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, sched_feat_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations sched_feat_fops = अणु
	.खोलो		= sched_feat_खोलो,
	.ग_लिखो		= sched_feat_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#अगर_घोषित CONFIG_SMP

अटल sमाप_प्रकार sched_scaling_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[16];

	अगर (cnt > 15)
		cnt = 15;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	अगर (kstrtouपूर्णांक(buf, 10, &sysctl_sched_tunable_scaling))
		वापस -EINVAL;

	अगर (sched_update_scaling())
		वापस -EINVAL;

	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल पूर्णांक sched_scaling_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", sysctl_sched_tunable_scaling);
	वापस 0;
पूर्ण

अटल पूर्णांक sched_scaling_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, sched_scaling_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations sched_scaling_fops = अणु
	.खोलो		= sched_scaling_खोलो,
	.ग_लिखो		= sched_scaling_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#पूर्ण_अगर /* SMP */

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC

अटल sमाप_प्रकार sched_dynamic_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[16];
	पूर्णांक mode;

	अगर (cnt > 15)
		cnt = 15;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;
	mode = sched_dynamic_mode(म_मालाip(buf));
	अगर (mode < 0)
		वापस mode;

	sched_dynamic_update(mode);

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल पूर्णांक sched_dynamic_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अटल स्थिर अक्षर * preempt_modes[] = अणु
		"none", "voluntary", "full"
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(preempt_modes); i++) अणु
		अगर (preempt_dynamic_mode == i)
			seq_माला_दो(m, "(");
		seq_माला_दो(m, preempt_modes[i]);
		अगर (preempt_dynamic_mode == i)
			seq_माला_दो(m, ")");

		seq_माला_दो(m, " ");
	पूर्ण

	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sched_dynamic_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, sched_dynamic_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations sched_dynamic_fops = अणु
	.खोलो		= sched_dynamic_खोलो,
	.ग_लिखो		= sched_dynamic_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PREEMPT_DYNAMIC */

__पढ़ो_mostly bool sched_debug_verbose;

अटल स्थिर काष्ठा seq_operations sched_debug_sops;

अटल पूर्णांक sched_debug_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस seq_खोलो(filp, &sched_debug_sops);
पूर्ण

अटल स्थिर काष्ठा file_operations sched_debug_fops = अणु
	.खोलो		= sched_debug_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल काष्ठा dentry *debugfs_sched;

अटल __init पूर्णांक sched_init_debug(व्योम)
अणु
	काष्ठा dentry __maybe_unused *numa;

	debugfs_sched = debugfs_create_dir("sched", शून्य);

	debugfs_create_file("features", 0644, debugfs_sched, शून्य, &sched_feat_fops);
	debugfs_create_bool("verbose", 0644, debugfs_sched, &sched_debug_verbose);
#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
	debugfs_create_file("preempt", 0644, debugfs_sched, शून्य, &sched_dynamic_fops);
#पूर्ण_अगर

	debugfs_create_u32("latency_ns", 0644, debugfs_sched, &sysctl_sched_latency);
	debugfs_create_u32("min_granularity_ns", 0644, debugfs_sched, &sysctl_sched_min_granularity);
	debugfs_create_u32("wakeup_granularity_ns", 0644, debugfs_sched, &sysctl_sched_wakeup_granularity);

	debugfs_create_u32("latency_warn_ms", 0644, debugfs_sched, &sysctl_resched_latency_warn_ms);
	debugfs_create_u32("latency_warn_once", 0644, debugfs_sched, &sysctl_resched_latency_warn_once);

#अगर_घोषित CONFIG_SMP
	debugfs_create_file("tunable_scaling", 0644, debugfs_sched, शून्य, &sched_scaling_fops);
	debugfs_create_u32("migration_cost_ns", 0644, debugfs_sched, &sysctl_sched_migration_cost);
	debugfs_create_u32("nr_migrate", 0644, debugfs_sched, &sysctl_sched_nr_migrate);

	mutex_lock(&sched_करोमुख्यs_mutex);
	update_sched_करोमुख्य_debugfs();
	mutex_unlock(&sched_करोमुख्यs_mutex);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_BALANCING
	numa = debugfs_create_dir("numa_balancing", debugfs_sched);

	debugfs_create_u32("scan_delay_ms", 0644, numa, &sysctl_numa_balancing_scan_delay);
	debugfs_create_u32("scan_period_min_ms", 0644, numa, &sysctl_numa_balancing_scan_period_min);
	debugfs_create_u32("scan_period_max_ms", 0644, numa, &sysctl_numa_balancing_scan_period_max);
	debugfs_create_u32("scan_size_mb", 0644, numa, &sysctl_numa_balancing_scan_size);
#पूर्ण_अगर

	debugfs_create_file("debug", 0444, debugfs_sched, शून्य, &sched_debug_fops);

	वापस 0;
पूर्ण
late_initcall(sched_init_debug);

#अगर_घोषित CONFIG_SMP

अटल cpumask_var_t		sd_sysctl_cpus;
अटल काष्ठा dentry		*sd_dentry;

अटल पूर्णांक sd_flags_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ flags = *(अचिन्हित पूर्णांक *)m->निजी;
	पूर्णांक idx;

	क्रम_each_set_bit(idx, &flags, __SD_FLAG_CNT) अणु
		seq_माला_दो(m, sd_flag_debug[idx].name);
		seq_माला_दो(m, " ");
	पूर्ण
	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sd_flags_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sd_flags_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations sd_flags_fops = अणु
	.खोलो		= sd_flags_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम रेजिस्टर_sd(काष्ठा sched_करोमुख्य *sd, काष्ठा dentry *parent)
अणु
#घोषणा SDM(type, mode, member)	\
	debugfs_create_##type(#member, mode, parent, &sd->member)

	SDM(uदीर्घ, 0644, min_पूर्णांकerval);
	SDM(uदीर्घ, 0644, max_पूर्णांकerval);
	SDM(u64,   0644, max_newidle_lb_cost);
	SDM(u32,   0644, busy_factor);
	SDM(u32,   0644, imbalance_pct);
	SDM(u32,   0644, cache_nice_tries);
	SDM(str,   0444, name);

#अघोषित SDM

	debugfs_create_file("flags", 0444, parent, &sd->flags, &sd_flags_fops);
पूर्ण

व्योम update_sched_करोमुख्य_debugfs(व्योम)
अणु
	पूर्णांक cpu, i;

	अगर (!cpumask_available(sd_sysctl_cpus)) अणु
		अगर (!alloc_cpumask_var(&sd_sysctl_cpus, GFP_KERNEL))
			वापस;
		cpumask_copy(sd_sysctl_cpus, cpu_possible_mask);
	पूर्ण

	अगर (!sd_dentry)
		sd_dentry = debugfs_create_dir("domains", debugfs_sched);

	क्रम_each_cpu(cpu, sd_sysctl_cpus) अणु
		काष्ठा sched_करोमुख्य *sd;
		काष्ठा dentry *d_cpu;
		अक्षर buf[32];

		snम_लिखो(buf, माप(buf), "cpu%d", cpu);
		debugfs_हटाओ(debugfs_lookup(buf, sd_dentry));
		d_cpu = debugfs_create_dir(buf, sd_dentry);

		i = 0;
		क्रम_each_करोमुख्य(cpu, sd) अणु
			काष्ठा dentry *d_sd;

			snम_लिखो(buf, माप(buf), "domain%d", i);
			d_sd = debugfs_create_dir(buf, d_cpu);

			रेजिस्टर_sd(sd, d_sd);
			i++;
		पूर्ण

		__cpumask_clear_cpu(cpu, sd_sysctl_cpus);
	पूर्ण
पूर्ण

व्योम dirty_sched_करोमुख्य_sysctl(पूर्णांक cpu)
अणु
	अगर (cpumask_available(sd_sysctl_cpus))
		__cpumask_set_cpu(cpu, sd_sysctl_cpus);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल व्योम prपूर्णांक_cfs_group_stats(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा task_group *tg)
अणु
	काष्ठा sched_entity *se = tg->se[cpu];

#घोषणा P(F)		SEQ_म_लिखो(m, "  .%-30s: %lld\n",	#F, (दीर्घ दीर्घ)F)
#घोषणा P_SCHEDSTAT(F)	SEQ_म_लिखो(m, "  .%-30s: %lld\n",	#F, (दीर्घ दीर्घ)schedstat_val(F))
#घोषणा PN(F)		SEQ_म_लिखो(m, "  .%-30s: %lld.%06ld\n", #F, SPLIT_NS((दीर्घ दीर्घ)F))
#घोषणा PN_SCHEDSTAT(F)	SEQ_म_लिखो(m, "  .%-30s: %lld.%06ld\n", #F, SPLIT_NS((दीर्घ दीर्घ)schedstat_val(F)))

	अगर (!se)
		वापस;

	PN(se->exec_start);
	PN(se->vrunसमय);
	PN(se->sum_exec_runसमय);

	अगर (schedstat_enabled()) अणु
		PN_SCHEDSTAT(se->statistics.रुको_start);
		PN_SCHEDSTAT(se->statistics.sleep_start);
		PN_SCHEDSTAT(se->statistics.block_start);
		PN_SCHEDSTAT(se->statistics.sleep_max);
		PN_SCHEDSTAT(se->statistics.block_max);
		PN_SCHEDSTAT(se->statistics.exec_max);
		PN_SCHEDSTAT(se->statistics.slice_max);
		PN_SCHEDSTAT(se->statistics.रुको_max);
		PN_SCHEDSTAT(se->statistics.रुको_sum);
		P_SCHEDSTAT(se->statistics.रुको_count);
	पूर्ण

	P(se->load.weight);
#अगर_घोषित CONFIG_SMP
	P(se->avg.load_avg);
	P(se->avg.util_avg);
	P(se->avg.runnable_avg);
#पूर्ण_अगर

#अघोषित PN_SCHEDSTAT
#अघोषित PN
#अघोषित P_SCHEDSTAT
#अघोषित P
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_SCHED
अटल DEFINE_SPINLOCK(sched_debug_lock);
अटल अक्षर group_path[PATH_MAX];

अटल व्योम task_group_path(काष्ठा task_group *tg, अक्षर *path, पूर्णांक plen)
अणु
	अगर (स्वतःgroup_path(tg, path, plen))
		वापस;

	cgroup_path(tg->css.cgroup, path, plen);
पूर्ण

/*
 * Only 1 SEQ_म_लिखो_task_group_path() caller can use the full length
 * group_path[] क्रम cgroup path. Other simultaneous callers will have
 * to use a लघुer stack buffer. A "..." suffix is appended at the end
 * of the stack buffer so that it will show up in हाल the output length
 * matches the given buffer size to indicate possible path name truncation.
 */
#घोषणा SEQ_म_लिखो_task_group_path(m, tg, fmt...)			\
अणु									\
	अगर (spin_trylock(&sched_debug_lock)) अणु				\
		task_group_path(tg, group_path, माप(group_path));	\
		SEQ_म_लिखो(m, fmt, group_path);				\
		spin_unlock(&sched_debug_lock);				\
	पूर्ण अन्यथा अणु							\
		अक्षर buf[128];						\
		अक्षर *bufend = buf + माप(buf) - 3;			\
		task_group_path(tg, buf, bufend - buf);			\
		म_नकल(bufend - 1, "...");				\
		SEQ_म_लिखो(m, fmt, buf);				\
	पूर्ण								\
पूर्ण
#पूर्ण_अगर

अटल व्योम
prपूर्णांक_task(काष्ठा seq_file *m, काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	अगर (task_current(rq, p))
		SEQ_म_लिखो(m, ">R");
	अन्यथा
		SEQ_म_लिखो(m, " %c", task_state_to_अक्षर(p));

	SEQ_म_लिखो(m, " %15s %5d %9Ld.%06ld %9Ld %5d ",
		p->comm, task_pid_nr(p),
		SPLIT_NS(p->se.vrunसमय),
		(दीर्घ दीर्घ)(p->nvcsw + p->nivcsw),
		p->prio);

	SEQ_म_लिखो(m, "%9Ld.%06ld %9Ld.%06ld %9Ld.%06ld",
		SPLIT_NS(schedstat_val_or_zero(p->se.statistics.रुको_sum)),
		SPLIT_NS(p->se.sum_exec_runसमय),
		SPLIT_NS(schedstat_val_or_zero(p->se.statistics.sum_sleep_runसमय)));

#अगर_घोषित CONFIG_NUMA_BALANCING
	SEQ_म_लिखो(m, " %d %d", task_node(p), task_numa_group_id(p));
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_SCHED
	SEQ_म_लिखो_task_group_path(m, task_group(p), " %s")
#पूर्ण_अगर

	SEQ_म_लिखो(m, "\n");
पूर्ण

अटल व्योम prपूर्णांक_rq(काष्ठा seq_file *m, काष्ठा rq *rq, पूर्णांक rq_cpu)
अणु
	काष्ठा task_काष्ठा *g, *p;

	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, "runnable tasks:\n");
	SEQ_म_लिखो(m, " S            task   PID         tree-key  switches  prio"
		   "     wait-time             sum-exec        sum-sleep\n");
	SEQ_म_लिखो(m, "-------------------------------------------------------"
		   "------------------------------------------------------\n");

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (task_cpu(p) != rq_cpu)
			जारी;

		prपूर्णांक_task(m, rq, p);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम prपूर्णांक_cfs_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा cfs_rq *cfs_rq)
अणु
	s64 MIN_vrunसमय = -1, min_vrunसमय, max_vrunसमय = -1,
		spपढ़ो, rq0_min_vrunसमय, spपढ़ो0;
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा sched_entity *last;
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो_task_group_path(m, cfs_rq->tg, "cfs_rq[%d]:%s\n", cpu);
#अन्यथा
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, "cfs_rq[%d]:\n", cpu);
#पूर्ण_अगर
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "exec_clock",
			SPLIT_NS(cfs_rq->exec_घड़ी));

	raw_spin_lock_irqsave(&rq->lock, flags);
	अगर (rb_first_cached(&cfs_rq->tasks_समयline))
		MIN_vrunसमय = (__pick_first_entity(cfs_rq))->vrunसमय;
	last = __pick_last_entity(cfs_rq);
	अगर (last)
		max_vrunसमय = last->vrunसमय;
	min_vrunसमय = cfs_rq->min_vrunसमय;
	rq0_min_vrunसमय = cpu_rq(0)->cfs.min_vrunसमय;
	raw_spin_unlock_irqrestore(&rq->lock, flags);
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "MIN_vruntime",
			SPLIT_NS(MIN_vrunसमय));
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "min_vruntime",
			SPLIT_NS(min_vrunसमय));
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "max_vruntime",
			SPLIT_NS(max_vrunसमय));
	spपढ़ो = max_vrunसमय - MIN_vrunसमय;
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "spread",
			SPLIT_NS(spपढ़ो));
	spपढ़ो0 = min_vrunसमय - rq0_min_vrunसमय;
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", "spread0",
			SPLIT_NS(spपढ़ो0));
	SEQ_म_लिखो(m, "  .%-30s: %d\n", "nr_spread_over",
			cfs_rq->nr_spपढ़ो_over);
	SEQ_म_लिखो(m, "  .%-30s: %d\n", "nr_running", cfs_rq->nr_running);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "load", cfs_rq->load.weight);
#अगर_घोषित CONFIG_SMP
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", "load_avg",
			cfs_rq->avg.load_avg);
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", "runnable_avg",
			cfs_rq->avg.runnable_avg);
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", "util_avg",
			cfs_rq->avg.util_avg);
	SEQ_म_लिखो(m, "  .%-30s: %u\n", "util_est_enqueued",
			cfs_rq->avg.util_est.enqueued);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "removed.load_avg",
			cfs_rq->हटाओd.load_avg);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "removed.util_avg",
			cfs_rq->हटाओd.util_avg);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "removed.runnable_avg",
			cfs_rq->हटाओd.runnable_avg);
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", "tg_load_avg_contrib",
			cfs_rq->tg_load_avg_contrib);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "tg_load_avg",
			atomic_दीर्घ_पढ़ो(&cfs_rq->tg->load_avg));
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	SEQ_म_लिखो(m, "  .%-30s: %d\n", "throttled",
			cfs_rq->throttled);
	SEQ_म_लिखो(m, "  .%-30s: %d\n", "throttle_count",
			cfs_rq->throttle_count);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	prपूर्णांक_cfs_group_stats(m, cpu, cfs_rq->tg);
#पूर्ण_अगर
पूर्ण

व्योम prपूर्णांक_rt_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा rt_rq *rt_rq)
अणु
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो_task_group_path(m, rt_rq->tg, "rt_rq[%d]:%s\n", cpu);
#अन्यथा
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, "rt_rq[%d]:\n", cpu);
#पूर्ण_अगर

#घोषणा P(x) \
	SEQ_म_लिखो(m, "  .%-30s: %Ld\n", #x, (दीर्घ दीर्घ)(rt_rq->x))
#घोषणा PU(x) \
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", #x, (अचिन्हित दीर्घ)(rt_rq->x))
#घोषणा PN(x) \
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", #x, SPLIT_NS(rt_rq->x))

	PU(rt_nr_running);
#अगर_घोषित CONFIG_SMP
	PU(rt_nr_migratory);
#पूर्ण_अगर
	P(rt_throttled);
	PN(rt_समय);
	PN(rt_runसमय);

#अघोषित PN
#अघोषित PU
#अघोषित P
पूर्ण

व्योम prपूर्णांक_dl_rq(काष्ठा seq_file *m, पूर्णांक cpu, काष्ठा dl_rq *dl_rq)
अणु
	काष्ठा dl_bw *dl_bw;

	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, "dl_rq[%d]:\n", cpu);

#घोषणा PU(x) \
	SEQ_म_लिखो(m, "  .%-30s: %lu\n", #x, (अचिन्हित दीर्घ)(dl_rq->x))

	PU(dl_nr_running);
#अगर_घोषित CONFIG_SMP
	PU(dl_nr_migratory);
	dl_bw = &cpu_rq(cpu)->rd->dl_bw;
#अन्यथा
	dl_bw = &dl_rq->dl_bw;
#पूर्ण_अगर
	SEQ_म_लिखो(m, "  .%-30s: %lld\n", "dl_bw->bw", dl_bw->bw);
	SEQ_म_लिखो(m, "  .%-30s: %lld\n", "dl_bw->total_bw", dl_bw->total_bw);

#अघोषित PU
पूर्ण

अटल व्योम prपूर्णांक_cpu(काष्ठा seq_file *m, पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

#अगर_घोषित CONFIG_X86
	अणु
		अचिन्हित पूर्णांक freq = cpu_khz ? : 1;

		SEQ_म_लिखो(m, "cpu#%d, %u.%03u MHz\n",
			   cpu, freq / 1000, (freq % 1000));
	पूर्ण
#अन्यथा
	SEQ_म_लिखो(m, "cpu#%d\n", cpu);
#पूर्ण_अगर

#घोषणा P(x)								\
करो अणु									\
	अगर (माप(rq->x) == 4)						\
		SEQ_म_लिखो(m, "  .%-30s: %ld\n", #x, (दीर्घ)(rq->x));	\
	अन्यथा								\
		SEQ_म_लिखो(m, "  .%-30s: %Ld\n", #x, (दीर्घ दीर्घ)(rq->x));\
पूर्ण जबतक (0)

#घोषणा PN(x) \
	SEQ_म_लिखो(m, "  .%-30s: %Ld.%06ld\n", #x, SPLIT_NS(rq->x))

	P(nr_running);
	P(nr_चयनes);
	P(nr_unपूर्णांकerruptible);
	PN(next_balance);
	SEQ_म_लिखो(m, "  .%-30s: %ld\n", "curr->pid", (दीर्घ)(task_pid_nr(rq->curr)));
	PN(घड़ी);
	PN(घड़ी_प्रकारask);
#अघोषित P
#अघोषित PN

#अगर_घोषित CONFIG_SMP
#घोषणा P64(n) SEQ_म_लिखो(m, "  .%-30s: %Ld\n", #n, rq->n);
	P64(avg_idle);
	P64(max_idle_balance_cost);
#अघोषित P64
#पूर्ण_अगर

#घोषणा P(n) SEQ_म_लिखो(m, "  .%-30s: %d\n", #n, schedstat_val(rq->n));
	अगर (schedstat_enabled()) अणु
		P(yld_count);
		P(sched_count);
		P(sched_goidle);
		P(ttwu_count);
		P(ttwu_local);
	पूर्ण
#अघोषित P

	prपूर्णांक_cfs_stats(m, cpu);
	prपूर्णांक_rt_stats(m, cpu);
	prपूर्णांक_dl_stats(m, cpu);

	prपूर्णांक_rq(m, rq, cpu);
	SEQ_म_लिखो(m, "\n");
पूर्ण

अटल स्थिर अक्षर *sched_tunable_scaling_names[] = अणु
	"none",
	"logarithmic",
	"linear"
पूर्ण;

अटल व्योम sched_debug_header(काष्ठा seq_file *m)
अणु
	u64 kसमय, sched_clk, cpu_clk;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	kसमय = kसमय_प्रकारo_ns(kसमय_get());
	sched_clk = sched_घड़ी();
	cpu_clk = local_घड़ी();
	local_irq_restore(flags);

	SEQ_म_लिखो(m, "Sched Debug Version: v0.11, %s %.*s\n",
		init_utsname()->release,
		(पूर्णांक)म_खोज(init_utsname()->version, " "),
		init_utsname()->version);

#घोषणा P(x) \
	SEQ_म_लिखो(m, "%-40s: %Ld\n", #x, (दीर्घ दीर्घ)(x))
#घोषणा PN(x) \
	SEQ_म_लिखो(m, "%-40s: %Ld.%06ld\n", #x, SPLIT_NS(x))
	PN(kसमय);
	PN(sched_clk);
	PN(cpu_clk);
	P(jअगरfies);
#अगर_घोषित CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
	P(sched_घड़ी_stable());
#पूर्ण_अगर
#अघोषित PN
#अघोषित P

	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, "sysctl_sched\n");

#घोषणा P(x) \
	SEQ_म_लिखो(m, "  .%-40s: %Ld\n", #x, (दीर्घ दीर्घ)(x))
#घोषणा PN(x) \
	SEQ_म_लिखो(m, "  .%-40s: %Ld.%06ld\n", #x, SPLIT_NS(x))
	PN(sysctl_sched_latency);
	PN(sysctl_sched_min_granularity);
	PN(sysctl_sched_wakeup_granularity);
	P(sysctl_sched_child_runs_first);
	P(sysctl_sched_features);
#अघोषित PN
#अघोषित P

	SEQ_म_लिखो(m, "  .%-40s: %d (%s)\n",
		"sysctl_sched_tunable_scaling",
		sysctl_sched_tunable_scaling,
		sched_tunable_scaling_names[sysctl_sched_tunable_scaling]);
	SEQ_म_लिखो(m, "\n");
पूर्ण

अटल पूर्णांक sched_debug_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक cpu = (अचिन्हित दीर्घ)(v - 2);

	अगर (cpu != -1)
		prपूर्णांक_cpu(m, cpu);
	अन्यथा
		sched_debug_header(m);

	वापस 0;
पूर्ण

व्योम sysrq_sched_debug_show(व्योम)
अणु
	पूर्णांक cpu;

	sched_debug_header(शून्य);
	क्रम_each_online_cpu(cpu) अणु
		/*
		 * Need to reset softlockup watchकरोgs on all CPUs, because
		 * another CPU might be blocked रुकोing क्रम us to process
		 * an IPI or stop_machine.
		 */
		touch_nmi_watchकरोg();
		touch_all_softlockup_watchकरोgs();
		prपूर्णांक_cpu(शून्य, cpu);
	पूर्ण
पूर्ण

/*
 * This iterator needs some explanation.
 * It वापसs 1 क्रम the header position.
 * This means 2 is CPU 0.
 * In a hotplugged प्रणाली some CPUs, including CPU 0, may be missing so we have
 * to use cpumask_* to iterate over the CPUs.
 */
अटल व्योम *sched_debug_start(काष्ठा seq_file *file, loff_t *offset)
अणु
	अचिन्हित दीर्घ n = *offset;

	अगर (n == 0)
		वापस (व्योम *) 1;

	n--;

	अगर (n > 0)
		n = cpumask_next(n - 1, cpu_online_mask);
	अन्यथा
		n = cpumask_first(cpu_online_mask);

	*offset = n + 1;

	अगर (n < nr_cpu_ids)
		वापस (व्योम *)(अचिन्हित दीर्घ)(n + 2);

	वापस शून्य;
पूर्ण

अटल व्योम *sched_debug_next(काष्ठा seq_file *file, व्योम *data, loff_t *offset)
अणु
	(*offset)++;
	वापस sched_debug_start(file, offset);
पूर्ण

अटल व्योम sched_debug_stop(काष्ठा seq_file *file, व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations sched_debug_sops = अणु
	.start		= sched_debug_start,
	.next		= sched_debug_next,
	.stop		= sched_debug_stop,
	.show		= sched_debug_show,
पूर्ण;

#घोषणा __PS(S, F) SEQ_म_लिखो(m, "%-45s:%21Ld\n", S, (दीर्घ दीर्घ)(F))
#घोषणा __P(F) __PS(#F, F)
#घोषणा   P(F) __PS(#F, p->F)
#घोषणा   PM(F, M) __PS(#F, p->F & (M))
#घोषणा __PSN(S, F) SEQ_म_लिखो(m, "%-45s:%14Ld.%06ld\n", S, SPLIT_NS((दीर्घ दीर्घ)(F)))
#घोषणा __PN(F) __PSN(#F, F)
#घोषणा   PN(F) __PSN(#F, p->F)


#अगर_घोषित CONFIG_NUMA_BALANCING
व्योम prपूर्णांक_numa_stats(काष्ठा seq_file *m, पूर्णांक node, अचिन्हित दीर्घ tsf,
		अचिन्हित दीर्घ tpf, अचिन्हित दीर्घ gsf, अचिन्हित दीर्घ gpf)
अणु
	SEQ_म_लिखो(m, "numa_faults node=%d ", node);
	SEQ_म_लिखो(m, "task_private=%lu task_shared=%lu ", tpf, tsf);
	SEQ_म_लिखो(m, "group_private=%lu group_shared=%lu\n", gpf, gsf);
पूर्ण
#पूर्ण_अगर


अटल व्योम sched_show_numa(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m)
अणु
#अगर_घोषित CONFIG_NUMA_BALANCING
	काष्ठा mempolicy *pol;

	अगर (p->mm)
		P(mm->numa_scan_seq);

	task_lock(p);
	pol = p->mempolicy;
	अगर (pol && !(pol->flags & MPOL_F_MORON))
		pol = शून्य;
	mpol_get(pol);
	task_unlock(p);

	P(numa_pages_migrated);
	P(numa_preferred_nid);
	P(total_numa_faults);
	SEQ_म_लिखो(m, "current_node=%d, numa_group_id=%d\n",
			task_node(p), task_numa_group_id(p));
	show_numa_stats(p, m);
	mpol_put(pol);
#पूर्ण_अगर
पूर्ण

व्योम proc_sched_show_task(काष्ठा task_काष्ठा *p, काष्ठा pid_namespace *ns,
						  काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ nr_चयनes;

	SEQ_म_लिखो(m, "%s (%d, #threads: %d)\n", p->comm, task_pid_nr_ns(p, ns),
						get_nr_thपढ़ोs(p));
	SEQ_म_लिखो(m,
		"---------------------------------------------------------"
		"----------\n");

#घोषणा P_SCHEDSTAT(F)  __PS(#F, schedstat_val(p->F))
#घोषणा PN_SCHEDSTAT(F) __PSN(#F, schedstat_val(p->F))

	PN(se.exec_start);
	PN(se.vrunसमय);
	PN(se.sum_exec_runसमय);

	nr_चयनes = p->nvcsw + p->nivcsw;

	P(se.nr_migrations);

	अगर (schedstat_enabled()) अणु
		u64 avg_atom, avg_per_cpu;

		PN_SCHEDSTAT(se.statistics.sum_sleep_runसमय);
		PN_SCHEDSTAT(se.statistics.रुको_start);
		PN_SCHEDSTAT(se.statistics.sleep_start);
		PN_SCHEDSTAT(se.statistics.block_start);
		PN_SCHEDSTAT(se.statistics.sleep_max);
		PN_SCHEDSTAT(se.statistics.block_max);
		PN_SCHEDSTAT(se.statistics.exec_max);
		PN_SCHEDSTAT(se.statistics.slice_max);
		PN_SCHEDSTAT(se.statistics.रुको_max);
		PN_SCHEDSTAT(se.statistics.रुको_sum);
		P_SCHEDSTAT(se.statistics.रुको_count);
		PN_SCHEDSTAT(se.statistics.ioरुको_sum);
		P_SCHEDSTAT(se.statistics.ioरुको_count);
		P_SCHEDSTAT(se.statistics.nr_migrations_cold);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_affine);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_running);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_hot);
		P_SCHEDSTAT(se.statistics.nr_क्रमced_migrations);
		P_SCHEDSTAT(se.statistics.nr_wakeups);
		P_SCHEDSTAT(se.statistics.nr_wakeups_sync);
		P_SCHEDSTAT(se.statistics.nr_wakeups_migrate);
		P_SCHEDSTAT(se.statistics.nr_wakeups_local);
		P_SCHEDSTAT(se.statistics.nr_wakeups_remote);
		P_SCHEDSTAT(se.statistics.nr_wakeups_affine);
		P_SCHEDSTAT(se.statistics.nr_wakeups_affine_attempts);
		P_SCHEDSTAT(se.statistics.nr_wakeups_passive);
		P_SCHEDSTAT(se.statistics.nr_wakeups_idle);

		avg_atom = p->se.sum_exec_runसमय;
		अगर (nr_चयनes)
			avg_atom = भाग64_ul(avg_atom, nr_चयनes);
		अन्यथा
			avg_atom = -1LL;

		avg_per_cpu = p->se.sum_exec_runसमय;
		अगर (p->se.nr_migrations) अणु
			avg_per_cpu = भाग64_u64(avg_per_cpu,
						p->se.nr_migrations);
		पूर्ण अन्यथा अणु
			avg_per_cpu = -1LL;
		पूर्ण

		__PN(avg_atom);
		__PN(avg_per_cpu);
	पूर्ण

	__P(nr_चयनes);
	__PS("nr_voluntary_switches", p->nvcsw);
	__PS("nr_involuntary_switches", p->nivcsw);

	P(se.load.weight);
#अगर_घोषित CONFIG_SMP
	P(se.avg.load_sum);
	P(se.avg.runnable_sum);
	P(se.avg.util_sum);
	P(se.avg.load_avg);
	P(se.avg.runnable_avg);
	P(se.avg.util_avg);
	P(se.avg.last_update_समय);
	P(se.avg.util_est.ewma);
	PM(se.avg.util_est.enqueued, ~UTIL_AVG_UNCHANGED);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UCLAMP_TASK
	__PS("uclamp.min", p->uclamp_req[UCLAMP_MIN].value);
	__PS("uclamp.max", p->uclamp_req[UCLAMP_MAX].value);
	__PS("effective uclamp.min", uclamp_eff_value(p, UCLAMP_MIN));
	__PS("effective uclamp.max", uclamp_eff_value(p, UCLAMP_MAX));
#पूर्ण_अगर
	P(policy);
	P(prio);
	अगर (task_has_dl_policy(p)) अणु
		P(dl.runसमय);
		P(dl.deadline);
	पूर्ण
#अघोषित PN_SCHEDSTAT
#अघोषित P_SCHEDSTAT

	अणु
		अचिन्हित पूर्णांक this_cpu = raw_smp_processor_id();
		u64 t0, t1;

		t0 = cpu_घड़ी(this_cpu);
		t1 = cpu_घड़ी(this_cpu);
		__PS("clock-delta", t1-t0);
	पूर्ण

	sched_show_numa(p, m);
पूर्ण

व्योम proc_sched_set_task(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_SCHEDSTATS
	स_रखो(&p->se.statistics, 0, माप(p->se.statistics));
#पूर्ण_अगर
पूर्ण

व्योम resched_latency_warn(पूर्णांक cpu, u64 latency)
अणु
	अटल DEFINE_RATELIMIT_STATE(latency_check_ratelimit, 60 * 60 * HZ, 1);

	WARN(__ratelimit(&latency_check_ratelimit),
	     "sched: CPU %d need_resched set for > %llu ns (%d ticks) "
	     "without schedule\n",
	     cpu, latency, cpu_rq(cpu)->ticks_without_resched);
पूर्ण
