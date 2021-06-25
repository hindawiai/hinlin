<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mfd/ucb1x00-core.c
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 *
 *  The UCB1x00 core driver provides basic services क्रम handling IO,
 *  the ADC, पूर्णांकerrupts, and accessing रेजिस्टरs.  It is deचिन्हित
 *  such that everything goes through this layer, thereby providing
 *  a consistent locking methoकरोlogy, as well as allowing the drivers
 *  to be used on other non-MCP-enabled hardware platक्रमms.
 *
 *  Note that all locks are निजी to this file.  Nothing अन्यथा may
 *  touch them.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/ucb1x00.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpio/driver.h>

अटल DEFINE_MUTEX(ucb1x00_mutex);
अटल LIST_HEAD(ucb1x00_drivers);
अटल LIST_HEAD(ucb1x00_devices);

/**
 *	ucb1x00_io_set_dir - set IO direction
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@in:  bitfield of IO pins to be set as inमाला_दो
 *	@out: bitfield of IO pins to be set as outमाला_दो
 *
 *	Set the IO direction of the ten general purpose IO pins on
 *	the UCB1x00 chip.  The @in bitfield has priority over the
 *	@out bitfield, in that अगर you specअगरy a pin as both input
 *	and output, it will end up as an input.
 *
 *	ucb1x00_enable must have been called to enable the comms
 *	beक्रमe using this function.
 *
 *	This function takes a spinlock, disabling पूर्णांकerrupts.
 */
व्योम ucb1x00_io_set_dir(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक in, अचिन्हित पूर्णांक out)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_dir |= out;
	ucb->io_dir &= ~in;

	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_सूची, ucb->io_dir);
	spin_unlock_irqrestore(&ucb->io_lock, flags);
पूर्ण

/**
 *	ucb1x00_io_ग_लिखो - set or clear IO outमाला_दो
 *	@ucb:   UCB1x00 काष्ठाure describing chip
 *	@set:   bitfield of IO pins to set to logic '1'
 *	@clear: bitfield of IO pins to set to logic '0'
 *
 *	Set the IO output state of the specअगरied IO pins.  The value
 *	is retained अगर the pins are subsequently configured as inमाला_दो.
 *	The @clear bitfield has priority over the @set bitfield -
 *	outमाला_दो will be cleared.
 *
 *	ucb1x00_enable must have been called to enable the comms
 *	beक्रमe using this function.
 *
 *	This function takes a spinlock, disabling पूर्णांकerrupts.
 */
व्योम ucb1x00_io_ग_लिखो(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_out |= set;
	ucb->io_out &= ~clear;

	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_DATA, ucb->io_out);
	spin_unlock_irqrestore(&ucb->io_lock, flags);
पूर्ण

/**
 *	ucb1x00_io_पढ़ो - पढ़ो the current state of the IO pins
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Return a bitfield describing the logic state of the ten
 *	general purpose IO pins.
 *
 *	ucb1x00_enable must have been called to enable the comms
 *	beक्रमe using this function.
 *
 *	This function करोes not take any mutexes or spinlocks.
 */
अचिन्हित पूर्णांक ucb1x00_io_पढ़ो(काष्ठा ucb1x00 *ucb)
अणु
	वापस ucb1x00_reg_पढ़ो(ucb, UCB_IO_DATA);
पूर्ण

अटल व्योम ucb1x00_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ucb1x00 *ucb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	अगर (value)
		ucb->io_out |= 1 << offset;
	अन्यथा
		ucb->io_out &= ~(1 << offset);

	ucb1x00_enable(ucb);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_DATA, ucb->io_out);
	ucb1x00_disable(ucb);
	spin_unlock_irqrestore(&ucb->io_lock, flags);
पूर्ण

अटल पूर्णांक ucb1x00_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ucb1x00 *ucb = gpiochip_get_data(chip);
	अचिन्हित val;

	ucb1x00_enable(ucb);
	val = ucb1x00_reg_पढ़ो(ucb, UCB_IO_DATA);
	ucb1x00_disable(ucb);

	वापस !!(val & (1 << offset));
