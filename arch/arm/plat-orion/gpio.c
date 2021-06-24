<शैली गुरु>
/*
 * arch/arm/plat-orion/gpio.c
 *
 * Marvell Orion SoC GPIO handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <plat/orion-gpपन.स>

/*
 * GPIO unit रेजिस्टर offsets.
 */
#घोषणा GPIO_OUT_OFF		0x0000
#घोषणा GPIO_IO_CONF_OFF	0x0004
#घोषणा GPIO_BLINK_EN_OFF	0x0008
#घोषणा GPIO_IN_POL_OFF		0x000c
#घोषणा GPIO_DATA_IN_OFF	0x0010
#घोषणा GPIO_EDGE_CAUSE_OFF	0x0014
#घोषणा GPIO_EDGE_MASK_OFF	0x0018
#घोषणा GPIO_LEVEL_MASK_OFF	0x001c

काष्ठा orion_gpio_chip अणु
	काष्ठा gpio_chip	chip;
	spinlock_t		lock;
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		valid_input;
	अचिन्हित दीर्घ		valid_output;
	पूर्णांक			mask_offset;
	पूर्णांक			secondary_irq_base;
	काष्ठा irq_करोमुख्य       *करोमुख्य;
पूर्ण;

अटल व्योम __iomem *GPIO_OUT(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_OUT_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_IO_CONF(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_IO_CONF_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_BLINK_EN(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_BLINK_EN_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_IN_POL(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_IN_POL_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_DATA_IN(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_DATA_IN_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_EDGE_CAUSE(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + GPIO_EDGE_CAUSE_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_EDGE_MASK(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + ochip->mask_offset + GPIO_EDGE_MASK_OFF;
पूर्ण

अटल व्योम __iomem *GPIO_LEVEL_MASK(काष्ठा orion_gpio_chip *ochip)
अणु
	वापस ochip->base + ochip->mask_offset + GPIO_LEVEL_MASK_OFF;
पूर्ण


अटल काष्ठा orion_gpio_chip orion_gpio_chips[2];
अटल पूर्णांक orion_gpio_chip_count;

अटल अंतरभूत व्योम
__set_direction(काष्ठा orion_gpio_chip *ochip, अचिन्हित pin, पूर्णांक input)
अणु
	u32 u;

	u = पढ़ोl(GPIO_IO_CONF(ochip));
	अगर (input)
		u |= 1 << pin;
	अन्यथा
		u &= ~(1 << pin);
	ग_लिखोl(u, GPIO_IO_CONF(ochip));
पूर्ण

अटल व्योम __set_level(काष्ठा orion_gpio_chip *ochip, अचिन्हित pin, पूर्णांक high)
अणु
	u32 u;

	u = पढ़ोl(GPIO_OUT(ochip));
	अगर (high)
		u |= 1 << pin;
	अन्यथा
		u &= ~(1 << pin);
	ग_लिखोl(u, GPIO_OUT(ochip));
पूर्ण

अटल अंतरभूत व्योम
__set_blinking(काष्ठा orion_gpio_chip *ochip, अचिन्हित pin, पूर्णांक blink)
अणु
	u32 u;

	u = पढ़ोl(GPIO_BLINK_EN(ochip));
	अगर (blink)
		u |= 1 << pin;
	अन्यथा
		u &= ~(1 << pin);
	ग_लिखोl(u, GPIO_BLINK_EN(ochip));
पूर्ण

अटल अंतरभूत पूर्णांक
orion_gpio_is_valid(काष्ठा orion_gpio_chip *ochip, अचिन्हित pin, पूर्णांक mode)
अणु
	अगर (pin >= ochip->chip.ngpio)
		जाओ err_out;

	अगर ((mode & GPIO_INPUT_OK) && !test_bit(pin, &ochip->valid_input))
		जाओ err_out;

	अगर ((mode & GPIO_OUTPUT_OK) && !test_bit(pin, &ochip->valid_output))
		जाओ err_out;

	वापस 1;

err_out:
	pr_debug("%s: invalid GPIO %d\n", __func__, pin);
	वापस false;
पूर्ण

/*
 * GPIO primitives.
 */
अटल पूर्णांक orion_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);

	अगर (orion_gpio_is_valid(ochip, pin, GPIO_INPUT_OK) ||
	    orion_gpio_is_valid(ochip, pin, GPIO_OUTPUT_OK))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक orion_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	अगर (!orion_gpio_is_valid(ochip, pin, GPIO_INPUT_OK))
		वापस -EINVAL;

	spin_lock_irqsave(&ochip->lock, flags);
	__set_direction(ochip, pin, 1);
	spin_unlock_irqrestore(&ochip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);
	पूर्णांक val;

	अगर (पढ़ोl(GPIO_IO_CONF(ochip)) & (1 << pin)) अणु
		val = पढ़ोl(GPIO_DATA_IN(ochip)) ^ पढ़ोl(GPIO_IN_POL(ochip));
	पूर्ण अन्यथा अणु
		val = पढ़ोl(GPIO_OUT(ochip));
	पूर्ण

	वापस (val >> pin) & 1;
पूर्ण

अटल पूर्णांक
orion_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	अगर (!orion_gpio_is_valid(ochip, pin, GPIO_OUTPUT_OK))
		वापस -EINVAL;

	spin_lock_irqsave(&ochip->lock, flags);
	__set_blinking(ochip, pin, 0);
	__set_level(ochip, pin, value);
	__set_direction(ochip, pin, 0);
	spin_unlock_irqrestore(&ochip->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम orion_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ochip->lock, flags);
	__set_level(ochip, pin, value);
	spin_unlock_irqrestore(&ochip->lock, flags);
पूर्ण

अटल पूर्णांक orion_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);

	वापस irq_create_mapping(ochip->करोमुख्य,
				  ochip->secondary_irq_base + pin);
पूर्ण

/*
 * Orion-specअगरic GPIO API extensions.
 */
अटल काष्ठा orion_gpio_chip *orion_gpio_chip_find(पूर्णांक pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < orion_gpio_chip_count; i++) अणु
		काष्ठा orion_gpio_chip *ochip = orion_gpio_chips + i;
		काष्ठा gpio_chip *chip = &ochip->chip;

		अगर (pin >= chip->base && pin < chip->base + chip->ngpio)
			वापस ochip;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init orion_gpio_set_unused(अचिन्हित pin)
अणु
	काष्ठा orion_gpio_chip *ochip = orion_gpio_chip_find(pin);

	अगर (ochip == शून्य)
		वापस;

	pin -= ochip->chip.base;

	/* Configure as output, drive low. */
	__set_level(ochip, pin, 0);
	__set_direction(ochip, pin, 0);
पूर्ण

व्योम __init orion_gpio_set_valid(अचिन्हित pin, पूर्णांक mode)
अणु
	काष्ठा orion_gpio_chip *ochip = orion_gpio_chip_find(pin);

	अगर (ochip == शून्य)
		वापस;

	pin -= ochip->chip.base;

	अगर (mode == 1)
		mode = GPIO_INPUT_OK | GPIO_OUTPUT_OK;

	अगर (mode & GPIO_INPUT_OK)
		__set_bit(pin, &ochip->valid_input);
	अन्यथा
		__clear_bit(pin, &ochip->valid_input);

	अगर (mode & GPIO_OUTPUT_OK)
		__set_bit(pin, &ochip->valid_output);
	अन्यथा
		__clear_bit(pin, &ochip->valid_output);
पूर्ण

व्योम orion_gpio_set_blink(अचिन्हित pin, पूर्णांक blink)
अणु
	काष्ठा orion_gpio_chip *ochip = orion_gpio_chip_find(pin);
	अचिन्हित दीर्घ flags;

	अगर (ochip == शून्य)
		वापस;

	spin_lock_irqsave(&ochip->lock, flags);
	__set_level(ochip, pin & 31, 0);
	__set_blinking(ochip, pin & 31, blink);
	spin_unlock_irqrestore(&ochip->lock, flags);
पूर्ण
EXPORT_SYMBOL(orion_gpio_set_blink);

#घोषणा ORION_BLINK_HALF_PERIOD 100 /* ms */

पूर्णांक orion_gpio_led_blink_set(काष्ठा gpio_desc *desc, पूर्णांक state,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	अचिन्हित gpio = desc_to_gpio(desc);

	अगर (delay_on && delay_off && !*delay_on && !*delay_off)
		*delay_on = *delay_off = ORION_BLINK_HALF_PERIOD;

	चयन (state) अणु
	हाल GPIO_LED_NO_BLINK_LOW:
	हाल GPIO_LED_NO_BLINK_HIGH:
		orion_gpio_set_blink(gpio, 0);
		gpio_set_value(gpio, state);
		अवरोध;
	हाल GPIO_LED_BLINK:
		orion_gpio_set_blink(gpio, 1);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(orion_gpio_led_blink_set);


/*****************************************************************************
 * Orion GPIO IRQ
 *
 * GPIO_IN_POL रेजिस्टर controls whether GPIO_DATA_IN will hold the same
 * value of the line or the opposite value.
 *
 * Level IRQ handlers: DATA_IN is used directly as cause रेजिस्टर.
 *                     Interrupt are masked by LEVEL_MASK रेजिस्टरs.
 * Edge IRQ handlers:  Change in DATA_IN are latched in EDGE_CAUSE.
 *                     Interrupt are masked by EDGE_MASK रेजिस्टरs.
 * Both-edge handlers: Similar to regular Edge handlers, but also swaps
 *                     the polarity to catch the next line transaction.
 *                     This is a race condition that might not perfectly
 *                     work on some use हालs.
 *
 * Every eight GPIO lines are grouped (OR'ed) beक्रमe going up to मुख्य
 * cause रेजिस्टर.
 *
 *                    EDGE  cause    mask
 *        data-in   /--------| |-----| |----\
 *     -----| |-----                         ---- to मुख्य cause reg
 *           X      \----------------| |----/
 *        polarity    LEVEL          mask
 *
 ****************************************************************************/

अटल पूर्णांक gpio_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा orion_gpio_chip *ochip = gc->निजी;
	पूर्णांक pin;
	u32 u;

	pin = d->hwirq - ochip->secondary_irq_base;

	u = पढ़ोl(GPIO_IO_CONF(ochip)) & (1 << pin);
	अगर (!u) अणु
		वापस -EINVAL;
	पूर्ण

	type &= IRQ_TYPE_SENSE_MASK;
	अगर (type == IRQ_TYPE_NONE)
		वापस -EINVAL;

	/* Check अगर we need to change chip and handler */
	अगर (!(ct->type & type))
		अगर (irq_setup_alt_chip(d, type))
			वापस -EINVAL;

	/*
	 * Configure पूर्णांकerrupt polarity.
	 */
	अगर (type == IRQ_TYPE_EDGE_RISING || type == IRQ_TYPE_LEVEL_HIGH) अणु
		u = पढ़ोl(GPIO_IN_POL(ochip));
		u &= ~(1 << pin);
		ग_लिखोl(u, GPIO_IN_POL(ochip));
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_EDGE_FALLING || type == IRQ_TYPE_LEVEL_LOW) अणु
		u = पढ़ोl(GPIO_IN_POL(ochip));
		u |= 1 << pin;
		ग_लिखोl(u, GPIO_IN_POL(ochip));
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_EDGE_BOTH) अणु
		u32 v;

		v = पढ़ोl(GPIO_IN_POL(ochip)) ^ पढ़ोl(GPIO_DATA_IN(ochip));

		/*
		 * set initial polarity based on current input level
		 */
		u = पढ़ोl(GPIO_IN_POL(ochip));
		अगर (v & (1 << pin))
			u |= 1 << pin;		/* falling */
		अन्यथा
			u &= ~(1 << pin);	/* rising */
		ग_लिखोl(u, GPIO_IN_POL(ochip));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा orion_gpio_chip *ochip = irq_desc_get_handler_data(desc);
	u32 cause, type;
	पूर्णांक i;

	अगर (ochip == शून्य)
		वापस;

	cause = पढ़ोl(GPIO_DATA_IN(ochip)) & पढ़ोl(GPIO_LEVEL_MASK(ochip));
	cause |= पढ़ोl(GPIO_EDGE_CAUSE(ochip)) & पढ़ोl(GPIO_EDGE_MASK(ochip));

	क्रम (i = 0; i < ochip->chip.ngpio; i++) अणु
		पूर्णांक irq;

		irq = ochip->secondary_irq_base + i;

		अगर (!(cause & (1 << i)))
			जारी;

		type = irq_get_trigger_type(irq);
		अगर ((type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH) अणु
			/* Swap polarity (race with GPIO line) */
			u32 polarity;

			polarity = पढ़ोl(GPIO_IN_POL(ochip));
			polarity ^= 1 << i;
			ग_लिखोl(polarity, GPIO_IN_POL(ochip));
		पूर्ण
		generic_handle_irq(irq);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल व्योम orion_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु

	काष्ठा orion_gpio_chip *ochip = gpiochip_get_data(chip);
	u32 out, io_conf, blink, in_pol, data_in, cause, edg_msk, lvl_msk;
	स्थिर अक्षर *label;
	पूर्णांक i;

	out	= पढ़ोl_relaxed(GPIO_OUT(ochip));
	io_conf	= पढ़ोl_relaxed(GPIO_IO_CONF(ochip));
	blink	= पढ़ोl_relaxed(GPIO_BLINK_EN(ochip));
	in_pol	= पढ़ोl_relaxed(GPIO_IN_POL(ochip));
	data_in	= पढ़ोl_relaxed(GPIO_DATA_IN(ochip));
	cause	= पढ़ोl_relaxed(GPIO_EDGE_CAUSE(ochip));
	edg_msk	= पढ़ोl_relaxed(GPIO_EDGE_MASK(ochip));
	lvl_msk	= पढ़ोl_relaxed(GPIO_LEVEL_MASK(ochip));

	क्रम_each_requested_gpio(chip, i, label) अणु
		u32 msk;
		bool is_out;

		msk = 1 << i;
		is_out = !(io_conf & msk);

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s)", chip->base + i, label);

		अगर (is_out) अणु
			seq_म_लिखो(s, " out %s %s\n",
				   out & msk ? "hi" : "lo",
				   blink & msk ? "(blink )" : "");
			जारी;
		पूर्ण

		seq_म_लिखो(s, " in  %s (act %s) - IRQ",
			   (data_in ^ in_pol) & msk  ? "hi" : "lo",
			   in_pol & msk ? "lo" : "hi");
		अगर (!((edg_msk | lvl_msk) & msk)) अणु
			seq_माला_दो(s, " disabled\n");
			जारी;
		पूर्ण
		अगर (edg_msk & msk)
			seq_माला_दो(s, " edge ");
		अगर (lvl_msk & msk)
			seq_माला_दो(s, " level");
		seq_म_लिखो(s, " (%s)\n", cause & msk ? "pending" : "clear  ");
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा orion_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल व्योम orion_gpio_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 reg_val;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	reg_val = irq_reg_पढ़ोl(gc, ct->regs.mask);
	reg_val |= mask;
	irq_reg_ग_लिखोl(gc, reg_val, ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम orion_gpio_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;
	u32 reg_val;

	irq_gc_lock(gc);
	reg_val = irq_reg_पढ़ोl(gc, ct->regs.mask);
	reg_val &= ~mask;
	irq_reg_ग_लिखोl(gc, reg_val, ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण

व्योम __init orion_gpio_init(काष्ठा device_node *np,
			    पूर्णांक gpio_base, पूर्णांक ngpio,
			    व्योम __iomem *base, पूर्णांक mask_offset,
			    पूर्णांक secondary_irq_base,
			    पूर्णांक irqs[4])
अणु
	काष्ठा orion_gpio_chip *ochip;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अक्षर gc_label[16];
	पूर्णांक i;

	अगर (orion_gpio_chip_count == ARRAY_SIZE(orion_gpio_chips))
		वापस;

	snम_लिखो(gc_label, माप(gc_label), "orion_gpio%d",
		orion_gpio_chip_count);

	ochip = orion_gpio_chips + orion_gpio_chip_count;
	ochip->chip.label = kstrdup(gc_label, GFP_KERNEL);
	ochip->chip.request = orion_gpio_request;
	ochip->chip.direction_input = orion_gpio_direction_input;
	ochip->chip.get = orion_gpio_get;
	ochip->chip.direction_output = orion_gpio_direction_output;
	ochip->chip.set = orion_gpio_set;
	ochip->chip.to_irq = orion_gpio_to_irq;
	ochip->chip.base = gpio_base;
	ochip->chip.ngpio = ngpio;
	ochip->chip.can_sleep = 0;
#अगर_घोषित CONFIG_OF
	ochip->chip.of_node = np;
#पूर्ण_अगर
	ochip->chip.dbg_show = orion_gpio_dbg_show;

	spin_lock_init(&ochip->lock);
	ochip->base = (व्योम __iomem *)base;
	ochip->valid_input = 0;
	ochip->valid_output = 0;
	ochip->mask_offset = mask_offset;
	ochip->secondary_irq_base = secondary_irq_base;

	gpiochip_add_data(&ochip->chip, ochip);

	/*
	 * Mask and clear GPIO पूर्णांकerrupts.
	 */
	ग_लिखोl(0, GPIO_EDGE_CAUSE(ochip));
	ग_लिखोl(0, GPIO_EDGE_MASK(ochip));
	ग_लिखोl(0, GPIO_LEVEL_MASK(ochip));

	/* Setup the पूर्णांकerrupt handlers. Each chip can have up to 4
	 * पूर्णांकerrupt handlers, with each handler dealing with 8 GPIO
	 * pins. */

	क्रम (i = 0; i < 4; i++) अणु
		अगर (irqs[i]) अणु
			irq_set_chained_handler_and_data(irqs[i],
							 gpio_irq_handler,
							 ochip);
		पूर्ण
	पूर्ण

	gc = irq_alloc_generic_chip("orion_gpio_irq", 2,
				    secondary_irq_base,
				    ochip->base, handle_level_irq);
	gc->निजी = ochip;
	ct = gc->chip_types;
	ct->regs.mask = ochip->mask_offset + GPIO_LEVEL_MASK_OFF;
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->chip.irq_mask = orion_gpio_mask_irq;
	ct->chip.irq_unmask = orion_gpio_unmask_irq;
	ct->chip.irq_set_type = gpio_irq_set_type;
	ct->chip.name = ochip->chip.label;

	ct++;
	ct->regs.mask = ochip->mask_offset + GPIO_EDGE_MASK_OFF;
	ct->regs.ack = GPIO_EDGE_CAUSE_OFF;
	ct->type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	ct->chip.irq_ack = irq_gc_ack_clr_bit;
	ct->chip.irq_mask = orion_gpio_mask_irq;
	ct->chip.irq_unmask = orion_gpio_unmask_irq;
	ct->chip.irq_set_type = gpio_irq_set_type;
	ct->handler = handle_edge_irq;
	ct->chip.name = ochip->chip.label;

	irq_setup_generic_chip(gc, IRQ_MSK(ngpio), IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST, IRQ_LEVEL | IRQ_NOPROBE);

	/* Setup irq करोमुख्य on top of the generic chip. */
	ochip->करोमुख्य = irq_करोमुख्य_add_legacy(np,
					      ochip->chip.ngpio,
					      ochip->secondary_irq_base,
					      ochip->secondary_irq_base,
					      &irq_करोमुख्य_simple_ops,
					      ochip);
	अगर (!ochip->करोमुख्य)
		panic("%s: couldn't allocate irq domain (DT).\n",
		      ochip->chip.label);

	orion_gpio_chip_count++;
पूर्ण
