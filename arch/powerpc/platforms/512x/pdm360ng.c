<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010 DENX Software Engineering
 *
 * Anम_से_दij Gustschin, <agust@denx.de>
 *
 * PDM360NG board setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>

#समावेश "mpc512x.h"

#अगर defined(CONFIG_TOUCHSCREEN_ADS7846) || \
    defined(CONFIG_TOUCHSCREEN_ADS7846_MODULE)
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/notअगरier.h>

अटल व्योम *pdm360ng_gpio_base;

अटल पूर्णांक pdm360ng_get_penकरोwn_state(व्योम)
अणु
	u32 reg;

	reg = in_be32(pdm360ng_gpio_base + 0xc);
	अगर (reg & 0x40)
		setbits32(pdm360ng_gpio_base + 0xc, 0x40);

	reg = in_be32(pdm360ng_gpio_base + 0x8);

	/* वापस 1 अगर pen is करोwn */
	वापस (reg & 0x40) == 0;
पूर्ण

अटल काष्ठा ads7846_platक्रमm_data pdm360ng_ads7846_pdata = अणु
	.model			= 7845,
	.get_penकरोwn_state	= pdm360ng_get_penकरोwn_state,
	.irq_flags		= IRQF_TRIGGER_LOW,
पूर्ण;

अटल पूर्णांक __init pdm360ng_penirq_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-gpio");
	अगर (!np) अणु
		pr_err("%s: Can't find 'mpc5121-gpio' node\n", __func__);
		वापस -ENODEV;
	पूर्ण

	pdm360ng_gpio_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!pdm360ng_gpio_base) अणु
		pr_err("%s: Can't map gpio regs.\n", __func__);
		वापस -ENODEV;
	पूर्ण
	out_be32(pdm360ng_gpio_base + 0xc, 0xffffffff);
	setbits32(pdm360ng_gpio_base + 0x18, 0x2000);
	setbits32(pdm360ng_gpio_base + 0x10, 0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक pdm360ng_touchscreen_notअगरier_call(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event, व्योम *__dev)
अणु
	काष्ठा device *dev = __dev;

	अगर ((event == BUS_NOTIFY_ADD_DEVICE) &&
	    of_device_is_compatible(dev->of_node, "ti,ads7846")) अणु
		dev->platक्रमm_data = &pdm360ng_ads7846_pdata;
		वापस NOTIFY_OK;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block pdm360ng_touchscreen_nb = अणु
	.notअगरier_call = pdm360ng_touchscreen_notअगरier_call,
पूर्ण;

अटल व्योम __init pdm360ng_touchscreen_init(व्योम)
अणु
	अगर (pdm360ng_penirq_init())
		वापस;

	bus_रेजिस्टर_notअगरier(&spi_bus_type, &pdm360ng_touchscreen_nb);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init pdm360ng_touchscreen_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TOUCHSCREEN_ADS7846 */

व्योम __init pdm360ng_init(व्योम)
अणु
	mpc512x_init();
	pdm360ng_touchscreen_init();
पूर्ण

अटल पूर्णांक __init pdm360ng_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("ifm,pdm360ng"))
		वापस 0;

	mpc512x_init_early();

	वापस 1;
पूर्ण

define_machine(pdm360ng) अणु
	.name			= "PDM360NG",
	.probe			= pdm360ng_probe,
	.setup_arch		= mpc512x_setup_arch,
	.init			= pdm360ng_init,
	.init_IRQ		= mpc512x_init_IRQ,
	.get_irq		= ipic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.restart		= mpc512x_restart,
पूर्ण;
