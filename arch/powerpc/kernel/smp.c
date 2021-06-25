<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP support क्रम ppc.
 *
 * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great
 * deal of code from the sparc and पूर्णांकel versions.
 *
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 *
 * PowerPC-64 Support added by Dave Engebretsen, Peter Bergner, and
 * Mike Corrigan अणुengebret|bergner|mikecपूर्ण@us.ibm.com
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/topology.h>
#समावेश <linux/profile.h>
#समावेश <linux/processor.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/stackprotector.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/vdso_datapage.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#पूर्ण_अगर
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/kup.h>

#अगर_घोषित DEBUG
#समावेश <यंत्र/udbg.h>
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
/* State of each CPU during hotplug phases */
अटल DEFINE_PER_CPU(पूर्णांक, cpu_state) = अणु 0 पूर्ण;
#पूर्ण_अगर

काष्ठा task_काष्ठा *secondary_current;
bool has_big_cores;
bool coregroup_enabled;
bool thपढ़ो_group_shares_l2;

DEFINE_PER_CPU(cpumask_var_t, cpu_sibling_map);
DEFINE_PER_CPU(cpumask_var_t, cpu_smallcore_map);
DEFINE_PER_CPU(cpumask_var_t, cpu_l2_cache_map);
DEFINE_PER_CPU(cpumask_var_t, cpu_core_map);
अटल DEFINE_PER_CPU(cpumask_var_t, cpu_coregroup_map);

EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);
EXPORT_PER_CPU_SYMBOL(cpu_l2_cache_map);
EXPORT_PER_CPU_SYMBOL(cpu_core_map);
EXPORT_SYMBOL_GPL(has_big_cores);

क्रमागत अणु
#अगर_घोषित CONFIG_SCHED_SMT
	smt_idx,
#पूर्ण_अगर
	cache_idx,
	mc_idx,
	die_idx,
पूर्ण;

#घोषणा MAX_THREAD_LIST_SIZE	8
#घोषणा THREAD_GROUP_SHARE_L1   1
#घोषणा THREAD_GROUP_SHARE_L2   2
काष्ठा thपढ़ो_groups अणु
	अचिन्हित पूर्णांक property;
	अचिन्हित पूर्णांक nr_groups;
	अचिन्हित पूर्णांक thपढ़ोs_per_group;
	अचिन्हित पूर्णांक thपढ़ो_list[MAX_THREAD_LIST_SIZE];
पूर्ण;

/* Maximum number of properties that groups of thपढ़ोs within a core can share */
#घोषणा MAX_THREAD_GROUP_PROPERTIES 2

काष्ठा thपढ़ो_groups_list अणु
	अचिन्हित पूर्णांक nr_properties;
	काष्ठा thपढ़ो_groups property_tgs[MAX_THREAD_GROUP_PROPERTIES];
पूर्ण;

अटल काष्ठा thपढ़ो_groups_list tgl[NR_CPUS] __initdata;
/*
 * On big-cores प्रणाली, thपढ़ो_group_l1_cache_map क्रम each CPU corresponds to
 * the set its siblings that share the L1-cache.
 */
अटल DEFINE_PER_CPU(cpumask_var_t, thपढ़ो_group_l1_cache_map);

/*
 * On some big-cores प्रणाली, thपढ़ो_group_l2_cache_map क्रम each CPU
 * corresponds to the set its siblings within the core that share the
 * L2-cache.
 */
अटल DEFINE_PER_CPU(cpumask_var_t, thपढ़ो_group_l2_cache_map);

/* SMP operations क्रम this machine */
काष्ठा smp_ops_t *smp_ops;

/* Can't be अटल due to PowerMac hackery */
अस्थिर अचिन्हित पूर्णांक cpu_callin_map[NR_CPUS];

पूर्णांक smt_enabled_at_boot = 1;

/*
 * Returns 1 अगर the specअगरied cpu should be brought up during boot.
 * Used to inhibit booting thपढ़ोs अगर they've been disabled or
 * limited on the command line
 */
पूर्णांक smp_generic_cpu_bootable(अचिन्हित पूर्णांक nr)
अणु
	/* Special हाल - we inhibit secondary thपढ़ो startup
	 * during boot अगर the user requests it.
	 */
	अगर (प्रणाली_state < SYSTEM_RUNNING && cpu_has_feature(CPU_FTR_SMT)) अणु
		अगर (!smt_enabled_at_boot && cpu_thपढ़ो_in_core(nr) != 0)
			वापस 0;
		अगर (smt_enabled_at_boot
		    && cpu_thपढ़ो_in_core(nr) >= smt_enabled_at_boot)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण


#अगर_घोषित CONFIG_PPC64
पूर्णांक smp_generic_kick_cpu(पूर्णांक nr)
अणु
	अगर (nr < 0 || nr >= nr_cpu_ids)
		वापस -EINVAL;

	/*
	 * The processor is currently spinning, रुकोing क्रम the
	 * cpu_start field to become non-zero After we set cpu_start,
	 * the processor will जारी on to secondary_start
	 */
	अगर (!paca_ptrs[nr]->cpu_start) अणु
		paca_ptrs[nr]->cpu_start = 1;
		smp_mb();
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
	/*
	 * Ok it's not there, so it might be soft-unplugged, let's
	 * try to bring it back
	 */
	generic_set_cpu_up(nr);
	smp_wmb();
	smp_send_reschedule(nr);
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

अटल irqवापस_t call_function_action(पूर्णांक irq, व्योम *data)
अणु
	generic_smp_call_function_पूर्णांकerrupt();
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t reschedule_action(पूर्णांक irq, व्योम *data)
अणु
	scheduler_ipi();
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
अटल irqवापस_t tick_broadcast_ipi_action(पूर्णांक irq, व्योम *data)
अणु
	समयr_broadcast_पूर्णांकerrupt();
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NMI_IPI
अटल irqवापस_t nmi_ipi_action(पूर्णांक irq, व्योम *data)
अणु
	smp_handle_nmi_ipi(get_irq_regs());
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

अटल irq_handler_t smp_ipi_action[] = अणु
	[PPC_MSG_CALL_FUNCTION] =  call_function_action,
	[PPC_MSG_RESCHEDULE] = reschedule_action,
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	[PPC_MSG_TICK_BROADCAST] = tick_broadcast_ipi_action,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NMI_IPI
	[PPC_MSG_NMI_IPI] = nmi_ipi_action,
#पूर्ण_अगर
पूर्ण;

/*
 * The NMI IPI is a fallback and not truly non-maskable. It is simpler
 * than going through the call function infraकाष्ठाure, and strongly
 * serialized, so it is more appropriate क्रम debugging.
 */
स्थिर अक्षर *smp_ipi_name[] = अणु
	[PPC_MSG_CALL_FUNCTION] =  "ipi call function",
	[PPC_MSG_RESCHEDULE] = "ipi reschedule",
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	[PPC_MSG_TICK_BROADCAST] = "ipi tick-broadcast",
#पूर्ण_अगर
#अगर_घोषित CONFIG_NMI_IPI
	[PPC_MSG_NMI_IPI] = "nmi ipi",
#पूर्ण_अगर
पूर्ण;

/* optional function to request ipi, क्रम controllers with >= 4 ipis */
पूर्णांक smp_request_message_ipi(पूर्णांक virq, पूर्णांक msg)
अणु
	पूर्णांक err;

	अगर (msg < 0 || msg > PPC_MSG_NMI_IPI)
		वापस -EINVAL;
