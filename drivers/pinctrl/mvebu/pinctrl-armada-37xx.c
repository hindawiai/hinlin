<शैली गुरु>
/*
 * Marvell 37xx SoC pinctrl driver
 *
 * Copyright (C) 2017 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2 or later. This program is licensed "as is"
 * without any warranty of any kind, whether express or implied.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "../pinctrl-utils.h"

#घोषणा OUTPUT_EN	0x0
#घोषणा INPUT_VAL	0x10
#घोषणा OUTPUT_VAL	0x18
#घोषणा OUTPUT_CTL	0x20
#घोषणा SELECTION	0x30

#घोषणा IRQ_EN		0x0
#घोषणा IRQ_POL		0x08
#घोषणा IRQ_STATUS	0x10
#घोषणा IRQ_WKUP	0x18

#घोषणा NB_FUNCS 3
#घोषणा GPIO_PER_REG	32

/**
 * काष्ठा armada_37xx_pin_group: represents group of pins of a pinmux function.
 * The pins of a pinmux groups are composed of one or two groups of contiguous
 * pins.
 * @name:	Name of the pin group, used to lookup the group.
 * @start_pin:	Index of the first pin of the मुख्य range of pins beदीर्घing to
 *		the group
 * @npins:	Number of pins included in the first range
 * @reg_mask:	Bit mask matching the group in the selection रेजिस्टर
 * @val:	Value to ग_लिखो to the रेजिस्टरs क्रम a given function
 * @extra_pin:	Index of the first pin of the optional second range of pins
 *		beदीर्घing to the group
 * @extra_npins:Number of pins included in the second optional range
 * @funcs:	A list of pinmux functions that can be selected क्रम this group.
 * @pins:	List of the pins included in the group
 */
काष्ठा armada_37xx_pin_group अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	start_pin;
	अचिन्हित पूर्णांक	npins;
	u32		reg_mask;
	u32		val[NB_FUNCS];
	अचिन्हित पूर्णांक	extra_pin;
	अचिन्हित पूर्णांक	extra_npins;
	स्थिर अक्षर	*funcs[NB_FUNCS];
	अचिन्हित पूर्णांक	*pins;
पूर्ण;

काष्ठा armada_37xx_pin_data अणु
	u8				nr_pins;
	अक्षर				*name;
	काष्ठा armada_37xx_pin_group	*groups;
	पूर्णांक				ngroups;
पूर्ण;

काष्ठा armada_37xx_pmx_func अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**groups;
	अचिन्हित पूर्णांक		ngroups;
पूर्ण;

काष्ठा armada_37xx_pm_state अणु
	u32 out_en_l;
	u32 out_en_h;
	u32 out_val_l;
	u32 out_val_h;
	u32 irq_en_l;
	u32 irq_en_h;
	u32 irq_pol_l;
	u32 irq_pol_h;
	u32 selection;
पूर्ण;

काष्ठा armada_37xx_pinctrl अणु
	काष्ठा regmap			*regmap;
	व्योम __iomem			*base;
	स्थिर काष्ठा armada_37xx_pin_data	*data;
	काष्ठा device			*dev;
	काष्ठा gpio_chip		gpio_chip;
	काष्ठा irq_chip			irq_chip;
	spinlock_t			irq_lock;
	काष्ठा pinctrl_desc		pctl;
	काष्ठा pinctrl_dev		*pctl_dev;
	काष्ठा armada_37xx_pin_group	*groups;
	अचिन्हित पूर्णांक			ngroups;
	काष्ठा armada_37xx_pmx_func	*funcs;
	अचिन्हित पूर्णांक			nfuncs;
	काष्ठा armada_37xx_pm_state	pm;
पूर्ण;

#घोषणा PIN_GRP(_name, _start, _nr, _mask, _func1, _func2)	\
	अणु					\
		.name = _name,			\
		.start_pin = _start,		\
		.npins = _nr,			\
		.reg_mask = _mask,		\
		.val = अणु0, _maskपूर्ण,		\
		.funcs = अणु_func1, _func2पूर्ण	\
	पूर्ण

#घोषणा PIN_GRP_GPIO(_name, _start, _nr, _mask, _func1)	\
	अणु					\
		.name = _name,			\
		.start_pin = _start,		\
		.npins = _nr,			\
		.reg_mask = _mask,		\
		.val = अणु0, _maskपूर्ण,		\
		.funcs = अणु_func1, "gpio"पूर्ण	\
	पूर्ण

#घोषणा PIN_GRP_GPIO_2(_name, _start, _nr, _mask, _val1, _val2, _func1)   \
	अणु					\
		.name = _name,			\
		.start_pin = _start,		\
		.npins = _nr,			\
		.reg_mask = _mask,		\
		.val = अणु_val1, _val2पूर्ण,		\
		.funcs = अणु_func1, "gpio"पूर्ण	\
	पूर्ण

