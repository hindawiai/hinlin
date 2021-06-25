<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic helpers क्रम smp ipi calls
 *
 * (C) Jens Axboe <jens.axboe@oracle.com> 2008
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/irq_work.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gfp.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/idle.h>
#समावेश <linux/hypervisor.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/jump_label.h>

#समावेश "smpboot.h"
#समावेश "sched/smp.h"

#घोषणा CSD_TYPE(_csd)	((_csd)->node.u_flags & CSD_FLAG_TYPE_MASK)

#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG
जोड़ cfd_seq_cnt अणु
	u64		val;
	काष्ठा अणु
		u64	src:16;
		u64	dst:16;
#घोषणा CFD_SEQ_NOCPU	0xffff
		u64	type:4;
#घोषणा CFD_SEQ_QUEUE	0
#घोषणा CFD_SEQ_IPI	1
#घोषणा CFD_SEQ_NOIPI	2
#घोषणा CFD_SEQ_PING	3
#घोषणा CFD_SEQ_PINGED	4
#घोषणा CFD_SEQ_HANDLE	5
#घोषणा CFD_SEQ_DEQUEUE	6
#घोषणा CFD_SEQ_IDLE	7
#घोषणा CFD_SEQ_GOTIPI	8
#घोषणा CFD_SEQ_HDLEND	9
		u64	cnt:28;
	पूर्ण		u;
पूर्ण;

अटल अक्षर *seq_type[] = अणु
	[CFD_SEQ_QUEUE]		= "queue",
	[CFD_SEQ_IPI]		= "ipi",
	[CFD_SEQ_NOIPI]		= "noipi",
	[CFD_SEQ_PING]		= "ping",
	[CFD_SEQ_PINGED]	= "pinged",
	[CFD_SEQ_HANDLE]	= "handle",
	[CFD_SEQ_DEQUEUE]	= "dequeue (src CPU 0 == empty)",
	[CFD_SEQ_IDLE]		= "idle",
	[CFD_SEQ_GOTIPI]	= "gotipi",
	[CFD_SEQ_HDLEND]	= "hdlend (src CPU 0 == early)",
पूर्ण;

काष्ठा cfd_seq_local अणु
	u64	ping;
	u64	pinged;
	u64	handle;
	u64	dequeue;
	u64	idle;
	u64	gotipi;
	u64	hdlend;
पूर्ण;
#पूर्ण_अगर

काष्ठा cfd_percpu अणु
	call_single_data_t	csd;
#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG
	u64	seq_queue;
	u64	seq_ipi;
	u64	seq_noipi;
#पूर्ण_अगर
पूर्ण;

काष्ठा call_function_data अणु
	काष्ठा cfd_percpu	__percpu *pcpu;
	cpumask_var_t		cpumask;
	cpumask_var_t		cpumask_ipi;
पूर्ण;

अटल DEFINE_PER_CPU_ALIGNED(काष्ठा call_function_data, cfd_data);

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा llist_head, call_single_queue);

अटल व्योम flush_smp_call_function_queue(bool warn_cpu_offline);

पूर्णांक smpcfd_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा call_function_data *cfd = &per_cpu(cfd_data, cpu);

	अगर (!zalloc_cpumask_var_node(&cfd->cpumask, GFP_KERNEL,
				     cpu_to_node(cpu)))
		वापस -ENOMEM;
	अगर (!zalloc_cpumask_var_node(&cfd->cpumask_ipi, GFP_KERNEL,
				     cpu_to_node(cpu))) अणु
		मुक्त_cpumask_var(cfd->cpumask);
		वापस -ENOMEM;
	पूर्ण
	cfd->pcpu = alloc_percpu(काष्ठा cfd_percpu);
	अगर (!cfd->pcpu) अणु
		मुक्त_cpumask_var(cfd->cpumask);
		मुक्त_cpumask_var(cfd->cpumask_ipi);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smpcfd_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा call_function_data *cfd = &per_cpu(cfd_data, cpu);

	मुक्त_cpumask_var(cfd->cpumask);
	मुक्त_cpumask_var(cfd->cpumask_ipi);
	मुक्त_percpu(cfd->pcpu);
	वापस 0;
पूर्ण

पूर्णांक smpcfd_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * The IPIs क्रम the smp-call-function callbacks queued by other
	 * CPUs might arrive late, either due to hardware latencies or
	 * because this CPU disabled पूर्णांकerrupts (inside stop-machine)
	 * beक्रमe the IPIs were sent. So flush out any pending callbacks
	 * explicitly (without रुकोing क्रम the IPIs to arrive), to
	 * ensure that the outgoing CPU करोesn't go offline with work
	 * still pending.
	 */
	flush_smp_call_function_queue(false);
	irq_work_run();
	वापस 0;
पूर्ण

व्योम __init call_function_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		init_llist_head(&per_cpu(call_single_queue, i));

	smpcfd_prepare_cpu(smp_processor_id());
पूर्ण

#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG

अटल DEFINE_STATIC_KEY_FALSE(csdlock_debug_enabled);
अटल DEFINE_STATIC_KEY_FALSE(csdlock_debug_extended);

अटल पूर्णांक __init csdlock_debug(अक्षर *str)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (str && !म_भेद(str, "ext")) अणु
		val = 1;
		अटल_branch_enable(&csdlock_debug_extended);
	पूर्ण अन्यथा
		get_option(&str, &val);

	अगर (val)
		अटल_branch_enable(&csdlock_debug_enabled);

	वापस 0;
पूर्ण
early_param("csdlock_debug", csdlock_debug);

अटल DEFINE_PER_CPU(call_single_data_t *, cur_csd);
अटल DEFINE_PER_CPU(smp_call_func_t, cur_csd_func);
अटल DEFINE_PER_CPU(व्योम *, cur_csd_info);
अटल DEFINE_PER_CPU(काष्ठा cfd_seq_local, cfd_seq_local);

