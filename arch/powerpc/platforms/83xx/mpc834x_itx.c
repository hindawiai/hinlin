<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc834x_itx.c
 *
 * MPC834x ITX board specअगरic routines
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc83xx.h"

अटल स्थिर काष्ठा of_device_id mpc834x_itx_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,pq2pro-localbus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init mpc834x_itx_declare_of_platक्रमm_devices(व्योम)
अणु
	mpc83xx_declare_of_platक्रमm_devices();
	वापस of_platक्रमm_bus_probe(शून्य, mpc834x_itx_ids, शून्य);
पूर्ण
machine_device_initcall(mpc834x_itx, mpc834x_itx_declare_of_platक्रमm_devices);

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc834x_itx_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();

	mpc834x_usb_cfg();
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc834x_itx_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC834xMITX");
पूर्ण

define_machine(mpc834x_itx) अणु
	.name			= "MPC834x ITX",
	.probe			= mpc834x_itx_probe,
	.setup_arch		= mpc834x_itx_setup_arch,
	.discover_phbs  	= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
