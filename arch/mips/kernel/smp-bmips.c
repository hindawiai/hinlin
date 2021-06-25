<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011 by Kevin Cernekee (cernekee@gmail.com)
 *
 * SMP support क्रम BMIPS
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>
#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bmips.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpu-features.h>

अटल पूर्णांक __maybe_unused max_cpus = 1;

/* these may be configured by the platक्रमm code */
पूर्णांक bmips_smp_enabled = 1;
पूर्णांक bmips_cpu_offset;
cpumask_t bmips_booted_mask;
अचिन्हित दीर्घ bmips_tp1_irqs = IE_IRQ1;

#घोषणा RESET_FROM_KSEG0		0x80080800
#घोषणा RESET_FROM_KSEG1		0xa0080800

अटल व्योम bmips_set_reset_vec(पूर्णांक cpu, u32 val);

#अगर_घोषित CONFIG_SMP

/* initial $sp, $gp - used by arch/mips/kernel/bmips_vec.S */
अचिन्हित दीर्घ bmips_smp_boot_sp;
अचिन्हित दीर्घ bmips_smp_boot_gp;

अटल व्योम bmips43xx_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action);
अटल व्योम bmips5000_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action);
अटल irqवापस_t bmips43xx_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t bmips5000_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* SW पूर्णांकerrupts 0,1 are used क्रम पूर्णांकerprocessor संकेतing */
#घोषणा IPI0_IRQ			(MIPS_CPU_IRQ_BASE + 0)
#घोषणा IPI1_IRQ			(MIPS_CPU_IRQ_BASE + 1)

#घोषणा CPUNUM(cpu, shअगरt)		(((cpu) + bmips_cpu_offset) << (shअगरt))
#घोषणा ACTION_CLR_IPI(cpu, ipi)	(0x2000 | CPUNUM(cpu, 9) | ((ipi) << 8))
#घोषणा ACTION_SET_IPI(cpu, ipi)	(0x3000 | CPUNUM(cpu, 9) | ((ipi) << 8))
#घोषणा ACTION_BOOT_THREAD(cpu)		(0x08 | CPUNUM(cpu, 0))

