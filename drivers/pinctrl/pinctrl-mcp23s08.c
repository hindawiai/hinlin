<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* MCP23S08 SPI/I2C GPIO driver */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "pinctrl-mcp23s08.h"

/* Registers are all 8 bits wide.
 *
 * The mcp23s17 has twice as many bits, and can be configured to work
 * with either 16 bit रेजिस्टरs or with two adjacent 8 bit banks.
 */
#घोषणा MCP_IOसूची	0x00		/* init/reset:  all ones */
#घोषणा MCP_IPOL	0x01
#घोषणा MCP_GPINTEN	0x02
#घोषणा MCP_DEFVAL	0x03
#घोषणा MCP_INTCON	0x04
#घोषणा MCP_IOCON	0x05
#	define IOCON_MIRROR	(1 << 6)
#	define IOCON_SEQOP	(1 << 5)
#	define IOCON_HAEN	(1 << 3)
#	define IOCON_ODR	(1 << 2)
#	define IOCON_INTPOL	(1 << 1)
#	define IOCON_INTCC	(1)
#घोषणा MCP_GPPU	0x06
#घोषणा MCP_INTF	0x07
#घोषणा MCP_INTCAP	0x08
#घोषणा MCP_GPIO	0x09
#घोषणा MCP_OLAT	0x0a

अटल स्थिर काष्ठा reg_शेष mcp23x08_शेषs[] = अणु
	अणु.reg = MCP_IOसूची,		.def = 0xffपूर्ण,
	अणु.reg = MCP_IPOL,		.def = 0x00पूर्ण,
	अणु.reg = MCP_GPINTEN,		.def = 0x00पूर्ण,
	अणु.reg = MCP_DEFVAL,		.def = 0x00पूर्ण,
	अणु.reg = MCP_INTCON,		.def = 0x00पूर्ण,
	अणु.reg = MCP_IOCON,		.def = 0x00पूर्ण,
	अणु.reg = MCP_GPPU,		.def = 0x00पूर्ण,
	अणु.reg = MCP_OLAT,		.def = 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range mcp23x08_अस्थिर_range = अणु
	.range_min = MCP_INTF,
	.range_max = MCP_GPIO,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp23x08_अस्थिर_table = अणु
	.yes_ranges = &mcp23x08_अस्थिर_range,
	.n_yes_ranges = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_range mcp23x08_precious_range = अणु
	.range_min = MCP_GPIO,
	.range_max = MCP_GPIO,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp23x08_precious_table = अणु
	.yes_ranges = &mcp23x08_precious_range,
	.n_yes_ranges = 1,
पूर्ण;

स्थिर काष्ठा regmap_config mcp23x08_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_stride = 1,
	.अस्थिर_table = &mcp23x08_अस्थिर_table,
	.precious_table = &mcp23x08_precious_table,
	.reg_शेषs = mcp23x08_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(mcp23x08_शेषs),
	.cache_type = REGCACHE_FLAT,
	.max_रेजिस्टर = MCP_OLAT,
पूर्ण;
EXPORT_SYMBOL_GPL(mcp23x08_regmap);

अटल स्थिर काष्ठा reg_शेष mcp23x17_शेषs[] = अणु
	अणु.reg = MCP_IOसूची << 1,		.def = 0xffffपूर्ण,
	अणु.reg = MCP_IPOL << 1,		.def = 0x0000पूर्ण,
	अणु.reg = MCP_GPINTEN << 1,	.def = 0x0000पूर्ण,
	अणु.reg = MCP_DEFVAL << 1,	.def = 0x0000पूर्ण,
	अणु.reg = MCP_INTCON << 1,	.def = 0x0000पूर्ण,
	अणु.reg = MCP_IOCON << 1,		.def = 0x0000पूर्ण,
	अणु.reg = MCP_GPPU << 1,		.def = 0x0000पूर्ण,
	अणु.reg = MCP_OLAT << 1,		.def = 0x0000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range mcp23x17_अस्थिर_range = अणु
	.range_min = MCP_INTF << 1,
	.range_max = MCP_GPIO << 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp23x17_अस्थिर_table = अणु
	.yes_ranges = &mcp23x17_अस्थिर_range,
	.n_yes_ranges = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_range mcp23x17_precious_range = अणु
	.range_min = MCP_INTCAP << 1,
	.range_max = MCP_GPIO << 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp23x17_precious_table = अणु
	.yes_ranges = &mcp23x17_precious_range,
	.n_yes_ranges = 1,
