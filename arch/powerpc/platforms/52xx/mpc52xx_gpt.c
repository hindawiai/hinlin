<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC5200 General Purpose Timer device driver
 *
 * Copyright (c) 2009 Secret Lab Technologies Ltd.
 * Copyright (c) 2008 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 *
 * This file is a driver क्रम the the General Purpose Timer (gpt) devices
 * found on the MPC5200 SoC.  Each समयr has an IO pin which can be used
 * क्रम GPIO or can be used to उठाओ पूर्णांकerrupts.  The समयr function can
 * be used independently from the IO pin, or it can be used to control
 * output संकेतs or measure input संकेतs.
 *
 * This driver supports the GPIO and IRQ controller functions of the GPT
 * device.  Timer functions are not yet supported.
 *
 * The समयr gpt0 can be used as watchकरोg (wdt).  If the wdt mode is used,
 * this prevents the use of any gpt0 gpt function (i.e. they will fail with
 * -EBUSY).  Thus, the safety wdt function always has precedence over the gpt
 * function.  If the kernel has been compiled with CONFIG_WATCHDOG_NOWAYOUT,
 * this means that gpt0 is locked in wdt mode until the next reboot - this
 * may be a requirement in safety applications.
 *
 * To use the GPIO function, the following two properties must be added
 * to the device tree node क्रम the gpt device (typically in the .dts file
 * क्रम the board):
 * 	gpio-controller;
 * 	#gpio-cells = < 2 >;
 * This driver will रेजिस्टर the GPIO pin अगर it finds the gpio-controller
 * property in the device tree.
 *
 * To use the IRQ controller function, the following two properties must
 * be added to the device tree node क्रम the gpt device:
 * 	पूर्णांकerrupt-controller;
 * 	#पूर्णांकerrupt-cells = < 1 >;
 * The IRQ controller binding only uses one cell to specअगरy the पूर्णांकerrupt,
 * and the IRQ flags are encoded in the cell.  A cell is not used to encode
 * the IRQ number because the GPT only has a single IRQ source.  For flags,
 * a value of '1' means rising edge sensitive and '2' means falling edge.
 *
 * The GPIO and the IRQ controller functions can be used at the same समय,
 * but in this use हाल the IO line will only work as an input.  Trying to
 * use it as a GPIO output will not work.
 *
 * When using the GPIO line as an output, it can either be driven as normal
 * IO, or it can be an Open Collector (OC) output.  At the moment it is the
 * responsibility of either the bootloader or the platक्रमm setup code to set
 * the output mode.  This driver करोes not change the output mode setting.
 */

#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/mpc52xx.h>

MODULE_DESCRIPTION("Freescale MPC52xx gpt driver");
MODULE_AUTHOR("Sascha Hauer, Grant Likely, Albrecht Dreथ");
MODULE_LICENSE("GPL");

/**
 * काष्ठा mpc52xx_gpt - Private data काष्ठाure क्रम MPC52xx GPT driver
 * @dev: poपूर्णांकer to device काष्ठाure
 * @regs: भव address of GPT रेजिस्टरs
 * @lock: spinlock to coordinate between dअगरferent functions.
 * @gc: gpio_chip instance काष्ठाure; used when GPIO is enabled
 * @irqhost: Poपूर्णांकer to irq_करोमुख्य instance; used when IRQ mode is supported
 * @wdt_mode: only relevant क्रम gpt0: bit 0 (MPC52xx_GPT_CAN_WDT) indicates
 *   अगर the gpt may be used as wdt, bit 1 (MPC52xx_GPT_IS_WDT) indicates
 *   अगर the समयr is actively used as wdt which blocks gpt functions
 */
काष्ठा mpc52xx_gpt_priv अणु
	काष्ठा list_head list;		/* List of all GPT devices */
	काष्ठा device *dev;
	काष्ठा mpc52xx_gpt __iomem *regs;
	raw_spinlock_t lock;
	काष्ठा irq_करोमुख्य *irqhost;
	u32 ipb_freq;
	u8 wdt_mode;

#अगर defined(CONFIG_GPIOLIB)
	काष्ठा gpio_chip gc;
#पूर्ण_अगर
पूर्ण;