पूर्ण

अटल पूर्णांक ucb1x00_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ucb1x00 *ucb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_dir &= ~(1 << offset);
	ucb1x00_enable(ucb);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_सूची, ucb->io_dir);
	ucb1x00_disable(ucb);
	spin_unlock_irqrestore(&ucb->io_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ucb1x00_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset
		, पूर्णांक value)
अणु
	काष्ठा ucb1x00 *ucb = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित old, mask = 1 << offset;

	spin_lock_irqsave(&ucb->io_lock, flags);
	old = ucb->io_out;
	अगर (value)
		ucb->io_out |= mask;
	अन्यथा
		ucb->io_out &= ~mask;

	ucb1x00_enable(ucb);
	अगर (old != ucb->io_out)
		ucb1x00_reg_ग_लिखो(ucb, UCB_IO_DATA, ucb->io_out);

	अगर (!(ucb->io_dir & mask)) अणु
		ucb->io_dir |= mask;
		ucb1x00_reg_ग_लिखो(ucb, UCB_IO_सूची, ucb->io_dir);
	पूर्ण
	ucb1x00_disable(ucb);
	spin_unlock_irqrestore(&ucb->io_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ucb1x00_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ucb1x00 *ucb = gpiochip_get_data(chip);

	वापस ucb->irq_base > 0 ? ucb->irq_base + offset : -ENXIO;
पूर्ण

/*
 * UCB1300 data sheet says we must:
 *  1. enable ADC	=> 5us (including reference startup समय)
 *  2. select input	=> 51*tsibclk  => 4.3us
 *  3. start conversion	=> 102*tsibclk => 8.5us
 * (tsibclk = 1/11981000)
 * Period between SIB 128-bit frames = 10.7us
 */

/**
 *	ucb1x00_adc_enable - enable the ADC converter
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Enable the ucb1x00 and ADC converter on the UCB1x00 क्रम use.
 *	Any code wishing to use the ADC converter must call this
 *	function prior to using it.
 *
 *	This function takes the ADC mutex to prevent two or more
 *	concurrent uses, and thereक्रमe may sleep.  As a result, it
 *	can only be called from process context, not पूर्णांकerrupt
 *	context.
 *
 *	You should release the ADC as soon as possible using
 *	ucb1x00_adc_disable.
 */
व्योम ucb1x00_adc_enable(काष्ठा ucb1x00 *ucb)
अणु
	mutex_lock(&ucb->adc_mutex);

	ucb->adc_cr |= UCB_ADC_ENA;

	ucb1x00_enable(ucb);
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, ucb->adc_cr);
पूर्ण

/**
 *	ucb1x00_adc_पढ़ो - पढ़ो the specअगरied ADC channel
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@adc_channel: ADC channel mask
 *	@sync: रुको क्रम syncronisation pulse.
 *
 *	Start an ADC conversion and रुको क्रम the result.  Note that
 *	synchronised ADC conversions (via the ADCSYNC pin) must रुको
 *	until the trigger is निश्चितed and the conversion is finished.
 *
 *	This function currently spins रुकोing क्रम the conversion to
 *	complete (2 frames max without sync).
 *
 *	If called क्रम a synchronised ADC conversion, it may sleep
 *	with the ADC mutex held.
 */
अचिन्हित पूर्णांक ucb1x00_adc_पढ़ो(काष्ठा ucb1x00 *ucb, पूर्णांक adc_channel, पूर्णांक sync)
अणु
	अचिन्हित पूर्णांक val;

	अगर (sync)
		adc_channel |= UCB_ADC_SYNC_ENA;

	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, ucb->adc_cr | adc_channel);
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, ucb->adc_cr | adc_channel | UCB_ADC_START);

	क्रम (;;) अणु
		val = ucb1x00_reg_पढ़ो(ucb, UCB_ADC_DATA);
		अगर (val & UCB_ADC_DAT_VAL)
			अवरोध;
		/* yield to other processes */
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(1);
	पूर्ण

	वापस UCB_ADC_DAT(val);
