<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, BayLibre, SAS. All rights reserved.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * Driver क्रम Semtech SX150X I2C GPIO Expanders
 * The handling of the 4-bit chips (SX1501/SX1504/SX1507) is untested.
 *
 * Author: Gregory Bean <gbean@codeaurora.org>
 */

#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

/* The chip models of sx150x */
क्रमागत अणु
	SX150X_123 = 0,
	SX150X_456,
	SX150X_789,
पूर्ण;
क्रमागत अणु
	SX150X_789_REG_MISC_AUTOCLEAR_OFF = 1 << 0,
	SX150X_MAX_REGISTER = 0xad,
	SX150X_IRQ_TYPE_EDGE_RISING = 0x1,
	SX150X_IRQ_TYPE_EDGE_FALLING = 0x2,
	SX150X_789_RESET_KEY1 = 0x12,
	SX150X_789_RESET_KEY2 = 0x34,
पूर्ण;

काष्ठा sx150x_123_pri अणु
	u8 reg_pld_mode;
	u8 reg_pld_table0;
	u8 reg_pld_table1;
	u8 reg_pld_table2;
	u8 reg_pld_table3;
	u8 reg_pld_table4;
	u8 reg_advanced;
पूर्ण;

काष्ठा sx150x_456_pri अणु
	u8 reg_pld_mode;
	u8 reg_pld_table0;
	u8 reg_pld_table1;
	u8 reg_pld_table2;
	u8 reg_pld_table3;
	u8 reg_pld_table4;
	u8 reg_advanced;
पूर्ण;

काष्ठा sx150x_789_pri अणु
	u8 reg_drain;
	u8 reg_polarity;
	u8 reg_घड़ी;
	u8 reg_misc;
	u8 reg_reset;
	u8 ngpios;
पूर्ण;

काष्ठा sx150x_device_data अणु
	u8 model;
	u8 reg_pullup;
	u8 reg_pulldn;
	u8 reg_dir;
	u8 reg_data;
	u8 reg_irq_mask;
	u8 reg_irq_src;
	u8 reg_sense;
	u8 ngpios;
	जोड़ अणु
		काष्ठा sx150x_123_pri x123;
		काष्ठा sx150x_456_pri x456;
		काष्ठा sx150x_789_pri x789;
	पूर्ण pri;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
पूर्ण;

