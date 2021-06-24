<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  htc-i2cpld.c
 *  Chip driver क्रम an unknown CPLD chip found on omap850 HTC devices like
 *  the HTC Wizard and HTC Herald.
 *  The cpld is located on the i2c bus and acts as an input/output GPIO
 *  extender.
 *
 *  Copyright (C) 2009 Cory Maccarrone <darkstar6262@gmail.com>
 *
 *  Based on work करोne in the linwizard project
 *  Copyright (C) 2008-2009 Angelo Arrअगरano <miknix@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/htcpld.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

काष्ठा htcpld_chip अणु
	spinlock_t              lock;

	/* chip info */
	u8                      reset;
	u8                      addr;
	काष्ठा device           *dev;
	काष्ठा i2c_client	*client;

	/* Output details */
	u8                      cache_out;
	काष्ठा gpio_chip        chip_out;

	/* Input details */
	u8                      cache_in;
	काष्ठा gpio_chip        chip_in;

	u16                     irqs_enabled;
	uपूर्णांक                    irq_start;
	पूर्णांक                     nirqs;

	अचिन्हित पूर्णांक		flow_type;
	/*
	 * Work काष्ठाure to allow क्रम setting values outside of any
	 * possible पूर्णांकerrupt context
	 */
	काष्ठा work_काष्ठा set_val_work;
पूर्ण;

काष्ठा htcpld_data अणु
	/* irq info */
	u16                irqs_enabled;
	uपूर्णांक               irq_start;
	पूर्णांक                nirqs;
	uपूर्णांक               chained_irq;
	अचिन्हित पूर्णांक       पूर्णांक_reset_gpio_hi;
	अचिन्हित पूर्णांक       पूर्णांक_reset_gpio_lo;

	/* htcpld info */
	काष्ठा htcpld_chip *chip;
	अचिन्हित पूर्णांक       nchips;
पूर्ण;

/* There करोes not appear to be a way to proactively mask पूर्णांकerrupts
 * on the htcpld chip itself.  So, we simply ignore पूर्णांकerrupts that
 * aren't desired. */
अटल व्योम htcpld_mask(काष्ठा irq_data *data)
अणु
	काष्ठा htcpld_chip *chip = irq_data_get_irq_chip_data(data);
	chip->irqs_enabled &= ~(1 << (data->irq - chip->irq_start));
	pr_debug("HTCPLD mask %d %04x\n", data->irq, chip->irqs_enabled);
पूर्ण
अटल व्योम htcpld_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा htcpld_chip *chip = irq_data_get_irq_chip_data(data);
	chip->irqs_enabled |= 1 << (data->irq - chip->irq_start);
	pr_debug("HTCPLD unmask %d %04x\n", data->irq, chip->irqs_enabled);
पूर्ण

अटल पूर्णांक htcpld_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा htcpld_chip *chip = irq_data_get_irq_chip_data(data);

	अगर (flags & ~IRQ_TYPE_SENSE_MASK)
		वापस -EINVAL;

	/* We only allow edge triggering */
	अगर (flags & (IRQ_TYPE_LEVEL_LOW|IRQ_TYPE_LEVEL_HIGH))
		वापस -EINVAL;

	chip->flow_type = flags;
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip htcpld_muxed_chip = अणु
	.name         = "htcpld",
	.irq_mask     = htcpld_mask,
	.irq_unmask   = htcpld_unmask,
	.irq_set_type = htcpld_set_type,
पूर्ण;

/* To properly dispatch IRQ events, we need to पढ़ो from the
 * chip.  This is an I2C action that could possibly sleep
 * (which is bad in पूर्णांकerrupt context) -- so we use a thपढ़ोed
 * पूर्णांकerrupt handler to get around that.
 */
