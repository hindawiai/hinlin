<शैली गुरु>
/*
 * Copyright (C) 2014-2017 Broadcom
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

/*
 * This file contains the Broadcom Northstar Plus (NSP) GPIO driver that
 * supports the chipCommonA GPIO controller. Basic PINCONF such as bias,
 * pull up/करोwn, slew and drive strength are also supported in this driver.
 *
 * Pins from the chipCommonA  GPIO can be inभागidually muxed to GPIO function,
 * through the पूर्णांकeraction with the NSP IOMUX controller.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/slab.h>

#समावेश "../pinctrl-utils.h"

#घोषणा NSP_CHIP_A_INT_STATUS		0x00
#घोषणा NSP_CHIP_A_INT_MASK		0x04
#घोषणा NSP_GPIO_DATA_IN		0x40
#घोषणा NSP_GPIO_DATA_OUT		0x44
#घोषणा NSP_GPIO_OUT_EN			0x48
#घोषणा NSP_GPIO_INT_POLARITY		0x50
#घोषणा NSP_GPIO_INT_MASK		0x54
#घोषणा NSP_GPIO_EVENT			0x58
#घोषणा NSP_GPIO_EVENT_INT_MASK		0x5c
#घोषणा NSP_GPIO_EVENT_INT_POLARITY	0x64
#घोषणा NSP_CHIP_A_GPIO_INT_BIT		0x01

/* I/O parameters offset क्रम chipcommon A GPIO */
#घोषणा NSP_GPIO_DRV_CTRL		0x00
#घोषणा NSP_GPIO_HYSTERESIS_EN		0x10
#घोषणा NSP_GPIO_SLEW_RATE_EN		0x14
#घोषणा NSP_PULL_UP_EN			0x18
#घोषणा NSP_PULL_DOWN_EN		0x1c
#घोषणा GPIO_DRV_STRENGTH_BITS		0x03

/*
 * nsp GPIO core
 *
 * @dev: poपूर्णांकer to device
 * @base: I/O रेजिस्टर base क्रम nsp GPIO controller
 * @io_ctrl: I/O रेजिस्टर base क्रम PINCONF support outside the GPIO block
 * @gc: GPIO chip
 * @pctl: poपूर्णांकer to pinctrl_dev
 * @pctldesc: pinctrl descriptor
 * @lock: lock to protect access to I/O रेजिस्टरs
 */
काष्ठा nsp_gpio अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *io_ctrl;
	काष्ठा irq_chip irqchip;
	काष्ठा gpio_chip gc;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_desc pctldesc;
	raw_spinlock_t lock;
पूर्ण;

क्रमागत base_type अणु
	REG,
	IO_CTRL
पूर्ण;

/*
 * Mapping from PINCONF pins to GPIO pins is 1-to-1
 */
अटल अंतरभूत अचिन्हित nsp_pin_to_gpio(अचिन्हित pin)
अणु
	वापस pin;
पूर्ण

/*
 *  nsp_set_bit - set or clear one bit (corresponding to the GPIO pin) in a
 *  nsp GPIO रेजिस्टर
 *
 *  @nsp_gpio: nsp GPIO device
 *  @base_type: reg base to modअगरy
 *  @reg: रेजिस्टर offset
 *  @gpio: GPIO pin
 *  @set: set or clear
 */
अटल अंतरभूत व्योम nsp_set_bit(काष्ठा nsp_gpio *chip, क्रमागत base_type address,
			       अचिन्हित पूर्णांक reg, अचिन्हित gpio, bool set)
अणु
	u32 val;
	व्योम __iomem *base_address;

	अगर (address == IO_CTRL)
		base_address = chip->io_ctrl;
	अन्यथा
		base_address = chip->base;

	val = पढ़ोl(base_address + reg);
	अगर (set)
		val |= BIT(gpio);
	अन्यथा
		val &= ~BIT(gpio);

	ग_लिखोl(val, base_address + reg);
पूर्ण

/*
 *  nsp_get_bit - get one bit (corresponding to the GPIO pin) in a
 *  nsp GPIO रेजिस्टर
 */
अटल अंतरभूत bool nsp_get_bit(काष्ठा nsp_gpio *chip, क्रमागत base_type address,
			       अचिन्हित पूर्णांक reg, अचिन्हित gpio)
अणु
	अगर (address == IO_CTRL)
		वापस !!(पढ़ोl(chip->io_ctrl + reg) & BIT(gpio));
	अन्यथा
		वापस !!(पढ़ोl(chip->base + reg) & BIT(gpio));
पूर्ण

