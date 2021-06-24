<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007, 2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: John Rigby, <jrigby@मुक्तscale.com>, Thur Mar 29 2007
 *
 * Description:
 * MPC5121 ADS board setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>

#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc512x.h"
#समावेश "mpc5121_ads.h"

अटल व्योम __init mpc5121_ads_setup_arch(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "MPC5121 ADS board from Freescale Semiconductor\n");
	/*
	 * cpld regs are needed early
	 */
	mpc5121_ads_cpld_map();

	mpc512x_setup_arch();
पूर्ण

अटल व्योम __init mpc5121_ads_setup_pci(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, "pci", "fsl,mpc5121-pci")
		mpc83xx_add_bridge(np);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init mpc5121_ads_init_IRQ(व्योम)
अणु
	mpc512x_init_IRQ();
	mpc5121_ads_cpld_pic_init();
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc5121_ads_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("fsl,mpc5121ads"))
		वापस 0;

	mpc512x_init_early();

	वापस 1;
पूर्ण

define_machine(mpc5121_ads) अणु
	.name			= "MPC5121 ADS",
	.probe			= mpc5121_ads_probe,
	.setup_arch		= mpc5121_ads_setup_arch,
	.discover_phbs		= mpc5121_ads_setup_pci,
	.init			= mpc512x_init,
	.init_IRQ		= mpc5121_ads_init_IRQ,
	.get_irq		= ipic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.restart		= mpc512x_restart,
पूर्ण;
