<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * RajeshwarR: Dec 11, 2007
 *   -- Added support क्रम Inter Processor Interrupts
 *
 * Vineetg: Nov 1st, 2007
 *    -- Initial Write (Borrowed heavily from ARM)
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/profile.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/reboot.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/export.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach_desc.h>

#अगर_अघोषित CONFIG_ARC_HAS_LLSC
arch_spinlock_t smp_atomic_ops_lock = __ARCH_SPIN_LOCK_UNLOCKED;
arch_spinlock_t smp_bitops_lock = __ARCH_SPIN_LOCK_UNLOCKED;

EXPORT_SYMBOL_GPL(smp_atomic_ops_lock);
EXPORT_SYMBOL_GPL(smp_bitops_lock);
#पूर्ण_अगर

काष्ठा plat_smp_ops  __weak plat_smp_ops;

/* XXX: per cpu ? Only needed once in early seconday boot */
काष्ठा task_काष्ठा *secondary_idle_tsk;

/* Called from start_kernel */
व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
पूर्ण

अटल पूर्णांक __init arc_get_cpu_map(स्थिर अक्षर *name, काष्ठा cpumask *cpumask)
अणु
	अचिन्हित दीर्घ dt_root = of_get_flat_dt_root();
	स्थिर अक्षर *buf;

	buf = of_get_flat_dt_prop(dt_root, name, शून्य);
	अगर (!buf)
		वापस -EINVAL;

	अगर (cpulist_parse(buf, cpumask))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Read from DeviceTree and setup cpu possible mask. If there is no
 * "possible-cpus" property in DeviceTree pretend all [0..NR_CPUS-1] exist.
 */
अटल व्योम __init arc_init_cpu_possible(व्योम)
अणु
	काष्ठा cpumask cpumask;

	अगर (arc_get_cpu_map("possible-cpus", &cpumask)) अणु
		pr_warn("Failed to get possible-cpus from dtb, pretending all %u cpus exist\n",
			NR_CPUS);

		cpumask_setall(&cpumask);
	पूर्ण

	अगर (!cpumask_test_cpu(0, &cpumask))
		panic("Master cpu (cpu[0]) is missed in cpu possible mask!");

	init_cpu_possible(&cpumask);
पूर्ण

/*
 * Called from setup_arch() beक्रमe calling setup_processor()
 *
 * - Initialise the CPU possible map early - this describes the CPUs
 *   which may be present or become present in the प्रणाली.
 * - Call early smp init hook. This can initialize a specअगरic multi-core
 *   IP which is say common to several platक्रमms (hence not part of
 *   platक्रमm specअगरic पूर्णांक_early() hook)
 */
व्योम __init smp_init_cpus(व्योम)
अणु
	arc_init_cpu_possible();

	अगर (plat_smp_ops.init_early_smp)
		plat_smp_ops.init_early_smp();
पूर्ण

/* called from init ( ) =>  process 1 */
व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/*
	 * अगर platक्रमm didn't set the present map alपढ़ोy, करो it now
	 * boot cpu is set to present alपढ़ोy by init/मुख्य.c
	 */
	अगर (num_present_cpus() <= 1)
		init_cpu_present(cpu_possible_mask);
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु

पूर्ण

/*
 * Default smp boot helper क्रम Run-on-reset हाल where all cores start off
 * together. Non-masters need to रुको क्रम Master to start running.
 * This is implemented using a flag in memory, which Non-masters spin-रुको on.
 * Master sets it to cpu-id of core to "ungate" it.
 */
अटल अस्थिर पूर्णांक wake_flag;

#अगर_घोषित CONFIG_ISA_ARCOMPACT

#घोषणा __boot_पढ़ो(f)		f
#घोषणा __boot_ग_लिखो(f, v)	f = v

#अन्यथा

#घोषणा __boot_पढ़ो(f)		arc_पढ़ो_uncached_32(&f)
#घोषणा __boot_ग_लिखो(f, v)	arc_ग_लिखो_uncached_32(&f, v)

#पूर्ण_अगर

अटल व्योम arc_शेष_smp_cpu_kick(पूर्णांक cpu, अचिन्हित दीर्घ pc)
अणु
	BUG_ON(cpu == 0);

	__boot_ग_लिखो(wake_flag, cpu);
पूर्ण

