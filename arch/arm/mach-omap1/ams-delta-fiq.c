<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Amstrad E3 FIQ handling
 *
 *  Copyright (C) 2009 Janusz Krzysztofik
 *  Copyright (c) 2006 Matt Callow
 *  Copyright (c) 2004 Amstrad Plc
 *  Copyright (C) 2001 RidgeRun, Inc.
 *
 * Parts of this code are taken from linux/arch/arm/mach-omap/irq.c
 * in the MontaVista 2.4 kernel (and the Amstrad changes therein)
 */
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/ams-delta-fiq.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/fiq.h>

#समावेश "ams-delta-fiq.h"
#समावेश "board-ams-delta.h"

अटल काष्ठा fiq_handler fh = अणु
	.name	= "ams-delta-fiq"
पूर्ण;

/*
 * This buffer is shared between FIQ and IRQ contexts.
 * The FIQ and IRQ isrs can both पढ़ो and ग_लिखो it.
 * It is काष्ठाured as a header section several 32bit slots,
 * followed by the circular buffer where the FIQ isr stores
 * keystrokes received from the qwerty keyboard.  See
 * <linux/platक्रमm_data/ams-delta-fiq.h> क्रम details of offsets.
 */
अटल अचिन्हित पूर्णांक fiq_buffer[1024];

अटल काष्ठा irq_chip *irq_chip;
अटल काष्ठा irq_data *irq_data[16];
अटल अचिन्हित पूर्णांक irq_counter[16];

अटल स्थिर अक्षर *pin_name[16] __initस्थिर = अणु
	[AMS_DELTA_GPIO_PIN_KEYBRD_DATA]	= "keybrd_data",
	[AMS_DELTA_GPIO_PIN_KEYBRD_CLK]		= "keybrd_clk",
पूर्ण;

अटल irqवापस_t deferred_fiq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_data *d;
	पूर्णांक gpio, irq_num, fiq_count;

	/*
	 * For each handled GPIO पूर्णांकerrupt, keep calling its पूर्णांकerrupt handler
	 * until the IRQ counter catches the FIQ incremented पूर्णांकerrupt counter.
	 */
	क्रम (gpio = AMS_DELTA_GPIO_PIN_KEYBRD_CLK;
			gpio <= AMS_DELTA_GPIO_PIN_HOOK_SWITCH; gpio++) अणु
		d = irq_data[gpio];
		irq_num = d->irq;
		fiq_count = fiq_buffer[FIQ_CNT_INT_00 + gpio];

		अगर (irq_counter[gpio] < fiq_count &&
				gpio != AMS_DELTA_GPIO_PIN_KEYBRD_CLK) अणु
			/*
			 * handle_simple_irq() that OMAP GPIO edge
			 * पूर्णांकerrupts शेष to since commit 80ac93c27441
			 * requires पूर्णांकerrupt alपढ़ोy acked and unmasked.
			 */
			अगर (!WARN_ON_ONCE(!irq_chip->irq_unmask))
				irq_chip->irq_unmask(d);
		पूर्ण
		क्रम (; irq_counter[gpio] < fiq_count; irq_counter[gpio]++)
			generic_handle_irq(irq_num);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init ams_delta_init_fiq(काष्ठा gpio_chip *chip,
			       काष्ठा platक्रमm_device *serio)
