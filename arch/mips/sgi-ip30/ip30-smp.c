<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip30-smp.c: SMP on IP30 architecture.
 * Based off of the original IP30 SMP code, with inspiration from ip27-smp.c
 * and smp-bmips.c.
 *
 * Copyright (C) 2005-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *               2006-2007, 2014-2015 Joshua Kinard <kumba@gentoo.org>
 *               2009 Johannes Dickgreber <tanzy@gmx.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/sgi/heart.h>

#समावेश "ip30-common.h"

#घोषणा MPCONF_MAGIC	0xbaddeed2
#घोषणा	MPCONF_ADDR	0xa800000000000600L
#घोषणा MPCONF_SIZE	0x80
#घोषणा MPCONF(x)	(MPCONF_ADDR + (x) * MPCONF_SIZE)

/* HEART can theoretically करो 4 CPUs, but only 2 are physically possible */
#घोषणा MP_NCPU		2

काष्ठा mpconf अणु
	u32 magic;
	u32 prid;
	u32 physid;
	u32 virtid;
	u32 scachesz;
	u16 fanloads;
	u16 res;
	व्योम *launch;
	व्योम *rendezvous;
	u64 res2[3];
	व्योम *stackaddr;
	व्योम *lnch_parm;
	व्योम *rndv_parm;
	u32 idleflag;
पूर्ण;

अटल व्योम ip30_smp_send_ipi_single(पूर्णांक cpu, u32 action)
अणु
	पूर्णांक irq;

	चयन (action) अणु
	हाल SMP_RESCHEDULE_YOURSELF:
		irq = HEART_L2_INT_RESCHED_CPU_0;
		अवरोध;
	हाल SMP_CALL_FUNCTION:
		irq = HEART_L2_INT_CALL_CPU_0;
		अवरोध;
	शेष:
		panic("IP30: Unknown action value in %s!\n", __func__);
	पूर्ण

	irq += cpu;

	/* Poke the other CPU -- it's got mail! */
	heart_ग_लिखो(BIT_ULL(irq), &heart_regs->set_isr);
पूर्ण

अटल व्योम ip30_smp_send_ipi_mask(स्थिर काष्ठा cpumask *mask, u32 action)
अणु
	u32 i;

	क्रम_each_cpu(i, mask)
		ip30_smp_send_ipi_single(i, action);
पूर्ण

अटल व्योम __init ip30_smp_setup(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ncpu = 0;
	काष्ठा mpconf *mpc;

	init_cpu_possible(cpumask_of(0));

	/* Scan the MPCONF काष्ठाure and क्रमागतerate available CPUs. */
	क्रम (i = 0; i < MP_NCPU; i++) अणु
		mpc = (काष्ठा mpconf *)MPCONF(i);
		अगर (mpc->magic == MPCONF_MAGIC) अणु
			set_cpu_possible(i, true);
			__cpu_number_map[i] = ++ncpu;
			__cpu_logical_map[ncpu] = i;
			pr_info("IP30: Slot: %d, PrID: %.8x, PhyID: %d, VirtID: %d\n",
				i, mpc->prid, mpc->physid, mpc->virtid);
		पूर्ण
	पूर्ण
	pr_info("IP30: Detected %d CPU(s) present.\n", ncpu);

	/*
	 * Set the coherency algorithm to '5' (cacheable coherent
	 * exclusive on ग_लिखो).  This is needed on IP30 SMP, especially
	 * क्रम R14000 CPUs, otherwise, inकाष्ठाion bus errors will
	 * occur upon reaching userland.
	 */
	change_c0_config(CONF_CM_CMASK, CONF_CM_CACHABLE_COW);
पूर्ण

अटल व्योम __init ip30_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* nothing to करो here */
पूर्ण

अटल पूर्णांक __init ip30_smp_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा mpconf *mpc = (काष्ठा mpconf *)MPCONF(cpu);

	/* Stack poपूर्णांकer (sp). */
	mpc->stackaddr = (व्योम *)__KSTK_TOS(idle);

	/* Global poपूर्णांकer (gp). */
	mpc->lnch_parm = task_thपढ़ो_info(idle);

	mb(); /* make sure stack and lparm are written */

	/* Boot CPUx. */
	mpc->launch = smp_bootstrap;

	/* CPUx now executes smp_bootstrap, then ip30_smp_finish */
	वापस 0;
पूर्ण

अटल व्योम __init ip30_smp_init_cpu(व्योम)
अणु
	ip30_per_cpu_init();
पूर्ण

अटल व्योम __init ip30_smp_finish(व्योम)
अणु
	enable_percpu_irq(get_c0_compare_पूर्णांक(), IRQ_TYPE_NONE);
	local_irq_enable();
पूर्ण

काष्ठा plat_smp_ops __पढ़ो_mostly ip30_smp_ops = अणु
	.send_ipi_single	= ip30_smp_send_ipi_single,
	.send_ipi_mask		= ip30_smp_send_ipi_mask,
	.smp_setup		= ip30_smp_setup,
	.prepare_cpus		= ip30_smp_prepare_cpus,
	.boot_secondary		= ip30_smp_boot_secondary,
	.init_secondary		= ip30_smp_init_cpu,
	.smp_finish		= ip30_smp_finish,
	.prepare_boot_cpu	= ip30_smp_init_cpu,
पूर्ण;
