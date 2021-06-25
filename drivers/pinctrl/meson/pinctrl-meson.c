<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pin controller and GPIO driver क्रम Amlogic Meson SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

/*
 * The available pins are organized in banks (A,B,C,D,E,X,Y,Z,AO,
 * BOOT,CARD क्रम meson6, X,Y,DV,H,Z,AO,BOOT,CARD क्रम meson8 and
 * X,Y,DV,H,AO,BOOT,CARD,DIF क्रम meson8b) and each bank has a
 * variable number of pins.
 *
 * The AO bank is special because it beदीर्घs to the Always-On घातer
 * करोमुख्य which can't be घातered off; the bank also uses a set of
 * रेजिस्टरs dअगरferent from the other banks.
 *
 * For each pin controller there are 4 dअगरferent रेजिस्टर ranges that
 * control the following properties of the pins:
 *  1) pin muxing
 *  2) pull enable/disable
 *  3) pull up/करोwn
 *  4) GPIO direction, output value, input value
 *
 * In some हालs the रेजिस्टर ranges क्रम pull enable and pull
 * direction are the same and thus there are only 3 रेजिस्टर ranges.
 *
 * Since Meson G12A SoC, the ao रेजिस्टर ranges क्रम gpio, pull enable
 * and pull direction are the same, so there are only 2 रेजिस्टर ranges.
 *
 * For the pull and GPIO configuration every bank uses a contiguous
 * set of bits in the रेजिस्टर sets described above; the same रेजिस्टर
 * can be shared by more banks with dअगरferent offsets.
 *
 * In addition to this there are some रेजिस्टरs shared between all
 * banks that control the IRQ functionality. This feature is not
 * supported at the moment by the driver.
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/seq_file.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-meson.h"

अटल स्थिर अचिन्हित पूर्णांक meson_bit_strides[] = अणु
	1, 1, 1, 1, 1, 2, 1
पूर्ण;

/**
 * meson_get_bank() - find the bank containing a given pin
 *
 * @pc:		the pinctrl instance
 * @pin:	the pin number
 * @bank:	the found bank
 *
 * Return:	0 on success, a negative value on error
 */
अटल पूर्णांक meson_get_bank(काष्ठा meson_pinctrl *pc, अचिन्हित पूर्णांक pin,
			  काष्ठा meson_bank **bank)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pc->data->num_banks; i++) अणु
		अगर (pin >= pc->data->banks[i].first &&
		    pin <= pc->data->banks[i].last) अणु
			*bank = &pc->data->banks[i];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * meson_calc_reg_and_bit() - calculate रेजिस्टर and bit क्रम a pin
 *
 * @bank:	the bank containing the pin
 * @pin:	the pin number
 * @reg_type:	the type of रेजिस्टर needed (pull-enable, pull, etc...)
 * @reg:	the computed रेजिस्टर offset
 * @bit:	the computed bit
 */
अटल व्योम meson_calc_reg_and_bit(काष्ठा meson_bank *bank, अचिन्हित पूर्णांक pin,
				   क्रमागत meson_reg_type reg_type,
				   अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *bit)
अणु
	काष्ठा meson_reg_desc *desc = &bank->regs[reg_type];

	*bit = (desc->bit + pin - bank->first) * meson_bit_strides[reg_type];
	*reg = (desc->reg + (*bit / 32)) * 4;
	*bit &= 0x1f;
पूर्ण

अटल पूर्णांक meson_get_groups_count(काष्ठा pinctrl_dev *pcdev)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	वापस pc->data->num_groups;
पूर्ण

अटल स्थिर अक्षर *meson_get_group_name(काष्ठा pinctrl_dev *pcdev,
					अचिन्हित selector)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	वापस pc->data->groups[selector].name;
पूर्ण

