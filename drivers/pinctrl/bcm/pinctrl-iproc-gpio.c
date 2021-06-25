<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2017 Broadcom
 */

/*
 * This file contains the Broadcom Iproc GPIO driver that supports 3
 * GPIO controllers on Iproc including the ASIU GPIO controller, the
 * chipCommonG GPIO controller, and the always-on GPIO controller. Basic
 * PINCONF such as bias pull up/करोwn, and drive strength are also supported
 * in this driver.
 *
 * It provides the functionality where pins from the GPIO can be
 * inभागidually muxed to GPIO function, अगर inभागidual pad
 * configuration is supported, through the पूर्णांकeraction with respective
 * SoCs IOMUX controller.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "../pinctrl-utils.h"

#घोषणा IPROC_GPIO_DATA_IN_OFFSET   0x00
#घोषणा IPROC_GPIO_DATA_OUT_OFFSET  0x04
#घोषणा IPROC_GPIO_OUT_EN_OFFSET    0x08
#घोषणा IPROC_GPIO_INT_TYPE_OFFSET  0x0c
#घोषणा IPROC_GPIO_INT_DE_OFFSET    0x10
#घोषणा IPROC_GPIO_INT_EDGE_OFFSET  0x14
#घोषणा IPROC_GPIO_INT_MSK_OFFSET   0x18
#घोषणा IPROC_GPIO_INT_STAT_OFFSET  0x1c
#घोषणा IPROC_GPIO_INT_MSTAT_OFFSET 0x20
#घोषणा IPROC_GPIO_INT_CLR_OFFSET   0x24
#घोषणा IPROC_GPIO_PAD_RES_OFFSET   0x34
#घोषणा IPROC_GPIO_RES_EN_OFFSET    0x38

/* drive strength control क्रम ASIU GPIO */
#घोषणा IPROC_GPIO_ASIU_DRV0_CTRL_OFFSET 0x58

/* pinconf क्रम CCM GPIO */
#घोषणा IPROC_GPIO_PULL_DN_OFFSET   0x10
#घोषणा IPROC_GPIO_PULL_UP_OFFSET   0x14

/* pinconf क्रम CRMU(aon) GPIO and CCM GPIO*/
#घोषणा IPROC_GPIO_DRV_CTRL_OFFSET  0x00

#घोषणा GPIO_BANK_SIZE 0x200
#घोषणा NGPIOS_PER_BANK 32
#घोषणा GPIO_BANK(pin) ((pin) / NGPIOS_PER_BANK)

#घोषणा IPROC_GPIO_REG(pin, reg) (GPIO_BANK(pin) * GPIO_BANK_SIZE + (reg))
#घोषणा IPROC_GPIO_SHIFT(pin) ((pin) % NGPIOS_PER_BANK)

#घोषणा GPIO_DRV_STRENGTH_BIT_SHIFT  20
#घोषणा GPIO_DRV_STRENGTH_BITS       3
#घोषणा GPIO_DRV_STRENGTH_BIT_MASK   ((1 << GPIO_DRV_STRENGTH_BITS) - 1)

क्रमागत iproc_pinconf_param अणु
	IPROC_PINCONF_DRIVE_STRENGTH = 0,
	IPROC_PINCONF_BIAS_DISABLE,
	IPROC_PINCONF_BIAS_PULL_UP,
	IPROC_PINCONF_BIAS_PULL_DOWN,
	IPROC_PINCON_MAX,
पूर्ण;

क्रमागत iproc_pinconf_ctrl_type अणु
	IOCTRL_TYPE_AON = 1,
	IOCTRL_TYPE_CDRU,
	IOCTRL_TYPE_INVALID,
पूर्ण;

