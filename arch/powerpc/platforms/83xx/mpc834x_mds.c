<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/83xx/mpc834x_mds.c
 *
 * MPC834x MDS board specअगरic routines
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

#घोषणा BCSR5_INT_USB		0x02
अटल पूर्णांक mpc834xemds_usb_cfg(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *bcsr_regs = शून्य;
	u8 bcsr5;

	mpc834x_usb_cfg();
	/* Map BCSR area */
	np = of_find_node_by_name(शून्य, "bcsr");
	अगर (np) अणु
		काष्ठा resource res;

		of_address_to_resource(np, 0, &res);
		bcsr_regs = ioremap(res.start, resource_size(&res));
		of_node_put(np);
	पूर्ण
	अगर (!bcsr_regs)
		वापस -1;

	/*
	 * अगर Processor Board is plugged पूर्णांकo PIB board,
	 * क्रमce to use the PHY on Processor Board
	 */
	bcsr5 = in_8(bcsr_regs + 5);
	अगर (!(bcsr5 & BCSR5_INT_USB))
		out_8(bcsr_regs + 5, (bcsr5 | BCSR5_INT_USB));
	iounmap(bcsr_regs);
	वापस 0;
पूर्ण

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc834x_mds_setup_arch(व्योम)
अणु
	mpc83xx_setup_arch();

	mpc834xemds_usb_cfg();
पूर्ण

machine_device_initcall(mpc834x_mds, mpc83xx_declare_of_platक्रमm_devices);

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc834x_mds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC834xMDS");
पूर्ण

define_machine(mpc834x_mds) अणु
	.name			= "MPC834x MDS",
	.probe			= mpc834x_mds_probe,
	.setup_arch		= mpc834x_mds_setup_arch,
	.discover_phbs  	= mpc83xx_setup_pci,
	.init_IRQ		= mpc83xx_ipic_init_IRQ,
	.get_irq		= ipic_get_irq,
	.restart		= mpc83xx_restart,
	.समय_init		= mpc83xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
