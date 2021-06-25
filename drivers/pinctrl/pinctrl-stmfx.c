<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STMicroelectronics Multi-Function eXpander (STMFX) GPIO expander
 *
 * Copyright (C) 2019 STMicroelectronics
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>.
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/sपंचांगfx.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "core.h"
#समावेश "pinctrl-utils.h"

/* GPIOs expander */
/* GPIO_STATE1 0x10, GPIO_STATE2 0x11, GPIO_STATE3 0x12 */
#घोषणा STMFX_REG_GPIO_STATE		STMFX_REG_GPIO_STATE1 /* R */
/* GPIO_सूची1 0x60, GPIO_सूची2 0x61, GPIO_सूची3 0x63 */
#घोषणा STMFX_REG_GPIO_सूची		STMFX_REG_GPIO_सूची1 /* RW */
/* GPIO_TYPE1 0x64, GPIO_TYPE2 0x65, GPIO_TYPE3 0x66 */
#घोषणा STMFX_REG_GPIO_TYPE		STMFX_REG_GPIO_TYPE1 /* RW */
/* GPIO_PUPD1 0x68, GPIO_PUPD2 0x69, GPIO_PUPD3 0x6A */
#घोषणा STMFX_REG_GPIO_PUPD		STMFX_REG_GPIO_PUPD1 /* RW */
/* GPO_SET1 0x6C, GPO_SET2 0x6D, GPO_SET3 0x6E */
#घोषणा STMFX_REG_GPO_SET		STMFX_REG_GPO_SET1 /* RW */
/* GPO_CLR1 0x70, GPO_CLR2 0x71, GPO_CLR3 0x72 */
#घोषणा STMFX_REG_GPO_CLR		STMFX_REG_GPO_CLR1 /* RW */
/* IRQ_GPI_SRC1 0x48, IRQ_GPI_SRC2 0x49, IRQ_GPI_SRC3 0x4A */
#घोषणा STMFX_REG_IRQ_GPI_SRC		STMFX_REG_IRQ_GPI_SRC1 /* RW */
/* IRQ_GPI_EVT1 0x4C, IRQ_GPI_EVT2 0x4D, IRQ_GPI_EVT3 0x4E */
#घोषणा STMFX_REG_IRQ_GPI_EVT		STMFX_REG_IRQ_GPI_EVT1 /* RW */
/* IRQ_GPI_TYPE1 0x50, IRQ_GPI_TYPE2 0x51, IRQ_GPI_TYPE3 0x52 */
#घोषणा STMFX_REG_IRQ_GPI_TYPE		STMFX_REG_IRQ_GPI_TYPE1 /* RW */
/* IRQ_GPI_PENDING1 0x0C, IRQ_GPI_PENDING2 0x0D, IRQ_GPI_PENDING3 0x0E*/
#घोषणा STMFX_REG_IRQ_GPI_PENDING	STMFX_REG_IRQ_GPI_PENDING1 /* R */
/* IRQ_GPI_ACK1 0x54, IRQ_GPI_ACK2 0x55, IRQ_GPI_ACK3 0x56 */
#घोषणा STMFX_REG_IRQ_GPI_ACK		STMFX_REG_IRQ_GPI_ACK1 /* RW */

#घोषणा NR_GPIO_REGS			3
#घोषणा NR_GPIOS_PER_REG		8
#घोषणा get_reg(offset)			((offset) / NR_GPIOS_PER_REG)
#घोषणा get_shअगरt(offset)		((offset) % NR_GPIOS_PER_REG)
#घोषणा get_mask(offset)		(BIT(get_shअगरt(offset)))

/*
 * STMFX pinctrl can have up to 24 pins अगर STMFX other functions are not used.
 * Pins availability is managed thanks to gpio-ranges property.
 */
अटल स्थिर काष्ठा pinctrl_pin_desc sपंचांगfx_pins[] = अणु
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
	PINCTRL_PIN(16, "agpio0"),
	PINCTRL_PIN(17, "agpio1"),
	PINCTRL_PIN(18, "agpio2"),
	PINCTRL_PIN(19, "agpio3"),
	PINCTRL_PIN(20, "agpio4"),
	PINCTRL_PIN(21, "agpio5"),
	PINCTRL_PIN(22, "agpio6"),
	PINCTRL_PIN(23, "agpio7"),
पूर्ण;