पूर्ण;

स्थिर काष्ठा regmap_config mcp23x17_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.reg_stride = 2,
	.max_रेजिस्टर = MCP_OLAT << 1,
	.अस्थिर_table = &mcp23x17_अस्थिर_table,
	.precious_table = &mcp23x17_precious_table,
	.reg_शेषs = mcp23x17_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(mcp23x17_शेषs),
	.cache_type = REGCACHE_FLAT,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;
EXPORT_SYMBOL_GPL(mcp23x17_regmap);

अटल पूर्णांक mcp_पढ़ो(काष्ठा mcp23s08 *mcp, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	वापस regmap_पढ़ो(mcp->regmap, reg << mcp->reg_shअगरt, val);
पूर्ण

अटल पूर्णांक mcp_ग_लिखो(काष्ठा mcp23s08 *mcp, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	वापस regmap_ग_लिखो(mcp->regmap, reg << mcp->reg_shअगरt, val);
पूर्ण

अटल पूर्णांक mcp_set_mask(काष्ठा mcp23s08 *mcp, अचिन्हित पूर्णांक reg,
		       अचिन्हित पूर्णांक mask, bool enabled)
अणु
	u16 val  = enabled ? 0xffff : 0x0000;
	वापस regmap_update_bits(mcp->regmap, reg << mcp->reg_shअगरt,
				  mask, val);
पूर्ण

अटल पूर्णांक mcp_set_bit(काष्ठा mcp23s08 *mcp, अचिन्हित पूर्णांक reg,
		       अचिन्हित पूर्णांक pin, bool enabled)
अणु
	u16 mask = BIT(pin);
	वापस mcp_set_mask(mcp, reg, mask, enabled);
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc mcp23x08_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc mcp23x17_pins[] = अणु
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
पूर्ण;

अटल पूर्णांक mcp_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *mcp_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित पूर्णांक group)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक mcp_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group,
					स्थिर अचिन्हित पूर्णांक **pins,
					अचिन्हित पूर्णांक *num_pins)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mcp_pinctrl_ops = अणु
	.get_groups_count = mcp_pinctrl_get_groups_count,
	.get_group_name = mcp_pinctrl_get_group_name,
	.get_group_pins = mcp_pinctrl_get_group_pins,