पूर्ण

/**
 *	ucb1x00_adc_disable - disable the ADC converter
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Disable the ADC converter and release the ADC mutex.
 */
व्योम ucb1x00_adc_disable(काष्ठा ucb1x00 *ucb)
अणु
	ucb->adc_cr &= ~UCB_ADC_ENA;
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, ucb->adc_cr);
	ucb1x00_disable(ucb);

	mutex_unlock(&ucb->adc_mutex);
पूर्ण

/*
 * UCB1x00 Interrupt handling.
 *
 * The UCB1x00 can generate पूर्णांकerrupts when the SIBCLK is stopped.
 * Since we need to पढ़ो an पूर्णांकernal रेजिस्टर, we must re-enable
 * SIBCLK to talk to the chip.  We leave the घड़ी running until
 * we have finished processing all पूर्णांकerrupts from the chip.
 */
अटल व्योम ucb1x00_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा ucb1x00 *ucb = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक isr, i;

	ucb1x00_enable(ucb);
	isr = ucb1x00_reg_पढ़ो(ucb, UCB_IE_STATUS);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, isr);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, 0);

	क्रम (i = 0; i < 16 && isr; i++, isr >>= 1)
		अगर (isr & 1)
			generic_handle_irq(ucb->irq_base + i);
	ucb1x00_disable(ucb);
पूर्ण

अटल व्योम ucb1x00_irq_update(काष्ठा ucb1x00 *ucb, अचिन्हित mask)
अणु
	ucb1x00_enable(ucb);
	अगर (ucb->irq_ris_enbl & mask)
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, ucb->irq_ris_enbl &
				  ucb->irq_mask);
	अगर (ucb->irq_fal_enbl & mask)
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, ucb->irq_fal_enbl &
				  ucb->irq_mask);
	ucb1x00_disable(ucb);
पूर्ण