#घोषणा CSD_LOCK_TIMEOUT (5ULL * NSEC_PER_SEC)
अटल atomic_t csd_bug_count = ATOMIC_INIT(0);
अटल u64 cfd_seq;

#घोषणा CFD_SEQ(s, d, t, c)	\
	(जोड़ cfd_seq_cnt)अणु .u.src = s, .u.dst = d, .u.type = t, .u.cnt = c पूर्ण

अटल u64 cfd_seq_inc(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक type)
अणु
	जोड़ cfd_seq_cnt new, old;

	new = CFD_SEQ(src, dst, type, 0);

	करो अणु
		old.val = READ_ONCE(cfd_seq);
		new.u.cnt = old.u.cnt + 1;
	पूर्ण जबतक (cmpxchg(&cfd_seq, old.val, new.val) != old.val);

	वापस old.val;
पूर्ण

#घोषणा cfd_seq_store(var, src, dst, type)				\
	करो अणु								\
		अगर (अटल_branch_unlikely(&csdlock_debug_extended))	\
			var = cfd_seq_inc(src, dst, type);		\
	पूर्ण जबतक (0)

/* Record current CSD work क्रम current CPU, शून्य to erase. */
अटल व्योम __csd_lock_record(काष्ठा __call_single_data *csd)
अणु
	अगर (!csd) अणु
		smp_mb(); /* शून्य cur_csd after unlock. */
		__this_cpu_ग_लिखो(cur_csd, शून्य);
		वापस;
	पूर्ण
	__this_cpu_ग_लिखो(cur_csd_func, csd->func);
	__this_cpu_ग_लिखो(cur_csd_info, csd->info);
	smp_wmb(); /* func and info beक्रमe csd. */
	__this_cpu_ग_लिखो(cur_csd, csd);
	smp_mb(); /* Update cur_csd beक्रमe function call. */
		  /* Or beक्रमe unlock, as the हाल may be. */
पूर्ण

अटल __always_अंतरभूत व्योम csd_lock_record(काष्ठा __call_single_data *csd)
अणु
	अगर (अटल_branch_unlikely(&csdlock_debug_enabled))
		__csd_lock_record(csd);
पूर्ण

अटल पूर्णांक csd_lock_रुको_अ_लोpu(काष्ठा __call_single_data *csd)
अणु
	अचिन्हित पूर्णांक csd_type;

	csd_type = CSD_TYPE(csd);
	अगर (csd_type == CSD_TYPE_ASYNC || csd_type == CSD_TYPE_SYNC)
		वापस csd->node.dst; /* Other CSD_TYPE_ values might not have ->dst. */
	वापस -1;
पूर्ण

अटल व्योम cfd_seq_data_add(u64 val, अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dst,
			     अचिन्हित पूर्णांक type, जोड़ cfd_seq_cnt *data,
			     अचिन्हित पूर्णांक *n_data, अचिन्हित पूर्णांक now)
अणु
	जोड़ cfd_seq_cnt new[2];
	अचिन्हित पूर्णांक i, j, k;

	new[0].val = val;
	new[1] = CFD_SEQ(src, dst, type, new[0].u.cnt + 1);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (new[i].u.cnt <= now)
			new[i].u.cnt |= 0x80000000U;
		क्रम (j = 0; j < *n_data; j++) अणु
			अगर (new[i].u.cnt == data[j].u.cnt) अणु
				/* Direct पढ़ो value trumps generated one. */
				अगर (i == 0)
					data[j].val = new[i].val;
				अवरोध;
			पूर्ण
			अगर (new[i].u.cnt < data[j].u.cnt) अणु
				क्रम (k = *n_data; k > j; k--)
					data[k].val = data[k - 1].val;
				data[j].val = new[i].val;
				(*n_data)++;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (j == *n_data) अणु
			data[j].val = new[i].val;
			(*n_data)++;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *csd_lock_get_type(अचिन्हित पूर्णांक type)
अणु
	वापस (type >= ARRAY_SIZE(seq_type)) ? "?" : seq_type[type];
पूर्ण

अटल व्योम csd_lock_prपूर्णांक_extended(काष्ठा __call_single_data *csd, पूर्णांक cpu)
अणु
	काष्ठा cfd_seq_local *seq = &per_cpu(cfd_seq_local, cpu);
	अचिन्हित पूर्णांक srccpu = csd->node.src;
	काष्ठा call_function_data *cfd = per_cpu_ptr(&cfd_data, srccpu);
	काष्ठा cfd_percpu *pcpu = per_cpu_ptr(cfd->pcpu, cpu);
	अचिन्हित पूर्णांक now;
	जोड़ cfd_seq_cnt data[2 * ARRAY_SIZE(seq_type)];
	अचिन्हित पूर्णांक n_data = 0, i;

	data[0].val = READ_ONCE(cfd_seq);
	now = data[0].u.cnt;

	cfd_seq_data_add(pcpu->seq_queue,			srccpu, cpu,	       CFD_SEQ_QUEUE,  data, &n_data, now);
	cfd_seq_data_add(pcpu->seq_ipi,				srccpu, cpu,	       CFD_SEQ_IPI,    data, &n_data, now);
	cfd_seq_data_add(pcpu->seq_noipi,			srccpu, cpu,	       CFD_SEQ_NOIPI,  data, &n_data, now);

	cfd_seq_data_add(per_cpu(cfd_seq_local.ping, srccpu),	srccpu, CFD_SEQ_NOCPU, CFD_SEQ_PING,   data, &n_data, now);
	cfd_seq_data_add(per_cpu(cfd_seq_local.pinged, srccpu), srccpu, CFD_SEQ_NOCPU, CFD_SEQ_PINGED, data, &n_data, now);

	cfd_seq_data_add(seq->idle,    CFD_SEQ_NOCPU, cpu, CFD_SEQ_IDLE,    data, &n_data, now);
	cfd_seq_data_add(seq->gotipi,  CFD_SEQ_NOCPU, cpu, CFD_SEQ_GOTIPI,  data, &n_data, now);
	cfd_seq_data_add(seq->handle,  CFD_SEQ_NOCPU, cpu, CFD_SEQ_HANDLE,  data, &n_data, now);
	cfd_seq_data_add(seq->dequeue, CFD_SEQ_NOCPU, cpu, CFD_SEQ_DEQUEUE, data, &n_data, now);
	cfd_seq_data_add(seq->hdlend,  CFD_SEQ_NOCPU, cpu, CFD_SEQ_HDLEND,  data, &n_data, now);

	क्रम (i = 0; i < n_data; i++) अणु
		pr_alert("\tcsd: cnt(%07x): %04x->%04x %s\n",
			 data[i].u.cnt & ~0x80000000U, data[i].u.src,
			 data[i].u.dst, csd_lock_get_type(data[i].u.type));
	पूर्ण
	pr_alert("\tcsd: cnt now: %07x\n", now);