काष्ठा sपंचांगfx_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा sपंचांगfx *sपंचांगfx;
	काष्ठा pinctrl_dev *pctl_dev;
	काष्ठा pinctrl_desc pctl_desc;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
	काष्ठा mutex lock; /* IRQ bus lock */
	अचिन्हित दीर्घ gpio_valid_mask;
	/* Cache of IRQ_GPI_* रेजिस्टरs क्रम bus_lock */
	u8 irq_gpi_src[NR_GPIO_REGS];
	u8 irq_gpi_type[NR_GPIO_REGS];
	u8 irq_gpi_evt[NR_GPIO_REGS];
	u8 irq_toggle_edge[NR_GPIO_REGS];
#अगर_घोषित CONFIG_PM
	/* Backup of GPIO_* रेजिस्टरs क्रम suspend/resume */
	u8 bkp_gpio_state[NR_GPIO_REGS];
	u8 bkp_gpio_dir[NR_GPIO_REGS];
	u8 bkp_gpio_type[NR_GPIO_REGS];
	u8 bkp_gpio_pupd[NR_GPIO_REGS];
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sपंचांगfx_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = STMFX_REG_GPIO_STATE + get_reg(offset);
	u32 mask = get_mask(offset);
	u32 value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctl->sपंचांगfx->map, reg, &value);

	वापस ret ? ret : !!(value & mask);
पूर्ण

अटल व्योम sपंचांगfx_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = value ? STMFX_REG_GPO_SET : STMFX_REG_GPO_CLR;
	u32 mask = get_mask(offset);

	regmap_ग_लिखो_bits(pctl->sपंचांगfx->map, reg + get_reg(offset),
			  mask, mask);
पूर्ण

अटल पूर्णांक sपंचांगfx_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = STMFX_REG_GPIO_सूची + get_reg(offset);
	u32 mask = get_mask(offset);
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctl->sपंचांगfx->map, reg, &val);
	/*
	 * On sपंचांगfx, gpio pins direction is (0)input, (1)output.
	 */
	अगर (ret)
		वापस ret;

	अगर (val & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक sपंचांगfx_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = STMFX_REG_GPIO_सूची + get_reg(offset);
	u32 mask = get_mask(offset);

	वापस regmap_ग_लिखो_bits(pctl->sपंचांगfx->map, reg, mask, 0);
पूर्ण

अटल पूर्णांक sपंचांगfx_gpio_direction_output(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = STMFX_REG_GPIO_सूची + get_reg(offset);
	u32 mask = get_mask(offset);

	sपंचांगfx_gpio_set(gc, offset, value);

	वापस regmap_ग_लिखो_bits(pctl->sपंचांगfx->map, reg, mask, mask);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_get_pupd(काष्ठा sपंचांगfx_pinctrl *pctl,
				  अचिन्हित पूर्णांक offset)
अणु
	u32 reg = STMFX_REG_GPIO_PUPD + get_reg(offset);
	u32 pupd, mask = get_mask(offset);
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctl->sपंचांगfx->map, reg, &pupd);
	अगर (ret)
		वापस ret;

	वापस !!(pupd & mask);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_set_pupd(काष्ठा sपंचांगfx_pinctrl *pctl,
				  अचिन्हित पूर्णांक offset, u32 pupd)
अणु
	u32 reg = STMFX_REG_GPIO_PUPD + get_reg(offset);
	u32 mask = get_mask(offset);

	वापस regmap_ग_लिखो_bits(pctl->sपंचांगfx->map, reg, mask, pupd ? mask : 0);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_get_type(काष्ठा sपंचांगfx_pinctrl *pctl,
				  अचिन्हित पूर्णांक offset)
अणु
	u32 reg = STMFX_REG_GPIO_TYPE + get_reg(offset);
	u32 type, mask = get_mask(offset);
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctl->sपंचांगfx->map, reg, &type);
	अगर (ret)
		वापस ret;

	वापस !!(type & mask);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_set_type(काष्ठा sपंचांगfx_pinctrl *pctl,
				  अचिन्हित पूर्णांक offset, u32 type)