#अगर_घोषित CONFIG_OF
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mcp_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा mcp23s08 *mcp = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक data, status;
	पूर्णांक ret;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = mcp_पढ़ो(mcp, MCP_GPPU, &data);
		अगर (ret < 0)
			वापस ret;
		status = (data & BIT(pin)) ? 1 : 0;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = 0;

	वापस status ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक mcp_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा mcp23s08 *mcp = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 arg;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = mcp_set_bit(mcp, MCP_GPPU, pin, arg);
			अवरोध;
		शेष:
			dev_dbg(mcp->dev, "Invalid config param %04x\n", param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mcp_pinconf_ops = अणु
	.pin_config_get = mcp_pinconf_get,
	.pin_config_set = mcp_pinconf_set,
	.is_generic = true,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक mcp23s08_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा mcp23s08	*mcp = gpiochip_get_data(chip);
	पूर्णांक status;

	mutex_lock(&mcp->lock);
	status = mcp_set_bit(mcp, MCP_IOसूची, offset, true);
	mutex_unlock(&mcp->lock);

	वापस status;
पूर्ण

अटल पूर्णांक mcp23s08_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा mcp23s08	*mcp = gpiochip_get_data(chip);
	पूर्णांक status, ret;

	mutex_lock(&mcp->lock);

	/* REVISIT पढ़ोing this clears any IRQ ... */
	ret = mcp_पढ़ो(mcp, MCP_GPIO, &status);
	अगर (ret < 0)
		status = 0;
	अन्यथा अणु
		mcp->cached_gpio = status;
		status = !!(status & (1 << offset));
	पूर्ण

	mutex_unlock(&mcp->lock);
	वापस status;
पूर्ण

अटल पूर्णांक __mcp23s08_set(काष्ठा mcp23s08 *mcp, अचिन्हित mask, bool value)
अणु
	वापस mcp_set_mask(mcp, MCP_OLAT, mask, value);
पूर्ण

अटल व्योम mcp23s08_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा mcp23s08	*mcp = gpiochip_get_data(chip);
	अचिन्हित mask = BIT(offset);

	mutex_lock(&mcp->lock);
	__mcp23s08_set(mcp, mask, !!value);
	mutex_unlock(&mcp->lock);
पूर्ण

अटल पूर्णांक
mcp23s08_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा mcp23s08	*mcp = gpiochip_get_data(chip);
	अचिन्हित mask = BIT(offset);
	पूर्णांक status;

	mutex_lock(&mcp->lock);
	status = __mcp23s08_set(mcp, mask, value);
	अगर (status == 0) अणु
		status = mcp_set_mask(mcp, MCP_IOसूची, mask, false);
	पूर्ण
	mutex_unlock(&mcp->lock);
	वापस status;
पूर्ण

/*----------------------------------------------------------------------*/
अटल irqवापस_t mcp23s08_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mcp23s08 *mcp = data;
	पूर्णांक पूर्णांकcap, पूर्णांकcon, पूर्णांकf, i, gpio, gpio_orig, पूर्णांकcap_mask, defval;
	अचिन्हित पूर्णांक child_irq;
	bool पूर्णांकf_set, पूर्णांकcap_changed, gpio_bit_changed,
		defval_changed, gpio_set;

	mutex_lock(&mcp->lock);
	अगर (mcp_पढ़ो(mcp, MCP_INTF, &पूर्णांकf))
		जाओ unlock;

	अगर (mcp_पढ़ो(mcp, MCP_INTCAP, &पूर्णांकcap))
		जाओ unlock;

	अगर (mcp_पढ़ो(mcp, MCP_INTCON, &पूर्णांकcon))
		जाओ unlock;

	अगर (mcp_पढ़ो(mcp, MCP_DEFVAL, &defval))
		जाओ unlock;

	/* This clears the पूर्णांकerrupt(configurable on S18) */
	अगर (mcp_पढ़ो(mcp, MCP_GPIO, &gpio))
		जाओ unlock;

	gpio_orig = mcp->cached_gpio;
	mcp->cached_gpio = gpio;
	mutex_unlock(&mcp->lock);

	अगर (पूर्णांकf == 0) अणु
		/* There is no पूर्णांकerrupt pending */
		वापस IRQ_HANDLED;
	पूर्ण

	dev_dbg(mcp->chip.parent,
		"intcap 0x%04X intf 0x%04X gpio_orig 0x%04X gpio 0x%04X\n",
		पूर्णांकcap, पूर्णांकf, gpio_orig, gpio);

	क्रम (i = 0; i < mcp->chip.ngpio; i++) अणु
		/* We must check all of the inमाला_दो on the chip,
		 * otherwise we may not notice a change on >=2 pins.
		 *
		 * On at least the mcp23s17, INTCAP is only updated
		 * one byte at a समय(INTCAPA and INTCAPB are
		 * not written to at the same समय - only on a per-bank
		 * basis).
		 *
		 * INTF only contains the single bit that caused the
		 * पूर्णांकerrupt per-bank.  On the mcp23s17, there is
		 * INTFA and INTFB.  If two pins are changed on the A
		 * side at the same समय, INTF will only have one bit
		 * set.  If one pin on the A side and one pin on the B
		 * side are changed at the same समय, INTF will have
		 * two bits set.  Thus, INTF can't be the only check
		 * to see अगर the input has changed.
		 */

		पूर्णांकf_set = पूर्णांकf & BIT(i);
		अगर (i < 8 && पूर्णांकf_set)
			पूर्णांकcap_mask = 0x00FF;
		अन्यथा अगर (i >= 8 && पूर्णांकf_set)
			पूर्णांकcap_mask = 0xFF00;
		अन्यथा
			पूर्णांकcap_mask = 0x00;

		पूर्णांकcap_changed = (पूर्णांकcap_mask &
			(पूर्णांकcap & BIT(i))) !=
			(पूर्णांकcap_mask & (BIT(i) & gpio_orig));
		gpio_set = BIT(i) & gpio;
		gpio_bit_changed = (BIT(i) & gpio_orig) !=
			(BIT(i) & gpio);
		defval_changed = (BIT(i) & पूर्णांकcon) &&
			((BIT(i) & gpio) !=
			(BIT(i) & defval));

		अगर (((gpio_bit_changed || पूर्णांकcap_changed) &&
			(BIT(i) & mcp->irq_rise) && gpio_set) ||
		    ((gpio_bit_changed || पूर्णांकcap_changed) &&
			(BIT(i) & mcp->irq_fall) && !gpio_set) ||
		    defval_changed) अणु
			child_irq = irq_find_mapping(mcp->chip.irq.करोमुख्य, i);
			handle_nested_irq(child_irq);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;

unlock:
	mutex_unlock(&mcp->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mcp23s08_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा mcp23s08 *mcp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pos = data->hwirq;

	mcp_set_bit(mcp, MCP_GPINTEN, pos, false);
पूर्ण

अटल व्योम mcp23s08_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा mcp23s08 *mcp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pos = data->hwirq;

	mcp_set_bit(mcp, MCP_GPINTEN, pos, true);
पूर्ण

अटल पूर्णांक mcp23s08_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा mcp23s08 *mcp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pos = data->hwirq;

	अगर ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) अणु
		mcp_set_bit(mcp, MCP_INTCON, pos, false);
		mcp->irq_rise |= BIT(pos);
		mcp->irq_fall |= BIT(pos);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_EDGE_RISING) अणु
		mcp_set_bit(mcp, MCP_INTCON, pos, false);
		mcp->irq_rise |= BIT(pos);
		mcp->irq_fall &= ~BIT(pos);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_EDGE_FALLING) अणु
		mcp_set_bit(mcp, MCP_INTCON, pos, false);
		mcp->irq_rise &= ~BIT(pos);
		mcp->irq_fall |= BIT(pos);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_LEVEL_HIGH) अणु
		mcp_set_bit(mcp, MCP_INTCON, pos, true);
		mcp_set_bit(mcp, MCP_DEFVAL, pos, false);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_LEVEL_LOW) अणु
		mcp_set_bit(mcp, MCP_INTCON, pos, true);
		mcp_set_bit(mcp, MCP_DEFVAL, pos, true);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम mcp23s08_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा mcp23s08 *mcp = gpiochip_get_data(gc);

	mutex_lock(&mcp->lock);
	regcache_cache_only(mcp->regmap, true);