अटल व्योम ucb1x00_irq_noop(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम ucb1x00_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा ucb1x00 *ucb = irq_data_get_irq_chip_data(data);
	अचिन्हित mask = 1 << (data->irq - ucb->irq_base);

	raw_spin_lock(&ucb->irq_lock);
	ucb->irq_mask &= ~mask;
	ucb1x00_irq_update(ucb, mask);
	raw_spin_unlock(&ucb->irq_lock);
पूर्ण

अटल व्योम ucb1x00_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा ucb1x00 *ucb = irq_data_get_irq_chip_data(data);
	अचिन्हित mask = 1 << (data->irq - ucb->irq_base);

	raw_spin_lock(&ucb->irq_lock);
	ucb->irq_mask |= mask;
	ucb1x00_irq_update(ucb, mask);
	raw_spin_unlock(&ucb->irq_lock);
पूर्ण

अटल पूर्णांक ucb1x00_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा ucb1x00 *ucb = irq_data_get_irq_chip_data(data);
	अचिन्हित mask = 1 << (data->irq - ucb->irq_base);

	raw_spin_lock(&ucb->irq_lock);
	अगर (type & IRQ_TYPE_EDGE_RISING)
		ucb->irq_ris_enbl |= mask;
	अन्यथा
		ucb->irq_ris_enbl &= ~mask;

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		ucb->irq_fal_enbl |= mask;
	अन्यथा
		ucb->irq_fal_enbl &= ~mask;
	अगर (ucb->irq_mask & mask) अणु
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, ucb->irq_ris_enbl &
				  ucb->irq_mask);
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, ucb->irq_fal_enbl &
				  ucb->irq_mask);
	पूर्ण
	raw_spin_unlock(&ucb->irq_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ucb1x00_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा ucb1x00 *ucb = irq_data_get_irq_chip_data(data);
	काष्ठा ucb1x00_plat_data *pdata = ucb->mcp->attached_device.platक्रमm_data;
	अचिन्हित mask = 1 << (data->irq - ucb->irq_base);

	अगर (!pdata || !pdata->can_wakeup)
		वापस -EINVAL;

	raw_spin_lock(&ucb->irq_lock);
	अगर (on)
		ucb->irq_wake |= mask;
	अन्यथा
		ucb->irq_wake &= ~mask;
	raw_spin_unlock(&ucb->irq_lock);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ucb1x00_irqchip = अणु
	.name = "ucb1x00",
	.irq_ack = ucb1x00_irq_noop,
	.irq_mask = ucb1x00_irq_mask,
	.irq_unmask = ucb1x00_irq_unmask,
	.irq_set_type = ucb1x00_irq_set_type,
	.irq_set_wake = ucb1x00_irq_set_wake,
पूर्ण;

अटल पूर्णांक ucb1x00_add_dev(काष्ठा ucb1x00 *ucb, काष्ठा ucb1x00_driver *drv)
अणु
	काष्ठा ucb1x00_dev *dev;
	पूर्णांक ret;

	dev = kदो_स्मृति(माप(काष्ठा ucb1x00_dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->ucb = ucb;
	dev->drv = drv;

	ret = drv->add(dev);
	अगर (ret) अणु
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	list_add_tail(&dev->dev_node, &ucb->devs);
	list_add_tail(&dev->drv_node, &drv->devs);

	वापस ret;
पूर्ण

अटल व्योम ucb1x00_हटाओ_dev(काष्ठा ucb1x00_dev *dev)
अणु
	dev->drv->हटाओ(dev);
	list_del(&dev->dev_node);
	list_del(&dev->drv_node);
	kमुक्त(dev);
पूर्ण

/*
 * Try to probe our पूर्णांकerrupt, rather than relying on lots of
 * hard-coded machine dependencies.  For reference, the expected
 * IRQ mappings are:
 *
 *  	Machine		Default IRQ
 *	adsbitsy	IRQ_GPCIN4
 *	cerf		IRQ_GPIO_UCB1200_IRQ
 *	flexanet	IRQ_GPIO_GUI
 *	मुक्तbird	IRQ_GPIO_FREEBIRD_UCB1300_IRQ
 *	graphicsclient	ADS_EXT_IRQ(8)
 *	graphicsmaster	ADS_EXT_IRQ(8)
 *	lart		LART_IRQ_UCB1200
 *	omnimeter	IRQ_GPIO23
 *	pfs168		IRQ_GPIO_UCB1300_IRQ
 *	simpad		IRQ_GPIO_UCB1300_IRQ
 *	shannon		SHANNON_IRQ_GPIO_IRQ_CODEC
 *	yopy		IRQ_GPIO_UCB1200_IRQ
 */
अटल पूर्णांक ucb1x00_detect_irq(काष्ठा ucb1x00 *ucb)
अणु
	अचिन्हित दीर्घ mask;

	mask = probe_irq_on();

	/*
	 * Enable the ADC पूर्णांकerrupt.
	 */
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, UCB_IE_ADC);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, UCB_IE_ADC);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, 0xffff);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, 0);

	/*
	 * Cause an ADC पूर्णांकerrupt.
	 */
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, UCB_ADC_ENA);
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, UCB_ADC_ENA | UCB_ADC_START);

	/*
	 * Wait क्रम the conversion to complete.
	 */
	जबतक ((ucb1x00_reg_पढ़ो(ucb, UCB_ADC_DATA) & UCB_ADC_DAT_VAL) == 0);
	ucb1x00_reg_ग_लिखो(ucb, UCB_ADC_CR, 0);

	/*
	 * Disable and clear पूर्णांकerrupt.
	 */
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, 0);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, 0);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, 0xffff);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IE_CLEAR, 0);

	/*
	 * Read triggered पूर्णांकerrupt.
	 */
	वापस probe_irq_off(mask);