व्योम arc_platक्रमm_smp_रुको_to_boot(पूर्णांक cpu)
अणु
	/* क्रम halt-on-reset, we've रुकोed alपढ़ोy */
	अगर (IS_ENABLED(CONFIG_ARC_SMP_HALT_ON_RESET))
		वापस;

	जबतक (__boot_पढ़ो(wake_flag) != cpu)
		;

	__boot_ग_लिखो(wake_flag, 0);
पूर्ण

स्थिर अक्षर *arc_platक्रमm_smp_cpuinfo(व्योम)
अणु
	वापस plat_smp_ops.info ? : "";
पूर्ण

/*
 * The very first "C" code executed by secondary
 * Called from यंत्र stub in head.S
 * "current"/R25 alपढ़ोy setup by low level boot code
 */
व्योम start_kernel_secondary(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* MMU, Caches, Vector Table, Interrupts etc */
	setup_processor();

	mmget(mm);
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	/* Some SMP H/w setup - क्रम each cpu */
	अगर (plat_smp_ops.init_per_cpu)
		plat_smp_ops.init_per_cpu(cpu);

	अगर (machine_desc->init_per_cpu)
		machine_desc->init_per_cpu(cpu);

	notअगरy_cpu_starting(cpu);
	set_cpu_online(cpu, true);

	pr_info("## CPU%u LIVE ##: Executing Code...\n", cpu);

	local_irq_enable();
	preempt_disable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

/*
 * Called from kernel_init( ) -> smp_init( ) - क्रम each CPU
 *
 * At this poपूर्णांक, Secondary Processor  is "HALT"ed:
 *  -It booted, but was halted in head.S
 *  -It was configured to halt-on-reset
 *  So need to wake it up.
 *
 * Essential requirements being where to run from (PC) and stack (SP)
*/
पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ रुको_till;

	secondary_idle_tsk = idle;

	pr_info("Idle Task [%d] %p", cpu, idle);
	pr_info("Trying to bring up CPU%u ...\n", cpu);

	अगर (plat_smp_ops.cpu_kick)
		plat_smp_ops.cpu_kick(cpu,
				(अचिन्हित दीर्घ)first_lines_of_secondary);
	अन्यथा
		arc_शेष_smp_cpu_kick(cpu, (अचिन्हित दीर्घ)शून्य);

	/* रुको क्रम 1 sec after kicking the secondary */
	रुको_till = jअगरfies + HZ;
	जबतक (समय_beक्रमe(jअगरfies, रुको_till)) अणु
		अगर (cpu_online(cpu))
			अवरोध;
	पूर्ण

	अगर (!cpu_online(cpu)) अणु
		pr_info("Timeout: CPU%u FAILED to come up !!!\n", cpu);
		वापस -1;
	पूर्ण

	secondary_idle_tsk = शून्य;

	वापस 0;
पूर्ण

/*
 * not supported here
 */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

/*****************************************************************************/
/*              Inter Processor Interrupt Handling                           */
/*****************************************************************************/

क्रमागत ipi_msg_type अणु
	IPI_EMPTY = 0,
	IPI_RESCHEDULE = 1,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
पूर्ण;

/*
 * In arches with IRQ क्रम each msg type (above), receiver can use IRQ-id  to
 * figure out what msg was sent. For those which करोn't (ARC has dedicated IPI
 * IRQ), the msg-type needs to be conveyed via per-cpu data
 */

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, ipi_data);

अटल व्योम ipi_send_msg_one(पूर्णांक cpu, क्रमागत ipi_msg_type msg)
अणु
	अचिन्हित दीर्घ __percpu *ipi_data_ptr = per_cpu_ptr(&ipi_data, cpu);
	अचिन्हित दीर्घ old, new;
	अचिन्हित दीर्घ flags;

	pr_debug("%d Sending msg [%d] to %d\n", smp_processor_id(), msg, cpu);

	local_irq_save(flags);

	/*
	 * Atomically ग_लिखो new msg bit (in हाल others are writing too),
	 * and पढ़ो back old value
	 */
	करो अणु
		new = old = READ_ONCE(*ipi_data_ptr);
		new |= 1U << msg;
	पूर्ण जबतक (cmpxchg(ipi_data_ptr, old, new) != old);

	/*
	 * Call the platक्रमm specअगरic IPI kick function, but aव्योम अगर possible:
	 * Only करो so अगर there's no pending msg from other concurrent sender(s).
	 * Otherwise, recevier will see this msg as well when it takes the
	 * IPI corresponding to that msg. This is true, even अगर it is alपढ़ोy in
	 * IPI handler, because !@old means it has not yet dequeued the msg(s)
	 * so @new msg can be a मुक्त-loader
	 */
	अगर (plat_smp_ops.ipi_send && !old)
		plat_smp_ops.ipi_send(cpu);

	local_irq_restore(flags);