पूर्ण

अटल व्योम mcp23s08_irq_bus_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा mcp23s08 *mcp = gpiochip_get_data(gc);

	regcache_cache_only(mcp->regmap, false);
	regcache_sync(mcp->regmap);

	mutex_unlock(&mcp->lock);
पूर्ण

अटल पूर्णांक mcp23s08_irq_setup(काष्ठा mcp23s08 *mcp)
अणु
	काष्ठा gpio_chip *chip = &mcp->chip;
	पूर्णांक err;
	अचिन्हित दीर्घ irqflags = IRQF_ONESHOT | IRQF_SHARED;

	अगर (mcp->irq_active_high)
		irqflags |= IRQF_TRIGGER_HIGH;
	अन्यथा
		irqflags |= IRQF_TRIGGER_LOW;

	err = devm_request_thपढ़ोed_irq(chip->parent, mcp->irq, शून्य,
					mcp23s08_irq,
					irqflags, dev_name(chip->parent), mcp);
	अगर (err != 0) अणु
		dev_err(chip->parent, "unable to request IRQ#%d: %d\n",
			mcp->irq, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

पूर्णांक mcp23s08_probe_one(काष्ठा mcp23s08 *mcp, काष्ठा device *dev,
		       अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक base)
अणु
	पूर्णांक status, ret;
	bool mirror = false;
	bool खोलो_drain = false;

	mutex_init(&mcp->lock);

	mcp->dev = dev;
	mcp->addr = addr;

	mcp->irq_active_high = false;
	mcp->irq_chip.name = dev_name(dev);
	mcp->irq_chip.irq_mask = mcp23s08_irq_mask;
	mcp->irq_chip.irq_unmask = mcp23s08_irq_unmask;
	mcp->irq_chip.irq_set_type = mcp23s08_irq_set_type;
	mcp->irq_chip.irq_bus_lock = mcp23s08_irq_bus_lock;
	mcp->irq_chip.irq_bus_sync_unlock = mcp23s08_irq_bus_unlock;

	mcp->chip.direction_input = mcp23s08_direction_input;
	mcp->chip.get = mcp23s08_get;
	mcp->chip.direction_output = mcp23s08_direction_output;
	mcp->chip.set = mcp23s08_set;
#अगर_घोषित CONFIG_OF_GPIO
	mcp->chip.of_gpio_n_cells = 2;
	mcp->chip.of_node = dev->of_node;
#पूर्ण_अगर

	mcp->chip.base = base;
	mcp->chip.can_sleep = true;
	mcp->chip.parent = dev;
	mcp->chip.owner = THIS_MODULE;

	/* verअगरy MCP_IOCON.SEQOP = 0, so sequential पढ़ोs work,
	 * and MCP_IOCON.HAEN = 1, so we work with all chips.
	 */

	ret = mcp_पढ़ो(mcp, MCP_IOCON, &status);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret, "can't identify chip %d\n", addr);

	mcp->irq_controller =
		device_property_पढ़ो_bool(dev, "interrupt-controller");
	अगर (mcp->irq && mcp->irq_controller) अणु
		mcp->irq_active_high =
			device_property_पढ़ो_bool(dev,
					      "microchip,irq-active-high");

		mirror = device_property_पढ़ो_bool(dev, "microchip,irq-mirror");
		खोलो_drain = device_property_पढ़ो_bool(dev, "drive-open-drain");
	पूर्ण

	अगर ((status & IOCON_SEQOP) || !(status & IOCON_HAEN) || mirror ||
	     mcp->irq_active_high || खोलो_drain) अणु
		/* mcp23s17 has IOCON twice, make sure they are in sync */
		status &= ~(IOCON_SEQOP | (IOCON_SEQOP << 8));
		status |= IOCON_HAEN | (IOCON_HAEN << 8);
		अगर (mcp->irq_active_high)
			status |= IOCON_INTPOL | (IOCON_INTPOL << 8);
		अन्यथा
			status &= ~(IOCON_INTPOL | (IOCON_INTPOL << 8));

		अगर (mirror)
			status |= IOCON_MIRROR | (IOCON_MIRROR << 8);

		अगर (खोलो_drain)
			status |= IOCON_ODR | (IOCON_ODR << 8);

		अगर (type == MCP_TYPE_S18 || type == MCP_TYPE_018)
			status |= IOCON_INTCC | (IOCON_INTCC << 8);

		ret = mcp_ग_लिखो(mcp, MCP_IOCON, status);
		अगर (ret < 0)
			वापस dev_err_probe(dev, ret, "can't write IOCON %d\n", addr);
	पूर्ण

	अगर (mcp->irq && mcp->irq_controller) अणु
		काष्ठा gpio_irq_chip *girq = &mcp->chip.irq;

		girq->chip = &mcp->irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		girq->thपढ़ोed = true;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &mcp->chip, mcp);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret, "can't add GPIO chip\n");

	mcp->pinctrl_desc.pctlops = &mcp_pinctrl_ops;
	mcp->pinctrl_desc.confops = &mcp_pinconf_ops;
	mcp->pinctrl_desc.npins = mcp->chip.ngpio;
	अगर (mcp->pinctrl_desc.npins == 8)
		mcp->pinctrl_desc.pins = mcp23x08_pins;
	अन्यथा अगर (mcp->pinctrl_desc.npins == 16)
		mcp->pinctrl_desc.pins = mcp23x17_pins;
	mcp->pinctrl_desc.owner = THIS_MODULE;

	mcp->pctldev = devm_pinctrl_रेजिस्टर(dev, &mcp->pinctrl_desc, mcp);
	अगर (IS_ERR(mcp->pctldev))
		वापस dev_err_probe(dev, PTR_ERR(mcp->pctldev), "can't register controller\n");

	अगर (mcp->irq) अणु
		ret = mcp23s08_irq_setup(mcp);
		अगर (ret)
			वापस dev_err_probe(dev, ret, "can't setup IRQ\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mcp23s08_probe_one);

MODULE_LICENSE("GPL");