पूर्ण

अटल व्योम ucb1x00_release(काष्ठा device *dev)
अणु
	काष्ठा ucb1x00 *ucb = classdev_to_ucb1x00(dev);
	kमुक्त(ucb);
पूर्ण

अटल काष्ठा class ucb1x00_class = अणु
	.name		= "ucb1x00",
	.dev_release	= ucb1x00_release,
पूर्ण;

अटल पूर्णांक ucb1x00_probe(काष्ठा mcp *mcp)
अणु
	काष्ठा ucb1x00_plat_data *pdata = mcp->attached_device.platक्रमm_data;
	काष्ठा ucb1x00_driver *drv;
	काष्ठा ucb1x00 *ucb;
	अचिन्हित id, i, irq_base;
	पूर्णांक ret = -ENODEV;

	/* Tell the platक्रमm to deनिश्चित the UCB1x00 reset */
	अगर (pdata && pdata->reset)
		pdata->reset(UCB_RST_PROBE);

	mcp_enable(mcp);
	id = mcp_reg_पढ़ो(mcp, UCB_ID);
	mcp_disable(mcp);

	अगर (id != UCB_ID_1200 && id != UCB_ID_1300 && id != UCB_ID_TC35143) अणु
		prपूर्णांकk(KERN_WARNING "UCB1x00 ID not found: %04x\n", id);
		जाओ out;
	पूर्ण

	ucb = kzalloc(माप(काष्ठा ucb1x00), GFP_KERNEL);
	ret = -ENOMEM;
	अगर (!ucb)
		जाओ out;

	device_initialize(&ucb->dev);
	ucb->dev.class = &ucb1x00_class;
	ucb->dev.parent = &mcp->attached_device;
	dev_set_name(&ucb->dev, "ucb1x00");

	raw_spin_lock_init(&ucb->irq_lock);
	spin_lock_init(&ucb->io_lock);
	mutex_init(&ucb->adc_mutex);

	ucb->id  = id;
	ucb->mcp = mcp;

	ret = device_add(&ucb->dev);
	अगर (ret)
		जाओ err_dev_add;

	ucb1x00_enable(ucb);
	ucb->irq = ucb1x00_detect_irq(ucb);
	ucb1x00_disable(ucb);
	अगर (!ucb->irq) अणु
		dev_err(&ucb->dev, "IRQ probe failed\n");
		ret = -ENODEV;
		जाओ err_no_irq;
	पूर्ण

	ucb->gpio.base = -1;
	irq_base = pdata ? pdata->irq_base : 0;
	ucb->irq_base = irq_alloc_descs(-1, irq_base, 16, -1);
	अगर (ucb->irq_base < 0) अणु
		dev_err(&ucb->dev, "unable to allocate 16 irqs: %d\n",
			ucb->irq_base);
		ret = ucb->irq_base;
		जाओ err_irq_alloc;
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित irq = ucb->irq_base + i;

		irq_set_chip_and_handler(irq, &ucb1x00_irqchip, handle_edge_irq);
		irq_set_chip_data(irq, ucb);
		irq_clear_status_flags(irq, IRQ_NOREQUEST);
	पूर्ण

	irq_set_irq_type(ucb->irq, IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler_and_data(ucb->irq, ucb1x00_irq, ucb);

	अगर (pdata && pdata->gpio_base) अणु
		ucb->gpio.label = dev_name(&ucb->dev);
		ucb->gpio.parent = &ucb->dev;
		ucb->gpio.owner = THIS_MODULE;
		ucb->gpio.base = pdata->gpio_base;
		ucb->gpio.ngpio = 10;
		ucb->gpio.set = ucb1x00_gpio_set;
		ucb->gpio.get = ucb1x00_gpio_get;
		ucb->gpio.direction_input = ucb1x00_gpio_direction_input;
		ucb->gpio.direction_output = ucb1x00_gpio_direction_output;
		ucb->gpio.to_irq = ucb1x00_to_irq;
		ret = gpiochip_add_data(&ucb->gpio, ucb);
		अगर (ret)
			जाओ err_gpio_add;
	पूर्ण अन्यथा
		dev_info(&ucb->dev, "gpio_base not set so no gpiolib support");

	mcp_set_drvdata(mcp, ucb);

	अगर (pdata)
		device_set_wakeup_capable(&ucb->dev, pdata->can_wakeup);

	INIT_LIST_HEAD(&ucb->devs);
	mutex_lock(&ucb1x00_mutex);
	list_add_tail(&ucb->node, &ucb1x00_devices);
	list_क्रम_each_entry(drv, &ucb1x00_drivers, node) अणु
		ucb1x00_add_dev(ucb, drv);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);

	वापस ret;

 err_gpio_add:
	irq_set_chained_handler(ucb->irq, शून्य);
 err_irq_alloc:
	अगर (ucb->irq_base > 0)
		irq_मुक्त_descs(ucb->irq_base, 16);
 err_no_irq:
	device_del(&ucb->dev);
 err_dev_add:
	put_device(&ucb->dev);
 out:
	अगर (pdata && pdata->reset)
		pdata->reset(UCB_RST_PROBE_FAIL);
	वापस ret;
