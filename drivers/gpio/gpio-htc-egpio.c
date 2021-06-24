<शैली गुरु>
/*
 * Support क्रम the GPIO/IRQ expander chips present on several HTC phones.
 * These are implemented in CPLD chips present on the board.
 *
 * Copyright (c) 2007 Kevin O'Connor <kevin@koconnor.net>
 * Copyright (c) 2007 Philipp Zabel <philipp.zabel@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPL license.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_data/gpio-htc-egpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/driver.h>

काष्ठा egpio_chip अणु
	पूर्णांक              reg_start;
	पूर्णांक              cached_values;
	अचिन्हित दीर्घ    is_out;
	काष्ठा device    *dev;
	काष्ठा gpio_chip chip;
पूर्ण;

काष्ठा egpio_info अणु
	spinlock_t        lock;

	/* iomem info */
	व्योम __iomem      *base_addr;
	पूर्णांक               bus_shअगरt;	/* byte shअगरt */
	पूर्णांक               reg_shअगरt;	/* bit shअगरt */
	पूर्णांक               reg_mask;

	/* irq info */
	पूर्णांक               ack_रेजिस्टर;
	पूर्णांक               ack_ग_लिखो;
	u16               irqs_enabled;
	uपूर्णांक              irq_start;
	पूर्णांक               nirqs;
	uपूर्णांक              chained_irq;

	/* egpio info */
	काष्ठा egpio_chip *chip;
	पूर्णांक               nchips;
पूर्ण;

अटल अंतरभूत व्योम egpio_ग_लिखोw(u16 value, काष्ठा egpio_info *ei, पूर्णांक reg)
अणु
	ग_लिखोw(value, ei->base_addr + (reg << ei->bus_shअगरt));
पूर्ण

अटल अंतरभूत u16 egpio_पढ़ोw(काष्ठा egpio_info *ei, पूर्णांक reg)
अणु
	वापस पढ़ोw(ei->base_addr + (reg << ei->bus_shअगरt));
पूर्ण

/*
 * IRQs
 */

अटल अंतरभूत व्योम ack_irqs(काष्ठा egpio_info *ei)
अणु
	egpio_ग_लिखोw(ei->ack_ग_लिखो, ei, ei->ack_रेजिस्टर);
	pr_debug("EGPIO ack - write %x to base+%x\n",
			ei->ack_ग_लिखो, ei->ack_रेजिस्टर << ei->bus_shअगरt);
पूर्ण

अटल व्योम egpio_ack(काष्ठा irq_data *data)
अणु
पूर्ण

/* There करोes not appear to be a way to proactively mask पूर्णांकerrupts
 * on the egpio chip itself.  So, we simply ignore पूर्णांकerrupts that
 * aren't desired. */
अटल व्योम egpio_mask(काष्ठा irq_data *data)
अणु
	काष्ठा egpio_info *ei = irq_data_get_irq_chip_data(data);
	ei->irqs_enabled &= ~(1 << (data->irq - ei->irq_start));
	pr_debug("EGPIO mask %d %04x\n", data->irq, ei->irqs_enabled);
पूर्ण

अटल व्योम egpio_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा egpio_info *ei = irq_data_get_irq_chip_data(data);
	ei->irqs_enabled |= 1 << (data->irq - ei->irq_start);
	pr_debug("EGPIO unmask %d %04x\n", data->irq, ei->irqs_enabled);
पूर्ण

अटल काष्ठा irq_chip egpio_muxed_chip = अणु
	.name		= "htc-egpio",
	.irq_ack	= egpio_ack,
	.irq_mask	= egpio_mask,
	.irq_unmask	= egpio_unmask,
पूर्ण;

अटल व्योम egpio_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा egpio_info *ei = irq_desc_get_handler_data(desc);
	पूर्णांक irqpin;

	/* Read current pins. */
	अचिन्हित दीर्घ पढ़ोval = egpio_पढ़ोw(ei, ei->ack_रेजिस्टर);
	pr_debug("IRQ reg: %x\n", (अचिन्हित पूर्णांक)पढ़ोval);
	/* Ack/unmask पूर्णांकerrupts. */
	ack_irqs(ei);
	/* Process all set pins. */
	पढ़ोval &= ei->irqs_enabled;
	क्रम_each_set_bit(irqpin, &पढ़ोval, ei->nirqs) अणु
		/* Run irq handler */
		pr_debug("got IRQ %d\n", irqpin);
		generic_handle_irq(ei->irq_start + irqpin);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक egpio_pos(काष्ठा egpio_info *ei, पूर्णांक bit)
