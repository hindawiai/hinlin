<शैली गुरु>
/*
 * Platक्रमm setup क्रम the Freescale mpc885ads board
 *
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * Copyright 2005 MontaVista Software Inc.
 *
 * Heavily modअगरied by Scott Wood <scottwood@मुक्तscale.com>
 * Copyright 2007 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>

#समावेश <linux/fs_enet_pd.h>
#समावेश <linux/fs_uart_pd.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/mii.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/cpm1.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <यंत्र/udbg.h>

#समावेश "mpc885ads.h"
#समावेश "mpc8xx.h"

अटल u32 __iomem *bcsr, *bcsr5;

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin mpc885ads_pins[] = अणु
	/* SMC1 */
	अणुCPM_PORTB, 24, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

	/* SMC2 */
#अगर_अघोषित CONFIG_MPC8xx_SECOND_ETH_FEC2
	अणुCPM_PORTE, 21, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTE, 20, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */
#पूर्ण_अगर

	/* SCC3 */
	अणुCPM_PORTA, 9, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTA, 8, CPM_PIN_INPUTपूर्ण, /* TX */
	अणुCPM_PORTC, 4, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* RENA */
	अणुCPM_PORTC, 5, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* CLSN */
	अणुCPM_PORTE, 27, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TENA */
	अणुCPM_PORTE, 17, CPM_PIN_INPUTपूर्ण, /* CLK5 */
	अणुCPM_PORTE, 16, CPM_PIN_INPUTपूर्ण, /* CLK6 */

	/* MII1 */
	अणुCPM_PORTA, 0, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTA, 1, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTA, 2, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTA, 3, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTA, 4, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTA, 10, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTA, 11, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTB, 19, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTB, 31, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTC, 12, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTC, 13, CPM_PIN_INPUTपूर्ण,
	अणुCPM_PORTE, 30, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 31, CPM_PIN_OUTPUTपूर्ण,

	/* MII2 */
#अगर_घोषित CONFIG_MPC8xx_SECOND_ETH_FEC2
	अणुCPM_PORTE, 14, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 15, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 16, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 17, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 18, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 19, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 20, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणुCPM_PORTE, 21, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 22, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 23, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 24, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 25, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 26, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 27, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 28, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTE, 29, CPM_PIN_OUTPUTपूर्ण,
#पूर्ण_अगर
	/* I2C */
	अणुCPM_PORTB, 26, CPM_PIN_INPUT | CPM_PIN_OPENDRAINपूर्ण,
	अणुCPM_PORTB, 27, CPM_PIN_INPUT | CPM_PIN_OPENDRAINपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mpc885ads_pins); i++) अणु
		काष्ठा cpm_pin *pin = &mpc885ads_pins[i];
		cpm1_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm1_clk_setup(CPM_CLK_SMC1, CPM_BRG1, CPM_CLK_RTX);
	cpm1_clk_setup(CPM_CLK_SMC2, CPM_BRG2, CPM_CLK_RTX);
	cpm1_clk_setup(CPM_CLK_SCC3, CPM_CLK5, CPM_CLK_TX);
	cpm1_clk_setup(CPM_CLK_SCC3, CPM_CLK6, CPM_CLK_RX);

	/* Set FEC1 and FEC2 to MII mode */
	clrbits32(&mpc8xx_immr->im_cpm.cp_cptr, 0x00000180);
पूर्ण

अटल व्योम __init mpc885ads_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;

	cpm_reset();
	init_ioports();

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc885ads-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_CRIT "Could not find fsl,mpc885ads-bcsr node\n");
		वापस;
	पूर्ण

	bcsr = of_iomap(np, 0);
	bcsr5 = of_iomap(np, 1);
	of_node_put(np);

	अगर (!bcsr || !bcsr5) अणु
		prपूर्णांकk(KERN_CRIT "Could not remap BCSR\n");
		वापस;
	पूर्ण

	clrbits32(&bcsr[1], BCSR1_RS232EN_1);
#अगर_घोषित CONFIG_MPC8xx_SECOND_ETH_FEC2
	setbits32(&bcsr[1], BCSR1_RS232EN_2);
#अन्यथा
	clrbits32(&bcsr[1], BCSR1_RS232EN_2);
#पूर्ण_अगर

	clrbits32(bcsr5, BCSR5_MII1_EN);
	setbits32(bcsr5, BCSR5_MII1_RST);
	udelay(1000);
	clrbits32(bcsr5, BCSR5_MII1_RST);

#अगर_घोषित CONFIG_MPC8xx_SECOND_ETH_FEC2
	clrbits32(bcsr5, BCSR5_MII2_EN);
	setbits32(bcsr5, BCSR5_MII2_RST);
	udelay(1000);
	clrbits32(bcsr5, BCSR5_MII2_RST);
#अन्यथा
	setbits32(bcsr5, BCSR5_MII2_EN);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MPC8xx_SECOND_ETH_SCC3
	clrbits32(&bcsr[4], BCSR4_ETH10_RST);
	udelay(1000);
	setbits32(&bcsr[4], BCSR4_ETH10_RST);

	setbits32(&bcsr[1], BCSR1_ETHEN);

	np = of_find_node_by_path("/soc@ff000000/cpm@9c0/serial@a80");
#अन्यथा
	np = of_find_node_by_path("/soc@ff000000/cpm@9c0/ethernet@a40");
#पूर्ण_अगर

	/* The SCC3 enet रेजिस्टरs overlap the SMC1 रेजिस्टरs, so
	 * one of the two must be हटाओd from the device tree.
	 */

	अगर (np) अणु
		of_detach_node(np);
		of_node_put(np);
	पूर्ण
पूर्ण

अटल पूर्णांक __init mpc885ads_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,mpc885ads");
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
machine_device_initcall(mpc885_ads, declare_of_platक्रमm_devices);

define_machine(mpc885_ads) अणु
	.name			= "Freescale MPC885 ADS",
	.probe			= mpc885ads_probe,
	.setup_arch		= mpc885ads_setup_arch,
	.init_IRQ		= mpc8xx_pics_init,
	.get_irq		= mpc8xx_get_irq,
	.restart		= mpc8xx_restart,
	.calibrate_decr		= mpc8xx_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
