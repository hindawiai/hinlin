<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC8272 ADS board support
 *
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Based on code by Vitaly Bordug <vbordug@ru.mvista.com>
 * Copyright (c) 2006 MontaVista Software, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>

#समावेश <platक्रमms/82xx/pq2.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "pq2.h"

अटल व्योम __init mpc8272_ads_pic_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_compatible_node(शून्य, शून्य,
	                                                 "fsl,cpm2-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "PIC init: can not find fsl,cpm2-pic node\n");
		वापस;
	पूर्ण

	cpm2_pic_init(np);
	of_node_put(np);

	/* Initialize stuff क्रम the 82xx CPLD IC and install demux  */
	pq2ads_pci_init_irq();
पूर्ण

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin mpc8272_ads_pins[] = अणु
	/* SCC1 */
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC4 */
	अणु3, 21, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC1 */
	अणु0, 14, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 15, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 18, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 19, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 21, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 26, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 27, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 28, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 30, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 31, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु2, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC2 */
	अणु1, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 20, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 22, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 25, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 26, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 27, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु1, 30, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 31, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* I2C */
	अणु3, 14, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_OPENDRAINपूर्ण,
	अणु3, 15, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_OPENDRAINपूर्ण,

	/* USB */
	अणु2, 10, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 11, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 24, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 25, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mpc8272_ads_pins); i++) अणु
		काष्ठा cpm_pin *pin = &mpc8272_ads_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC3, CPM_CLK8, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC3, CPM_CLK8, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC4, CPM_BRG4, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC4, CPM_BRG4, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK11, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK10, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK15, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK16, CPM_CLK_TX);
पूर्ण

अटल व्योम __init mpc8272_ads_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;
	__be32 __iomem *bcsr;

	अगर (ppc_md.progress)
		ppc_md.progress("mpc8272_ads_setup_arch()", 0);

	cpm2_reset();

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8272ads-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "No bcsr in device tree\n");
		वापस;
	पूर्ण

	bcsr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!bcsr) अणु
		prपूर्णांकk(KERN_ERR "Cannot map BCSR registers\n");
		वापस;
	पूर्ण

#घोषणा BCSR1_FETHIEN		0x08000000
#घोषणा BCSR1_FETH_RST		0x04000000
#घोषणा BCSR1_RS232_EN1		0x02000000
#घोषणा BCSR1_RS232_EN2		0x01000000
#घोषणा BCSR3_USB_nEN		0x80000000
#घोषणा BCSR3_FETHIEN2		0x10000000
#घोषणा BCSR3_FETH2_RST		0x08000000

	clrbits32(&bcsr[1], BCSR1_RS232_EN1 | BCSR1_RS232_EN2 | BCSR1_FETHIEN);
	setbits32(&bcsr[1], BCSR1_FETH_RST);

	clrbits32(&bcsr[3], BCSR3_FETHIEN2);
	setbits32(&bcsr[3], BCSR3_FETH2_RST);

	clrbits32(&bcsr[3], BCSR3_USB_nEN);

	iounmap(bcsr);

	init_ioports();

	अगर (ppc_md.progress)
		ppc_md.progress("mpc8272_ads_setup_arch(), finish", 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .name = "soc", पूर्ण,
	अणु .name = "cpm", पूर्ण,
	अणु .name = "localbus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	/* Publish the QE devices */
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);
	वापस 0;
पूर्ण
machine_device_initcall(mpc8272_ads, declare_of_platक्रमm_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc8272_ads_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,mpc8272ads");
पूर्ण

define_machine(mpc8272_ads)
अणु
	.name = "Freescale MPC8272 ADS",
	.probe = mpc8272_ads_probe,
	.setup_arch = mpc8272_ads_setup_arch,
	.discover_phbs = pq2_init_pci,
	.init_IRQ = mpc8272_ads_pic_init,
	.get_irq = cpm2_get_irq,
	.calibrate_decr = generic_calibrate_decr,
	.restart = pq2_restart,
	.progress = udbg_progress,
पूर्ण;
