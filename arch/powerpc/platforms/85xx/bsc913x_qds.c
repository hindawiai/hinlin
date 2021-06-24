<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BSC913xQDS Board Setup
 *
 * Author:
 *   Harninder Rai <harninder.rai@मुक्तscale.com>
 *   Priyanka Jain <Priyanka.Jain@मुक्तscale.com>
 *
 * Copyright 2014 Freescale Semiconductor Inc.
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/mpic.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <यंत्र/udbg.h>

#समावेश "mpc85xx.h"
#समावेश "smp.h"

व्योम __init bsc913x_qds_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGLE_DEST_CPU,
	  0, 256, " OpenPIC  ");

	अगर (!mpic)
		pr_err("bsc913x: Failed to allocate MPIC structure\n");
	अन्यथा
		mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init bsc913x_qds_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("bsc913x_qds_setup_arch()", 0);

#अगर defined(CONFIG_SMP)
	mpc85xx_smp_init();
#पूर्ण_अगर

	fsl_pci_assign_primary();

	pr_info("bsc913x board from Freescale Semiconductor\n");
पूर्ण

machine_arch_initcall(bsc9132_qds, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */

अटल पूर्णांक __init bsc9132_qds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,bsc9132qds");
पूर्ण

define_machine(bsc9132_qds) अणु
	.name			= "BSC9132 QDS",
	.probe			= bsc9132_qds_probe,
	.setup_arch		= bsc913x_qds_setup_arch,
	.init_IRQ		= bsc913x_qds_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