#अगर_अघोषित CONFIG_NMI_IPI
	अगर (msg == PPC_MSG_NMI_IPI)
		वापस 1;
#पूर्ण_अगर

	err = request_irq(virq, smp_ipi_action[msg],
			  IRQF_PERCPU | IRQF_NO_THREAD | IRQF_NO_SUSPEND,
			  smp_ipi_name[msg], शून्य);
	WARN(err < 0, "unable to request_irq %d for %s (rc %d)\n",
		virq, smp_ipi_name[msg], err);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PPC_SMP_MUXED_IPI
काष्ठा cpu_messages अणु
	दीर्घ messages;			/* current messages */
पूर्ण;
अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा cpu_messages, ipi_message);

व्योम smp_muxed_ipi_set_message(पूर्णांक cpu, पूर्णांक msg)
अणु
	काष्ठा cpu_messages *info = &per_cpu(ipi_message, cpu);
	अक्षर *message = (अक्षर *)&info->messages;

	/*
	 * Order previous accesses beक्रमe accesses in the IPI handler.
	 */
	smp_mb();
	message[msg] = 1;
पूर्ण

व्योम smp_muxed_ipi_message_pass(पूर्णांक cpu, पूर्णांक msg)
अणु
	smp_muxed_ipi_set_message(cpu, msg);

	/*
	 * cause_ipi functions are required to include a full barrier
	 * beक्रमe करोing whatever causes the IPI.
	 */
	smp_ops->cause_ipi(cpu);
पूर्ण

#अगर_घोषित __BIG_ENDIAN__
#घोषणा IPI_MESSAGE(A) (1uL << ((BITS_PER_LONG - 8) - 8 * (A)))
#अन्यथा
#घोषणा IPI_MESSAGE(A) (1uL << (8 * (A)))
#पूर्ण_अगर

irqवापस_t smp_ipi_demux(व्योम)
अणु
	mb();	/* order any irq clear */

	वापस smp_ipi_demux_relaxed();
पूर्ण

/* sync-मुक्त variant. Callers should ensure synchronization */
irqवापस_t smp_ipi_demux_relaxed(व्योम)
अणु
	काष्ठा cpu_messages *info;
	अचिन्हित दीर्घ all;

	info = this_cpu_ptr(&ipi_message);
	करो अणु
		all = xchg(&info->messages, 0);
#अगर defined(CONFIG_KVM_XICS) && defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE)
		/*
		 * Must check क्रम PPC_MSG_RM_HOST_ACTION messages
		 * beक्रमe PPC_MSG_CALL_FUNCTION messages because when
		 * a VM is destroyed, we call kick_all_cpus_sync()
		 * to ensure that any pending PPC_MSG_RM_HOST_ACTION
		 * messages have completed beक्रमe we मुक्त any VCPUs.
		 */
		अगर (all & IPI_MESSAGE(PPC_MSG_RM_HOST_ACTION))
			kvmppc_xics_ipi_action();
#पूर्ण_अगर
		अगर (all & IPI_MESSAGE(PPC_MSG_CALL_FUNCTION))
			generic_smp_call_function_पूर्णांकerrupt();
		अगर (all & IPI_MESSAGE(PPC_MSG_RESCHEDULE))
			scheduler_ipi();
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
		अगर (all & IPI_MESSAGE(PPC_MSG_TICK_BROADCAST))
			समयr_broadcast_पूर्णांकerrupt();
#पूर्ण_अगर
#अगर_घोषित CONFIG_NMI_IPI
		अगर (all & IPI_MESSAGE(PPC_MSG_NMI_IPI))
			nmi_ipi_action(0, शून्य);
#पूर्ण_अगर
	पूर्ण जबतक (info->messages);

	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SMP_MUXED_IPI */

अटल अंतरभूत व्योम करो_message_pass(पूर्णांक cpu, पूर्णांक msg)
अणु
	अगर (smp_ops->message_pass)
		smp_ops->message_pass(cpu, msg);
#अगर_घोषित CONFIG_PPC_SMP_MUXED_IPI
	अन्यथा
		smp_muxed_ipi_message_pass(cpu, msg);
#पूर्ण_अगर
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	अगर (likely(smp_ops))
		करो_message_pass(cpu, PPC_MSG_RESCHEDULE);
पूर्ण
EXPORT_SYMBOL_GPL(smp_send_reschedule);

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	करो_message_pass(cpu, PPC_MSG_CALL_FUNCTION);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		करो_message_pass(cpu, PPC_MSG_CALL_FUNCTION);
पूर्ण

#अगर_घोषित CONFIG_NMI_IPI

/*
 * "NMI IPI" प्रणाली.
 *
 * NMI IPIs may not be recoverable, so should not be used as ongoing part of
 * a running प्रणाली. They can be used क्रम crash, debug, halt/reboot, etc.
 *
 * The IPI call रुकोs with पूर्णांकerrupts disabled until all tarमाला_लो enter the
 * NMI handler, then वापसs. Subsequent IPIs can be issued beक्रमe tarमाला_लो
 * have वापसed from their handlers, so there is no guarantee about
 * concurrency or re-entrancy.
 *
 * A new NMI can be issued beक्रमe all tarमाला_लो निकास the handler.
 *
 * The IPI call may समय out without all tarमाला_लो entering the NMI handler.
 * In that हाल, there is some logic to recover (and ignore subsequent
 * NMI पूर्णांकerrupts that may eventually be उठाओd), but the platक्रमm पूर्णांकerrupt
 * handler may not be able to distinguish this from other exception causes,
 * which may cause a crash.
 */

अटल atomic_t __nmi_ipi_lock = ATOMIC_INIT(0);
अटल काष्ठा cpumask nmi_ipi_pending_mask;
अटल bool nmi_ipi_busy = false;
अटल व्योम (*nmi_ipi_function)(काष्ठा pt_regs *) = शून्य;

अटल व्योम nmi_ipi_lock_start(अचिन्हित दीर्घ *flags)
अणु
	raw_local_irq_save(*flags);
	hard_irq_disable();
	जबतक (atomic_cmpxchg(&__nmi_ipi_lock, 0, 1) == 1) अणु
		raw_local_irq_restore(*flags);
		spin_until_cond(atomic_पढ़ो(&__nmi_ipi_lock) == 0);
		raw_local_irq_save(*flags);
		hard_irq_disable();
	पूर्ण
पूर्ण

अटल व्योम nmi_ipi_lock(व्योम)
अणु
	जबतक (atomic_cmpxchg(&__nmi_ipi_lock, 0, 1) == 1)
		spin_until_cond(atomic_पढ़ो(&__nmi_ipi_lock) == 0);
पूर्ण

अटल व्योम nmi_ipi_unlock(व्योम)
अणु
	smp_mb();
	WARN_ON(atomic_पढ़ो(&__nmi_ipi_lock) != 1);
	atomic_set(&__nmi_ipi_lock, 0);
पूर्ण

अटल व्योम nmi_ipi_unlock_end(अचिन्हित दीर्घ *flags)
अणु
	nmi_ipi_unlock();
	raw_local_irq_restore(*flags);
पूर्ण

/*
 * Platक्रमm NMI handler calls this to ack
 */