अटल पूर्णांक meson_get_group_pins(काष्ठा pinctrl_dev *pcdev, अचिन्हित selector,
				स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	*pins = pc->data->groups[selector].pins;
	*num_pins = pc->data->groups[selector].num_pins;

	वापस 0;
पूर्ण

अटल व्योम meson_pin_dbg_show(काष्ठा pinctrl_dev *pcdev, काष्ठा seq_file *s,
			       अचिन्हित offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pcdev->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops meson_pctrl_ops = अणु
	.get_groups_count	= meson_get_groups_count,
	.get_group_name		= meson_get_group_name,
	.get_group_pins		= meson_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
	.pin_dbg_show		= meson_pin_dbg_show,
पूर्ण;

पूर्णांक meson_pmx_get_funcs_count(काष्ठा pinctrl_dev *pcdev)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	वापस pc->data->num_funcs;
पूर्ण
EXPORT_SYMBOL_GPL(meson_pmx_get_funcs_count);

स्थिर अक्षर *meson_pmx_get_func_name(काष्ठा pinctrl_dev *pcdev,
				    अचिन्हित selector)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	वापस pc->data->funcs[selector].name;
पूर्ण
EXPORT_SYMBOL_GPL(meson_pmx_get_func_name);

पूर्णांक meson_pmx_get_groups(काष्ठा pinctrl_dev *pcdev, अचिन्हित selector,
			 स्थिर अक्षर * स्थिर **groups,
			 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	*groups = pc->data->funcs[selector].groups;
	*num_groups = pc->data->funcs[selector].num_groups;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_pmx_get_groups);

अटल पूर्णांक meson_pinconf_set_gpio_bit(काष्ठा meson_pinctrl *pc,
				      अचिन्हित पूर्णांक pin,
				      अचिन्हित पूर्णांक reg_type,
				      bool arg)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit;
	पूर्णांक ret;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, reg_type, &reg, &bit);
	वापस regmap_update_bits(pc->reg_gpio, reg, BIT(bit),
				  arg ? BIT(bit) : 0);
पूर्ण

अटल पूर्णांक meson_pinconf_get_gpio_bit(काष्ठा meson_pinctrl *pc,
				      अचिन्हित पूर्णांक pin,
				      अचिन्हित पूर्णांक reg_type)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit, val;
	पूर्णांक ret;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, reg_type, &reg, &bit);
	ret = regmap_पढ़ो(pc->reg_gpio, reg, &val);
	अगर (ret)
		वापस ret;

	वापस BIT(bit) & val ? 1 : 0;
पूर्ण

अटल पूर्णांक meson_pinconf_set_output(काष्ठा meson_pinctrl *pc,
				    अचिन्हित पूर्णांक pin,
				    bool out)
अणु
	वापस meson_pinconf_set_gpio_bit(pc, pin, REG_सूची, !out);
पूर्ण

