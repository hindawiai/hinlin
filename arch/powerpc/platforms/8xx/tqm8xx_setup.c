<शैली गुरु>
/*
 * Platक्रमm setup क्रम the MPC8xx based boards from TQM.
 *
 * Heiko Schocher <hs@denx.de>
 * Copyright 2010 DENX Software Engineering GmbH
 *
 * based on:
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
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>

#समावेश <linux/fs_enet_pd.h>
#समावेश <linux/fs_uart_pd.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/mii.h>
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

#समावेश "mpc8xx.h"

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin tqm8xx_pins[] __initdata = अणु
	/* SMC1 */
	अणुCPM_PORTB, 24, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

	/* SCC1 */
	अणुCPM_PORTA, 5, CPM_PIN_INPUTपूर्ण, /* CLK1 */
	अणुCPM_PORTA, 7, CPM_PIN_INPUTपूर्ण, /* CLK2 */
	अणुCPM_PORTA, 14, CPM_PIN_INPUTपूर्ण, /* TX */
	अणुCPM_PORTA, 15, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTC, 15, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TENA */
	अणुCPM_PORTC, 10, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण,
	अणुCPM_PORTC, 11, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण,
पूर्ण;

अटल काष्ठा cpm_pin tqm8xx_fec_pins[] __initdata = अणु
	/* MII */
	अणुCPM_PORTD, 3, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 4, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 5, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 6, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 7, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 8, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 9, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 10, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 11, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 12, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 13, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 14, CPM_PIN_OUTPUTपूर्ण,
	अणुCPM_PORTD, 15, CPM_PIN_OUTPUTपूर्ण,
पूर्ण;

अटल व्योम __init init_pins(पूर्णांक n, काष्ठा cpm_pin *pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		cpm1_set_pin(pin->port, pin->pin, pin->flags);
		pin++;
	पूर्ण
पूर्ण

अटल व्योम __init init_ioports(व्योम)
अणु
	काष्ठा device_node *dnode;
	काष्ठा property *prop;
	पूर्णांक	len;

	init_pins(ARRAY_SIZE(tqm8xx_pins), &tqm8xx_pins[0]);

	cpm1_clk_setup(CPM_CLK_SMC1, CPM_BRG1, CPM_CLK_RTX);

	dnode = of_find_node_by_name(शून्य, "aliases");
	अगर (dnode == शून्य)
		वापस;
	prop = of_find_property(dnode, "ethernet1", &len);
	अगर (prop == शून्य)
		वापस;

	/* init FEC pins */
	init_pins(ARRAY_SIZE(tqm8xx_fec_pins), &tqm8xx_fec_pins[0]);
पूर्ण

अटल व्योम __init tqm8xx_setup_arch(व्योम)
अणु
	cpm_reset();
	init_ioports();
पूर्ण

अटल पूर्णांक __init tqm8xx_probe(व्योम)
अणु
	वापस of_machine_is_compatible("tqc,tqm8xx");
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .name = "soc", पूर्ण,
	अणु .name = "cpm", पूर्ण,
	अणु .name = "localbus", पूर्ण,
	अणु .compatible = "simple-bus" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(tqm8xx, declare_of_platक्रमm_devices);

define_machine(tqm8xx) अणु
	.name			= "TQM8xx",
	.probe			= tqm8xx_probe,
	.setup_arch		= tqm8xx_setup_arch,
	.init_IRQ		= mpc8xx_pics_init,
	.get_irq		= mpc8xx_get_irq,
	.restart		= mpc8xx_restart,
	.calibrate_decr		= mpc8xx_calibrate_decr,
	.set_rtc_समय		= mpc8xx_set_rtc_समय,
	.get_rtc_समय		= mpc8xx_get_rtc_समय,
	.progress		= udbg_progress,
पूर्ण;