पूर्णांक smp_handle_nmi_ipi(काष्ठा pt_regs *regs)
अणु
	व्योम (*fn)(काष्ठा pt_regs *) = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक me = raw_smp_processor_id();
	पूर्णांक ret = 0;

	/*
	 * Unexpected NMIs are possible here because the पूर्णांकerrupt may not
	 * be able to distinguish NMI IPIs from other types of NMIs, or
	 * because the caller may have समयd out.
	 */
	nmi_ipi_lock_start(&flags);
	अगर (cpumask_test_cpu(me, &nmi_ipi_pending_mask)) अणु
		cpumask_clear_cpu(me, &nmi_ipi_pending_mask);
		fn = READ_ONCE(nmi_ipi_function);
		WARN_ON_ONCE(!fn);
		ret = 1;
	पूर्ण
	nmi_ipi_unlock_end(&flags);

	अगर (fn)
		fn(regs);

	वापस ret;
पूर्ण

अटल व्योम करो_smp_send_nmi_ipi(पूर्णांक cpu, bool safe)
अणु
	अगर (!safe && smp_ops->cause_nmi_ipi && smp_ops->cause_nmi_ipi(cpu))
		वापस;

	अगर (cpu >= 0) अणु
		करो_message_pass(cpu, PPC_MSG_NMI_IPI);
	पूर्ण अन्यथा अणु
		पूर्णांक c;

		क्रम_each_online_cpu(c) अणु
			अगर (c == raw_smp_processor_id())
				जारी;
			करो_message_pass(c, PPC_MSG_NMI_IPI);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * - cpu is the target CPU (must not be this CPU), or NMI_IPI_ALL_OTHERS.
 * - fn is the target callback function.
 * - delay_us > 0 is the delay beक्रमe giving up रुकोing क्रम tarमाला_लो to
 *   begin executing the handler, == 0 specअगरies indefinite delay.
 */
अटल पूर्णांक __smp_send_nmi_ipi(पूर्णांक cpu, व्योम (*fn)(काष्ठा pt_regs *),
				u64 delay_us, bool safe)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक me = raw_smp_processor_id();
	पूर्णांक ret = 1;

	BUG_ON(cpu == me);
	BUG_ON(cpu < 0 && cpu != NMI_IPI_ALL_OTHERS);

	अगर (unlikely(!smp_ops))
		वापस 0;

	nmi_ipi_lock_start(&flags);
	जबतक (nmi_ipi_busy) अणु
		nmi_ipi_unlock_end(&flags);
		spin_until_cond(!nmi_ipi_busy);
		nmi_ipi_lock_start(&flags);
	पूर्ण
	nmi_ipi_busy = true;
	nmi_ipi_function = fn;

	WARN_ON_ONCE(!cpumask_empty(&nmi_ipi_pending_mask));

	अगर (cpu < 0) अणु
		/* ALL_OTHERS */
		cpumask_copy(&nmi_ipi_pending_mask, cpu_online_mask);
		cpumask_clear_cpu(me, &nmi_ipi_pending_mask);
	पूर्ण अन्यथा अणु
		cpumask_set_cpu(cpu, &nmi_ipi_pending_mask);
	पूर्ण

	nmi_ipi_unlock();

	/* Interrupts reमुख्य hard disabled */

	करो_smp_send_nmi_ipi(cpu, safe);

	nmi_ipi_lock();
	/* nmi_ipi_busy is set here, so unlock/lock is okay */
	जबतक (!cpumask_empty(&nmi_ipi_pending_mask)) अणु
		nmi_ipi_unlock();
		udelay(1);
		nmi_ipi_lock();
		अगर (delay_us) अणु
			delay_us--;
			अगर (!delay_us)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cpumask_empty(&nmi_ipi_pending_mask)) अणु
		/* Timeout रुकोing क्रम CPUs to call smp_handle_nmi_ipi */
		ret = 0;
		cpumask_clear(&nmi_ipi_pending_mask);
	पूर्ण

	nmi_ipi_function = शून्य;
	nmi_ipi_busy = false;

	nmi_ipi_unlock_end(&flags);

	वापस ret;
पूर्ण

पूर्णांक smp_send_nmi_ipi(पूर्णांक cpu, व्योम (*fn)(काष्ठा pt_regs *), u64 delay_us)
अणु
	वापस __smp_send_nmi_ipi(cpu, fn, delay_us, false);
पूर्ण