काष्ठा sx150x_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_desc pinctrl_desc;
	काष्ठा gpio_chip gpio;
	काष्ठा irq_chip irq_chip;
	काष्ठा regmap *regmap;
	काष्ठा अणु
		u32 sense;
		u32 masked;
	पूर्ण irq;
	काष्ठा mutex lock;
	स्थिर काष्ठा sx150x_device_data *data;
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc sx150x_4_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "oscio"),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc sx150x_8_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
	PINCTRL_PIN(8, "oscio"),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc sx150x_16_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
	PINCTRL_PIN(8, "gpio8"),
	PINCTRL_PIN(9, "gpio9"),
	PINCTRL_PIN(10, "gpio10"),
	PINCTRL_PIN(11, "gpio11"),
	PINCTRL_PIN(12, "gpio12"),
	PINCTRL_PIN(13, "gpio13"),
	PINCTRL_PIN(14, "gpio14"),
	PINCTRL_PIN(15, "gpio15"),
	PINCTRL_PIN(16, "oscio"),
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1501q_device_data = अणु
	.model = SX150X_123,
	.reg_pullup	= 0x02,
	.reg_pulldn	= 0x03,
	.reg_dir	= 0x01,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x05,
	.reg_irq_src	= 0x08,
	.reg_sense	= 0x07,
	.pri.x123 = अणु
		.reg_pld_mode	= 0x10,
		.reg_pld_table0	= 0x11,
		.reg_pld_table2	= 0x13,
		.reg_advanced	= 0xad,
	पूर्ण,
	.ngpios	= 4,
	.pins = sx150x_4_pins,
	.npins = 4, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1502q_device_data = अणु
	.model = SX150X_123,
	.reg_pullup	= 0x02,
	.reg_pulldn	= 0x03,
	.reg_dir	= 0x01,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x05,
	.reg_irq_src	= 0x08,
	.reg_sense	= 0x06,
	.pri.x123 = अणु
		.reg_pld_mode	= 0x10,
		.reg_pld_table0	= 0x11,
		.reg_pld_table1	= 0x12,
		.reg_pld_table2	= 0x13,
		.reg_pld_table3	= 0x14,
		.reg_pld_table4	= 0x15,
		.reg_advanced	= 0xad,
	पूर्ण,
	.ngpios	= 8,
	.pins = sx150x_8_pins,
	.npins = 8, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1503q_device_data = अणु
	.model = SX150X_123,
	.reg_pullup	= 0x04,
	.reg_pulldn	= 0x06,
	.reg_dir	= 0x02,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x08,
	.reg_irq_src	= 0x0e,
	.reg_sense	= 0x0a,
	.pri.x123 = अणु
		.reg_pld_mode	= 0x20,
		.reg_pld_table0	= 0x22,
		.reg_pld_table1	= 0x24,
		.reg_pld_table2	= 0x26,
		.reg_pld_table3	= 0x28,
		.reg_pld_table4	= 0x2a,
		.reg_advanced	= 0xad,
	पूर्ण,
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins  = 16, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1504q_device_data = अणु
	.model = SX150X_456,
	.reg_pullup	= 0x02,
	.reg_pulldn	= 0x03,
	.reg_dir	= 0x01,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x05,
	.reg_irq_src	= 0x08,
	.reg_sense	= 0x07,
	.pri.x456 = अणु
		.reg_pld_mode	= 0x10,
		.reg_pld_table0	= 0x11,
		.reg_pld_table2	= 0x13,
	पूर्ण,
	.ngpios	= 4,
	.pins = sx150x_4_pins,
	.npins = 4, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1505q_device_data = अणु
	.model = SX150X_456,
	.reg_pullup	= 0x02,
	.reg_pulldn	= 0x03,
	.reg_dir	= 0x01,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x05,
	.reg_irq_src	= 0x08,
	.reg_sense	= 0x06,
	.pri.x456 = अणु
		.reg_pld_mode	= 0x10,
		.reg_pld_table0	= 0x11,
		.reg_pld_table1	= 0x12,
		.reg_pld_table2	= 0x13,
		.reg_pld_table3	= 0x14,
		.reg_pld_table4	= 0x15,
	पूर्ण,
	.ngpios	= 8,
	.pins = sx150x_8_pins,
	.npins = 8, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1506q_device_data = अणु
	.model = SX150X_456,
	.reg_pullup	= 0x04,
	.reg_pulldn	= 0x06,
	.reg_dir	= 0x02,
	.reg_data	= 0x00,
	.reg_irq_mask	= 0x08,
	.reg_irq_src	= 0x0e,
	.reg_sense	= 0x0a,
	.pri.x456 = अणु
		.reg_pld_mode	= 0x20,
		.reg_pld_table0	= 0x22,
		.reg_pld_table1	= 0x24,
		.reg_pld_table2	= 0x26,
		.reg_pld_table3	= 0x28,
		.reg_pld_table4	= 0x2a,
		.reg_advanced	= 0xad,
	पूर्ण,
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins = 16, /* oscio not available */
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1507q_device_data = अणु
	.model = SX150X_789,
	.reg_pullup	= 0x03,
	.reg_pulldn	= 0x04,
	.reg_dir	= 0x07,
	.reg_data	= 0x08,
	.reg_irq_mask	= 0x09,
	.reg_irq_src	= 0x0b,
	.reg_sense	= 0x0a,
	.pri.x789 = अणु
		.reg_drain	= 0x05,
		.reg_polarity	= 0x06,
		.reg_घड़ी	= 0x0d,
		.reg_misc	= 0x0e,
		.reg_reset	= 0x7d,
	पूर्ण,
	.ngpios = 4,
	.pins = sx150x_4_pins,
	.npins = ARRAY_SIZE(sx150x_4_pins),
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1508q_device_data = अणु
	.model = SX150X_789,
	.reg_pullup	= 0x03,
	.reg_pulldn	= 0x04,
	.reg_dir	= 0x07,
	.reg_data	= 0x08,
	.reg_irq_mask	= 0x09,
	.reg_irq_src	= 0x0c,
	.reg_sense	= 0x0a,
	.pri.x789 = अणु
		.reg_drain	= 0x05,
		.reg_polarity	= 0x06,
		.reg_घड़ी	= 0x0f,
		.reg_misc	= 0x10,
		.reg_reset	= 0x7d,
	पूर्ण,
	.ngpios = 8,
	.pins = sx150x_8_pins,
	.npins = ARRAY_SIZE(sx150x_8_pins),
पूर्ण;