LIST_HEAD(mpc52xx_gpt_list);
DEFINE_MUTEX(mpc52xx_gpt_list_mutex);

#घोषणा MPC52xx_GPT_MODE_MS_MASK	(0x07)
#घोषणा MPC52xx_GPT_MODE_MS_IC		(0x01)
#घोषणा MPC52xx_GPT_MODE_MS_OC		(0x02)
#घोषणा MPC52xx_GPT_MODE_MS_PWM		(0x03)
#घोषणा MPC52xx_GPT_MODE_MS_GPIO	(0x04)

#घोषणा MPC52xx_GPT_MODE_GPIO_MASK	(0x30)
#घोषणा MPC52xx_GPT_MODE_GPIO_OUT_LOW	(0x20)
#घोषणा MPC52xx_GPT_MODE_GPIO_OUT_HIGH	(0x30)

#घोषणा MPC52xx_GPT_MODE_COUNTER_ENABLE	(0x1000)
#घोषणा MPC52xx_GPT_MODE_CONTINUOUS	(0x0400)
#घोषणा MPC52xx_GPT_MODE_OPEN_DRAIN	(0x0200)
#घोषणा MPC52xx_GPT_MODE_IRQ_EN		(0x0100)
#घोषणा MPC52xx_GPT_MODE_WDT_EN		(0x8000)

#घोषणा MPC52xx_GPT_MODE_ICT_MASK	(0x030000)
#घोषणा MPC52xx_GPT_MODE_ICT_RISING	(0x010000)
#घोषणा MPC52xx_GPT_MODE_ICT_FALLING	(0x020000)
#घोषणा MPC52xx_GPT_MODE_ICT_TOGGLE	(0x030000)

#घोषणा MPC52xx_GPT_MODE_WDT_PING	(0xa5)

#घोषणा MPC52xx_GPT_STATUS_IRQMASK	(0x000f)

#घोषणा MPC52xx_GPT_CAN_WDT		(1 << 0)
#घोषणा MPC52xx_GPT_IS_WDT		(1 << 1)


/* ---------------------------------------------------------------------
 * Cascaded पूर्णांकerrupt controller hooks
 */

अटल व्योम mpc52xx_gpt_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	setbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_IRQ_EN);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);
पूर्ण

अटल व्योम mpc52xx_gpt_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	clrbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_IRQ_EN);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);
पूर्ण

अटल व्योम mpc52xx_gpt_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);

	out_be32(&gpt->regs->status, MPC52xx_GPT_STATUS_IRQMASK);
पूर्ण

अटल पूर्णांक mpc52xx_gpt_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	u32 reg;

	dev_dbg(gpt->dev, "%s: virq=%i type=%x\n", __func__, d->irq, flow_type);

	raw_spin_lock_irqsave(&gpt->lock, flags);
	reg = in_be32(&gpt->regs->mode) & ~MPC52xx_GPT_MODE_ICT_MASK;
	अगर (flow_type & IRQF_TRIGGER_RISING)
		reg |= MPC52xx_GPT_MODE_ICT_RISING;
	अगर (flow_type & IRQF_TRIGGER_FALLING)
		reg |= MPC52xx_GPT_MODE_ICT_FALLING;
	out_be32(&gpt->regs->mode, reg);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mpc52xx_gpt_irq_chip = अणु
	.name = "MPC52xx GPT",
	.irq_unmask = mpc52xx_gpt_irq_unmask,
	.irq_mask = mpc52xx_gpt_irq_mask,
	.irq_ack = mpc52xx_gpt_irq_ack,
	.irq_set_type = mpc52xx_gpt_irq_set_type,
पूर्ण;

अटल व्योम mpc52xx_gpt_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = irq_desc_get_handler_data(desc);
	पूर्णांक sub_virq;
	u32 status;

	status = in_be32(&gpt->regs->status) & MPC52xx_GPT_STATUS_IRQMASK;
	अगर (status) अणु
		sub_virq = irq_linear_revmap(gpt->irqhost, 0);
		generic_handle_irq(sub_virq);
	पूर्ण
पूर्ण