पूर्ण

अटल व्योम ucb1x00_हटाओ(काष्ठा mcp *mcp)
अणु
	काष्ठा ucb1x00_plat_data *pdata = mcp->attached_device.platक्रमm_data;
	काष्ठा ucb1x00 *ucb = mcp_get_drvdata(mcp);
	काष्ठा list_head *l, *n;

	mutex_lock(&ucb1x00_mutex);
	list_del(&ucb->node);
	list_क्रम_each_safe(l, n, &ucb->devs) अणु
		काष्ठा ucb1x00_dev *dev = list_entry(l, काष्ठा ucb1x00_dev, dev_node);
		ucb1x00_हटाओ_dev(dev);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);

	अगर (ucb->gpio.base != -1)
		gpiochip_हटाओ(&ucb->gpio);

	irq_set_chained_handler(ucb->irq, शून्य);
	irq_मुक्त_descs(ucb->irq_base, 16);
	device_unरेजिस्टर(&ucb->dev);

	अगर (pdata && pdata->reset)
		pdata->reset(UCB_RST_REMOVE);
पूर्ण

पूर्णांक ucb1x00_रेजिस्टर_driver(काष्ठा ucb1x00_driver *drv)
अणु
	काष्ठा ucb1x00 *ucb;

	INIT_LIST_HEAD(&drv->devs);
	mutex_lock(&ucb1x00_mutex);
	list_add_tail(&drv->node, &ucb1x00_drivers);
	list_क्रम_each_entry(ucb, &ucb1x00_devices, node) अणु
		ucb1x00_add_dev(ucb, drv);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);
	वापस 0;
पूर्ण

व्योम ucb1x00_unरेजिस्टर_driver(काष्ठा ucb1x00_driver *drv)
अणु
	काष्ठा list_head *n, *l;

	mutex_lock(&ucb1x00_mutex);
	list_del(&drv->node);
	list_क्रम_each_safe(l, n, &drv->devs) अणु
		काष्ठा ucb1x00_dev *dev = list_entry(l, काष्ठा ucb1x00_dev, drv_node);
		ucb1x00_हटाओ_dev(dev);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ucb1x00_suspend(काष्ठा device *dev)