#घोषणा PIN_GRP_GPIO_3(_name, _start, _nr, _mask, _v1, _v2, _v3, _f1, _f2) \
	अणु					\
		.name = _name,			\
		.start_pin = _start,		\
		.npins = _nr,			\
		.reg_mask = _mask,		\
		.val = अणु_v1, _v2, _v3पूर्ण,	\
		.funcs = अणु_f1, _f2, "gpio"पूर्ण	\
	पूर्ण

#घोषणा PIN_GRP_EXTRA(_name, _start, _nr, _mask, _v1, _v2, _start2, _nr2, \
		      _f1, _f2)				\
	अणु						\
		.name = _name,				\
		.start_pin = _start,			\
		.npins = _nr,				\
		.reg_mask = _mask,			\
		.val = अणु_v1, _v2पूर्ण,			\
		.extra_pin = _start2,			\
		.extra_npins = _nr2,			\
		.funcs = अणु_f1, _f2पूर्ण			\
	पूर्ण

अटल काष्ठा armada_37xx_pin_group armada_37xx_nb_groups[] = अणु
	PIN_GRP_GPIO("jtag", 20, 5, BIT(0), "jtag"),
	PIN_GRP_GPIO("sdio0", 8, 3, BIT(1), "sdio"),
	PIN_GRP_GPIO("emmc_nb", 27, 9, BIT(2), "emmc"),
	PIN_GRP_GPIO("pwm0", 11, 1, BIT(3), "pwm"),
	PIN_GRP_GPIO("pwm1", 12, 1, BIT(4), "pwm"),
	PIN_GRP_GPIO("pwm2", 13, 1, BIT(5), "pwm"),
	PIN_GRP_GPIO("pwm3", 14, 1, BIT(6), "pwm"),
	PIN_GRP_GPIO("pmic1", 7, 1, BIT(7), "pmic"),
	PIN_GRP_GPIO("pmic0", 6, 1, BIT(8), "pmic"),
	PIN_GRP_GPIO("i2c2", 2, 2, BIT(9), "i2c"),
	PIN_GRP_GPIO("i2c1", 0, 2, BIT(10), "i2c"),
	PIN_GRP_GPIO("spi_cs1", 17, 1, BIT(12), "spi"),
	PIN_GRP_GPIO_2("spi_cs2", 18, 1, BIT(13) | BIT(19), 0, BIT(13), "spi"),
	PIN_GRP_GPIO_2("spi_cs3", 19, 1, BIT(14) | BIT(19), 0, BIT(14), "spi"),
	PIN_GRP_GPIO("onewire", 4, 1, BIT(16), "onewire"),
	PIN_GRP_GPIO("uart1", 25, 2, BIT(17), "uart"),
	PIN_GRP_GPIO("spi_quad", 15, 2, BIT(18), "spi"),
	PIN_GRP_EXTRA("uart2", 9, 2, BIT(1) | BIT(13) | BIT(14) | BIT(19),
		      BIT(1) | BIT(13) | BIT(14), BIT(1) | BIT(19),
		      18, 2, "gpio", "uart"),
	PIN_GRP_GPIO_2("led0_od", 11, 1, BIT(20), BIT(20), 0, "led"),
	PIN_GRP_GPIO_2("led1_od", 12, 1, BIT(21), BIT(21), 0, "led"),
	PIN_GRP_GPIO_2("led2_od", 13, 1, BIT(22), BIT(22), 0, "led"),
	PIN_GRP_GPIO_2("led3_od", 14, 1, BIT(23), BIT(23), 0, "led"),
पूर्ण;

अटल काष्ठा armada_37xx_pin_group armada_37xx_sb_groups[] = अणु
	PIN_GRP_GPIO("usb32_drvvbus0", 0, 1, BIT(0), "drvbus"),
	PIN_GRP_GPIO("usb2_drvvbus1", 1, 1, BIT(1), "drvbus"),
	PIN_GRP_GPIO("sdio_sb", 24, 6, BIT(2), "sdio"),
	PIN_GRP_GPIO("rgmii", 6, 12, BIT(3), "mii"),
	PIN_GRP_GPIO("smi", 18, 2, BIT(4), "smi"),
	PIN_GRP_GPIO("pcie1", 3, 1, BIT(5), "pcie"), /* this actually controls "pcie1_reset" */
	PIN_GRP_GPIO("pcie1_clkreq", 4, 1, BIT(9), "pcie"),
	PIN_GRP_GPIO("pcie1_wakeup", 5, 1, BIT(10), "pcie"),
	PIN_GRP_GPIO("ptp", 20, 3, BIT(11) | BIT(12) | BIT(13), "ptp"),
	PIN_GRP("ptp_clk", 21, 1, BIT(6), "ptp", "mii"),
	PIN_GRP("ptp_trig", 22, 1, BIT(7), "ptp", "mii"),
	PIN_GRP_GPIO_3("mii_col", 23, 1, BIT(8) | BIT(14), 0, BIT(8), BIT(14),
		       "mii", "mii_err"),