/*
 * Iproc GPIO core
 *
 * @dev: poपूर्णांकer to device
 * @base: I/O रेजिस्टर base क्रम Iproc GPIO controller
 * @io_ctrl: I/O रेजिस्टर base क्रम certain type of Iproc GPIO controller that
 * has the PINCONF support implemented outside of the GPIO block
 * @lock: lock to protect access to I/O रेजिस्टरs
 * @gc: GPIO chip
 * @num_banks: number of GPIO banks, each bank supports up to 32 GPIOs
 * @pinmux_is_supported: flag to indicate this GPIO controller contains pins
 * that can be inभागidually muxed to GPIO
 * @pinconf_disable: contains a list of PINCONF parameters that need to be
 * disabled
 * @nr_pinconf_disable: total number of PINCONF parameters that need to be
 * disabled
 * @pctl: poपूर्णांकer to pinctrl_dev
 * @pctldesc: pinctrl descriptor
 */
काष्ठा iproc_gpio अणु
	काष्ठा device *dev;

	व्योम __iomem *base;
	व्योम __iomem *io_ctrl;
	क्रमागत iproc_pinconf_ctrl_type io_ctrl_type;

	raw_spinlock_t lock;

	काष्ठा irq_chip irqchip;
	काष्ठा gpio_chip gc;
	अचिन्हित num_banks;

	bool pinmux_is_supported;

	क्रमागत pin_config_param *pinconf_disable;
	अचिन्हित पूर्णांक nr_pinconf_disable;

	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_desc pctldesc;
पूर्ण;

/*
 * Mapping from PINCONF pins to GPIO pins is 1-to-1
 */
अटल अंतरभूत अचिन्हित iproc_pin_to_gpio(अचिन्हित pin)
अणु
	वापस pin;
पूर्ण

/**
 *  iproc_set_bit - set or clear one bit (corresponding to the GPIO pin) in a
 *  Iproc GPIO रेजिस्टर
 *
 *  @chip: Iproc GPIO device
 *  @reg: रेजिस्टर offset
 *  @gpio: GPIO pin
 *  @set: set or clear
 */
अटल अंतरभूत व्योम iproc_set_bit(काष्ठा iproc_gpio *chip, अचिन्हित पूर्णांक reg,
				  अचिन्हित gpio, bool set)
अणु
	अचिन्हित पूर्णांक offset = IPROC_GPIO_REG(gpio, reg);
	अचिन्हित पूर्णांक shअगरt = IPROC_GPIO_SHIFT(gpio);
	u32 val;

	val = पढ़ोl(chip->base + offset);
	अगर (set)
		val |= BIT(shअगरt);
	अन्यथा
		val &= ~BIT(shअगरt);
	ग_लिखोl(val, chip->base + offset);
पूर्ण

अटल अंतरभूत bool iproc_get_bit(काष्ठा iproc_gpio *chip, अचिन्हित पूर्णांक reg,
				  अचिन्हित gpio)
अणु
	अचिन्हित पूर्णांक offset = IPROC_GPIO_REG(gpio, reg);
	अचिन्हित पूर्णांक shअगरt = IPROC_GPIO_SHIFT(gpio);

	वापस !!(पढ़ोl(chip->base + offset) & BIT(shअगरt));
पूर्ण