अटल स्थिर काष्ठा sx150x_device_data sx1509q_device_data = अणु
	.model = SX150X_789,
	.reg_pullup	= 0x06,
	.reg_pulldn	= 0x08,
	.reg_dir	= 0x0e,
	.reg_data	= 0x10,
	.reg_irq_mask	= 0x12,
	.reg_irq_src	= 0x18,
	.reg_sense	= 0x14,
	.pri.x789 = अणु
		.reg_drain	= 0x0a,
		.reg_polarity	= 0x0c,
		.reg_घड़ी	= 0x1e,
		.reg_misc	= 0x1f,
		.reg_reset	= 0x7d,
	पूर्ण,
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins = ARRAY_SIZE(sx150x_16_pins),
पूर्ण;

अटल पूर्णांक sx150x_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *sx150x_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित पूर्णांक group)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक sx150x_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group,
					स्थिर अचिन्हित पूर्णांक **pins,
					अचिन्हित पूर्णांक *num_pins)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sx150x_pinctrl_ops = अणु
	.get_groups_count = sx150x_pinctrl_get_groups_count,
	.get_group_name = sx150x_pinctrl_get_group_name,
	.get_group_pins = sx150x_pinctrl_get_group_pins,
#अगर_घोषित CONFIG_OF
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
#पूर्ण_अगर
पूर्ण;

अटल bool sx150x_pin_is_oscio(काष्ठा sx150x_pinctrl *pctl, अचिन्हित पूर्णांक pin)
अणु
	अगर (pin >= pctl->data->npins)
		वापस false;

	/* OSCIO pin is only present in 789 devices */
	अगर (pctl->data->model != SX150X_789)
		वापस false;

	वापस !म_भेद(pctl->data->pins[pin].name, "oscio");
पूर्ण

अटल पूर्णांक sx150x_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	अगर (sx150x_pin_is_oscio(pctl, offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	ret = regmap_पढ़ो(pctl->regmap, pctl->data->reg_dir, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक sx150x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	अगर (sx150x_pin_is_oscio(pctl, offset))
		वापस -EINVAL;

	ret = regmap_पढ़ो(pctl->regmap, pctl->data->reg_data, &value);
	अगर (ret < 0)
		वापस ret;

	वापस !!(value & BIT(offset));
पूर्ण

अटल पूर्णांक __sx150x_gpio_set(काष्ठा sx150x_pinctrl *pctl, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	वापस regmap_ग_लिखो_bits(pctl->regmap, pctl->data->reg_data,
				 BIT(offset), value ? BIT(offset) : 0);
पूर्ण

अटल पूर्णांक sx150x_gpio_oscio_set(काष्ठा sx150x_pinctrl *pctl,
				 पूर्णांक value)
अणु
	वापस regmap_ग_लिखो(pctl->regmap,
			    pctl->data->pri.x789.reg_घड़ी,
			    (value ? 0x1f : 0x10));
पूर्ण

अटल व्योम sx150x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);

	अगर (sx150x_pin_is_oscio(pctl, offset))
		sx150x_gpio_oscio_set(pctl, value);
	अन्यथा
		__sx150x_gpio_set(pctl, offset, value);
पूर्ण

अटल व्योम sx150x_gpio_set_multiple(काष्ठा gpio_chip *chip,
				     अचिन्हित दीर्घ *mask,
				     अचिन्हित दीर्घ *bits)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);

	regmap_ग_लिखो_bits(pctl->regmap, pctl->data->reg_data, *mask, *bits);
पूर्ण

अटल पूर्णांक sx150x_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);

	अगर (sx150x_pin_is_oscio(pctl, offset))
		वापस -EINVAL;

	वापस regmap_ग_लिखो_bits(pctl->regmap,
				 pctl->data->reg_dir,
				 BIT(offset), BIT(offset));
पूर्ण

अटल पूर्णांक sx150x_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा sx150x_pinctrl *pctl = gpiochip_get_data(chip);
	पूर्णांक ret;

	अगर (sx150x_pin_is_oscio(pctl, offset))
		वापस sx150x_gpio_oscio_set(pctl, value);

	ret = __sx150x_gpio_set(pctl, offset, value);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो_bits(pctl->regmap,
				 pctl->data->reg_dir,
				 BIT(offset), 0);
पूर्ण

अटल व्योम sx150x_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक n = d->hwirq;

	pctl->irq.masked |= BIT(n);
पूर्ण

अटल व्योम sx150x_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक n = d->hwirq;

	pctl->irq.masked &= ~BIT(n);
पूर्ण

अटल व्योम sx150x_irq_set_sense(काष्ठा sx150x_pinctrl *pctl,
				 अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक sense)
अणु
	/*
	 * Every पूर्णांकerrupt line is represented by two bits shअगरted
	 * proportionally to the line number
	 */
	स्थिर अचिन्हित पूर्णांक n = line * 2;
	स्थिर अचिन्हित पूर्णांक mask = ~((SX150X_IRQ_TYPE_EDGE_RISING |
				     SX150X_IRQ_TYPE_EDGE_FALLING) << n);

	pctl->irq.sense &= mask;
	pctl->irq.sense |= sense << n;
पूर्ण

अटल पूर्णांक sx150x_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक n, val = 0;

	अगर (flow_type & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		वापस -EINVAL;

	n = d->hwirq;

	अगर (flow_type & IRQ_TYPE_EDGE_RISING)
		val |= SX150X_IRQ_TYPE_EDGE_RISING;
	अगर (flow_type & IRQ_TYPE_EDGE_FALLING)
		val |= SX150X_IRQ_TYPE_EDGE_FALLING;

	sx150x_irq_set_sense(pctl, n, val);
	वापस 0;
पूर्ण

अटल irqवापस_t sx150x_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sx150x_pinctrl *pctl = (काष्ठा sx150x_pinctrl *)dev_id;
	अचिन्हित दीर्घ n, status;
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(pctl->regmap, pctl->data->reg_irq_src, &val);
	अगर (err < 0)
		वापस IRQ_NONE;

	err = regmap_ग_लिखो(pctl->regmap, pctl->data->reg_irq_src, val);
	अगर (err < 0)
		वापस IRQ_NONE;

	status = val;
	क्रम_each_set_bit(n, &status, pctl->data->ngpios)
		handle_nested_irq(irq_find_mapping(pctl->gpio.irq.करोमुख्य, n));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sx150x_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));

	mutex_lock(&pctl->lock);