अणु
	u32 reg = STMFX_REG_GPIO_TYPE + get_reg(offset);
	u32 mask = get_mask(offset);

	वापस regmap_ग_लिखो_bits(pctl->sपंचांगfx->map, reg, mask, type ? mask : 0);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	काष्ठा pinctrl_gpio_range *range;
	u32 arg = 0;
	पूर्णांक ret, dir, type, pupd;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	अगर (!range)
		वापस -EINVAL;

	dir = sपंचांगfx_gpio_get_direction(&pctl->gpio_chip, pin);
	अगर (dir < 0)
		वापस dir;

	/*
	 * Currently the gpiolib IN is 1 and OUT is 0 but let's not count
	 * on it just to be on the safe side also in the future :)
	 */
	dir = (dir == GPIO_LINE_सूचीECTION_IN) ? 1 : 0;

	type = sपंचांगfx_pinconf_get_type(pctl, pin);
	अगर (type < 0)
		वापस type;
	pupd = sपंचांगfx_pinconf_get_pupd(pctl, pin);
	अगर (pupd < 0)
		वापस pupd;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर ((!dir && (!type || !pupd)) || (dir && !type))
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (dir && type && !pupd)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (type && pupd)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर ((!dir && type) || (dir && !type))
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर ((!dir && !type) || (dir && type))
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		अगर (dir)
			वापस -EINVAL;

		ret = sपंचांगfx_gpio_get(&pctl->gpio_chip, pin);
		अगर (ret < 0)
			वापस ret;

		arg = ret;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pinctrl_gpio_range *range;
	क्रमागत pin_config_param param;
	u32 arg;
	पूर्णांक i, ret;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	अगर (!range) अणु
		dev_err(pctldev->dev, "pin %d is not available\n", pin);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			ret = sपंचांगfx_pinconf_set_type(pctl, pin, 0);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = sपंचांगfx_pinconf_set_type(pctl, pin, 1);
			अगर (ret)
				वापस ret;
			ret = sपंचांगfx_pinconf_set_pupd(pctl, pin, 0);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = sपंचांगfx_pinconf_set_type(pctl, pin, 1);
			अगर (ret)
				वापस ret;
			ret = sपंचांगfx_pinconf_set_pupd(pctl, pin, 1);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			ret = sपंचांगfx_pinconf_set_type(pctl, pin, 1);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			ret = sपंचांगfx_gpio_direction_output(&pctl->gpio_chip,
							  pin, arg);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांगfx_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक dir, type, pupd, val;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, offset);
	अगर (!range)
		वापस;

	dir = sपंचांगfx_gpio_get_direction(&pctl->gpio_chip, offset);
	अगर (dir < 0)
		वापस;
	type = sपंचांगfx_pinconf_get_type(pctl, offset);
	अगर (type < 0)
		वापस;
	pupd = sपंचांगfx_pinconf_get_pupd(pctl, offset);
	अगर (pupd < 0)
		वापस;
	val = sपंचांगfx_gpio_get(&pctl->gpio_chip, offset);
	अगर (val < 0)
		वापस;

	अगर (dir == GPIO_LINE_सूचीECTION_OUT) अणु
		seq_म_लिखो(s, "output %s ", val ? "high" : "low");
		अगर (type)
			seq_म_लिखो(s, "open drain %s internal pull-up ",
				   pupd ? "with" : "without");
		अन्यथा
			seq_माला_दो(s, "push pull no pull ");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, "input %s ", val ? "high" : "low");
		अगर (type)
			seq_म_लिखो(s, "with internal pull-%s ",
				   pupd ? "up" : "down");
		अन्यथा
			seq_म_लिखो(s, "%s ", pupd ? "floating" : "analog");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sपंचांगfx_pinconf_ops = अणु
	.pin_config_get		= sपंचांगfx_pinconf_get,
	.pin_config_set		= sपंचांगfx_pinconf_set,
	.pin_config_dbg_show	= sपंचांगfx_pinconf_dbg_show,
पूर्ण;

अटल पूर्णांक sपंचांगfx_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *sपंचांगfx_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित पूर्णांक selector)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector,
					स्थिर अचिन्हित पूर्णांक **pins,
					अचिन्हित पूर्णांक *num_pins)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sपंचांगfx_pinctrl_ops = अणु
	.get_groups_count = sपंचांगfx_pinctrl_get_groups_count,
	.get_group_name = sपंचांगfx_pinctrl_get_group_name,
	.get_group_pins = sपंचांगfx_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल व्योम sपंचांगfx_pinctrl_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	pctl->irq_gpi_src[reg] &= ~mask;
