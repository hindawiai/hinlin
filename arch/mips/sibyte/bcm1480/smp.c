<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001,2002,2004 Broadcom Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fw/cfe/cfe_api.h>
#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>

/*
 * These are routines क्रम dealing with the bcm1480 smp capabilities
 * independent of board/firmware
 */

अटल व्योम *mailbox_0_set_regs[] = अणु
	IOADDR(A_BCM1480_IMR_CPU0_BASE + R_BCM1480_IMR_MAILBOX_0_SET_CPU),
	IOADDR(A_BCM1480_IMR_CPU1_BASE + R_BCM1480_IMR_MAILBOX_0_SET_CPU),
	IOADDR(A_BCM1480_IMR_CPU2_BASE + R_BCM1480_IMR_MAILBOX_0_SET_CPU),
	IOADDR(A_BCM1480_IMR_CPU3_BASE + R_BCM1480_IMR_MAILBOX_0_SET_CPU),
पूर्ण;

अटल व्योम *mailbox_0_clear_regs[] = अणु
	IOADDR(A_BCM1480_IMR_CPU0_BASE + R_BCM1480_IMR_MAILBOX_0_CLR_CPU),
	IOADDR(A_BCM1480_IMR_CPU1_BASE + R_BCM1480_IMR_MAILBOX_0_CLR_CPU),
	IOADDR(A_BCM1480_IMR_CPU2_BASE + R_BCM1480_IMR_MAILBOX_0_CLR_CPU),
	IOADDR(A_BCM1480_IMR_CPU3_BASE + R_BCM1480_IMR_MAILBOX_0_CLR_CPU),
पूर्ण;

अटल व्योम *mailbox_0_regs[] = अणु
	IOADDR(A_BCM1480_IMR_CPU0_BASE + R_BCM1480_IMR_MAILBOX_0_CPU),
	IOADDR(A_BCM1480_IMR_CPU1_BASE + R_BCM1480_IMR_MAILBOX_0_CPU),
	IOADDR(A_BCM1480_IMR_CPU2_BASE + R_BCM1480_IMR_MAILBOX_0_CPU),
	IOADDR(A_BCM1480_IMR_CPU3_BASE + R_BCM1480_IMR_MAILBOX_0_CPU),
पूर्ण;

/*
 * SMP init and finish on secondary CPUs
 */
व्योम bcm1480_smp_init(व्योम)
अणु
	अचिन्हित पूर्णांक imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Set पूर्णांकerrupt mask, but करोn't enable */
	change_c0_status(ST0_IM, imask);
पूर्ण

/*
 * These are routines क्रम dealing with the sb1250 smp capabilities
 * independent of board/firmware
 */

/*
 * Simple enough; everything is set up, so just poke the appropriate mailbox
 * रेजिस्टर, and we should be set
 */
अटल व्योम bcm1480_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	__raw_ग_लिखोq((((u64)action)<< 48), mailbox_0_set_regs[cpu]);
पूर्ण

अटल व्योम bcm1480_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
				  अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		bcm1480_send_ipi_single(i, action);
पूर्ण

/*
 * Code to run on secondary just after probing the CPU
 */
अटल व्योम bcm1480_init_secondary(व्योम)
अणु
	बाह्य व्योम bcm1480_smp_init(व्योम);

	bcm1480_smp_init();
पूर्ण

/*
 * Do any tidying up beक्रमe marking online and running the idle
 * loop
 */
अटल व्योम bcm1480_smp_finish(व्योम)
अणु
	बाह्य व्योम sb1480_घड़ीevent_init(व्योम);

	sb1480_घड़ीevent_init();
	local_irq_enable();
पूर्ण

/*
 * Setup the PC, SP, and GP of a secondary processor and start it
 * running!
 */
अटल पूर्णांक bcm1480_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक retval;

	retval = cfe_cpu_start(cpu_logical_map(cpu), &smp_bootstrap,
			       __KSTK_TOS(idle),
			       (अचिन्हित दीर्घ)task_thपढ़ो_info(idle), 0);
	अगर (retval != 0)
		prपूर्णांकk("cfe_start_cpu(%i) returned %i\n" , cpu, retval);
	वापस retval;
पूर्ण

/*
 * Use CFE to find out how many CPUs are available, setting up
 * cpu_possible_mask and the logical/physical mappings.
 * XXXKW will the boot CPU ever not be physical 0?
 *
 * Common setup beक्रमe any secondaries are started
 */
अटल व्योम __init bcm1480_smp_setup(व्योम)
अणु
	पूर्णांक i, num;

	init_cpu_possible(cpumask_of(0));
	__cpu_number_map[0] = 0;
	__cpu_logical_map[0] = 0;

	क्रम (i = 1, num = 0; i < NR_CPUS; i++) अणु
		अगर (cfe_cpu_stop(i) == 0) अणु
			set_cpu_possible(i, true);
			__cpu_number_map[i] = ++num;
			__cpu_logical_map[num] = i;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO "Detected %i available secondary CPU(s)\n", num);
पूर्ण

अटल व्योम __init bcm1480_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

स्थिर काष्ठा plat_smp_ops bcm1480_smp_ops = अणु
	.send_ipi_single	= bcm1480_send_ipi_single,
	.send_ipi_mask		= bcm1480_send_ipi_mask,
	.init_secondary		= bcm1480_init_secondary,
	.smp_finish		= bcm1480_smp_finish,
	.boot_secondary		= bcm1480_boot_secondary,
	.smp_setup		= bcm1480_smp_setup,
	.prepare_cpus		= bcm1480_prepare_cpus,
पूर्ण;

व्योम bcm1480_mailbox_पूर्णांकerrupt(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक irq = K_BCM1480_INT_MBOX_0_0;
	अचिन्हित पूर्णांक action;

	kstat_incr_irq_this_cpu(irq);
	/* Load the mailbox रेजिस्टर to figure out what we're supposed to करो */
	action = (__raw_पढ़ोq(mailbox_0_regs[cpu]) >> 48) & 0xffff;

	/* Clear the mailbox to clear the पूर्णांकerrupt */
	__raw_ग_लिखोq(((u64)action)<<48, mailbox_0_clear_regs[cpu]);

	अगर (action & SMP_RESCHEDULE_YOURSELF)
		scheduler_ipi();

	अगर (action & SMP_CALL_FUNCTION) अणु
		irq_enter();
		generic_smp_call_function_पूर्णांकerrupt();
		irq_निकास();
	पूर्ण
पूर्ण
