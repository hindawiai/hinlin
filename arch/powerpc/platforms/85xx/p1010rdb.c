<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * P1010RDB Board Setup
 *
 * Copyright 2011 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

व्योम __init p1010_rdb_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGLE_DEST_CPU,
	  0, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);

	mpic_init(mpic);
पूर्ण


/*
 * Setup the architecture
 */
अटल व्योम __init p1010_rdb_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("p1010_rdb_setup_arch()", 0);

	fsl_pci_assign_primary();

	prपूर्णांकk(KERN_INFO "P1010 RDB board from Freescale Semiconductor\n");
पूर्ण

machine_arch_initcall(p1010_rdb, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init p1010_rdb_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,P1010RDB"))
		वापस 1;
	अगर (of_machine_is_compatible("fsl,P1010RDB-PB"))
		वापस 1;
	वापस 0;
पूर्ण

define_machine(p1010_rdb) अणु
	.name			= "P1010 RDB",
	.probe			= p1010_rdb_probe,
	.setup_arch		= p1010_rdb_setup_arch,
	.init_IRQ		= p1010_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