अटल व्योम __init bmips_smp_setup(व्योम)
अणु
	पूर्णांक i, cpu = 1, boot_cpu = 0;
	पूर्णांक cpu_hw_पूर्णांकr;

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
		/* arbitration priority */
		clear_c0_brcm_cmt_ctrl(0x30);

		/* NBK and weak order flags */
		set_c0_brcm_config_0(0x30000);

		/* Find out अगर we are running on TP0 or TP1 */
		boot_cpu = !!(पढ़ो_c0_brcm_cmt_local() & (1 << 31));

		/*
		 * MIPS पूर्णांकerrupts 0,1 (SW INT 0,1) cross over to the other
		 * thपढ़ो
		 * MIPS पूर्णांकerrupt 2 (HW INT 0) is the CPU0 L1 controller output
		 * MIPS पूर्णांकerrupt 3 (HW INT 1) is the CPU1 L1 controller output
		 */
		अगर (boot_cpu == 0)
			cpu_hw_पूर्णांकr = 0x02;
		अन्यथा
			cpu_hw_पूर्णांकr = 0x1d;

		change_c0_brcm_cmt_पूर्णांकr(0xf8018000,
					(cpu_hw_पूर्णांकr << 27) | (0x03 << 15));

		/* single core, 2 thपढ़ोs (2 pipelines) */
		max_cpus = 2;

		अवरोध;
	हाल CPU_BMIPS5000:
		/* enable raceless SW पूर्णांकerrupts */
		set_c0_brcm_config(0x03 << 22);

		/* route HW पूर्णांकerrupt 0 to CPU0, HW पूर्णांकerrupt 1 to CPU1 */
		change_c0_brcm_mode(0x1f << 27, 0x02 << 27);

		/* N cores, 2 thपढ़ोs per core */
		max_cpus = (((पढ़ो_c0_brcm_config() >> 6) & 0x03) + 1) << 1;

		/* clear any pending SW पूर्णांकerrupts */
		क्रम (i = 0; i < max_cpus; i++) अणु
			ग_लिखो_c0_brcm_action(ACTION_CLR_IPI(i, 0));
			ग_लिखो_c0_brcm_action(ACTION_CLR_IPI(i, 1));
		पूर्ण

		अवरोध;
	शेष:
		max_cpus = 1;
	पूर्ण

	अगर (!bmips_smp_enabled)
		max_cpus = 1;

	/* this can be overridden by the BSP */
	अगर (!board_ebase_setup)
		board_ebase_setup = &bmips_ebase_setup;

	अगर (max_cpus > 1) अणु
		__cpu_number_map[boot_cpu] = 0;
		__cpu_logical_map[0] = boot_cpu;

		क्रम (i = 0; i < max_cpus; i++) अणु
			अगर (i != boot_cpu) अणु
				__cpu_number_map[i] = cpu;
				__cpu_logical_map[cpu] = i;
				cpu++;
			पूर्ण
			set_cpu_possible(i, 1);
			set_cpu_present(i, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		__cpu_number_map[0] = boot_cpu;
		__cpu_logical_map[0] = 0;
		set_cpu_possible(0, 1);
		set_cpu_present(0, 1);
	पूर्ण
पूर्ण

/*
 * IPI IRQ setup - runs on CPU0
 */
अटल व्योम bmips_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	irqवापस_t (*bmips_ipi_पूर्णांकerrupt)(पूर्णांक irq, व्योम *dev_id);

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
		bmips_ipi_पूर्णांकerrupt = bmips43xx_ipi_पूर्णांकerrupt;
		अवरोध;
	हाल CPU_BMIPS5000:
		bmips_ipi_पूर्णांकerrupt = bmips5000_ipi_पूर्णांकerrupt;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (request_irq(IPI0_IRQ, bmips_ipi_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_SUSPEND, "smp_ipi0", शून्य))
		panic("Can't request IPI0 interrupt");
	अगर (request_irq(IPI1_IRQ, bmips_ipi_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_SUSPEND, "smp_ipi1", शून्य))
		panic("Can't request IPI1 interrupt");
पूर्ण

/*
 * Tell the hardware to boot CPUx - runs on CPU0
 */
अटल पूर्णांक bmips_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	bmips_smp_boot_sp = __KSTK_TOS(idle);
	bmips_smp_boot_gp = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);
	mb();

	/*
	 * Initial boot sequence क्रम secondary CPU:
	 *   bmips_reset_nmi_vec @ a000_0000 ->
	 *   bmips_smp_entry ->
	 *   plat_wired_tlb_setup (cached function call; optional) ->
	 *   start_secondary (cached jump)
	 *
	 * Warm restart sequence:
	 *   play_dead WAIT loop ->
	 *   bmips_smp_पूर्णांक_vec @ BMIPS_WARM_RESTART_VEC ->
	 *   eret to play_dead ->
	 *   bmips_secondary_reentry ->
	 *   start_secondary
	 */

	pr_info("SMP: Booting CPU%d...\n", cpu);

	अगर (cpumask_test_cpu(cpu, &bmips_booted_mask)) अणु
		/* kseg1 might not exist अगर this CPU enabled XKS01 */
		bmips_set_reset_vec(cpu, RESET_FROM_KSEG0);

		चयन (current_cpu_type()) अणु
		हाल CPU_BMIPS4350:
		हाल CPU_BMIPS4380:
			bmips43xx_send_ipi_single(cpu, 0);
			अवरोध;
		हाल CPU_BMIPS5000:
			bmips5000_send_ipi_single(cpu, 0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		bmips_set_reset_vec(cpu, RESET_FROM_KSEG1);

		चयन (current_cpu_type()) अणु
		हाल CPU_BMIPS4350:
		हाल CPU_BMIPS4380:
			/* Reset slave TP1 अगर booting from TP0 */
			अगर (cpu_logical_map(cpu) == 1)
				set_c0_brcm_cmt_ctrl(0x01);
			अवरोध;
		हाल CPU_BMIPS5000:
			ग_लिखो_c0_brcm_action(ACTION_BOOT_THREAD(cpu));
			अवरोध;
		पूर्ण
		cpumask_set_cpu(cpu, &bmips_booted_mask);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Early setup - runs on secondary CPU after cache probe
 */
अटल व्योम bmips_init_secondary(व्योम)
अणु
	bmips_cpu_setup();

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
		clear_c0_cause(smp_processor_id() ? C_SW1 : C_SW0);
		अवरोध;
	हाल CPU_BMIPS5000:
		ग_लिखो_c0_brcm_action(ACTION_CLR_IPI(smp_processor_id(), 0));
		cpu_set_core(&current_cpu_data, (पढ़ो_c0_brcm_config() >> 25) & 3);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Late setup - runs on secondary CPU beक्रमe entering the idle loop
 */
अटल व्योम bmips_smp_finish(व्योम)
अणु
	pr_info("SMP: CPU%d is running\n", smp_processor_id());

	/* make sure there won't be a समयr पूर्णांकerrupt क्रम a little जबतक */
	ग_लिखो_c0_compare(पढ़ो_c0_count() + mips_hpt_frequency / HZ);

	irq_enable_hazard();
	set_c0_status(IE_SW0 | IE_SW1 | bmips_tp1_irqs | IE_IRQ5 | ST0_IE);
	irq_enable_hazard();
पूर्ण

/*
 * BMIPS5000 raceless IPIs
 *
 * Each CPU has two inbound SW IRQs which are independent of all other CPUs.
 * IPI0 is used क्रम SMP_RESCHEDULE_YOURSELF
 * IPI1 is used क्रम SMP_CALL_FUNCTION
 */

अटल व्योम bmips5000_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	ग_लिखो_c0_brcm_action(ACTION_SET_IPI(cpu, action == SMP_CALL_FUNCTION));
पूर्ण

अटल irqवापस_t bmips5000_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक action = irq - IPI0_IRQ;

	ग_लिखो_c0_brcm_action(ACTION_CLR_IPI(smp_processor_id(), action));

	अगर (action == 0)
		scheduler_ipi();
	अन्यथा
		generic_smp_call_function_पूर्णांकerrupt();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bmips5000_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
	अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		bmips5000_send_ipi_single(i, action);
पूर्ण

/*
 * BMIPS43xx racey IPIs
 *
 * We use one inbound SW IRQ क्रम each CPU.
 *
 * A spinlock must be held in order to keep CPUx from accidentally clearing
 * an incoming IPI when it ग_लिखोs CP0 CAUSE to उठाओ an IPI on CPUy.  The
 * same spinlock is used to protect the action masks.
 */

अटल DEFINE_SPINLOCK(ipi_lock);
अटल DEFINE_PER_CPU(पूर्णांक, ipi_action_mask);

अटल व्योम bmips43xx_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipi_lock, flags);
	set_c0_cause(cpu ? C_SW1 : C_SW0);
	per_cpu(ipi_action_mask, cpu) |= action;
	irq_enable_hazard();
	spin_unlock_irqrestore(&ipi_lock, flags);