पूर्ण

/*
 * Complain अगर too much समय spent रुकोing.  Note that only
 * the CSD_TYPE_SYNC/ASYNC types provide the destination CPU,
 * so रुकोing on other types माला_लो much less inक्रमmation.
 */
अटल bool csd_lock_रुको_tooदीर्घ(काष्ठा __call_single_data *csd, u64 ts0, u64 *ts1, पूर्णांक *bug_id)
अणु
	पूर्णांक cpu = -1;
	पूर्णांक cpux;
	bool firstसमय;
	u64 ts2, ts_delta;
	call_single_data_t *cpu_cur_csd;
	अचिन्हित पूर्णांक flags = READ_ONCE(csd->node.u_flags);

	अगर (!(flags & CSD_FLAG_LOCK)) अणु
		अगर (!unlikely(*bug_id))
			वापस true;
		cpu = csd_lock_रुको_अ_लोpu(csd);
		pr_alert("csd: CSD lock (#%d) got unstuck on CPU#%02d, CPU#%02d released the lock.\n",
			 *bug_id, raw_smp_processor_id(), cpu);
		वापस true;
	पूर्ण

	ts2 = sched_घड़ी();
	ts_delta = ts2 - *ts1;
	अगर (likely(ts_delta <= CSD_LOCK_TIMEOUT))
		वापस false;

	firstसमय = !*bug_id;
	अगर (firstसमय)
		*bug_id = atomic_inc_वापस(&csd_bug_count);
	cpu = csd_lock_रुको_अ_लोpu(csd);
	अगर (WARN_ONCE(cpu < 0 || cpu >= nr_cpu_ids, "%s: cpu = %d\n", __func__, cpu))
		cpux = 0;
	अन्यथा
		cpux = cpu;
	cpu_cur_csd = smp_load_acquire(&per_cpu(cur_csd, cpux)); /* Beक्रमe func and info. */
	pr_alert("csd: %s non-responsive CSD lock (#%d) on CPU#%d, waiting %llu ns for CPU#%02d %pS(%ps).\n",
		 firstसमय ? "Detected" : "Continued", *bug_id, raw_smp_processor_id(), ts2 - ts0,
		 cpu, csd->func, csd->info);
	अगर (cpu_cur_csd && csd != cpu_cur_csd) अणु
		pr_alert("\tcsd: CSD lock (#%d) handling prior %pS(%ps) request.\n",
			 *bug_id, READ_ONCE(per_cpu(cur_csd_func, cpux)),
			 READ_ONCE(per_cpu(cur_csd_info, cpux)));
	पूर्ण अन्यथा अणु
		pr_alert("\tcsd: CSD lock (#%d) %s.\n",
			 *bug_id, !cpu_cur_csd ? "unresponsive" : "handling this request");
	पूर्ण
	अगर (cpu >= 0) अणु
		अगर (अटल_branch_unlikely(&csdlock_debug_extended))
			csd_lock_prपूर्णांक_extended(csd, cpu);
		अगर (!trigger_single_cpu_backtrace(cpu))
			dump_cpu_task(cpu);
		अगर (!cpu_cur_csd) अणु
			pr_alert("csd: Re-sending CSD lock (#%d) IPI from CPU#%02d to CPU#%02d\n", *bug_id, raw_smp_processor_id(), cpu);
			arch_send_call_function_single_ipi(cpu);
		पूर्ण
	पूर्ण
	dump_stack();
	*ts1 = ts2;

	वापस false;
पूर्ण

/*
 * csd_lock/csd_unlock used to serialize access to per-cpu csd resources
 *
 * For non-synchronous ipi calls the csd can still be in use by the
 * previous function call. For multi-cpu calls its even more पूर्णांकeresting
 * as we'll have to ensure no other cpu is observing our csd.
 */
अटल व्योम __csd_lock_रुको(काष्ठा __call_single_data *csd)
अणु
	पूर्णांक bug_id = 0;
	u64 ts0, ts1;

	ts1 = ts0 = sched_घड़ी();
	क्रम (;;) अणु
		अगर (csd_lock_रुको_tooदीर्घ(csd, ts0, &ts1, &bug_id))
			अवरोध;
		cpu_relax();
	पूर्ण
	smp_acquire__after_ctrl_dep();
पूर्ण

अटल __always_अंतरभूत व्योम csd_lock_रुको(काष्ठा __call_single_data *csd)
अणु
	अगर (अटल_branch_unlikely(&csdlock_debug_enabled)) अणु
		__csd_lock_रुको(csd);
		वापस;
	पूर्ण

	smp_cond_load_acquire(&csd->node.u_flags, !(VAL & CSD_FLAG_LOCK));
पूर्ण

