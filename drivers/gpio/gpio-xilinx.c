<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx gpio driver क्रम xps/axi_gpio IP.
 *
 * Copyright 2008 - 2013 Xilinx, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

/* Register Offset Definitions */
#घोषणा XGPIO_DATA_OFFSET   (0x0)	/* Data रेजिस्टर  */
#घोषणा XGPIO_TRI_OFFSET    (0x4)	/* I/O direction रेजिस्टर  */

#घोषणा XGPIO_CHANNEL_OFFSET	0x8

#घोषणा XGPIO_GIER_OFFSET	0x11c /* Global Interrupt Enable */
#घोषणा XGPIO_GIER_IE		BIT(31)
#घोषणा XGPIO_IPISR_OFFSET	0x120 /* IP Interrupt Status */
#घोषणा XGPIO_IPIER_OFFSET	0x128 /* IP Interrupt Enable */

/* Read/Write access to the GPIO रेजिस्टरs */
#अगर defined(CONFIG_ARCH_ZYNQ) || defined(CONFIG_X86)
# define xgpio_पढ़ोreg(offset)		पढ़ोl(offset)
# define xgpio_ग_लिखोreg(offset, val)	ग_लिखोl(val, offset)
#अन्यथा
# define xgpio_पढ़ोreg(offset)		__raw_पढ़ोl(offset)
# define xgpio_ग_लिखोreg(offset, val)	__raw_ग_लिखोl(val, offset)
#पूर्ण_अगर

/**
 * काष्ठा xgpio_instance - Stores inक्रमmation about GPIO device
 * @gc: GPIO chip
 * @regs: रेजिस्टर block
 * @gpio_width: GPIO width क्रम every channel
 * @gpio_state: GPIO ग_लिखो state shaकरोw रेजिस्टर
 * @gpio_last_irq_पढ़ो: GPIO पढ़ो state रेजिस्टर from last पूर्णांकerrupt
 * @gpio_dir: GPIO direction shaकरोw रेजिस्टर
 * @gpio_lock: Lock used क्रम synchronization
 * @irq: IRQ used by GPIO device
 * @irqchip: IRQ chip
 * @irq_enable: GPIO IRQ enable/disable bitfield
 * @irq_rising_edge: GPIO IRQ rising edge enable/disable bitfield
 * @irq_falling_edge: GPIO IRQ falling edge enable/disable bitfield
 * @clk: घड़ी resource क्रम this driver
 */
काष्ठा xgpio_instance अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक gpio_width[2];
	u32 gpio_state[2];
	u32 gpio_last_irq_पढ़ो[2];
	u32 gpio_dir[2];
	spinlock_t gpio_lock;	/* For serializing operations */
	पूर्णांक irq;
	काष्ठा irq_chip irqchip;
	u32 irq_enable[2];
	u32 irq_rising_edge[2];
	u32 irq_falling_edge[2];
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत पूर्णांक xgpio_index(काष्ठा xgpio_instance *chip, पूर्णांक gpio)
अणु
	अगर (gpio >= chip->gpio_width[0])
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xgpio_regoffset(काष्ठा xgpio_instance *chip, पूर्णांक gpio)
अणु
	अगर (xgpio_index(chip, gpio))
		वापस XGPIO_CHANNEL_OFFSET;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xgpio_offset(काष्ठा xgpio_instance *chip, पूर्णांक gpio)
अणु
	अगर (xgpio_index(chip, gpio))
		वापस gpio - chip->gpio_width[0];

	वापस gpio;
पूर्ण

/**
 * xgpio_get - Read the specअगरied संकेत of the GPIO device.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 *
 * This function पढ़ोs the specअगरied संकेत of the GPIO device.
 *
 * Return:
 * 0 अगर direction of GPIO संकेतs is set as input otherwise it
 * वापसs negative error value.
 */
अटल पूर्णांक xgpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा xgpio_instance *chip = gpiochip_get_data(gc);
	u32 val;

	val = xgpio_पढ़ोreg(chip->regs + XGPIO_DATA_OFFSET +
			    xgpio_regoffset(chip, gpio));

	वापस !!(val & BIT(xgpio_offset(chip, gpio)));