अटल irqवापस_t nsp_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gpio_chip *gc = (काष्ठा gpio_chip *)data;
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	पूर्णांक bit;
	अचिन्हित दीर्घ पूर्णांक_bits = 0;
	u32 पूर्णांक_status;

	/* go through the entire GPIOs and handle all पूर्णांकerrupts */
	पूर्णांक_status = पढ़ोl(chip->base + NSP_CHIP_A_INT_STATUS);
	अगर (पूर्णांक_status & NSP_CHIP_A_GPIO_INT_BIT) अणु
		अचिन्हित पूर्णांक event, level;

		/* Get level and edge पूर्णांकerrupts */
		event = पढ़ोl(chip->base + NSP_GPIO_EVENT_INT_MASK) &
			      पढ़ोl(chip->base + NSP_GPIO_EVENT);
		level = पढ़ोl(chip->base + NSP_GPIO_DATA_IN) ^
			      पढ़ोl(chip->base + NSP_GPIO_INT_POLARITY);
		level &= पढ़ोl(chip->base + NSP_GPIO_INT_MASK);
		पूर्णांक_bits = level | event;

		क्रम_each_set_bit(bit, &पूर्णांक_bits, gc->ngpio)
			generic_handle_irq(
				irq_linear_revmap(gc->irq.करोमुख्य, bit));
	पूर्ण

	वापस  पूर्णांक_bits ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम nsp_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;
	u32 val = BIT(gpio);
	u32 trigger_type;

	trigger_type = irq_get_trigger_type(d->irq);
	अगर (trigger_type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		ग_लिखोl(val, chip->base + NSP_GPIO_EVENT);
पूर्ण

/*
 *  nsp_gpio_irq_set_mask - mask/unmask a GPIO पूर्णांकerrupt
 *
 *  @d: IRQ chip data
 *  @unmask: mask/unmask GPIO पूर्णांकerrupt
 */
अटल व्योम nsp_gpio_irq_set_mask(काष्ठा irq_data *d, bool unmask)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;
	u32 trigger_type;

	trigger_type = irq_get_trigger_type(d->irq);
	अगर (trigger_type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		nsp_set_bit(chip, REG, NSP_GPIO_EVENT_INT_MASK, gpio, unmask);
	अन्यथा
		nsp_set_bit(chip, REG, NSP_GPIO_INT_MASK, gpio, unmask);
पूर्ण

अटल व्योम nsp_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_gpio_irq_set_mask(d, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम nsp_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_gpio_irq_set_mask(d, true);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक nsp_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित gpio = d->hwirq;
	bool level_low;
	bool falling;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	falling = nsp_get_bit(chip, REG, NSP_GPIO_EVENT_INT_POLARITY, gpio);
	level_low = nsp_get_bit(chip, REG, NSP_GPIO_INT_POLARITY, gpio);

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		falling = false;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		falling = true;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		level_low = false;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		level_low = true;
		अवरोध;

	शेष:
		dev_err(chip->dev, "invalid GPIO IRQ type 0x%x\n",
			type);
		raw_spin_unlock_irqrestore(&chip->lock, flags);
		वापस -EINVAL;
	पूर्ण

	nsp_set_bit(chip, REG, NSP_GPIO_EVENT_INT_POLARITY, gpio, falling);
	nsp_set_bit(chip, REG, NSP_GPIO_INT_POLARITY, gpio, level_low);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u level_low:%s falling:%s\n", gpio,
		level_low ? "true" : "false", falling ? "true" : "false");
	वापस 0;
पूर्ण

अटल पूर्णांक nsp_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, REG, NSP_GPIO_OUT_EN, gpio, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set input\n", gpio);
	वापस 0;
पूर्ण

अटल पूर्णांक nsp_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित gpio,
				     पूर्णांक val)
अणु
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, REG, NSP_GPIO_OUT_EN, gpio, true);
	nsp_set_bit(chip, REG, NSP_GPIO_DATA_OUT, gpio, !!(val));
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set output, value:%d\n", gpio, val);
	वापस 0;
पूर्ण

अटल पूर्णांक nsp_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	पूर्णांक val;

	raw_spin_lock_irqsave(&chip->lock, flags);
	val = nsp_get_bit(chip, REG, NSP_GPIO_OUT_EN, gpio);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	वापस !val;
पूर्ण

अटल व्योम nsp_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक val)
अणु
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, REG, NSP_GPIO_DATA_OUT, gpio, !!(val));
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set, value:%d\n", gpio, val);
पूर्ण

अटल पूर्णांक nsp_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा nsp_gpio *chip = gpiochip_get_data(gc);

	वापस !!(पढ़ोl(chip->base + NSP_GPIO_DATA_IN) & BIT(gpio));
पूर्ण

अटल पूर्णांक nsp_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 1;
पूर्ण