अटल व्योम __smp_call_single_queue_debug(पूर्णांक cpu, काष्ठा llist_node *node)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	काष्ठा cfd_seq_local *seq = this_cpu_ptr(&cfd_seq_local);
	काष्ठा call_function_data *cfd = this_cpu_ptr(&cfd_data);
	काष्ठा cfd_percpu *pcpu = per_cpu_ptr(cfd->pcpu, cpu);

	cfd_seq_store(pcpu->seq_queue, this_cpu, cpu, CFD_SEQ_QUEUE);
	अगर (llist_add(node, &per_cpu(call_single_queue, cpu))) अणु
		cfd_seq_store(pcpu->seq_ipi, this_cpu, cpu, CFD_SEQ_IPI);
		cfd_seq_store(seq->ping, this_cpu, cpu, CFD_SEQ_PING);
		send_call_function_single_ipi(cpu);
		cfd_seq_store(seq->pinged, this_cpu, cpu, CFD_SEQ_PINGED);
	पूर्ण अन्यथा अणु
		cfd_seq_store(pcpu->seq_noipi, this_cpu, cpu, CFD_SEQ_NOIPI);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा cfd_seq_store(var, src, dst, type)

अटल व्योम csd_lock_record(काष्ठा __call_single_data *csd)
अणु
पूर्ण

अटल __always_अंतरभूत व्योम csd_lock_रुको(काष्ठा __call_single_data *csd)
अणु
	smp_cond_load_acquire(&csd->node.u_flags, !(VAL & CSD_FLAG_LOCK));
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम csd_lock(काष्ठा __call_single_data *csd)
अणु
	csd_lock_रुको(csd);
	csd->node.u_flags |= CSD_FLAG_LOCK;

	/*
	 * prevent CPU from reordering the above assignment
	 * to ->flags with any subsequent assignments to other
	 * fields of the specअगरied call_single_data_t काष्ठाure:
	 */
	smp_wmb();
पूर्ण

अटल __always_अंतरभूत व्योम csd_unlock(काष्ठा __call_single_data *csd)
अणु
	WARN_ON(!(csd->node.u_flags & CSD_FLAG_LOCK));

	/*
	 * ensure we're all करोne beक्रमe releasing data:
	 */
	smp_store_release(&csd->node.u_flags, 0);
पूर्ण

अटल DEFINE_PER_CPU_SHARED_ALIGNED(call_single_data_t, csd_data);

व्योम __smp_call_single_queue(पूर्णांक cpu, काष्ठा llist_node *node)
अणु
#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG
	अगर (अटल_branch_unlikely(&csdlock_debug_extended)) अणु
		अचिन्हित पूर्णांक type;

		type = CSD_TYPE(container_of(node, call_single_data_t,
					     node.llist));
		अगर (type == CSD_TYPE_SYNC || type == CSD_TYPE_ASYNC) अणु
			__smp_call_single_queue_debug(cpu, node);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * The list addition should be visible beक्रमe sending the IPI
	 * handler locks the list to pull the entry off it because of
	 * normal cache coherency rules implied by spinlocks.
	 *
	 * If IPIs can go out of order to the cache coherency protocol
	 * in an architecture, sufficient synchronisation should be added
	 * to arch code to make it appear to obey cache coherency WRT
	 * locking and barrier primitives. Generic code isn't really
	 * equipped to करो the right thing...
	 */
	अगर (llist_add(node, &per_cpu(call_single_queue, cpu)))
		send_call_function_single_ipi(cpu);
पूर्ण

/*
 * Insert a previously allocated call_single_data_t element
 * क्रम execution on the given CPU. data must alपढ़ोy have
 * ->func, ->info, and ->flags set.
 */
अटल पूर्णांक generic_exec_single(पूर्णांक cpu, काष्ठा __call_single_data *csd)
अणु
	अगर (cpu == smp_processor_id()) अणु
		smp_call_func_t func = csd->func;
		व्योम *info = csd->info;
		अचिन्हित दीर्घ flags;

		/*
		 * We can unlock early even क्रम the synchronous on-stack हाल,
		 * since we're करोing this from the same CPU..
		 */
		csd_lock_record(csd);
		csd_unlock(csd);
		local_irq_save(flags);
		func(info);
		csd_lock_record(शून्य);
		local_irq_restore(flags);
		वापस 0;
	पूर्ण

	अगर ((अचिन्हित)cpu >= nr_cpu_ids || !cpu_online(cpu)) अणु
		csd_unlock(csd);
		वापस -ENXIO;
	पूर्ण

	__smp_call_single_queue(cpu, &csd->node.llist);

	वापस 0;
पूर्ण

/**
 * generic_smp_call_function_single_पूर्णांकerrupt - Execute SMP IPI callbacks
 *
 * Invoked by arch to handle an IPI क्रम call function single.
 * Must be called with पूर्णांकerrupts disabled.
 */
व्योम generic_smp_call_function_single_पूर्णांकerrupt(व्योम)
अणु
	cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->gotipi, CFD_SEQ_NOCPU,
		      smp_processor_id(), CFD_SEQ_GOTIPI);
	flush_smp_call_function_queue(true);
पूर्ण

/**
 * flush_smp_call_function_queue - Flush pending smp-call-function callbacks
 *
 * @warn_cpu_offline: If set to 'true', warn अगर callbacks were queued on an
 *		      offline CPU. Skip this check अगर set to 'false'.
 *
 * Flush any pending smp-call-function callbacks queued on this CPU. This is
 * invoked by the generic IPI handler, as well as by a CPU about to go offline,
 * to ensure that all pending IPI callbacks are run beक्रमe it goes completely
 * offline.
 *
 * Loop through the call_single_queue and run all the queued callbacks.
 * Must be called with पूर्णांकerrupts disabled.
 */