अटल पूर्णांक mpc52xx_gpt_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			       irq_hw_number_t hw)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = h->host_data;

	dev_dbg(gpt->dev, "%s: h=%p, virq=%i\n", __func__, h, virq);
	irq_set_chip_data(virq, gpt);
	irq_set_chip_and_handler(virq, &mpc52xx_gpt_irq_chip, handle_edge_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_gpt_irq_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
				 स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				 irq_hw_number_t *out_hwirq,
				 अचिन्हित पूर्णांक *out_flags)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = h->host_data;

	dev_dbg(gpt->dev, "%s: flags=%i\n", __func__, पूर्णांकspec[0]);

	अगर ((पूर्णांकsize < 1) || (पूर्णांकspec[0] > 3)) अणु
		dev_err(gpt->dev, "bad irq specifier in %pOF\n", ct);
		वापस -EINVAL;
	पूर्ण

	*out_hwirq = 0; /* The GPT only has 1 IRQ line */
	*out_flags = पूर्णांकspec[0];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mpc52xx_gpt_irq_ops = अणु
	.map = mpc52xx_gpt_irq_map,
	.xlate = mpc52xx_gpt_irq_xlate,
पूर्ण;

अटल व्योम
mpc52xx_gpt_irq_setup(काष्ठा mpc52xx_gpt_priv *gpt, काष्ठा device_node *node)
अणु
	पूर्णांक cascade_virq;
	अचिन्हित दीर्घ flags;
	u32 mode;

	cascade_virq = irq_of_parse_and_map(node, 0);
	अगर (!cascade_virq)
		वापस;

	gpt->irqhost = irq_करोमुख्य_add_linear(node, 1, &mpc52xx_gpt_irq_ops, gpt);
	अगर (!gpt->irqhost) अणु
		dev_err(gpt->dev, "irq_domain_add_linear() failed\n");
		वापस;
	पूर्ण

	irq_set_handler_data(cascade_virq, gpt);
	irq_set_chained_handler(cascade_virq, mpc52xx_gpt_irq_cascade);

	/* If the GPT is currently disabled, then change it to be in Input
	 * Capture mode.  If the mode is non-zero, then the pin could be
	 * alपढ़ोy in use क्रम something. */
	raw_spin_lock_irqsave(&gpt->lock, flags);
	mode = in_be32(&gpt->regs->mode);
	अगर ((mode & MPC52xx_GPT_MODE_MS_MASK) == 0)
		out_be32(&gpt->regs->mode, mode | MPC52xx_GPT_MODE_MS_IC);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	dev_dbg(gpt->dev, "%s() complete. virq=%i\n", __func__, cascade_virq);
पूर्ण


/* ---------------------------------------------------------------------
 * GPIOLIB hooks
 */
#अगर defined(CONFIG_GPIOLIB)
अटल पूर्णांक mpc52xx_gpt_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = gpiochip_get_data(gc);

	वापस (in_be32(&gpt->regs->status) >> 8) & 1;
पूर्ण

अटल व्योम
mpc52xx_gpt_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक v)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	u32 r;

	dev_dbg(gpt->dev, "%s: gpio:%d v:%d\n", __func__, gpio, v);
	r = v ? MPC52xx_GPT_MODE_GPIO_OUT_HIGH : MPC52xx_GPT_MODE_GPIO_OUT_LOW;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	clrsetbits_be32(&gpt->regs->mode, MPC52xx_GPT_MODE_GPIO_MASK, r);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);
पूर्ण

अटल पूर्णांक mpc52xx_gpt_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	dev_dbg(gpt->dev, "%s: gpio:%d\n", __func__, gpio);

	raw_spin_lock_irqsave(&gpt->lock, flags);
	clrbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_GPIO_MASK);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_gpt_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	mpc52xx_gpt_gpio_set(gc, gpio, val);
	वापस 0;
पूर्ण

