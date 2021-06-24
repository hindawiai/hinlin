<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * driver/mfd/asic3.c
 *
 * Compaq ASIC3 support.
 *
 * Copyright 2001 Compaq Computer Corporation.
 * Copyright 2004-2005 Phil Blundell
 * Copyright 2007-2008 OpenedHand Ltd.
 *
 * Authors: Phil Blundell <pb@handhelds.org>,
 *	    Samuel Ortiz <sameo@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/asic3.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ds1wm.h>
#समावेश <linux/mfd/पंचांगपन.स>

#समावेश <linux/mmc/host.h>

क्रमागत अणु
	ASIC3_CLOCK_SPI,
	ASIC3_CLOCK_OWM,
	ASIC3_CLOCK_PWM0,
	ASIC3_CLOCK_PWM1,
	ASIC3_CLOCK_LED0,
	ASIC3_CLOCK_LED1,
	ASIC3_CLOCK_LED2,
	ASIC3_CLOCK_SD_HOST,
	ASIC3_CLOCK_SD_BUS,
	ASIC3_CLOCK_SMBUS,
	ASIC3_CLOCK_EX0,
	ASIC3_CLOCK_EX1,
पूर्ण;

काष्ठा asic3_clk अणु
	पूर्णांक enabled;
	अचिन्हित पूर्णांक cdex;
	अचिन्हित दीर्घ rate;
पूर्ण;

#घोषणा INIT_CDEX(_name, _rate)	\
	[ASIC3_CLOCK_##_name] = अणु		\
		.cdex = CLOCK_CDEX_##_name,	\
		.rate = _rate,			\
	पूर्ण

अटल काष्ठा asic3_clk asic3_clk_init[] __initdata = अणु
	INIT_CDEX(SPI, 0),
	INIT_CDEX(OWM, 5000000),
	INIT_CDEX(PWM0, 0),
	INIT_CDEX(PWM1, 0),
	INIT_CDEX(LED0, 0),
	INIT_CDEX(LED1, 0),
	INIT_CDEX(LED2, 0),
	INIT_CDEX(SD_HOST, 24576000),
	INIT_CDEX(SD_BUS, 12288000),
	INIT_CDEX(SMBUS, 0),
	INIT_CDEX(EX0, 32768),
	INIT_CDEX(EX1, 24576000),
पूर्ण;

काष्ठा asic3 अणु
	व्योम __iomem *mapping;
	अचिन्हित पूर्णांक bus_shअगरt;
	अचिन्हित पूर्णांक irq_nr;
	अचिन्हित पूर्णांक irq_base;
	raw_spinlock_t lock;
	u16 irq_bothedge[4];
	काष्ठा gpio_chip gpio;
	काष्ठा device *dev;
	व्योम __iomem *पंचांगio_cnf;

	काष्ठा asic3_clk घड़ीs[ARRAY_SIZE(asic3_clk_init)];
पूर्ण;

अटल पूर्णांक asic3_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset);

व्योम asic3_ग_लिखो_रेजिस्टर(काष्ठा asic3 *asic, अचिन्हित पूर्णांक reg, u32 value)
अणु
	ioग_लिखो16(value, asic->mapping +
		  (reg >> asic->bus_shअगरt));
पूर्ण
EXPORT_SYMBOL_GPL(asic3_ग_लिखो_रेजिस्टर);

u32 asic3_पढ़ो_रेजिस्टर(काष्ठा asic3 *asic, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो16(asic->mapping +
			(reg >> asic->bus_shअगरt));
पूर्ण
EXPORT_SYMBOL_GPL(asic3_पढ़ो_रेजिस्टर);

अटल व्योम asic3_set_रेजिस्टर(काष्ठा asic3 *asic, u32 reg, u32 bits, bool set)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&asic->lock, flags);
	val = asic3_पढ़ो_रेजिस्टर(asic, reg);
	अगर (set)
		val |= bits;
	अन्यथा
		val &= ~bits;
	asic3_ग_लिखो_रेजिस्टर(asic, reg, val);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

/* IRQs */
#घोषणा MAX_ASIC_ISR_LOOPS    20
#घोषणा ASIC3_GPIO_BASE_INCR \
	(ASIC3_GPIO_B_BASE - ASIC3_GPIO_A_BASE)

अटल व्योम asic3_irq_flip_edge(काष्ठा asic3 *asic,
				u32 base, पूर्णांक bit)