अणु
	काष्ठा ucb1x00_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा ucb1x00 *ucb = dev_get_drvdata(dev);
	काष्ठा ucb1x00_dev *udev;

	mutex_lock(&ucb1x00_mutex);
	list_क्रम_each_entry(udev, &ucb->devs, dev_node) अणु
		अगर (udev->drv->suspend)
			udev->drv->suspend(udev);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);

	अगर (ucb->irq_wake) अणु
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&ucb->irq_lock, flags);
		ucb1x00_enable(ucb);
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, ucb->irq_ris_enbl &
				  ucb->irq_wake);
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, ucb->irq_fal_enbl &
				  ucb->irq_wake);
		ucb1x00_disable(ucb);
		raw_spin_unlock_irqrestore(&ucb->irq_lock, flags);

		enable_irq_wake(ucb->irq);
	पूर्ण अन्यथा अगर (pdata && pdata->reset)
		pdata->reset(UCB_RST_SUSPEND);

	वापस 0;
पूर्ण

अटल पूर्णांक ucb1x00_resume(काष्ठा device *dev)
अणु
	काष्ठा ucb1x00_plat_data *pdata = dev_get_platdata(dev);
	काष्ठा ucb1x00 *ucb = dev_get_drvdata(dev);
	काष्ठा ucb1x00_dev *udev;

	अगर (!ucb->irq_wake && pdata && pdata->reset)
		pdata->reset(UCB_RST_RESUME);

	ucb1x00_enable(ucb);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_DATA, ucb->io_out);
	ucb1x00_reg_ग_लिखो(ucb, UCB_IO_सूची, ucb->io_dir);

	अगर (ucb->irq_wake) अणु
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&ucb->irq_lock, flags);
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_RIS, ucb->irq_ris_enbl &
				  ucb->irq_mask);
		ucb1x00_reg_ग_लिखो(ucb, UCB_IE_FAL, ucb->irq_fal_enbl &
				  ucb->irq_mask);
		raw_spin_unlock_irqrestore(&ucb->irq_lock, flags);

		disable_irq_wake(ucb->irq);
	पूर्ण
	ucb1x00_disable(ucb);

	mutex_lock(&ucb1x00_mutex);
	list_क्रम_each_entry(udev, &ucb->devs, dev_node) अणु
		अगर (udev->drv->resume)
			udev->drv->resume(udev);
	पूर्ण
	mutex_unlock(&ucb1x00_mutex);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ucb1x00_pm_ops, ucb1x00_suspend, ucb1x00_resume);

अटल काष्ठा mcp_driver ucb1x00_driver = अणु
	.drv		= अणु
		.name	= "ucb1x00",
		.owner	= THIS_MODULE,
		.pm	= &ucb1x00_pm_ops,
	पूर्ण,
	.probe		= ucb1x00_probe,
	.हटाओ		= ucb1x00_हटाओ,
पूर्ण;

अटल पूर्णांक __init ucb1x00_init(व्योम)
अणु
	पूर्णांक ret = class_रेजिस्टर(&ucb1x00_class);
	अगर (ret == 0) अणु
		ret = mcp_driver_रेजिस्टर(&ucb1x00_driver);
		अगर (ret)
			class_unरेजिस्टर(&ucb1x00_class);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास ucb1x00_निकास(व्योम)
अणु
	mcp_driver_unरेजिस्टर(&ucb1x00_driver);
	class_unरेजिस्टर(&ucb1x00_class);
पूर्ण

module_init(ucb1x00_init);
module_निकास(ucb1x00_निकास);

EXPORT_SYMBOL(ucb1x00_io_set_dir);
EXPORT_SYMBOL(ucb1x00_io_ग_लिखो);
EXPORT_SYMBOL(ucb1x00_io_पढ़ो);

EXPORT_SYMBOL(ucb1x00_adc_enable);
EXPORT_SYMBOL(ucb1x00_adc_पढ़ो);
EXPORT_SYMBOL(ucb1x00_adc_disable);

EXPORT_SYMBOL(ucb1x00_रेजिस्टर_driver);
EXPORT_SYMBOL(ucb1x00_unरेजिस्टर_driver);

MODULE_ALIAS("mcp:ucb1x00");
MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("UCB1x00 core driver");
MODULE_LICENSE("GPL");
