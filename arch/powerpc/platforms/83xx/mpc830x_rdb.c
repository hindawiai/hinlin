<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc830x_rdb.c
 *
 * Description: MPC830x RDB board specअगरic routines.
 * This file is based on mpc831x_rdb.c
 *
 * Copyright (C) Freescale Semiconductor, Inc. 2009. All rights reserved.
 * Copyright (C) 2010. Ilya Yanok, Emcraft Systems, yanok@emcraft.com
 */

#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश "mpc83xx.h"

/*
 * Setup the architecture
 */
अटल व्योम __init mpc830x_rdb_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
	mpc831x_usb_cfg();
पूर्ण

अटल स्थिर अक्षर *board[] __initdata = अणु
	"MPC8308RDB",
	"fsl,mpc8308rdb",
	"denx,mpc8308_p1m",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc830x_rdb_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

machine_device_initcall(mpc830x_rdb, mpc83xx_declare_of_platक्रमm_devices);

define_machine(mpc830x_rdb) अणु
	.name			= "MPC830x RDB",
	.probe			= mpc830x_rdb_probe,
	.setup_arch		= mpc830x_rdb_setup_arch,
	.discover_phbs		= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
