<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen SMP support
 *
 * This file implements the Xen versions of smp_ops.  SMP under Xen is
 * very straightक्रमward.  Bringing a CPU up is simply a matter of
 * loading its initial context and setting it running.
 *
 * IPIs are handled through the Xen event mechanism.
 *
 * Because भव CPUs can be scheduled onto any real CPU, there's no
 * useful topology inक्रमmation क्रम the kernel to make use of.  As a
 * result, all CPUs are treated as अगर they're single-core and
 * single-thपढ़ोed.
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/tick.h>
#समावेश <linux/nmi.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/stackprotector.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/io_apic.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/पूर्णांकerface/xenpmu.h>

#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/events.h>

#समावेश <xen/hvc-console.h>
#समावेश "xen-ops.h"
#समावेश "mmu.h"
#समावेश "smp.h"
#समावेश "pmu.h"

cpumask_var_t xen_cpu_initialized_map;

अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_irq_work) = अणु .irq = -1 पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_pmu_irq) = अणु .irq = -1 पूर्ण;

अटल irqवापस_t xen_irq_work_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
व्योम यंत्र_cpu_bringup_and_idle(व्योम);

अटल व्योम cpu_bringup(व्योम)
अणु
	पूर्णांक cpu;

	cr4_init();
	cpu_init();
	touch_softlockup_watchकरोg();
	preempt_disable();

	/* PVH runs in ring 0 and allows us to करो native syscalls. Yay! */
	अगर (!xen_feature(XENFEAT_supervisor_mode_kernel)) अणु
		xen_enable_sysenter();
		xen_enable_syscall();
	पूर्ण
	cpu = smp_processor_id();
	smp_store_cpu_info(cpu);
	cpu_data(cpu).x86_max_cores = 1;
	set_cpu_sibling_map(cpu);

	speculative_store_bypass_ht_init();

	xen_setup_cpu_घड़ीevents();

	notअगरy_cpu_starting(cpu);

	set_cpu_online(cpu, true);

	cpu_set_state_online(cpu);  /* Implies full memory barrier. */

	/* We can take पूर्णांकerrupts now: we're officially "up". */
	local_irq_enable();
पूर्ण

यंत्रlinkage __visible व्योम cpu_bringup_and_idle(व्योम)
अणु
	cpu_bringup();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

व्योम xen_smp_पूर्णांकr_मुक्त_pv(अचिन्हित पूर्णांक cpu)
अणु
	अगर (per_cpu(xen_irq_work, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_irq_work, cpu).irq, शून्य);
		per_cpu(xen_irq_work, cpu).irq = -1;
		kमुक्त(per_cpu(xen_irq_work, cpu).name);
		per_cpu(xen_irq_work, cpu).name = शून्य;
	पूर्ण

	अगर (per_cpu(xen_pmu_irq, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_pmu_irq, cpu).irq, शून्य);
		per_cpu(xen_pmu_irq, cpu).irq = -1;
		kमुक्त(per_cpu(xen_pmu_irq, cpu).name);
		per_cpu(xen_pmu_irq, cpu).name = शून्य;
	पूर्ण
पूर्ण