अणु
	u16 edge;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&asic->lock, flags);
	edge = asic3_पढ़ो_रेजिस्टर(asic,
				   base + ASIC3_GPIO_EDGE_TRIGGER);
	edge ^= bit;
	asic3_ग_लिखो_रेजिस्टर(asic,
			     base + ASIC3_GPIO_EDGE_TRIGGER, edge);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल व्योम asic3_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा asic3 *asic = irq_desc_get_handler_data(desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	पूर्णांक iter, i;
	अचिन्हित दीर्घ flags;

	data->chip->irq_ack(data);

	क्रम (iter = 0 ; iter < MAX_ASIC_ISR_LOOPS; iter++) अणु
		u32 status;
		पूर्णांक bank;

		raw_spin_lock_irqsave(&asic->lock, flags);
		status = asic3_पढ़ो_रेजिस्टर(asic,
					     ASIC3_OFFSET(INTR, P_INT_STAT));
		raw_spin_unlock_irqrestore(&asic->lock, flags);

		/* Check all ten रेजिस्टर bits */
		अगर ((status & 0x3ff) == 0)
			अवरोध;

		/* Handle GPIO IRQs */
		क्रम (bank = 0; bank < ASIC3_NUM_GPIO_BANKS; bank++) अणु
			अगर (status & (1 << bank)) अणु
				अचिन्हित दीर्घ base, istat;

				base = ASIC3_GPIO_A_BASE
				       + bank * ASIC3_GPIO_BASE_INCR;
				raw_spin_lock_irqsave(&asic->lock, flags);
				istat = asic3_पढ़ो_रेजिस्टर(asic,
							    base +
							    ASIC3_GPIO_INT_STATUS);
				/* Clearing IntStatus */
				asic3_ग_लिखो_रेजिस्टर(asic,
						     base +
						     ASIC3_GPIO_INT_STATUS, 0);
				raw_spin_unlock_irqrestore(&asic->lock, flags);

				क्रम (i = 0; i < ASIC3_GPIOS_PER_BANK; i++) अणु
					पूर्णांक bit = (1 << i);
					अचिन्हित पूर्णांक irqnr;

					अगर (!(istat & bit))
						जारी;

					irqnr = asic->irq_base +
						(ASIC3_GPIOS_PER_BANK * bank)
						+ i;
					generic_handle_irq(irqnr);
					अगर (asic->irq_bothedge[bank] & bit)
						asic3_irq_flip_edge(asic, base,
								    bit);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Handle reमुख्यing IRQs in the status रेजिस्टर */
		क्रम (i = ASIC3_NUM_GPIOS; i < ASIC3_NR_IRQS; i++) अणु
			/* They start at bit 4 and go up */
			अगर (status & (1 << (i - ASIC3_NUM_GPIOS + 4)))
				generic_handle_irq(asic->irq_base + i);
		पूर्ण
	पूर्ण

	अगर (iter >= MAX_ASIC_ISR_LOOPS)
		dev_err(asic->dev, "interrupt processing overrun\n");
पूर्ण

अटल अंतरभूत पूर्णांक asic3_irq_to_bank(काष्ठा asic3 *asic, पूर्णांक irq)
अणु
	पूर्णांक n;

	n = (irq - asic->irq_base) >> 4;

	वापस (n * (ASIC3_GPIO_B_BASE - ASIC3_GPIO_A_BASE));
पूर्ण

अटल अंतरभूत पूर्णांक asic3_irq_to_index(काष्ठा asic3 *asic, पूर्णांक irq)
अणु
	वापस (irq - asic->irq_base) & 0xf;
पूर्ण

अटल व्योम asic3_mask_gpio_irq(काष्ठा irq_data *data)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 val, bank, index;
	अचिन्हित दीर्घ flags;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);

	raw_spin_lock_irqsave(&asic->lock, flags);
	val = asic3_पढ़ो_रेजिस्टर(asic, bank + ASIC3_GPIO_MASK);
	val |= 1 << index;
	asic3_ग_लिखो_रेजिस्टर(asic, bank + ASIC3_GPIO_MASK, val);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल व्योम asic3_mask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	पूर्णांक regval;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&asic->lock, flags);
	regval = asic3_पढ़ो_रेजिस्टर(asic,
				     ASIC3_INTR_BASE +
				     ASIC3_INTR_INT_MASK);

	regval &= ~(ASIC3_INTMASK_MASK0 <<
		    (data->irq - (asic->irq_base + ASIC3_NUM_GPIOS)));

	asic3_ग_लिखो_रेजिस्टर(asic,
			     ASIC3_INTR_BASE +
			     ASIC3_INTR_INT_MASK,
			     regval);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल व्योम asic3_unmask_gpio_irq(काष्ठा irq_data *data)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 val, bank, index;
	अचिन्हित दीर्घ flags;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);

	raw_spin_lock_irqsave(&asic->lock, flags);
	val = asic3_पढ़ो_रेजिस्टर(asic, bank + ASIC3_GPIO_MASK);
	val &= ~(1 << index);
	asic3_ग_लिखो_रेजिस्टर(asic, bank + ASIC3_GPIO_MASK, val);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल व्योम asic3_unmask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	पूर्णांक regval;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&asic->lock, flags);
	regval = asic3_पढ़ो_रेजिस्टर(asic,
				     ASIC3_INTR_BASE +
				     ASIC3_INTR_INT_MASK);

	regval |= (ASIC3_INTMASK_MASK0 <<
		   (data->irq - (asic->irq_base + ASIC3_NUM_GPIOS)));

	asic3_ग_लिखो_रेजिस्टर(asic,
			     ASIC3_INTR_BASE +
			     ASIC3_INTR_INT_MASK,
			     regval);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल पूर्णांक asic3_gpio_irq_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 bank, index;
	u16 trigger, level, edge, bit;
	अचिन्हित दीर्घ flags;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);
	bit = 1<<index;

	raw_spin_lock_irqsave(&asic->lock, flags);
	level = asic3_पढ़ो_रेजिस्टर(asic,
				    bank + ASIC3_GPIO_LEVEL_TRIGGER);
	edge = asic3_पढ़ो_रेजिस्टर(asic,
				   bank + ASIC3_GPIO_EDGE_TRIGGER);
	trigger = asic3_पढ़ो_रेजिस्टर(asic,
				      bank + ASIC3_GPIO_TRIGGER_TYPE);
	asic->irq_bothedge[(data->irq - asic->irq_base) >> 4] &= ~bit;

	अगर (type == IRQ_TYPE_EDGE_RISING) अणु
		trigger |= bit;
		edge |= bit;
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_EDGE_FALLING) अणु
		trigger |= bit;
		edge &= ~bit;
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_EDGE_BOTH) अणु
		trigger |= bit;
		अगर (asic3_gpio_get(&asic->gpio, data->irq - asic->irq_base))
			edge &= ~bit;
		अन्यथा
			edge |= bit;
		asic->irq_bothedge[(data->irq - asic->irq_base) >> 4] |= bit;
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_LEVEL_LOW) अणु
		trigger &= ~bit;
		level &= ~bit;
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_LEVEL_HIGH) अणु
		trigger &= ~bit;
		level |= bit;
	पूर्ण अन्यथा अणु
		/*
		 * अगर type == IRQ_TYPE_NONE, we should mask पूर्णांकerrupts, but
		 * be careful to not unmask them अगर mask was also called.
		 * Probably need पूर्णांकernal state क्रम mask.
		 */
		dev_notice(asic->dev, "irq type not changed\n");
	पूर्ण
	asic3_ग_लिखो_रेजिस्टर(asic, bank + ASIC3_GPIO_LEVEL_TRIGGER,
			     level);
	asic3_ग_लिखो_रेजिस्टर(asic, bank + ASIC3_GPIO_EDGE_TRIGGER,
			     edge);
	asic3_ग_लिखो_रेजिस्टर(asic, bank + ASIC3_GPIO_TRIGGER_TYPE,
			     trigger);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक asic3_gpio_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 bank, index;
	u16 bit;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);
	bit = 1<<index;

	asic3_set_रेजिस्टर(asic, bank + ASIC3_GPIO_SLEEP_MASK, bit, !on);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip asic3_gpio_irq_chip = अणु
	.name		= "ASIC3-GPIO",
	.irq_ack	= asic3_mask_gpio_irq,
	.irq_mask	= asic3_mask_gpio_irq,
	.irq_unmask	= asic3_unmask_gpio_irq,
	.irq_set_type	= asic3_gpio_irq_type,
	.irq_set_wake	= asic3_gpio_irq_set_wake,