अटल पूर्णांक meson_pinconf_get_output(काष्ठा meson_pinctrl *pc,
				    अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret = meson_pinconf_get_gpio_bit(pc, pin, REG_सूची);

	अगर (ret < 0)
		वापस ret;

	वापस !ret;
पूर्ण

अटल पूर्णांक meson_pinconf_set_drive(काष्ठा meson_pinctrl *pc,
				   अचिन्हित पूर्णांक pin,
				   bool high)
अणु
	वापस meson_pinconf_set_gpio_bit(pc, pin, REG_OUT, high);
पूर्ण

अटल पूर्णांक meson_pinconf_get_drive(काष्ठा meson_pinctrl *pc,
				   अचिन्हित पूर्णांक pin)
अणु
	वापस meson_pinconf_get_gpio_bit(pc, pin, REG_OUT);
पूर्ण

अटल पूर्णांक meson_pinconf_set_output_drive(काष्ठा meson_pinctrl *pc,
					  अचिन्हित पूर्णांक pin,
					  bool high)
अणु
	पूर्णांक ret;

	ret = meson_pinconf_set_output(pc, pin, true);
	अगर (ret)
		वापस ret;

	वापस meson_pinconf_set_drive(pc, pin, high);
पूर्ण

अटल पूर्णांक meson_pinconf_disable_bias(काष्ठा meson_pinctrl *pc,
				      अचिन्हित पूर्णांक pin)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit = 0;
	पूर्णांक ret;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_PULLEN, &reg, &bit);
	ret = regmap_update_bits(pc->reg_pullen, reg, BIT(bit), 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_enable_bias(काष्ठा meson_pinctrl *pc, अचिन्हित पूर्णांक pin,
				     bool pull_up)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit, val = 0;
	पूर्णांक ret;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_PULL, &reg, &bit);
	अगर (pull_up)
		val = BIT(bit);

	ret = regmap_update_bits(pc->reg_pull, reg, BIT(bit), val);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_PULLEN, &reg, &bit);
	ret = regmap_update_bits(pc->reg_pullen, reg, BIT(bit),	BIT(bit));
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_set_drive_strength(काष्ठा meson_pinctrl *pc,
					    अचिन्हित पूर्णांक pin,
					    u16 drive_strength_ua)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit, ds_val;
	पूर्णांक ret;

	अगर (!pc->reg_ds) अणु
		dev_err(pc->dev, "drive-strength not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_DS, &reg, &bit);

	अगर (drive_strength_ua <= 500) अणु
		ds_val = MESON_PINCONF_DRV_500UA;
	पूर्ण अन्यथा अगर (drive_strength_ua <= 2500) अणु
		ds_val = MESON_PINCONF_DRV_2500UA;
	पूर्ण अन्यथा अगर (drive_strength_ua <= 3000) अणु
		ds_val = MESON_PINCONF_DRV_3000UA;
	पूर्ण अन्यथा अगर (drive_strength_ua <= 4000) अणु
		ds_val = MESON_PINCONF_DRV_4000UA;
	पूर्ण अन्यथा अणु
		dev_warn_once(pc->dev,
			      "pin %u: invalid drive-strength : %d , default to 4mA\n",
			      pin, drive_strength_ua);
		ds_val = MESON_PINCONF_DRV_4000UA;
	पूर्ण

	ret = regmap_update_bits(pc->reg_ds, reg, 0x3 << bit, ds_val << bit);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_set(काष्ठा pinctrl_dev *pcdev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक arg = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_DRIVE_STRENGTH_UA:
		हाल PIN_CONFIG_OUTPUT_ENABLE:
		हाल PIN_CONFIG_OUTPUT:
			arg = pinconf_to_config_argument(configs[i]);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = meson_pinconf_disable_bias(pc, pin);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = meson_pinconf_enable_bias(pc, pin, true);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = meson_pinconf_enable_bias(pc, pin, false);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH_UA:
			ret = meson_pinconf_set_drive_strength(pc, pin, arg);
			अवरोध;
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			ret = meson_pinconf_set_output(pc, pin, arg);
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			ret = meson_pinconf_set_output_drive(pc, pin, arg);
			अवरोध;
		शेष:
			ret = -ENOTSUPP;
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_get_pull(काष्ठा meson_pinctrl *pc, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit, val;
	पूर्णांक ret, conf;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_PULLEN, &reg, &bit);

	ret = regmap_पढ़ो(pc->reg_pullen, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & BIT(bit))) अणु
		conf = PIN_CONFIG_BIAS_DISABLE;
	पूर्ण अन्यथा अणु
		meson_calc_reg_and_bit(bank, pin, REG_PULL, &reg, &bit);

		ret = regmap_पढ़ो(pc->reg_pull, reg, &val);
		अगर (ret)
			वापस ret;

		अगर (val & BIT(bit))
			conf = PIN_CONFIG_BIAS_PULL_UP;
		अन्यथा
			conf = PIN_CONFIG_BIAS_PULL_DOWN;
	पूर्ण

	वापस conf;
पूर्ण

अटल पूर्णांक meson_pinconf_get_drive_strength(काष्ठा meson_pinctrl *pc,
					    अचिन्हित पूर्णांक pin,
					    u16 *drive_strength_ua)
अणु
	काष्ठा meson_bank *bank;
	अचिन्हित पूर्णांक reg, bit;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!pc->reg_ds)
		वापस -ENOTSUPP;

	ret = meson_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, pin, REG_DS, &reg, &bit);

	ret = regmap_पढ़ो(pc->reg_ds, reg, &val);
	अगर (ret)
		वापस ret;

	चयन ((val >> bit) & 0x3) अणु
	हाल MESON_PINCONF_DRV_500UA:
		*drive_strength_ua = 500;
		अवरोध;
	हाल MESON_PINCONF_DRV_2500UA:
		*drive_strength_ua = 2500;
		अवरोध;
	हाल MESON_PINCONF_DRV_3000UA:
		*drive_strength_ua = 3000;
		अवरोध;
	हाल MESON_PINCONF_DRV_4000UA:
		*drive_strength_ua = 4000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_get(काष्ठा pinctrl_dev *pcdev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *config)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u16 arg;
	पूर्णांक ret;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (meson_pinconf_get_pull(pc, pin) == param)
			arg = 1;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH_UA:
		ret = meson_pinconf_get_drive_strength(pc, pin, &arg);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		ret = meson_pinconf_get_output(pc, pin);
		अगर (ret <= 0)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		ret = meson_pinconf_get_output(pc, pin);
		अगर (ret <= 0)
			वापस -EINVAL;

		ret = meson_pinconf_get_drive(pc, pin);
		अगर (ret < 0)
			वापस -EINVAL;

		arg = ret;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	dev_dbg(pc->dev, "pinconf for pin %u is %lu\n", pin, *config);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_group_set(काष्ठा pinctrl_dev *pcdev,
				   अचिन्हित पूर्णांक num_group,
				   अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	काष्ठा meson_pmx_group *group = &pc->data->groups[num_group];
	पूर्णांक i;

	dev_dbg(pc->dev, "set pinconf for group %s\n", group->name);

	क्रम (i = 0; i < group->num_pins; i++) अणु
		meson_pinconf_set(pcdev, group->pins[i], configs,
				  num_configs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pinconf_group_get(काष्ठा pinctrl_dev *pcdev,
				   अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops meson_pinconf_ops = अणु
	.pin_config_get		= meson_pinconf_get,
	.pin_config_set		= meson_pinconf_set,
	.pin_config_group_get	= meson_pinconf_group_get,
	.pin_config_group_set	= meson_pinconf_group_set,
	.is_generic		= true,
पूर्ण;

अटल पूर्णांक meson_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा meson_pinctrl *pc = gpiochip_get_data(chip);
	पूर्णांक ret;

	ret = meson_pinconf_get_output(pc, gpio);
	अगर (ret < 0)
		वापस ret;

	वापस ret ? GPIO_LINE_सूचीECTION_OUT : GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक meson_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस meson_pinconf_set_output(gpiochip_get_data(chip), gpio, false);
पूर्ण

अटल पूर्णांक meson_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				       पूर्णांक value)
अणु
	वापस meson_pinconf_set_output_drive(gpiochip_get_data(chip),
					      gpio, value);
पूर्ण

अटल व्योम meson_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित gpio, पूर्णांक value)
अणु
	meson_pinconf_set_drive(gpiochip_get_data(chip), gpio, value);
पूर्ण

अटल पूर्णांक meson_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा meson_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg, bit, val;
	काष्ठा meson_bank *bank;
	पूर्णांक ret;

	ret = meson_get_bank(pc, gpio, &bank);
	अगर (ret)
		वापस ret;

	meson_calc_reg_and_bit(bank, gpio, REG_IN, &reg, &bit);
	regmap_पढ़ो(pc->reg_gpio, reg, &val);

	वापस !!(val & BIT(bit));
पूर्ण

अटल पूर्णांक meson_gpiolib_रेजिस्टर(काष्ठा meson_pinctrl *pc)
अणु
	पूर्णांक ret;

	pc->chip.label = pc->data->name;
	pc->chip.parent = pc->dev;
	pc->chip.request = gpiochip_generic_request;
	pc->chip.मुक्त = gpiochip_generic_मुक्त;
	pc->chip.set_config = gpiochip_generic_config;
	pc->chip.get_direction = meson_gpio_get_direction;
	pc->chip.direction_input = meson_gpio_direction_input;
	pc->chip.direction_output = meson_gpio_direction_output;
	pc->chip.get = meson_gpio_get;
	pc->chip.set = meson_gpio_set;
	pc->chip.base = -1;
	pc->chip.ngpio = pc->data->num_pins;
	pc->chip.can_sleep = false;
	pc->chip.of_node = pc->of_node;
	pc->chip.of_gpio_n_cells = 2;

	ret = gpiochip_add_data(&pc->chip, pc);
	अगर (ret) अणु
		dev_err(pc->dev, "can't add gpio chip %s\n",
			pc->data->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा regmap_config meson_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल काष्ठा regmap *meson_map_resource(काष्ठा meson_pinctrl *pc,
					 काष्ठा device_node *node, अक्षर *name)
अणु
	काष्ठा resource res;
	व्योम __iomem *base;
	पूर्णांक i;

	i = of_property_match_string(node, "reg-names", name);
	अगर (of_address_to_resource(node, i, &res))
		वापस शून्य;

	base = devm_ioremap_resource(pc->dev, &res);
	अगर (IS_ERR(base))
		वापस ERR_CAST(base);

	meson_regmap_config.max_रेजिस्टर = resource_size(&res) - 4;
	meson_regmap_config.name = devm_kaप्र_लिखो(pc->dev, GFP_KERNEL,
						  "%pOFn-%s", node,
						  name);
	अगर (!meson_regmap_config.name)
		वापस ERR_PTR(-ENOMEM);

	वापस devm_regmap_init_mmio(pc->dev, base, &meson_regmap_config);
पूर्ण

अटल पूर्णांक meson_pinctrl_parse_dt(काष्ठा meson_pinctrl *pc,
				  काष्ठा device_node *node)
अणु
	काष्ठा device_node *np, *gpio_np = शून्य;

	क्रम_each_child_of_node(node, np) अणु
		अगर (!of_find_property(np, "gpio-controller", शून्य))
			जारी;
		अगर (gpio_np) अणु
			dev_err(pc->dev, "multiple gpio nodes\n");
			of_node_put(np);
			वापस -EINVAL;
		पूर्ण
		gpio_np = np;
	पूर्ण

	अगर (!gpio_np) अणु
		dev_err(pc->dev, "no gpio node found\n");
		वापस -EINVAL;
	पूर्ण

	pc->of_node = gpio_np;

	pc->reg_mux = meson_map_resource(pc, gpio_np, "mux");
	अगर (IS_ERR_OR_शून्य(pc->reg_mux)) अणु
		dev_err(pc->dev, "mux registers not found\n");
		वापस pc->reg_mux ? PTR_ERR(pc->reg_mux) : -ENOENT;
	पूर्ण

	pc->reg_gpio = meson_map_resource(pc, gpio_np, "gpio");
	अगर (IS_ERR_OR_शून्य(pc->reg_gpio)) अणु
		dev_err(pc->dev, "gpio registers not found\n");
		वापस pc->reg_gpio ? PTR_ERR(pc->reg_gpio) : -ENOENT;
	पूर्ण

	pc->reg_pull = meson_map_resource(pc, gpio_np, "pull");
	अगर (IS_ERR(pc->reg_pull))
		pc->reg_pull = शून्य;

	pc->reg_pullen = meson_map_resource(pc, gpio_np, "pull-enable");
	अगर (IS_ERR(pc->reg_pullen))
		pc->reg_pullen = शून्य;

	pc->reg_ds = meson_map_resource(pc, gpio_np, "ds");
	अगर (IS_ERR(pc->reg_ds)) अणु
		dev_dbg(pc->dev, "ds registers not found - skipping\n");
		pc->reg_ds = शून्य;
	पूर्ण

	अगर (pc->data->parse_dt)
		वापस pc->data->parse_dt(pc);

	वापस 0;
पूर्ण

पूर्णांक meson8_aobus_parse_dt_extra(काष्ठा meson_pinctrl *pc)
अणु
	अगर (!pc->reg_pull)
		वापस -EINVAL;

	pc->reg_pullen = pc->reg_pull;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson8_aobus_parse_dt_extra);

पूर्णांक meson_a1_parse_dt_extra(काष्ठा meson_pinctrl *pc)
अणु
	pc->reg_pull = pc->reg_gpio;
	pc->reg_pullen = pc->reg_gpio;
	pc->reg_ds = pc->reg_gpio;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_a1_parse_dt_extra);