पूर्ण

अटल irqवापस_t bmips43xx_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक action, cpu = irq - IPI0_IRQ;

	spin_lock_irqsave(&ipi_lock, flags);
	action = __this_cpu_पढ़ो(ipi_action_mask);
	per_cpu(ipi_action_mask, cpu) = 0;
	clear_c0_cause(cpu ? C_SW1 : C_SW0);
	spin_unlock_irqrestore(&ipi_lock, flags);

	अगर (action & SMP_RESCHEDULE_YOURSELF)
		scheduler_ipi();
	अगर (action & SMP_CALL_FUNCTION)
		generic_smp_call_function_पूर्णांकerrupt();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bmips43xx_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
	अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		bmips43xx_send_ipi_single(i, action);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक bmips_cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	pr_info("SMP: CPU%d is offline\n", cpu);

	set_cpu_online(cpu, false);
	calculate_cpu_क्रमeign_map();
	irq_cpu_offline();
	clear_c0_status(IE_IRQ5);

	local_flush_tlb_all();
	local_flush_icache_range(0, ~0);

	वापस 0;
पूर्ण

अटल व्योम bmips_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
पूर्ण

व्योम __ref play_dead(व्योम)
अणु
	idle_task_निकास();

	/* flush data cache */
	_dma_cache_wback_inv(0, ~0);

	/*
	 * Wakeup is on SW0 or SW1; disable everything अन्यथा
	 * Use BEV !IV (BMIPS_WARM_RESTART_VEC) to aव्योम the regular Linux
	 * IRQ handlers; this clears ST0_IE and वापसs immediately.
	 */
	clear_c0_cause(CAUSEF_IV | C_SW0 | C_SW1);
	change_c0_status(
		IE_IRQ5 | bmips_tp1_irqs | IE_SW0 | IE_SW1 | ST0_IE | ST0_BEV,
		IE_SW0 | IE_SW1 | ST0_IE | ST0_BEV);
	irq_disable_hazard();

	/*
	 * रुको क्रम SW पूर्णांकerrupt from bmips_boot_secondary(), then jump
	 * back to start_secondary()
	 */
	__यंत्र__ __अस्थिर__(
	"	wait\n"
	"	j	bmips_secondary_reentry\n"
	: : : "memory");
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