अटल व्योम flush_smp_call_function_queue(bool warn_cpu_offline)
अणु
	call_single_data_t *csd, *csd_next;
	काष्ठा llist_node *entry, *prev;
	काष्ठा llist_head *head;
	अटल bool warned;

	lockdep_निश्चित_irqs_disabled();

	head = this_cpu_ptr(&call_single_queue);
	cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->handle, CFD_SEQ_NOCPU,
		      smp_processor_id(), CFD_SEQ_HANDLE);
	entry = llist_del_all(head);
	cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->dequeue,
		      /* Special meaning of source cpu: 0 == queue empty */
		      entry ? CFD_SEQ_NOCPU : 0,
		      smp_processor_id(), CFD_SEQ_DEQUEUE);
	entry = llist_reverse_order(entry);

	/* There shouldn't be any pending callbacks on an offline CPU. */
	अगर (unlikely(warn_cpu_offline && !cpu_online(smp_processor_id()) &&
		     !warned && !llist_empty(head))) अणु
		warned = true;
		WARN(1, "IPI on offline CPU %d\n", smp_processor_id());

		/*
		 * We करोn't have to use the _safe() variant here
		 * because we are not invoking the IPI handlers yet.
		 */
		llist_क्रम_each_entry(csd, entry, node.llist) अणु
			चयन (CSD_TYPE(csd)) अणु
			हाल CSD_TYPE_ASYNC:
			हाल CSD_TYPE_SYNC:
			हाल CSD_TYPE_IRQ_WORK:
				pr_warn("IPI callback %pS sent to offline CPU\n",
					csd->func);
				अवरोध;

			हाल CSD_TYPE_TTWU:
				pr_warn("IPI task-wakeup sent to offline CPU\n");
				अवरोध;

			शेष:
				pr_warn("IPI callback, unknown type %d, sent to offline CPU\n",
					CSD_TYPE(csd));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * First; run all SYNC callbacks, people are रुकोing क्रम us.
	 */
	prev = शून्य;
	llist_क्रम_each_entry_safe(csd, csd_next, entry, node.llist) अणु
		/* Do we रुको until *after* callback? */
		अगर (CSD_TYPE(csd) == CSD_TYPE_SYNC) अणु
			smp_call_func_t func = csd->func;
			व्योम *info = csd->info;

			अगर (prev) अणु
				prev->next = &csd_next->node.llist;
			पूर्ण अन्यथा अणु
				entry = &csd_next->node.llist;
			पूर्ण

			csd_lock_record(csd);
			func(info);
			csd_unlock(csd);
			csd_lock_record(शून्य);
		पूर्ण अन्यथा अणु
			prev = &csd->node.llist;
		पूर्ण
	पूर्ण

	अगर (!entry) अणु
		cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->hdlend,
			      0, smp_processor_id(),
			      CFD_SEQ_HDLEND);
		वापस;
	पूर्ण

	/*
	 * Second; run all !SYNC callbacks.
	 */
	prev = शून्य;
	llist_क्रम_each_entry_safe(csd, csd_next, entry, node.llist) अणु
		पूर्णांक type = CSD_TYPE(csd);

		अगर (type != CSD_TYPE_TTWU) अणु
			अगर (prev) अणु
				prev->next = &csd_next->node.llist;
			पूर्ण अन्यथा अणु
				entry = &csd_next->node.llist;
			पूर्ण

			अगर (type == CSD_TYPE_ASYNC) अणु
				smp_call_func_t func = csd->func;
				व्योम *info = csd->info;

				csd_lock_record(csd);
				csd_unlock(csd);
				func(info);
				csd_lock_record(शून्य);
			पूर्ण अन्यथा अगर (type == CSD_TYPE_IRQ_WORK) अणु
				irq_work_single(csd);
			पूर्ण

		पूर्ण अन्यथा अणु
			prev = &csd->node.llist;
		पूर्ण
	पूर्ण

	/*
	 * Third; only CSD_TYPE_TTWU is left, issue those.
	 */
	अगर (entry)
		sched_ttwu_pending(entry);

	cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->hdlend, CFD_SEQ_NOCPU,
		      smp_processor_id(), CFD_SEQ_HDLEND);
पूर्ण

व्योम flush_smp_call_function_from_idle(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (llist_empty(this_cpu_ptr(&call_single_queue)))
		वापस;

	cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->idle, CFD_SEQ_NOCPU,
		      smp_processor_id(), CFD_SEQ_IDLE);
	local_irq_save(flags);
	flush_smp_call_function_queue(true);
	अगर (local_softirq_pending())
		करो_softirq();

	local_irq_restore(flags);
पूर्ण

/*
 * smp_call_function_single - Run a function on a specअगरic CPU
 * @func: The function to run. This must be fast and non-blocking.
 * @info: An arbitrary poपूर्णांकer to pass to the function.
 * @रुको: If true, रुको until function has completed on other CPUs.
 *
 * Returns 0 on success, अन्यथा a negative status code.
 */
पूर्णांक smp_call_function_single(पूर्णांक cpu, smp_call_func_t func, व्योम *info,
			     पूर्णांक रुको)
अणु
	call_single_data_t *csd;
	call_single_data_t csd_stack = अणु
		.node = अणु .u_flags = CSD_FLAG_LOCK | CSD_TYPE_SYNC, पूर्ण,
	पूर्ण;
	पूर्णांक this_cpu;
	पूर्णांक err;

	/*
	 * prevent preemption and reschedule on another processor,
	 * as well as CPU removal
	 */
	this_cpu = get_cpu();

	/*
	 * Can deadlock when called with पूर्णांकerrupts disabled.
	 * We allow cpu's that are not yet online though, as no one अन्यथा can
	 * send smp call function पूर्णांकerrupt to this cpu and as such deadlocks
	 * can't happen.
	 */
	WARN_ON_ONCE(cpu_online(this_cpu) && irqs_disabled()
		     && !oops_in_progress);

	/*
	 * When @रुको we can deadlock when we पूर्णांकerrupt between llist_add() and
	 * arch_send_call_function_ipi*(); when !@रुको we can deadlock due to
	 * csd_lock() on because the पूर्णांकerrupt context uses the same csd
	 * storage.
	 */
	WARN_ON_ONCE(!in_task());

	csd = &csd_stack;
	अगर (!रुको) अणु
		csd = this_cpu_ptr(&csd_data);
		csd_lock(csd);
	पूर्ण

	csd->func = func;
	csd->info = info;
#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG
	csd->node.src = smp_processor_id();
	csd->node.dst = cpu;
