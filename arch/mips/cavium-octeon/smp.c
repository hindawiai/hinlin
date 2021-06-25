<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2008, 2009, 2010 Cavium Networks
 */
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kexec.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश "octeon_boot.h"

अस्थिर अचिन्हित दीर्घ octeon_processor_boot = 0xff;
अस्थिर अचिन्हित दीर्घ octeon_processor_sp;
अस्थिर अचिन्हित दीर्घ octeon_processor_gp;
#अगर_घोषित CONFIG_RELOCATABLE
अस्थिर अचिन्हित दीर्घ octeon_processor_relocated_kernel_entry;
#पूर्ण_अगर /* CONFIG_RELOCATABLE */

#अगर_घोषित CONFIG_HOTPLUG_CPU
uपूर्णांक64_t octeon_bootloader_entry_addr;
EXPORT_SYMBOL(octeon_bootloader_entry_addr);
#पूर्ण_अगर

बाह्य व्योम kernel_entry(अचिन्हित दीर्घ arg1, ...);

अटल व्योम octeon_icache_flush(व्योम)
अणु
	यंत्र अस्थिर ("synci 0($0)\n");
पूर्ण

अटल व्योम (*octeon_message_functions[8])(व्योम) = अणु
	scheduler_ipi,
	generic_smp_call_function_पूर्णांकerrupt,
	octeon_icache_flush,
पूर्ण;

अटल irqवापस_t mailbox_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u64 mbox_clrx = CVMX_CIU_MBOX_CLRX(cvmx_get_core_num());
	u64 action;
	पूर्णांक i;

	/*
	 * Make sure the function array initialization reमुख्यs
	 * correct.
	 */
	BUILD_BUG_ON(SMP_RESCHEDULE_YOURSELF != (1 << 0));
	BUILD_BUG_ON(SMP_CALL_FUNCTION       != (1 << 1));
	BUILD_BUG_ON(SMP_ICACHE_FLUSH        != (1 << 2));

	/*
	 * Load the mailbox रेजिस्टर to figure out what we're supposed
	 * to करो.
	 */
	action = cvmx_पढ़ो_csr(mbox_clrx);

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		action &= 0xff;
	अन्यथा
		action &= 0xffff;

	/* Clear the mailbox to clear the पूर्णांकerrupt */
	cvmx_ग_लिखो_csr(mbox_clrx, action);

	क्रम (i = 0; i < ARRAY_SIZE(octeon_message_functions) && action;) अणु
		अगर (action & 1) अणु
			व्योम (*fn)(व्योम) = octeon_message_functions[i];

			अगर (fn)
				fn();
		पूर्ण
		action >>= 1;
		i++;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * Cause the function described by call_data to be executed on the passed
 * cpu.	 When the function has finished, increment the finished field of
 * call_data.
 */
व्योम octeon_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	पूर्णांक coreid = cpu_logical_map(cpu);
	/*
	pr_info("SMP: Mailbox send cpu=%d, coreid=%d, action=%u\n", cpu,
	       coreid, action);
	*/
	cvmx_ग_लिखो_csr(CVMX_CIU_MBOX_SETX(coreid), action);
पूर्ण

अटल अंतरभूत व्योम octeon_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
					अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		octeon_send_ipi_single(i, action);
पूर्ण

/**
 * Detect available CPUs, populate cpu_possible_mask
 */
