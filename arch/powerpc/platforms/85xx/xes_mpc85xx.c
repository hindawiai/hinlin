<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Extreme Engineering Solutions, Inc.
 *
 * X-ES board-specअगरic functionality
 *
 * Based on mpc85xx_ds code from Freescale Semiconductor, Inc.
 *
 * Author: Nate Case <nहाल@xes-inc.com>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
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
#समावेश "smp.h"

#समावेश "mpc85xx.h"

/* A few bit definitions needed क्रम fixups on some boards */
#घोषणा MPC85xx_L2CTL_L2E		0x80000000 /* L2 enable */
#घोषणा MPC85xx_L2CTL_L2I		0x40000000 /* L2 flash invalidate */
#घोषणा MPC85xx_L2CTL_L2SIZ_MASK	0x30000000 /* L2 SRAM size (R/O) */

व्योम __init xes_mpc85xx_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

अटल व्योम xes_mpc85xx_configure_l2(व्योम __iomem *l2_base)
अणु
	अस्थिर uपूर्णांक32_t ctl, पंचांगp;

	यंत्र अस्थिर("msync; isync");
	पंचांगp = in_be32(l2_base);

	/*
	 * xMon may have enabled part of L2 as SRAM, so we need to set it
	 * up क्रम all cache mode just to be safe.
	 */
	prपूर्णांकk(KERN_INFO "xes_mpc85xx: Enabling L2 as cache\n");

	ctl = MPC85xx_L2CTL_L2E | MPC85xx_L2CTL_L2I;
	अगर (of_machine_is_compatible("MPC8540") ||
	    of_machine_is_compatible("MPC8560"))
		/*
		 * Assume L2 SRAM is used fully क्रम cache, so set
		 * L2BLKSZ (bits 4:5) to match L2SIZ (bits 2:3).
		 */
		ctl |= (पंचांगp & MPC85xx_L2CTL_L2SIZ_MASK) >> 2;

	यंत्र अस्थिर("msync; isync");
	out_be32(l2_base, ctl);
	यंत्र अस्थिर("msync; isync");
पूर्ण

अटल व्योम xes_mpc85xx_fixups(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक err;

	/*
	 * Legacy xMon firmware on some X-ES boards करोes not enable L2
	 * as cache.  We must ensure that they get enabled here.
	 */
	क्रम_each_node_by_name(np, "l2-cache-controller") अणु
		काष्ठा resource r[2];
		व्योम __iomem *l2_base;

		/* Only MPC8548, MPC8540, and MPC8560 boards are affected */
		अगर (!of_device_is_compatible(np,
				    "fsl,mpc8548-l2-cache-controller") &&
		    !of_device_is_compatible(np,
				    "fsl,mpc8540-l2-cache-controller") &&
		    !of_device_is_compatible(np,
				    "fsl,mpc8560-l2-cache-controller"))
			जारी;

		err = of_address_to_resource(np, 0, &r[0]);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING "xes_mpc85xx: Could not get "
			       "resource for device tree node '%pOF'",
			       np);
			जारी;
		पूर्ण

		l2_base = ioremap(r[0].start, resource_size(&r[0]));

		xes_mpc85xx_configure_l2(l2_base);
	पूर्ण
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init xes_mpc85xx_setup_arch(व्योम)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model = "Unknown";

	root = of_find_node_by_path("/");
	अगर (root == शून्य)
		वापस;

	model = of_get_property(root, "model", शून्य);

	prपूर्णांकk(KERN_INFO "X-ES MPC85xx-based single-board computer: %s\n",
	       model + म_माप("xes,"));

	xes_mpc85xx_fixups();

	mpc85xx_smp_init();

	fsl_pci_assign_primary();
पूर्ण

machine_arch_initcall(xes_mpc8572, mpc85xx_common_publish_devices);
machine_arch_initcall(xes_mpc8548, mpc85xx_common_publish_devices);
machine_arch_initcall(xes_mpc8540, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init xes_mpc8572_probe(व्योम)
अणु
	वापस of_machine_is_compatible("xes,MPC8572");
पूर्ण

अटल पूर्णांक __init xes_mpc8548_probe(व्योम)
अणु
	वापस of_machine_is_compatible("xes,MPC8548");
पूर्ण

अटल पूर्णांक __init xes_mpc8540_probe(व्योम)
अणु
	वापस of_machine_is_compatible("xes,MPC8540");
पूर्ण

define_machine(xes_mpc8572) अणु
	.name			= "X-ES MPC8572",
	.probe			= xes_mpc8572_probe,
	.setup_arch		= xes_mpc85xx_setup_arch,
	.init_IRQ		= xes_mpc85xx_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(xes_mpc8548) अणु
	.name			= "X-ES MPC8548",
	.probe			= xes_mpc8548_probe,
	.setup_arch		= xes_mpc85xx_setup_arch,
	.init_IRQ		= xes_mpc85xx_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(xes_mpc8540) अणु
	.name			= "X-ES MPC8540",
	.probe			= xes_mpc8540_probe,
	.setup_arch		= xes_mpc85xx_setup_arch,
	.init_IRQ		= xes_mpc85xx_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