पूर्ण

/**
 * xgpio_set - Write the specअगरied संकेत of the GPIO device.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * This function ग_लिखोs the specअगरied value in to the specअगरied संकेत of the
 * GPIO device.
 */
अटल व्योम xgpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = gpiochip_get_data(gc);
	पूर्णांक index =  xgpio_index(chip, gpio);
	पूर्णांक offset =  xgpio_offset(chip, gpio);

	spin_lock_irqsave(&chip->gpio_lock, flags);

	/* Write to GPIO संकेत and set its direction to output */
	अगर (val)
		chip->gpio_state[index] |= BIT(offset);
	अन्यथा
		chip->gpio_state[index] &= ~BIT(offset);

	xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET +
		       xgpio_regoffset(chip, gpio), chip->gpio_state[index]);

	spin_unlock_irqrestore(&chip->gpio_lock, flags);
पूर्ण

/**
 * xgpio_set_multiple - Write the specअगरied संकेतs of the GPIO device.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @mask:   Mask of the GPIOS to modअगरy.
 * @bits:   Value to be wrote on each GPIO
 *
 * This function ग_लिखोs the specअगरied values पूर्णांकo the specअगरied संकेतs of the
 * GPIO devices.
 */
अटल व्योम xgpio_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
			       अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = gpiochip_get_data(gc);
	पूर्णांक index = xgpio_index(chip, 0);
	पूर्णांक offset, i;

	spin_lock_irqsave(&chip->gpio_lock, flags);

	/* Write to GPIO संकेतs */
	क्रम (i = 0; i < gc->ngpio; i++) अणु
		अगर (*mask == 0)
			अवरोध;
		/* Once finished with an index ग_लिखो it out to the रेजिस्टर */
		अगर (index !=  xgpio_index(chip, i)) अणु
			xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET +
				       index * XGPIO_CHANNEL_OFFSET,
				       chip->gpio_state[index]);
			spin_unlock_irqrestore(&chip->gpio_lock, flags);
			index =  xgpio_index(chip, i);
			spin_lock_irqsave(&chip->gpio_lock, flags);
		पूर्ण
		अगर (__test_and_clear_bit(i, mask)) अणु
			offset =  xgpio_offset(chip, i);
			अगर (test_bit(i, bits))
				chip->gpio_state[index] |= BIT(offset);
			अन्यथा
				chip->gpio_state[index] &= ~BIT(offset);
		पूर्ण
	पूर्ण

	xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET +
		       index * XGPIO_CHANNEL_OFFSET, chip->gpio_state[index]);

	spin_unlock_irqrestore(&chip->gpio_lock, flags);
पूर्ण

/**
 * xgpio_dir_in - Set the direction of the specअगरied GPIO संकेत as input.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 *
 * Return:
 * 0 - अगर direction of GPIO संकेतs is set as input
 * otherwise it वापसs negative error value.
 */
अटल पूर्णांक xgpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = gpiochip_get_data(gc);
	पूर्णांक index =  xgpio_index(chip, gpio);
	पूर्णांक offset =  xgpio_offset(chip, gpio);

	spin_lock_irqsave(&chip->gpio_lock, flags);

	/* Set the GPIO bit in shaकरोw रेजिस्टर and set direction as input */
	chip->gpio_dir[index] |= BIT(offset);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_TRI_OFFSET +
		       xgpio_regoffset(chip, gpio), chip->gpio_dir[index]);

	spin_unlock_irqrestore(&chip->gpio_lock, flags);

	वापस 0;
पूर्ण

/**
 * xgpio_dir_out - Set the direction of the specअगरied GPIO संकेत as output.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * This function sets the direction of specअगरied GPIO संकेत as output.
 *
 * Return:
 * If all GPIO संकेतs of GPIO chip is configured as input then it वापसs
 * error otherwise it वापसs 0.
 */