स्थिर काष्ठा plat_smp_ops bmips43xx_smp_ops = अणु
	.smp_setup		= bmips_smp_setup,
	.prepare_cpus		= bmips_prepare_cpus,
	.boot_secondary		= bmips_boot_secondary,
	.smp_finish		= bmips_smp_finish,
	.init_secondary		= bmips_init_secondary,
	.send_ipi_single	= bmips43xx_send_ipi_single,
	.send_ipi_mask		= bmips43xx_send_ipi_mask,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= bmips_cpu_disable,
	.cpu_die		= bmips_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा plat_smp_ops bmips5000_smp_ops = अणु
	.smp_setup		= bmips_smp_setup,
	.prepare_cpus		= bmips_prepare_cpus,
	.boot_secondary		= bmips_boot_secondary,
	.smp_finish		= bmips_smp_finish,
	.init_secondary		= bmips_init_secondary,
	.send_ipi_single	= bmips5000_send_ipi_single,
	.send_ipi_mask		= bmips5000_send_ipi_mask,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= bmips_cpu_disable,
	.cpu_die		= bmips_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* CONFIG_SMP */

/***********************************************************************
 * BMIPS vector relocation
 * This is primarily used क्रम SMP boot, but it is applicable to some
 * UP BMIPS प्रणालीs as well.
 ***********************************************************************/

अटल व्योम bmips_wr_vec(अचिन्हित दीर्घ dst, अक्षर *start, अक्षर *end)
अणु
	स_नकल((व्योम *)dst, start, end - start);
	dma_cache_wback(dst, end - start);
	local_flush_icache_range(dst, dst + (end - start));
	inकाष्ठाion_hazard();
पूर्ण

अटल अंतरभूत व्योम bmips_nmi_handler_setup(व्योम)
अणु
	bmips_wr_vec(BMIPS_NMI_RESET_VEC, bmips_reset_nmi_vec,
		bmips_reset_nmi_vec_end);
	bmips_wr_vec(BMIPS_WARM_RESTART_VEC, bmips_smp_पूर्णांक_vec,
		bmips_smp_पूर्णांक_vec_end);