अणु
	वापस bit >> ei->reg_shअगरt;
पूर्ण

अटल अंतरभूत पूर्णांक egpio_bit(काष्ठा egpio_info *ei, पूर्णांक bit)
अणु
	वापस 1 << (bit & ((1 << ei->reg_shअगरt)-1));
पूर्ण

/*
 * Input pins
 */

अटल पूर्णांक egpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा egpio_chip *egpio;
	काष्ठा egpio_info *ei;
	अचिन्हित           bit;
	पूर्णांक                reg;
	पूर्णांक                value;

	pr_debug("egpio_get_value(%d)\n", chip->base + offset);

	egpio = gpiochip_get_data(chip);
	ei    = dev_get_drvdata(egpio->dev);
	bit   = egpio_bit(ei, offset);
	reg   = egpio->reg_start + egpio_pos(ei, offset);

	अगर (test_bit(offset, &egpio->is_out)) अणु
		वापस !!(egpio->cached_values & (1 << offset));
	पूर्ण अन्यथा अणु
		value = egpio_पढ़ोw(ei, reg);
		pr_debug("readw(%p + %x) = %x\n",
			 ei->base_addr, reg << ei->bus_shअगरt, value);
		वापस !!(value & bit);
	पूर्ण
पूर्ण

अटल पूर्णांक egpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा egpio_chip *egpio;

	egpio = gpiochip_get_data(chip);
	वापस test_bit(offset, &egpio->is_out) ? -EINVAL : 0;
पूर्ण


/*
 * Output pins
 */

अटल व्योम egpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	अचिन्हित दीर्घ     flag;
	काष्ठा egpio_chip *egpio;
	काष्ठा egpio_info *ei;
	पूर्णांक               pos;
	पूर्णांक               reg;
	पूर्णांक               shअगरt;

	pr_debug("egpio_set(%s, %d(%d), %d)\n",
			chip->label, offset, offset+chip->base, value);

	egpio = gpiochip_get_data(chip);
	ei    = dev_get_drvdata(egpio->dev);
	pos   = egpio_pos(ei, offset);
	reg   = egpio->reg_start + pos;
	shअगरt = pos << ei->reg_shअगरt;

	pr_debug("egpio %s: reg %d = 0x%04x\n", value ? "set" : "clear",
			reg, (egpio->cached_values >> shअगरt) & ei->reg_mask);

	spin_lock_irqsave(&ei->lock, flag);
	अगर (value)
		egpio->cached_values |= (1 << offset);
	अन्यथा
		egpio->cached_values &= ~(1 << offset);
	egpio_ग_लिखोw((egpio->cached_values >> shअगरt) & ei->reg_mask, ei, reg);
	spin_unlock_irqrestore(&ei->lock, flag);
पूर्ण

अटल पूर्णांक egpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा egpio_chip *egpio;

	egpio = gpiochip_get_data(chip);
	अगर (test_bit(offset, &egpio->is_out)) अणु
		egpio_set(chip, offset, value);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक egpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा egpio_chip *egpio;

	egpio = gpiochip_get_data(chip);

	अगर (test_bit(offset, &egpio->is_out))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल व्योम egpio_ग_लिखो_cache(काष्ठा egpio_info *ei)
अणु
	पूर्णांक               i;
	काष्ठा egpio_chip *egpio;
	पूर्णांक               shअगरt;

	क्रम (i = 0; i < ei->nchips; i++) अणु
		egpio = &(ei->chip[i]);
		अगर (!egpio->is_out)
			जारी;

		क्रम (shअगरt = 0; shअगरt < egpio->chip.ngpio;
				shअगरt += (1<<ei->reg_shअगरt)) अणु

			पूर्णांक reg = egpio->reg_start + egpio_pos(ei, shअगरt);

			अगर (!((egpio->is_out >> shअगरt) & ei->reg_mask))
				जारी;

			pr_debug("EGPIO: setting %x to %x, was %x\n", reg,
				(egpio->cached_values >> shअगरt) & ei->reg_mask,
				egpio_पढ़ोw(ei, reg));

			egpio_ग_लिखोw((egpio->cached_values >> shअगरt)
					& ei->reg_mask, ei, reg);
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Setup
 */

