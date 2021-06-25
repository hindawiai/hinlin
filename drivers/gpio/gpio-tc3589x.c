<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Hanumath Prasad <hanumath.prasad@stericsson.com> क्रम ST-Ericsson
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/tc3589x.h>
#समावेश <linux/bitops.h>

/*
 * These रेजिस्टरs are modअगरied under the irq bus lock and cached to aव्योम
 * unnecessary ग_लिखोs in bus_sync_unlock.
 */
क्रमागत अणु REG_IBE, REG_IEV, REG_IS, REG_IE, REG_सूचीECT पूर्ण;

#घोषणा CACHE_NR_REGS	5
#घोषणा CACHE_NR_BANKS	3

काष्ठा tc3589x_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा tc3589x *tc3589x;
	काष्ठा device *dev;
	काष्ठा mutex irq_lock;
	/* Caches of पूर्णांकerrupt control रेजिस्टरs क्रम bus_lock */
	u8 regs[CACHE_NR_REGS][CACHE_NR_BANKS];
	u8 oldregs[CACHE_NR_REGS][CACHE_NR_BANKS];
पूर्ण;

अटल पूर्णांक tc3589x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 reg = TC3589x_GPIODATA0 + (offset / 8) * 2;
	u8 mask = BIT(offset % 8);
	पूर्णांक ret;

	ret = tc3589x_reg_पढ़ो(tc3589x, reg);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & mask);
पूर्ण

अटल व्योम tc3589x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 reg = TC3589x_GPIODATA0 + (offset / 8) * 2;
	अचिन्हित पूर्णांक pos = offset % 8;
	u8 data[] = अणुval ? BIT(pos) : 0, BIT(pos)पूर्ण;

	tc3589x_block_ग_लिखो(tc3589x, reg, ARRAY_SIZE(data), data);
पूर्ण

अटल पूर्णांक tc3589x_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 reg = TC3589x_GPIOसूची0 + offset / 8;
	अचिन्हित पूर्णांक pos = offset % 8;

	tc3589x_gpio_set(chip, offset, val);

	वापस tc3589x_set_bits(tc3589x, reg, BIT(pos), BIT(pos));
पूर्ण

अटल पूर्णांक tc3589x_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 reg = TC3589x_GPIOसूची0 + offset / 8;
	अचिन्हित पूर्णांक pos = offset % 8;

	वापस tc3589x_set_bits(tc3589x, reg, BIT(pos), 0);
पूर्ण

अटल पूर्णांक tc3589x_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 reg = TC3589x_GPIOसूची0 + offset / 8;
	अचिन्हित पूर्णांक pos = offset % 8;
	पूर्णांक ret;

	ret = tc3589x_reg_पढ़ो(tc3589x, reg);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & BIT(pos))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक tc3589x_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	/*
	 * These रेजिस्टरs are alterated at each second address
	 * ODM bit 0 = drive to GND or Hi-Z (खोलो drain)
	 * ODM bit 1 = drive to VDD or Hi-Z (खोलो source)
	 */
	u8 odmreg = TC3589x_GPIOODM0 + (offset / 8) * 2;
	u8 odereg = TC3589x_GPIOODE0 + (offset / 8) * 2;
	अचिन्हित पूर्णांक pos = offset % 8;
	पूर्णांक ret;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		/* Set खोलो drain mode */
		ret = tc3589x_set_bits(tc3589x, odmreg, BIT(pos), 0);
		अगर (ret)
			वापस ret;
		/* Enable खोलो drain/source mode */
		वापस tc3589x_set_bits(tc3589x, odereg, BIT(pos), BIT(pos));
	हाल PIN_CONFIG_DRIVE_OPEN_SOURCE:
		/* Set खोलो source mode */
		ret = tc3589x_set_bits(tc3589x, odmreg, BIT(pos), BIT(pos));
		अगर (ret)
			वापस ret;
		/* Enable खोलो drain/source mode */
		वापस tc3589x_set_bits(tc3589x, odereg, BIT(pos), BIT(pos));
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		/* Disable खोलो drain/source mode */
		वापस tc3589x_set_bits(tc3589x, odereg, BIT(pos), 0);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "tc3589x",
	.owner			= THIS_MODULE,
	.get			= tc3589x_gpio_get,
	.set			= tc3589x_gpio_set,
	.direction_output	= tc3589x_gpio_direction_output,
	.direction_input	= tc3589x_gpio_direction_input,
	.get_direction		= tc3589x_gpio_get_direction,
	.set_config		= tc3589x_gpio_set_config,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक tc3589x_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	अगर (type == IRQ_TYPE_EDGE_BOTH) अणु
		tc3589x_gpio->regs[REG_IBE][regoffset] |= mask;
		वापस 0;
	पूर्ण

	tc3589x_gpio->regs[REG_IBE][regoffset] &= ~mask;

	अगर (type == IRQ_TYPE_LEVEL_LOW || type == IRQ_TYPE_LEVEL_HIGH)
		tc3589x_gpio->regs[REG_IS][regoffset] |= mask;
	अन्यथा
		tc3589x_gpio->regs[REG_IS][regoffset] &= ~mask;

	अगर (type == IRQ_TYPE_EDGE_RISING || type == IRQ_TYPE_LEVEL_HIGH)
		tc3589x_gpio->regs[REG_IEV][regoffset] |= mask;
	अन्यथा
		tc3589x_gpio->regs[REG_IEV][regoffset] &= ~mask;

	वापस 0;
पूर्ण

अटल व्योम tc3589x_gpio_irq_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);

	mutex_lock(&tc3589x_gpio->irq_lock);