पूर्ण

काष्ठा reset_vec_info अणु
	पूर्णांक cpu;
	u32 val;
पूर्ण;

अटल व्योम bmips_set_reset_vec_remote(व्योम *vinfo)
अणु
	काष्ठा reset_vec_info *info = vinfo;
	पूर्णांक shअगरt = info->cpu & 0x01 ? 16 : 0;
	u32 mask = ~(0xffff << shअगरt), val = info->val >> 16;

	preempt_disable();
	अगर (smp_processor_id() > 0) अणु
		smp_call_function_single(0, &bmips_set_reset_vec_remote,
					 info, 1);
	पूर्ण अन्यथा अणु
		अगर (info->cpu & 0x02) अणु
			/* BMIPS5200 "should" use mask/shअगरt, but it's buggy */
			bmips_ग_लिखो_zscm_reg(0xa0, (val << 16) | val);
			bmips_पढ़ो_zscm_reg(0xa0);
		पूर्ण अन्यथा अणु
			ग_लिखो_c0_brcm_bootvec((पढ़ो_c0_brcm_bootvec() & mask) |
					      (val << shअगरt));
		पूर्ण
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम bmips_set_reset_vec(पूर्णांक cpu, u32 val)
अणु
	काष्ठा reset_vec_info info;

	अगर (current_cpu_type() == CPU_BMIPS5000) अणु
		/* this needs to run from CPU0 (which is always online) */
		info.cpu = cpu;
		info.val = val;
		bmips_set_reset_vec_remote(&info);
	पूर्ण अन्यथा अणु
		व्योम __iomem *cbr = BMIPS_GET_CBR();

		अगर (cpu == 0)
			__raw_ग_लिखोl(val, cbr + BMIPS_RELO_VECTOR_CONTROL_0);
		अन्यथा अणु
			अगर (current_cpu_type() != CPU_BMIPS4380)
				वापस;
			__raw_ग_लिखोl(val, cbr + BMIPS_RELO_VECTOR_CONTROL_1);
		पूर्ण
	पूर्ण
	__sync();
	back_to_back_c0_hazard();
पूर्ण

व्योम bmips_ebase_setup(व्योम)
अणु
	अचिन्हित दीर्घ new_ebase = ebase;

	BUG_ON(ebase != CKSEG0);

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS4350:
		/*
		 * BMIPS4350 cannot relocate the normal vectors, but it
		 * can relocate the BEV=1 vectors.  So CPU1 starts up at
		 * the relocated BEV=1, IV=0 general exception vector @
		 * 0xa000_0380.
		 *
		 * set_uncached_handler() is used here because:
		 *  - CPU1 will run this from uncached space
		 *  - None of the cacheflush functions are set up yet
		 */
		set_uncached_handler(BMIPS_WARM_RESTART_VEC - CKSEG0,
			&bmips_smp_पूर्णांक_vec, 0x80);
		__sync();
		वापस;
	हाल CPU_BMIPS3300:
	हाल CPU_BMIPS4380:
		/*
		 * 0x8000_0000: reset/NMI (initially in kseg1)
		 * 0x8000_0400: normal vectors
		 */
		new_ebase = 0x80000400;
		bmips_set_reset_vec(0, RESET_FROM_KSEG0);
		अवरोध;
	हाल CPU_BMIPS5000:
		/*
		 * 0x8000_0000: reset/NMI (initially in kseg1)
		 * 0x8000_1000: normal vectors
		 */
		new_ebase = 0x80001000;
		bmips_set_reset_vec(0, RESET_FROM_KSEG0);
		ग_लिखो_c0_ebase(new_ebase);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	board_nmi_handler_setup = &bmips_nmi_handler_setup;
	ebase = new_ebase;
पूर्ण