पूर्ण

अटल व्योम sपंचांगfx_pinctrl_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	pctl->irq_gpi_src[reg] |= mask;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	अगर (type == IRQ_TYPE_NONE)
		वापस -EINVAL;

	अगर (type & IRQ_TYPE_EDGE_BOTH) अणु
		pctl->irq_gpi_evt[reg] |= mask;
		irq_set_handler_locked(data, handle_edge_irq);
	पूर्ण अन्यथा अणु
		pctl->irq_gpi_evt[reg] &= ~mask;
		irq_set_handler_locked(data, handle_level_irq);
	पूर्ण

	अगर ((type & IRQ_TYPE_EDGE_RISING) || (type & IRQ_TYPE_LEVEL_HIGH))
		pctl->irq_gpi_type[reg] |= mask;
	अन्यथा
		pctl->irq_gpi_type[reg] &= ~mask;

	/*
	 * In हाल of (type & IRQ_TYPE_EDGE_BOTH), we need to know current
	 * GPIO value to set the right edge trigger. But in atomic context
	 * here we can't access registers over I2C. That's why (type &
	 * IRQ_TYPE_EDGE_BOTH) will be managed in .irq_sync_unlock.
	 */

	अगर ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
		pctl->irq_toggle_edge[reg] |= mask;
	अन्यथा
		pctl->irq_toggle_edge[reg] &= mask;

	वापस 0;
पूर्ण

अटल व्योम sपंचांगfx_pinctrl_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);

	mutex_lock(&pctl->lock);
पूर्ण

अटल व्योम sपंचांगfx_pinctrl_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	/*
	 * In हाल of IRQ_TYPE_EDGE_BOTH), पढ़ो the current GPIO value
	 * (this couldn't be करोne in .irq_set_type because of atomic context)
	 * to set the right irq trigger type.
	 */
	अगर (pctl->irq_toggle_edge[reg] & mask) अणु
		अगर (sपंचांगfx_gpio_get(gpio_chip, data->hwirq))
			pctl->irq_gpi_type[reg] &= ~mask;
		अन्यथा
			pctl->irq_gpi_type[reg] |= mask;
	पूर्ण

	regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_EVT,
			  pctl->irq_gpi_evt, NR_GPIO_REGS);
	regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_TYPE,
			  pctl->irq_gpi_type, NR_GPIO_REGS);
	regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_SRC,
			  pctl->irq_gpi_src, NR_GPIO_REGS);

	mutex_unlock(&pctl->lock);
पूर्ण

अटल पूर्णांक sपंचांगfx_gpio_irq_request_resources(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	पूर्णांक ret;

	ret = sपंचांगfx_gpio_direction_input(gpio_chip, data->hwirq);
	अगर (ret)
		वापस ret;

	वापस gpiochip_reqres_irq(gpio_chip, data->hwirq);
पूर्ण

अटल व्योम sपंचांगfx_gpio_irq_release_resources(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);

	वापस gpiochip_relres_irq(gpio_chip, data->hwirq);
पूर्ण

अटल व्योम sपंचांगfx_pinctrl_irq_toggle_trigger(काष्ठा sपंचांगfx_pinctrl *pctl,
					     अचिन्हित पूर्णांक offset)
अणु
	u32 reg = get_reg(offset);
	u32 mask = get_mask(offset);
	पूर्णांक val;

	अगर (!(pctl->irq_toggle_edge[reg] & mask))
		वापस;

	val = sपंचांगfx_gpio_get(&pctl->gpio_chip, offset);
	अगर (val < 0)
		वापस;

	अगर (val) अणु
		pctl->irq_gpi_type[reg] &= mask;
		regmap_ग_लिखो_bits(pctl->sपंचांगfx->map,
				  STMFX_REG_IRQ_GPI_TYPE + reg,
				  mask, 0);

	पूर्ण अन्यथा अणु
		pctl->irq_gpi_type[reg] |= mask;
		regmap_ग_लिखो_bits(pctl->sपंचांगfx->map,
				  STMFX_REG_IRQ_GPI_TYPE + reg,
				  mask, mask);
	पूर्ण
पूर्ण

अटल irqवापस_t sपंचांगfx_pinctrl_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = (काष्ठा sपंचांगfx_pinctrl *)dev_id;
	काष्ठा gpio_chip *gc = &pctl->gpio_chip;
	u8 pending[NR_GPIO_REGS];
	u8 src[NR_GPIO_REGS] = अणु0, 0, 0पूर्ण;
	अचिन्हित दीर्घ n, status;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_PENDING,
			       &pending, NR_GPIO_REGS);
	अगर (ret)
		वापस IRQ_NONE;

	regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_SRC,
			  src, NR_GPIO_REGS);

	status = *(अचिन्हित दीर्घ *)pending;
	क्रम_each_set_bit(n, &status, gc->ngpio) अणु
		handle_nested_irq(irq_find_mapping(gc->irq.करोमुख्य, n));
		sपंचांगfx_pinctrl_irq_toggle_trigger(pctl, n);
	पूर्ण

	regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_SRC,
			  pctl->irq_gpi_src, NR_GPIO_REGS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_gpio_function_enable(काष्ठा sपंचांगfx_pinctrl *pctl)