अटल irqवापस_t htcpld_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा htcpld_data *htcpld = dev;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	पूर्णांक irqpin;

	अगर (!htcpld) अणु
		pr_debug("htcpld is null in ISR\n");
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * For each chip, करो a पढ़ो of the chip and trigger any पूर्णांकerrupts
	 * desired.  The पूर्णांकerrupts will be triggered from LSB to MSB (i.e.
	 * bit 0 first, then bit 1, etc.)
	 *
	 * For chips that have no पूर्णांकerrupt range specअगरied, just skip 'em.
	 */
	क्रम (i = 0; i < htcpld->nchips; i++) अणु
		काष्ठा htcpld_chip *chip = &htcpld->chip[i];
		काष्ठा i2c_client *client;
		पूर्णांक val;
		अचिन्हित दीर्घ uval, old_val;

		अगर (!chip) अणु
			pr_debug("chip %d is null in ISR\n", i);
			जारी;
		पूर्ण

		अगर (chip->nirqs == 0)
			जारी;

		client = chip->client;
		अगर (!client) अणु
			pr_debug("client %d is null in ISR\n", i);
			जारी;
		पूर्ण

		/* Scan the chip */
		val = i2c_smbus_पढ़ो_byte_data(client, chip->cache_out);
		अगर (val < 0) अणु
			/* Throw a warning and skip this chip */
			dev_warn(chip->dev, "Unable to read from chip: %d\n",
				 val);
			जारी;
		पूर्ण

		uval = (अचिन्हित दीर्घ)val;

		spin_lock_irqsave(&chip->lock, flags);

		/* Save away the old value so we can compare it */
		old_val = chip->cache_in;

		/* Write the new value */
		chip->cache_in = uval;

		spin_unlock_irqrestore(&chip->lock, flags);

		/*
		 * For each bit in the data (starting at bit 0), trigger
		 * associated पूर्णांकerrupts.
		 */
		क्रम (irqpin = 0; irqpin < chip->nirqs; irqpin++) अणु
			अचिन्हित oldb, newb, type = chip->flow_type;

			irq = chip->irq_start + irqpin;

			/* Run the IRQ handler, but only अगर the bit value
			 * changed, and the proper flags are set */
			oldb = (old_val >> irqpin) & 1;
			newb = (uval >> irqpin) & 1;

			अगर ((!oldb && newb && (type & IRQ_TYPE_EDGE_RISING)) ||
			    (oldb && !newb && (type & IRQ_TYPE_EDGE_FALLING))) अणु
				pr_debug("fire IRQ %d\n", irqpin);
				generic_handle_irq(irq);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * In order to जारी receiving पूर्णांकerrupts, the पूर्णांक_reset_gpio must
	 * be निश्चितed.
	 */
	अगर (htcpld->पूर्णांक_reset_gpio_hi)
		gpio_set_value(htcpld->पूर्णांक_reset_gpio_hi, 1);
	अगर (htcpld->पूर्णांक_reset_gpio_lo)
		gpio_set_value(htcpld->पूर्णांक_reset_gpio_lo, 0);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * The GPIO set routines can be called from पूर्णांकerrupt context, especially अगर,
 * क्रम example they're attached to the led-gpio framework and a trigger is
 * enabled.  As such, we declared work above in the htcpld_chip काष्ठाure,
 * and that work is scheduled in the set routine.  The kernel can then run
 * the I2C functions, which will sleep, in process context.
 */
अटल व्योम htcpld_chip_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा i2c_client *client;
	काष्ठा htcpld_chip *chip_data = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	client = chip_data->client;
	अगर (!client)
		वापस;

	spin_lock_irqsave(&chip_data->lock, flags);
	अगर (val)
		chip_data->cache_out |= (1 << offset);
	अन्यथा
		chip_data->cache_out &= ~(1 << offset);
	spin_unlock_irqrestore(&chip_data->lock, flags);

	schedule_work(&(chip_data->set_val_work));
पूर्ण