पूर्ण

अटल व्योम ipi_send_msg(स्थिर काष्ठा cpumask *callmap, क्रमागत ipi_msg_type msg)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, callmap)
		ipi_send_msg_one(cpu, msg);
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	ipi_send_msg_one(cpu, IPI_RESCHEDULE);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	काष्ठा cpumask tarमाला_लो;
	cpumask_copy(&tarमाला_लो, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &tarमाला_लो);
	ipi_send_msg(&tarमाला_लो, IPI_CPU_STOP);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	ipi_send_msg_one(cpu, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	ipi_send_msg(mask, IPI_CALL_FUNC);
पूर्ण

/*
 * ipi_cpu_stop - handle IPI from smp_send_stop()
 */
अटल व्योम ipi_cpu_stop(व्योम)
अणु
	machine_halt();
पूर्ण

अटल अंतरभूत पूर्णांक __करो_IPI(अचिन्हित दीर्घ msg)
अणु
	पूर्णांक rc = 0;

	चयन (msg) अणु
	हाल IPI_RESCHEDULE:
		scheduler_ipi();
		अवरोध;

	हाल IPI_CALL_FUNC:
		generic_smp_call_function_पूर्णांकerrupt();
		अवरोध;

	हाल IPI_CPU_STOP:
		ipi_cpu_stop();
		अवरोध;

	शेष:
		rc = 1;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * arch-common ISR to handle क्रम पूर्णांकer-processor पूर्णांकerrupts
 * Has hooks क्रम platक्रमm specअगरic IPI
 */
irqवापस_t करो_IPI(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ pending;
	अचिन्हित दीर्घ __maybe_unused copy;

	pr_debug("IPI [%ld] received on cpu %d\n",
		 *this_cpu_ptr(&ipi_data), smp_processor_id());

	अगर (plat_smp_ops.ipi_clear)
		plat_smp_ops.ipi_clear(irq);

	/*
	 * "dequeue" the msg corresponding to this IPI (and possibly other
	 * piggybacked msg from elided IPIs: see ipi_send_msg_one() above)
	 */
	copy = pending = xchg(this_cpu_ptr(&ipi_data), 0);

	करो अणु
		अचिन्हित दीर्घ msg = __ffs(pending);
		पूर्णांक rc;

		rc = __करो_IPI(msg);
		अगर (rc)
			pr_info("IPI with bogus msg %ld in %ld\n", msg, copy);
		pending &= ~(1U << msg);
	पूर्ण जबतक (pending);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * API called by platक्रमm code to hookup arch-common ISR to their IPI IRQ
 *
 * Note: If IPI is provided by platक्रमm (vs. say ARC MCIP), their पूर्णांकc setup/map
 * function needs to call call irq_set_percpu_devid() क्रम IPI IRQ, otherwise
 * request_percpu_irq() below will fail
 */
अटल DEFINE_PER_CPU(पूर्णांक, ipi_dev);

पूर्णांक smp_ipi_irq_setup(पूर्णांक cpu, irq_hw_number_t hwirq)
अणु
	पूर्णांक *dev = per_cpu_ptr(&ipi_dev, cpu);
	अचिन्हित पूर्णांक virq = irq_find_mapping(शून्य, hwirq);

	अगर (!virq)
		panic("Cannot find virq for root domain and hwirq=%lu", hwirq);

	/* Boot cpu calls request, all call enable */
	अगर (!cpu) अणु
		पूर्णांक rc;

		rc = request_percpu_irq(virq, करो_IPI, "IPI Interrupt", dev);
		अगर (rc)
			panic("Percpu IRQ request failed for %u\n", virq);
	पूर्ण

	enable_percpu_irq(virq, 0);

	वापस 0;
पूर्ण