अणु
	काष्ठा pinctrl_gpio_range *gpio_range;
	काष्ठा pinctrl_dev *pctl_dev = pctl->pctl_dev;
	u32 func = STMFX_FUNC_GPIO;

	pctl->gpio_valid_mask = GENMASK(15, 0);

	gpio_range = pinctrl_find_gpio_range_from_pin(pctl_dev, 16);
	अगर (gpio_range) अणु
		func |= STMFX_FUNC_ALTGPIO_LOW;
		pctl->gpio_valid_mask |= GENMASK(19, 16);
	पूर्ण

	gpio_range = pinctrl_find_gpio_range_from_pin(pctl_dev, 20);
	अगर (gpio_range) अणु
		func |= STMFX_FUNC_ALTGPIO_HIGH;
		pctl->gpio_valid_mask |= GENMASK(23, 20);
	पूर्ण

	वापस sपंचांगfx_function_enable(pctl->sपंचांगfx, func);
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sपंचांगfx_pinctrl *pctl;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक irq, ret;

	pctl = devm_kzalloc(sपंचांगfx->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctl);

	pctl->dev = &pdev->dev;
	pctl->sपंचांगfx = sपंचांगfx;

	अगर (!of_find_property(np, "gpio-ranges", शून्य)) अणु
		dev_err(pctl->dev, "missing required gpio-ranges property\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	mutex_init(&pctl->lock);

	/* Register pin controller */
	pctl->pctl_desc.name = "stmfx-pinctrl";
	pctl->pctl_desc.pctlops = &sपंचांगfx_pinctrl_ops;
	pctl->pctl_desc.confops = &sपंचांगfx_pinconf_ops;
	pctl->pctl_desc.pins = sपंचांगfx_pins;
	pctl->pctl_desc.npins = ARRAY_SIZE(sपंचांगfx_pins);
	pctl->pctl_desc.owner = THIS_MODULE;
	pctl->pctl_desc.link_consumers = true;

	ret = devm_pinctrl_रेजिस्टर_and_init(pctl->dev, &pctl->pctl_desc,
					     pctl, &pctl->pctl_dev);
	अगर (ret) अणु
		dev_err(pctl->dev, "pinctrl registration failed\n");
		वापस ret;
	पूर्ण

	ret = pinctrl_enable(pctl->pctl_dev);
	अगर (ret) अणु
		dev_err(pctl->dev, "pinctrl enable failed\n");
		वापस ret;
	पूर्ण

	/* Register gpio controller */
	pctl->gpio_chip.label = "stmfx-gpio";
	pctl->gpio_chip.parent = pctl->dev;
	pctl->gpio_chip.get_direction = sपंचांगfx_gpio_get_direction;
	pctl->gpio_chip.direction_input = sपंचांगfx_gpio_direction_input;
	pctl->gpio_chip.direction_output = sपंचांगfx_gpio_direction_output;
	pctl->gpio_chip.get = sपंचांगfx_gpio_get;
	pctl->gpio_chip.set = sपंचांगfx_gpio_set;
	pctl->gpio_chip.set_config = gpiochip_generic_config;
	pctl->gpio_chip.base = -1;
	pctl->gpio_chip.ngpio = pctl->pctl_desc.npins;
	pctl->gpio_chip.can_sleep = true;
	pctl->gpio_chip.of_node = np;

	pctl->irq_chip.name = dev_name(pctl->dev);
	pctl->irq_chip.irq_mask = sपंचांगfx_pinctrl_irq_mask;
	pctl->irq_chip.irq_unmask = sपंचांगfx_pinctrl_irq_unmask;
	pctl->irq_chip.irq_set_type = sपंचांगfx_pinctrl_irq_set_type;
	pctl->irq_chip.irq_bus_lock = sपंचांगfx_pinctrl_irq_bus_lock;
	pctl->irq_chip.irq_bus_sync_unlock = sपंचांगfx_pinctrl_irq_bus_sync_unlock;
	pctl->irq_chip.irq_request_resources = sपंचांगfx_gpio_irq_request_resources;
	pctl->irq_chip.irq_release_resources = sपंचांगfx_gpio_irq_release_resources;

	girq = &pctl->gpio_chip.irq;
	girq->chip = &pctl->irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->thपढ़ोed = true;

	ret = devm_gpiochip_add_data(pctl->dev, &pctl->gpio_chip, pctl);
	अगर (ret) अणु
		dev_err(pctl->dev, "gpio_chip registration failed\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगfx_pinctrl_gpio_function_enable(pctl);
	अगर (ret)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(pctl->dev, irq, शून्य,
					sपंचांगfx_pinctrl_irq_thपढ़ो_fn,
					IRQF_ONESHOT,
					pctl->irq_chip.name, pctl);
	अगर (ret) अणु
		dev_err(pctl->dev, "cannot request irq%d\n", irq);
		वापस ret;
	पूर्ण

	dev_info(pctl->dev,
		 "%ld GPIOs available\n", hweight_दीर्घ(pctl->gpio_valid_mask));

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = dev_get_drvdata(pdev->dev.parent);

	वापस sपंचांगfx_function_disable(sपंचांगfx,
				      STMFX_FUNC_GPIO |
				      STMFX_FUNC_ALTGPIO_LOW |
				      STMFX_FUNC_ALTGPIO_HIGH);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांगfx_pinctrl_backup_regs(काष्ठा sपंचांगfx_pinctrl *pctl)
अणु
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_STATE,
			       &pctl->bkp_gpio_state, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_पढ़ो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_सूची,
			       &pctl->bkp_gpio_dir, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_पढ़ो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_TYPE,
			       &pctl->bkp_gpio_type, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_पढ़ो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_PUPD,
			       &pctl->bkp_gpio_pupd, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_restore_regs(काष्ठा sपंचांगfx_pinctrl *pctl)
अणु
	पूर्णांक ret;

	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_सूची,
				pctl->bkp_gpio_dir, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_TYPE,
				pctl->bkp_gpio_type, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_GPIO_PUPD,
				pctl->bkp_gpio_pupd, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_GPO_SET,
				pctl->bkp_gpio_state, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_EVT,
				pctl->irq_gpi_evt, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_TYPE,
				pctl->irq_gpi_type, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;
	ret = regmap_bulk_ग_लिखो(pctl->sपंचांगfx->map, STMFX_REG_IRQ_GPI_SRC,
				pctl->irq_gpi_src, NR_GPIO_REGS);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sपंचांगfx_pinctrl_backup_regs(pctl);
	अगर (ret) अणु
		dev_err(pctl->dev, "registers backup failure\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfx_pinctrl *pctl = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sपंचांगfx_pinctrl_restore_regs(pctl);
	अगर (ret) अणु
		dev_err(pctl->dev, "registers restoration failure\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांगfx_pinctrl_dev_pm_ops,
			 sपंचांगfx_pinctrl_suspend, sपंचांगfx_pinctrl_resume);

अटल स्थिर काष्ठा of_device_id sपंचांगfx_pinctrl_of_match[] = अणु
	अणु .compatible = "st,stmfx-0300-pinctrl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगfx_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver sपंचांगfx_pinctrl_driver = अणु
	.driver = अणु
		.name = "stmfx-pinctrl",
		.of_match_table = sपंचांगfx_pinctrl_of_match,
		.pm = &sपंचांगfx_pinctrl_dev_pm_ops,
	पूर्ण,
	.probe = sपंचांगfx_pinctrl_probe,
	.हटाओ = sपंचांगfx_pinctrl_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांगfx_pinctrl_driver);

MODULE_DESCRIPTION("STMFX pinctrl/GPIO driver");
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_LICENSE("GPL v2");