अटल व्योम
mpc52xx_gpt_gpio_setup(काष्ठा mpc52xx_gpt_priv *gpt, काष्ठा device_node *node)
अणु
	पूर्णांक rc;

	/* Only setup GPIO अगर the device tree claims the GPT is
	 * a GPIO controller */
	अगर (!of_find_property(node, "gpio-controller", शून्य))
		वापस;

	gpt->gc.label = kaप्र_लिखो(GFP_KERNEL, "%pOF", node);
	अगर (!gpt->gc.label) अणु
		dev_err(gpt->dev, "out of memory\n");
		वापस;
	पूर्ण

	gpt->gc.ngpio = 1;
	gpt->gc.direction_input  = mpc52xx_gpt_gpio_dir_in;
	gpt->gc.direction_output = mpc52xx_gpt_gpio_dir_out;
	gpt->gc.get = mpc52xx_gpt_gpio_get;
	gpt->gc.set = mpc52xx_gpt_gpio_set;
	gpt->gc.base = -1;
	gpt->gc.of_node = node;

	/* Setup बाह्यal pin in GPIO mode */
	clrsetbits_be32(&gpt->regs->mode, MPC52xx_GPT_MODE_MS_MASK,
			MPC52xx_GPT_MODE_MS_GPIO);

	rc = gpiochip_add_data(&gpt->gc, gpt);
	अगर (rc)
		dev_err(gpt->dev, "gpiochip_add_data() failed; rc=%i\n", rc);

	dev_dbg(gpt->dev, "%s() complete.\n", __func__);
पूर्ण
#अन्यथा /* defined(CONFIG_GPIOLIB) */
अटल व्योम
mpc52xx_gpt_gpio_setup(काष्ठा mpc52xx_gpt_priv *p, काष्ठा device_node *np) अणु पूर्ण
#पूर्ण_अगर /* defined(CONFIG_GPIOLIB) */

/***********************************************************************
 * Timer API
 */

/**
 * mpc52xx_gpt_from_irq - Return the GPT device associated with an IRQ number
 * @irq: irq of समयr.
 */
काष्ठा mpc52xx_gpt_priv *mpc52xx_gpt_from_irq(पूर्णांक irq)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt;
	काष्ठा list_head *pos;

	/* Iterate over the list of समयrs looking क्रम a matching device */
	mutex_lock(&mpc52xx_gpt_list_mutex);
	list_क्रम_each(pos, &mpc52xx_gpt_list) अणु
		gpt = container_of(pos, काष्ठा mpc52xx_gpt_priv, list);
		अगर (gpt->irqhost && irq == irq_linear_revmap(gpt->irqhost, 0)) अणु
			mutex_unlock(&mpc52xx_gpt_list_mutex);
			वापस gpt;
		पूर्ण
	पूर्ण
	mutex_unlock(&mpc52xx_gpt_list_mutex);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mpc52xx_gpt_from_irq);

अटल पूर्णांक mpc52xx_gpt_करो_start(काष्ठा mpc52xx_gpt_priv *gpt, u64 period,
				पूर्णांक continuous, पूर्णांक as_wdt)
अणु
	u32 clear, set;
	u64 घड़ीs;
	u32 prescale;
	अचिन्हित दीर्घ flags;

	clear = MPC52xx_GPT_MODE_MS_MASK | MPC52xx_GPT_MODE_CONTINUOUS;
	set = MPC52xx_GPT_MODE_MS_GPIO | MPC52xx_GPT_MODE_COUNTER_ENABLE;
	अगर (as_wdt) अणु
		clear |= MPC52xx_GPT_MODE_IRQ_EN;
		set |= MPC52xx_GPT_MODE_WDT_EN;
	पूर्ण अन्यथा अगर (continuous)
		set |= MPC52xx_GPT_MODE_CONTINUOUS;

	/* Determine the number of घड़ीs in the requested period.  64 bit
	 * arithmatic is करोne here to preserve the precision until the value
	 * is scaled back करोwn पूर्णांकo the u32 range.  Period is in 'ns', bus
	 * frequency is in Hz. */
	घड़ीs = period * (u64)gpt->ipb_freq;
	करो_भाग(घड़ीs, 1000000000); /* Scale it करोwn to ns range */

	/* This device cannot handle a घड़ी count greater than 32 bits */
	अगर (घड़ीs > 0xffffffff)
		वापस -EINVAL;

	/* Calculate the prescaler and count values from the घड़ीs value.
	 * 'clocks' is the number of घड़ी ticks in the period.  The समयr
	 * has 16 bit precision and a 16 bit prescaler.  Prescaler is
	 * calculated by पूर्णांकeger भागiding the घड़ीs by 0x10000 (shअगरting
	 * करोwn 16 bits) to obtain the smallest possible भागisor क्रम घड़ीs
	 * to get a 16 bit count value.
	 *
	 * Note: the prescale रेजिस्टर is '1' based, not '0' based.  ie. a
	 * value of '1' means भागide the घड़ी by one.  0xffff भागides the
	 * घड़ी by 0xffff.  '0x0000' करोes not भागide by zero, but wraps
	 * around and भागides by 0x10000.  That is why prescale must be
	 * a u32 variable, not a u16, क्रम this calculation. */
	prescale = (घड़ीs >> 16) + 1;
	करो_भाग(घड़ीs, prescale);
	अगर (घड़ीs > 0xffff) अणु
		pr_err("calculation error; prescale:%x clocks:%llx\n",
		       prescale, घड़ीs);
		वापस -EINVAL;
	पूर्ण

	/* Set and enable the समयr, reject an attempt to use a wdt as gpt */
	raw_spin_lock_irqsave(&gpt->lock, flags);
	अगर (as_wdt)
		gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
	अन्यथा अगर ((gpt->wdt_mode & MPC52xx_GPT_IS_WDT) != 0) अणु
		raw_spin_unlock_irqrestore(&gpt->lock, flags);
		वापस -EBUSY;
	पूर्ण
	out_be32(&gpt->regs->count, prescale << 16 | घड़ीs);
	clrsetbits_be32(&gpt->regs->mode, clear, set);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	वापस 0;
