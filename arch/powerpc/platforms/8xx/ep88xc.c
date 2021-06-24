<शैली गुरु>
/*
 * Platक्रमm setup क्रम the Embedded Planet EP88xC board
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 * Copyright 2007 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/cpm1.h>

#समावेश "mpc8xx.h"

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin ep88xc_pins[] = अणु
	/* SMC1 */
	अणु1, 24, CPM_PIN_INPUTपूर्ण, /* RX */
	अणु1, 25, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

	/* SCC2 */
	अणु0, 12, CPM_PIN_INPUTपूर्ण, /* TX */
	अणु0, 13, CPM_PIN_INPUTपूर्ण, /* RX */
	अणु2, 8, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* CD */
	अणु2, 9, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* CTS */
	अणु2, 14, CPM_PIN_INPUTपूर्ण, /* RTS */

	/* MII1 */
	अणु0, 0, CPM_PIN_INPUTपूर्ण,
	अणु0, 1, CPM_PIN_INPUTपूर्ण,
	अणु0, 2, CPM_PIN_INPUTपूर्ण,
	अणु0, 3, CPM_PIN_INPUTपूर्ण,
	अणु0, 4, CPM_PIN_OUTPUTपूर्ण,
	अणु0, 10, CPM_PIN_OUTPUTपूर्ण,
	अणु0, 11, CPM_PIN_OUTPUTपूर्ण,
	अणु1, 19, CPM_PIN_INPUTपूर्ण,
	अणु1, 31, CPM_PIN_INPUTपूर्ण,
	अणु2, 12, CPM_PIN_INPUTपूर्ण,
	अणु2, 13, CPM_PIN_INPUTपूर्ण,
	अणु3, 8, CPM_PIN_INPUTपूर्ण,
	अणु4, 30, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 31, CPM_PIN_OUTPUTपूर्ण,

	/* MII2 */
	अणु4, 14, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 15, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 16, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 17, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 18, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 19, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 20, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 21, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 22, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 23, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 24, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 25, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 26, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 27, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 28, CPM_PIN_OUTPUTपूर्ण,
	अणु4, 29, CPM_PIN_OUTPUTपूर्ण,

	/* USB */
	अणु0, 6, CPM_PIN_INPUTपूर्ण,  /* CLK2 */
	अणु0, 14, CPM_PIN_INPUTपूर्ण, /* USBOE */
	अणु0, 15, CPM_PIN_INPUTपूर्ण, /* USBRXD */
	अणु2, 6, CPM_PIN_OUTPUTपूर्ण, /* USBTXN */
	अणु2, 7, CPM_PIN_OUTPUTपूर्ण, /* USBTXP */
	अणु2, 10, CPM_PIN_INPUTपूर्ण, /* USBRXN */
	अणु2, 11, CPM_PIN_INPUTपूर्ण, /* USBRXP */

	/* Misc */
	अणु1, 26, CPM_PIN_INPUTपूर्ण, /* BRGO2 */
	अणु1, 27, CPM_PIN_INPUTपूर्ण, /* BRGO1 */
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ep88xc_pins); i++) अणु
		काष्ठा cpm_pin *pin = &ep88xc_pins[i];
		cpm1_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm1_clk_setup(CPM_CLK_SMC1, CPM_BRG1, CPM_CLK_RTX);
	cpm1_clk_setup(CPM_CLK_SCC1, CPM_CLK2, CPM_CLK_TX); /* USB */
	cpm1_clk_setup(CPM_CLK_SCC1, CPM_CLK2, CPM_CLK_RX);
	cpm1_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_TX);
	cpm1_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_RX);
पूर्ण

अटल u8 __iomem *ep88xc_bcsr;

#घोषणा BCSR7_SCC2_ENABLE 0x10

#घोषणा BCSR8_PHY1_ENABLE 0x80
#घोषणा BCSR8_PHY1_POWER  0x40
#घोषणा BCSR8_PHY2_ENABLE 0x20
#घोषणा BCSR8_PHY2_POWER  0x10

#घोषणा BCSR9_USB_ENABLE  0x80
#घोषणा BCSR9_USB_POWER   0x40
#घोषणा BCSR9_USB_HOST    0x20
#घोषणा BCSR9_USB_FULL_SPEED_TARGET 0x10

अटल व्योम __init ep88xc_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;

	cpm_reset();
	init_ioports();

	np = of_find_compatible_node(शून्य, शून्य, "fsl,ep88xc-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_CRIT "Could not find fsl,ep88xc-bcsr node\n");
		वापस;
	पूर्ण

	ep88xc_bcsr = of_iomap(np, 0);
	of_node_put(np);

	अगर (!ep88xc_bcsr) अणु
		prपूर्णांकk(KERN_CRIT "Could not remap BCSR\n");
		वापस;
	पूर्ण

	setbits8(&ep88xc_bcsr[7], BCSR7_SCC2_ENABLE);
	setbits8(&ep88xc_bcsr[8], BCSR8_PHY1_ENABLE | BCSR8_PHY1_POWER |
	                          BCSR8_PHY2_ENABLE | BCSR8_PHY2_POWER);
पूर्ण

अटल पूर्णांक __init ep88xc_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,ep88xc");
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
machine_device_initcall(ep88xc, declare_of_platक्रमm_devices);

define_machine(ep88xc) अणु
	.name = "Embedded Planet EP88xC",
	.probe = ep88xc_probe,
	.setup_arch = ep88xc_setup_arch,
	.init_IRQ = mpc8xx_pics_init,
	.get_irq	= mpc8xx_get_irq,
	.restart = mpc8xx_restart,
	.calibrate_decr = mpc8xx_calibrate_decr,
	.progress = udbg_progress,
पूर्ण;
