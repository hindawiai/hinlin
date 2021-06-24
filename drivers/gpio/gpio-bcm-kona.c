<शैली गुरु>
/*
 * Broadcom Kona GPIO Driver
 *
 * Author: Broadcom Corporation <bcm-kernel-feedback-list@broadcom.com>
 * Copyright (C) 2012-2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of_device.h>
#समावेश <linux/init.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>

#घोषणा BCM_GPIO_PASSWD				0x00a5a501
#घोषणा GPIO_PER_BANK				32
#घोषणा GPIO_MAX_BANK_NUM			8

#घोषणा GPIO_BANK(gpio)				((gpio) >> 5)
#घोषणा GPIO_BIT(gpio)				((gpio) & (GPIO_PER_BANK - 1))

/* There is a GPIO control रेजिस्टर क्रम each GPIO */
#घोषणा GPIO_CONTROL(gpio)			(0x00000100 + ((gpio) << 2))

/* The reमुख्यing रेजिस्टरs are per GPIO bank */
#घोषणा GPIO_OUT_STATUS(bank)			(0x00000000 + ((bank) << 2))
#घोषणा GPIO_IN_STATUS(bank)			(0x00000020 + ((bank) << 2))
#घोषणा GPIO_OUT_SET(bank)			(0x00000040 + ((bank) << 2))
#घोषणा GPIO_OUT_CLEAR(bank)			(0x00000060 + ((bank) << 2))
#घोषणा GPIO_INT_STATUS(bank)			(0x00000080 + ((bank) << 2))
#घोषणा GPIO_INT_MASK(bank)			(0x000000a0 + ((bank) << 2))
#घोषणा GPIO_INT_MSKCLR(bank)			(0x000000c0 + ((bank) << 2))
#घोषणा GPIO_PWD_STATUS(bank)			(0x00000500 + ((bank) << 2))

#घोषणा GPIO_GPPWR_OFFSET			0x00000520

#घोषणा GPIO_GPCTR0_DBR_SHIFT			5
#घोषणा GPIO_GPCTR0_DBR_MASK			0x000001e0

#घोषणा GPIO_GPCTR0_ITR_SHIFT			3
#घोषणा GPIO_GPCTR0_ITR_MASK			0x00000018
#घोषणा GPIO_GPCTR0_ITR_CMD_RISING_EDGE		0x00000001
#घोषणा GPIO_GPCTR0_ITR_CMD_FALLING_EDGE	0x00000002
#घोषणा GPIO_GPCTR0_ITR_CMD_BOTH_EDGE		0x00000003

#घोषणा GPIO_GPCTR0_IOTR_MASK			0x00000001
#घोषणा GPIO_GPCTR0_IOTR_CMD_0UTPUT		0x00000000
#घोषणा GPIO_GPCTR0_IOTR_CMD_INPUT		0x00000001

#घोषणा GPIO_GPCTR0_DB_ENABLE_MASK		0x00000100

#घोषणा LOCK_CODE				0xffffffff
#घोषणा UNLOCK_CODE				0x00000000

काष्ठा bcm_kona_gpio अणु
	व्योम __iomem *reg_base;
	पूर्णांक num_bank;
	raw_spinlock_t lock;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा bcm_kona_gpio_bank *banks;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

काष्ठा bcm_kona_gpio_bank अणु
	पूर्णांक id;
	पूर्णांक irq;
	/* Used in the पूर्णांकerrupt handler */
	काष्ठा bcm_kona_gpio *kona_gpio;
पूर्ण;

अटल अंतरभूत व्योम bcm_kona_gpio_ग_लिखो_lock_regs(व्योम __iomem *reg_base,
						पूर्णांक bank_id, u32 lockcode)
अणु
	ग_लिखोl(BCM_GPIO_PASSWD, reg_base + GPIO_GPPWR_OFFSET);
	ग_लिखोl(lockcode, reg_base + GPIO_PWD_STATUS(bank_id));
पूर्ण

