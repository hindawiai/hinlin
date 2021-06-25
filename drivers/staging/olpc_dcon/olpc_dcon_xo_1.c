<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mainly by David Woodhouse, somewhat modअगरied by Jordan Crouse
 *
 * Copyright तऊ 2006-2007  Red Hat, Inc.
 * Copyright तऊ 2006-2007  Advanced Micro Devices, Inc.
 * Copyright तऊ 2009       VIA Technology, Inc.
 * Copyright (c) 2010  Andres Salomon <dilinger@queued.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cs5535.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/olpc.h>

#समावेश "olpc_dcon.h"

क्रमागत dcon_gpios अणु
	OLPC_DCON_STAT0,
	OLPC_DCON_STAT1,
	OLPC_DCON_IRQ,
	OLPC_DCON_LOAD,
	OLPC_DCON_BLANK,
पूर्ण;

अटल स्थिर काष्ठा dcon_gpio gpios_asis[] = अणु
	[OLPC_DCON_STAT0] = अणु .name = "dcon_stat0", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_STAT1] = अणु .name = "dcon_stat1", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_IRQ] = अणु .name = "dcon_irq", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_LOAD] = अणु .name = "dcon_load", .flags = GPIOD_ASIS पूर्ण,
	[OLPC_DCON_BLANK] = अणु .name = "dcon_blank", .flags = GPIOD_ASIS पूर्ण,
पूर्ण;

अटल काष्ठा gpio_desc *gpios[5];

अटल पूर्णांक dcon_init_xo_1(काष्ठा dcon_priv *dcon)
अणु
	अचिन्हित अक्षर lob;
	पूर्णांक ret, i;
	स्थिर काष्ठा dcon_gpio *pin = &gpios_asis[0];

	क्रम (i = 0; i < ARRAY_SIZE(gpios_asis); i++) अणु
		gpios[i] = devm_gpiod_get(&dcon->client->dev, pin[i].name,
					  pin[i].flags);
		अगर (IS_ERR(gpios[i])) अणु
			ret = PTR_ERR(gpios[i]);
			pr_err("failed to request %s GPIO: %d\n", pin[i].name,
			       ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Turn off the event enable क्रम GPIO7 just to be safe */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_EVENTS_ENABLE);

	/*
	 * Determine the current state by पढ़ोing the GPIO bit; earlier
	 * stages of the boot process have established the state.
	 *
	 * Note that we पढ़ो GPIO_OUTPUT_VAL rather than GPIO_READ_BACK here;
	 * this is because OFW will disable input क्रम the pin and set a value..
	 * READ_BACK will only contain a valid value अगर input is enabled and
	 * then a value is set.  So, future पढ़ोings of the pin can use
	 * READ_BACK, but the first one cannot.  Awesome, huh?
	 */
	dcon->curr_src = cs5535_gpio_isset(OLPC_GPIO_DCON_LOAD, GPIO_OUTPUT_VAL)
		? DCON_SOURCE_CPU
		: DCON_SOURCE_DCON;
	dcon->pending_src = dcon->curr_src;

	/* Set the directions क्रम the GPIO pins */
	gpiod_direction_input(gpios[OLPC_DCON_STAT0]);
	gpiod_direction_input(gpios[OLPC_DCON_STAT1]);
	gpiod_direction_input(gpios[OLPC_DCON_IRQ]);
	gpiod_direction_input(gpios[OLPC_DCON_BLANK]);
	gpiod_direction_output(gpios[OLPC_DCON_LOAD],
			       dcon->curr_src == DCON_SOURCE_CPU);

	/* Set up the पूर्णांकerrupt mappings */

	/* Set the IRQ to pair 2 */
	cs5535_gpio_setup_event(OLPC_GPIO_DCON_IRQ, 2, 0);

	/* Enable group 2 to trigger the DCON पूर्णांकerrupt */
	cs5535_gpio_set_irq(2, DCON_IRQ);

	/* Select edge level क्रम पूर्णांकerrupt (in PIC) */
	lob = inb(0x4d0);
	lob &= ~(1 << DCON_IRQ);
	outb(lob, 0x4d0);

	/* Register the पूर्णांकerrupt handler */
	अगर (request_irq(DCON_IRQ, &dcon_पूर्णांकerrupt, 0, "DCON", dcon)) अणु
		pr_err("failed to request DCON's irq\n");
		वापस -EIO;
	पूर्ण

	/* Clear INV_EN क्रम GPIO7 (DCONIRQ) */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_INVERT);

	/* Enable filter क्रम GPIO12 (DCONBLANK) */
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_INPUT_FILTER);

	/* Disable filter क्रम GPIO7 */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_FILTER);

	/* Disable event counter क्रम GPIO7 (DCONIRQ) and GPIO12 (DCONBLANK) */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_EVENT_COUNT);
	cs5535_gpio_clear(OLPC_GPIO_DCON_BLANK, GPIO_INPUT_EVENT_COUNT);

	/* Add GPIO12 to the Filter Event Pair #7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_FE7_SEL);

	/* Turn off negative Edge Enable क्रम GPIO12 */
	cs5535_gpio_clear(OLPC_GPIO_DCON_BLANK, GPIO_NEGATIVE_EDGE_EN);

	/* Enable negative Edge Enable क्रम GPIO7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_EN);

	/* Zero the filter amount क्रम Filter Event Pair #7 */
	cs5535_gpio_set(0, GPIO_FLTR7_AMOUNT);

	/* Clear the negative edge status क्रम GPIO7 and GPIO12 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_NEGATIVE_EDGE_STS);

	/* FIXME:  Clear the positive status as well, just to be sure */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_POSITIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_POSITIVE_EDGE_STS);

	/* Enable events क्रम GPIO7 (DCONIRQ) and GPIO12 (DCONBLANK) */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_EVENTS_ENABLE);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_EVENTS_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम dcon_wiggle_xo_1(व्योम)