पूर्ण;

अटल काष्ठा irq_chip asic3_irq_chip = अणु
	.name		= "ASIC3",
	.irq_ack	= asic3_mask_irq,
	.irq_mask	= asic3_mask_irq,
	.irq_unmask	= asic3_unmask_irq,
पूर्ण;

अटल पूर्णांक __init asic3_irq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ clksel = 0;
	अचिन्हित पूर्णांक irq, irq_base;
	पूर्णांक ret;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	asic->irq_nr = ret;

	/* turn on घड़ी to IRQ controller */
	clksel |= CLOCK_SEL_CX;
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, SEL),
			     clksel);

	irq_base = asic->irq_base;

	क्रम (irq = irq_base; irq < irq_base + ASIC3_NR_IRQS; irq++) अणु
		अगर (irq < asic->irq_base + ASIC3_NUM_GPIOS)
			irq_set_chip(irq, &asic3_gpio_irq_chip);
		अन्यथा
			irq_set_chip(irq, &asic3_irq_chip);

		irq_set_chip_data(irq, asic);
		irq_set_handler(irq, handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(INTR, INT_MASK),
			     ASIC3_INTMASK_GINTMASK);

	irq_set_chained_handler_and_data(asic->irq_nr, asic3_irq_demux, asic);
	irq_set_irq_type(asic->irq_nr, IRQ_TYPE_EDGE_RISING);

	वापस 0;