अटल व्योम bcm_kona_gpio_lock_gpio(काष्ठा bcm_kona_gpio *kona_gpio,
					अचिन्हित gpio)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक bank_id = GPIO_BANK(gpio);

	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(kona_gpio->reg_base + GPIO_PWD_STATUS(bank_id));
	val |= BIT(gpio);
	bcm_kona_gpio_ग_लिखो_lock_regs(kona_gpio->reg_base, bank_id, val);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल व्योम bcm_kona_gpio_unlock_gpio(काष्ठा bcm_kona_gpio *kona_gpio,
					अचिन्हित gpio)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक bank_id = GPIO_BANK(gpio);

	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(kona_gpio->reg_base + GPIO_PWD_STATUS(bank_id));
	val &= ~BIT(gpio);
	bcm_kona_gpio_ग_लिखो_lock_regs(kona_gpio->reg_base, bank_id, val);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_get_dir(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);
	व्योम __iomem *reg_base = kona_gpio->reg_base;
	u32 val;

	val = पढ़ोl(reg_base + GPIO_CONTROL(gpio)) & GPIO_GPCTR0_IOTR_MASK;
	वापस val ? GPIO_LINE_सूचीECTION_IN : GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल व्योम bcm_kona_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val, reg_offset;
	अचिन्हित दीर्घ flags;

	kona_gpio = gpiochip_get_data(chip);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	/* this function only applies to output pin */
	अगर (bcm_kona_gpio_get_dir(chip, gpio) == GPIO_LINE_सूचीECTION_IN)
		जाओ out;

	reg_offset = value ? GPIO_OUT_SET(bank_id) : GPIO_OUT_CLEAR(bank_id);

	val = पढ़ोl(reg_base + reg_offset);
	val |= BIT(bit);
	ग_लिखोl(val, reg_base + reg_offset);

out:
	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val, reg_offset;
	अचिन्हित दीर्घ flags;

	kona_gpio = gpiochip_get_data(chip);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	अगर (bcm_kona_gpio_get_dir(chip, gpio) == GPIO_LINE_सूचीECTION_IN)
		reg_offset = GPIO_IN_STATUS(bank_id);
	अन्यथा
		reg_offset = GPIO_OUT_STATUS(bank_id);

	/* पढ़ो the GPIO bank status */
	val = पढ़ोl(reg_base + reg_offset);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);

	/* वापस the specअगरied bit status */
	वापस !!(val & BIT(bit));
पूर्ण

अटल पूर्णांक bcm_kona_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);

	bcm_kona_gpio_unlock_gpio(kona_gpio, gpio);
	वापस 0;
पूर्ण

अटल व्योम bcm_kona_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);

	bcm_kona_gpio_lock_gpio(kona_gpio, gpio);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	u32 val;
	अचिन्हित दीर्घ flags;

	kona_gpio = gpiochip_get_data(chip);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_CONTROL(gpio));
	val &= ~GPIO_GPCTR0_IOTR_MASK;
	val |= GPIO_GPCTR0_IOTR_CMD_INPUT;
	ग_लिखोl(val, reg_base + GPIO_CONTROL(gpio));

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_gpio_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val, reg_offset;
	अचिन्हित दीर्घ flags;

	kona_gpio = gpiochip_get_data(chip);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_CONTROL(gpio));
	val &= ~GPIO_GPCTR0_IOTR_MASK;
	val |= GPIO_GPCTR0_IOTR_CMD_0UTPUT;
	ग_लिखोl(val, reg_base + GPIO_CONTROL(gpio));
	reg_offset = value ? GPIO_OUT_SET(bank_id) : GPIO_OUT_CLEAR(bank_id);

	val = पढ़ोl(reg_base + reg_offset);
	val |= BIT(bit);
	ग_लिखोl(val, reg_base + reg_offset);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;

	kona_gpio = gpiochip_get_data(chip);
	अगर (gpio >= kona_gpio->gpio_chip.ngpio)
		वापस -ENXIO;
	वापस irq_create_mapping(kona_gpio->irq_करोमुख्य, gpio);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_set_debounce(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				      अचिन्हित debounce)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	u32 val, res;
	अचिन्हित दीर्घ flags;

	kona_gpio = gpiochip_get_data(chip);
	reg_base = kona_gpio->reg_base;
	/* debounce must be 1-128ms (or 0) */
	अगर ((debounce > 0 && debounce < 1000) || debounce > 128000) अणु
		dev_err(chip->parent, "Debounce value %u not in range\n",
			debounce);
		वापस -EINVAL;
	पूर्ण

	/* calculate debounce bit value */
	अगर (debounce != 0) अणु
		/* Convert to ms */
		debounce /= 1000;
		/* find the MSB */
		res = fls(debounce) - 1;
		/* Check अगर MSB-1 is set (round up or करोwn) */
		अगर (res > 0 && (debounce & BIT(res - 1)))
			res++;
	पूर्ण

	/* spin lock क्रम पढ़ो-modअगरy-ग_लिखो of the GPIO रेजिस्टर */
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_CONTROL(gpio));
	val &= ~GPIO_GPCTR0_DBR_MASK;

	अगर (debounce == 0) अणु
		/* disable debounce */
		val &= ~GPIO_GPCTR0_DB_ENABLE_MASK;
	पूर्ण अन्यथा अणु
		val |= GPIO_GPCTR0_DB_ENABLE_MASK |
		    (res << GPIO_GPCTR0_DBR_SHIFT);
	पूर्ण

	ग_लिखोl(val, reg_base + GPIO_CONTROL(gpio));

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				    अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	वापस bcm_kona_gpio_set_debounce(chip, gpio, debounce);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label = "bcm-kona-gpio",
	.owner = THIS_MODULE,
	.request = bcm_kona_gpio_request,
	.मुक्त = bcm_kona_gpio_मुक्त,
	.get_direction = bcm_kona_gpio_get_dir,
	.direction_input = bcm_kona_gpio_direction_input,
	.get = bcm_kona_gpio_get,
	.direction_output = bcm_kona_gpio_direction_output,
	.set = bcm_kona_gpio_set,
	.set_config = bcm_kona_gpio_set_config,
	.to_irq = bcm_kona_gpio_to_irq,
	.base = 0,