अटल व्योम htcpld_chip_set_ni(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा htcpld_chip *chip_data;
	काष्ठा i2c_client *client;

	chip_data = container_of(work, काष्ठा htcpld_chip, set_val_work);
	client = chip_data->client;
	i2c_smbus_पढ़ो_byte_data(client, chip_data->cache_out);
पूर्ण

अटल पूर्णांक htcpld_chip_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा htcpld_chip *chip_data = gpiochip_get_data(chip);
	u8 cache;

	अगर (!म_भेदन(chip->label, "htcpld-out", 10)) अणु
		cache = chip_data->cache_out;
	पूर्ण अन्यथा अगर (!म_भेदन(chip->label, "htcpld-in", 9)) अणु
		cache = chip_data->cache_in;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस (cache >> offset) & 1;
पूर्ण

अटल पूर्णांक htcpld_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	htcpld_chip_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक htcpld_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	/*
	 * No-op: this function can only be called on the input chip.
	 * We करो however make sure the offset is within range.
	 */
	वापस (offset < chip->ngpio) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक htcpld_chip_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा htcpld_chip *chip_data = gpiochip_get_data(chip);

	अगर (offset < chip_data->nirqs)
		वापस chip_data->irq_start + offset;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम htcpld_chip_reset(काष्ठा i2c_client *client)
अणु
	काष्ठा htcpld_chip *chip_data = i2c_get_clientdata(client);
	अगर (!chip_data)
		वापस;

	i2c_smbus_पढ़ो_byte_data(
		client, (chip_data->cache_out = chip_data->reset));
पूर्ण

अटल पूर्णांक htcpld_setup_chip_irq(
		काष्ठा platक्रमm_device *pdev,
		पूर्णांक chip_index)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा htcpld_chip *chip;
	अचिन्हित पूर्णांक irq, irq_end;

	/* Get the platक्रमm and driver data */
	htcpld = platक्रमm_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];

	/* Setup irq handlers */
	irq_end = chip->irq_start + chip->nirqs;
	क्रम (irq = chip->irq_start; irq < irq_end; irq++) अणु
		irq_set_chip_and_handler(irq, &htcpld_muxed_chip,
					 handle_simple_irq);
		irq_set_chip_data(irq, chip);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक htcpld_रेजिस्टर_chip_i2c(
		काष्ठा platक्रमm_device *pdev,
		पूर्णांक chip_index)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा htcpld_core_platक्रमm_data *pdata;
	काष्ठा htcpld_chip *chip;
	काष्ठा htcpld_chip_platक्रमm_data *plat_chip_data;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info info;

	/* Get the platक्रमm and driver data */
	pdata = dev_get_platdata(dev);
	htcpld = platक्रमm_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];
	plat_chip_data = &pdata->chip[chip_index];

	adapter = i2c_get_adapter(pdata->i2c_adapter_id);
	अगर (!adapter) अणु
		/* Eek, no such I2C adapter!  Bail out. */
		dev_warn(dev, "Chip at i2c address 0x%x: Invalid i2c adapter %d\n",
			 plat_chip_data->addr, pdata->i2c_adapter_id);
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_BYTE_DATA)) अणु
		dev_warn(dev, "i2c adapter %d non-functional\n",
			 pdata->i2c_adapter_id);
		i2c_put_adapter(adapter);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	info.addr = plat_chip_data->addr;
	strlcpy(info.type, "htcpld-chip", I2C_NAME_SIZE);
	info.platक्रमm_data = chip;

	/* Add the I2C device.  This calls the probe() function. */
	client = i2c_new_client_device(adapter, &info);
	अगर (IS_ERR(client)) अणु
		/* I2C device registration failed, contineu with the next */
		dev_warn(dev, "Unable to add I2C device for 0x%x\n",
			 plat_chip_data->addr);
		i2c_put_adapter(adapter);
		वापस PTR_ERR(client);
	पूर्ण

	i2c_set_clientdata(client, chip);
	snम_लिखो(client->name, I2C_NAME_SIZE, "Chip_0x%x", client->addr);
	chip->client = client;

	/* Reset the chip */
	htcpld_chip_reset(client);
	chip->cache_in = i2c_smbus_पढ़ो_byte_data(client, chip->cache_out);

	वापस 0;
पूर्ण

अटल व्योम htcpld_unरेजिस्टर_chip_i2c(
		काष्ठा platक्रमm_device *pdev,
		पूर्णांक chip_index)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा htcpld_chip *chip;

	/* Get the platक्रमm and driver data */
	htcpld = platक्रमm_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];

	i2c_unरेजिस्टर_device(chip->client);
पूर्ण

