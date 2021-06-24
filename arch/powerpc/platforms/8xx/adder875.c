<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Analogue & Micro Adder MPC875 board support
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/fs_enet_pd.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cpm1.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/prom.h>

#समावेश "mpc8xx.h"

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल __initdata काष्ठा cpm_pin adder875_pins[] = अणु
	/* SMC1 */
	अणुCPM_PORTB, 24, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

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
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adder875_pins); i++) अणु
		स्थिर काष्ठा cpm_pin *pin = &adder875_pins[i];
		cpm1_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm1_clk_setup(CPM_CLK_SMC1, CPM_BRG1, CPM_CLK_RTX);

	/* Set FEC1 and FEC2 to MII mode */
	clrbits32(&mpc8xx_immr->im_cpm.cp_cptr, 0x00000180);
पूर्ण

अटल व्योम __init adder875_setup(व्योम)
अणु
	cpm_reset();
	init_ioports();
पूर्ण

अटल पूर्णांक __init adder875_probe(व्योम)
अणु
	वापस of_machine_is_compatible("analogue-and-micro,adder875");
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
machine_device_initcall(adder875, declare_of_platक्रमm_devices);

define_machine(adder875) अणु
	.name = "Adder MPC875",
	.probe = adder875_probe,
	.setup_arch = adder875_setup,
	.init_IRQ = mpc8xx_pics_init,
	.get_irq = mpc8xx_get_irq,
	.restart = mpc8xx_restart,
	.calibrate_decr = generic_calibrate_decr,
	.progress = udbg_progress,
पूर्ण;