पूर्ण

अटल व्योम sx150x_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));

	regmap_ग_लिखो(pctl->regmap, pctl->data->reg_irq_mask, pctl->irq.masked);
	regmap_ग_लिखो(pctl->regmap, pctl->data->reg_sense, pctl->irq.sense);
	mutex_unlock(&pctl->lock);
पूर्ण

अटल पूर्णांक sx150x_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा sx150x_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	पूर्णांक ret;
	u32 arg;
	अचिन्हित पूर्णांक data;

	अगर (sx150x_pin_is_oscio(pctl, pin)) अणु
		चयन (param) अणु
		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		हाल PIN_CONFIG_OUTPUT:
			ret = regmap_पढ़ो(pctl->regmap,
					  pctl->data->pri.x789.reg_घड़ी,
					  &data);
			अगर (ret < 0)
				वापस ret;

			अगर (param == PIN_CONFIG_DRIVE_PUSH_PULL)
				arg = (data & 0x1f) ? 1 : 0;
			अन्यथा अणु
				अगर ((data & 0x1f) == 0x1f)
					arg = 1;
				अन्यथा अगर ((data & 0x1f) == 0x10)
					arg = 0;
				अन्यथा
					वापस -EINVAL;
			पूर्ण

			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		जाओ out;
	पूर्ण

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = regmap_पढ़ो(pctl->regmap,
				  pctl->data->reg_pulldn,
				  &data);
		data &= BIT(pin);

		अगर (ret < 0)
			वापस ret;

		अगर (!ret)
			वापस -EINVAL;

		arg = 1;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = regmap_पढ़ो(pctl->regmap,
				  pctl->data->reg_pullup,
				  &data);
		data &= BIT(pin);

		अगर (ret < 0)
			वापस ret;

		अगर (!ret)
			वापस -EINVAL;

		arg = 1;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (pctl->data->model != SX150X_789)
			वापस -ENOTSUPP;

		ret = regmap_पढ़ो(pctl->regmap,
				  pctl->data->pri.x789.reg_drain,
				  &data);
		data &= BIT(pin);

		अगर (ret < 0)
			वापस ret;

		अगर (!data)
			वापस -EINVAL;

		arg = 1;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर (pctl->data->model != SX150X_789)
			arg = true;
		अन्यथा अणु
			ret = regmap_पढ़ो(pctl->regmap,
					  pctl->data->pri.x789.reg_drain,
					  &data);
			data &= BIT(pin);

			अगर (ret < 0)
				वापस ret;

			अगर (data)
				वापस -EINVAL;

			arg = 1;
		पूर्ण
		अवरोध;

	हाल PIN_CONFIG_OUTPUT:
		ret = sx150x_gpio_get_direction(&pctl->gpio, pin);
		अगर (ret < 0)
			वापस ret;

		अगर (ret == GPIO_LINE_सूचीECTION_IN)
			वापस -EINVAL;

		ret = sx150x_gpio_get(&pctl->gpio, pin);
		अगर (ret < 0)
			वापस ret;

		arg = ret;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