पूर्ण

/**
 * mpc52xx_gpt_start_समयr - Set and enable the GPT समयr
 * @gpt: Poपूर्णांकer to gpt निजी data काष्ठाure
 * @period: period of समयr in ns; max. ~130s @ 33MHz IPB घड़ी
 * @continuous: set to 1 to make समयr continuous मुक्त running
 *
 * An पूर्णांकerrupt will be generated every समय the समयr fires
 */
पूर्णांक mpc52xx_gpt_start_समयr(काष्ठा mpc52xx_gpt_priv *gpt, u64 period,
                            पूर्णांक continuous)
अणु
	वापस mpc52xx_gpt_करो_start(gpt, period, continuous, 0);
पूर्ण
EXPORT_SYMBOL(mpc52xx_gpt_start_समयr);

/**
 * mpc52xx_gpt_stop_समयr - Stop a gpt
 * @gpt: Poपूर्णांकer to gpt निजी data काष्ठाure
 *
 * Returns an error अगर attempting to stop a wdt
 */
पूर्णांक mpc52xx_gpt_stop_समयr(काष्ठा mpc52xx_gpt_priv *gpt)
अणु
	अचिन्हित दीर्घ flags;

	/* reject the operation अगर the समयr is used as watchकरोg (gpt 0 only) */
	raw_spin_lock_irqsave(&gpt->lock, flags);
	अगर ((gpt->wdt_mode & MPC52xx_GPT_IS_WDT) != 0) अणु
		raw_spin_unlock_irqrestore(&gpt->lock, flags);
		वापस -EBUSY;
	पूर्ण

	clrbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_COUNTER_ENABLE);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc52xx_gpt_stop_समयr);

/**
 * mpc52xx_gpt_समयr_period - Read the समयr period
 * @gpt: Poपूर्णांकer to gpt निजी data काष्ठाure
 *
 * Returns the समयr period in ns
 */
u64 mpc52xx_gpt_समयr_period(काष्ठा mpc52xx_gpt_priv *gpt)
अणु
	u64 period;
	u64 prescale;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	period = in_be32(&gpt->regs->count);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	prescale = period >> 16;
	period &= 0xffff;
	अगर (prescale == 0)
		prescale = 0x10000;
	period = period * prescale * 1000000000ULL;
	करो_भाग(period, (u64)gpt->ipb_freq);
	वापस period;
पूर्ण
EXPORT_SYMBOL(mpc52xx_gpt_समयr_period);

#अगर defined(CONFIG_MPC5200_WDT)
/***********************************************************************
 * Watchकरोg API क्रम gpt0
 */

#घोषणा WDT_IDENTITY	    "mpc52xx watchdog on GPT0"

