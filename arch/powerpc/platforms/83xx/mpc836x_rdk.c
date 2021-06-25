<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC8360E-RDK board file.
 *
 * Copyright (c) 2006  Freescale Semiconductor, Inc.
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

machine_device_initcall(mpc836x_rdk, mpc83xx_declare_of_platक्रमm_devices);

अटल व्योम __init mpc836x_rdk_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened.
 */
अटल पूर्णांक __init mpc836x_rdk_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,mpc8360rdk");
पूर्ण

define_machine(mpc836x_rdk) अणु
	.name		= "MPC836x RDK",
	.probe		= mpc836x_rdk_probe,
	.setup_arch	= mpc836x_rdk_setup_arch,
	.discover_phbs  = mpc83xx_setup_pci,
	.init_IRQ	= mpc83xx_ipic_init_IRQ,
	.get_irq	= ipic_get_irq,
	.restart	= mpc83xx_restart,
	.समय_init	= mpc83xx_समय_init,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
