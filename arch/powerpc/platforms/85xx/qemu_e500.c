<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Paravirt target क्रम a generic QEMU e500 machine
 *
 * This is पूर्णांकended to be a flexible device-tree-driven platक्रमm, not fixed
 * to a particular piece of hardware or a particular spec of भव hardware,
 * beyond the assumption of an e500-family CPU.  Some things are still hardcoded
 * here, such as MPIC, but this is a limitation of the current code rather than
 * an पूर्णांकerface contract with QEMU.
 *
 * Copyright 2012 Freescale Semiconductor Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"
#समावेश "mpc85xx.h"

व्योम __init qemu_e500_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
	अचिन्हित पूर्णांक flags = MPIC_BIG_ENDIAN | MPIC_SINGLE_DEST_CPU |
		MPIC_ENABLE_COREINT;

	mpic = mpic_alloc(शून्य, 0, flags, 0, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

अटल व्योम __init qemu_e500_setup_arch(व्योम)
अणु
	ppc_md.progress("qemu_e500_setup_arch()", 0);

	fsl_pci_assign_primary();
	swiotlb_detect_4g();
	mpc85xx_smp_init();
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init qemu_e500_probe(व्योम)
अणु
	वापस !!of_machine_is_compatible("fsl,qemu-e500");
पूर्ण

machine_arch_initcall(qemu_e500, mpc85xx_common_publish_devices);

define_machine(qemu_e500) अणु
	.name			= "QEMU e500",
	.probe			= qemu_e500_probe,
	.setup_arch		= qemu_e500_setup_arch,
	.init_IRQ		= qemu_e500_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_coreपूर्णांक_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