/*
 * Only one group: "gpio_grp", since this local pinctrl device only perक्रमms
 * GPIO specअगरic PINCONF configurations
 */
अटल स्थिर अक्षर *nsp_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector)
अणु
	वापस "gpio_grp";
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops nsp_pctrl_ops = अणु
	.get_groups_count = nsp_get_groups_count,
	.get_group_name = nsp_get_group_name,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक nsp_gpio_set_slew(काष्ठा nsp_gpio *chip, अचिन्हित gpio, u32 slew)
अणु
	अगर (slew)
		nsp_set_bit(chip, IO_CTRL, NSP_GPIO_SLEW_RATE_EN, gpio, true);
	अन्यथा
		nsp_set_bit(chip, IO_CTRL, NSP_GPIO_SLEW_RATE_EN, gpio, false);

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_gpio_set_pull(काष्ठा nsp_gpio *chip, अचिन्हित gpio,
			     bool pull_up, bool pull_करोwn)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, IO_CTRL, NSP_PULL_DOWN_EN, gpio, pull_करोwn);
	nsp_set_bit(chip, IO_CTRL, NSP_PULL_UP_EN, gpio, pull_up);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set pullup:%d pulldown: %d\n",
		gpio, pull_up, pull_करोwn);
	वापस 0;
पूर्ण

अटल व्योम nsp_gpio_get_pull(काष्ठा nsp_gpio *chip, अचिन्हित gpio,
			      bool *pull_up, bool *pull_करोwn)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	*pull_up = nsp_get_bit(chip, IO_CTRL, NSP_PULL_UP_EN, gpio);
	*pull_करोwn = nsp_get_bit(chip, IO_CTRL, NSP_PULL_DOWN_EN, gpio);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक nsp_gpio_set_strength(काष्ठा nsp_gpio *chip, अचिन्हित gpio,
				 u32 strength)
अणु
	u32 offset, shअगरt, i;
	u32 val;
	अचिन्हित दीर्घ flags;

	/* make sure drive strength is supported */
	अगर (strength < 2 || strength > 16 || (strength % 2))
		वापस -ENOTSUPP;

	shअगरt = gpio;
	offset = NSP_GPIO_DRV_CTRL;
	dev_dbg(chip->dev, "gpio:%u set drive strength:%d mA\n", gpio,
		strength);
	raw_spin_lock_irqsave(&chip->lock, flags);
	strength = (strength / 2) - 1;
	क्रम (i = GPIO_DRV_STRENGTH_BITS; i > 0; i--) अणु
		val = पढ़ोl(chip->io_ctrl + offset);
		val &= ~BIT(shअगरt);
		val |= ((strength >> (i-1)) & 0x1) << shअगरt;
		ग_लिखोl(val, chip->io_ctrl + offset);
		offset += 4;
	पूर्ण
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_gpio_get_strength(काष्ठा nsp_gpio *chip, अचिन्हित gpio,
				 u16 *strength)