पूर्णांक smp_send_safe_nmi_ipi(पूर्णांक cpu, व्योम (*fn)(काष्ठा pt_regs *), u64 delay_us)
अणु
	वापस __smp_send_nmi_ipi(cpu, fn, delay_us, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_NMI_IPI */

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		करो_message_pass(cpu, PPC_MSG_TICK_BROADCAST);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUGGER
अटल व्योम debugger_ipi_callback(काष्ठा pt_regs *regs)
अणु
	debugger_ipi(regs);
पूर्ण

व्योम smp_send_debugger_अवरोध(व्योम)
अणु
	smp_send_nmi_ipi(NMI_IPI_ALL_OTHERS, debugger_ipi_callback, 1000000);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_CORE
व्योम crash_send_ipi(व्योम (*crash_ipi_callback)(काष्ठा pt_regs *))
अणु
	पूर्णांक cpu;

	smp_send_nmi_ipi(NMI_IPI_ALL_OTHERS, crash_ipi_callback, 1000000);
	अगर (kdump_in_progress() && crash_wake_offline) अणु
		क्रम_each_present_cpu(cpu) अणु
			अगर (cpu_online(cpu))
				जारी;
			/*
			 * crash_ipi_callback will रुको क्रम
			 * all cpus, including offline CPUs.
			 * We करोn't care about nmi_ipi_function.
			 * Offline cpus will jump straight पूर्णांकo
			 * crash_ipi_callback, we can skip the
			 * entire NMI dance and रुकोing क्रम
			 * cpus to clear pending mask, etc.
			 */
			करो_smp_send_nmi_ipi(cpu, false);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NMI_IPI
अटल व्योम nmi_stop_this_cpu(काष्ठा pt_regs *regs)
अणु
	/*
	 * IRQs are alपढ़ोy hard disabled by the smp_handle_nmi_ipi.
	 */
	spin_begin();
	जबतक (1)
		spin_cpu_relax();
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	smp_send_nmi_ipi(NMI_IPI_ALL_OTHERS, nmi_stop_this_cpu, 1000000);
पूर्ण

#अन्यथा /* CONFIG_NMI_IPI */

अटल व्योम stop_this_cpu(व्योम *dummy)
अणु
	hard_irq_disable();
	spin_begin();
	जबतक (1)
		spin_cpu_relax();
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	अटल bool stopped = false;

	/*
	 * Prevent रुकोing on csd lock from a previous smp_send_stop.
	 * This is racy, but in general callers try to करो the right
	 * thing and only fire off one smp_send_stop (e.g., see
	 * kernel/panic.c)
	 */
	अगर (stopped)
		वापस;

	stopped = true;

	smp_call_function(stop_this_cpu, शून्य, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_NMI_IPI */

काष्ठा task_काष्ठा *current_set[NR_CPUS];

अटल व्योम smp_store_cpu_info(पूर्णांक id)
अणु
	per_cpu(cpu_pvr, id) = mfspr(SPRN_PVR);
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	per_cpu(next_tlbcam_idx, id)
		= (mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY) - 1;
#पूर्ण_अगर
पूर्ण

/*
 * Relationships between CPUs are मुख्यtained in a set of per-cpu cpumasks so
 * rather than just passing around the cpumask we pass around a function that
 * वापसs the that cpumask क्रम the given CPU.
 */
अटल व्योम set_cpus_related(पूर्णांक i, पूर्णांक j, काष्ठा cpumask *(*get_cpumask)(पूर्णांक))
अणु
	cpumask_set_cpu(i, get_cpumask(j));
	cpumask_set_cpu(j, get_cpumask(i));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम set_cpus_unrelated(पूर्णांक i, पूर्णांक j,
		काष्ठा cpumask *(*get_cpumask)(पूर्णांक))
अणु
	cpumask_clear_cpu(i, get_cpumask(j));
	cpumask_clear_cpu(j, get_cpumask(i));
पूर्ण
#पूर्ण_अगर

/*
 * Extends set_cpus_related. Instead of setting one CPU at a समय in
 * dsपंचांगask, set srcmask at oneshot. dsपंचांगask should be super set of srcmask.
 */
अटल व्योम or_cpumasks_related(पूर्णांक i, पूर्णांक j, काष्ठा cpumask *(*srcmask)(पूर्णांक),
				काष्ठा cpumask *(*dsपंचांगask)(पूर्णांक))
अणु
	काष्ठा cpumask *mask;
	पूर्णांक k;

	mask = srcmask(j);
	क्रम_each_cpu(k, srcmask(i))
		cpumask_or(dsपंचांगask(k), dsपंचांगask(k), mask);

	अगर (i == j)
		वापस;

	mask = srcmask(i);
	क्रम_each_cpu(k, srcmask(j))
		cpumask_or(dsपंचांगask(k), dsपंचांगask(k), mask);
पूर्ण

/*
 * parse_thपढ़ो_groups: Parses the "ibm,thread-groups" device tree
 *                      property क्रम the CPU device node @dn and stores
 *                      the parsed output in the thपढ़ो_groups_list
 *                      काष्ठाure @tglp.
 *
 * @dn: The device node of the CPU device.
 * @tglp: Poपूर्णांकer to a thपढ़ो group list काष्ठाure पूर्णांकo which the parsed
 *      output of "ibm,thread-groups" is stored.
 *
 * ibm,thपढ़ो-groups[0..N-1] array defines which group of thपढ़ोs in
 * the CPU-device node can be grouped together based on the property.
 *
 * This array can represent thपढ़ो groupings क्रम multiple properties.
 *
 * ibm,thपढ़ो-groups[i + 0] tells us the property based on which the
 * thपढ़ोs are being grouped together. If this value is 1, it implies
 * that the thपढ़ोs in the same group share L1, translation cache. If
 * the value is 2, it implies that the thपढ़ोs in the same group share
 * the same L2 cache.
 *
 * ibm,thपढ़ो-groups[i+1] tells us how many such thपढ़ो groups exist क्रम the
 * property ibm,thपढ़ो-groups[i]
 *
 * ibm,thपढ़ो-groups[i+2] tells us the number of thपढ़ोs in each such
 * group.
 * Suppose k = (ibm,thपढ़ो-groups[i+1] * ibm,thपढ़ो-groups[i+2]), then,
 *
 * ibm,thपढ़ो-groups[i+3..i+k+2] (is the list of thपढ़ोs identअगरied by
 * "ibm,ppc-interrupt-server#s" arranged as per their membership in
 * the grouping.
 *
 * Example:
 * If "ibm,thread-groups" = [1,2,4,8,10,12,14,9,11,13,15,2,2,4,8,10,12,14,9,11,13,15]
 * This can be decomposed up पूर्णांकo two consecutive arrays:
 * a) [1,2,4,8,10,12,14,9,11,13,15]
 * b) [2,2,4,8,10,12,14,9,11,13,15]
 *
 * where in,
 *
 * a) provides inक्रमmation of Property "1" being shared by "2" groups,
 *  each with "4" thपढ़ोs each. The "ibm,ppc-interrupt-server#s" of
 *  the first group is अणु8,10,12,14पूर्ण and the
 *  "ibm,ppc-interrupt-server#s" of the second group is
 *  अणु9,11,13,15पूर्ण. Property "1" is indicative of the thपढ़ो in the
 *  group sharing L1 cache, translation cache and Inकाष्ठाion Data
 *  flow.
 *
 * b) provides inक्रमmation of Property "2" being shared by "2" groups,
 *  each group with "4" thपढ़ोs. The "ibm,ppc-interrupt-server#s" of
 *  the first group is अणु8,10,12,14पूर्ण and the
 *  "ibm,ppc-interrupt-server#s" of the second group is
 *  अणु9,11,13,15पूर्ण. Property "2" indicates that the thपढ़ोs in each
 *  group share the L2-cache.
 *
 * Returns 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 */
अटल पूर्णांक parse_thपढ़ो_groups(काष्ठा device_node *dn,
			       काष्ठा thपढ़ो_groups_list *tglp)
अणु
	अचिन्हित पूर्णांक property_idx = 0;
	u32 *thपढ़ो_group_array;
	माप_प्रकार total_thपढ़ोs;
	पूर्णांक ret = 0, count;
	u32 *thपढ़ो_list;
	पूर्णांक i = 0;

	count = of_property_count_u32_elems(dn, "ibm,thread-groups");
	thपढ़ो_group_array = kसुस्मृति(count, माप(u32), GFP_KERNEL);
	ret = of_property_पढ़ो_u32_array(dn, "ibm,thread-groups",
					 thपढ़ो_group_array, count);
	अगर (ret)
		जाओ out_मुक्त;

	जबतक (i < count && property_idx < MAX_THREAD_GROUP_PROPERTIES) अणु
		पूर्णांक j;
		काष्ठा thपढ़ो_groups *tg = &tglp->property_tgs[property_idx++];

		tg->property = thपढ़ो_group_array[i];
		tg->nr_groups = thपढ़ो_group_array[i + 1];
		tg->thपढ़ोs_per_group = thपढ़ो_group_array[i + 2];
		total_thपढ़ोs = tg->nr_groups * tg->thपढ़ोs_per_group;

		thपढ़ो_list = &thपढ़ो_group_array[i + 3];

		क्रम (j = 0; j < total_thपढ़ोs; j++)
			tg->thपढ़ो_list[j] = thपढ़ो_list[j];
		i = i + 3 + total_thपढ़ोs;
	पूर्ण

	tglp->nr_properties = property_idx;

out_मुक्त:
	kमुक्त(thपढ़ो_group_array);
	वापस ret;
पूर्ण

/*
 * get_cpu_thपढ़ो_group_start : Searches the thपढ़ो group in tg->thपढ़ो_list
 *                              that @cpu beदीर्घs to.
 *
 * @cpu : The logical CPU whose thपढ़ो group is being searched.
 * @tg : The thपढ़ो-group काष्ठाure of the CPU node which @cpu beदीर्घs
 *       to.
 *
 * Returns the index to tg->thपढ़ो_list that poपूर्णांकs to the the start
 * of the thपढ़ो_group that @cpu beदीर्घs to.
 *
 * Returns -1 अगर cpu करोesn't beदीर्घ to any of the groups poपूर्णांकed to by
 * tg->thपढ़ो_list.
 */
अटल पूर्णांक get_cpu_thपढ़ो_group_start(पूर्णांक cpu, काष्ठा thपढ़ो_groups *tg)
अणु
	पूर्णांक hw_cpu_id = get_hard_smp_processor_id(cpu);
	पूर्णांक i, j;

	क्रम (i = 0; i < tg->nr_groups; i++) अणु
		पूर्णांक group_start = i * tg->thपढ़ोs_per_group;

		क्रम (j = 0; j < tg->thपढ़ोs_per_group; j++) अणु
			पूर्णांक idx = group_start + j;

			अगर (tg->thपढ़ो_list[idx] == hw_cpu_id)
				वापस group_start;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल काष्ठा thपढ़ो_groups *__init get_thपढ़ो_groups(पूर्णांक cpu,
						      पूर्णांक group_property,
						      पूर्णांक *err)
अणु
	काष्ठा device_node *dn = of_get_cpu_node(cpu, शून्य);
	काष्ठा thपढ़ो_groups_list *cpu_tgl = &tgl[cpu];
	काष्ठा thपढ़ो_groups *tg = शून्य;
	पूर्णांक i;
	*err = 0;

	अगर (!dn) अणु
		*err = -ENODATA;
		वापस शून्य;
	पूर्ण

	अगर (!cpu_tgl->nr_properties) अणु
		*err = parse_thपढ़ो_groups(dn, cpu_tgl);
		अगर (*err)
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < cpu_tgl->nr_properties; i++) अणु
		अगर (cpu_tgl->property_tgs[i].property == group_property) अणु
			tg = &cpu_tgl->property_tgs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tg)
		*err = -EINVAL;
