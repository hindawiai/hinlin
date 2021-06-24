<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Xianghua Xiao <x.xiao@मुक्तscale.com>
 *         Zhang Wei <wei.zhang@मुक्तscale.com>
 *
 * Copyright 2006 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/inst.h>

#समावेश <sysdev/fsl_soc.h>

#समावेश "mpc86xx.h"

बाह्य व्योम __secondary_start_mpc86xx(व्योम);

#घोषणा MCM_PORT_CONFIG_OFFSET	0x10

/* Offset from CCSRBAR */
#घोषणा MPC86xx_MCM_OFFSET      (0x1000)
#घोषणा MPC86xx_MCM_SIZE        (0x1000)

अटल व्योम __init
smp_86xx_release_core(पूर्णांक nr)
अणु
	__be32 __iomem *mcm_vaddr;
	अचिन्हित दीर्घ pcr;

	अगर (nr < 0 || nr >= NR_CPUS)
		वापस;

	/*
	 * Startup Core #nr.
	 */
	mcm_vaddr = ioremap(get_immrbase() + MPC86xx_MCM_OFFSET,
			    MPC86xx_MCM_SIZE);
	pcr = in_be32(mcm_vaddr + (MCM_PORT_CONFIG_OFFSET >> 2));
	pcr |= 1 << (nr + 24);
	out_be32(mcm_vaddr + (MCM_PORT_CONFIG_OFFSET >> 2), pcr);

	iounmap(mcm_vaddr);
पूर्ण


अटल पूर्णांक __init
smp_86xx_kick_cpu(पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक save_vector;
	अचिन्हित दीर्घ target, flags;
	पूर्णांक n = 0;
	अचिन्हित पूर्णांक *vector = (अचिन्हित पूर्णांक *)(KERNELBASE + 0x100);

	अगर (nr < 0 || nr >= NR_CPUS)
		वापस -ENOENT;

	pr_debug("smp_86xx_kick_cpu: kick CPU #%d\n", nr);

	local_irq_save(flags);

	/* Save reset vector */
	save_vector = *vector;

	/* Setup fake reset vector to call __secondary_start_mpc86xx. */
	target = (अचिन्हित दीर्घ) __secondary_start_mpc86xx;
	patch_branch((काष्ठा ppc_inst *)vector, target, BRANCH_SET_LINK);

	/* Kick that CPU */
	smp_86xx_release_core(nr);

	/* Wait a bit क्रम the CPU to take the exception. */
	जबतक ((__secondary_hold_acknowledge != nr) && (n++, n < 1000))
		mdelay(1);

	/* Restore the exception vector */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)vector, ppc_inst(save_vector));

	local_irq_restore(flags);

	pr_debug("wait CPU #%d for %d msecs.\n", nr, n);

	वापस 0;
पूर्ण


अटल व्योम __init
smp_86xx_setup_cpu(पूर्णांक cpu_nr)
अणु
	mpic_setup_this_cpu();
पूर्ण


काष्ठा smp_ops_t smp_86xx_ops = अणु
	.cause_nmi_ipi = शून्य,
	.message_pass = smp_mpic_message_pass,
	.probe = smp_mpic_probe,
	.kick_cpu = smp_86xx_kick_cpu,
	.setup_cpu = smp_86xx_setup_cpu,
	.take_समयbase = smp_generic_take_समयbase,
	.give_समयbase = smp_generic_give_समयbase,
पूर्ण;


व्योम __init
mpc86xx_smp_init(व्योम)
अणु
	smp_ops = &smp_86xx_ops;
पूर्ण
