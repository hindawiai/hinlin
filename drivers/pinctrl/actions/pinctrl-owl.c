<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * OWL SoC's Pinctrl driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Copyright (c) 2018 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-owl.h"

/**
 * काष्ठा owl_pinctrl - pinctrl state of the device
 * @dev: device handle
 * @pctrldev: pinctrl handle
 * @chip: gpio chip
 * @lock: spinlock to protect रेजिस्टरs
 * @clk: घड़ी control
 * @soc: reference to soc_data
 * @base: pinctrl रेजिस्टर base address
 * @irq_chip: IRQ chip inक्रमmation
 * @num_irq: number of possible पूर्णांकerrupts
 * @irq: पूर्णांकerrupt numbers
 */
काष्ठा owl_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctrldev;
	काष्ठा gpio_chip chip;
	raw_spinlock_t lock;
	काष्ठा clk *clk;
	स्थिर काष्ठा owl_pinctrl_soc_data *soc;
	व्योम __iomem *base;
	काष्ठा irq_chip irq_chip;
	अचिन्हित पूर्णांक num_irq;
	अचिन्हित पूर्णांक *irq;
पूर्ण;

अटल व्योम owl_update_bits(व्योम __iomem *base, u32 mask, u32 val)
अणु
	u32 reg_val;

	reg_val = पढ़ोl_relaxed(base);

	reg_val = (reg_val & ~mask) | (val & mask);

	ग_लिखोl_relaxed(reg_val, base);
पूर्ण

अटल u32 owl_पढ़ो_field(काष्ठा owl_pinctrl *pctrl, u32 reg,
				u32 bit, u32 width)
अणु
	u32 पंचांगp, mask;

	पंचांगp = पढ़ोl_relaxed(pctrl->base + reg);
	mask = (1 << width) - 1;

	वापस (पंचांगp >> bit) & mask;
पूर्ण

अटल व्योम owl_ग_लिखो_field(काष्ठा owl_pinctrl *pctrl, u32 reg, u32 arg,
				u32 bit, u32 width)
अणु
	u32 mask;

	mask = (1 << width) - 1;
	mask = mask << bit;

	owl_update_bits(pctrl->base + reg, mask, (arg << bit));
पूर्ण

अटल पूर्णांक owl_get_groups_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	वापस pctrl->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *owl_get_group_name(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक group)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	वापस pctrl->soc->groups[group].name;
पूर्ण