अटल व्योम iproc_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	काष्ठा irq_chip *irq_chip = irq_desc_get_chip(desc);
	पूर्णांक i, bit;

	chained_irq_enter(irq_chip, desc);

	/* go through the entire GPIO banks and handle all पूर्णांकerrupts */
	क्रम (i = 0; i < chip->num_banks; i++) अणु
		अचिन्हित दीर्घ val = पढ़ोl(chip->base + (i * GPIO_BANK_SIZE) +
					  IPROC_GPIO_INT_MSTAT_OFFSET);

		क्रम_each_set_bit(bit, &val, NGPIOS_PER_BANK) अणु
			अचिन्हित pin = NGPIOS_PER_BANK * i + bit;
			पूर्णांक child_irq = irq_find_mapping(gc->irq.करोमुख्य, pin);

			/*
			 * Clear the पूर्णांकerrupt beक्रमe invoking the
			 * handler, so we करो not leave any winकरोw
			 */
			ग_लिखोl(BIT(bit), chip->base + (i * GPIO_BANK_SIZE) +
			       IPROC_GPIO_INT_CLR_OFFSET);

			generic_handle_irq(child_irq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(irq_chip, desc);
पूर्ण


अटल व्योम iproc_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;
	अचिन्हित पूर्णांक offset = IPROC_GPIO_REG(gpio,
			IPROC_GPIO_INT_CLR_OFFSET);
	अचिन्हित पूर्णांक shअगरt = IPROC_GPIO_SHIFT(gpio);
	u32 val = BIT(shअगरt);

	ग_लिखोl(val, chip->base + offset);
पूर्ण

/**
 *  iproc_gpio_irq_set_mask - mask/unmask a GPIO पूर्णांकerrupt
 *
 *  @d: IRQ chip data
 *  @unmask: mask/unmask GPIO पूर्णांकerrupt
 */
अटल व्योम iproc_gpio_irq_set_mask(काष्ठा irq_data *d, bool unmask)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;

	iproc_set_bit(chip, IPROC_GPIO_INT_MSK_OFFSET, gpio, unmask);
पूर्ण

अटल व्योम iproc_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_gpio_irq_set_mask(d, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम iproc_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_gpio_irq_set_mask(d, true);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक iproc_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;
	bool level_triggered = false;
	bool dual_edge = false;
	bool rising_or_high = false;
	अचिन्हित दीर्घ flags;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		rising_or_high = true;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		dual_edge = true;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		level_triggered = true;
		rising_or_high = true;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		level_triggered = true;
		अवरोध;

	शेष:
		dev_err(chip->dev, "invalid GPIO IRQ type 0x%x\n",
			type);
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_INT_TYPE_OFFSET, gpio,
		       level_triggered);
	iproc_set_bit(chip, IPROC_GPIO_INT_DE_OFFSET, gpio, dual_edge);
	iproc_set_bit(chip, IPROC_GPIO_INT_EDGE_OFFSET, gpio,
		       rising_or_high);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev,
		"gpio:%u level_triggered:%d dual_edge:%d rising_or_high:%d\n",
		gpio, level_triggered, dual_edge, rising_or_high);

	वापस 0;
पूर्ण

/*
 * Request the Iproc IOMUX pinmux controller to mux inभागidual pins to GPIO
 */
अटल पूर्णांक iproc_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = gc->base + offset;

	/* not all Iproc GPIO pins can be muxed inभागidually */
	अगर (!chip->pinmux_is_supported)
		वापस 0;

	वापस pinctrl_gpio_request(gpio);
पूर्ण

अटल व्योम iproc_gpio_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = gc->base + offset;

	अगर (!chip->pinmux_is_supported)
		वापस;

	pinctrl_gpio_मुक्त(gpio);
पूर्ण

अटल पूर्णांक iproc_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_OUT_EN_OFFSET, gpio, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set input\n", gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित gpio,
					पूर्णांक val)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_OUT_EN_OFFSET, gpio, true);
	iproc_set_bit(chip, IPROC_GPIO_DATA_OUT_OFFSET, gpio, !!(val));
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set output, value:%d\n", gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = IPROC_GPIO_REG(gpio, IPROC_GPIO_OUT_EN_OFFSET);
	अचिन्हित पूर्णांक shअगरt = IPROC_GPIO_SHIFT(gpio);

	अगर (पढ़ोl(chip->base + offset) & BIT(shअगरt))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल व्योम iproc_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक val)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_set_bit(chip, IPROC_GPIO_DATA_OUT_OFFSET, gpio, !!(val));
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set, value:%d\n", gpio, val);
पूर्ण

अटल पूर्णांक iproc_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा iproc_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = IPROC_GPIO_REG(gpio,
					      IPROC_GPIO_DATA_IN_OFFSET);
	अचिन्हित पूर्णांक shअगरt = IPROC_GPIO_SHIFT(gpio);

	वापस !!(पढ़ोl(chip->base + offset) & BIT(shअगरt));
पूर्ण

/*
 * Mapping of the iProc PINCONF parameters to the generic pin configuration
 * parameters
 */