out:
	of_node_put(dn);
	वापस tg;
पूर्ण

अटल पूर्णांक __init init_thपढ़ो_group_cache_map(पूर्णांक cpu, पूर्णांक cache_property)

अणु
	पूर्णांक first_thपढ़ो = cpu_first_thपढ़ो_sibling(cpu);
	पूर्णांक i, cpu_group_start = -1, err = 0;
	काष्ठा thपढ़ो_groups *tg = शून्य;
	cpumask_var_t *mask = शून्य;

	अगर (cache_property != THREAD_GROUP_SHARE_L1 &&
	    cache_property != THREAD_GROUP_SHARE_L2)
		वापस -EINVAL;

	tg = get_thपढ़ो_groups(cpu, cache_property, &err);
	अगर (!tg)
		वापस err;

	cpu_group_start = get_cpu_thपढ़ो_group_start(cpu, tg);

	अगर (unlikely(cpu_group_start == -1)) अणु
		WARN_ON_ONCE(1);
		वापस -ENODATA;
	पूर्ण

	अगर (cache_property == THREAD_GROUP_SHARE_L1)
		mask = &per_cpu(thपढ़ो_group_l1_cache_map, cpu);
	अन्यथा अगर (cache_property == THREAD_GROUP_SHARE_L2)
		mask = &per_cpu(thपढ़ो_group_l2_cache_map, cpu);

	zalloc_cpumask_var_node(mask, GFP_KERNEL, cpu_to_node(cpu));

	क्रम (i = first_thपढ़ो; i < first_thपढ़ो + thपढ़ोs_per_core; i++) अणु
		पूर्णांक i_group_start = get_cpu_thपढ़ो_group_start(i, tg);

		अगर (unlikely(i_group_start == -1)) अणु
			WARN_ON_ONCE(1);
			वापस -ENODATA;
		पूर्ण

		अगर (i_group_start == cpu_group_start)
			cpumask_set_cpu(i, *mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool shared_caches;

#अगर_घोषित CONFIG_SCHED_SMT
/* cpumask of CPUs with asymmetric SMT dependency */
अटल पूर्णांक घातerpc_smt_flags(व्योम)
अणु
	पूर्णांक flags = SD_SHARE_CPUCAPACITY | SD_SHARE_PKG_RESOURCES;

	अगर (cpu_has_feature(CPU_FTR_ASYM_SMT)) अणु
		prपूर्णांकk_once(KERN_INFO "Enabling Asymmetric SMT scheduling\n");
		flags |= SD_ASYM_PACKING;
	पूर्ण
	वापस flags;
पूर्ण
#पूर्ण_अगर

/*
 * P9 has a slightly odd architecture where pairs of cores share an L2 cache.
 * This topology makes it *much* cheaper to migrate tasks between adjacent cores
 * since the migrated task reमुख्यs cache hot. We want to take advantage of this
 * at the scheduler level so an extra topology level is required.
 */
अटल पूर्णांक घातerpc_shared_cache_flags(व्योम)
अणु
	वापस SD_SHARE_PKG_RESOURCES;
पूर्ण

/*
 * We can't just pass cpu_l2_cache_mask() directly because
 * वापसs a non-स्थिर poपूर्णांकer and the compiler barfs on that.
 */
अटल स्थिर काष्ठा cpumask *shared_cache_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_l2_cache_map, cpu);
पूर्ण

#अगर_घोषित CONFIG_SCHED_SMT
अटल स्थिर काष्ठा cpumask *smallcore_smt_mask(पूर्णांक cpu)
अणु
	वापस cpu_smallcore_mask(cpu);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_coregroup_map, cpu);
पूर्ण

अटल bool has_coregroup_support(व्योम)
अणु
	वापस coregroup_enabled;
पूर्ण

अटल स्थिर काष्ठा cpumask *cpu_mc_mask(पूर्णांक cpu)
अणु
	वापस cpu_coregroup_mask(cpu);
पूर्ण

अटल काष्ठा sched_करोमुख्य_topology_level घातerpc_topology[] = अणु
#अगर_घोषित CONFIG_SCHED_SMT
	अणु cpu_smt_mask, घातerpc_smt_flags, SD_INIT_NAME(SMT) पूर्ण,