/* wdt_is_active stores whether or not the /dev/watchकरोg device is खोलोed */
अटल अचिन्हित दीर्घ wdt_is_active;

/* wdt-capable gpt */
अटल काष्ठा mpc52xx_gpt_priv *mpc52xx_gpt_wdt;

/* low-level wdt functions */
अटल अंतरभूत व्योम mpc52xx_gpt_wdt_ping(काष्ठा mpc52xx_gpt_priv *gpt_wdt)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gpt_wdt->lock, flags);
	out_8((u8 *) &gpt_wdt->regs->mode, MPC52xx_GPT_MODE_WDT_PING);
	raw_spin_unlock_irqrestore(&gpt_wdt->lock, flags);
पूर्ण

/* wdt misc device api */
अटल sमाप_प्रकार mpc52xx_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt_wdt = file->निजी_data;
	mpc52xx_gpt_wdt_ping(gpt_wdt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info mpc5200_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity	= WDT_IDENTITY,
पूर्ण;

अटल दीर्घ mpc52xx_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt_wdt = file->निजी_data;
	पूर्णांक __user *data = (पूर्णांक __user *)arg;
	पूर्णांक समयout;
	u64 real_समयout;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = copy_to_user(data, &mpc5200_wdt_info,
				   माप(mpc5200_wdt_info));
		अगर (ret)
			ret = -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(0, data);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		mpc52xx_gpt_wdt_ping(gpt_wdt);
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समयout, data);
		अगर (ret)
			अवरोध;
		real_समयout = (u64) समयout * 1000000000ULL;
		ret = mpc52xx_gpt_करो_start(gpt_wdt, real_समयout, 0, 1);
		अगर (ret)
			अवरोध;
		/* fall through and वापस the समयout */

	हाल WDIOC_GETTIMEOUT:
		/* we need to round here as to aव्योम e.g. the following
		 * situation:
		 * - समयout requested is 1 second;
		 * - real समयout @33MHz is 999997090ns
		 * - the पूर्णांक भागide by 10^9 will वापस 0.
		 */
		real_समयout =
			mpc52xx_gpt_समयr_period(gpt_wdt) + 500000000ULL;
		करो_भाग(real_समयout, 1000000000ULL);
		समयout = (पूर्णांक) real_समयout;
		ret = put_user(समयout, data);
		अवरोध;

	शेष:
		ret = -ENOTTY;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mpc52xx_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	/* sanity check */
	अगर (!mpc52xx_gpt_wdt)
		वापस -ENODEV;

	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &wdt_is_active))
		वापस -EBUSY;

	/* Set and activate the watchकरोg with 30 seconds समयout */
	ret = mpc52xx_gpt_करो_start(mpc52xx_gpt_wdt, 30ULL * 1000000000ULL,
				   0, 1);
	अगर (ret) अणु
		clear_bit(0, &wdt_is_active);
		वापस ret;
	पूर्ण

	file->निजी_data = mpc52xx_gpt_wdt;
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक mpc52xx_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* note: releasing the wdt in NOWAYOUT-mode करोes not stop it */
#अगर !defined(CONFIG_WATCHDOG_NOWAYOUT)
	काष्ठा mpc52xx_gpt_priv *gpt_wdt = file->निजी_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gpt_wdt->lock, flags);
	clrbits32(&gpt_wdt->regs->mode,
		  MPC52xx_GPT_MODE_COUNTER_ENABLE | MPC52xx_GPT_MODE_WDT_EN);
	gpt_wdt->wdt_mode &= ~MPC52xx_GPT_IS_WDT;
	raw_spin_unlock_irqrestore(&gpt_wdt->lock, flags);
#पूर्ण_अगर
	clear_bit(0, &wdt_is_active);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations mpc52xx_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= mpc52xx_wdt_ग_लिखो,
	.unlocked_ioctl = mpc52xx_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= mpc52xx_wdt_खोलो,
	.release	= mpc52xx_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice mpc52xx_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &mpc52xx_wdt_fops,
पूर्ण;

अटल पूर्णांक mpc52xx_gpt_wdt_init(व्योम)
अणु
	पूर्णांक err;

	/* try to रेजिस्टर the watchकरोg misc device */
	err = misc_रेजिस्टर(&mpc52xx_wdt_miscdev);
	अगर (err)
		pr_err("%s: cannot register watchdog device\n", WDT_IDENTITY);
	अन्यथा
		pr_info("%s: watchdog device registered\n", WDT_IDENTITY);
	वापस err;