#पूर्ण_अगर

	err = generic_exec_single(cpu, csd);

	अगर (रुको)
		csd_lock_रुको(csd);

	put_cpu();

	वापस err;
पूर्ण
EXPORT_SYMBOL(smp_call_function_single);

/**
 * smp_call_function_single_async(): Run an asynchronous function on a
 * 			         specअगरic CPU.
 * @cpu: The CPU to run on.
 * @csd: Pre-allocated and setup data काष्ठाure
 *
 * Like smp_call_function_single(), but the call is asynchonous and
 * can thus be करोne from contexts with disabled पूर्णांकerrupts.
 *
 * The caller passes his own pre-allocated data काष्ठाure
 * (ie: embedded in an object) and is responsible क्रम synchronizing it
 * such that the IPIs perक्रमmed on the @csd are strictly serialized.
 *
 * If the function is called with one csd which has not yet been
 * processed by previous call to smp_call_function_single_async(), the
 * function will वापस immediately with -EBUSY showing that the csd
 * object is still in progress.
 *
 * NOTE: Be careful, there is unक्रमtunately no current debugging facility to
 * validate the correctness of this serialization.
 */
पूर्णांक smp_call_function_single_async(पूर्णांक cpu, काष्ठा __call_single_data *csd)
अणु
	पूर्णांक err = 0;

	preempt_disable();

	अगर (csd->node.u_flags & CSD_FLAG_LOCK) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	csd->node.u_flags = CSD_FLAG_LOCK;
	smp_wmb();

	err = generic_exec_single(cpu, csd);

out:
	preempt_enable();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(smp_call_function_single_async);

/*
 * smp_call_function_any - Run a function on any of the given cpus
 * @mask: The mask of cpus it can run on.
 * @func: The function to run. This must be fast and non-blocking.
 * @info: An arbitrary poपूर्णांकer to pass to the function.
 * @रुको: If true, रुको until function has completed.
 *
 * Returns 0 on success, अन्यथा a negative status code (अगर no cpus were online).
 *
 * Selection preference:
 *	1) current cpu अगर in @mask
 *	2) any cpu of current node अगर in @mask
 *	3) any other online cpu in @mask
 */
पूर्णांक smp_call_function_any(स्थिर काष्ठा cpumask *mask,
			  smp_call_func_t func, व्योम *info, पूर्णांक रुको)
अणु
	अचिन्हित पूर्णांक cpu;
	स्थिर काष्ठा cpumask *nodemask;
	पूर्णांक ret;

	/* Try क्रम same CPU (cheapest) */
	cpu = get_cpu();
	अगर (cpumask_test_cpu(cpu, mask))
		जाओ call;

	/* Try क्रम same node. */
	nodemask = cpumask_of_node(cpu_to_node(cpu));
	क्रम (cpu = cpumask_first_and(nodemask, mask); cpu < nr_cpu_ids;
	     cpu = cpumask_next_and(cpu, nodemask, mask)) अणु
		अगर (cpu_online(cpu))
			जाओ call;
	पूर्ण

	/* Any online will करो: smp_call_function_single handles nr_cpu_ids. */
	cpu = cpumask_any_and(mask, cpu_online_mask);
call:
	ret = smp_call_function_single(cpu, func, info, रुको);
	put_cpu();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(smp_call_function_any);

/*
 * Flags to be used as scf_flags argument of smp_call_function_many_cond().
 *
 * %SCF_WAIT:		Wait until function execution is completed
 * %SCF_RUN_LOCAL:	Run also locally अगर local cpu is set in cpumask
 */
#घोषणा SCF_WAIT	(1U << 0)
#घोषणा SCF_RUN_LOCAL	(1U << 1)

अटल व्योम smp_call_function_many_cond(स्थिर काष्ठा cpumask *mask,
					smp_call_func_t func, व्योम *info,
					अचिन्हित पूर्णांक scf_flags,
					smp_cond_func_t cond_func)
अणु
	पूर्णांक cpu, last_cpu, this_cpu = smp_processor_id();
	काष्ठा call_function_data *cfd;
	bool रुको = scf_flags & SCF_WAIT;
	bool run_remote = false;
	bool run_local = false;
	पूर्णांक nr_cpus = 0;

	lockdep_निश्चित_preemption_disabled();

	/*
	 * Can deadlock when called with पूर्णांकerrupts disabled.
	 * We allow cpu's that are not yet online though, as no one अन्यथा can
	 * send smp call function पूर्णांकerrupt to this cpu and as such deadlocks
	 * can't happen.
	 */
	अगर (cpu_online(this_cpu) && !oops_in_progress &&
	    !early_boot_irqs_disabled)
		lockdep_निश्चित_irqs_enabled();

	/*
	 * When @रुको we can deadlock when we पूर्णांकerrupt between llist_add() and
	 * arch_send_call_function_ipi*(); when !@रुको we can deadlock due to
	 * csd_lock() on because the पूर्णांकerrupt context uses the same csd
	 * storage.
	 */
	WARN_ON_ONCE(!in_task());

	/* Check अगर we need local execution. */
	अगर ((scf_flags & SCF_RUN_LOCAL) && cpumask_test_cpu(this_cpu, mask))
		run_local = true;

	/* Check अगर we need remote execution, i.e., any CPU excluding this one. */
	cpu = cpumask_first_and(mask, cpu_online_mask);
	अगर (cpu == this_cpu)
		cpu = cpumask_next_and(cpu, mask, cpu_online_mask);
	अगर (cpu < nr_cpu_ids)
		run_remote = true;

	अगर (run_remote) अणु
		cfd = this_cpu_ptr(&cfd_data);
		cpumask_and(cfd->cpumask, mask, cpu_online_mask);
		__cpumask_clear_cpu(this_cpu, cfd->cpumask);

		cpumask_clear(cfd->cpumask_ipi);
		क्रम_each_cpu(cpu, cfd->cpumask) अणु
			काष्ठा cfd_percpu *pcpu = per_cpu_ptr(cfd->pcpu, cpu);
			call_single_data_t *csd = &pcpu->csd;

			अगर (cond_func && !cond_func(cpu, info))
				जारी;

			csd_lock(csd);
			अगर (रुको)
				csd->node.u_flags |= CSD_TYPE_SYNC;
			csd->func = func;
			csd->info = info;