#पूर्ण_अगर
	अणु shared_cache_mask, घातerpc_shared_cache_flags, SD_INIT_NAME(CACHE) पूर्ण,
	अणु cpu_mc_mask, SD_INIT_NAME(MC) पूर्ण,
	अणु cpu_cpu_mask, SD_INIT_NAME(DIE) पूर्ण,
	अणु शून्य, पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_big_cores(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक err = init_thपढ़ो_group_cache_map(cpu, THREAD_GROUP_SHARE_L1);

		अगर (err)
			वापस err;

		zalloc_cpumask_var_node(&per_cpu(cpu_smallcore_map, cpu),
					GFP_KERNEL,
					cpu_to_node(cpu));
	पूर्ण

	has_big_cores = true;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक err = init_thपढ़ो_group_cache_map(cpu, THREAD_GROUP_SHARE_L2);

		अगर (err)
			वापस err;
	पूर्ण

	thपढ़ो_group_shares_l2 = true;
	pr_debug("L2 cache only shared by the threads in the small core\n");
	वापस 0;
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक cpu;

	DBG("smp_prepare_cpus\n");

	/* 
	 * setup_cpu may need to be called on the boot cpu. We havent
	 * spun any cpus up but lets be paranoid.
	 */
	BUG_ON(boot_cpuid != smp_processor_id());

	/* Fixup boot cpu */
	smp_store_cpu_info(boot_cpuid);
	cpu_callin_map[boot_cpuid] = 1;

	क्रम_each_possible_cpu(cpu) अणु
		zalloc_cpumask_var_node(&per_cpu(cpu_sibling_map, cpu),
					GFP_KERNEL, cpu_to_node(cpu));
		zalloc_cpumask_var_node(&per_cpu(cpu_l2_cache_map, cpu),
					GFP_KERNEL, cpu_to_node(cpu));
		zalloc_cpumask_var_node(&per_cpu(cpu_core_map, cpu),
					GFP_KERNEL, cpu_to_node(cpu));
		अगर (has_coregroup_support())
			zalloc_cpumask_var_node(&per_cpu(cpu_coregroup_map, cpu),
						GFP_KERNEL, cpu_to_node(cpu));

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
		/*
		 * numa_node_id() works after this.
		 */
		अगर (cpu_present(cpu)) अणु
			set_cpu_numa_node(cpu, numa_cpu_lookup_table[cpu]);
			set_cpu_numa_mem(cpu,
				local_memory_node(numa_cpu_lookup_table[cpu]));
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Init the cpumasks so the boot CPU is related to itself */
	cpumask_set_cpu(boot_cpuid, cpu_sibling_mask(boot_cpuid));
	cpumask_set_cpu(boot_cpuid, cpu_l2_cache_mask(boot_cpuid));
	cpumask_set_cpu(boot_cpuid, cpu_core_mask(boot_cpuid));

	अगर (has_coregroup_support())
		cpumask_set_cpu(boot_cpuid, cpu_coregroup_mask(boot_cpuid));

	init_big_cores();
	अगर (has_big_cores) अणु
		cpumask_set_cpu(boot_cpuid,
				cpu_smallcore_mask(boot_cpuid));
	पूर्ण

	अगर (cpu_to_chip_id(boot_cpuid) != -1) अणु
		पूर्णांक idx = num_possible_cpus() / thपढ़ोs_per_core;

		/*
		 * All thपढ़ोs of a core will all beदीर्घ to the same core,
		 * chip_id_lookup_table will have one entry per core.
		 * Assumption: अगर boot_cpuid करोesn't have a chip-id, then no
		 * other CPUs, will also not have chip-id.
		 */
		chip_id_lookup_table = kसुस्मृति(idx, माप(पूर्णांक), GFP_KERNEL);
		अगर (chip_id_lookup_table)
			स_रखो(chip_id_lookup_table, -1, माप(पूर्णांक) * idx);
	पूर्ण

	अगर (smp_ops && smp_ops->probe)
		smp_ops->probe();
पूर्ण

व्योम smp_prepare_boot_cpu(व्योम)
अणु
	BUG_ON(smp_processor_id() != boot_cpuid);
#अगर_घोषित CONFIG_PPC64
	paca_ptrs[boot_cpuid]->__current = current;
#पूर्ण_अगर
	set_numa_node(numa_cpu_lookup_table[boot_cpuid]);
	current_set[boot_cpuid] = current;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

पूर्णांक generic_cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (cpu == boot_cpuid)
		वापस -EBUSY;

	set_cpu_online(cpu, false);
#अगर_घोषित CONFIG_PPC64
	vdso_data->processorCount--;
#पूर्ण_अगर
	/* Update affinity of all IRQs previously aimed at this CPU */
	irq_migrate_all_off_this_cpu();

	/*
	 * Depending on the details of the पूर्णांकerrupt controller, it's possible
	 * that one of the पूर्णांकerrupts we just migrated away from this CPU is
	 * actually alपढ़ोy pending on this CPU. If we leave it in that state
	 * the पूर्णांकerrupt will never be EOI'ed, and will never fire again. So
	 * temporarily enable पूर्णांकerrupts here, to allow any pending पूर्णांकerrupt to
	 * be received (and EOI'ed), beक्रमe we take this CPU offline.
	 */
	local_irq_enable();
	mdelay(1);
	local_irq_disable();

	वापस 0;
पूर्ण

व्योम generic_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		smp_rmb();
		अगर (is_cpu_dead(cpu))
			वापस;
		msleep(100);
	पूर्ण
	prपूर्णांकk(KERN_ERR "CPU%d didn't die...\n", cpu);
पूर्ण

व्योम generic_set_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	per_cpu(cpu_state, cpu) = CPU_DEAD;
पूर्ण

/*
 * The cpu_state should be set to CPU_UP_PREPARE in kick_cpu(), otherwise
 * the cpu_state is always CPU_DEAD after calling generic_set_cpu_dead(),
 * which makes the delay in generic_cpu_die() not happen.
 */
व्योम generic_set_cpu_up(अचिन्हित पूर्णांक cpu)
अणु
	per_cpu(cpu_state, cpu) = CPU_UP_PREPARE;
पूर्ण

पूर्णांक generic_check_cpu_restart(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_state, cpu) == CPU_UP_PREPARE;
पूर्ण

पूर्णांक is_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_state, cpu) == CPU_DEAD;
पूर्ण

अटल bool secondaries_inhibited(व्योम)
अणु
	वापस kvm_hv_mode_active();
पूर्ण

#अन्यथा /* HOTPLUG_CPU */

#घोषणा secondaries_inhibited()		0

#पूर्ण_अगर

अटल व्योम cpu_idle_thपढ़ो_init(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
#अगर_घोषित CONFIG_PPC64
	paca_ptrs[cpu]->__current = idle;
	paca_ptrs[cpu]->kstack = (अचिन्हित दीर्घ)task_stack_page(idle) +
				 THREAD_SIZE - STACK_FRAME_OVERHEAD;
#पूर्ण_अगर
	idle->cpu = cpu;
	secondary_current = current_set[cpu] = idle;
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक rc, c;

	/*
	 * Don't allow secondary thपढ़ोs to come online अगर inhibited
	 */
	अगर (thपढ़ोs_per_core > 1 && secondaries_inhibited() &&
	    cpu_thपढ़ो_in_subcore(cpu))
		वापस -EBUSY;

	अगर (smp_ops == शून्य ||
	    (smp_ops->cpu_bootable && !smp_ops->cpu_bootable(cpu)))
		वापस -EINVAL;

	cpu_idle_thपढ़ो_init(cpu, tidle);

	/*
	 * The platक्रमm might need to allocate resources prior to bringing
	 * up the CPU
	 */
	अगर (smp_ops->prepare_cpu) अणु
		rc = smp_ops->prepare_cpu(cpu);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Make sure callin-map entry is 0 (can be leftover a CPU
	 * hotplug
	 */
	cpu_callin_map[cpu] = 0;

	/* The inक्रमmation क्रम processor bringup must
	 * be written out to मुख्य store beक्रमe we release
	 * the processor.
	 */
	smp_mb();

	/* wake up cpus */
	DBG("smp: kicking cpu %d\n", cpu);
	rc = smp_ops->kick_cpu(cpu);
	अगर (rc) अणु
		pr_err("smp: failed starting cpu %d (rc %d)\n", cpu, rc);
		वापस rc;
	पूर्ण

	/*
	 * रुको to see अगर the cpu made a callin (is actually up).
	 * use this value that I found through experimentation.
	 * -- Cort
	 */
	अगर (प्रणाली_state < SYSTEM_RUNNING)
		क्रम (c = 50000; c && !cpu_callin_map[cpu]; c--)
			udelay(100);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अन्यथा
		/*
		 * CPUs can take much दीर्घer to come up in the
		 * hotplug हाल.  Wait five seconds.
		 */
		क्रम (c = 5000; c && !cpu_callin_map[cpu]; c--)
			msleep(1);
#पूर्ण_अगर

	अगर (!cpu_callin_map[cpu]) अणु
		prपूर्णांकk(KERN_ERR "Processor %u is stuck.\n", cpu);
		वापस -ENOENT;
	पूर्ण

	DBG("Processor %u found.\n", cpu);

	अगर (smp_ops->give_समयbase)
		smp_ops->give_समयbase();

	/* Wait until cpu माला_दो itself in the online & active maps */
	spin_until_cond(cpu_online(cpu));

	वापस 0;
पूर्ण

/* Return the value of the reg property corresponding to the given
 * logical cpu.
 */
पूर्णांक cpu_to_core_id(पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *reg;
	पूर्णांक id = -1;

	np = of_get_cpu_node(cpu, शून्य);
	अगर (!np)
		जाओ out;

	reg = of_get_property(np, "reg", शून्य);
	अगर (!reg)
		जाओ out;

	id = be32_to_cpup(reg);
out:
	of_node_put(np);
	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_to_core_id);

/* Helper routines क्रम cpu to core mapping */
पूर्णांक cpu_core_index_of_thपढ़ो(पूर्णांक cpu)
अणु
	वापस cpu >> thपढ़ोs_shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_core_index_of_thपढ़ो);

पूर्णांक cpu_first_thपढ़ो_of_core(पूर्णांक core)
अणु
	वापस core << thपढ़ोs_shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_first_thपढ़ो_of_core);