पूर्ण

अटल पूर्णांक mpc52xx_gpt_wdt_setup(काष्ठा mpc52xx_gpt_priv *gpt,
				 स्थिर u32 *period)
अणु
	u64 real_समयout;

	/* remember the gpt क्रम the wdt operation */
	mpc52xx_gpt_wdt = gpt;

	/* configure the wdt अगर the device tree contained a समयout */
	अगर (!period || *period == 0)
		वापस 0;

	real_समयout = (u64) *period * 1000000000ULL;
	अगर (mpc52xx_gpt_करो_start(gpt, real_समयout, 0, 1))
		dev_warn(gpt->dev, "starting as wdt failed\n");
	अन्यथा
		dev_info(gpt->dev, "watchdog set to %us timeout\n", *period);
	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक mpc52xx_gpt_wdt_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mpc52xx_gpt_wdt_setup(काष्ठा mpc52xx_gpt_priv *gpt,
					स्थिर u32 *period)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर	/*  CONFIG_MPC5200_WDT	*/

/* ---------------------------------------------------------------------
 * of_platक्रमm bus binding code
 */
अटल पूर्णांक mpc52xx_gpt_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mpc52xx_gpt_priv *gpt;

	gpt = devm_kzalloc(&ofdev->dev, माप *gpt, GFP_KERNEL);
	अगर (!gpt)
		वापस -ENOMEM;

	raw_spin_lock_init(&gpt->lock);
	gpt->dev = &ofdev->dev;
	gpt->ipb_freq = mpc5xxx_get_bus_frequency(ofdev->dev.of_node);
	gpt->regs = of_iomap(ofdev->dev.of_node, 0);
	अगर (!gpt->regs)
		वापस -ENOMEM;

	dev_set_drvdata(&ofdev->dev, gpt);

	mpc52xx_gpt_gpio_setup(gpt, ofdev->dev.of_node);
	mpc52xx_gpt_irq_setup(gpt, ofdev->dev.of_node);

	mutex_lock(&mpc52xx_gpt_list_mutex);
	list_add(&gpt->list, &mpc52xx_gpt_list);
	mutex_unlock(&mpc52xx_gpt_list_mutex);

	/* check अगर this device could be a watchकरोg */
	अगर (of_get_property(ofdev->dev.of_node, "fsl,has-wdt", शून्य) ||
	    of_get_property(ofdev->dev.of_node, "has-wdt", शून्य)) अणु
		स्थिर u32 *on_boot_wdt;

		gpt->wdt_mode = MPC52xx_GPT_CAN_WDT;
		on_boot_wdt = of_get_property(ofdev->dev.of_node,
					      "fsl,wdt-on-boot", शून्य);
		अगर (on_boot_wdt) अणु
			dev_info(gpt->dev, "used as watchdog\n");
			gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
		पूर्ण अन्यथा
			dev_info(gpt->dev, "can function as watchdog\n");
		mpc52xx_gpt_wdt_setup(gpt, on_boot_wdt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_gpt_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस -EBUSY;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_gpt_match[] = अणु
	अणु .compatible = "fsl,mpc5200-gpt", पूर्ण,

	/* Depreciated compatible values; करोn't use क्रम new dts files */
	अणु .compatible = "fsl,mpc5200-gpt-gpio", पूर्ण,
	अणु .compatible = "mpc5200-gpt", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mpc52xx_gpt_driver = अणु
	.driver = अणु
		.name = "mpc52xx-gpt",
		.of_match_table = mpc52xx_gpt_match,
	पूर्ण,
	.probe = mpc52xx_gpt_probe,
	.हटाओ = mpc52xx_gpt_हटाओ,
पूर्ण;

अटल पूर्णांक __init mpc52xx_gpt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpc52xx_gpt_driver);
पूर्ण

/* Make sure GPIOs and IRQs get set up beक्रमe anyone tries to use them */
subsys_initcall(mpc52xx_gpt_init);
device_initcall(mpc52xx_gpt_wdt_init);