अटल व्योम octeon_smp_hotplug_setup(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	काष्ठा linux_app_boot_info *labi;

	अगर (!setup_max_cpus)
		वापस;

	labi = (काष्ठा linux_app_boot_info *)PHYS_TO_XKSEG_CACHED(LABI_ADDR_IN_BOOTLOADER);
	अगर (labi->labi_signature != LABI_SIGNATURE) अणु
		pr_info("The bootloader on this board does not support HOTPLUG_CPU.");
		वापस;
	पूर्ण

	octeon_bootloader_entry_addr = labi->InitTLBStart_addr;
#पूर्ण_अगर
पूर्ण

अटल व्योम __init octeon_smp_setup(व्योम)
अणु
	स्थिर पूर्णांक coreid = cvmx_get_core_num();
	पूर्णांक cpus;
	पूर्णांक id;
	काष्ठा cvmx_sysinfo *sysinfo = cvmx_sysinfo_get();

#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक core_mask = octeon_get_boot_coremask();
	अचिन्हित पूर्णांक num_cores = cvmx_octeon_num_cores();
#पूर्ण_अगर

	/* The present CPUs are initially just the boot cpu (CPU 0). */
	क्रम (id = 0; id < NR_CPUS; id++) अणु
		set_cpu_possible(id, id == 0);
		set_cpu_present(id, id == 0);
	पूर्ण

	__cpu_number_map[coreid] = 0;
	__cpu_logical_map[0] = coreid;

	/* The present CPUs get the lowest CPU numbers. */
	cpus = 1;
	क्रम (id = 0; id < NR_CPUS; id++) अणु
		अगर ((id != coreid) && cvmx_coremask_is_core_set(&sysinfo->core_mask, id)) अणु
			set_cpu_possible(cpus, true);
			set_cpu_present(cpus, true);
			__cpu_number_map[id] = cpus;
			__cpu_logical_map[cpus] = id;
			cpus++;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
	/*
	 * The possible CPUs are all those present on the chip.	 We
	 * will assign CPU numbers क्रम possible cores as well.	Cores
	 * are always consecutively numberd from 0.
	 */
	क्रम (id = 0; setup_max_cpus && octeon_bootloader_entry_addr &&
		     id < num_cores && id < NR_CPUS; id++) अणु
		अगर (!(core_mask & (1 << id))) अणु
			set_cpu_possible(cpus, true);
			__cpu_number_map[id] = cpus;
			__cpu_logical_map[cpus] = id;
			cpus++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	octeon_smp_hotplug_setup();
पूर्ण


#अगर_घोषित CONFIG_RELOCATABLE
पूर्णांक plat_post_relocation(दीर्घ offset)
अणु
	अचिन्हित दीर्घ entry = (अचिन्हित दीर्घ)kernel_entry;

	/* Send secondaries पूर्णांकo relocated kernel */
	octeon_processor_relocated_kernel_entry = entry + offset;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_RELOCATABLE */

/**
 * Firmware CPU startup hook
 *
 */
अटल पूर्णांक octeon_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक count;

	pr_info("SMP: Booting CPU%02d (CoreId %2d)...\n", cpu,
		cpu_logical_map(cpu));

	octeon_processor_sp = __KSTK_TOS(idle);
	octeon_processor_gp = (अचिन्हित दीर्घ)(task_thपढ़ो_info(idle));
	octeon_processor_boot = cpu_logical_map(cpu);
	mb();

	count = 10000;
	जबतक (octeon_processor_sp && count) अणु
		/* Waiting क्रम processor to get the SP and GP */
		udelay(1);
		count--;
	पूर्ण
	अगर (count == 0) अणु
		pr_err("Secondary boot timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * After we've करोne initial boot, this function is called to allow the
 * board code to clean up state, अगर needed
 */
अटल व्योम octeon_init_secondary(व्योम)
अणु
	अचिन्हित पूर्णांक sr;

	sr = set_c0_status(ST0_BEV);
	ग_लिखो_c0_ebase((u32)ebase);
	ग_लिखो_c0_status(sr);

	octeon_check_cpu_bist();
	octeon_init_cvmcount();

	octeon_irq_setup_secondary();
पूर्ण

/**
 * Callout to firmware beक्रमe smp_init
 *
 */
अटल व्योम __init octeon_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/*
	 * Only the low order mailbox bits are used क्रम IPIs, leave
	 * the other bits alone.
	 */
	cvmx_ग_लिखो_csr(CVMX_CIU_MBOX_CLRX(cvmx_get_core_num()), 0xffff);
	अगर (request_irq(OCTEON_IRQ_MBOX0, mailbox_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-IPI",
			mailbox_पूर्णांकerrupt)) अणु
		panic("Cannot request_irq(OCTEON_IRQ_MBOX0)");
	पूर्ण
पूर्ण

/**
 * Last chance क्रम the board code to finish SMP initialization beक्रमe
 * the CPU is "online".
 */
अटल व्योम octeon_smp_finish(व्योम)
अणु
	octeon_user_io_init();

	/* to generate the first CPU समयr पूर्णांकerrupt */
	ग_लिखो_c0_compare(पढ़ो_c0_count() + mips_hpt_frequency / HZ);
	local_irq_enable();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

/* State of each CPU. */
अटल DEFINE_PER_CPU(पूर्णांक, cpu_state);

अटल पूर्णांक octeon_cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (!octeon_bootloader_entry_addr)
		वापस -ENOTSUPP;

	set_cpu_online(cpu, false);
	calculate_cpu_क्रमeign_map();
	octeon_fixup_irqs();

	__flush_cache_all();
	local_flush_tlb_all();

	वापस 0;
पूर्ण

अटल व्योम octeon_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक coreid = cpu_logical_map(cpu);
	uपूर्णांक32_t mask, new_mask;
	स्थिर काष्ठा cvmx_booपंचांगem_named_block_desc *block_desc;

	जबतक (per_cpu(cpu_state, cpu) != CPU_DEAD)
		cpu_relax();

	/*
	 * This is a bit complicated strategics of getting/settig available
	 * cores mask, copied from bootloader
	 */

	mask = 1 << coreid;
	/* LINUX_APP_BOOT_BLOCK is initialized in bootoct binary */
	block_desc = cvmx_booपंचांगem_find_named_block(LINUX_APP_BOOT_BLOCK_NAME);

	अगर (!block_desc) अणु
		काष्ठा linux_app_boot_info *labi;

		labi = (काष्ठा linux_app_boot_info *)PHYS_TO_XKSEG_CACHED(LABI_ADDR_IN_BOOTLOADER);

		labi->avail_coremask |= mask;
		new_mask = labi->avail_coremask;
	पूर्ण अन्यथा अणु		       /* alternative, alपढ़ोy initialized */
		uपूर्णांक32_t *p = (uपूर्णांक32_t *)PHYS_TO_XKSEG_CACHED(block_desc->base_addr +
							       AVAIL_COREMASK_OFFSET_IN_LINUX_APP_BOOT_BLOCK);
		*p |= mask;
		new_mask = *p;
	पूर्ण

	pr_info("Reset core %d. Available Coremask = 0x%x \n", coreid, new_mask);
	mb();
	cvmx_ग_लिखो_csr(CVMX_CIU_PP_RST, 1 << coreid);
	cvmx_ग_लिखो_csr(CVMX_CIU_PP_RST, 0);
पूर्ण

व्योम play_dead(व्योम)
अणु
	पूर्णांक cpu = cpu_number_map(cvmx_get_core_num());

	idle_task_निकास();
	octeon_processor_boot = 0xff;
	per_cpu(cpu_state, cpu) = CPU_DEAD;

	mb();

	जबतक (1)	/* core will be reset here */
		;
पूर्ण

अटल व्योम start_after_reset(व्योम)
अणु
	kernel_entry(0, 0, 0);	/* set a2 = 0 क्रम secondary core */
पूर्ण

अटल पूर्णांक octeon_update_boot_vector(अचिन्हित पूर्णांक cpu)
अणु

	पूर्णांक coreid = cpu_logical_map(cpu);
	uपूर्णांक32_t avail_coremask;
	स्थिर काष्ठा cvmx_booपंचांगem_named_block_desc *block_desc;
	काष्ठा boot_init_vector *boot_vect =
		(काष्ठा boot_init_vector *)PHYS_TO_XKSEG_CACHED(BOOTLOADER_BOOT_VECTOR);

	block_desc = cvmx_booपंचांगem_find_named_block(LINUX_APP_BOOT_BLOCK_NAME);

	अगर (!block_desc) अणु
		काष्ठा linux_app_boot_info *labi;

		labi = (काष्ठा linux_app_boot_info *)PHYS_TO_XKSEG_CACHED(LABI_ADDR_IN_BOOTLOADER);

		avail_coremask = labi->avail_coremask;
		labi->avail_coremask &= ~(1 << coreid);
	पूर्ण अन्यथा अणु		       /* alternative, alपढ़ोy initialized */
		avail_coremask = *(uपूर्णांक32_t *)PHYS_TO_XKSEG_CACHED(
			block_desc->base_addr + AVAIL_COREMASK_OFFSET_IN_LINUX_APP_BOOT_BLOCK);
	पूर्ण

	अगर (!(avail_coremask & (1 << coreid))) अणु
		/* core not available, assume, that caught by simple-executive */
		cvmx_ग_लिखो_csr(CVMX_CIU_PP_RST, 1 << coreid);
		cvmx_ग_लिखो_csr(CVMX_CIU_PP_RST, 0);
	पूर्ण

	boot_vect[coreid].app_start_func_addr =
		(uपूर्णांक32_t) (अचिन्हित दीर्घ) start_after_reset;
	boot_vect[coreid].code_addr = octeon_bootloader_entry_addr;

	mb();

	cvmx_ग_लिखो_csr(CVMX_CIU_NMI, (1 << coreid) & avail_coremask);

	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_cavium_notअगरier(व्योम)
अणु
	वापस cpuhp_setup_state_nocalls(CPUHP_MIPS_SOC_PREPARE,
					 "mips/cavium:prepare",
					 octeon_update_boot_vector, शून्य);
पूर्ण
late_initcall(रेजिस्टर_cavium_notअगरier);

#पूर्ण_अगर	/* CONFIG_HOTPLUG_CPU */

अटल स्थिर काष्ठा plat_smp_ops octeon_smp_ops = अणु
	.send_ipi_single	= octeon_send_ipi_single,
	.send_ipi_mask		= octeon_send_ipi_mask,
	.init_secondary		= octeon_init_secondary,
	.smp_finish		= octeon_smp_finish,
	.boot_secondary		= octeon_boot_secondary,
	.smp_setup		= octeon_smp_setup,
	.prepare_cpus		= octeon_prepare_cpus,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= octeon_cpu_disable,
	.cpu_die		= octeon_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t octeon_78xx_reched_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	scheduler_ipi();
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t octeon_78xx_call_function_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	generic_smp_call_function_पूर्णांकerrupt();
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t octeon_78xx_icache_flush_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	octeon_icache_flush();
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Callout to firmware beक्रमe smp_init
 */
अटल व्योम octeon_78xx_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अगर (request_irq(OCTEON_IRQ_MBOX0 + 0,
			octeon_78xx_reched_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "Scheduler",
			octeon_78xx_reched_पूर्णांकerrupt)) अणु
		panic("Cannot request_irq for SchedulerIPI");
	पूर्ण
	अगर (request_irq(OCTEON_IRQ_MBOX0 + 1,
			octeon_78xx_call_function_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-Call",
			octeon_78xx_call_function_पूर्णांकerrupt)) अणु
		panic("Cannot request_irq for SMP-Call");
	पूर्ण
	अगर (request_irq(OCTEON_IRQ_MBOX0 + 2,
			octeon_78xx_icache_flush_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "ICache-Flush",
			octeon_78xx_icache_flush_पूर्णांकerrupt)) अणु
		panic("Cannot request_irq for ICache-Flush");
	पूर्ण
पूर्ण

अटल व्योम octeon_78xx_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (action & 1)
			octeon_ciu3_mbox_send(cpu, i);
		action >>= 1;
	पूर्ण
पूर्ण

अटल व्योम octeon_78xx_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
				      अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		octeon_78xx_send_ipi_single(cpu, action);
पूर्ण

अटल स्थिर काष्ठा plat_smp_ops octeon_78xx_smp_ops = अणु
	.send_ipi_single	= octeon_78xx_send_ipi_single,
	.send_ipi_mask		= octeon_78xx_send_ipi_mask,
	.init_secondary		= octeon_init_secondary,
	.smp_finish		= octeon_smp_finish,
	.boot_secondary		= octeon_boot_secondary,
	.smp_setup		= octeon_smp_setup,
	.prepare_cpus		= octeon_78xx_prepare_cpus,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= octeon_cpu_disable,
	.cpu_die		= octeon_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#पूर्ण_अगर
पूर्ण;

व्योम __init octeon_setup_smp(व्योम)
अणु
	स्थिर काष्ठा plat_smp_ops *ops;

	अगर (octeon_has_feature(OCTEON_FEATURE_CIU3))
		ops = &octeon_78xx_smp_ops;
	अन्यथा
		ops = &octeon_smp_ops;

	रेजिस्टर_smp_ops(ops);
पूर्ण