अटल स्थिर क्रमागत pin_config_param iproc_pinconf_disable_map[] = अणु
	[IPROC_PINCONF_DRIVE_STRENGTH] = PIN_CONFIG_DRIVE_STRENGTH,
	[IPROC_PINCONF_BIAS_DISABLE] = PIN_CONFIG_BIAS_DISABLE,
	[IPROC_PINCONF_BIAS_PULL_UP] = PIN_CONFIG_BIAS_PULL_UP,
	[IPROC_PINCONF_BIAS_PULL_DOWN] = PIN_CONFIG_BIAS_PULL_DOWN,
पूर्ण;

अटल bool iproc_pinconf_param_is_disabled(काष्ठा iproc_gpio *chip,
					    क्रमागत pin_config_param param)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!chip->nr_pinconf_disable)
		वापस false;

	क्रम (i = 0; i < chip->nr_pinconf_disable; i++)
		अगर (chip->pinconf_disable[i] == param)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक iproc_pinconf_disable_map_create(काष्ठा iproc_gpio *chip,
					    अचिन्हित दीर्घ disable_mask)
अणु
	अचिन्हित पूर्णांक map_size = ARRAY_SIZE(iproc_pinconf_disable_map);
	अचिन्हित पूर्णांक bit, nbits = 0;

	/* figure out total number of PINCONF parameters to disable */
	क्रम_each_set_bit(bit, &disable_mask, map_size)
		nbits++;

	अगर (!nbits)
		वापस 0;

	/*
	 * Allocate an array to store PINCONF parameters that need to be
	 * disabled
	 */
	chip->pinconf_disable = devm_kसुस्मृति(chip->dev, nbits,
					     माप(*chip->pinconf_disable),
					     GFP_KERNEL);
	अगर (!chip->pinconf_disable)
		वापस -ENOMEM;

	chip->nr_pinconf_disable = nbits;

	/* now store these parameters */
	nbits = 0;
	क्रम_each_set_bit(bit, &disable_mask, map_size)
		chip->pinconf_disable[nbits++] = iproc_pinconf_disable_map[bit];

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 1;
पूर्ण

/*
 * Only one group: "gpio_grp", since this local pinctrl device only perक्रमms
 * GPIO specअगरic PINCONF configurations
 */
अटल स्थिर अक्षर *iproc_get_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित selector)
अणु
	वापस "gpio_grp";
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops iproc_pctrl_ops = अणु
	.get_groups_count = iproc_get_groups_count,
	.get_group_name = iproc_get_group_name,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक iproc_gpio_set_pull(काष्ठा iproc_gpio *chip, अचिन्हित gpio,
				bool disable, bool pull_up)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक shअगरt;
	u32 val_1, val_2;

	raw_spin_lock_irqsave(&chip->lock, flags);
	अगर (chip->io_ctrl_type == IOCTRL_TYPE_CDRU) अणु
		base = chip->io_ctrl;
		shअगरt = IPROC_GPIO_SHIFT(gpio);

		val_1 = पढ़ोl(base + IPROC_GPIO_PULL_UP_OFFSET);
		val_2 = पढ़ोl(base + IPROC_GPIO_PULL_DN_OFFSET);
		अगर (disable) अणु
			/* no pull-up or pull-करोwn */
			val_1 &= ~BIT(shअगरt);
			val_2 &= ~BIT(shअगरt);
		पूर्ण अन्यथा अगर (pull_up) अणु
			val_1 |= BIT(shअगरt);
			val_2 &= ~BIT(shअगरt);
		पूर्ण अन्यथा अणु
			val_1 &= ~BIT(shअगरt);
			val_2 |= BIT(shअगरt);
		पूर्ण
		ग_लिखोl(val_1, base + IPROC_GPIO_PULL_UP_OFFSET);
		ग_लिखोl(val_2, base + IPROC_GPIO_PULL_DN_OFFSET);
	पूर्ण अन्यथा अणु
		अगर (disable) अणु
			iproc_set_bit(chip, IPROC_GPIO_RES_EN_OFFSET, gpio,
				      false);
		पूर्ण अन्यथा अणु
			iproc_set_bit(chip, IPROC_GPIO_PAD_RES_OFFSET, gpio,
				      pull_up);
			iproc_set_bit(chip, IPROC_GPIO_RES_EN_OFFSET, gpio,
				      true);
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&chip->lock, flags);
	dev_dbg(chip->dev, "gpio:%u set pullup:%d\n", gpio, pull_up);

	वापस 0;
