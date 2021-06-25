<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Board setup routines क्रम the Emerson/Artesyn MVME2500
 *
 * Copyright 2014 Elettra-Sincrotrone Trieste S.C.p.A.
 *
 * Based on earlier code by:
 *
 *	Xianghua Xiao (x.xiao@मुक्तscale.com)
 *	Tom Armistead (tom.armistead@emerson.com)
 *	Copyright 2012 Emerson
 *
 * Author Alessio Igor Bogani <alessio.bogani@elettra.eu>
 */

#समावेश <linux/pci.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

व्योम __init mvme2500_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0,
		  MPIC_BIG_ENDIAN | MPIC_SINGLE_DEST_CPU,
		0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init mvme2500_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mvme2500_setup_arch()", 0);
	fsl_pci_assign_primary();
	pr_info("MVME2500 board from Artesyn\n");
पूर्ण

machine_arch_initcall(mvme2500, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mvme2500_probe(व्योम)
अणु
	वापस of_machine_is_compatible("artesyn,MVME2500");
पूर्ण

define_machine(mvme2500) अणु
	.name			= "MVME2500",
	.probe			= mvme2500_probe,
	.setup_arch		= mvme2500_setup_arch,
	.init_IRQ		= mvme2500_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