अणु
	काष्ठा gpio_desc *gpiod, *data = शून्य, *clk = शून्य;
	व्योम *fiqhandler_start;
	अचिन्हित पूर्णांक fiqhandler_length;
	काष्ठा pt_regs FIQ_regs;
	अचिन्हित दीर्घ val, offset;
	पूर्णांक i, retval;

	/* Store irq_chip location क्रम IRQ handler use */
	irq_chip = chip->irq.chip;
	अगर (!irq_chip) अणु
		pr_err("%s: GPIO chip %s is missing IRQ function\n", __func__,
		       chip->label);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(irq_data); i++) अणु
		gpiod = gpiochip_request_own_desc(chip, i, pin_name[i],
						  GPIO_ACTIVE_HIGH, GPIOD_IN);
		अगर (IS_ERR(gpiod)) अणु
			pr_err("%s: failed to get GPIO pin %d (%ld)\n",
			       __func__, i, PTR_ERR(gpiod));
			वापस;
		पूर्ण
		/* Store irq_data location क्रम IRQ handler use */
		irq_data[i] = irq_get_irq_data(gpiod_to_irq(gpiod));

		/*
		 * FIQ handler takes full control over serio data and clk GPIO
		 * pins.  Initialize them and keep requested so nobody can
		 * पूर्णांकerfere.  Fail अगर any of those two couldn't be requested.
		 */
		चयन (i) अणु
		हाल AMS_DELTA_GPIO_PIN_KEYBRD_DATA:
			data = gpiod;
			gpiod_direction_input(data);
			अवरोध;
		हाल AMS_DELTA_GPIO_PIN_KEYBRD_CLK:
			clk = gpiod;
			gpiod_direction_input(clk);
			अवरोध;
		शेष:
			gpiochip_मुक्त_own_desc(gpiod);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!data || !clk)
		जाओ out_gpio;

	fiqhandler_start = &qwerty_fiqin_start;
	fiqhandler_length = &qwerty_fiqin_end - &qwerty_fiqin_start;
	pr_info("Installing fiq handler from %p, length 0x%x\n",
			fiqhandler_start, fiqhandler_length);

	retval = claim_fiq(&fh);
	अगर (retval) अणु
		pr_err("ams_delta_init_fiq(): couldn't claim FIQ, ret=%d\n",
				retval);
		जाओ out_gpio;
	पूर्ण

	retval = request_irq(INT_DEFERRED_FIQ, deferred_fiq,
			IRQ_TYPE_EDGE_RISING, "deferred_fiq", शून्य);
	अगर (retval < 0) अणु
		pr_err("Failed to get deferred_fiq IRQ, ret=%d\n", retval);
		release_fiq(&fh);
		जाओ out_gpio;
	पूर्ण
	/*
	 * Since no set_type() method is provided by OMAP irq chip,
	 * चयन to edge triggered पूर्णांकerrupt type manually.
	 */
	offset = IRQ_ILR0_REG_OFFSET +
			((INT_DEFERRED_FIQ - NR_IRQS_LEGACY) & 0x1f) * 0x4;
	val = omap_पढ़ोl(DEFERRED_FIQ_IH_BASE + offset) & ~(1 << 1);
	omap_ग_लिखोl(val, DEFERRED_FIQ_IH_BASE + offset);

	set_fiq_handler(fiqhandler_start, fiqhandler_length);

	/*
	 * Initialise the buffer which is shared
	 * between FIQ mode and IRQ mode
	 */
	fiq_buffer[FIQ_GPIO_INT_MASK]	= 0;
	fiq_buffer[FIQ_MASK]		= 0;
	fiq_buffer[FIQ_STATE]		= 0;
	fiq_buffer[FIQ_KEY]		= 0;
	fiq_buffer[FIQ_KEYS_CNT]	= 0;
	fiq_buffer[FIQ_KEYS_HICNT]	= 0;
	fiq_buffer[FIQ_TAIL_OFFSET]	= 0;
	fiq_buffer[FIQ_HEAD_OFFSET]	= 0;
	fiq_buffer[FIQ_BUF_LEN]		= 256;
	fiq_buffer[FIQ_MISSED_KEYS]	= 0;
	fiq_buffer[FIQ_BUFFER_START]	=
			(अचिन्हित पूर्णांक) &fiq_buffer[FIQ_CIRC_BUFF];

	क्रम (i = FIQ_CNT_INT_00; i <= FIQ_CNT_INT_15; i++)
		fiq_buffer[i] = 0;

	/*
	 * FIQ mode r9 always poपूर्णांकs to the fiq_buffer, because the FIQ isr
	 * will run in an unpredictable context. The fiq_buffer is the FIQ isr's
	 * only means of communication with the IRQ level and other kernel
	 * context code.
	 */
	FIQ_regs.ARM_r9 = (अचिन्हित पूर्णांक)fiq_buffer;
	set_fiq_regs(&FIQ_regs);

	pr_info("request_fiq(): fiq_buffer = %p\n", fiq_buffer);

	/*
	 * Redirect GPIO पूर्णांकerrupts to FIQ
	 */
	offset = IRQ_ILR0_REG_OFFSET + (INT_GPIO_BANK1 - NR_IRQS_LEGACY) * 0x4;
	val = omap_पढ़ोl(OMAP_IH1_BASE + offset) | 1;
	omap_ग_लिखोl(val, OMAP_IH1_BASE + offset);

	/* Initialize serio device IRQ resource and platक्रमm_data */
	serio->resource[0].start = gpiod_to_irq(clk);
	serio->resource[0].end = serio->resource[0].start;
	serio->dev.platक्रमm_data = fiq_buffer;

	/*
	 * Since FIQ handler perक्रमms handling of GPIO रेजिस्टरs क्रम
	 * "keybrd_clk" IRQ pin, ams_delta_serio driver used to set
	 * handle_simple_irq() as active IRQ handler क्रम that pin to aव्योम
	 * bad पूर्णांकeraction with gpio-omap driver.  This is no दीर्घer needed
	 * as handle_simple_irq() is now the शेष handler क्रम OMAP GPIO
	 * edge पूर्णांकerrupts.
	 * This comment replaces the obsolete code which has been हटाओd
	 * from the ams_delta_serio driver and stands here only as a reminder
	 * of that dependency on gpio-omap driver behavior.
	 */

	वापस;

out_gpio:
	अगर (data)
		gpiochip_मुक्त_own_desc(data);
	अगर (clk)
		gpiochip_मुक्त_own_desc(clk);
पूर्ण