अणु
	अचिन्हित पूर्णांक offset, shअगरt;
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	offset = NSP_GPIO_DRV_CTRL;
	shअगरt = gpio;

	raw_spin_lock_irqsave(&chip->lock, flags);
	*strength = 0;
	क्रम (i = (GPIO_DRV_STRENGTH_BITS - 1); i >= 0; i--) अणु
		val = पढ़ोl(chip->io_ctrl + offset) & BIT(shअगरt);
		val >>= shअगरt;
		*strength += (val << i);
		offset += 4;
	पूर्ण

	/* convert to mA */
	*strength = (*strength + 1) * 2;
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित selector,
			     अचिन्हित दीर्घ *config)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित selector,
			     अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा nsp_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक gpio;
	u16 arg = 0;
	bool pull_up, pull_करोwn;
	पूर्णांक ret;

	gpio = nsp_pin_to_gpio(pin);
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		nsp_gpio_get_pull(chip, gpio, &pull_up, &pull_करोwn);
		अगर ((pull_up == false) && (pull_करोwn == false))
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		nsp_gpio_get_pull(chip, gpio, &pull_up, &pull_करोwn);
		अगर (pull_up)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		nsp_gpio_get_pull(chip, gpio, &pull_up, &pull_करोwn);
		अगर (pull_करोwn)
			वापस 0;
		अन्यथा
			वापस -EINVAL;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		ret = nsp_gpio_get_strength(chip, gpio, &arg);
		अगर (ret)
			वापस ret;
		*config = pinconf_to_config_packed(param, arg);
		वापस 0;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nsp_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा nsp_gpio *chip = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 arg;
	अचिन्हित पूर्णांक i, gpio;
	पूर्णांक ret = -ENOTSUPP;

	gpio = nsp_pin_to_gpio(pin);
	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = nsp_gpio_set_pull(chip, gpio, false, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = nsp_gpio_set_pull(chip, gpio, true, false);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = nsp_gpio_set_pull(chip, gpio, false, true);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			ret = nsp_gpio_set_strength(chip, gpio, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल PIN_CONFIG_SLEW_RATE:
			ret = nsp_gpio_set_slew(chip, gpio, arg);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		शेष:
			dev_err(chip->dev, "invalid configuration\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops nsp_pconf_ops = अणु
	.is_generic = true,
	.pin_config_get = nsp_pin_config_get,
	.pin_config_set = nsp_pin_config_set,
	.pin_config_group_get = nsp_pin_config_group_get,
	.pin_config_group_set = nsp_pin_config_group_set,
पूर्ण;

/*
 * NSP GPIO controller supports some PINCONF related configurations such as
 * pull up, pull करोwn, slew and drive strength, when the pin is configured
 * to GPIO.
 *
 * Here a local pinctrl device is created with simple 1-to-1 pin mapping to the
 * local GPIO pins
 */
अटल पूर्णांक nsp_gpio_रेजिस्टर_pinconf(काष्ठा nsp_gpio *chip)
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
	pctldesc->pctlops = &nsp_pctrl_ops;
	pctldesc->pins = pins;
	pctldesc->npins = gc->ngpio;
	pctldesc->confops = &nsp_pconf_ops;

	chip->pctl = devm_pinctrl_रेजिस्टर(chip->dev, pctldesc, chip);
	अगर (IS_ERR(chip->pctl)) अणु
		dev_err(chip->dev, "unable to register pinctrl device\n");
		वापस PTR_ERR(chip->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nsp_gpio_of_match[] = अणु
	अणु.compatible = "brcm,nsp-gpio-a",पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक nsp_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nsp_gpio *chip;
	काष्ठा gpio_chip *gc;
	u32 val;
	पूर्णांक irq, ret;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &val)) अणु
		dev_err(&pdev->dev, "Missing ngpios OF property\n");
		वापस -ENODEV;
	पूर्ण

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

	chip->io_ctrl = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(chip->io_ctrl)) अणु
		dev_err(dev, "unable to map I/O memory\n");
		वापस PTR_ERR(chip->io_ctrl);
	पूर्ण

	raw_spin_lock_init(&chip->lock);
	gc = &chip->gc;
	gc->base = -1;
	gc->can_sleep = false;
	gc->ngpio = val;
	gc->label = dev_name(dev);
	gc->parent = dev;
	gc->of_node = dev->of_node;
	gc->request = gpiochip_generic_request;
	gc->मुक्त = gpiochip_generic_मुक्त;
	gc->direction_input = nsp_gpio_direction_input;
	gc->direction_output = nsp_gpio_direction_output;
	gc->get_direction = nsp_gpio_get_direction;
	gc->set = nsp_gpio_set;
	gc->get = nsp_gpio_get;

	/* optional GPIO पूर्णांकerrupt support */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;
		काष्ठा irq_chip *irqc;

		irqc = &chip->irqchip;
		irqc->name = "gpio-a";
		irqc->irq_ack = nsp_gpio_irq_ack;
		irqc->irq_mask = nsp_gpio_irq_mask;
		irqc->irq_unmask = nsp_gpio_irq_unmask;
		irqc->irq_set_type = nsp_gpio_irq_set_type;

		val = पढ़ोl(chip->base + NSP_CHIP_A_INT_MASK);
		val = val | NSP_CHIP_A_GPIO_INT_BIT;
		ग_लिखोl(val, (chip->base + NSP_CHIP_A_INT_MASK));

		/* Install ISR क्रम this GPIO controller. */
		ret = devm_request_irq(dev, irq, nsp_gpio_irq_handler,
				       IRQF_SHARED, "gpio-a", &chip->gc);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Unable to request IRQ%d: %d\n",
				irq, ret);
			वापस ret;
		पूर्ण

		girq = &chip->gc.irq;
		girq->chip = irqc;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, gc, chip);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to add GPIO chip\n");
		वापस ret;
	पूर्ण

	ret = nsp_gpio_रेजिस्टर_pinconf(chip);
	अगर (ret) अणु
		dev_err(dev, "unable to register pinconf\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nsp_gpio_driver = अणु
	.driver = अणु
		.name = "nsp-gpio-a",
		.of_match_table = nsp_gpio_of_match,
	पूर्ण,
	.probe = nsp_gpio_probe,
पूर्ण;

अटल पूर्णांक __init nsp_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&nsp_gpio_driver);
पूर्ण
arch_initcall_sync(nsp_gpio_init);