पूर्ण

अटल व्योम asic3_irq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक irq, irq_base;

	irq_base = asic->irq_base;

	क्रम (irq = irq_base; irq < irq_base + ASIC3_NR_IRQS; irq++) अणु
		irq_set_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
		irq_set_chip_and_handler(irq, शून्य, शून्य);
		irq_set_chip_data(irq, शून्य);
	पूर्ण
	irq_set_chained_handler(asic->irq_nr, शून्य);
पूर्ण

/* GPIOs */
अटल पूर्णांक asic3_gpio_direction(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक out)
अणु
	u32 mask = ASIC3_GPIO_TO_MASK(offset), out_reg;
	अचिन्हित पूर्णांक gpio_base;
	अचिन्हित दीर्घ flags;
	काष्ठा asic3 *asic;

	asic = gpiochip_get_data(chip);
	gpio_base = ASIC3_GPIO_TO_BASE(offset);

	अगर (gpio_base > ASIC3_GPIO_D_BASE) अणु
		dev_err(asic->dev, "Invalid base (0x%x) for gpio %d\n",
			gpio_base, offset);
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&asic->lock, flags);

	out_reg = asic3_पढ़ो_रेजिस्टर(asic, gpio_base + ASIC3_GPIO_सूचीECTION);

	/* Input is 0, Output is 1 */
	अगर (out)
		out_reg |= mask;
	अन्यथा
		out_reg &= ~mask;

	asic3_ग_लिखो_रेजिस्टर(asic, gpio_base + ASIC3_GPIO_सूचीECTION, out_reg);

	raw_spin_unlock_irqrestore(&asic->lock, flags);

	वापस 0;

पूर्ण

अटल पूर्णांक asic3_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित offset)
अणु
	वापस asic3_gpio_direction(chip, offset, 0);
पूर्ण

अटल पूर्णांक asic3_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित offset, पूर्णांक value)
अणु
	वापस asic3_gpio_direction(chip, offset, 1);
पूर्ण

अटल पूर्णांक asic3_gpio_get(काष्ठा gpio_chip *chip,
			  अचिन्हित offset)
अणु
	अचिन्हित पूर्णांक gpio_base;
	u32 mask = ASIC3_GPIO_TO_MASK(offset);
	काष्ठा asic3 *asic;

	asic = gpiochip_get_data(chip);
	gpio_base = ASIC3_GPIO_TO_BASE(offset);

	अगर (gpio_base > ASIC3_GPIO_D_BASE) अणु
		dev_err(asic->dev, "Invalid base (0x%x) for gpio %d\n",
			gpio_base, offset);
		वापस -EINVAL;
	पूर्ण

	वापस !!(asic3_पढ़ो_रेजिस्टर(asic,
				      gpio_base + ASIC3_GPIO_STATUS) & mask);
पूर्ण

अटल व्योम asic3_gpio_set(काष्ठा gpio_chip *chip,
			   अचिन्हित offset, पूर्णांक value)