पूर्ण;

अटल व्योम bcm_kona_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	अचिन्हित gpio = d->hwirq;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val;
	अचिन्हित दीर्घ flags;

	kona_gpio = irq_data_get_irq_chip_data(d);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_INT_STATUS(bank_id));
	val |= BIT(bit);
	ग_लिखोl(val, reg_base + GPIO_INT_STATUS(bank_id));

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल व्योम bcm_kona_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	अचिन्हित gpio = d->hwirq;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val;
	अचिन्हित दीर्घ flags;

	kona_gpio = irq_data_get_irq_chip_data(d);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_INT_MASK(bank_id));
	val |= BIT(bit);
	ग_लिखोl(val, reg_base + GPIO_INT_MASK(bank_id));
	gpiochip_disable_irq(&kona_gpio->gpio_chip, gpio);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल व्योम bcm_kona_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	अचिन्हित gpio = d->hwirq;
	पूर्णांक bank_id = GPIO_BANK(gpio);
	पूर्णांक bit = GPIO_BIT(gpio);
	u32 val;
	अचिन्हित दीर्घ flags;

	kona_gpio = irq_data_get_irq_chip_data(d);
	reg_base = kona_gpio->reg_base;
	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_INT_MSKCLR(bank_id));
	val |= BIT(bit);
	ग_लिखोl(val, reg_base + GPIO_INT_MSKCLR(bank_id));
	gpiochip_enable_irq(&kona_gpio->gpio_chip, gpio);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio;
	व्योम __iomem *reg_base;
	अचिन्हित gpio = d->hwirq;
	u32 lvl_type;
	u32 val;
	अचिन्हित दीर्घ flags;

	kona_gpio = irq_data_get_irq_chip_data(d);
	reg_base = kona_gpio->reg_base;
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		lvl_type = GPIO_GPCTR0_ITR_CMD_RISING_EDGE;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		lvl_type = GPIO_GPCTR0_ITR_CMD_FALLING_EDGE;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		lvl_type = GPIO_GPCTR0_ITR_CMD_BOTH_EDGE;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_LEVEL_LOW:
		/* BCM GPIO करोesn't support level triggering */
	शेष:
		dev_err(kona_gpio->gpio_chip.parent,
			"Invalid BCM GPIO irq type 0x%x\n", type);
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = पढ़ोl(reg_base + GPIO_CONTROL(gpio));
	val &= ~GPIO_GPCTR0_ITR_MASK;
	val |= lvl_type << GPIO_GPCTR0_ITR_SHIFT;
	ग_लिखोl(val, reg_base + GPIO_CONTROL(gpio));

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम bcm_kona_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	व्योम __iomem *reg_base;
	पूर्णांक bit, bank_id;
	अचिन्हित दीर्घ sta;
	काष्ठा bcm_kona_gpio_bank *bank = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);

	/*
	 * For bank पूर्णांकerrupts, we can't use chip_data to store the kona_gpio
	 * poपूर्णांकer, since GIC needs it क्रम its own purposes. Thereक्रमe, we get
	 * our poपूर्णांकer from the bank काष्ठाure.
	 */
	reg_base = bank->kona_gpio->reg_base;
	bank_id = bank->id;

	जबतक ((sta = पढ़ोl(reg_base + GPIO_INT_STATUS(bank_id)) &
		    (~(पढ़ोl(reg_base + GPIO_INT_MASK(bank_id)))))) अणु
		क्रम_each_set_bit(bit, &sta, 32) अणु
			पूर्णांक hwirq = GPIO_PER_BANK * bank_id + bit;
			पूर्णांक child_irq =
				irq_find_mapping(bank->kona_gpio->irq_करोमुख्य,
						 hwirq);
			/*
			 * Clear पूर्णांकerrupt beक्रमe handler is called so we करोn't
			 * miss any पूर्णांकerrupt occurred during executing them.
			 */
			ग_लिखोl(पढ़ोl(reg_base + GPIO_INT_STATUS(bank_id)) |
			       BIT(bit), reg_base + GPIO_INT_STATUS(bank_id));
			/* Invoke पूर्णांकerrupt handler */
			generic_handle_irq(child_irq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक bcm_kona_gpio_irq_reqres(काष्ठा irq_data *d)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio = irq_data_get_irq_chip_data(d);

	वापस gpiochip_reqres_irq(&kona_gpio->gpio_chip, d->hwirq);
पूर्ण

अटल व्योम bcm_kona_gpio_irq_relres(काष्ठा irq_data *d)
अणु
	काष्ठा bcm_kona_gpio *kona_gpio = irq_data_get_irq_chip_data(d);

	gpiochip_relres_irq(&kona_gpio->gpio_chip, d->hwirq);
पूर्ण

अटल काष्ठा irq_chip bcm_gpio_irq_chip = अणु
	.name = "bcm-kona-gpio",
	.irq_ack = bcm_kona_gpio_irq_ack,
	.irq_mask = bcm_kona_gpio_irq_mask,
	.irq_unmask = bcm_kona_gpio_irq_unmask,
	.irq_set_type = bcm_kona_gpio_irq_set_type,
	.irq_request_resources = bcm_kona_gpio_irq_reqres,
	.irq_release_resources = bcm_kona_gpio_irq_relres,
पूर्ण;

अटल काष्ठा of_device_id स्थिर bcm_kona_gpio_of_match[] = अणु
	अणु .compatible = "brcm,kona-gpio" पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * This lock class tells lockdep that GPIO irqs are in a dअगरferent
 * category than their parents, so it won't report false recursion.
 */
अटल काष्ठा lock_class_key gpio_lock_class;
अटल काष्ठा lock_class_key gpio_request_class;

अटल पूर्णांक bcm_kona_gpio_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hwirq)
अणु
	पूर्णांक ret;

	ret = irq_set_chip_data(irq, d->host_data);
	अगर (ret < 0)
		वापस ret;
	irq_set_lockdep_class(irq, &gpio_lock_class, &gpio_request_class);
	irq_set_chip_and_handler(irq, &bcm_gpio_irq_chip, handle_simple_irq);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल व्योम bcm_kona_gpio_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops bcm_kona_irq_ops = अणु
	.map = bcm_kona_gpio_irq_map,
	.unmap = bcm_kona_gpio_irq_unmap,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम bcm_kona_gpio_reset(काष्ठा bcm_kona_gpio *kona_gpio)
