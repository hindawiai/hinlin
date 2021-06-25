<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PQ2FADS board support
 *
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Loosely based on mp82xx ADS support by Vitaly Bordug <vbordug@ru.mvista.com>
 * Copyright (c) 2006 MontaVista Software, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "pq2ads.h"
#समावेश "pq2.h"

अटल व्योम __init pq2fads_pic_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm2-pic");
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

अटल काष्ठा cpm_pin pq2fads_pins[] = अणु
	/* SCC1 */
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC2 */
	अणु3, 27, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

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
	अणु2, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC3 */
	अणु1, 4, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 5, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 6, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 7, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 8, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 9, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 10, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 11, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 12, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 13, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 14, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 15, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pq2fads_pins); i++) अणु
		काष्ठा cpm_pin *pin = &pq2fads_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK13, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK14, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC3, CPM_CLK15, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC3, CPM_CLK16, CPM_CLK_TX);
पूर्ण

अटल व्योम __init pq2fads_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;
	__be32 __iomem *bcsr;

	अगर (ppc_md.progress)
		ppc_md.progress("pq2fads_setup_arch()", 0);

	cpm2_reset();

	np = of_find_compatible_node(शून्य, शून्य, "fsl,pq2fads-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "No fsl,pq2fads-bcsr in device tree\n");
		वापस;
	पूर्ण

	bcsr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!bcsr) अणु
		prपूर्णांकk(KERN_ERR "Cannot map BCSR registers\n");
		वापस;
	पूर्ण

	/* Enable the serial and ethernet ports */

	clrbits32(&bcsr[1], BCSR1_RS232_EN1 | BCSR1_RS232_EN2 | BCSR1_FETHIEN);
	setbits32(&bcsr[1], BCSR1_FETH_RST);

	clrbits32(&bcsr[3], BCSR3_FETHIEN2);
	setbits32(&bcsr[3], BCSR3_FETH2_RST);

	iounmap(bcsr);

	init_ioports();

	/* Enable बाह्यal IRQs */
	clrbits32(&cpm2_immr->im_siu_conf.siu_82xx.sc_siumcr, 0x0c000000);

	अगर (ppc_md.progress)
		ppc_md.progress("pq2fads_setup_arch(), finish", 0);
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init pq2fads_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,pq2fads");
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
machine_device_initcall(pq2fads, declare_of_platक्रमm_devices);

define_machine(pq2fads)
अणु
	.name = "Freescale PQ2FADS",
	.probe = pq2fads_probe,
	.setup_arch = pq2fads_setup_arch,
	.discover_phbs = pq2_init_pci,
	.init_IRQ = pq2fads_pic_init,
	.get_irq = cpm2_get_irq,
	.calibrate_decr = generic_calibrate_decr,
	.restart = pq2_restart,
	.progress = udbg_progress,
पूर्ण;
