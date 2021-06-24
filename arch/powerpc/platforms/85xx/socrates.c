<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2008 Emcraft Systems
 * Sergei Poselenov <sposelenov@emcraft.com>
 *
 * Based on MPC8560 ADS and arch/ppc tqm85xx ports
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 *
 * Copyright (c) 2005-2006 DENX Software Engineering
 * Stefan Roese <sr@denx.de>
 *
 * Based on original work by
 * 	Kumar Gala <kumar.gala@मुक्तscale.com>
 *      Copyright 2004 Freescale Semiconductor Inc.
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
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"
#समावेश "socrates_fpga_pic.h"

अटल व्योम __init socrates_pic_init(व्योम)
अणु
	काष्ठा device_node *np;

	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);

	np = of_find_compatible_node(शून्य, शून्य, "abb,socrates-fpga-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "Could not find socrates-fpga-pic node\n");
		वापस;
	पूर्ण
	socrates_fpga_pic_init(np);
	of_node_put(np);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init socrates_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("socrates_setup_arch()", 0);

	fsl_pci_assign_primary();
पूर्ण

machine_arch_initcall(socrates, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init socrates_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("abb,socrates"))
		वापस 1;

	वापस 0;
पूर्ण

define_machine(socrates) अणु
	.name			= "Socrates",
	.probe			= socrates_probe,
	.setup_arch		= socrates_setup_arch,
	.init_IRQ		= socrates_pic_init,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