अणु
	u32 mask, out_reg;
	अचिन्हित पूर्णांक gpio_base;
	अचिन्हित दीर्घ flags;
	काष्ठा asic3 *asic;

	asic = gpiochip_get_data(chip);
	gpio_base = ASIC3_GPIO_TO_BASE(offset);

	अगर (gpio_base > ASIC3_GPIO_D_BASE) अणु
		dev_err(asic->dev, "Invalid base (0x%x) for gpio %d\n",
			gpio_base, offset);
		वापस;
	पूर्ण

	mask = ASIC3_GPIO_TO_MASK(offset);

	raw_spin_lock_irqsave(&asic->lock, flags);

	out_reg = asic3_पढ़ो_रेजिस्टर(asic, gpio_base + ASIC3_GPIO_OUT);

	अगर (value)
		out_reg |= mask;
	अन्यथा
		out_reg &= ~mask;

	asic3_ग_लिखो_रेजिस्टर(asic, gpio_base + ASIC3_GPIO_OUT, out_reg);

	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल पूर्णांक asic3_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा asic3 *asic = gpiochip_get_data(chip);

	वापस asic->irq_base + offset;
पूर्ण

अटल __init पूर्णांक asic3_gpio_probe(काष्ठा platक्रमm_device *pdev,
				   u16 *gpio_config, पूर्णांक num)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);
	u16 alt_reg[ASIC3_NUM_GPIO_BANKS];
	u16 out_reg[ASIC3_NUM_GPIO_BANKS];
	u16 dir_reg[ASIC3_NUM_GPIO_BANKS];
	पूर्णांक i;

	स_रखो(alt_reg, 0, ASIC3_NUM_GPIO_BANKS * माप(u16));
	स_रखो(out_reg, 0, ASIC3_NUM_GPIO_BANKS * माप(u16));
	स_रखो(dir_reg, 0, ASIC3_NUM_GPIO_BANKS * माप(u16));

	/* Enable all GPIOs */
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_GPIO_OFFSET(A, MASK), 0xffff);
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_GPIO_OFFSET(B, MASK), 0xffff);
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_GPIO_OFFSET(C, MASK), 0xffff);
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_GPIO_OFFSET(D, MASK), 0xffff);

	क्रम (i = 0; i < num; i++) अणु
		u8 alt, pin, dir, init, bank_num, bit_num;
		u16 config = gpio_config[i];

		pin = ASIC3_CONFIG_GPIO_PIN(config);
		alt = ASIC3_CONFIG_GPIO_ALT(config);
		dir = ASIC3_CONFIG_GPIO_सूची(config);
		init = ASIC3_CONFIG_GPIO_INIT(config);

		bank_num = ASIC3_GPIO_TO_BANK(pin);
		bit_num = ASIC3_GPIO_TO_BIT(pin);

		alt_reg[bank_num] |= (alt << bit_num);
		out_reg[bank_num] |= (init << bit_num);
		dir_reg[bank_num] |= (dir << bit_num);
	पूर्ण

	क्रम (i = 0; i < ASIC3_NUM_GPIO_BANKS; i++) अणु
		asic3_ग_लिखो_रेजिस्टर(asic,
				     ASIC3_BANK_TO_BASE(i) +
				     ASIC3_GPIO_सूचीECTION,
				     dir_reg[i]);
		asic3_ग_लिखो_रेजिस्टर(asic,
				     ASIC3_BANK_TO_BASE(i) + ASIC3_GPIO_OUT,
				     out_reg[i]);
		asic3_ग_लिखो_रेजिस्टर(asic,
				     ASIC3_BANK_TO_BASE(i) +
				     ASIC3_GPIO_ALT_FUNCTION,
				     alt_reg[i]);
	पूर्ण

	वापस gpiochip_add_data(&asic->gpio, asic);
पूर्ण

अटल पूर्णांक asic3_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&asic->gpio);
	वापस 0;
पूर्ण

अटल व्योम asic3_clk_enable(काष्ठा asic3 *asic, काष्ठा asic3_clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	u32 cdex;

	raw_spin_lock_irqsave(&asic->lock, flags);
	अगर (clk->enabled++ == 0) अणु
		cdex = asic3_पढ़ो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, CDEX));
		cdex |= clk->cdex;
		asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, CDEX), cdex);
	पूर्ण
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

अटल व्योम asic3_clk_disable(काष्ठा asic3 *asic, काष्ठा asic3_clk *clk)
अणु
	अचिन्हित दीर्घ flags;
	u32 cdex;

	WARN_ON(clk->enabled == 0);

	raw_spin_lock_irqsave(&asic->lock, flags);
	अगर (--clk->enabled == 0) अणु
		cdex = asic3_पढ़ो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, CDEX));
		cdex &= ~clk->cdex;
		asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, CDEX), cdex);
	पूर्ण
	raw_spin_unlock_irqrestore(&asic->lock, flags);