अटल पूर्णांक xgpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = gpiochip_get_data(gc);
	पूर्णांक index =  xgpio_index(chip, gpio);
	पूर्णांक offset =  xgpio_offset(chip, gpio);

	spin_lock_irqsave(&chip->gpio_lock, flags);

	/* Write state of GPIO संकेत */
	अगर (val)
		chip->gpio_state[index] |= BIT(offset);
	अन्यथा
		chip->gpio_state[index] &= ~BIT(offset);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET +
			xgpio_regoffset(chip, gpio), chip->gpio_state[index]);

	/* Clear the GPIO bit in shaकरोw रेजिस्टर and set direction as output */
	chip->gpio_dir[index] &= ~BIT(offset);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_TRI_OFFSET +
			xgpio_regoffset(chip, gpio), chip->gpio_dir[index]);

	spin_unlock_irqrestore(&chip->gpio_lock, flags);

	वापस 0;
पूर्ण

/**
 * xgpio_save_regs - Set initial values of GPIO pins
 * @chip: Poपूर्णांकer to GPIO instance
 */
अटल व्योम xgpio_save_regs(काष्ठा xgpio_instance *chip)
अणु
	xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET,	chip->gpio_state[0]);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_TRI_OFFSET, chip->gpio_dir[0]);

	अगर (!chip->gpio_width[1])
		वापस;

	xgpio_ग_लिखोreg(chip->regs + XGPIO_DATA_OFFSET + XGPIO_CHANNEL_OFFSET,
		       chip->gpio_state[1]);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_TRI_OFFSET + XGPIO_CHANNEL_OFFSET,
		       chip->gpio_dir[1]);
पूर्ण

अटल पूर्णांक xgpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(chip->parent);
	/*
	 * If the device is alपढ़ोy active pm_runसमय_get() will वापस 1 on
	 * success, but gpio_request still needs to वापस 0.
	 */
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम xgpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	pm_runसमय_put(chip->parent);
पूर्ण