out:
	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक sx150x_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा sx150x_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 arg;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		अगर (sx150x_pin_is_oscio(pctl, pin)) अणु
			अगर (param == PIN_CONFIG_OUTPUT) अणु
				ret = sx150x_gpio_direction_output(&pctl->gpio,
								   pin, arg);
				अगर (ret < 0)
					वापस ret;

				जारी;
			पूर्ण अन्यथा
				वापस -ENOTSUPP;
		पूर्ण

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->reg_pulldn,
						BIT(pin), 0);
			अगर (ret < 0)
				वापस ret;

			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->reg_pullup,
						BIT(pin), 0);
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->reg_pullup,
						BIT(pin), BIT(pin));
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->reg_pulldn,
						BIT(pin), BIT(pin));
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			अगर (pctl->data->model != SX150X_789 ||
			    sx150x_pin_is_oscio(pctl, pin))
				वापस -ENOTSUPP;

			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->pri.x789.reg_drain,
						BIT(pin), BIT(pin));
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			अगर (pctl->data->model != SX150X_789 ||
			    sx150x_pin_is_oscio(pctl, pin))
				वापस 0;

			ret = regmap_ग_लिखो_bits(pctl->regmap,
						pctl->data->pri.x789.reg_drain,
						BIT(pin), 0);
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		हाल PIN_CONFIG_OUTPUT:
			ret = sx150x_gpio_direction_output(&pctl->gpio,
							   pin, arg);
			अगर (ret < 0)
				वापस ret;

			अवरोध;

		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sx150x_pinconf_ops = अणु
	.pin_config_get = sx150x_pinconf_get,
	.pin_config_set = sx150x_pinconf_set,
	.is_generic = true,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id sx150x_id[] = अणु
	अणु"sx1501q", (kernel_uदीर्घ_t) &sx1501q_device_data पूर्ण,
	अणु"sx1502q", (kernel_uदीर्घ_t) &sx1502q_device_data पूर्ण,
	अणु"sx1503q", (kernel_uदीर्घ_t) &sx1503q_device_data पूर्ण,
	अणु"sx1504q", (kernel_uदीर्घ_t) &sx1504q_device_data पूर्ण,
	अणु"sx1505q", (kernel_uदीर्घ_t) &sx1505q_device_data पूर्ण,
	अणु"sx1506q", (kernel_uदीर्घ_t) &sx1506q_device_data पूर्ण,
	अणु"sx1507q", (kernel_uदीर्घ_t) &sx1507q_device_data पूर्ण,
	अणु"sx1508q", (kernel_uदीर्घ_t) &sx1508q_device_data पूर्ण,
	अणु"sx1509q", (kernel_uदीर्घ_t) &sx1509q_device_data पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id sx150x_of_match[] = अणु
	अणु .compatible = "semtech,sx1501q", .data = &sx1501q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1502q", .data = &sx1502q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1503q", .data = &sx1503q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1504q", .data = &sx1504q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1505q", .data = &sx1505q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1506q", .data = &sx1506q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1507q", .data = &sx1507q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1508q", .data = &sx1508q_device_data पूर्ण,
	अणु .compatible = "semtech,sx1509q", .data = &sx1509q_device_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sx150x_reset(काष्ठा sx150x_pinctrl *pctl)
अणु
	पूर्णांक err;

	err = i2c_smbus_ग_लिखो_byte_data(pctl->client,
					pctl->data->pri.x789.reg_reset,
					SX150X_789_RESET_KEY1);
	अगर (err < 0)
		वापस err;

	err = i2c_smbus_ग_लिखो_byte_data(pctl->client,
					pctl->data->pri.x789.reg_reset,
					SX150X_789_RESET_KEY2);
	वापस err;
पूर्ण

