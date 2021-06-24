<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * /proc/schedstat implementation
 */
#समावेश "sched.h"

/*
 * Current schedstat API version.
 *
 * Bump this up when changing the output क्रमmat or the meaning of an existing
 * क्रमmat, so that tools can adapt (or पात)
 */
#घोषणा SCHEDSTAT_VERSION 15

अटल पूर्णांक show_schedstat(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक cpu;

	अगर (v == (व्योम *)1) अणु
		seq_म_लिखो(seq, "version %d\n", SCHEDSTAT_VERSION);
		seq_म_लिखो(seq, "timestamp %lu\n", jअगरfies);
	पूर्ण अन्यथा अणु
		काष्ठा rq *rq;
#अगर_घोषित CONFIG_SMP
		काष्ठा sched_करोमुख्य *sd;
		पूर्णांक dcount = 0;
#पूर्ण_अगर
		cpu = (अचिन्हित दीर्घ)(v - 2);
		rq = cpu_rq(cpu);

		/* runqueue-specअगरic stats */
		seq_म_लिखो(seq,
		    "cpu%d %u 0 %u %u %u %u %llu %llu %lu",
		    cpu, rq->yld_count,
		    rq->sched_count, rq->sched_goidle,
		    rq->ttwu_count, rq->ttwu_local,
		    rq->rq_cpu_समय,
		    rq->rq_sched_info.run_delay, rq->rq_sched_info.pcount);

		seq_म_लिखो(seq, "\n");

#अगर_घोषित CONFIG_SMP
		/* करोमुख्य-specअगरic stats */
		rcu_पढ़ो_lock();
		क्रम_each_करोमुख्य(cpu, sd) अणु
			क्रमागत cpu_idle_type itype;

			seq_म_लिखो(seq, "domain%d %*pb", dcount++,
				   cpumask_pr_args(sched_करोमुख्य_span(sd)));
			क्रम (itype = CPU_IDLE; itype < CPU_MAX_IDLE_TYPES;
					itype++) अणु
				seq_म_लिखो(seq, " %u %u %u %u %u %u %u %u",
				    sd->lb_count[itype],
				    sd->lb_balanced[itype],
				    sd->lb_failed[itype],
				    sd->lb_imbalance[itype],
				    sd->lb_gained[itype],
				    sd->lb_hot_gained[itype],
				    sd->lb_nobusyq[itype],
				    sd->lb_nobusyg[itype]);
			पूर्ण
			seq_म_लिखो(seq,
				   " %u %u %u %u %u %u %u %u %u %u %u %u\n",
			    sd->alb_count, sd->alb_failed, sd->alb_pushed,
			    sd->sbe_count, sd->sbe_balanced, sd->sbe_pushed,
			    sd->sbf_count, sd->sbf_balanced, sd->sbf_pushed,
			    sd->ttwu_wake_remote, sd->ttwu_move_affine,
			    sd->ttwu_move_balance);
		पूर्ण
		rcu_पढ़ो_unlock();
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This iterator needs some explanation.
 * It वापसs 1 क्रम the header position.
 * This means 2 is cpu 0.
 * In a hotplugged प्रणाली some CPUs, including cpu 0, may be missing so we have
 * to use cpumask_* to iterate over the CPUs.
 */
अटल व्योम *schedstat_start(काष्ठा seq_file *file, loff_t *offset)
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

अटल व्योम *schedstat_next(काष्ठा seq_file *file, व्योम *data, loff_t *offset)
अणु
	(*offset)++;

	वापस schedstat_start(file, offset);
पूर्ण

अटल व्योम schedstat_stop(काष्ठा seq_file *file, व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations schedstat_sops = अणु
	.start = schedstat_start,
	.next  = schedstat_next,
	.stop  = schedstat_stop,
	.show  = show_schedstat,
पूर्ण;

अटल पूर्णांक __init proc_schedstat_init(व्योम)
अणु
	proc_create_seq("schedstat", 0, शून्य, &schedstat_sops);
	वापस 0;
पूर्ण
subsys_initcall(proc_schedstat_init);