पूर्ण

अटल व्योम tc3589x_gpio_irq_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	अटल स्थिर u8 regmap[] = अणु
		[REG_IBE]	= TC3589x_GPIOIBE0,
		[REG_IEV]	= TC3589x_GPIOIEV0,
		[REG_IS]	= TC3589x_GPIOIS0,
		[REG_IE]	= TC3589x_GPIOIE0,
		[REG_सूचीECT]	= TC3589x_सूचीECT0,
	पूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0; i < CACHE_NR_REGS; i++) अणु
		क्रम (j = 0; j < CACHE_NR_BANKS; j++) अणु
			u8 old = tc3589x_gpio->oldregs[i][j];
			u8 new = tc3589x_gpio->regs[i][j];

			अगर (new == old)
				जारी;

			tc3589x_gpio->oldregs[i][j] = new;
			tc3589x_reg_ग_लिखो(tc3589x, regmap[i] + j, new);
		पूर्ण
	पूर्ण

	mutex_unlock(&tc3589x_gpio->irq_lock);
पूर्ण

अटल व्योम tc3589x_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	tc3589x_gpio->regs[REG_IE][regoffset] &= ~mask;
	tc3589x_gpio->regs[REG_सूचीECT][regoffset] |= mask;
पूर्ण

अटल व्योम tc3589x_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	tc3589x_gpio->regs[REG_IE][regoffset] |= mask;
	tc3589x_gpio->regs[REG_सूचीECT][regoffset] &= ~mask;
पूर्ण

अटल काष्ठा irq_chip tc3589x_gpio_irq_chip = अणु
	.name			= "tc3589x-gpio",
	.irq_bus_lock		= tc3589x_gpio_irq_lock,
	.irq_bus_sync_unlock	= tc3589x_gpio_irq_sync_unlock,
	.irq_mask		= tc3589x_gpio_irq_mask,
	.irq_unmask		= tc3589x_gpio_irq_unmask,
	.irq_set_type		= tc3589x_gpio_irq_set_type,
पूर्ण;

अटल irqवापस_t tc3589x_gpio_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा tc3589x_gpio *tc3589x_gpio = dev;
	काष्ठा tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 status[CACHE_NR_BANKS];
	पूर्णांक ret;
	पूर्णांक i;

	ret = tc3589x_block_पढ़ो(tc3589x, TC3589x_GPIOMIS0,
				 ARRAY_SIZE(status), status);
	अगर (ret < 0)
		वापस IRQ_NONE;

	क्रम (i = 0; i < ARRAY_SIZE(status); i++) अणु
		अचिन्हित पूर्णांक stat = status[i];
		अगर (!stat)
			जारी;

		जबतक (stat) अणु
			पूर्णांक bit = __ffs(stat);
			पूर्णांक line = i * 8 + bit;
			पूर्णांक irq = irq_find_mapping(tc3589x_gpio->chip.irq.करोमुख्य,
						   line);

			handle_nested_irq(irq);
			stat &= ~(1 << bit);
		पूर्ण

		tc3589x_reg_ग_लिखो(tc3589x, TC3589x_GPIOIC0 + i, status[i]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tc3589x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tc3589x *tc3589x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा tc3589x_gpio *tc3589x_gpio;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret;
	पूर्णांक irq;

	अगर (!np) अणु
		dev_err(&pdev->dev, "No Device Tree node found\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	tc3589x_gpio = devm_kzalloc(&pdev->dev, माप(काष्ठा tc3589x_gpio),
				    GFP_KERNEL);
	अगर (!tc3589x_gpio)
		वापस -ENOMEM;

	mutex_init(&tc3589x_gpio->irq_lock);

	tc3589x_gpio->dev = &pdev->dev;
	tc3589x_gpio->tc3589x = tc3589x;

	tc3589x_gpio->chip = ढाँचा_chip;
	tc3589x_gpio->chip.ngpio = tc3589x->num_gpio;
	tc3589x_gpio->chip.parent = &pdev->dev;
	tc3589x_gpio->chip.base = -1;
	tc3589x_gpio->chip.of_node = np;

	girq = &tc3589x_gpio->chip.irq;
	girq->chip = &tc3589x_gpio_irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;
	girq->thपढ़ोed = true;

	/* Bring the GPIO module out of reset */
	ret = tc3589x_set_bits(tc3589x, TC3589x_RSTCTRL,
			       TC3589x_RSTCTRL_GPIRST, 0);
	अगर (ret < 0)
		वापस ret;

	 /* For tc35894, have to disable Direct KBD पूर्णांकerrupts,
	  * अन्यथा IRQST will always be 0x20, IRQN low level, can't
	  * clear the irq status.
	  * TODO: need more test on other tc3589x chip.
	  *
	  */
	ret = tc3589x_reg_ग_लिखो(tc3589x, TC3589x_DKBDMSK,
			TC3589x_DKBDMSK_ELINT | TC3589x_DKBDMSK_EINT);
	अगर (ret < 0)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev,
					irq, शून्य, tc3589x_gpio_irq,
					IRQF_ONESHOT, "tc3589x-gpio",
					tc3589x_gpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to get irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &tc3589x_gpio->chip,
				     tc3589x_gpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add gpiochip: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tc3589x_gpio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tc3589x_gpio_driver = अणु
	.driver.name	= "tc3589x-gpio",
	.probe		= tc3589x_gpio_probe,
पूर्ण;

अटल पूर्णांक __init tc3589x_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tc3589x_gpio_driver);
पूर्ण
subsys_initcall(tc3589x_gpio_init);
