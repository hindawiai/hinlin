<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * C293PCIE Board Setup
 *
 * Copyright 2013 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

व्योम __init c293_pcie_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGLE_DEST_CPU, 0, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);

	mpic_init(mpic);
पूर्ण


/*
 * Setup the architecture
 */
अटल व्योम __init c293_pcie_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("c293_pcie_setup_arch()", 0);

	fsl_pci_assign_primary();

	prपूर्णांकk(KERN_INFO "C293 PCIE board from Freescale Semiconductor\n");
पूर्ण

machine_arch_initcall(c293_pcie, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init c293_pcie_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,C293PCIE"))
		वापस 1;
	वापस 0;
पूर्ण

define_machine(c293_pcie) अणु
	.name			= "C293 PCIE",
	.probe			= c293_pcie_probe,
	.setup_arch		= c293_pcie_setup_arch,
	.init_IRQ		= c293_pcie_pic_init,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