अटल पूर्णांक htcpld_रेजिस्टर_chip_gpio(
		काष्ठा platक्रमm_device *pdev,
		पूर्णांक chip_index)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा htcpld_core_platक्रमm_data *pdata;
	काष्ठा htcpld_chip *chip;
	काष्ठा htcpld_chip_platक्रमm_data *plat_chip_data;
	काष्ठा gpio_chip *gpio_chip;
	पूर्णांक ret = 0;

	/* Get the platक्रमm and driver data */
	pdata = dev_get_platdata(dev);
	htcpld = platक्रमm_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];
	plat_chip_data = &pdata->chip[chip_index];

	/* Setup the GPIO chips */
	gpio_chip = &(chip->chip_out);
	gpio_chip->label           = "htcpld-out";
	gpio_chip->parent             = dev;
	gpio_chip->owner           = THIS_MODULE;
	gpio_chip->get             = htcpld_chip_get;
	gpio_chip->set             = htcpld_chip_set;
	gpio_chip->direction_input = शून्य;
	gpio_chip->direction_output = htcpld_direction_output;
	gpio_chip->base            = plat_chip_data->gpio_out_base;
	gpio_chip->ngpio           = plat_chip_data->num_gpios;

	gpio_chip = &(chip->chip_in);
	gpio_chip->label           = "htcpld-in";
	gpio_chip->parent             = dev;
	gpio_chip->owner           = THIS_MODULE;
	gpio_chip->get             = htcpld_chip_get;
	gpio_chip->set             = शून्य;
	gpio_chip->direction_input = htcpld_direction_input;
	gpio_chip->direction_output = शून्य;
	gpio_chip->to_irq          = htcpld_chip_to_irq;
	gpio_chip->base            = plat_chip_data->gpio_in_base;
	gpio_chip->ngpio           = plat_chip_data->num_gpios;

	/* Add the GPIO chips */
	ret = gpiochip_add_data(&(chip->chip_out), chip);
	अगर (ret) अणु
		dev_warn(dev, "Unable to register output GPIOs for 0x%x: %d\n",
			 plat_chip_data->addr, ret);
		वापस ret;
	पूर्ण

	ret = gpiochip_add_data(&(chip->chip_in), chip);
	अगर (ret) अणु
		dev_warn(dev, "Unable to register input GPIOs for 0x%x: %d\n",
			 plat_chip_data->addr, ret);
		gpiochip_हटाओ(&(chip->chip_out));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक htcpld_setup_chips(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा htcpld_core_platक्रमm_data *pdata;
	पूर्णांक i;

	/* Get the platक्रमm and driver data */
	pdata = dev_get_platdata(dev);
	htcpld = platक्रमm_get_drvdata(pdev);

	/* Setup each chip's output GPIOs */
	htcpld->nchips = pdata->num_chip;
	htcpld->chip = devm_kसुस्मृति(dev,
				    htcpld->nchips,
				    माप(काष्ठा htcpld_chip),
				    GFP_KERNEL);
	अगर (!htcpld->chip)
		वापस -ENOMEM;

	/* Add the chips as best we can */
	क्रम (i = 0; i < htcpld->nchips; i++) अणु
		पूर्णांक ret;

		/* Setup the HTCPLD chips */
		htcpld->chip[i].reset = pdata->chip[i].reset;
		htcpld->chip[i].cache_out = pdata->chip[i].reset;
		htcpld->chip[i].cache_in = 0;
		htcpld->chip[i].dev = dev;
		htcpld->chip[i].irq_start = pdata->chip[i].irq_base;
		htcpld->chip[i].nirqs = pdata->chip[i].num_irqs;

		INIT_WORK(&(htcpld->chip[i].set_val_work), &htcpld_chip_set_ni);
		spin_lock_init(&(htcpld->chip[i].lock));

		/* Setup the पूर्णांकerrupts क्रम the chip */
		अगर (htcpld->chained_irq) अणु
			ret = htcpld_setup_chip_irq(pdev, i);
			अगर (ret)
				जारी;
		पूर्ण

		/* Register the chip with I2C */
		ret = htcpld_रेजिस्टर_chip_i2c(pdev, i);
		अगर (ret)
			जारी;


		/* Register the chips with the GPIO subप्रणाली */
		ret = htcpld_रेजिस्टर_chip_gpio(pdev, i);
		अगर (ret) अणु
			/* Unरेजिस्टर the chip from i2c and जारी */
			htcpld_unरेजिस्टर_chip_i2c(pdev, i);
			जारी;
		पूर्ण

		dev_info(dev, "Registered chip at 0x%x\n", pdata->chip[i].addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक htcpld_core_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा htcpld_data *htcpld;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा htcpld_core_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस -ENODEV;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		dev_warn(dev, "Platform data not found for htcpld core!\n");
		वापस -ENXIO;
	पूर्ण

	htcpld = devm_kzalloc(dev, माप(काष्ठा htcpld_data), GFP_KERNEL);
	अगर (!htcpld)
		वापस -ENOMEM;

	/* Find chained irq */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res) अणु
		पूर्णांक flags;
		htcpld->chained_irq = res->start;

		/* Setup the chained पूर्णांकerrupt handler */
		flags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT;
		ret = request_thपढ़ोed_irq(htcpld->chained_irq,
					   शून्य, htcpld_handler,
					   flags, pdev->name, htcpld);
		अगर (ret) अणु
			dev_warn(dev, "Unable to setup chained irq handler: %d\n", ret);
			वापस ret;
		पूर्ण अन्यथा
			device_init_wakeup(dev, 0);
	पूर्ण

	/* Set the driver data */
	platक्रमm_set_drvdata(pdev, htcpld);

	/* Setup the htcpld chips */
	ret = htcpld_setup_chips(pdev);
	अगर (ret)
		वापस ret;

	/* Request the GPIO(s) क्रम the पूर्णांक reset and set them up */
	अगर (pdata->पूर्णांक_reset_gpio_hi) अणु
		ret = gpio_request(pdata->पूर्णांक_reset_gpio_hi, "htcpld-core");
		अगर (ret) अणु
			/*
			 * If it failed, that sucks, but we can probably
			 * जारी on without it.
			 */
			dev_warn(dev, "Unable to request int_reset_gpio_hi -- interrupts may not work\n");
			htcpld->पूर्णांक_reset_gpio_hi = 0;
		पूर्ण अन्यथा अणु
			htcpld->पूर्णांक_reset_gpio_hi = pdata->पूर्णांक_reset_gpio_hi;
			gpio_set_value(htcpld->पूर्णांक_reset_gpio_hi, 1);
		पूर्ण
	पूर्ण

	अगर (pdata->पूर्णांक_reset_gpio_lo) अणु
		ret = gpio_request(pdata->पूर्णांक_reset_gpio_lo, "htcpld-core");
		अगर (ret) अणु
			/*
			 * If it failed, that sucks, but we can probably
			 * जारी on without it.
			 */
			dev_warn(dev, "Unable to request int_reset_gpio_lo -- interrupts may not work\n");
			htcpld->पूर्णांक_reset_gpio_lo = 0;
		पूर्ण अन्यथा अणु
			htcpld->पूर्णांक_reset_gpio_lo = pdata->पूर्णांक_reset_gpio_lo;
			gpio_set_value(htcpld->पूर्णांक_reset_gpio_lo, 0);
		पूर्ण
	पूर्ण

	dev_info(dev, "Initialized successfully\n");
	वापस 0;
पूर्ण

/* The I2C Driver -- used पूर्णांकernally */
अटल स्थिर काष्ठा i2c_device_id htcpld_chip_id[] = अणु
	अणु "htcpld-chip", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver htcpld_chip_driver = अणु
	.driver = अणु
		.name	= "htcpld-chip",
	पूर्ण,
	.id_table = htcpld_chip_id,
पूर्ण;

/* The Core Driver */
अटल काष्ठा platक्रमm_driver htcpld_core_driver = अणु
	.driver = अणु
		.name = "i2c-htcpld",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init htcpld_core_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register the I2C Chip driver */
	ret = i2c_add_driver(&htcpld_chip_driver);
	अगर (ret)
		वापस ret;

	/* Probe क्रम our chips */
	वापस platक्रमm_driver_probe(&htcpld_core_driver, htcpld_core_probe);
पूर्ण
device_initcall(htcpld_core_init);