पूर्ण

/* MFD cells (SPI, PWM, LED, DS1WM, MMC) */
अटल काष्ठा ds1wm_driver_data ds1wm_pdata = अणु
	.active_high = 1,
	.reset_recover_delay = 1,
पूर्ण;

अटल काष्ठा resource ds1wm_resources[] = अणु
	अणु
		.start = ASIC3_OWM_BASE,
		.end   = ASIC3_OWM_BASE + 0x13,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = ASIC3_IRQ_OWM,
		.end   = ASIC3_IRQ_OWM,
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ds1wm_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Turn on बाह्यal घड़ीs and the OWM घड़ी */
	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX0]);
	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX1]);
	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_OWM]);
	usleep_range(1000, 5000);

	/* Reset and enable DS1WM */
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, RESET),
			   ASIC3_EXTCF_OWM_RESET, 1);
	usleep_range(1000, 5000);
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, RESET),
			   ASIC3_EXTCF_OWM_RESET, 0);
	usleep_range(1000, 5000);
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_OWM_EN, 1);
	usleep_range(1000, 5000);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1wm_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_OWM_EN, 0);

	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_OWM]);
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX0]);
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX1]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mfd_cell asic3_cell_ds1wm = अणु
	.name          = "ds1wm",
	.enable        = ds1wm_enable,
	.disable       = ds1wm_disable,
	.platक्रमm_data = &ds1wm_pdata,
	.pdata_size    = माप(ds1wm_pdata),
	.num_resources = ARRAY_SIZE(ds1wm_resources),
	.resources     = ds1wm_resources,
पूर्ण;

अटल व्योम asic3_mmc_pwr(काष्ठा platक्रमm_device *pdev, पूर्णांक state)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	पंचांगio_core_mmc_pwr(asic->पंचांगio_cnf, 1 - asic->bus_shअगरt, state);
पूर्ण

अटल व्योम asic3_mmc_clk_भाग(काष्ठा platक्रमm_device *pdev, पूर्णांक state)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	पंचांगio_core_mmc_clk_भाग(asic->पंचांगio_cnf, 1 - asic->bus_shअगरt, state);
पूर्ण

अटल काष्ठा पंचांगio_mmc_data asic3_mmc_data = अणु
	.hclk           = 24576000,
	.ocr_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
	.set_pwr        = asic3_mmc_pwr,
	.set_clk_भाग    = asic3_mmc_clk_भाग,
पूर्ण;

अटल काष्ठा resource asic3_mmc_resources[] = अणु
	अणु
		.start = ASIC3_SD_CTRL_BASE,
		.end   = ASIC3_SD_CTRL_BASE + 0x3ff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = 0,
		.end   = 0,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक asic3_mmc_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Not sure अगर it must be करोne bit by bit, but leaving as-is */
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_LEVCD, 1);
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_LEVWP, 1);
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SUSPEND, 0);
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_PCLR, 0);

	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX0]);
	/* CLK32 used क्रम card detection and क्रम पूर्णांकerruption detection
	 * when HCLK is stopped.
	 */
	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX1]);
	usleep_range(1000, 5000);

	/* HCLK 24.576 MHz, BCLK 12.288 MHz: */
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, SEL),
		CLOCK_SEL_CX | CLOCK_SEL_SD_HCLK_SEL);

	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_SD_HOST]);
	asic3_clk_enable(asic, &asic->घड़ीs[ASIC3_CLOCK_SD_BUS]);
	usleep_range(1000, 5000);

	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_SD_MEM_ENABLE, 1);

	/* Enable SD card slot 3.3V घातer supply */
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SDPWR, 1);

	/* ASIC3_SD_CTRL_BASE assumes 32-bit addressing, TMIO is 16-bit */
	पंचांगio_core_mmc_enable(asic->पंचांगio_cnf, 1 - asic->bus_shअगरt,
			     ASIC3_SD_CTRL_BASE >> 1);

	वापस 0;
पूर्ण