पूर्ण;

अटल स्थिर काष्ठा armada_37xx_pin_data armada_37xx_pin_nb = अणु
	.nr_pins = 36,
	.name = "GPIO1",
	.groups = armada_37xx_nb_groups,
	.ngroups = ARRAY_SIZE(armada_37xx_nb_groups),
पूर्ण;

अटल स्थिर काष्ठा armada_37xx_pin_data armada_37xx_pin_sb = अणु
	.nr_pins = 30,
	.name = "GPIO2",
	.groups = armada_37xx_sb_groups,
	.ngroups = ARRAY_SIZE(armada_37xx_sb_groups),
पूर्ण;

अटल अंतरभूत व्योम armada_37xx_update_reg(अचिन्हित पूर्णांक *reg,
					  अचिन्हित पूर्णांक *offset)
अणु
	/* We never have more than 2 रेजिस्टरs */
	अगर (*offset >= GPIO_PER_REG) अणु
		*offset -= GPIO_PER_REG;
		*reg += माप(u32);
	पूर्ण
पूर्ण

अटल काष्ठा armada_37xx_pin_group *armada_37xx_find_next_grp_by_pin(
	काष्ठा armada_37xx_pinctrl *info, पूर्णांक pin, पूर्णांक *grp)
अणु
	जबतक (*grp < info->ngroups) अणु
		काष्ठा armada_37xx_pin_group *group = &info->groups[*grp];
		पूर्णांक j;

		*grp = *grp + 1;
		क्रम (j = 0; j < (group->npins + group->extra_npins); j++)
			अगर (group->pins[j] == pin)
				वापस group;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक armada_37xx_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
			    अचिन्हित पूर्णांक selector, अचिन्हित दीर्घ *config)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक armada_37xx_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
			    अचिन्हित पूर्णांक selector, अचिन्हित दीर्घ *configs,
			    अचिन्हित पूर्णांक num_configs)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops armada_37xx_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_group_get = armada_37xx_pin_config_group_get,
	.pin_config_group_set = armada_37xx_pin_config_group_set,
पूर्ण;

अटल पूर्णांक armada_37xx_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *armada_37xx_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक group)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->groups[group].name;
पूर्ण

अटल पूर्णांक armada_37xx_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक selector,
				      स्थिर अचिन्हित पूर्णांक **pins,
				      अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins +
		info->groups[selector].extra_npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops armada_37xx_pctrl_ops = अणु
	.get_groups_count	= armada_37xx_get_groups_count,
	.get_group_name		= armada_37xx_get_group_name,
	.get_group_pins		= armada_37xx_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

/*
 * Pinmux_ops handling
 */

अटल पूर्णांक armada_37xx_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->nfuncs;
पूर्ण

अटल स्थिर अक्षर *armada_37xx_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->funcs[selector].name;
पूर्ण

