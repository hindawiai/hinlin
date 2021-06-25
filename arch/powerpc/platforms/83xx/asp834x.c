<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/asp834x.c
 *
 * Analogue & Micro ASP8347 board specअगरic routines
 * clone of mpc834x_itx
 *
 * Copyright 2008 Codehermit
 *
 * Maपूर्णांकainer: Bryan O'Donoghue <boकरोnoghue@codhermit.ie>
 */

#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/udbg.h>

#समावेश "mpc83xx.h"

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init asp834x_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();
	mpc834x_usb_cfg();
पूर्ण

machine_device_initcall(asp834x, mpc83xx_declare_of_platक्रमm_devices);

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init asp834x_probe(व्योम)
अणु
	वापस of_machine_is_compatible("analogue-and-micro,asp8347e");
पूर्ण

define_machine(asp834x) अणु
	.name			= "ASP8347E",
	.probe			= asp834x_probe,
	.setup_arch		= asp834x_setup_arch,
	.discover_phbs		= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