अटल पूर्णांक __init egpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा htc_egpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा resource   *res;
	काष्ठा egpio_info *ei;
	काष्ठा gpio_chip  *chip;
	अचिन्हित पूर्णांक      irq, irq_end;
	पूर्णांक               i;

	/* Initialize ei data काष्ठाure. */
	ei = devm_kzalloc(&pdev->dev, माप(*ei), GFP_KERNEL);
	अगर (!ei)
		वापस -ENOMEM;

	spin_lock_init(&ei->lock);

	/* Find chained irq */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res)
		ei->chained_irq = res->start;

	/* Map egpio chip पूर्णांकo भव address space. */
	ei->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ei->base_addr))
		वापस PTR_ERR(ei->base_addr);

	अगर ((pdata->bus_width != 16) && (pdata->bus_width != 32))
		वापस -EINVAL;

	ei->bus_shअगरt = fls(pdata->bus_width - 1) - 3;
	pr_debug("bus_shift = %d\n", ei->bus_shअगरt);

	अगर ((pdata->reg_width != 8) && (pdata->reg_width != 16))
		वापस -EINVAL;

	ei->reg_shअगरt = fls(pdata->reg_width - 1);
	pr_debug("reg_shift = %d\n", ei->reg_shअगरt);

	ei->reg_mask = (1 << pdata->reg_width) - 1;

	platक्रमm_set_drvdata(pdev, ei);

	ei->nchips = pdata->num_chips;
	ei->chip = devm_kसुस्मृति(&pdev->dev,
				ei->nchips, माप(काष्ठा egpio_chip),
				GFP_KERNEL);
	अगर (!ei->chip)
		वापस -ENOMEM;

	क्रम (i = 0; i < ei->nchips; i++) अणु
		ei->chip[i].reg_start = pdata->chip[i].reg_start;
		ei->chip[i].cached_values = pdata->chip[i].initial_values;
		ei->chip[i].is_out = pdata->chip[i].direction;
		ei->chip[i].dev = &(pdev->dev);
		chip = &(ei->chip[i].chip);
		chip->label = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
					     "htc-egpio-%d",
					     i);
		अगर (!chip->label)
			वापस -ENOMEM;

		chip->parent          = &pdev->dev;
		chip->owner           = THIS_MODULE;
		chip->get             = egpio_get;
		chip->set             = egpio_set;
		chip->direction_input = egpio_direction_input;
		chip->direction_output = egpio_direction_output;
		chip->get_direction   = egpio_get_direction;
		chip->base            = pdata->chip[i].gpio_base;
		chip->ngpio           = pdata->chip[i].num_gpios;

		gpiochip_add_data(chip, &ei->chip[i]);
	पूर्ण

	/* Set initial pin values */
	egpio_ग_लिखो_cache(ei);

	ei->irq_start = pdata->irq_base;
	ei->nirqs = pdata->num_irqs;
	ei->ack_रेजिस्टर = pdata->ack_रेजिस्टर;

	अगर (ei->chained_irq) अणु
		/* Setup irq handlers */
		ei->ack_ग_लिखो = 0xFFFF;
		अगर (pdata->invert_acks)
			ei->ack_ग_लिखो = 0;
		irq_end = ei->irq_start + ei->nirqs;
		क्रम (irq = ei->irq_start; irq < irq_end; irq++) अणु
			irq_set_chip_and_handler(irq, &egpio_muxed_chip,
						 handle_simple_irq);
			irq_set_chip_data(irq, ei);
			irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
		पूर्ण
		irq_set_irq_type(ei->chained_irq, IRQ_TYPE_EDGE_RISING);
		irq_set_chained_handler_and_data(ei->chained_irq,
						 egpio_handler, ei);
		ack_irqs(ei);

		device_init_wakeup(&pdev->dev, 1);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक egpio_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा egpio_info *ei = platक्रमm_get_drvdata(pdev);

	अगर (ei->chained_irq && device_may_wakeup(&pdev->dev))
		enable_irq_wake(ei->chained_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक egpio_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा egpio_info *ei = platक्रमm_get_drvdata(pdev);

	अगर (ei->chained_irq && device_may_wakeup(&pdev->dev))
		disable_irq_wake(ei->chained_irq);

	/* Update रेजिस्टरs from the cache, in हाल
	   the CPLD was घातered off during suspend */
	egpio_ग_लिखो_cache(ei);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा egpio_suspend शून्य
#घोषणा egpio_resume शून्य
#पूर्ण_अगर


अटल काष्ठा platक्रमm_driver egpio_driver = अणु
	.driver = अणु
		.name = "htc-egpio",
		.suppress_bind_attrs = true,
	पूर्ण,
	.suspend      = egpio_suspend,
	.resume       = egpio_resume,
पूर्ण;

अटल पूर्णांक __init egpio_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&egpio_driver, egpio_probe);
पूर्ण
/* start early क्रम dependencies */
subsys_initcall(egpio_init);