अटल पूर्णांक asic3_mmc_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Put in suspend mode */
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SUSPEND, 1);

	/* Disable घड़ीs */
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_SD_HOST]);
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_SD_BUS]);
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX0]);
	asic3_clk_disable(asic, &asic->घड़ीs[ASIC3_CLOCK_EX1]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mfd_cell asic3_cell_mmc = अणु
	.name          = "tmio-mmc",
	.enable        = asic3_mmc_enable,
	.disable       = asic3_mmc_disable,
	.suspend       = asic3_mmc_disable,
	.resume        = asic3_mmc_enable,
	.platक्रमm_data = &asic3_mmc_data,
	.pdata_size    = माप(asic3_mmc_data),
	.num_resources = ARRAY_SIZE(asic3_mmc_resources),
	.resources     = asic3_mmc_resources,
पूर्ण;

अटल स्थिर पूर्णांक घड़ी_ledn[ASIC3_NUM_LEDS] = अणु
	[0] = ASIC3_CLOCK_LED0,
	[1] = ASIC3_CLOCK_LED1,
	[2] = ASIC3_CLOCK_LED2,
पूर्ण;

अटल पूर्णांक asic3_leds_enable(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	asic3_clk_enable(asic, &asic->घड़ीs[घड़ी_ledn[cell->id]]);

	वापस 0;
पूर्ण

अटल पूर्णांक asic3_leds_disable(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	asic3_clk_disable(asic, &asic->घड़ीs[घड़ी_ledn[cell->id]]);

	वापस 0;
पूर्ण

अटल पूर्णांक asic3_leds_suspend(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	जबतक (asic3_gpio_get(&asic->gpio, ASIC3_GPIO(C, cell->id)) != 0)
		usleep_range(1000, 5000);

	asic3_clk_disable(asic, &asic->घड़ीs[घड़ी_ledn[cell->id]]);

	वापस 0;
पूर्ण

अटल काष्ठा mfd_cell asic3_cell_leds[ASIC3_NUM_LEDS] = अणु
	[0] = अणु
		.name          = "leds-asic3",
		.id            = 0,
		.enable        = asic3_leds_enable,
		.disable       = asic3_leds_disable,
		.suspend       = asic3_leds_suspend,
		.resume        = asic3_leds_enable,
	पूर्ण,
	[1] = अणु
		.name          = "leds-asic3",
		.id            = 1,
		.enable        = asic3_leds_enable,
		.disable       = asic3_leds_disable,
		.suspend       = asic3_leds_suspend,
		.resume        = asic3_leds_enable,
	पूर्ण,
	[2] = अणु
		.name          = "leds-asic3",
		.id            = 2,
		.enable        = asic3_leds_enable,
		.disable       = asic3_leds_disable,
		.suspend       = asic3_leds_suspend,
		.resume        = asic3_leds_enable,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init asic3_mfd_probe(काष्ठा platक्रमm_device *pdev,
				  काष्ठा asic3_platक्रमm_data *pdata,
				  काष्ठा resource *mem)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *mem_sdio;
	पूर्णांक irq, ret;

	mem_sdio = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem_sdio)
		dev_dbg(asic->dev, "no SDIO MEM resource\n");

	irq = platक्रमm_get_irq(pdev, 1);
	अगर (irq < 0)
		dev_dbg(asic->dev, "no SDIO IRQ resource\n");

	/* DS1WM */
	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_OWM_SMB, 0);

	ds1wm_resources[0].start >>= asic->bus_shअगरt;
	ds1wm_resources[0].end   >>= asic->bus_shअगरt;

	/* MMC */
	अगर (mem_sdio) अणु
		asic->पंचांगio_cnf = ioremap((ASIC3_SD_CONFIG_BASE >>
					  asic->bus_shअगरt) + mem_sdio->start,
				 ASIC3_SD_CONFIG_SIZE >> asic->bus_shअगरt);
		अगर (!asic->पंचांगio_cnf) अणु
			ret = -ENOMEM;
			dev_dbg(asic->dev, "Couldn't ioremap SD_CONFIG\n");
			जाओ out;
		पूर्ण
	पूर्ण
	asic3_mmc_resources[0].start >>= asic->bus_shअगरt;
	asic3_mmc_resources[0].end   >>= asic->bus_shअगरt;

	अगर (pdata->घड़ी_rate) अणु
		ds1wm_pdata.घड़ी_rate = pdata->घड़ी_rate;
		ret = mfd_add_devices(&pdev->dev, pdev->id,
			&asic3_cell_ds1wm, 1, mem, asic->irq_base, शून्य);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (mem_sdio && (irq >= 0)) अणु
		ret = mfd_add_devices(&pdev->dev, pdev->id,
			&asic3_cell_mmc, 1, mem_sdio, irq, शून्य);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = 0;
	अगर (pdata->leds) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ASIC3_NUM_LEDS; ++i) अणु
			asic3_cell_leds[i].platक्रमm_data = &pdata->leds[i];
			asic3_cell_leds[i].pdata_size = माप(pdata->leds[i]);
		पूर्ण
		ret = mfd_add_devices(&pdev->dev, 0,
			asic3_cell_leds, ASIC3_NUM_LEDS, शून्य, 0, शून्य);
	पूर्ण

 out:
	वापस ret;
पूर्ण

अटल व्योम asic3_mfd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);

	mfd_हटाओ_devices(&pdev->dev);
	iounmap(asic->पंचांगio_cnf);