/* Must be called when no change can occur to cpu_present_mask,
 * i.e. during cpu online or offline.
 */
अटल काष्ठा device_node *cpu_to_l2cache(पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	काष्ठा device_node *cache;

	अगर (!cpu_present(cpu))
		वापस शून्य;

	np = of_get_cpu_node(cpu, शून्य);
	अगर (np == शून्य)
		वापस शून्य;

	cache = of_find_next_cache_node(np);

	of_node_put(np);

	वापस cache;
पूर्ण

अटल bool update_mask_by_l2(पूर्णांक cpu, cpumask_var_t *mask)
अणु
	काष्ठा cpumask *(*submask_fn)(पूर्णांक) = cpu_sibling_mask;
	काष्ठा device_node *l2_cache, *np;
	पूर्णांक i;

	अगर (has_big_cores)
		submask_fn = cpu_smallcore_mask;

	/*
	 * If the thपढ़ोs in a thपढ़ो-group share L2 cache, then the
	 * L2-mask can be obtained from thपढ़ो_group_l2_cache_map.
	 */
	अगर (thपढ़ो_group_shares_l2) अणु
		cpumask_set_cpu(cpu, cpu_l2_cache_mask(cpu));

		क्रम_each_cpu(i, per_cpu(thपढ़ो_group_l2_cache_map, cpu)) अणु
			अगर (cpu_online(i))
				set_cpus_related(i, cpu, cpu_l2_cache_mask);
		पूर्ण

		/* Verअगरy that L1-cache siblings are a subset of L2 cache-siblings */
		अगर (!cpumask_equal(submask_fn(cpu), cpu_l2_cache_mask(cpu)) &&
		    !cpumask_subset(submask_fn(cpu), cpu_l2_cache_mask(cpu))) अणु
			pr_warn_once("CPU %d : Inconsistent L1 and L2 cache siblings\n",
				     cpu);
		पूर्ण

		वापस true;
	पूर्ण

	l2_cache = cpu_to_l2cache(cpu);
	अगर (!l2_cache || !*mask) अणु
		/* Assume only core siblings share cache with this CPU */
		क्रम_each_cpu(i, submask_fn(cpu))
			set_cpus_related(cpu, i, cpu_l2_cache_mask);

		वापस false;
	पूर्ण

	cpumask_and(*mask, cpu_online_mask, cpu_cpu_mask(cpu));

	/* Update l2-cache mask with all the CPUs that are part of submask */
	or_cpumasks_related(cpu, cpu, submask_fn, cpu_l2_cache_mask);

	/* Skip all CPUs alपढ़ोy part of current CPU l2-cache mask */
	cpumask_andnot(*mask, *mask, cpu_l2_cache_mask(cpu));

	क्रम_each_cpu(i, *mask) अणु
		/*
		 * when updating the marks the current CPU has not been marked
		 * online, but we need to update the cache masks
		 */
		np = cpu_to_l2cache(i);

		/* Skip all CPUs alपढ़ोy part of current CPU l2-cache */
		अगर (np == l2_cache) अणु
			or_cpumasks_related(cpu, i, submask_fn, cpu_l2_cache_mask);
			cpumask_andnot(*mask, *mask, submask_fn(i));
		पूर्ण अन्यथा अणु
			cpumask_andnot(*mask, *mask, cpu_l2_cache_mask(i));
		पूर्ण

		of_node_put(np);
	पूर्ण
	of_node_put(l2_cache);

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम हटाओ_cpu_from_masks(पूर्णांक cpu)
अणु
	काष्ठा cpumask *(*mask_fn)(पूर्णांक) = cpu_sibling_mask;
	पूर्णांक i;

	अगर (shared_caches)
		mask_fn = cpu_l2_cache_mask;

	क्रम_each_cpu(i, mask_fn(cpu)) अणु
		set_cpus_unrelated(cpu, i, cpu_l2_cache_mask);
		set_cpus_unrelated(cpu, i, cpu_sibling_mask);
		अगर (has_big_cores)
			set_cpus_unrelated(cpu, i, cpu_smallcore_mask);
	पूर्ण

	क्रम_each_cpu(i, cpu_core_mask(cpu))
		set_cpus_unrelated(cpu, i, cpu_core_mask);

	अगर (has_coregroup_support()) अणु
		क्रम_each_cpu(i, cpu_coregroup_mask(cpu))
			set_cpus_unrelated(cpu, i, cpu_coregroup_mask);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम add_cpu_to_smallcore_masks(पूर्णांक cpu)
अणु
	पूर्णांक i;

	अगर (!has_big_cores)
		वापस;

	cpumask_set_cpu(cpu, cpu_smallcore_mask(cpu));

	क्रम_each_cpu(i, per_cpu(thपढ़ो_group_l1_cache_map, cpu)) अणु
		अगर (cpu_online(i))
			set_cpus_related(i, cpu, cpu_smallcore_mask);
	पूर्ण
पूर्ण

अटल व्योम update_coregroup_mask(पूर्णांक cpu, cpumask_var_t *mask)
अणु
	काष्ठा cpumask *(*submask_fn)(पूर्णांक) = cpu_sibling_mask;
	पूर्णांक coregroup_id = cpu_to_coregroup_id(cpu);
	पूर्णांक i;

	अगर (shared_caches)
		submask_fn = cpu_l2_cache_mask;

	अगर (!*mask) अणु
		/* Assume only siblings are part of this CPU's coregroup */
		क्रम_each_cpu(i, submask_fn(cpu))
			set_cpus_related(cpu, i, cpu_coregroup_mask);

		वापस;
	पूर्ण

	cpumask_and(*mask, cpu_online_mask, cpu_cpu_mask(cpu));

	/* Update coregroup mask with all the CPUs that are part of submask */
	or_cpumasks_related(cpu, cpu, submask_fn, cpu_coregroup_mask);

	/* Skip all CPUs alपढ़ोy part of coregroup mask */
	cpumask_andnot(*mask, *mask, cpu_coregroup_mask(cpu));

	क्रम_each_cpu(i, *mask) अणु
		/* Skip all CPUs not part of this coregroup */
		अगर (coregroup_id == cpu_to_coregroup_id(i)) अणु
			or_cpumasks_related(cpu, i, submask_fn, cpu_coregroup_mask);
			cpumask_andnot(*mask, *mask, submask_fn(i));
		पूर्ण अन्यथा अणु
			cpumask_andnot(*mask, *mask, cpu_coregroup_mask(i));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम add_cpu_to_masks(पूर्णांक cpu)
अणु
	काष्ठा cpumask *(*submask_fn)(पूर्णांक) = cpu_sibling_mask;
	पूर्णांक first_thपढ़ो = cpu_first_thपढ़ो_sibling(cpu);
	cpumask_var_t mask;
	पूर्णांक chip_id = -1;
	bool ret;
	पूर्णांक i;

	/*
	 * This CPU will not be in the online mask yet so we need to manually
	 * add it to it's own thपढ़ो sibling mask.
	 */
	cpumask_set_cpu(cpu, cpu_sibling_mask(cpu));

	क्रम (i = first_thपढ़ो; i < first_thपढ़ो + thपढ़ोs_per_core; i++)
		अगर (cpu_online(i))
			set_cpus_related(i, cpu, cpu_sibling_mask);

	add_cpu_to_smallcore_masks(cpu);

	/* In CPU-hotplug path, hence use GFP_ATOMIC */
	ret = alloc_cpumask_var_node(&mask, GFP_ATOMIC, cpu_to_node(cpu));
	update_mask_by_l2(cpu, &mask);

	अगर (has_coregroup_support())
		update_coregroup_mask(cpu, &mask);

	अगर (chip_id_lookup_table && ret)
		chip_id = cpu_to_chip_id(cpu);

	अगर (chip_id == -1) अणु
		cpumask_copy(per_cpu(cpu_core_map, cpu), cpu_cpu_mask(cpu));
		जाओ out;
	पूर्ण

	अगर (shared_caches)
		submask_fn = cpu_l2_cache_mask;

	/* Update core_mask with all the CPUs that are part of submask */
	or_cpumasks_related(cpu, cpu, submask_fn, cpu_core_mask);

	/* Skip all CPUs alपढ़ोy part of current CPU core mask */
	cpumask_andnot(mask, cpu_online_mask, cpu_core_mask(cpu));

	क्रम_each_cpu(i, mask) अणु
		अगर (chip_id == cpu_to_chip_id(i)) अणु
			or_cpumasks_related(cpu, i, submask_fn, cpu_core_mask);
			cpumask_andnot(mask, mask, submask_fn(i));
		पूर्ण अन्यथा अणु
			cpumask_andnot(mask, mask, cpu_core_mask(i));
		पूर्ण
	पूर्ण

out:
	मुक्त_cpumask_var(mask);
पूर्ण

/* Activate a secondary processor. */
व्योम start_secondary(व्योम *unused)
अणु
	अचिन्हित पूर्णांक cpu = raw_smp_processor_id();

	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	smp_store_cpu_info(cpu);
	set_dec(tb_ticks_per_jअगरfy);
	rcu_cpu_starting(cpu);
	preempt_disable();
	cpu_callin_map[cpu] = 1;

	अगर (smp_ops->setup_cpu)
		smp_ops->setup_cpu(cpu);
	अगर (smp_ops->take_समयbase)
		smp_ops->take_समयbase();

	secondary_cpu_समय_init();

#अगर_घोषित CONFIG_PPC64
	अगर (प्रणाली_state == SYSTEM_RUNNING)
		vdso_data->processorCount++;

	vdso_अ_लोpu_init();
#पूर्ण_अगर
	set_numa_node(numa_cpu_lookup_table[cpu]);
	set_numa_mem(local_memory_node(numa_cpu_lookup_table[cpu]));

	/* Update topology CPU masks */
	add_cpu_to_masks(cpu);

	/*
	 * Check क्रम any shared caches. Note that this must be करोne on a
	 * per-core basis because one core in the pair might be disabled.
	 */
	अगर (!shared_caches) अणु
		काष्ठा cpumask *(*sibling_mask)(पूर्णांक) = cpu_sibling_mask;
		काष्ठा cpumask *mask = cpu_l2_cache_mask(cpu);

		अगर (has_big_cores)
			sibling_mask = cpu_smallcore_mask;

		अगर (cpumask_weight(mask) > cpumask_weight(sibling_mask(cpu)))
			shared_caches = true;
	पूर्ण

	smp_wmb();
	notअगरy_cpu_starting(cpu);
	set_cpu_online(cpu, true);

	boot_init_stack_canary();

	local_irq_enable();

	/* We can enable ftrace क्रम secondary cpus now */
	this_cpu_enable_ftrace();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);

	BUG();