#अगर_घोषित CONFIG_CSD_LOCK_WAIT_DEBUG
			csd->node.src = smp_processor_id();
			csd->node.dst = cpu;
#पूर्ण_अगर
			cfd_seq_store(pcpu->seq_queue, this_cpu, cpu, CFD_SEQ_QUEUE);
			अगर (llist_add(&csd->node.llist, &per_cpu(call_single_queue, cpu))) अणु
				__cpumask_set_cpu(cpu, cfd->cpumask_ipi);
				nr_cpus++;
				last_cpu = cpu;

				cfd_seq_store(pcpu->seq_ipi, this_cpu, cpu, CFD_SEQ_IPI);
			पूर्ण अन्यथा अणु
				cfd_seq_store(pcpu->seq_noipi, this_cpu, cpu, CFD_SEQ_NOIPI);
			पूर्ण
		पूर्ण

		cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->ping, this_cpu, CFD_SEQ_NOCPU, CFD_SEQ_PING);

		/*
		 * Choose the most efficient way to send an IPI. Note that the
		 * number of CPUs might be zero due to concurrent changes to the
		 * provided mask.
		 */
		अगर (nr_cpus == 1)
			send_call_function_single_ipi(last_cpu);
		अन्यथा अगर (likely(nr_cpus > 1))
			arch_send_call_function_ipi_mask(cfd->cpumask_ipi);

		cfd_seq_store(this_cpu_ptr(&cfd_seq_local)->pinged, this_cpu, CFD_SEQ_NOCPU, CFD_SEQ_PINGED);
	पूर्ण

	अगर (run_local && (!cond_func || cond_func(this_cpu, info))) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		func(info);
		local_irq_restore(flags);
	पूर्ण

	अगर (run_remote && रुको) अणु
		क्रम_each_cpu(cpu, cfd->cpumask) अणु
			call_single_data_t *csd;

			csd = &per_cpu_ptr(cfd->pcpu, cpu)->csd;
			csd_lock_रुको(csd);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * smp_call_function_many(): Run a function on a set of CPUs.
 * @mask: The set of cpus to run on (only runs on online subset).
 * @func: The function to run. This must be fast and non-blocking.
 * @info: An arbitrary poपूर्णांकer to pass to the function.
 * @flags: Biपंचांगask that controls the operation. If %SCF_WAIT is set, रुको
 *        (atomically) until function has completed on other CPUs. If
 *        %SCF_RUN_LOCAL is set, the function will also be run locally
 *        अगर the local CPU is set in the @cpumask.
 *
 * If @रुको is true, then वापसs once @func has वापसed.
 *
 * You must not call this function with disabled पूर्णांकerrupts or from a
 * hardware पूर्णांकerrupt handler or from a bottom half handler. Preemption
 * must be disabled when calling this function.
 */
व्योम smp_call_function_many(स्थिर काष्ठा cpumask *mask,
			    smp_call_func_t func, व्योम *info, bool रुको)
अणु
	smp_call_function_many_cond(mask, func, info, रुको * SCF_WAIT, शून्य);
पूर्ण
EXPORT_SYMBOL(smp_call_function_many);

/**
 * smp_call_function(): Run a function on all other CPUs.
 * @func: The function to run. This must be fast and non-blocking.
 * @info: An arbitrary poपूर्णांकer to pass to the function.
 * @रुको: If true, रुको (atomically) until function has completed
 *        on other CPUs.
 *
 * Returns 0.
 *
 * If @रुको is true, then वापसs once @func has वापसed; otherwise
 * it वापसs just beक्रमe the target cpu calls @func.
 *
 * You must not call this function with disabled पूर्णांकerrupts or from a
 * hardware पूर्णांकerrupt handler or from a bottom half handler.
 */
व्योम smp_call_function(smp_call_func_t func, व्योम *info, पूर्णांक रुको)
अणु
	preempt_disable();
	smp_call_function_many(cpu_online_mask, func, info, रुको);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(smp_call_function);

/* Setup configured maximum number of CPUs to activate */
अचिन्हित पूर्णांक setup_max_cpus = NR_CPUS;
EXPORT_SYMBOL(setup_max_cpus);


/*
 * Setup routine क्रम controlling SMP activation
 *
 * Command-line option of "nosmp" or "maxcpus=0" will disable SMP
 * activation entirely (the MPS table probe still happens, though).
 *
 * Command-line option of "maxcpus=<NUM>", where <NUM> is an पूर्णांकeger
 * greater than 0, limits the maximum number of CPUs activated in
 * SMP mode to <NUM>.
 */

व्योम __weak arch_disable_smp_support(व्योम) अणु पूर्ण

अटल पूर्णांक __init nosmp(अक्षर *str)
अणु
	setup_max_cpus = 0;
	arch_disable_smp_support();

	वापस 0;
पूर्ण

early_param("nosmp", nosmp);

/* this is hard limit */
अटल पूर्णांक __init nrcpus(अक्षर *str)
अणु
	पूर्णांक nr_cpus;

	अगर (get_option(&str, &nr_cpus) && nr_cpus > 0 && nr_cpus < nr_cpu_ids)
		nr_cpu_ids = nr_cpus;

	वापस 0;
पूर्ण

early_param("nr_cpus", nrcpus);

अटल पूर्णांक __init maxcpus(अक्षर *str)
अणु
	get_option(&str, &setup_max_cpus);
	अगर (setup_max_cpus == 0)
		arch_disable_smp_support();

	वापस 0;
पूर्ण

early_param("maxcpus", maxcpus);

/* Setup number of possible processor ids */
अचिन्हित पूर्णांक nr_cpu_ids __पढ़ो_mostly = NR_CPUS;
EXPORT_SYMBOL(nr_cpu_ids);