पूर्ण

/* Core */
अटल पूर्णांक __init asic3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा asic3 *asic;
	काष्ठा resource *mem;
	अचिन्हित दीर्घ clksel;
	पूर्णांक ret = 0;

	asic = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा asic3), GFP_KERNEL);
	अगर (!asic)
		वापस -ENOMEM;

	raw_spin_lock_init(&asic->lock);
	platक्रमm_set_drvdata(pdev, asic);
	asic->dev = &pdev->dev;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(asic->dev, "no MEM resource\n");
		वापस -ENOMEM;
	पूर्ण

	asic->mapping = ioremap(mem->start, resource_size(mem));
	अगर (!asic->mapping) अणु
		dev_err(asic->dev, "Couldn't ioremap\n");
		वापस -ENOMEM;
	पूर्ण

	asic->irq_base = pdata->irq_base;

	/* calculate bus shअगरt from mem resource */
	asic->bus_shअगरt = 2 - (resource_size(mem) >> 12);

	clksel = 0;
	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, SEL), clksel);

	ret = asic3_irq_probe(pdev);
	अगर (ret < 0) अणु
		dev_err(asic->dev, "Couldn't probe IRQs\n");
		जाओ out_unmap;
	पूर्ण

	asic->gpio.label = "asic3";
	asic->gpio.base = pdata->gpio_base;
	asic->gpio.ngpio = ASIC3_NUM_GPIOS;
	asic->gpio.get = asic3_gpio_get;
	asic->gpio.set = asic3_gpio_set;
	asic->gpio.direction_input = asic3_gpio_direction_input;
	asic->gpio.direction_output = asic3_gpio_direction_output;
	asic->gpio.to_irq = asic3_gpio_to_irq;

	ret = asic3_gpio_probe(pdev,
			       pdata->gpio_config,
			       pdata->gpio_config_num);
	अगर (ret < 0) अणु
		dev_err(asic->dev, "GPIO probe failed\n");
		जाओ out_irq;
	पूर्ण

	/* Making a per-device copy is only needed क्रम the
	 * theoretical हाल of multiple ASIC3s on one board:
	 */
	स_नकल(asic->घड़ीs, asic3_clk_init, माप(asic3_clk_init));

	asic3_mfd_probe(pdev, pdata, mem);

	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
		(ASIC3_EXTCF_CF0_BUF_EN|ASIC3_EXTCF_CF0_PWAIT_EN), 1);

	dev_info(asic->dev, "ASIC3 Core driver\n");

	वापस 0;

 out_irq:
	asic3_irq_हटाओ(pdev);

 out_unmap:
	iounmap(asic->mapping);

	वापस ret;
पूर्ण

अटल पूर्णांक asic3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा asic3 *asic = platक्रमm_get_drvdata(pdev);

	asic3_set_रेजिस्टर(asic, ASIC3_OFFSET(EXTCF, SELECT),
		(ASIC3_EXTCF_CF0_BUF_EN|ASIC3_EXTCF_CF0_PWAIT_EN), 0);

	asic3_mfd_हटाओ(pdev);

	ret = asic3_gpio_हटाओ(pdev);
	अगर (ret < 0)
		वापस ret;
	asic3_irq_हटाओ(pdev);

	asic3_ग_लिखो_रेजिस्टर(asic, ASIC3_OFFSET(CLOCK, SEL), 0);

	iounmap(asic->mapping);

	वापस 0;
पूर्ण

अटल व्योम asic3_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण

अटल काष्ठा platक्रमm_driver asic3_device_driver = अणु
	.driver		= अणु
		.name	= "asic3",
	पूर्ण,
	.हटाओ		= asic3_हटाओ,
	.shutकरोwn	= asic3_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init asic3_init(व्योम)
अणु
	पूर्णांक retval = 0;

	retval = platक्रमm_driver_probe(&asic3_device_driver, asic3_probe);

	वापस retval;
पूर्ण

subsys_initcall(asic3_init);