अणु
	व्योम __iomem *reg_base;
	पूर्णांक i;

	reg_base = kona_gpio->reg_base;
	/* disable पूर्णांकerrupts and clear status */
	क्रम (i = 0; i < kona_gpio->num_bank; i++) अणु
		/* Unlock the entire bank first */
		bcm_kona_gpio_ग_लिखो_lock_regs(reg_base, i, UNLOCK_CODE);
		ग_लिखोl(0xffffffff, reg_base + GPIO_INT_MASK(i));
		ग_लिखोl(0xffffffff, reg_base + GPIO_INT_STATUS(i));
		/* Now re-lock the bank */
		bcm_kona_gpio_ग_लिखो_lock_regs(reg_base, i, LOCK_CODE);
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_kona_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा bcm_kona_gpio_bank *bank;
	काष्ठा bcm_kona_gpio *kona_gpio;
	काष्ठा gpio_chip *chip;
	पूर्णांक ret;
	पूर्णांक i;

	match = of_match_device(bcm_kona_gpio_of_match, dev);
	अगर (!match) अणु
		dev_err(dev, "Failed to find gpio controller\n");
		वापस -ENODEV;
	पूर्ण

	kona_gpio = devm_kzalloc(dev, माप(*kona_gpio), GFP_KERNEL);
	अगर (!kona_gpio)
		वापस -ENOMEM;

	kona_gpio->gpio_chip = ढाँचा_chip;
	chip = &kona_gpio->gpio_chip;
	ret = platक्रमm_irq_count(pdev);
	अगर (!ret) अणु
		dev_err(dev, "Couldn't determine # GPIO banks\n");
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		वापस dev_err_probe(dev, ret, "Couldn't determine GPIO banks\n");
	पूर्ण
	kona_gpio->num_bank = ret;

	अगर (kona_gpio->num_bank > GPIO_MAX_BANK_NUM) अणु
		dev_err(dev, "Too many GPIO banks configured (max=%d)\n",
			GPIO_MAX_BANK_NUM);
		वापस -ENXIO;
	पूर्ण
	kona_gpio->banks = devm_kसुस्मृति(dev,
					kona_gpio->num_bank,
					माप(*kona_gpio->banks),
					GFP_KERNEL);
	अगर (!kona_gpio->banks)
		वापस -ENOMEM;

	kona_gpio->pdev = pdev;
	platक्रमm_set_drvdata(pdev, kona_gpio);
	chip->of_node = dev->of_node;
	chip->ngpio = kona_gpio->num_bank * GPIO_PER_BANK;

	kona_gpio->irq_करोमुख्य = irq_करोमुख्य_add_linear(dev->of_node,
						      chip->ngpio,
						      &bcm_kona_irq_ops,
						      kona_gpio);
	अगर (!kona_gpio->irq_करोमुख्य) अणु
		dev_err(dev, "Couldn't allocate IRQ domain\n");
		वापस -ENXIO;
	पूर्ण

	kona_gpio->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(kona_gpio->reg_base)) अणु
		ret = PTR_ERR(kona_gpio->reg_base);
		जाओ err_irq_करोमुख्य;
	पूर्ण

	क्रम (i = 0; i < kona_gpio->num_bank; i++) अणु
		bank = &kona_gpio->banks[i];
		bank->id = i;
		bank->irq = platक्रमm_get_irq(pdev, i);
		bank->kona_gpio = kona_gpio;
		अगर (bank->irq < 0) अणु
			dev_err(dev, "Couldn't get IRQ for bank %d", i);
			ret = -ENOENT;
			जाओ err_irq_करोमुख्य;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "Setting up Kona GPIO\n");

	bcm_kona_gpio_reset(kona_gpio);

	ret = devm_gpiochip_add_data(dev, chip, kona_gpio);
	अगर (ret < 0) अणु
		dev_err(dev, "Couldn't add GPIO chip -- %d\n", ret);
		जाओ err_irq_करोमुख्य;
	पूर्ण
	क्रम (i = 0; i < kona_gpio->num_bank; i++) अणु
		bank = &kona_gpio->banks[i];
		irq_set_chained_handler_and_data(bank->irq,
						 bcm_kona_gpio_irq_handler,
						 bank);
	पूर्ण

	raw_spin_lock_init(&kona_gpio->lock);

	वापस 0;

err_irq_करोमुख्य:
	irq_करोमुख्य_हटाओ(kona_gpio->irq_करोमुख्य);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm_kona_gpio_driver = अणु
	.driver = अणु
			.name = "bcm-kona-gpio",
			.of_match_table = bcm_kona_gpio_of_match,
	पूर्ण,
	.probe = bcm_kona_gpio_probe,
पूर्ण;
builtin_platक्रमm_driver(bcm_kona_gpio_driver);
