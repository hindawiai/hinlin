<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc837x_rdb.c
 *
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 *
 * MPC837x RDB board specअगरic routines
 */

#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

अटल व्योम mpc837x_rdb_sd_cfg(व्योम)
अणु
	व्योम __iomem *im;

	im = ioremap(get_immrbase(), 0x1000);
	अगर (!im) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/*
	 * On RDB boards (in contrast to MDS) USBB pins are used क्रम SD only,
	 * so we can safely mux them away from the USB block.
	 */
	clrsetbits_be32(im + MPC83XX_SICRL_OFFS, MPC837X_SICRL_USBB_MASK,
						 MPC837X_SICRL_SD);
	clrsetbits_be32(im + MPC83XX_SICRH_OFFS, MPC837X_SICRH_SPI_MASK,
						 MPC837X_SICRH_SD);
	iounmap(im);
पूर्ण

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc837x_rdb_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
	mpc837x_usb_cfg();
	mpc837x_rdb_sd_cfg();
पूर्ण

machine_device_initcall(mpc837x_rdb, mpc83xx_declare_of_platक्रमm_devices);

अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"fsl,mpc8377rdb",
	"fsl,mpc8378rdb",
	"fsl,mpc8379rdb",
	"fsl,mpc8377wlan",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc837x_rdb_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

define_machine(mpc837x_rdb) अणु
	.name			= "MPC837x RDB/WLAN",
	.probe			= mpc837x_rdb_probe,
	.setup_arch		= mpc837x_rdb_setup_arch,
	.discover_phbs  	= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