अटल पूर्णांक sx150x_init_misc(काष्ठा sx150x_pinctrl *pctl)
अणु
	u8 reg, value;

	चयन (pctl->data->model) अणु
	हाल SX150X_789:
		reg   = pctl->data->pri.x789.reg_misc;
		value = SX150X_789_REG_MISC_AUTOCLEAR_OFF;
		अवरोध;
	हाल SX150X_456:
		reg   = pctl->data->pri.x456.reg_advanced;
		value = 0x00;

		/*
		 * Only SX1506 has RegAdvanced, SX1504/5 are expected
		 * to initialize this offset to zero
		 */
		अगर (!reg)
			वापस 0;
		अवरोध;
	हाल SX150X_123:
		reg   = pctl->data->pri.x123.reg_advanced;
		value = 0x00;
		अवरोध;
	शेष:
		WARN(1, "Unknown chip model %d\n", pctl->data->model);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_ग_लिखो(pctl->regmap, reg, value);
पूर्ण

अटल पूर्णांक sx150x_init_hw(काष्ठा sx150x_pinctrl *pctl)
अणु
	स्थिर u8 reg[] = अणु
		[SX150X_789] = pctl->data->pri.x789.reg_polarity,
		[SX150X_456] = pctl->data->pri.x456.reg_pld_mode,
		[SX150X_123] = pctl->data->pri.x123.reg_pld_mode,
	पूर्ण;
	पूर्णांक err;

	अगर (pctl->data->model == SX150X_789 &&
	    of_property_पढ़ो_bool(pctl->dev->of_node, "semtech,probe-reset")) अणु
		err = sx150x_reset(pctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = sx150x_init_misc(pctl);
	अगर (err < 0)
		वापस err;

	/* Set all pins to work in normal mode */
	वापस regmap_ग_लिखो(pctl->regmap, reg[pctl->data->model], 0);
पूर्ण

अटल पूर्णांक sx150x_regmap_reg_width(काष्ठा sx150x_pinctrl *pctl,
				   अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा sx150x_device_data *data = pctl->data;

	अगर (reg == data->reg_sense) अणु
		/*
		 * RegSense packs two bits of configuration per GPIO,
		 * so we'd need to पढ़ो twice as many bits as there
		 * are GPIO in our chip
		 */
		वापस 2 * data->ngpios;
	पूर्ण अन्यथा अगर ((data->model == SX150X_789 &&
		    (reg == data->pri.x789.reg_misc ||
		     reg == data->pri.x789.reg_घड़ी ||
		     reg == data->pri.x789.reg_reset))
		   ||
		   (data->model == SX150X_123 &&
		    reg == data->pri.x123.reg_advanced)
		   ||
		   (data->model == SX150X_456 &&
		    data->pri.x456.reg_advanced &&
		    reg == data->pri.x456.reg_advanced)) अणु
		वापस 8;
	पूर्ण अन्यथा अणु
		वापस data->ngpios;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक sx150x_maybe_swizzle(काष्ठा sx150x_pinctrl *pctl,
					 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक a, b;
	स्थिर काष्ठा sx150x_device_data *data = pctl->data;

	/*
	 * Whereas SX1509 presents RegSense in a simple layout as such:
	 *	reg     [ f f e e d d c c ]
	 *	reg + 1 [ b b a a 9 9 8 8 ]
	 *	reg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *	reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * SX1503 and SX1506 deviate from that data layout, instead storing
	 * their contents as follows:
	 *
	 *	reg     [ f f e e d d c c ]
	 *	reg + 1 [ 7 7 6 6 5 5 4 4 ]
	 *	reg + 2 [ b b a a 9 9 8 8 ]
	 *	reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * so, taking that पूर्णांकo account, we swap two
	 * inner bytes of a 4-byte result
	 */

	अगर (reg == data->reg_sense &&
	    data->ngpios == 16 &&
	    (data->model == SX150X_123 ||
	     data->model == SX150X_456)) अणु
		a = val & 0x00ff0000;
		b = val & 0x0000ff00;

		val &= 0xff0000ff;
		val |= b << 8;
		val |= a >> 8;
	पूर्ण

	वापस val;
पूर्ण

/*
 * In order to mask the dअगरferences between 16 and 8 bit expander
 * devices we set up a sligthly ficticious regmap that pretends to be
 * a set of 32-bit (to accommodate RegSenseLow/RegSenseHigh
 * pair/quartet) रेजिस्टरs and transparently reस्थिरructs those
 * रेजिस्टरs via multiple I2C/SMBus पढ़ोs
 *
 * This way the rest of the driver code, पूर्णांकerfacing with the chip via
 * regmap API, can work assuming that each GPIO pin is represented by
 * a group of bits at an offset proportional to GPIO number within a
 * given रेजिस्टर.
 */
अटल पूर्णांक sx150x_regmap_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *result)
अणु
	पूर्णांक ret, n;
	काष्ठा sx150x_pinctrl *pctl = context;
	काष्ठा i2c_client *i2c = pctl->client;
	स्थिर पूर्णांक width = sx150x_regmap_reg_width(pctl, reg);
	अचिन्हित पूर्णांक idx, val;

	/*
	 * There are four potential हालs covered by this function:
	 *
	 * 1) 8-pin chip, single configuration bit रेजिस्टर
	 *
	 *	This is trivial the code below just needs to पढ़ो:
	 *		reg  [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 2) 8-pin chip, द्विगुन configuration bit रेजिस्टर (RegSense)
	 *
	 *	The पढ़ो will be करोne as follows:
	 *		reg      [ 7 7 6 6 5 5 4 4 ]
	 *		reg + 1  [ 3 3 2 2 1 1 0 0 ]
	 *
	 * 3) 16-pin chip, single configuration bit रेजिस्टर
	 *
	 *	The पढ़ो will be करोne as follows:
	 *		reg     [ f e d c b a 9 8 ]
	 *		reg + 1 [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 4) 16-pin chip, द्विगुन configuration bit रेजिस्टर (RegSense)
	 *
	 *	The पढ़ो will be करोne as follows:
	 *		reg     [ f f e e d d c c ]
	 *		reg + 1 [ b b a a 9 9 8 8 ]
	 *		reg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *		reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 */

	क्रम (n = width, val = 0, idx = reg; n > 0; n -= 8, idx++) अणु
		val <<= 8;

		ret = i2c_smbus_पढ़ो_byte_data(i2c, idx);
		अगर (ret < 0)
			वापस ret;

		val |= ret;
	पूर्ण

	*result = sx150x_maybe_swizzle(pctl, reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sx150x_regmap_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret, n;
	काष्ठा sx150x_pinctrl *pctl = context;
	काष्ठा i2c_client *i2c = pctl->client;
	स्थिर पूर्णांक width = sx150x_regmap_reg_width(pctl, reg);

	val = sx150x_maybe_swizzle(pctl, reg, val);

	n = (width - 1) & ~7;
	करो अणु
		स्थिर u8 byte = (val >> n) & 0xff;

		ret = i2c_smbus_ग_लिखो_byte_data(i2c, reg, byte);
		अगर (ret < 0)
			वापस ret;

		reg++;
		n -= 8;
	पूर्ण जबतक (n >= 0);

	वापस 0;
पूर्ण

अटल bool sx150x_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा sx150x_pinctrl *pctl = i2c_get_clientdata(to_i2c_client(dev));

	वापस reg == pctl->data->reg_irq_src || reg == pctl->data->reg_data;
पूर्ण

अटल स्थिर काष्ठा regmap_config sx150x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,

	.cache_type = REGCACHE_RBTREE,

	.reg_पढ़ो = sx150x_regmap_reg_पढ़ो,
	.reg_ग_लिखो = sx150x_regmap_reg_ग_लिखो,

	.max_रेजिस्टर = SX150X_MAX_REGISTER,
	.अस्थिर_reg = sx150x_reg_अस्थिर,
पूर्ण;

अटल पूर्णांक sx150x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	अटल स्थिर u32 i2c_funcs = I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WRITE_WORD_DATA;
	काष्ठा device *dev = &client->dev;
	काष्ठा sx150x_pinctrl *pctl;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, i2c_funcs))
		वापस -ENOSYS;

	pctl = devm_kzalloc(dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pctl);

	pctl->dev = dev;
	pctl->client = client;

	अगर (dev->of_node)
		pctl->data = of_device_get_match_data(dev);
	अन्यथा
		pctl->data = (काष्ठा sx150x_device_data *)id->driver_data;

	अगर (!pctl->data)
		वापस -EINVAL;

	pctl->regmap = devm_regmap_init(dev, शून्य, pctl,
					&sx150x_regmap_config);
	अगर (IS_ERR(pctl->regmap)) अणु
		ret = PTR_ERR(pctl->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	mutex_init(&pctl->lock);

	ret = sx150x_init_hw(pctl);
	अगर (ret)
		वापस ret;

	/* Pinctrl_desc */
	pctl->pinctrl_desc.name = "sx150x-pinctrl";
	pctl->pinctrl_desc.pctlops = &sx150x_pinctrl_ops;
	pctl->pinctrl_desc.confops = &sx150x_pinconf_ops;
	pctl->pinctrl_desc.pins = pctl->data->pins;
	pctl->pinctrl_desc.npins = pctl->data->npins;
	pctl->pinctrl_desc.owner = THIS_MODULE;

	ret = devm_pinctrl_रेजिस्टर_and_init(dev, &pctl->pinctrl_desc,
					     pctl, &pctl->pctldev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register pinctrl device\n");
		वापस ret;
	पूर्ण

	/* Register GPIO controller */
	pctl->gpio.base = -1;
	pctl->gpio.ngpio = pctl->data->npins;
	pctl->gpio.get_direction = sx150x_gpio_get_direction;
	pctl->gpio.direction_input = sx150x_gpio_direction_input;
	pctl->gpio.direction_output = sx150x_gpio_direction_output;
	pctl->gpio.get = sx150x_gpio_get;
	pctl->gpio.set = sx150x_gpio_set;
	pctl->gpio.set_config = gpiochip_generic_config;
	pctl->gpio.parent = dev;
#अगर_घोषित CONFIG_OF_GPIO
	pctl->gpio.of_node = dev->of_node;
#पूर्ण_अगर
	pctl->gpio.can_sleep = true;
	pctl->gpio.label = devm_kstrdup(dev, client->name, GFP_KERNEL);
	अगर (!pctl->gpio.label)
		वापस -ENOMEM;

	/*
	 * Setting multiple pins is not safe when all pins are not
	 * handled by the same regmap रेजिस्टर. The oscio pin (present
	 * on the SX150X_789 chips) lives in its own रेजिस्टर, so
	 * would require locking that is not in place at this समय.
	 */
	अगर (pctl->data->model != SX150X_789)
		pctl->gpio.set_multiple = sx150x_gpio_set_multiple;

	/* Add Interrupt support अगर an irq is specअगरied */
	अगर (client->irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		pctl->irq_chip.irq_mask = sx150x_irq_mask;
		pctl->irq_chip.irq_unmask = sx150x_irq_unmask;
		pctl->irq_chip.irq_set_type = sx150x_irq_set_type;
		pctl->irq_chip.irq_bus_lock = sx150x_irq_bus_lock;
		pctl->irq_chip.irq_bus_sync_unlock = sx150x_irq_bus_sync_unlock;
		pctl->irq_chip.name = devm_kstrdup(dev, client->name,
						   GFP_KERNEL);
		अगर (!pctl->irq_chip.name)
			वापस -ENOMEM;

		pctl->irq.masked = ~0;
		pctl->irq.sense = 0;

		/*
		 * Because sx150x_irq_thपढ़ोed_fn invokes all of the
		 * nested पूर्णांकerrupt handlers via handle_nested_irq,
		 * any "handler" asचिन्हित to काष्ठा gpio_irq_chip
		 * below is going to be ignored, so the choice of the
		 * function करोes not matter that much.
		 *
		 * We set it to handle_bad_irq to aव्योम confusion,
		 * plus it will be instantly noticeable अगर it is ever
		 * called (should not happen)
		 */
		girq = &pctl->gpio.irq;
		girq->chip = &pctl->irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
		girq->thपढ़ोed = true;

		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						sx150x_irq_thपढ़ो_fn,
						IRQF_ONESHOT | IRQF_SHARED |
						IRQF_TRIGGER_FALLING,
						pctl->irq_chip.name, pctl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &pctl->gpio, pctl);
	अगर (ret)
		वापस ret;

	/*
	 * Pin control functions need to be enabled AFTER रेजिस्टरing the
	 * GPIO chip because sx150x_pinconf_set() calls
	 * sx150x_gpio_direction_output().
	 */
	ret = pinctrl_enable(pctl->pctldev);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable pinctrl device\n");
		वापस ret;
	पूर्ण

	ret = gpiochip_add_pin_range(&pctl->gpio, dev_name(dev),
				     0, 0, pctl->data->npins);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver sx150x_driver = अणु
	.driver = अणु
		.name = "sx150x-pinctrl",
		.of_match_table = of_match_ptr(sx150x_of_match),
	पूर्ण,
	.probe    = sx150x_probe,
	.id_table = sx150x_id,
पूर्ण;

अटल पूर्णांक __init sx150x_init(व्योम)
अणु
	वापस i2c_add_driver(&sx150x_driver);
पूर्ण
subsys_initcall(sx150x_init);
