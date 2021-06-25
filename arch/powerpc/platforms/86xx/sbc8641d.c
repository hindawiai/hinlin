<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SBC8641D board specअगरic routines
 *
 * Copyright 2008 Wind River Systems Inc.
 *
 * By Paul Gorपंचांगaker (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Based largely on the 8641 HPCN support by Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_pci.h>
#समावेश <sysdev/fsl_soc.h>

#समावेश "mpc86xx.h"

अटल व्योम __init
sbc8641_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("sbc8641_setup_arch()", 0);

	prपूर्णांकk("SBC8641 board from Wind River\n");

#अगर_घोषित CONFIG_SMP
	mpc86xx_smp_init();
#पूर्ण_अगर

	fsl_pci_assign_primary();
पूर्ण


अटल व्योम
sbc8641_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Wind River Systems\n");

	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);
पूर्ण


/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init sbc8641_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("wind,sbc8641"))
		वापस 1;	/* Looks good */

	वापस 0;
पूर्ण

machine_arch_initcall(sbc8641, mpc86xx_common_publish_devices);

define_machine(sbc8641) अणु
	.name			= "SBC8641D",
	.probe			= sbc8641_probe,
	.setup_arch		= sbc8641_setup_arch,
	.init_IRQ		= mpc86xx_init_irq,
	.show_cpuinfo		= sbc8641_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.समय_init		= mpc86xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
पूर्ण;