यंत्रlinkage व्योम __weak plat_wired_tlb_setup(व्योम)
अणु
	/*
	 * Called when starting/restarting a secondary CPU.
	 * Kernel stacks and other important data might only be accessible
	 * once the wired entries are present.
	 */
पूर्ण

व्योम bmips_cpu_setup(व्योम)
अणु
	व्योम __iomem __maybe_unused *cbr = BMIPS_GET_CBR();
	u32 __maybe_unused cfg;

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS3300:
		/* Set BIU to async mode */
		set_c0_brcm_bus_pll(BIT(22));
		__sync();

		/* put the BIU back in sync mode */
		clear_c0_brcm_bus_pll(BIT(22));

		/* clear BHTD to enable branch history table */
		clear_c0_brcm_reset(BIT(16));

		/* Flush and enable RAC */
		cfg = __raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);
		__raw_ग_लिखोl(cfg | 0x100, cbr + BMIPS_RAC_CONFIG);
		__raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);

		cfg = __raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);
		__raw_ग_लिखोl(cfg | 0xf, cbr + BMIPS_RAC_CONFIG);
		__raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);

		cfg = __raw_पढ़ोl(cbr + BMIPS_RAC_ADDRESS_RANGE);
		__raw_ग_लिखोl(cfg | 0x0fff0000, cbr + BMIPS_RAC_ADDRESS_RANGE);
		__raw_पढ़ोl(cbr + BMIPS_RAC_ADDRESS_RANGE);
		अवरोध;

	हाल CPU_BMIPS4380:
		/* CBG workaround क्रम early BMIPS4380 CPUs */
		चयन (पढ़ो_c0_prid()) अणु
		हाल 0x2a040:
		हाल 0x2a042:
		हाल 0x2a044:
		हाल 0x2a060:
			cfg = __raw_पढ़ोl(cbr + BMIPS_L2_CONFIG);
			__raw_ग_लिखोl(cfg & ~0x07000000, cbr + BMIPS_L2_CONFIG);
			__raw_पढ़ोl(cbr + BMIPS_L2_CONFIG);
		पूर्ण

		/* clear BHTD to enable branch history table */
		clear_c0_brcm_config_0(BIT(21));

		/* XI/ROTR enable */
		set_c0_brcm_config_0(BIT(23));
		set_c0_brcm_cmt_ctrl(BIT(15));
		अवरोध;

	हाल CPU_BMIPS5000:
		/* enable RDHWR, BRDHWR */
		set_c0_brcm_config(BIT(17) | BIT(21));

		/* Disable JTB */
		__यंत्र__ __अस्थिर__(
		"	.set	noreorder\n"
		"	li	$8, 0x5a455048\n"
		"	.word	0x4088b00f\n"	/* mtc0	t0, $22, 15 */
		"	.word	0x4008b008\n"	/* mfc0	t0, $22, 8 */
		"	li	$9, 0x00008000\n"
		"	or	$8, $8, $9\n"
		"	.word	0x4088b008\n"	/* mtc0	t0, $22, 8 */
		"	sync\n"
		"	li	$8, 0x0\n"
		"	.word	0x4088b00f\n"	/* mtc0	t0, $22, 15 */
		"	.set	reorder\n"
		: : : "$8", "$9");

		/* XI enable */
		set_c0_brcm_config(BIT(27));

		/* enable MIPS32R2 ROR inकाष्ठाion क्रम XI TLB handlers */
		__यंत्र__ __अस्थिर__(
		"	li	$8, 0x5a455048\n"
		"	.word	0x4088b00f\n"	/* mtc0 $8, $22, 15 */
		"	nop; nop; nop\n"
		"	.word	0x4008b008\n"	/* mfc0 $8, $22, 8 */
		"	lui	$9, 0x0100\n"
		"	or	$8, $9\n"
		"	.word	0x4088b008\n"	/* mtc0 $8, $22, 8 */
		: : : "$8", "$9");
		अवरोध;
	पूर्ण
पूर्ण
