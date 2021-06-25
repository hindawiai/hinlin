<शैली गुरु>
/*arch/घातerpc/platक्रमms/8xx/mpc86xads_setup.c
 *
 * Platक्रमm setup क्रम the Freescale mpc86xads board
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
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/cpm1.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <यंत्र/udbg.h>

#समावेश "mpc86xads.h"
#समावेश "mpc8xx.h"

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin mpc866ads_pins[] = अणु
	/* SMC1 */
	अणुCPM_PORTB, 24, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

	/* SMC2 */
	अणुCPM_PORTB, 21, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 20, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TX */

	/* SCC1 */
	अणुCPM_PORTA, 6, CPM_PIN_INPUTपूर्ण, /* CLK1 */
	अणुCPM_PORTA, 7, CPM_PIN_INPUTपूर्ण, /* CLK2 */
	अणुCPM_PORTA, 14, CPM_PIN_INPUTपूर्ण, /* TX */
	अणुCPM_PORTA, 15, CPM_PIN_INPUTपूर्ण, /* RX */
	अणुCPM_PORTB, 19, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण, /* TENA */
	अणुCPM_PORTC, 10, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* RENA */
	अणुCPM_PORTC, 11, CPM_PIN_INPUT | CPM_PIN_SECONDARY | CPM_PIN_GPIOपूर्ण, /* CLSN */

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

	/* I2C */
	अणुCPM_PORTB, 26, CPM_PIN_INPUT | CPM_PIN_OPENDRAINपूर्ण,
	अणुCPM_PORTB, 27, CPM_PIN_INPUT | CPM_PIN_OPENDRAINपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mpc866ads_pins); i++) अणु
		काष्ठा cpm_pin *pin = &mpc866ads_pins[i];
		cpm1_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm1_clk_setup(CPM_CLK_SMC1, CPM_BRG1, CPM_CLK_RTX);
	cpm1_clk_setup(CPM_CLK_SMC2, CPM_BRG2, CPM_CLK_RTX);
	cpm1_clk_setup(CPM_CLK_SCC1, CPM_CLK1, CPM_CLK_TX);
	cpm1_clk_setup(CPM_CLK_SCC1, CPM_CLK2, CPM_CLK_RX);

	/* Set FEC1 and FEC2 to MII mode */
	clrbits32(&mpc8xx_immr->im_cpm.cp_cptr, 0x00000180);
पूर्ण

अटल व्योम __init mpc86xads_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;
	u32 __iomem *bcsr_io;

	cpm_reset();
	init_ioports();

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc866ads-bcsr");
	अगर (!np) अणु
		prपूर्णांकk(KERN_CRIT "Could not find fsl,mpc866ads-bcsr node\n");
		वापस;
	पूर्ण

	bcsr_io = of_iomap(np, 0);
	of_node_put(np);

	अगर (bcsr_io == शून्य) अणु
		prपूर्णांकk(KERN_CRIT "Could not remap BCSR\n");
		वापस;
	पूर्ण

	clrbits32(bcsr_io, BCSR1_RS232EN_1 | BCSR1_RS232EN_2 | BCSR1_ETHEN);
	iounmap(bcsr_io);
पूर्ण

अटल पूर्णांक __init mpc86xads_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,mpc866ads");
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .name = "soc", पूर्ण,
	अणु .name = "cpm", पूर्ण,
	अणु .name = "localbus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(mpc86x_ads, declare_of_platक्रमm_devices);

define_machine(mpc86x_ads) अणु
	.name			= "MPC86x ADS",
	.probe			= mpc86xads_probe,
	.setup_arch		= mpc86xads_setup_arch,
	.init_IRQ		= mpc8xx_pics_init,
	.get_irq		= mpc8xx_get_irq,
	.restart		= mpc8xx_restart,
	.calibrate_decr		= mpc8xx_calibrate_decr,
	.set_rtc_समय		= mpc8xx_set_rtc_समय,
	.get_rtc_समय		= mpc8xx_get_rtc_समय,
	.progress		= udbg_progress,
पूर्ण;