पूर्ण

अटल व्योम iproc_gpio_get_pull(काष्ठा iproc_gpio *chip, अचिन्हित gpio,
				 bool *disable, bool *pull_up)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक shअगरt;
	u32 val_1, val_2;

	raw_spin_lock_irqsave(&chip->lock, flags);
	अगर (chip->io_ctrl_type == IOCTRL_TYPE_CDRU) अणु
		base = chip->io_ctrl;
		shअगरt = IPROC_GPIO_SHIFT(gpio);

		val_1 = पढ़ोl(base + IPROC_GPIO_PULL_UP_OFFSET) & BIT(shअगरt);
		val_2 = पढ़ोl(base + IPROC_GPIO_PULL_DN_OFFSET) & BIT(shअगरt);

		*pull_up = val_1 ? true : false;
		*disable = (val_1 | val_2) ? false : true;

	पूर्ण अन्यथा अणु
		*disable = !iproc_get_bit(chip, IPROC_GPIO_RES_EN_OFFSET, gpio);
		*pull_up = iproc_get_bit(chip, IPROC_GPIO_PAD_RES_OFFSET, gpio);
	पूर्ण
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

#घोषणा DRV_STRENGTH_OFFSET(gpio, bit, type)  ((type) == IOCTRL_TYPE_AON ? \
	((2 - (bit)) * 4 + IPROC_GPIO_DRV_CTRL_OFFSET) : \
	((type) == IOCTRL_TYPE_CDRU) ? \
	((bit) * 4 + IPROC_GPIO_DRV_CTRL_OFFSET) : \
	((bit) * 4 + IPROC_GPIO_REG(gpio, IPROC_GPIO_ASIU_DRV0_CTRL_OFFSET)))

अटल पूर्णांक iproc_gpio_set_strength(काष्ठा iproc_gpio *chip, अचिन्हित gpio,
				    अचिन्हित strength)
अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक i, offset, shअगरt;
	u32 val;
	अचिन्हित दीर्घ flags;

	/* make sure drive strength is supported */
	अगर (strength < 2 ||  strength > 16 || (strength % 2))
		वापस -ENOTSUPP;

	अगर (chip->io_ctrl) अणु
		base = chip->io_ctrl;
	पूर्ण अन्यथा अणु
		base = chip->base;
	पूर्ण

	shअगरt = IPROC_GPIO_SHIFT(gpio);

	dev_dbg(chip->dev, "gpio:%u set drive strength:%d mA\n", gpio,
		strength);

	raw_spin_lock_irqsave(&chip->lock, flags);
	strength = (strength / 2) - 1;
	क्रम (i = 0; i < GPIO_DRV_STRENGTH_BITS; i++) अणु
		offset = DRV_STRENGTH_OFFSET(gpio, i, chip->io_ctrl_type);
		val = पढ़ोl(base + offset);
		val &= ~BIT(shअगरt);
		val |= ((strength >> i) & 0x1) << shअगरt;
		ग_लिखोl(val, base + offset);
	पूर्ण
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_gpio_get_strength(काष्ठा iproc_gpio *chip, अचिन्हित gpio,
				    u16 *strength)
अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक i, offset, shअगरt;
	u32 val;
	अचिन्हित दीर्घ flags;

	अगर (chip->io_ctrl) अणु
		base = chip->io_ctrl;
	पूर्ण अन्यथा अणु
		base = chip->base;
	पूर्ण

	shअगरt = IPROC_GPIO_SHIFT(gpio);

	raw_spin_lock_irqsave(&chip->lock, flags);
	*strength = 0;
	क्रम (i = 0; i < GPIO_DRV_STRENGTH_BITS; i++) अणु
		offset = DRV_STRENGTH_OFFSET(gpio, i, chip->io_ctrl_type);
		val = पढ़ोl(base + offset) & BIT(shअगरt);
		val >>= shअगरt;
		*strength += (val << i);
	पूर्ण

	/* convert to mA */
	*strength = (*strength + 1) * 2;
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा iproc_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित gpio = iproc_pin_to_gpio(pin);
	u16 arg;
	bool disable, pull_up;
	पूर्णांक ret;

	अगर (iproc_pinconf_param_is_disabled(chip, param))
		वापस -ENOTSUPP;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		अगर (disable)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		अगर (!disable && pull_up)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		iproc_gpio_get_pull(chip, gpio, &disable, &pull_up);
		अगर (!disable && !pull_up)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		ret = iproc_gpio_get_strength(chip, gpio, &arg);
		अगर (ret)
			वापस ret;
		*config = pinconf_to_config_packed(param, arg);

		वापस 0;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक iproc_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				 अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा iproc_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 arg;
	अचिन्हित i, gpio = iproc_pin_to_gpio(pin);
	पूर्णांक ret = -ENOTSUPP;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		अगर (iproc_pinconf_param_is_disabled(chip, param))
			वापस -ENOTSUPP;

		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = iproc_gpio_set_pull(chip, gpio, true, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = iproc_gpio_set_pull(chip, gpio, false, true);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = iproc_gpio_set_pull(chip, gpio, false, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			ret = iproc_gpio_set_strength(chip, gpio, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		शेष:
			dev_err(chip->dev, "invalid configuration\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण /* क्रम each config */

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops iproc_pconf_ops = अणु
	.is_generic = true,
	.pin_config_get = iproc_pin_config_get,
	.pin_config_set = iproc_pin_config_set,
पूर्ण;

/*
 * Iproc GPIO controller supports some PINCONF related configurations such as
 * pull up, pull करोwn, and drive strength, when the pin is configured to GPIO
 *
 * Here a local pinctrl device is created with simple 1-to-1 pin mapping to the
 * local GPIO pins
 */
अटल पूर्णांक iproc_gpio_रेजिस्टर_pinconf(काष्ठा iproc_gpio *chip)
अणु
	काष्ठा pinctrl_desc *pctldesc = &chip->pctldesc;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा gpio_chip *gc = &chip->gc;
	पूर्णांक i;

	pins = devm_kसुस्मृति(chip->dev, gc->ngpio, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < gc->ngpio; i++) अणु
		pins[i].number = i;
		pins[i].name = devm_kaप्र_लिखो(chip->dev, GFP_KERNEL,
					      "gpio-%d", i);
		अगर (!pins[i].name)
			वापस -ENOMEM;
	पूर्ण

	pctldesc->name = dev_name(chip->dev);
	pctldesc->pctlops = &iproc_pctrl_ops;
	pctldesc->pins = pins;
	pctldesc->npins = gc->ngpio;
	pctldesc->confops = &iproc_pconf_ops;

	chip->pctl = devm_pinctrl_रेजिस्टर(chip->dev, pctldesc, chip);
	अगर (IS_ERR(chip->pctl)) अणु
		dev_err(chip->dev, "unable to register pinctrl device\n");
		वापस PTR_ERR(chip->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id iproc_gpio_of_match[] = अणु
	अणु .compatible = "brcm,iproc-gpio" पूर्ण,
	अणु .compatible = "brcm,cygnus-ccm-gpio" पूर्ण,
	अणु .compatible = "brcm,cygnus-asiu-gpio" पूर्ण,
	अणु .compatible = "brcm,cygnus-crmu-gpio" पूर्ण,
	अणु .compatible = "brcm,iproc-nsp-gpio" पूर्ण,
	अणु .compatible = "brcm,iproc-stingray-gpio" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक iproc_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा iproc_gpio *chip;
	काष्ठा gpio_chip *gc;
	u32 ngpios, pinconf_disable_mask = 0;
	पूर्णांक irq, ret;
	bool no_pinconf = false;
	क्रमागत iproc_pinconf_ctrl_type io_ctrl_type = IOCTRL_TYPE_INVALID;

	/* NSP करोes not support drive strength config */
	अगर (of_device_is_compatible(dev->of_node, "brcm,iproc-nsp-gpio"))
		pinconf_disable_mask = BIT(IPROC_PINCONF_DRIVE_STRENGTH);
	/* Stingray करोes not support pinconf in this controller */
	अन्यथा अगर (of_device_is_compatible(dev->of_node,
					 "brcm,iproc-stingray-gpio"))
		no_pinconf = true;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = dev;
	platक्रमm_set_drvdata(pdev, chip);

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base)) अणु
		dev_err(dev, "unable to map I/O memory\n");
		वापस PTR_ERR(chip->base);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		chip->io_ctrl = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(chip->io_ctrl)) अणु
			dev_err(dev, "unable to map I/O memory\n");
			वापस PTR_ERR(chip->io_ctrl);
		पूर्ण
		अगर (of_device_is_compatible(dev->of_node,
					    "brcm,cygnus-ccm-gpio"))
			io_ctrl_type = IOCTRL_TYPE_CDRU;
		अन्यथा
			io_ctrl_type = IOCTRL_TYPE_AON;
	पूर्ण

	chip->io_ctrl_type = io_ctrl_type;

	अगर (of_property_पढ़ो_u32(dev->of_node, "ngpios", &ngpios)) अणु
		dev_err(&pdev->dev, "missing ngpios DT property\n");
		वापस -ENODEV;
	पूर्ण

	raw_spin_lock_init(&chip->lock);

	gc = &chip->gc;
	gc->base = -1;
	gc->ngpio = ngpios;
	chip->num_banks = (ngpios + NGPIOS_PER_BANK - 1) / NGPIOS_PER_BANK;
	gc->label = dev_name(dev);
	gc->parent = dev;
	gc->of_node = dev->of_node;
	gc->request = iproc_gpio_request;
	gc->मुक्त = iproc_gpio_मुक्त;
	gc->direction_input = iproc_gpio_direction_input;
	gc->direction_output = iproc_gpio_direction_output;
	gc->get_direction = iproc_gpio_get_direction;
	gc->set = iproc_gpio_set;
	gc->get = iproc_gpio_get;

	chip->pinmux_is_supported = of_property_पढ़ो_bool(dev->of_node,
							"gpio-ranges");

	/* optional GPIO पूर्णांकerrupt support */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा irq_chip *irqc;
		काष्ठा gpio_irq_chip *girq;

		irqc = &chip->irqchip;
		irqc->name = dev_name(dev);
		irqc->irq_ack = iproc_gpio_irq_ack;
		irqc->irq_mask = iproc_gpio_irq_mask;
		irqc->irq_unmask = iproc_gpio_irq_unmask;
		irqc->irq_set_type = iproc_gpio_irq_set_type;
		irqc->irq_enable = iproc_gpio_irq_unmask;
		irqc->irq_disable = iproc_gpio_irq_mask;

		girq = &gc->irq;
		girq->chip = irqc;
		girq->parent_handler = iproc_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
	पूर्ण

	ret = gpiochip_add_data(gc, chip);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to add GPIO chip\n");
		वापस ret;
	पूर्ण

	अगर (!no_pinconf) अणु
		ret = iproc_gpio_रेजिस्टर_pinconf(chip);
		अगर (ret) अणु
			dev_err(dev, "unable to register pinconf\n");
			जाओ err_rm_gpiochip;
		पूर्ण

		अगर (pinconf_disable_mask) अणु
			ret = iproc_pinconf_disable_map_create(chip,
							 pinconf_disable_mask);
			अगर (ret) अणु
				dev_err(dev,
					"unable to create pinconf disable map\n");
				जाओ err_rm_gpiochip;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_rm_gpiochip:
	gpiochip_हटाओ(gc);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver iproc_gpio_driver = अणु
	.driver = अणु
		.name = "iproc-gpio",
		.of_match_table = iproc_gpio_of_match,
	पूर्ण,
	.probe = iproc_gpio_probe,
पूर्ण;

अटल पूर्णांक __init iproc_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&iproc_gpio_driver);
पूर्ण
arch_initcall_sync(iproc_gpio_init);