पूर्ण

पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस 0;
पूर्ण

अटल व्योम fixup_topology(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_SCHED_SMT
	अगर (has_big_cores) अणु
		pr_info("Big cores detected but using small core scheduling\n");
		घातerpc_topology[smt_idx].mask = smallcore_smt_mask;
	पूर्ण
#पूर्ण_अगर

	अगर (!has_coregroup_support())
		घातerpc_topology[mc_idx].mask = घातerpc_topology[cache_idx].mask;

	/*
	 * Try to consolidate topology levels here instead of
	 * allowing scheduler to degenerate.
	 * - Dont consolidate अगर masks are dअगरferent.
	 * - Dont consolidate अगर sd_flags exists and are dअगरferent.
	 */
	क्रम (i = 1; i <= die_idx; i++) अणु
		अगर (घातerpc_topology[i].mask != घातerpc_topology[i - 1].mask)
			जारी;

		अगर (घातerpc_topology[i].sd_flags && घातerpc_topology[i - 1].sd_flags &&
				घातerpc_topology[i].sd_flags != घातerpc_topology[i - 1].sd_flags)
			जारी;

		अगर (!घातerpc_topology[i - 1].sd_flags)
			घातerpc_topology[i - 1].sd_flags = घातerpc_topology[i].sd_flags;

		घातerpc_topology[i].mask = घातerpc_topology[i + 1].mask;
		घातerpc_topology[i].sd_flags = घातerpc_topology[i + 1].sd_flags;
#अगर_घोषित CONFIG_SCHED_DEBUG
		घातerpc_topology[i].name = घातerpc_topology[i + 1].name;
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	/*
	 * We are running pinned to the boot CPU, see rest_init().
	 */
	अगर (smp_ops && smp_ops->setup_cpu)
		smp_ops->setup_cpu(boot_cpuid);

	अगर (smp_ops && smp_ops->bringup_करोne)
		smp_ops->bringup_करोne();

	dump_numa_cpu_topology();

	fixup_topology();
	set_sched_topology(घातerpc_topology);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक __cpu_disable(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक err;

	अगर (!smp_ops->cpu_disable)
		वापस -ENOSYS;

	this_cpu_disable_ftrace();

	err = smp_ops->cpu_disable();
	अगर (err)
		वापस err;

	/* Update sibling maps */
	हटाओ_cpu_from_masks(cpu);

	वापस 0;
पूर्ण

व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अगर (smp_ops->cpu_die)
		smp_ops->cpu_die(cpu);
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	sched_preempt_enable_no_resched();

	/*
	 * Disable on the करोwn path. This will be re-enabled by
	 * start_secondary() via start_secondary_resume() below
	 */
	this_cpu_disable_ftrace();

	अगर (smp_ops->cpu_offline_self)
		smp_ops->cpu_offline_self();

	/* If we वापस, we re-enter start_secondary */
	start_secondary_resume();
पूर्ण

#पूर्ण_अगर
