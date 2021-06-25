<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007,2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: John Rigby, <jrigby@मुक्तscale.com>
 *
 * Description:
 * MPC512x SoC setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>

#समावेश "mpc512x.h"

/*
 * list of supported boards
 */
अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"prt,prtlvt",
	"fsl,mpc5125ads",
	"ifm,ac14xx",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc512x_generic_probe(व्योम)
अणु
	अगर (!of_device_compatible_match(of_root, board))
		वापस 0;

	mpc512x_init_early();

	वापस 1;
पूर्ण

define_machine(mpc512x_generic) अणु
	.name			= "MPC512x generic",
	.probe			= mpc512x_generic_probe,
	.init			= mpc512x_init,
	.setup_arch		= mpc512x_setup_arch,
	.init_IRQ		= mpc512x_init_IRQ,
	.get_irq		= ipic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.restart		= mpc512x_restart,
पूर्ण;