अटल पूर्णांक armada_37xx_pmx_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*groups = info->funcs[selector].groups;
	*num_groups = info->funcs[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_pmx_set_by_name(काष्ठा pinctrl_dev *pctldev,
				       स्थिर अक्षर *name,
				       काष्ठा armada_37xx_pin_group *grp)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक reg = SELECTION;
	अचिन्हित पूर्णांक mask = grp->reg_mask;
	पूर्णांक func, val;

	dev_dbg(info->dev, "enable function %s group %s\n",
		name, grp->name);

	func = match_string(grp->funcs, NB_FUNCS, name);
	अगर (func < 0)
		वापस -ENOTSUPP;

	val = grp->val[func];

	regmap_update_bits(info->regmap, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_pmx_set(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक selector,
			       अचिन्हित पूर्णांक group)
अणु

	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा armada_37xx_pin_group *grp = &info->groups[group];
	स्थिर अक्षर *name = info->funcs[selector].name;

	वापस armada_37xx_pmx_set_by_name(pctldev, name, grp);
पूर्ण

अटल अंतरभूत व्योम armada_37xx_irq_update_reg(अचिन्हित पूर्णांक *reg,
					  काष्ठा irq_data *d)
अणु
	पूर्णांक offset = irqd_to_hwirq(d);

	armada_37xx_update_reg(reg, &offset);
पूर्ण

अटल पूर्णांक armada_37xx_gpio_direction_input(काष्ठा gpio_chip *chip,
					    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = OUTPUT_EN;
	अचिन्हित पूर्णांक mask;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);

	वापस regmap_update_bits(info->regmap, reg, mask, 0);
पूर्ण

अटल पूर्णांक armada_37xx_gpio_get_direction(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = OUTPUT_EN;
	अचिन्हित पूर्णांक val, mask;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);
	regmap_पढ़ो(info->regmap, reg, &val);

	अगर (val & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक armada_37xx_gpio_direction_output(काष्ठा gpio_chip *chip,
					     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = OUTPUT_EN;
	अचिन्हित पूर्णांक mask, val, ret;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);

	ret = regmap_update_bits(info->regmap, reg, mask, mask);

	अगर (ret)
		वापस ret;

	reg = OUTPUT_VAL;
	val = value ? mask : 0;
	regmap_update_bits(info->regmap, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = INPUT_VAL;
	अचिन्हित पूर्णांक val, mask;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);

	regmap_पढ़ो(info->regmap, reg, &val);

	वापस (val & mask) != 0;
पूर्ण

अटल व्योम armada_37xx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 पूर्णांक value)
अणु
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = OUTPUT_VAL;
	अचिन्हित पूर्णांक mask, val;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);
	val = value ? mask : 0;

	regmap_update_bits(info->regmap, reg, mask, val);
पूर्ण

अटल पूर्णांक armada_37xx_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					      काष्ठा pinctrl_gpio_range *range,
					      अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = range->gc;

	dev_dbg(info->dev, "gpio_direction for pin %u as %s-%d to %s\n",
		offset, range->name, offset, input ? "input" : "output");

	अगर (input)
		armada_37xx_gpio_direction_input(chip, offset);
	अन्यथा
		armada_37xx_gpio_direction_output(chip, offset, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					   काष्ठा pinctrl_gpio_range *range,
					   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा armada_37xx_pin_group *group;
	पूर्णांक grp = 0;

	dev_dbg(info->dev, "requesting gpio %d\n", offset);

	जबतक ((group = armada_37xx_find_next_grp_by_pin(info, offset, &grp)))
		armada_37xx_pmx_set_by_name(pctldev, "gpio", group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops armada_37xx_pmx_ops = अणु
	.get_functions_count	= armada_37xx_pmx_get_funcs_count,
	.get_function_name	= armada_37xx_pmx_get_func_name,
	.get_function_groups	= armada_37xx_pmx_get_groups,
	.set_mux		= armada_37xx_pmx_set,
	.gpio_request_enable	= armada_37xx_gpio_request_enable,
	.gpio_set_direction	= armada_37xx_pmx_gpio_set_direction,
पूर्ण;

अटल स्थिर काष्ठा gpio_chip armada_37xx_gpiolib_chip = अणु
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.set = armada_37xx_gpio_set,
	.get = armada_37xx_gpio_get,
	.get_direction	= armada_37xx_gpio_get_direction,
	.direction_input = armada_37xx_gpio_direction_input,
	.direction_output = armada_37xx_gpio_direction_output,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम armada_37xx_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 reg = IRQ_STATUS;
	अचिन्हित दीर्घ flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	ग_लिखोl(d->mask, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);
पूर्ण

अटल व्योम armada_37xx_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_EN;
	अचिन्हित दीर्घ flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	val = पढ़ोl(info->base + reg);
	ग_लिखोl(val & ~d->mask, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);
पूर्ण

अटल व्योम armada_37xx_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_EN;
	अचिन्हित दीर्घ flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	val = पढ़ोl(info->base + reg);
	ग_लिखोl(val | d->mask, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);
पूर्ण

अटल पूर्णांक armada_37xx_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_WKUP;
	अचिन्हित दीर्घ flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	val = पढ़ोl(info->base + reg);
	अगर (on)
		val |= (BIT(d->hwirq % GPIO_PER_REG));
	अन्यथा
		val &= ~(BIT(d->hwirq % GPIO_PER_REG));
	ग_लिखोl(val, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_POL;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->irq_lock, flags);
	armada_37xx_irq_update_reg(&reg, d);
	val = पढ़ोl(info->base + reg);
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		val &= ~(BIT(d->hwirq % GPIO_PER_REG));
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		val |= (BIT(d->hwirq % GPIO_PER_REG));
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH: अणु
		u32 in_val, in_reg = INPUT_VAL;

		armada_37xx_irq_update_reg(&in_reg, d);
		regmap_पढ़ो(info->regmap, in_reg, &in_val);

		/* Set initial polarity based on current input level. */
		अगर (in_val & BIT(d->hwirq % GPIO_PER_REG))
			val |= BIT(d->hwirq % GPIO_PER_REG);	/* falling */
		अन्यथा
			val &= ~(BIT(d->hwirq % GPIO_PER_REG));	/* rising */
		अवरोध;
	पूर्ण
	शेष:
		spin_unlock_irqrestore(&info->irq_lock, flags);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(val, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_edge_both_irq_swap_pol(काष्ठा armada_37xx_pinctrl *info,
					     u32 pin_idx)
अणु
	u32 reg_idx = pin_idx / GPIO_PER_REG;
	u32 bit_num = pin_idx % GPIO_PER_REG;
	u32 p, l, ret;
	अचिन्हित दीर्घ flags;

	regmap_पढ़ो(info->regmap, INPUT_VAL + 4*reg_idx, &l);

	spin_lock_irqsave(&info->irq_lock, flags);
	p = पढ़ोl(info->base + IRQ_POL + 4 * reg_idx);
	अगर ((p ^ l) & (1 << bit_num)) अणु
		/*
		 * For the gpios which are used क्रम both-edge irqs, when their
		 * पूर्णांकerrupts happen, their input levels are changed,
		 * yet their पूर्णांकerrupt polarities are kept in old values, we
		 * should synchronize their पूर्णांकerrupt polarities; क्रम example,
		 * at first a gpio's input level is low and its पूर्णांकerrupt
		 * polarity control is "Detect rising edge", then the gpio has
		 * a पूर्णांकerrupt , its level turns to high, we should change its
		 * polarity control to "Detect falling edge" correspondingly.
		 */
		p ^= 1 << bit_num;
		ग_लिखोl(p, info->base + IRQ_POL + 4 * reg_idx);
		ret = 0;
	पूर्ण अन्यथा अणु
		/* Spurious irq */
		ret = -1;
	पूर्ण

	spin_unlock_irqrestore(&info->irq_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम armada_37xx_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा armada_37xx_pinctrl *info = gpiochip_get_data(gc);
	काष्ठा irq_करोमुख्य *d = gc->irq.करोमुख्य;
	पूर्णांक i;

	chained_irq_enter(chip, desc);
	क्रम (i = 0; i <= d->revmap_size / GPIO_PER_REG; i++) अणु
		u32 status;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&info->irq_lock, flags);
		status = पढ़ोl_relaxed(info->base + IRQ_STATUS + 4 * i);
		/* Manage only the पूर्णांकerrupt that was enabled */
		status &= पढ़ोl_relaxed(info->base + IRQ_EN + 4 * i);
		spin_unlock_irqrestore(&info->irq_lock, flags);
		जबतक (status) अणु
			u32 hwirq = ffs(status) - 1;
			u32 virq = irq_find_mapping(d, hwirq +
						     i * GPIO_PER_REG);
			u32 t = irq_get_trigger_type(virq);

			अगर ((t & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH) अणु
				/* Swap polarity (race with GPIO line) */
				अगर (armada_37xx_edge_both_irq_swap_pol(info,
					hwirq + i * GPIO_PER_REG)) अणु
					/*
					 * For spurious irq, which gpio level
					 * is not as expected after incoming
					 * edge, just ack the gpio irq.
					 */
					ग_लिखोl(1 << hwirq,
					       info->base +
					       IRQ_STATUS + 4 * i);
					जाओ update_status;
				पूर्ण
			पूर्ण

			generic_handle_irq(virq);

update_status:
			/* Update status in हाल a new IRQ appears */
			spin_lock_irqsave(&info->irq_lock, flags);
			status = पढ़ोl_relaxed(info->base +
					       IRQ_STATUS + 4 * i);
			/* Manage only the पूर्णांकerrupt that was enabled */
			status &= पढ़ोl_relaxed(info->base + IRQ_EN + 4 * i);
			spin_unlock_irqrestore(&info->irq_lock, flags);
		पूर्ण
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

अटल अचिन्हित पूर्णांक armada_37xx_irq_startup(काष्ठा irq_data *d)
अणु
	/*
	 * The mask field is a "precomputed biपंचांगask क्रम accessing the
	 * chip रेजिस्टरs" which was पूर्णांकroduced क्रम the generic
	 * irqchip framework. As we करोn't use this framework, we can
	 * reuse this field क्रम our own usage.
	 */
	d->mask = BIT(d->hwirq % GPIO_PER_REG);

	armada_37xx_irq_unmask(d);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_irqchip_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					काष्ठा armada_37xx_pinctrl *info)
अणु
	काष्ठा device_node *np = info->dev->of_node;
	काष्ठा gpio_chip *gc = &info->gpio_chip;
	काष्ठा irq_chip *irqchip = &info->irq_chip;
	काष्ठा gpio_irq_chip *girq = &gc->irq;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource res;
	पूर्णांक ret = -ENODEV, i, nr_irq_parent;

	/* Check अगर we have at least one gpio-controller child node */
	क्रम_each_child_of_node(info->dev->of_node, np) अणु
		अगर (of_property_पढ़ो_bool(np, "gpio-controller")) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		dev_err(dev, "no gpio-controller child node\n");
		वापस ret;
	पूर्ण

	nr_irq_parent = of_irq_count(np);
	spin_lock_init(&info->irq_lock);

	अगर (!nr_irq_parent) अणु
		dev_err(dev, "invalid or no IRQ\n");
		वापस 0;
	पूर्ण

	अगर (of_address_to_resource(info->dev->of_node, 1, &res)) अणु
		dev_err(dev, "cannot find IO resource\n");
		वापस -ENOENT;
	पूर्ण

	info->base = devm_ioremap_resource(info->dev, &res);
	अगर (IS_ERR(info->base))
		वापस PTR_ERR(info->base);

	irqchip->irq_ack = armada_37xx_irq_ack;
	irqchip->irq_mask = armada_37xx_irq_mask;
	irqchip->irq_unmask = armada_37xx_irq_unmask;
	irqchip->irq_set_wake = armada_37xx_irq_set_wake;
	irqchip->irq_set_type = armada_37xx_irq_set_type;
	irqchip->irq_startup = armada_37xx_irq_startup;
	irqchip->name = info->data->name;
	girq->chip = irqchip;
	girq->parent_handler = armada_37xx_irq_handler;
	/*
	 * Many पूर्णांकerrupts are connected to the parent पूर्णांकerrupt
	 * controller. But we करो not take advantage of this and use
	 * the chained irq with all of them.
	 */
	girq->num_parents = nr_irq_parent;
	girq->parents = devm_kसुस्मृति(&pdev->dev, nr_irq_parent,
				     माप(*girq->parents), GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	क्रम (i = 0; i < nr_irq_parent; i++) अणु
		पूर्णांक irq = irq_of_parse_and_map(np, i);

		अगर (irq < 0)
			जारी;
		girq->parents[i] = irq;
	पूर्ण
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_gpiochip_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					काष्ठा armada_37xx_pinctrl *info)
अणु
	काष्ठा device_node *np;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret = -ENODEV;

	क्रम_each_child_of_node(info->dev->of_node, np) अणु
		अगर (of_find_property(np, "gpio-controller", शून्य)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret)
		वापस ret;

	info->gpio_chip = armada_37xx_gpiolib_chip;

	gc = &info->gpio_chip;
	gc->ngpio = info->data->nr_pins;
	gc->parent = &pdev->dev;
	gc->base = -1;
	gc->of_node = np;
	gc->label = info->data->name;

	ret = armada_37xx_irqchip_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;
	ret = devm_gpiochip_add_data(&pdev->dev, gc, info);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * armada_37xx_add_function() - Add a new function to the list
 * @funcs: array of function to add the new one
 * @funcsize: size of the reमुख्यing space क्रम the function
 * @name: name of the function to add
 *
 * If it is a new function then create it by adding its name अन्यथा
 * increment the number of group associated to this function.
 */
अटल पूर्णांक armada_37xx_add_function(काष्ठा armada_37xx_pmx_func *funcs,
				    पूर्णांक *funcsize, स्थिर अक्षर *name)
अणु
	पूर्णांक i = 0;

	अगर (*funcsize <= 0)
		वापस -EOVERFLOW;

	जबतक (funcs->ngroups) अणु
		/* function alपढ़ोy there */
		अगर (म_भेद(funcs->name, name) == 0) अणु
			funcs->ngroups++;

			वापस -EEXIST;
		पूर्ण
		funcs++;
		i++;
	पूर्ण

	/* append new unique function */
	funcs->name = name;
	funcs->ngroups = 1;
	(*funcsize)--;

	वापस 0;
पूर्ण

/**
 * armada_37xx_fill_group() - complete the group array
 * @info: info driver instance
 *
 * Based on the data available from the armada_37xx_pin_group array
 * completes the last member of the काष्ठा क्रम each function: the list
 * of the groups associated to this function.
 *
 */
अटल पूर्णांक armada_37xx_fill_group(काष्ठा armada_37xx_pinctrl *info)
अणु
	पूर्णांक n, num = 0, funcsize = info->data->nr_pins;

	क्रम (n = 0; n < info->ngroups; n++) अणु
		काष्ठा armada_37xx_pin_group *grp = &info->groups[n];
		पूर्णांक i, j, f;

		grp->pins = devm_kसुस्मृति(info->dev,
					 grp->npins + grp->extra_npins,
					 माप(*grp->pins),
					 GFP_KERNEL);
		अगर (!grp->pins)
			वापस -ENOMEM;

		क्रम (i = 0; i < grp->npins; i++)
			grp->pins[i] = grp->start_pin + i;

		क्रम (j = 0; j < grp->extra_npins; j++)
			grp->pins[i+j] = grp->extra_pin + j;

		क्रम (f = 0; (f < NB_FUNCS) && grp->funcs[f]; f++) अणु
			पूर्णांक ret;
			/* check क्रम unique functions and count groups */
			ret = armada_37xx_add_function(info->funcs, &funcsize,
					    grp->funcs[f]);
			अगर (ret == -EOVERFLOW)
				dev_err(info->dev,
					"More functions than pins(%d)\n",
					info->data->nr_pins);
			अगर (ret < 0)
				जारी;
			num++;
		पूर्ण
	पूर्ण

	info->nfuncs = num;

	वापस 0;
पूर्ण

/**
 * armada_37xx_fill_funcs() - complete the funcs array
 * @info: info driver instance
 *
 * Based on the data available from the armada_37xx_pin_group array
 * completes the last two member of the काष्ठा क्रम each group:
 * - the list of the pins included in the group
 * - the list of pinmux functions that can be selected क्रम this group
 *
 */
अटल पूर्णांक armada_37xx_fill_func(काष्ठा armada_37xx_pinctrl *info)
अणु
	काष्ठा armada_37xx_pmx_func *funcs = info->funcs;
	पूर्णांक n;

	क्रम (n = 0; n < info->nfuncs; n++) अणु
		स्थिर अक्षर *name = funcs[n].name;
		स्थिर अक्षर **groups;
		पूर्णांक g;

		funcs[n].groups = devm_kसुस्मृति(info->dev,
					       funcs[n].ngroups,
					       माप(*(funcs[n].groups)),
					       GFP_KERNEL);
		अगर (!funcs[n].groups)
			वापस -ENOMEM;

		groups = funcs[n].groups;

		क्रम (g = 0; g < info->ngroups; g++) अणु
			काष्ठा armada_37xx_pin_group *gp = &info->groups[g];
			पूर्णांक f;

			f = match_string(gp->funcs, NB_FUNCS, name);
			अगर (f < 0)
				जारी;

			*groups = gp->name;
			groups++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					काष्ठा armada_37xx_pinctrl *info)
अणु
	स्थिर काष्ठा armada_37xx_pin_data *pin_data = info->data;
	काष्ठा pinctrl_desc *ctrldesc = &info->pctl;
	काष्ठा pinctrl_pin_desc *pindesc, *pdesc;
	पूर्णांक pin, ret;

	info->groups = pin_data->groups;
	info->ngroups = pin_data->ngroups;

	ctrldesc->name = "armada_37xx-pinctrl";
	ctrldesc->owner = THIS_MODULE;
	ctrldesc->pctlops = &armada_37xx_pctrl_ops;
	ctrldesc->pmxops = &armada_37xx_pmx_ops;
	ctrldesc->confops = &armada_37xx_pinconf_ops;

	pindesc = devm_kसुस्मृति(&pdev->dev,
			       pin_data->nr_pins, माप(*pindesc),
			       GFP_KERNEL);
	अगर (!pindesc)
		वापस -ENOMEM;

	ctrldesc->pins = pindesc;
	ctrldesc->npins = pin_data->nr_pins;

	pdesc = pindesc;
	क्रम (pin = 0; pin < pin_data->nr_pins; pin++) अणु
		pdesc->number = pin;
		pdesc->name = kaप्र_लिखो(GFP_KERNEL, "%s-%d",
					pin_data->name, pin);
		pdesc++;
	पूर्ण

	/*
	 * we allocate functions क्रम number of pins and hope there are
	 * fewer unique functions than pins available
	 */
	info->funcs = devm_kसुस्मृति(&pdev->dev,
				   pin_data->nr_pins,
				   माप(काष्ठा armada_37xx_pmx_func),
				   GFP_KERNEL);
	अगर (!info->funcs)
		वापस -ENOMEM;


	ret = armada_37xx_fill_group(info);
	अगर (ret)
		वापस ret;

	ret = armada_37xx_fill_func(info);
	अगर (ret)
		वापस ret;

	info->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, ctrldesc, info);
	अगर (IS_ERR(info->pctl_dev)) अणु
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		वापस PTR_ERR(info->pctl_dev);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM)
अटल पूर्णांक armada_3700_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा armada_37xx_pinctrl *info = dev_get_drvdata(dev);

	/* Save GPIO state */
	regmap_पढ़ो(info->regmap, OUTPUT_EN, &info->pm.out_en_l);
	regmap_पढ़ो(info->regmap, OUTPUT_EN + माप(u32), &info->pm.out_en_h);
	regmap_पढ़ो(info->regmap, OUTPUT_VAL, &info->pm.out_val_l);
	regmap_पढ़ो(info->regmap, OUTPUT_VAL + माप(u32),
		    &info->pm.out_val_h);

	info->pm.irq_en_l = पढ़ोl(info->base + IRQ_EN);
	info->pm.irq_en_h = पढ़ोl(info->base + IRQ_EN + माप(u32));
	info->pm.irq_pol_l = पढ़ोl(info->base + IRQ_POL);
	info->pm.irq_pol_h = पढ़ोl(info->base + IRQ_POL + माप(u32));

	/* Save pinctrl state */
	regmap_पढ़ो(info->regmap, SELECTION, &info->pm.selection);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_3700_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा armada_37xx_pinctrl *info = dev_get_drvdata(dev);
	काष्ठा gpio_chip *gc;
	काष्ठा irq_करोमुख्य *d;
	पूर्णांक i;

	/* Restore GPIO state */
	regmap_ग_लिखो(info->regmap, OUTPUT_EN, info->pm.out_en_l);
	regmap_ग_लिखो(info->regmap, OUTPUT_EN + माप(u32),
		     info->pm.out_en_h);
	regmap_ग_लिखो(info->regmap, OUTPUT_VAL, info->pm.out_val_l);
	regmap_ग_लिखो(info->regmap, OUTPUT_VAL + माप(u32),
		     info->pm.out_val_h);

	/*
	 * Input levels may change during suspend, which is not monitored at
	 * that समय. GPIOs used क्रम both-edge IRQs may not be synchronized
	 * anymore with their polarities (rising/falling edge) and must be
	 * re-configured manually.
	 */
	gc = &info->gpio_chip;
	d = gc->irq.करोमुख्य;
	क्रम (i = 0; i < gc->ngpio; i++) अणु
		u32 irq_bit = BIT(i % GPIO_PER_REG);
		u32 mask, *irq_pol, input_reg, virq, type, level;

		अगर (i < GPIO_PER_REG) अणु
			mask = info->pm.irq_en_l;
			irq_pol = &info->pm.irq_pol_l;
			input_reg = INPUT_VAL;
		पूर्ण अन्यथा अणु
			mask = info->pm.irq_en_h;
			irq_pol = &info->pm.irq_pol_h;
			input_reg = INPUT_VAL + माप(u32);
		पूर्ण

		अगर (!(mask & irq_bit))
			जारी;

		virq = irq_find_mapping(d, i);
		type = irq_get_trigger_type(virq);

		/*
		 * Synchronize level and polarity क्रम both-edge irqs:
		 *     - a high input level expects a falling edge,
		 *     - a low input level exepects a rising edge.
		 */
		अगर ((type & IRQ_TYPE_SENSE_MASK) ==
		    IRQ_TYPE_EDGE_BOTH) अणु
			regmap_पढ़ो(info->regmap, input_reg, &level);
			अगर ((*irq_pol ^ level) & irq_bit)
				*irq_pol ^= irq_bit;
		पूर्ण
	पूर्ण

	ग_लिखोl(info->pm.irq_en_l, info->base + IRQ_EN);
	ग_लिखोl(info->pm.irq_en_h, info->base + IRQ_EN + माप(u32));
	ग_लिखोl(info->pm.irq_pol_l, info->base + IRQ_POL);
	ग_लिखोl(info->pm.irq_pol_h, info->base + IRQ_POL + माप(u32));

	/* Restore pinctrl state */
	regmap_ग_लिखो(info->regmap, SELECTION, info->pm.selection);

	वापस 0;
पूर्ण

/*
 * Since pinctrl is an infraकाष्ठाure module, its resume should be issued prior
 * to other IO drivers.
 */
अटल स्थिर काष्ठा dev_pm_ops armada_3700_pinctrl_pm_ops = अणु
	.suspend_noirq = armada_3700_pinctrl_suspend,
	.resume_noirq = armada_3700_pinctrl_resume,
पूर्ण;

#घोषणा PINCTRL_ARMADA_37XX_DEV_PM_OPS (&armada_3700_pinctrl_pm_ops)
#अन्यथा
#घोषणा PINCTRL_ARMADA_37XX_DEV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id armada_37xx_pinctrl_of_match[] = अणु
	अणु
		.compatible = "marvell,armada3710-sb-pinctrl",
		.data = &armada_37xx_pin_sb,
	पूर्ण,
	अणु
		.compatible = "marvell,armada3710-nb-pinctrl",
		.data = &armada_37xx_pin_nb,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init armada_37xx_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा armada_37xx_pinctrl *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	info = devm_kzalloc(dev, माप(काष्ठा armada_37xx_pinctrl),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;

	regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&pdev->dev, "cannot get regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	info->regmap = regmap;

	info->data = of_device_get_match_data(dev);

	ret = armada_37xx_pinctrl_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;

	ret = armada_37xx_gpiochip_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver armada_37xx_pinctrl_driver = अणु
	.driver = अणु
		.name = "armada-37xx-pinctrl",
		.of_match_table = armada_37xx_pinctrl_of_match,
		.pm = PINCTRL_ARMADA_37XX_DEV_PM_OPS,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver_probe(armada_37xx_pinctrl_driver,
			      armada_37xx_pinctrl_probe);
