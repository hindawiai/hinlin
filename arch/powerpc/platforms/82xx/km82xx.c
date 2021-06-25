<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Keymile km82xx support
 * Copyright 2008-2011 DENX Software Engineering GmbH
 * Author: Heiko Schocher <hs@denx.de>
 *
 * based on code from:
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/mpc8260.h>
#समावेश <यंत्र/prom.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "pq2.h"

अटल व्योम __init km82xx_pic_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_compatible_node(शून्य, शून्य,
							"fsl,pq2-pic");
	अगर (!np) अणु
		pr_err("PIC init: can not find cpm-pic node\n");
		वापस;
	पूर्ण

	cpm2_pic_init(np);
	of_node_put(np);
पूर्ण

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल __initdata काष्ठा cpm_pin km82xx_pins[] = अणु
	/* SMC1 */
	अणु2, 4, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 5, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SMC2 */
	अणु0, 8, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 9, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC1 */
	अणु2, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 15, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,

	/* SCC4 */
	अणु2, 25, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 24, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2,  9, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2,  8, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 21, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,

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

	अणु2, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 23, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

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

	/* MDC */
	अणु0, 13, CPM_PIN_OUTPUT | CPM_PIN_GPIOपूर्ण,

#अगर defined(CONFIG_I2C_CPM)
	/* I2C */
	अणु3, 14, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_OPENDRAINपूर्ण,
	अणु3, 15, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_OPENDRAINपूर्ण,
#पूर्ण_अगर

	/* USB */
	अणु0, 10, CPM_PIN_OUTPUT | CPM_PIN_GPIOपूर्ण,    /* FULL_SPEED */
	अणु0, 11, CPM_PIN_OUTPUT | CPM_PIN_GPIOपूर्ण,    /*/SLAVE */
	अणु2, 10, CPM_PIN_INPUT  | CPM_PIN_PRIMARYपूर्ण, /* RXN */
	अणु2, 11, CPM_PIN_INPUT  | CPM_PIN_PRIMARYपूर्ण, /* RXP */
	अणु2, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण, /* /OE */
	अणु2, 27, CPM_PIN_INPUT  | CPM_PIN_PRIMARYपूर्ण, /* RXCLK */
	अणु3, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण, /* TXP */
	अणु3, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण, /* TXN */
	अणु3, 25, CPM_PIN_INPUT  | CPM_PIN_PRIMARYपूर्ण, /* RXD */

	/* SPI */
	अणु3, 16, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,/* SPI_MISO PD16 */
	अणु3, 17, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,/* SPI_MOSI PD17 */
	अणु3, 18, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,/* SPI_CLK PD18 */
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(km82xx_pins); i++) अणु
		स्थिर काष्ठा cpm_pin *pin = &km82xx_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_smc_clk_setup(CPM_CLK_SMC2, CPM_BRG8);
	cpm2_smc_clk_setup(CPM_CLK_SMC1, CPM_BRG7);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_CLK11, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_CLK11, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC3, CPM_CLK5, CPM_CLK_RTX);
	cpm2_clk_setup(CPM_CLK_SCC4, CPM_CLK7, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC4, CPM_CLK8, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK10, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK9,  CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK13, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK14, CPM_CLK_TX);

	/* Force USB FULL SPEED bit to '1' */
	setbits32(&cpm2_immr->im_ioport.iop_pdata, 1 << (31 - 10));
	/* clear USB_SLAVE */
	clrbits32(&cpm2_immr->im_ioport.iop_pdata, 1 << (31 - 11));
पूर्ण

अटल व्योम __init km82xx_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("km82xx_setup_arch()", 0);

	cpm2_reset();

	/* When this is set, snooping CPM DMA from RAM causes
	 * machine checks.  See erratum SIU18.
	 */
	clrbits32(&cpm2_immr->im_siu_conf.siu_82xx.sc_bcr, MPC82XX_BCR_PLDP);

	init_ioports();

	अगर (ppc_md.progress)
		ppc_md.progress("km82xx_setup_arch(), finish", 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(km82xx, declare_of_platक्रमm_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init km82xx_probe(व्योम)
अणु
	वापस of_machine_is_compatible("keymile,km82xx");
पूर्ण

define_machine(km82xx)
अणु
	.name = "Keymile km82xx",
	.probe = km82xx_probe,
	.setup_arch = km82xx_setup_arch,
	.init_IRQ = km82xx_pic_init,
	.get_irq = cpm2_get_irq,
	.calibrate_decr = generic_calibrate_decr,
	.restart = pq2_restart,
	.progress = udbg_progress,
पूर्ण;