/* An arch may set nr_cpu_ids earlier अगर needed, so this would be redundant */
व्योम __init setup_nr_cpu_ids(व्योम)
अणु
	nr_cpu_ids = find_last_bit(cpumask_bits(cpu_possible_mask),NR_CPUS) + 1;
पूर्ण

/* Called by boot processor to activate the rest. */
व्योम __init smp_init(व्योम)
अणु
	पूर्णांक num_nodes, num_cpus;

	idle_thपढ़ोs_init();
	cpuhp_thपढ़ोs_init();

	pr_info("Bringing up secondary CPUs ...\n");

	bringup_nonboot_cpus(setup_max_cpus);

	num_nodes = num_online_nodes();
	num_cpus  = num_online_cpus();
	pr_info("Brought up %d node%s, %d CPU%s\n",
		num_nodes, (num_nodes > 1 ? "s" : ""),
		num_cpus,  (num_cpus  > 1 ? "s" : ""));

	/* Any cleanup work */
	smp_cpus_करोne(setup_max_cpus);
पूर्ण

/*
 * on_each_cpu_cond(): Call a function on each processor क्रम which
 * the supplied function cond_func वापसs true, optionally रुकोing
 * क्रम all the required CPUs to finish. This may include the local
 * processor.
 * @cond_func:	A callback function that is passed a cpu id and
 *		the info parameter. The function is called
 *		with preemption disabled. The function should
 *		वापस a blooean value indicating whether to IPI
 *		the specअगरied CPU.
 * @func:	The function to run on all applicable CPUs.
 *		This must be fast and non-blocking.
 * @info:	An arbitrary poपूर्णांकer to pass to both functions.
 * @रुको:	If true, रुको (atomically) until function has
 *		completed on other CPUs.
 *
 * Preemption is disabled to protect against CPUs going offline but not online.
 * CPUs going online during the call will not be seen or sent an IPI.
 *
 * You must not call this function with disabled पूर्णांकerrupts or
 * from a hardware पूर्णांकerrupt handler or from a bottom half handler.
 */
व्योम on_each_cpu_cond_mask(smp_cond_func_t cond_func, smp_call_func_t func,
			   व्योम *info, bool रुको, स्थिर काष्ठा cpumask *mask)
अणु
	अचिन्हित पूर्णांक scf_flags = SCF_RUN_LOCAL;

	अगर (रुको)
		scf_flags |= SCF_WAIT;

	preempt_disable();
	smp_call_function_many_cond(mask, func, info, scf_flags, cond_func);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(on_each_cpu_cond_mask);

अटल व्योम करो_nothing(व्योम *unused)
अणु
पूर्ण

/**
 * kick_all_cpus_sync - Force all cpus out of idle
 *
 * Used to synchronize the update of pm_idle function poपूर्णांकer. It's
 * called after the poपूर्णांकer is updated and वापसs after the dummy
 * callback function has been executed on all cpus. The execution of
 * the function can only happen on the remote cpus after they have
 * left the idle function which had been called via pm_idle function
 * poपूर्णांकer. So it's guaranteed that nothing uses the previous poपूर्णांकer
 * anymore.
 */
व्योम kick_all_cpus_sync(व्योम)
अणु
	/* Make sure the change is visible beक्रमe we kick the cpus */
	smp_mb();
	smp_call_function(करो_nothing, शून्य, 1);
पूर्ण
EXPORT_SYMBOL_GPL(kick_all_cpus_sync);

/**
 * wake_up_all_idle_cpus - अवरोध all cpus out of idle
 * wake_up_all_idle_cpus try to अवरोध all cpus which is in idle state even
 * including idle polling cpus, क्रम non-idle cpus, we will करो nothing
 * क्रम them.
 */
व्योम wake_up_all_idle_cpus(व्योम)
अणु
	पूर्णांक cpu;

	preempt_disable();
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == smp_processor_id())
			जारी;

		wake_up_अगर_idle(cpu);
	पूर्ण
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(wake_up_all_idle_cpus);

/**
 * smp_call_on_cpu - Call a function on a specअगरic cpu
 *
 * Used to call a function on a specअगरic cpu and रुको क्रम it to वापस.
 * Optionally make sure the call is करोne on a specअगरied physical cpu via vcpu
 * pinning in order to support भवized environments.
 */
काष्ठा smp_call_on_cpu_काष्ठा अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा completion	करोne;
	पूर्णांक			(*func)(व्योम *);
	व्योम			*data;
	पूर्णांक			ret;
	पूर्णांक			cpu;
पूर्ण;

अटल व्योम smp_call_on_cpu_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smp_call_on_cpu_काष्ठा *sscs;

	sscs = container_of(work, काष्ठा smp_call_on_cpu_काष्ठा, work);
	अगर (sscs->cpu >= 0)
		hypervisor_pin_vcpu(sscs->cpu);
	sscs->ret = sscs->func(sscs->data);
	अगर (sscs->cpu >= 0)
		hypervisor_pin_vcpu(-1);

	complete(&sscs->करोne);
पूर्ण

पूर्णांक smp_call_on_cpu(अचिन्हित पूर्णांक cpu, पूर्णांक (*func)(व्योम *), व्योम *par, bool phys)
अणु
	काष्ठा smp_call_on_cpu_काष्ठा sscs = अणु
		.करोne = COMPLETION_INITIALIZER_ONSTACK(sscs.करोne),
		.func = func,
		.data = par,
		.cpu  = phys ? cpu : -1,
	पूर्ण;

	INIT_WORK_ONSTACK(&sscs.work, smp_call_on_cpu_callback);

	अगर (cpu >= nr_cpu_ids || !cpu_online(cpu))
		वापस -ENXIO;

	queue_work_on(cpu, प्रणाली_wq, &sscs.work);
	रुको_क्रम_completion(&sscs.करोne);

	वापस sscs.ret;
पूर्ण
EXPORT_SYMBOL_GPL(smp_call_on_cpu);
