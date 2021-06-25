<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc831x_rdb.c
 *
 * Description: MPC831x RDB board specअगरic routines.
 * This file is based on mpc834x_sys.c
 * Author: Lo Wlison <r43300@मुक्तscale.com>
 *
 * Copyright (C) Freescale Semiconductor, Inc. 2006. All rights reserved.
 */

#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

/*
 * Setup the architecture
 */
अटल व्योम __init mpc831x_rdb_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
	mpc831x_usb_cfg();
पूर्ण

अटल स्थिर अक्षर *board[] __initdata = अणु
	"MPC8313ERDB",
	"fsl,mpc8315erdb",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc831x_rdb_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

machine_device_initcall(mpc831x_rdb, mpc83xx_declare_of_platक्रमm_devices);

define_machine(mpc831x_rdb) अणु
	.name			= "MPC831x RDB",
	.probe			= mpc831x_rdb_probe,
	.setup_arch		= mpc831x_rdb_setup_arch,
	.discover_phbs		= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