पूर्णांक meson_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_pinctrl *pc;
	पूर्णांक ret;

	pc = devm_kzalloc(dev, माप(काष्ठा meson_pinctrl), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	pc->dev = dev;
	pc->data = (काष्ठा meson_pinctrl_data *) of_device_get_match_data(dev);

	ret = meson_pinctrl_parse_dt(pc, dev->of_node);
	अगर (ret)
		वापस ret;

	pc->desc.name		= "pinctrl-meson";
	pc->desc.owner		= THIS_MODULE;
	pc->desc.pctlops	= &meson_pctrl_ops;
	pc->desc.pmxops		= pc->data->pmx_ops;
	pc->desc.confops	= &meson_pinconf_ops;
	pc->desc.pins		= pc->data->pins;
	pc->desc.npins		= pc->data->num_pins;

	pc->pcdev = devm_pinctrl_रेजिस्टर(pc->dev, &pc->desc, pc);
	अगर (IS_ERR(pc->pcdev)) अणु
		dev_err(pc->dev, "can't register pinctrl device");
		वापस PTR_ERR(pc->pcdev);
	पूर्ण

	वापस meson_gpiolib_रेजिस्टर(pc);
पूर्ण
EXPORT_SYMBOL_GPL(meson_pinctrl_probe);

MODULE_LICENSE("GPL v2");