अणु
	पूर्णांक x;

	/*
	 * According to HiMax, when घातering the DCON up we should hold
	 * SMB_DATA high क्रम 8 SMB_CLK cycles.  This will क्रमce the DCON
	 * state machine to reset to a (sane) initial state.  Mitch Bradley
	 * did some testing and discovered that holding क्रम 16 SMB_CLK cycles
	 * worked a lot more reliably, so that's what we करो here.
	 *
	 * According to the cs5536 spec, to set GPIO14 to SMB_CLK we must
	 * simultaneously set AUX1 IN/OUT to GPIO14; ditto क्रम SMB_DATA and
	 * GPIO15.
	 */
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_VAL);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_ENABLE);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_ENABLE);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX2);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX2);
	cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_INPUT_AUX1);
	cs5535_gpio_clear(OLPC_GPIO_SMB_DATA, GPIO_INPUT_AUX1);

	क्रम (x = 0; x < 16; x++) अणु
		udelay(5);
		cs5535_gpio_clear(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
		udelay(5);
		cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_VAL);
	पूर्ण
	udelay(5);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_OUTPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_OUTPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_CLK, GPIO_INPUT_AUX1);
	cs5535_gpio_set(OLPC_GPIO_SMB_DATA, GPIO_INPUT_AUX1);
पूर्ण

अटल व्योम dcon_set_dconload_1(पूर्णांक val)
अणु
	gpiod_set_value(gpios[OLPC_DCON_LOAD], val);
पूर्ण

अटल पूर्णांक dcon_पढ़ो_status_xo_1(u8 *status)
अणु
	*status = gpiod_get_value(gpios[OLPC_DCON_STAT0]);
	*status |= gpiod_get_value(gpios[OLPC_DCON_STAT1]) << 1;

	/* Clear the negative edge status क्रम GPIO7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_STS);

	वापस 0;
पूर्ण

काष्ठा dcon_platक्रमm_data dcon_pdata_xo_1 = अणु
	.init = dcon_init_xo_1,
	.bus_stabilize_wiggle = dcon_wiggle_xo_1,
	.set_dconload = dcon_set_dconload_1,
	.पढ़ो_status = dcon_पढ़ो_status_xo_1,
पूर्ण;