अटल पूर्णांक __maybe_unused xgpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा xgpio_instance *gpio = dev_get_drvdata(dev);
	काष्ठा irq_data *data = irq_get_irq_data(gpio->irq);

	अगर (!data) अणु
		dev_err(dev, "irq_get_irq_data() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!irqd_is_wakeup_set(data))
		वापस pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

/**
 * xgpio_हटाओ - Remove method क्रम the GPIO device.
 * @pdev: poपूर्णांकer to the platक्रमm device
 *
 * This function हटाओ gpiochips and मुक्तs all the allocated resources.
 *
 * Return: 0 always
 */
अटल पूर्णांक xgpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgpio_instance *gpio = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(gpio->clk);

	वापस 0;
पूर्ण

/**
 * xgpio_irq_ack - Acknowledge a child GPIO पूर्णांकerrupt.
 * @irq_data: per IRQ and chip data passed करोwn to chip functions
 * This currently करोes nothing, but irq_ack is unconditionally called by
 * handle_edge_irq and thereक्रमe must be defined.
 */
अटल व्योम xgpio_irq_ack(काष्ठा irq_data *irq_data)
अणु
पूर्ण

अटल पूर्णांक __maybe_unused xgpio_resume(काष्ठा device *dev)
अणु
	काष्ठा xgpio_instance *gpio = dev_get_drvdata(dev);
	काष्ठा irq_data *data = irq_get_irq_data(gpio->irq);

	अगर (!data) अणु
		dev_err(dev, "irq_get_irq_data() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!irqd_is_wakeup_set(data))
		वापस pm_runसमय_क्रमce_resume(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xgpio_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा xgpio_instance *gpio = platक्रमm_get_drvdata(pdev);

	clk_disable(gpio->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xgpio_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा xgpio_instance *gpio = platक्रमm_get_drvdata(pdev);

	वापस clk_enable(gpio->clk);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xgpio_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xgpio_suspend, xgpio_resume)
	SET_RUNTIME_PM_OPS(xgpio_runसमय_suspend,
			   xgpio_runसमय_resume, शून्य)
पूर्ण;

/**
 * xgpio_irq_mask - Write the specअगरied संकेत of the GPIO device.
 * @irq_data: per IRQ and chip data passed करोwn to chip functions
 */
अटल व्योम xgpio_irq_mask(काष्ठा irq_data *irq_data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = irq_data_get_irq_chip_data(irq_data);
	पूर्णांक irq_offset = irqd_to_hwirq(irq_data);
	पूर्णांक index = xgpio_index(chip, irq_offset);
	पूर्णांक offset = xgpio_offset(chip, irq_offset);

	spin_lock_irqsave(&chip->gpio_lock, flags);

	chip->irq_enable[index] &= ~BIT(offset);

	अगर (!chip->irq_enable[index]) अणु
		/* Disable per channel पूर्णांकerrupt */
		u32 temp = xgpio_पढ़ोreg(chip->regs + XGPIO_IPIER_OFFSET);

		temp &= ~BIT(index);
		xgpio_ग_लिखोreg(chip->regs + XGPIO_IPIER_OFFSET, temp);
	पूर्ण
	spin_unlock_irqrestore(&chip->gpio_lock, flags);
पूर्ण

/**
 * xgpio_irq_unmask - Write the specअगरied संकेत of the GPIO device.
 * @irq_data: per IRQ and chip data passed करोwn to chip functions
 */
अटल व्योम xgpio_irq_unmask(काष्ठा irq_data *irq_data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xgpio_instance *chip = irq_data_get_irq_chip_data(irq_data);
	पूर्णांक irq_offset = irqd_to_hwirq(irq_data);
	पूर्णांक index = xgpio_index(chip, irq_offset);
	पूर्णांक offset = xgpio_offset(chip, irq_offset);
	u32 old_enable = chip->irq_enable[index];

	spin_lock_irqsave(&chip->gpio_lock, flags);

	chip->irq_enable[index] |= BIT(offset);

	अगर (!old_enable) अणु
		/* Clear any existing per-channel पूर्णांकerrupts */
		u32 val = xgpio_पढ़ोreg(chip->regs + XGPIO_IPISR_OFFSET) &
			BIT(index);

		अगर (val)
			xgpio_ग_लिखोreg(chip->regs + XGPIO_IPISR_OFFSET, val);

		/* Update GPIO IRQ पढ़ो data beक्रमe enabling पूर्णांकerrupt*/
		val = xgpio_पढ़ोreg(chip->regs + XGPIO_DATA_OFFSET +
				    index * XGPIO_CHANNEL_OFFSET);
		chip->gpio_last_irq_पढ़ो[index] = val;

		/* Enable per channel पूर्णांकerrupt */
		val = xgpio_पढ़ोreg(chip->regs + XGPIO_IPIER_OFFSET);
		val |= BIT(index);
		xgpio_ग_लिखोreg(chip->regs + XGPIO_IPIER_OFFSET, val);
	पूर्ण

	spin_unlock_irqrestore(&chip->gpio_lock, flags);
पूर्ण

/**
 * xgpio_set_irq_type - Write the specअगरied संकेत of the GPIO device.
 * @irq_data: Per IRQ and chip data passed करोwn to chip functions
 * @type: Interrupt type that is to be set क्रम the gpio pin
 *
 * Return:
 * 0 अगर पूर्णांकerrupt type is supported otherwise -EINVAL
 */
अटल पूर्णांक xgpio_set_irq_type(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा xgpio_instance *chip = irq_data_get_irq_chip_data(irq_data);
	पूर्णांक irq_offset = irqd_to_hwirq(irq_data);
	पूर्णांक index = xgpio_index(chip, irq_offset);
	पूर्णांक offset = xgpio_offset(chip, irq_offset);

	/*
	 * The Xilinx GPIO hardware provides a single पूर्णांकerrupt status
	 * indication क्रम any state change in a given GPIO channel (bank).
	 * Thereक्रमe, only rising edge or falling edge triggers are
	 * supported.
	 */
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		chip->irq_rising_edge[index] |= BIT(offset);
		chip->irq_falling_edge[index] |= BIT(offset);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		chip->irq_rising_edge[index] |= BIT(offset);
		chip->irq_falling_edge[index] &= ~BIT(offset);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		chip->irq_rising_edge[index] &= ~BIT(offset);
		chip->irq_falling_edge[index] |= BIT(offset);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_set_handler_locked(irq_data, handle_edge_irq);
	वापस 0;
पूर्ण

/**
 * xgpio_irqhandler - Gpio पूर्णांकerrupt service routine
 * @desc: Poपूर्णांकer to पूर्णांकerrupt description
 */
अटल व्योम xgpio_irqhandler(काष्ठा irq_desc *desc)
अणु
	काष्ठा xgpio_instance *chip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	u32 num_channels = chip->gpio_width[1] ? 2 : 1;
	u32 offset = 0, index;
	u32 status = xgpio_पढ़ोreg(chip->regs + XGPIO_IPISR_OFFSET);

	xgpio_ग_लिखोreg(chip->regs + XGPIO_IPISR_OFFSET, status);

	chained_irq_enter(irqchip, desc);
	क्रम (index = 0; index < num_channels; index++) अणु
		अगर ((status & BIT(index))) अणु
			अचिन्हित दीर्घ rising_events, falling_events, all_events;
			अचिन्हित दीर्घ flags;
			u32 data, bit;
			अचिन्हित पूर्णांक irq;

			spin_lock_irqsave(&chip->gpio_lock, flags);
			data = xgpio_पढ़ोreg(chip->regs + XGPIO_DATA_OFFSET +
					     index * XGPIO_CHANNEL_OFFSET);
			rising_events = data &
					~chip->gpio_last_irq_पढ़ो[index] &
					chip->irq_enable[index] &
					chip->irq_rising_edge[index];
			falling_events = ~data &
					 chip->gpio_last_irq_पढ़ो[index] &
					 chip->irq_enable[index] &
					 chip->irq_falling_edge[index];
			dev_dbg(chip->gc.parent,
				"IRQ chan %u rising 0x%lx falling 0x%lx\n",
				index, rising_events, falling_events);
			all_events = rising_events | falling_events;
			chip->gpio_last_irq_पढ़ो[index] = data;
			spin_unlock_irqrestore(&chip->gpio_lock, flags);

			क्रम_each_set_bit(bit, &all_events, 32) अणु
				irq = irq_find_mapping(chip->gc.irq.करोमुख्य,
						       offset + bit);
				generic_handle_irq(irq);
			पूर्ण
		पूर्ण
		offset += chip->gpio_width[index];
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

/**
 * xgpio_probe - Probe method क्रम the GPIO device.
 * @pdev: poपूर्णांकer to the platक्रमm device
 *
 * Return:
 * It वापसs 0, अगर the driver is bound to the GPIO device, or
 * a negative value अगर there is an error.
 */
अटल पूर्णांक xgpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgpio_instance *chip;
	पूर्णांक status = 0;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 is_dual = 0;
	u32 cells = 2;
	काष्ठा gpio_irq_chip *girq;
	u32 temp;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chip);

	/* Update GPIO state shaकरोw रेजिस्टर with शेष value */
	अगर (of_property_पढ़ो_u32(np, "xlnx,dout-default", &chip->gpio_state[0]))
		chip->gpio_state[0] = 0x0;

	/* Update GPIO direction shaकरोw रेजिस्टर with शेष value */
	अगर (of_property_पढ़ो_u32(np, "xlnx,tri-default", &chip->gpio_dir[0]))
		chip->gpio_dir[0] = 0xFFFFFFFF;

	/* Update cells with gpio-cells value */
	अगर (of_property_पढ़ो_u32(np, "#gpio-cells", &cells))
		dev_dbg(&pdev->dev, "Missing gpio-cells property\n");

	अगर (cells != 2) अणु
		dev_err(&pdev->dev, "#gpio-cells mismatch\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check device node and parent device node क्रम device width
	 * and assume शेष width of 32
	 */
	अगर (of_property_पढ़ो_u32(np, "xlnx,gpio-width", &chip->gpio_width[0]))
		chip->gpio_width[0] = 32;

	अगर (chip->gpio_width[0] > 32)
		वापस -EINVAL;

	spin_lock_init(&chip->gpio_lock);

	अगर (of_property_पढ़ो_u32(np, "xlnx,is-dual", &is_dual))
		is_dual = 0;

	अगर (is_dual) अणु
		/* Update GPIO state shaकरोw रेजिस्टर with शेष value */
		अगर (of_property_पढ़ो_u32(np, "xlnx,dout-default-2",
					 &chip->gpio_state[1]))
			chip->gpio_state[1] = 0x0;

		/* Update GPIO direction shaकरोw रेजिस्टर with शेष value */
		अगर (of_property_पढ़ो_u32(np, "xlnx,tri-default-2",
					 &chip->gpio_dir[1]))
			chip->gpio_dir[1] = 0xFFFFFFFF;

		/*
		 * Check device node and parent device node क्रम device width
		 * and assume शेष width of 32
		 */
		अगर (of_property_पढ़ो_u32(np, "xlnx,gpio2-width",
					 &chip->gpio_width[1]))
			chip->gpio_width[1] = 32;

		अगर (chip->gpio_width[1] > 32)
			वापस -EINVAL;
	पूर्ण

	chip->gc.base = -1;
	chip->gc.ngpio = chip->gpio_width[0] + chip->gpio_width[1];
	chip->gc.parent = &pdev->dev;
	chip->gc.direction_input = xgpio_dir_in;
	chip->gc.direction_output = xgpio_dir_out;
	chip->gc.of_gpio_n_cells = cells;
	chip->gc.get = xgpio_get;
	chip->gc.set = xgpio_set;
	chip->gc.request = xgpio_request;
	chip->gc.मुक्त = xgpio_मुक्त;
	chip->gc.set_multiple = xgpio_set_multiple;

	chip->gc.label = dev_name(&pdev->dev);

	chip->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->regs)) अणु
		dev_err(&pdev->dev, "failed to ioremap memory resource\n");
		वापस PTR_ERR(chip->regs);
	पूर्ण

	chip->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(chip->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(chip->clk), "input clock not found.\n");

	status = clk_prepare_enable(chip->clk);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "Failed to prepare clk\n");
		वापस status;
	पूर्ण
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	xgpio_save_regs(chip);

	chip->irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (chip->irq <= 0)
		जाओ skip_irq;

	chip->irqchip.name = "gpio-xilinx";
	chip->irqchip.irq_ack = xgpio_irq_ack;
	chip->irqchip.irq_mask = xgpio_irq_mask;
	chip->irqchip.irq_unmask = xgpio_irq_unmask;
	chip->irqchip.irq_set_type = xgpio_set_irq_type;

	/* Disable per-channel पूर्णांकerrupts */
	xgpio_ग_लिखोreg(chip->regs + XGPIO_IPIER_OFFSET, 0);
	/* Clear any existing per-channel पूर्णांकerrupts */
	temp = xgpio_पढ़ोreg(chip->regs + XGPIO_IPISR_OFFSET);
	xgpio_ग_लिखोreg(chip->regs + XGPIO_IPISR_OFFSET, temp);
	/* Enable global पूर्णांकerrupts */
	xgpio_ग_लिखोreg(chip->regs + XGPIO_GIER_OFFSET, XGPIO_GIER_IE);

	girq = &chip->gc.irq;
	girq->chip = &chip->irqchip;
	girq->parent_handler = xgpio_irqhandler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents) अणु
		status = -ENOMEM;
		जाओ err_pm_put;
	पूर्ण
	girq->parents[0] = chip->irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;

skip_irq:
	status = devm_gpiochip_add_data(&pdev->dev, &chip->gc, chip);
	अगर (status) अणु
		dev_err(&pdev->dev, "failed to add GPIO chip\n");
		जाओ err_pm_put;
	पूर्ण

	pm_runसमय_put(&pdev->dev);
	वापस 0;

err_pm_put:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	clk_disable_unprepare(chip->clk);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgpio_of_match[] = अणु
	अणु .compatible = "xlnx,xps-gpio-1.00.a", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, xgpio_of_match);

अटल काष्ठा platक्रमm_driver xgpio_plat_driver = अणु
	.probe		= xgpio_probe,
	.हटाओ		= xgpio_हटाओ,
	.driver		= अणु
			.name = "gpio-xilinx",
			.of_match_table	= xgpio_of_match,
			.pm = &xgpio_dev_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xgpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xgpio_plat_driver);
पूर्ण

subsys_initcall(xgpio_init);

अटल व्योम __निकास xgpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&xgpio_plat_driver);
पूर्ण
module_निकास(xgpio_निकास);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx GPIO driver");
MODULE_LICENSE("GPL");