पूर्णांक xen_smp_पूर्णांकr_init_pv(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;
	अक्षर *callfunc_name, *pmu_name;

	callfunc_name = kaप्र_लिखो(GFP_KERNEL, "irqwork%d", cpu);
	rc = bind_ipi_to_irqhandler(XEN_IRQ_WORK_VECTOR,
				    cpu,
				    xen_irq_work_पूर्णांकerrupt,
				    IRQF_PERCPU|IRQF_NOBALANCING,
				    callfunc_name,
				    शून्य);
	अगर (rc < 0)
		जाओ fail;
	per_cpu(xen_irq_work, cpu).irq = rc;
	per_cpu(xen_irq_work, cpu).name = callfunc_name;

	अगर (is_xen_pmu(cpu)) अणु
		pmu_name = kaप्र_लिखो(GFP_KERNEL, "pmu%d", cpu);
		rc = bind_virq_to_irqhandler(VIRQ_XENPMU, cpu,
					     xen_pmu_irq_handler,
					     IRQF_PERCPU|IRQF_NOBALANCING,
					     pmu_name, शून्य);
		अगर (rc < 0)
			जाओ fail;
		per_cpu(xen_pmu_irq, cpu).irq = rc;
		per_cpu(xen_pmu_irq, cpu).name = pmu_name;
	पूर्ण

	वापस 0;

 fail:
	xen_smp_पूर्णांकr_मुक्त_pv(cpu);
	वापस rc;
पूर्ण

अटल व्योम __init xen_fill_possible_map(व्योम)
अणु
	पूर्णांक i, rc;

	अगर (xen_initial_करोमुख्य())
		वापस;

	क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		rc = HYPERVISOR_vcpu_op(VCPUOP_is_up, i, शून्य);
		अगर (rc >= 0) अणु
			num_processors++;
			set_cpu_possible(i, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init xen_filter_cpu_maps(व्योम)
अणु
	पूर्णांक i, rc;
	अचिन्हित पूर्णांक subtract = 0;

	अगर (!xen_initial_करोमुख्य())
		वापस;

	num_processors = 0;
	disabled_cpus = 0;
	क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		rc = HYPERVISOR_vcpu_op(VCPUOP_is_up, i, शून्य);
		अगर (rc >= 0) अणु
			num_processors++;
			set_cpu_possible(i, true);
		पूर्ण अन्यथा अणु
			set_cpu_possible(i, false);
			set_cpu_present(i, false);
			subtract++;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_HOTPLUG_CPU
	/* This is akin to using 'nr_cpus' on the Linux command line.
	 * Which is OK as when we use 'dom0_max_vcpus=X' we can only
	 * have up to X, जबतक nr_cpu_ids is greater than X. This
	 * normally is not a problem, except when CPU hotplugging
	 * is involved and then there might be more than X CPUs
	 * in the guest - which will not work as there is no
	 * hypercall to expand the max number of VCPUs an alपढ़ोy
	 * running guest has. So cap it up to X. */
	अगर (subtract)
		nr_cpu_ids = nr_cpu_ids - subtract;
#पूर्ण_अगर

पूर्ण

अटल व्योम __init xen_pv_smp_prepare_boot_cpu(व्योम)
अणु
	BUG_ON(smp_processor_id() != 0);
	native_smp_prepare_boot_cpu();

	अगर (!xen_feature(XENFEAT_writable_page_tables))
		/* We've चयनed to the "real" per-cpu gdt, so make
		 * sure the old memory can be recycled. */
		make_lowmem_page_पढ़ोग_लिखो(xen_initial_gdt);

	xen_filter_cpu_maps();
	xen_setup_vcpu_info_placement();

	/*
	 * The alternative logic (which patches the unlock/lock) runs beक्रमe
	 * the smp bootup up code is activated. Hence we need to set this up
	 * the core kernel is being patched. Otherwise we will have only
	 * modules patched but not core code.
	 */
	xen_init_spinlocks();
पूर्ण

अटल व्योम __init xen_pv_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित cpu;
	अचिन्हित पूर्णांक i;

	अगर (skip_ioapic_setup) अणु
		अक्षर *m = (max_cpus == 0) ?
			"The nosmp parameter is incompatible with Xen; " \
			"use Xen dom0_max_vcpus=1 parameter" :
			"The noapic parameter is incompatible with Xen";

		xen_raw_prपूर्णांकk(m);
		panic(m);
	पूर्ण
	xen_init_lock_cpu(0);

	smp_store_boot_cpu_info();
	cpu_data(0).x86_max_cores = 1;

	क्रम_each_possible_cpu(i) अणु
		zalloc_cpumask_var(&per_cpu(cpu_sibling_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_core_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_die_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_llc_shared_map, i), GFP_KERNEL);
	पूर्ण
	set_cpu_sibling_map(0);

	speculative_store_bypass_ht_init();

	xen_pmu_init(0);

	अगर (xen_smp_पूर्णांकr_init(0) || xen_smp_पूर्णांकr_init_pv(0))
		BUG();

	अगर (!alloc_cpumask_var(&xen_cpu_initialized_map, GFP_KERNEL))
		panic("could not allocate xen_cpu_initialized_map\n");

	cpumask_copy(xen_cpu_initialized_map, cpumask_of(0));

	/* Restrict the possible_map according to max_cpus. */
	जबतक ((num_possible_cpus() > 1) && (num_possible_cpus() > max_cpus)) अणु
		क्रम (cpu = nr_cpu_ids - 1; !cpu_possible(cpu); cpu--)
			जारी;
		set_cpu_possible(cpu, false);
	पूर्ण

	क्रम_each_possible_cpu(cpu)
		set_cpu_present(cpu, true);
पूर्ण

अटल पूर्णांक
cpu_initialize_context(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा vcpu_guest_context *ctxt;
	काष्ठा desc_काष्ठा *gdt;
	अचिन्हित दीर्घ gdt_mfn;

	/* used to tell cpu_init() that it can proceed with initialization */
	cpumask_set_cpu(cpu, cpu_callout_mask);
	अगर (cpumask_test_and_set_cpu(cpu, xen_cpu_initialized_map))
		वापस 0;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (ctxt == शून्य)
		वापस -ENOMEM;

	gdt = get_cpu_gdt_rw(cpu);

	स_रखो(&ctxt->fpu_ctxt, 0, माप(ctxt->fpu_ctxt));

	/*
	 * Bring up the CPU in cpu_bringup_and_idle() with the stack
	 * poपूर्णांकing just below where pt_regs would be अगर it were a normal
	 * kernel entry.
	 */
	ctxt->user_regs.eip = (अचिन्हित दीर्घ)यंत्र_cpu_bringup_and_idle;
	ctxt->flags = VGCF_IN_KERNEL;
	ctxt->user_regs.eflags = 0x1000; /* IOPL_RING1 */
	ctxt->user_regs.ds = __USER_DS;
	ctxt->user_regs.es = __USER_DS;
	ctxt->user_regs.ss = __KERNEL_DS;
	ctxt->user_regs.cs = __KERNEL_CS;
	ctxt->user_regs.esp = (अचिन्हित दीर्घ)task_pt_regs(idle);

	xen_copy_trap_info(ctxt->trap_ctxt);

	ctxt->ldt_ents = 0;

	BUG_ON((अचिन्हित दीर्घ)gdt & ~PAGE_MASK);

	gdt_mfn = arbitrary_virt_to_mfn(gdt);
	make_lowmem_page_पढ़ोonly(gdt);
	make_lowmem_page_पढ़ोonly(mfn_to_virt(gdt_mfn));

	ctxt->gdt_frames[0] = gdt_mfn;
	ctxt->gdt_ents      = GDT_ENTRIES;

	/*
	 * Set SS:SP that Xen will use when entering guest kernel mode
	 * from guest user mode.  Subsequent calls to load_sp0() can
	 * change this value.
	 */
	ctxt->kernel_ss = __KERNEL_DS;
	ctxt->kernel_sp = task_top_of_stack(idle);

	ctxt->gs_base_kernel = per_cpu_offset(cpu);
	ctxt->event_callback_eip    =
		(अचिन्हित दीर्घ)xen_यंत्र_exc_xen_hypervisor_callback;
	ctxt->failsafe_callback_eip =
		(अचिन्हित दीर्घ)xen_failsafe_callback;
	per_cpu(xen_cr3, cpu) = __pa(swapper_pg_dir);

	ctxt->ctrlreg[3] = xen_pfn_to_cr3(virt_to_gfn(swapper_pg_dir));
	अगर (HYPERVISOR_vcpu_op(VCPUOP_initialise, xen_vcpu_nr(cpu), ctxt))
		BUG();

	kमुक्त(ctxt);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_pv_cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक rc;

	rc = common_cpu_up(cpu, idle);
	अगर (rc)
		वापस rc;

	xen_setup_runstate_info(cpu);

	/*
	 * PV VCPUs are always successfully taken करोwn (see 'while' loop
	 * in xen_cpu_die()), so -EBUSY is an error.
	 */
	rc = cpu_check_up_prepare(cpu);
	अगर (rc)
		वापस rc;

	/* make sure पूर्णांकerrupts start blocked */
	per_cpu(xen_vcpu, cpu)->evtchn_upcall_mask = 1;

	rc = cpu_initialize_context(cpu, idle);
	अगर (rc)
		वापस rc;

	xen_pmu_init(cpu);

	rc = HYPERVISOR_vcpu_op(VCPUOP_up, xen_vcpu_nr(cpu), शून्य);
	BUG_ON(rc);

	जबतक (cpu_report_state(cpu) != CPU_ONLINE)
		HYPERVISOR_sched_op(SCHEDOP_yield, शून्य);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक xen_pv_cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अगर (cpu == 0)
		वापस -EBUSY;

	cpu_disable_common();

	load_cr3(swapper_pg_dir);
	वापस 0;
पूर्ण

अटल व्योम xen_pv_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	जबतक (HYPERVISOR_vcpu_op(VCPUOP_is_up,
				  xen_vcpu_nr(cpu), शून्य)) अणु
		__set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(HZ/10);
	पूर्ण

	अगर (common_cpu_die(cpu) == 0) अणु
		xen_smp_पूर्णांकr_मुक्त(cpu);
		xen_uninit_lock_cpu(cpu);
		xen_tearकरोwn_समयr(cpu);
		xen_pmu_finish(cpu);
	पूर्ण
पूर्ण

अटल व्योम xen_pv_play_dead(व्योम) /* used only with HOTPLUG_CPU */
अणु
	play_dead_common();
	HYPERVISOR_vcpu_op(VCPUOP_करोwn, xen_vcpu_nr(smp_processor_id()), शून्य);
	cpu_bringup();
	/*
	 * commit 4b0c0f294 (tick: Cleanup NOHZ per cpu data on cpu करोwn)
	 * clears certain data that the cpu_idle loop (which called us
	 * and that we वापस from) expects. The only way to get that
	 * data back is to call:
	 */
	tick_nohz_idle_enter();
	tick_nohz_idle_stop_tick_रक्षित();

	cpuhp_online_idle(CPUHP_AP_ONLINE_IDLE);
पूर्ण

#अन्यथा /* !CONFIG_HOTPLUG_CPU */
अटल पूर्णांक xen_pv_cpu_disable(व्योम)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम xen_pv_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	BUG();
पूर्ण

अटल व्योम xen_pv_play_dead(व्योम)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर
अटल व्योम stop_self(व्योम *v)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* make sure we're not pinning something करोwn */
	load_cr3(swapper_pg_dir);
	/* should set up a minimal gdt */

	set_cpu_online(cpu, false);

	HYPERVISOR_vcpu_op(VCPUOP_करोwn, xen_vcpu_nr(cpu), शून्य);
	BUG();
पूर्ण

अटल व्योम xen_pv_stop_other_cpus(पूर्णांक रुको)
अणु
	smp_call_function(stop_self, शून्य, रुको);
पूर्ण

अटल irqवापस_t xen_irq_work_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	irq_enter();
	irq_work_run();
	inc_irq_stat(apic_irq_work_irqs);
	irq_निकास();

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा smp_ops xen_smp_ops __initस्थिर = अणु
	.smp_prepare_boot_cpu = xen_pv_smp_prepare_boot_cpu,
	.smp_prepare_cpus = xen_pv_smp_prepare_cpus,
	.smp_cpus_करोne = xen_smp_cpus_करोne,

	.cpu_up = xen_pv_cpu_up,
	.cpu_die = xen_pv_cpu_die,
	.cpu_disable = xen_pv_cpu_disable,
	.play_dead = xen_pv_play_dead,

	.stop_other_cpus = xen_pv_stop_other_cpus,
	.smp_send_reschedule = xen_smp_send_reschedule,

	.send_call_func_ipi = xen_smp_send_call_function_ipi,
	.send_call_func_single_ipi = xen_smp_send_call_function_single_ipi,
पूर्ण;

व्योम __init xen_smp_init(व्योम)
अणु
	smp_ops = xen_smp_ops;
	xen_fill_possible_map();
पूर्ण