अटल पूर्णांक owl_get_group_pins(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक group,
				स्थिर अचिन्हित पूर्णांक **pins,
				अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	*pins = pctrl->soc->groups[group].pads;
	*num_pins = pctrl->soc->groups[group].npads;

	वापस 0;
पूर्ण

अटल व्योम owl_pin_dbg_show(काष्ठा pinctrl_dev *pctrldev,
				काष्ठा seq_file *s,
				अचिन्हित पूर्णांक offset)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	seq_म_लिखो(s, "%s", dev_name(pctrl->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops owl_pinctrl_ops = अणु
	.get_groups_count = owl_get_groups_count,
	.get_group_name = owl_get_group_name,
	.get_group_pins = owl_get_group_pins,
	.pin_dbg_show = owl_pin_dbg_show,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक owl_get_funcs_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	वापस pctrl->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *owl_get_func_name(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक function)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	वापस pctrl->soc->functions[function].name;
पूर्ण

अटल पूर्णांक owl_get_func_groups(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक function,
				स्थिर अक्षर * स्थिर **groups,
				अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	*groups = pctrl->soc->functions[function].groups;
	*num_groups = pctrl->soc->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_group_mfp_mask_val(स्थिर काष्ठा owl_pingroup *g,
				पूर्णांक function,
				u32 *mask,
				u32 *val)
अणु
	पूर्णांक id;
	u32 option_num;
	u32 option_mask;

	क्रम (id = 0; id < g->nfuncs; id++) अणु
		अगर (g->funcs[id] == function)
			अवरोध;
	पूर्ण
	अगर (WARN_ON(id == g->nfuncs))
		वापस -EINVAL;

	option_num = (1 << g->mfpctl_width);
	अगर (id > option_num)
		id -= option_num;

	option_mask = option_num - 1;
	*mask = (option_mask  << g->mfpctl_shअगरt);
	*val = (id << g->mfpctl_shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_set_mux(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक function,
				अचिन्हित पूर्णांक group)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	स्थिर काष्ठा owl_pingroup *g;
	अचिन्हित दीर्घ flags;
	u32 val, mask;

	g = &pctrl->soc->groups[group];

	अगर (get_group_mfp_mask_val(g, function, &mask, &val))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	owl_update_bits(pctrl->base + g->mfpctl_reg, mask, val);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops owl_pinmux_ops = अणु
	.get_functions_count = owl_get_funcs_count,
	.get_function_name = owl_get_func_name,
	.get_function_groups = owl_get_func_groups,
	.set_mux = owl_set_mux,
पूर्ण;

अटल पूर्णांक owl_pad_pinconf_reg(स्थिर काष्ठा owl_padinfo *info,
				अचिन्हित पूर्णांक param,
				u32 *reg,
				u32 *bit,
				u32 *width)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!info->pullctl)
			वापस -EINVAL;
		*reg = info->pullctl->reg;
		*bit = info->pullctl->shअगरt;
		*width = info->pullctl->width;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (!info->st)
			वापस -EINVAL;
		*reg = info->st->reg;
		*bit = info->st->shअगरt;
		*width = info->st->width;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_pin_config_get(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *config)
अणु
	पूर्णांक ret = 0;
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	स्थिर काष्ठा owl_padinfo *info;
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	u32 reg, bit, width, arg;

	info = &pctrl->soc->padinfo[pin];

	ret = owl_pad_pinconf_reg(info, param, &reg, &bit, &width);
	अगर (ret)
		वापस ret;

	arg = owl_पढ़ो_field(pctrl, reg, bit, width);

	अगर (!pctrl->soc->padctl_val2arg)
		वापस -ENOTSUPP;

	ret = pctrl->soc->padctl_val2arg(info, param, &arg);
	अगर (ret)
		वापस ret;

	*config = pinconf_to_config_packed(param, arg);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_pin_config_set(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs,
				अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	स्थिर काष्ठा owl_padinfo *info;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक param;
	u32 reg, bit, width, arg;
	पूर्णांक ret = 0, i;

	info = &pctrl->soc->padinfo[pin];

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		ret = owl_pad_pinconf_reg(info, param, &reg, &bit, &width);
		अगर (ret)
			वापस ret;

		अगर (!pctrl->soc->padctl_arg2val)
			वापस -ENOTSUPP;

		ret = pctrl->soc->padctl_arg2val(info, param, &arg);
		अगर (ret)
			वापस ret;

		raw_spin_lock_irqsave(&pctrl->lock, flags);

		owl_ग_लिखो_field(pctrl, reg, arg, bit, width);

		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक owl_group_pinconf_reg(स्थिर काष्ठा owl_pingroup *g,
				अचिन्हित पूर्णांक param,
				u32 *reg,
				u32 *bit,
				u32 *width)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (g->drv_reg < 0)
			वापस -EINVAL;
		*reg = g->drv_reg;
		*bit = g->drv_shअगरt;
		*width = g->drv_width;
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		अगर (g->sr_reg < 0)
			वापस -EINVAL;
		*reg = g->sr_reg;
		*bit = g->sr_shअगरt;
		*width = g->sr_width;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_group_pinconf_arg2val(स्थिर काष्ठा owl_pingroup *g,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		चयन (*arg) अणु
		हाल 2:
			*arg = OWL_PINCONF_DRV_2MA;
			अवरोध;
		हाल 4:
			*arg = OWL_PINCONF_DRV_4MA;
			अवरोध;
		हाल 8:
			*arg = OWL_PINCONF_DRV_8MA;
			अवरोध;
		हाल 12:
			*arg = OWL_PINCONF_DRV_12MA;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		अगर (*arg)
			*arg = OWL_PINCONF_SLEW_FAST;
		अन्यथा
			*arg = OWL_PINCONF_SLEW_SLOW;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_group_pinconf_val2arg(स्थिर काष्ठा owl_pingroup *g,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		चयन (*arg) अणु
		हाल OWL_PINCONF_DRV_2MA:
			*arg = 2;
			अवरोध;
		हाल OWL_PINCONF_DRV_4MA:
			*arg = 4;
			अवरोध;
		हाल OWL_PINCONF_DRV_8MA:
			*arg = 8;
			अवरोध;
		हाल OWL_PINCONF_DRV_12MA:
			*arg = 12;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		अगर (*arg)
			*arg = 1;
		अन्यथा
			*arg = 0;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_group_config_get(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक group,
				अचिन्हित दीर्घ *config)
अणु
	स्थिर काष्ठा owl_pingroup *g;
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	u32 reg, bit, width, arg;
	पूर्णांक ret;

	g = &pctrl->soc->groups[group];

	ret = owl_group_pinconf_reg(g, param, &reg, &bit, &width);
	अगर (ret)
		वापस ret;

	arg = owl_पढ़ो_field(pctrl, reg, bit, width);

	ret = owl_group_pinconf_val2arg(g, param, &arg);
	अगर (ret)
		वापस ret;

	*config = pinconf_to_config_packed(param, arg);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_group_config_set(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित पूर्णांक group,
				अचिन्हित दीर्घ *configs,
				अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर काष्ठा owl_pingroup *g;
	काष्ठा owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक param;
	u32 reg, bit, width, arg;
	पूर्णांक ret, i;

	g = &pctrl->soc->groups[group];

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		ret = owl_group_pinconf_reg(g, param, &reg, &bit, &width);
		अगर (ret)
			वापस ret;

		ret = owl_group_pinconf_arg2val(g, param, &arg);
		अगर (ret)
			वापस ret;

		/* Update रेजिस्टर */
		raw_spin_lock_irqsave(&pctrl->lock, flags);

		owl_ग_लिखो_field(pctrl, reg, arg, bit, width);

		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops owl_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = owl_pin_config_get,
	.pin_config_set = owl_pin_config_set,
	.pin_config_group_get = owl_group_config_get,
	.pin_config_group_set = owl_group_config_set,
पूर्ण;

अटल काष्ठा pinctrl_desc owl_pinctrl_desc = अणु
	.pctlops = &owl_pinctrl_ops,
	.pmxops = &owl_pinmux_ops,
	.confops = &owl_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा owl_gpio_port *
owl_gpio_get_port(काष्ठा owl_pinctrl *pctrl, अचिन्हित पूर्णांक *pin)
अणु
	अचिन्हित पूर्णांक start = 0, i;

	क्रम (i = 0; i < pctrl->soc->nports; i++) अणु
		स्थिर काष्ठा owl_gpio_port *port = &pctrl->soc->ports[i];

		अगर (*pin >= start && *pin < start + port->pins) अणु
			*pin -= start;
			वापस port;
		पूर्ण

		start += port->pins;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम owl_gpio_update_reg(व्योम __iomem *base, अचिन्हित पूर्णांक pin, पूर्णांक flag)
अणु
	u32 val;

	val = पढ़ोl_relaxed(base);

	अगर (flag)
		val |= BIT(pin);
	अन्यथा
		val &= ~BIT(pin);

	ग_लिखोl_relaxed(val, base);
पूर्ण

अटल पूर्णांक owl_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस -ENODEV;

	gpio_base = pctrl->base + port->offset;

	/*
	 * GPIOs have higher priority over other modules, so either setting
	 * them as OUT or IN is sufficient
	 */
	raw_spin_lock_irqsave(&pctrl->lock, flags);
	owl_gpio_update_reg(gpio_base + port->outen, offset, true);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम owl_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	/* disable gpio output */
	owl_gpio_update_reg(gpio_base + port->outen, offset, false);

	/* disable gpio input */
	owl_gpio_update_reg(gpio_base + port->inen, offset, false);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल पूर्णांक owl_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;
	u32 val;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस -ENODEV;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	val = पढ़ोl_relaxed(gpio_base + port->dat);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम owl_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	owl_gpio_update_reg(gpio_base + port->dat, offset, value);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल पूर्णांक owl_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस -ENODEV;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	owl_gpio_update_reg(gpio_base + port->outen, offset, false);
	owl_gpio_update_reg(gpio_base + port->inen, offset, true);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_gpio_direction_output(काष्ठा gpio_chip *chip,
				अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;

	port = owl_gpio_get_port(pctrl, &offset);
	अगर (WARN_ON(port == शून्य))
		वापस -ENODEV;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	owl_gpio_update_reg(gpio_base + port->inen, offset, false);
	owl_gpio_update_reg(gpio_base + port->outen, offset, true);
	owl_gpio_update_reg(gpio_base + port->dat, offset, value);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम irq_set_type(काष्ठा owl_pinctrl *pctrl, पूर्णांक gpio, अचिन्हित पूर्णांक type)
अणु
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset, value, irq_type = 0;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		/*
		 * Since the hardware करोesn't support पूर्णांकerrupts on both edges,
		 * emulate it in the software by setting the single edge
		 * पूर्णांकerrupt and चयनing to the opposite edge जबतक ACKing
		 * the पूर्णांकerrupt
		 */
		अगर (owl_gpio_get(&pctrl->chip, gpio))
			irq_type = OWL_GPIO_INT_EDGE_FALLING;
		अन्यथा
			irq_type = OWL_GPIO_INT_EDGE_RISING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		irq_type = OWL_GPIO_INT_EDGE_RISING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		irq_type = OWL_GPIO_INT_EDGE_FALLING;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_type = OWL_GPIO_INT_LEVEL_HIGH;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		irq_type = OWL_GPIO_INT_LEVEL_LOW;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	port = owl_gpio_get_port(pctrl, &gpio);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	offset = (gpio < 16) ? 4 : 0;
	value = पढ़ोl_relaxed(gpio_base + port->पूर्णांकc_type + offset);
	value &= ~(OWL_GPIO_INT_MASK << ((gpio % 16) * 2));
	value |= irq_type << ((gpio % 16) * 2);
	ग_लिखोl_relaxed(value, gpio_base + port->पूर्णांकc_type + offset);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल व्योम owl_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gpio = data->hwirq;
	u32 val;

	port = owl_gpio_get_port(pctrl, &gpio);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	owl_gpio_update_reg(gpio_base + port->पूर्णांकc_msk, gpio, false);

	/* disable port पूर्णांकerrupt अगर no पूर्णांकerrupt pending bit is active */
	val = पढ़ोl_relaxed(gpio_base + port->पूर्णांकc_msk);
	अगर (val == 0)
		owl_gpio_update_reg(gpio_base + port->पूर्णांकc_ctl,
					OWL_GPIO_CTLR_ENABLE + port->shared_ctl_offset * 5, false);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल व्योम owl_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gpio = data->hwirq;
	u32 value;

	port = owl_gpio_get_port(pctrl, &gpio);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;
	raw_spin_lock_irqsave(&pctrl->lock, flags);

	/* enable port पूर्णांकerrupt */
	value = पढ़ोl_relaxed(gpio_base + port->पूर्णांकc_ctl);
	value |= ((BIT(OWL_GPIO_CTLR_ENABLE) | BIT(OWL_GPIO_CTLR_SAMPLE_CLK_24M))
			<< port->shared_ctl_offset * 5);
	ग_लिखोl_relaxed(value, gpio_base + port->पूर्णांकc_ctl);

	/* enable GPIO पूर्णांकerrupt */
	owl_gpio_update_reg(gpio_base + port->पूर्णांकc_msk, gpio, true);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल व्योम owl_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *gpio_base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gpio = data->hwirq;

	/*
	 * Switch the पूर्णांकerrupt edge to the opposite edge of the पूर्णांकerrupt
	 * which got triggered क्रम the हाल of emulating both edges
	 */
	अगर (irqd_get_trigger_type(data) == IRQ_TYPE_EDGE_BOTH) अणु
		अगर (owl_gpio_get(gc, gpio))
			irq_set_type(pctrl, gpio, IRQ_TYPE_EDGE_FALLING);
		अन्यथा
			irq_set_type(pctrl, gpio, IRQ_TYPE_EDGE_RISING);
	पूर्ण

	port = owl_gpio_get_port(pctrl, &gpio);
	अगर (WARN_ON(port == शून्य))
		वापस;

	gpio_base = pctrl->base + port->offset;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	owl_gpio_update_reg(gpio_base + port->पूर्णांकc_ctl,
				OWL_GPIO_CTLR_PENDING + port->shared_ctl_offset * 5, true);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल पूर्णांक owl_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);
	काष्ठा owl_pinctrl *pctrl = gpiochip_get_data(gc);

	अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(data, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_edge_irq);

	irq_set_type(pctrl, data->hwirq, type);

	वापस 0;
पूर्ण

अटल व्योम owl_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा owl_pinctrl *pctrl = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य = pctrl->chip.irq.करोमुख्य;
	अचिन्हित पूर्णांक parent = irq_desc_get_irq(desc);
	स्थिर काष्ठा owl_gpio_port *port;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक pin, irq, offset = 0, i;
	अचिन्हित दीर्घ pending_irq;

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < pctrl->soc->nports; i++) अणु
		port = &pctrl->soc->ports[i];
		base = pctrl->base + port->offset;

		/* skip ports that are not associated with this irq */
		अगर (parent != pctrl->irq[i])
			जाओ skip;

		pending_irq = पढ़ोl_relaxed(base + port->पूर्णांकc_pd);

		क्रम_each_set_bit(pin, &pending_irq, port->pins) अणु
			irq = irq_find_mapping(करोमुख्य, offset + pin);
			generic_handle_irq(irq);

			/* clear pending पूर्णांकerrupt */
			owl_gpio_update_reg(base + port->पूर्णांकc_pd, pin, true);
		पूर्ण

skip:
		offset += port->pins;
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक owl_gpio_init(काष्ठा owl_pinctrl *pctrl)
अणु
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *gpio_irq;
	पूर्णांक ret, i, j, offset;

	chip = &pctrl->chip;
	chip->base = -1;
	chip->ngpio = pctrl->soc->ngpios;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->owner = THIS_MODULE;
	chip->of_node = pctrl->dev->of_node;

	pctrl->irq_chip.name = chip->of_node->name;
	pctrl->irq_chip.irq_ack = owl_gpio_irq_ack;
	pctrl->irq_chip.irq_mask = owl_gpio_irq_mask;
	pctrl->irq_chip.irq_unmask = owl_gpio_irq_unmask;
	pctrl->irq_chip.irq_set_type = owl_gpio_irq_set_type;

	gpio_irq = &chip->irq;
	gpio_irq->chip = &pctrl->irq_chip;
	gpio_irq->handler = handle_simple_irq;
	gpio_irq->शेष_type = IRQ_TYPE_NONE;
	gpio_irq->parent_handler = owl_gpio_irq_handler;
	gpio_irq->parent_handler_data = pctrl;
	gpio_irq->num_parents = pctrl->num_irq;
	gpio_irq->parents = pctrl->irq;

	gpio_irq->map = devm_kसुस्मृति(pctrl->dev, chip->ngpio,
				माप(*gpio_irq->map), GFP_KERNEL);
	अगर (!gpio_irq->map)
		वापस -ENOMEM;

	क्रम (i = 0, offset = 0; i < pctrl->soc->nports; i++) अणु
		स्थिर काष्ठा owl_gpio_port *port = &pctrl->soc->ports[i];

		क्रम (j = 0; j < port->pins; j++)
			gpio_irq->map[offset + j] = gpio_irq->parents[i];

		offset += port->pins;
	पूर्ण

	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to register gpiochip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक owl_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
				काष्ठा owl_pinctrl_soc_data *soc_data)
अणु
	काष्ठा owl_pinctrl *pctrl;
	पूर्णांक ret, i;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctrl->base))
		वापस PTR_ERR(pctrl->base);

	/* enable GPIO/MFP घड़ी */
	pctrl->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pctrl->clk)) अणु
		dev_err(&pdev->dev, "no clock defined\n");
		वापस PTR_ERR(pctrl->clk);
	पूर्ण

	ret = clk_prepare_enable(pctrl->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk enable failed\n");
		वापस ret;
	पूर्ण

	raw_spin_lock_init(&pctrl->lock);

	owl_pinctrl_desc.name = dev_name(&pdev->dev);
	owl_pinctrl_desc.pins = soc_data->pins;
	owl_pinctrl_desc.npins = soc_data->npins;

	pctrl->chip.direction_input  = owl_gpio_direction_input;
	pctrl->chip.direction_output = owl_gpio_direction_output;
	pctrl->chip.get = owl_gpio_get;
	pctrl->chip.set = owl_gpio_set;
	pctrl->chip.request = owl_gpio_request;
	pctrl->chip.मुक्त = owl_gpio_मुक्त;

	pctrl->soc = soc_data;
	pctrl->dev = &pdev->dev;

	pctrl->pctrldev = devm_pinctrl_रेजिस्टर(&pdev->dev,
					&owl_pinctrl_desc, pctrl);
	अगर (IS_ERR(pctrl->pctrldev)) अणु
		dev_err(&pdev->dev, "could not register Actions OWL pinmux driver\n");
		ret = PTR_ERR(pctrl->pctrldev);
		जाओ err_निकास;
	पूर्ण

	ret = platक्रमm_irq_count(pdev);
	अगर (ret < 0)
		जाओ err_निकास;

	pctrl->num_irq = ret;

	pctrl->irq = devm_kसुस्मृति(&pdev->dev, pctrl->num_irq,
					माप(*pctrl->irq), GFP_KERNEL);
	अगर (!pctrl->irq) अणु
		ret = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	क्रम (i = 0; i < pctrl->num_irq ; i++) अणु
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret < 0)
			जाओ err_निकास;
		pctrl->irq[i] = ret;
	पूर्ण

	ret = owl_gpio_init(pctrl);
	अगर (ret)
		जाओ err_निकास;

	platक्रमm_set_drvdata(pdev, pctrl);

	वापस 0;

err_निकास:
	clk_disable_unprepare(pctrl->clk);

	वापस ret;
पूर्ण
