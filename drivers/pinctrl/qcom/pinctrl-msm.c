<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, Sony Mobile Communications AB.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/reboot.h>
#समावेश <linux/pm.h>
#समावेश <linux/log2.h>
#समावेश <linux/qcom_scm.h>

#समावेश <linux/soc/qcom/irq.h>

#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "pinctrl-msm.h"
#समावेश "../pinctrl-utils.h"

#घोषणा MAX_NR_GPIO 300
#घोषणा MAX_NR_TILES 4
#घोषणा PS_HOLD_OFFSET 0x820

/**
 * काष्ठा msm_pinctrl - state क्रम a pinctrl-msm device
 * @dev:            device handle.
 * @pctrl:          pinctrl handle.
 * @chip:           gpiochip handle.
 * @desc:           pin controller descriptor
 * @restart_nb:     restart notअगरier block.
 * @irq_chip:       irq chip inक्रमmation
 * @irq:            parent irq क्रम the TLMM irq_chip.
 * @पूर्णांकr_target_use_scm: route irq to application cpu using scm calls
 * @lock:           Spinlock to protect रेजिस्टर resources as well
 *                  as msm_pinctrl data काष्ठाures.
 * @enabled_irqs:   Biपंचांगap of currently enabled irqs.
 * @dual_edge_irqs: Biपंचांगap of irqs that need sw emulated dual edge
 *                  detection.
 * @skip_wake_irqs: Skip IRQs that are handled by wakeup पूर्णांकerrupt controller
 * @disabled_क्रम_mux: These IRQs were disabled because we muxed away.
 * @soc:            Reference to soc_data of platक्रमm specअगरic data.
 * @regs:           Base addresses क्रम the TLMM tiles.
 * @phys_base:      Physical base address
 */
काष्ठा msm_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctrl;
	काष्ठा gpio_chip chip;
	काष्ठा pinctrl_desc desc;
	काष्ठा notअगरier_block restart_nb;

	काष्ठा irq_chip irq_chip;
	पूर्णांक irq;

	bool पूर्णांकr_target_use_scm;

	raw_spinlock_t lock;

	DECLARE_BITMAP(dual_edge_irqs, MAX_NR_GPIO);
	DECLARE_BITMAP(enabled_irqs, MAX_NR_GPIO);
	DECLARE_BITMAP(skip_wake_irqs, MAX_NR_GPIO);
	DECLARE_BITMAP(disabled_क्रम_mux, MAX_NR_GPIO);

	स्थिर काष्ठा msm_pinctrl_soc_data *soc;
	व्योम __iomem *regs[MAX_NR_TILES];
	u32 phys_base[MAX_NR_TILES];
पूर्ण;

#घोषणा MSM_ACCESSOR(name) \
अटल u32 msm_पढ़ोl_##name(काष्ठा msm_pinctrl *pctrl, \
			    स्थिर काष्ठा msm_pingroup *g) \
अणु \
	वापस पढ़ोl(pctrl->regs[g->tile] + g->name##_reg); \
पूर्ण \
अटल व्योम msm_ग_लिखोl_##name(u32 val, काष्ठा msm_pinctrl *pctrl, \
			      स्थिर काष्ठा msm_pingroup *g) \
अणु \
	ग_लिखोl(val, pctrl->regs[g->tile] + g->name##_reg); \
पूर्ण

MSM_ACCESSOR(ctl)
MSM_ACCESSOR(io)
MSM_ACCESSOR(पूर्णांकr_cfg)
MSM_ACCESSOR(पूर्णांकr_status)
MSM_ACCESSOR(पूर्णांकr_target)

अटल व्योम msm_ack_पूर्णांकr_status(काष्ठा msm_pinctrl *pctrl,
				स्थिर काष्ठा msm_pingroup *g)
अणु
	u32 val = g->पूर्णांकr_ack_high ? BIT(g->पूर्णांकr_status_bit) : 0;

	msm_ग_लिखोl_पूर्णांकr_status(val, pctrl, g);
पूर्ण

अटल पूर्णांक msm_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *msm_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->groups[group].name;
पूर्ण

अटल पूर्णांक msm_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित group,
			      स्थिर अचिन्हित **pins,
			      अचिन्हित *num_pins)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->soc->groups[group].pins;
	*num_pins = pctrl->soc->groups[group].npins;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops msm_pinctrl_ops = अणु
	.get_groups_count	= msm_get_groups_count,
	.get_group_name		= msm_get_group_name,
	.get_group_pins		= msm_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक msm_pinmux_request(काष्ठा pinctrl_dev *pctldev, अचिन्हित offset)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = &pctrl->chip;

	वापस gpiochip_line_is_valid(chip, offset) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक msm_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *msm_get_function_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित function)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->functions[function].name;
पूर्ण

अटल पूर्णांक msm_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित function,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->soc->functions[function].groups;
	*num_groups = pctrl->soc->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक msm_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित function,
			      अचिन्हित group)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *gc = &pctrl->chip;
	अचिन्हित पूर्णांक irq = irq_find_mapping(gc->irq.करोमुख्य, group);
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	अचिन्हित पूर्णांक gpio_func = pctrl->soc->gpio_func;
	स्थिर काष्ठा msm_pingroup *g;
	अचिन्हित दीर्घ flags;
	u32 val, mask;
	पूर्णांक i;

	g = &pctrl->soc->groups[group];
	mask = GENMASK(g->mux_bit + order_base_2(g->nfuncs) - 1, g->mux_bit);

	क्रम (i = 0; i < g->nfuncs; i++) अणु
		अगर (g->funcs[i] == function)
			अवरोध;
	पूर्ण

	अगर (WARN_ON(i == g->nfuncs))
		वापस -EINVAL;

	/*
	 * If an GPIO पूर्णांकerrupt is setup on this pin then we need special
	 * handling.  Specअगरically पूर्णांकerrupt detection logic will still see
	 * the pin twiddle even when we're muxed away.
	 *
	 * When we see a pin with an पूर्णांकerrupt setup on it then we'll disable
	 * (mask) पूर्णांकerrupts on it when we mux away until we mux back.  Note
	 * that disable_irq() refcounts and पूर्णांकerrupts are disabled as दीर्घ as
	 * at least one disable_irq() has been called.
	 */
	अगर (d && i != gpio_func &&
	    !test_and_set_bit(d->hwirq, pctrl->disabled_क्रम_mux))
		disable_irq(irq);

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_ctl(pctrl, g);
	val &= ~mask;
	val |= i << g->mux_bit;
	msm_ग_लिखोl_ctl(val, pctrl, g);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	अगर (d && i == gpio_func &&
	    test_and_clear_bit(d->hwirq, pctrl->disabled_क्रम_mux)) अणु
		/*
		 * Clear पूर्णांकerrupts detected जबतक not GPIO since we only
		 * masked things.
		 */
		अगर (d->parent_data && test_bit(d->hwirq, pctrl->skip_wake_irqs))
			irq_chip_set_parent_state(d, IRQCHIP_STATE_PENDING, false);
		अन्यथा
			msm_ack_पूर्णांकr_status(pctrl, g);

		enable_irq(irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm_pinmux_request_gpio(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset)
अणु
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा msm_pingroup *g = &pctrl->soc->groups[offset];

	/* No funcs? Probably ACPI so can't करो anything here */
	अगर (!g->nfuncs)
		वापस 0;

	वापस msm_pinmux_set_mux(pctldev, g->funcs[pctrl->soc->gpio_func], offset);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops msm_pinmux_ops = अणु
	.request		= msm_pinmux_request,
	.get_functions_count	= msm_get_functions_count,
	.get_function_name	= msm_get_function_name,
	.get_function_groups	= msm_get_function_groups,
	.gpio_request_enable	= msm_pinmux_request_gpio,
	.set_mux		= msm_pinmux_set_mux,
पूर्ण;

अटल पूर्णांक msm_config_reg(काष्ठा msm_pinctrl *pctrl,
			  स्थिर काष्ठा msm_pingroup *g,
			  अचिन्हित param,
			  अचिन्हित *mask,
			  अचिन्हित *bit)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
	हाल PIN_CONFIG_BIAS_PULL_UP:
		*bit = g->pull_bit;
		*mask = 3;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		*bit = g->od_bit;
		*mask = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		*bit = g->drv_bit;
		*mask = 7;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
	हाल PIN_CONFIG_INPUT_ENABLE:
		*bit = g->oe_bit;
		*mask = 1;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MSM_NO_PULL		0
#घोषणा MSM_PULL_DOWN		1
#घोषणा MSM_KEEPER		2
#घोषणा MSM_PULL_UP_NO_KEEPER	2
#घोषणा MSM_PULL_UP		3

अटल अचिन्हित msm_regval_to_drive(u32 val)
अणु
	वापस (val + 1) * 2;
पूर्ण

अटल पूर्णांक msm_config_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक group,
				अचिन्हित दीर्घ *config)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित param = pinconf_to_config_param(*config);
	अचिन्हित mask;
	अचिन्हित arg;
	अचिन्हित bit;
	पूर्णांक ret;
	u32 val;

	g = &pctrl->soc->groups[group];

	ret = msm_config_reg(pctrl, g, param, &mask, &bit);
	अगर (ret < 0)
		वापस ret;

	val = msm_पढ़ोl_ctl(pctrl, g);
	arg = (val >> bit) & mask;

	/* Convert रेजिस्टर value to pinconf value */
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (arg != MSM_NO_PULL)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (arg != MSM_PULL_DOWN)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		अगर (pctrl->soc->pull_no_keeper)
			वापस -ENOTSUPP;

		अगर (arg != MSM_KEEPER)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pctrl->soc->pull_no_keeper)
			arg = arg == MSM_PULL_UP_NO_KEEPER;
		अन्यथा
			arg = arg == MSM_PULL_UP;
		अगर (!arg)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		/* Pin is not खोलो-drain */
		अगर (!arg)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = msm_regval_to_drive(arg);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		/* Pin is not output */
		अगर (!arg)
			वापस -EINVAL;

		val = msm_पढ़ोl_io(pctrl, g);
		arg = !!(val & BIT(g->in_bit));
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		/* Pin is output */
		अगर (arg)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_config_group_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित group,
				अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	अचिन्हित param;
	अचिन्हित mask;
	अचिन्हित arg;
	अचिन्हित bit;
	पूर्णांक ret;
	u32 val;
	पूर्णांक i;

	g = &pctrl->soc->groups[group];

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		ret = msm_config_reg(pctrl, g, param, &mask, &bit);
		अगर (ret < 0)
			वापस ret;

		/* Convert pinconf values to रेजिस्टर values */
		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			arg = MSM_NO_PULL;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			arg = MSM_PULL_DOWN;
			अवरोध;
		हाल PIN_CONFIG_BIAS_BUS_HOLD:
			अगर (pctrl->soc->pull_no_keeper)
				वापस -ENOTSUPP;

			arg = MSM_KEEPER;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			अगर (pctrl->soc->pull_no_keeper)
				arg = MSM_PULL_UP_NO_KEEPER;
			अन्यथा
				arg = MSM_PULL_UP;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			arg = 1;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			/* Check क्रम invalid values */
			अगर (arg > 16 || arg < 2 || (arg % 2) != 0)
				arg = -1;
			अन्यथा
				arg = (arg / 2) - 1;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			/* set output value */
			raw_spin_lock_irqsave(&pctrl->lock, flags);
			val = msm_पढ़ोl_io(pctrl, g);
			अगर (arg)
				val |= BIT(g->out_bit);
			अन्यथा
				val &= ~BIT(g->out_bit);
			msm_ग_लिखोl_io(val, pctrl, g);
			raw_spin_unlock_irqrestore(&pctrl->lock, flags);

			/* enable output */
			arg = 1;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			/* disable output */
			arg = 0;
			अवरोध;
		शेष:
			dev_err(pctrl->dev, "Unsupported config parameter: %x\n",
				param);
			वापस -EINVAL;
		पूर्ण

		/* Range-check user-supplied value */
		अगर (arg & ~mask) अणु
			dev_err(pctrl->dev, "config %x: %x is invalid\n", param, arg);
			वापस -EINVAL;
		पूर्ण

		raw_spin_lock_irqsave(&pctrl->lock, flags);
		val = msm_पढ़ोl_ctl(pctrl, g);
		val &= ~(mask << bit);
		val |= arg << bit;
		msm_ग_लिखोl_ctl(val, pctrl, g);
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops msm_pinconf_ops = अणु
	.is_generic		= true,
	.pin_config_group_get	= msm_config_group_get,
	.pin_config_group_set	= msm_config_group_set,
पूर्ण;

अटल पूर्णांक msm_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 val;

	g = &pctrl->soc->groups[offset];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_ctl(pctrl, g);
	val &= ~BIT(g->oe_bit);
	msm_ग_लिखोl_ctl(val, pctrl, g);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 val;

	g = &pctrl->soc->groups[offset];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_io(pctrl, g);
	अगर (value)
		val |= BIT(g->out_bit);
	अन्यथा
		val &= ~BIT(g->out_bit);
	msm_ग_लिखोl_io(val, pctrl, g);

	val = msm_पढ़ोl_ctl(pctrl, g);
	val |= BIT(g->oe_bit);
	msm_ग_लिखोl_ctl(val, pctrl, g);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा msm_pingroup *g;
	u32 val;

	g = &pctrl->soc->groups[offset];

	val = msm_पढ़ोl_ctl(pctrl, g);

	वापस val & BIT(g->oe_bit) ? GPIO_LINE_सूचीECTION_OUT :
				      GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक msm_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	u32 val;

	g = &pctrl->soc->groups[offset];

	val = msm_पढ़ोl_io(pctrl, g);
	वापस !!(val & BIT(g->in_bit));
पूर्ण

अटल व्योम msm_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 val;

	g = &pctrl->soc->groups[offset];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_io(pctrl, g);
	अगर (value)
		val |= BIT(g->out_bit);
	अन्यथा
		val &= ~BIT(g->out_bit);
	msm_ग_लिखोl_io(val, pctrl, g);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल व्योम msm_gpio_dbg_show_one(काष्ठा seq_file *s,
				  काष्ठा pinctrl_dev *pctldev,
				  काष्ठा gpio_chip *chip,
				  अचिन्हित offset,
				  अचिन्हित gpio)
अणु
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित func;
	पूर्णांक is_out;
	पूर्णांक drive;
	पूर्णांक pull;
	पूर्णांक val;
	u32 ctl_reg, io_reg;

	अटल स्थिर अक्षर * स्थिर pulls_keeper[] = अणु
		"no pull",
		"pull down",
		"keeper",
		"pull up"
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर pulls_no_keeper[] = अणु
		"no pull",
		"pull down",
		"pull up",
	पूर्ण;

	अगर (!gpiochip_line_is_valid(chip, offset))
		वापस;

	g = &pctrl->soc->groups[offset];
	ctl_reg = msm_पढ़ोl_ctl(pctrl, g);
	io_reg = msm_पढ़ोl_io(pctrl, g);

	is_out = !!(ctl_reg & BIT(g->oe_bit));
	func = (ctl_reg >> g->mux_bit) & 7;
	drive = (ctl_reg >> g->drv_bit) & 7;
	pull = (ctl_reg >> g->pull_bit) & 3;

	अगर (is_out)
		val = !!(io_reg & BIT(g->out_bit));
	अन्यथा
		val = !!(io_reg & BIT(g->in_bit));

	seq_म_लिखो(s, " %-8s: %-3s", g->name, is_out ? "out" : "in");
	seq_म_लिखो(s, " %-4s func%d", val ? "high" : "low", func);
	seq_म_लिखो(s, " %dmA", msm_regval_to_drive(drive));
	अगर (pctrl->soc->pull_no_keeper)
		seq_म_लिखो(s, " %s", pulls_no_keeper[pull]);
	अन्यथा
		seq_म_लिखो(s, " %s", pulls_keeper[pull]);
	seq_माला_दो(s, "\n");
पूर्ण

अटल व्योम msm_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित gpio = chip->base;
	अचिन्हित i;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++)
		msm_gpio_dbg_show_one(s, शून्य, chip, i, gpio);
पूर्ण

#अन्यथा
#घोषणा msm_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल पूर्णांक msm_gpio_init_valid_mask(काष्ठा gpio_chip *gc,
				    अचिन्हित दीर्घ *valid_mask,
				    अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	पूर्णांक ret;
	अचिन्हित पूर्णांक len, i;
	स्थिर पूर्णांक *reserved = pctrl->soc->reserved_gpios;
	u16 *पंचांगp;

	/* Driver provided reserved list overrides DT and ACPI */
	अगर (reserved) अणु
		biपंचांगap_fill(valid_mask, ngpios);
		क्रम (i = 0; reserved[i] >= 0; i++) अणु
			अगर (i >= ngpios || reserved[i] >= ngpios) अणु
				dev_err(pctrl->dev, "invalid list of reserved GPIOs\n");
				वापस -EINVAL;
			पूर्ण
			clear_bit(reserved[i], valid_mask);
		पूर्ण

		वापस 0;
	पूर्ण

	/* The number of GPIOs in the ACPI tables */
	len = ret = device_property_count_u16(pctrl->dev, "gpios");
	अगर (ret < 0)
		वापस 0;

	अगर (ret > ngpios)
		वापस -EINVAL;

	पंचांगp = kदो_स्मृति_array(len, माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u16_array(pctrl->dev, "gpios", पंचांगp, len);
	अगर (ret < 0) अणु
		dev_err(pctrl->dev, "could not read list of GPIOs\n");
		जाओ out;
	पूर्ण

	biपंचांगap_zero(valid_mask, ngpios);
	क्रम (i = 0; i < len; i++)
		set_bit(पंचांगp[i], valid_mask);

out:
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा gpio_chip msm_gpio_ढाँचा = अणु
	.direction_input  = msm_gpio_direction_input,
	.direction_output = msm_gpio_direction_output,
	.get_direction    = msm_gpio_get_direction,
	.get              = msm_gpio_get,
	.set              = msm_gpio_set,
	.request          = gpiochip_generic_request,
	.मुक्त             = gpiochip_generic_मुक्त,
	.dbg_show         = msm_gpio_dbg_show,
पूर्ण;

/* For dual-edge पूर्णांकerrupts in software, since some hardware has no
 * such support:
 *
 * At appropriate moments, this function may be called to flip the polarity
 * settings of both-edge irq lines to try and catch the next edge.
 *
 * The attempt is considered successful अगर:
 * - the status bit goes high, indicating that an edge was caught, or
 * - the input value of the gpio करोesn't change during the attempt.
 * If the value changes twice during the process, that would cause the first
 * test to fail but would क्रमce the second, as two opposite
 * transitions would cause a detection no matter the polarity setting.
 *
 * The करो-loop tries to sledge-hammer बंदd the timing hole between
 * the initial value-पढ़ो and the polarity-ग_लिखो - अगर the line value changes
 * during that winकरोw, an पूर्णांकerrupt is lost, the new polarity setting is
 * incorrect, and the first success test will fail, causing a retry.
 *
 * Algorithm comes from Google's msmgpio driver.
 */
अटल व्योम msm_gpio_update_dual_edge_pos(काष्ठा msm_pinctrl *pctrl,
					  स्थिर काष्ठा msm_pingroup *g,
					  काष्ठा irq_data *d)
अणु
	पूर्णांक loop_limit = 100;
	अचिन्हित val, val2, पूर्णांकstat;
	अचिन्हित pol;

	करो अणु
		val = msm_पढ़ोl_io(pctrl, g) & BIT(g->in_bit);

		pol = msm_पढ़ोl_पूर्णांकr_cfg(pctrl, g);
		pol ^= BIT(g->पूर्णांकr_polarity_bit);
		msm_ग_लिखोl_पूर्णांकr_cfg(pol, pctrl, g);

		val2 = msm_पढ़ोl_io(pctrl, g) & BIT(g->in_bit);
		पूर्णांकstat = msm_पढ़ोl_पूर्णांकr_status(pctrl, g);
		अगर (पूर्णांकstat || (val == val2))
			वापस;
	पूर्ण जबतक (loop_limit-- > 0);
	dev_err(pctrl->dev, "dual-edge irq failed to stabilize, %#08x != %#08x\n",
		val, val2);
पूर्ण

अटल व्योम msm_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_pingroup *g;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (d->parent_data)
		irq_chip_mask_parent(d);

	अगर (test_bit(d->hwirq, pctrl->skip_wake_irqs))
		वापस;

	g = &pctrl->soc->groups[d->hwirq];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_पूर्णांकr_cfg(pctrl, g);
	/*
	 * There are two bits that control पूर्णांकerrupt क्रमwarding to the CPU. The
	 * RAW_STATUS_EN bit causes the level or edge sensed on the line to be
	 * latched पूर्णांकo the पूर्णांकerrupt status रेजिस्टर when the hardware detects
	 * an irq that it's configured क्रम (either edge क्रम edge type or level
	 * क्रम level type irq). The 'non-raw' status enable bit causes the
	 * hardware to निश्चित the summary पूर्णांकerrupt to the CPU अगर the latched
	 * status bit is set. There's a bug though, the edge detection logic
	 * seems to have a problem where toggling the RAW_STATUS_EN bit may
	 * cause the status bit to latch spuriously when there isn't any edge
	 * so we can't touch that bit क्रम edge type irqs and we have to keep
	 * the bit set anyway so that edges are latched जबतक the line is masked.
	 *
	 * To make matters more complicated, leaving the RAW_STATUS_EN bit
	 * enabled all the समय causes level पूर्णांकerrupts to re-latch पूर्णांकo the
	 * status रेजिस्टर because the level is still present on the line after
	 * we ack it. We clear the raw status enable bit during mask here and
	 * set the bit on unmask so the पूर्णांकerrupt can't latch पूर्णांकo the hardware
	 * जबतक it's masked.
	 */
	अगर (irqd_get_trigger_type(d) & IRQ_TYPE_LEVEL_MASK)
		val &= ~BIT(g->पूर्णांकr_raw_status_bit);

	val &= ~BIT(g->पूर्णांकr_enable_bit);
	msm_ग_लिखोl_पूर्णांकr_cfg(val, pctrl, g);

	clear_bit(d->hwirq, pctrl->enabled_irqs);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल व्योम msm_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_pingroup *g;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (d->parent_data)
		irq_chip_unmask_parent(d);

	अगर (test_bit(d->hwirq, pctrl->skip_wake_irqs))
		वापस;

	g = &pctrl->soc->groups[d->hwirq];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	val = msm_पढ़ोl_पूर्णांकr_cfg(pctrl, g);
	val |= BIT(g->पूर्णांकr_raw_status_bit);
	val |= BIT(g->पूर्णांकr_enable_bit);
	msm_ग_लिखोl_पूर्णांकr_cfg(val, pctrl, g);

	set_bit(d->hwirq, pctrl->enabled_irqs);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल व्योम msm_gpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	अगर (d->parent_data)
		irq_chip_enable_parent(d);

	अगर (!test_bit(d->hwirq, pctrl->skip_wake_irqs))
		msm_gpio_irq_unmask(d);
पूर्ण

अटल व्योम msm_gpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	अगर (d->parent_data)
		irq_chip_disable_parent(d);

	अगर (!test_bit(d->hwirq, pctrl->skip_wake_irqs))
		msm_gpio_irq_mask(d);
पूर्ण

/**
 * msm_gpio_update_dual_edge_parent() - Prime next edge क्रम IRQs handled by parent.
 * @d: The irq dta.
 *
 * This is much like msm_gpio_update_dual_edge_pos() but क्रम IRQs that are
 * normally handled by the parent irqchip.  The logic here is slightly
 * dअगरferent due to what's easy to do with our parent, but in principle it's
 * the same.
 */
अटल व्योम msm_gpio_update_dual_edge_parent(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_pingroup *g = &pctrl->soc->groups[d->hwirq];
	पूर्णांक loop_limit = 100;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक type;

	/* Read the value and make a guess about what edge we need to catch */
	val = msm_पढ़ोl_io(pctrl, g) & BIT(g->in_bit);
	type = val ? IRQ_TYPE_EDGE_FALLING : IRQ_TYPE_EDGE_RISING;

	करो अणु
		/* Set the parent to catch the next edge */
		irq_chip_set_type_parent(d, type);

		/*
		 * Possibly the line changed between when we last पढ़ो "val"
		 * (and decided what edge we needed) and when set the edge.
		 * If the value didn't change (or changed and then changed
		 * back) then we're करोne.
		 */
		val = msm_पढ़ोl_io(pctrl, g) & BIT(g->in_bit);
		अगर (type == IRQ_TYPE_EDGE_RISING) अणु
			अगर (!val)
				वापस;
			type = IRQ_TYPE_EDGE_FALLING;
		पूर्ण अन्यथा अगर (type == IRQ_TYPE_EDGE_FALLING) अणु
			अगर (val)
				वापस;
			type = IRQ_TYPE_EDGE_RISING;
		पूर्ण
	पूर्ण जबतक (loop_limit-- > 0);
	dev_warn_once(pctrl->dev, "dual-edge irq failed to stabilize\n");
पूर्ण

अटल व्योम msm_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_pingroup *g;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(d->hwirq, pctrl->skip_wake_irqs)) अणु
		अगर (test_bit(d->hwirq, pctrl->dual_edge_irqs))
			msm_gpio_update_dual_edge_parent(d);
		वापस;
	पूर्ण

	g = &pctrl->soc->groups[d->hwirq];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	msm_ack_पूर्णांकr_status(pctrl, g);

	अगर (test_bit(d->hwirq, pctrl->dual_edge_irqs))
		msm_gpio_update_dual_edge_pos(pctrl, g, d);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल bool msm_gpio_needs_dual_edge_parent_workaround(काष्ठा irq_data *d,
						       अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	वापस type == IRQ_TYPE_EDGE_BOTH &&
	       pctrl->soc->wakeirq_dual_edge_errata && d->parent_data &&
	       test_bit(d->hwirq, pctrl->skip_wake_irqs);
पूर्ण

अटल पूर्णांक msm_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_pingroup *g;
	अचिन्हित दीर्घ flags;
	bool was_enabled;
	u32 val;

	अगर (msm_gpio_needs_dual_edge_parent_workaround(d, type)) अणु
		set_bit(d->hwirq, pctrl->dual_edge_irqs);
		irq_set_handler_locked(d, handle_fasteoi_ack_irq);
		msm_gpio_update_dual_edge_parent(d);
		वापस 0;
	पूर्ण

	अगर (d->parent_data)
		irq_chip_set_type_parent(d, type);

	अगर (test_bit(d->hwirq, pctrl->skip_wake_irqs)) अणु
		clear_bit(d->hwirq, pctrl->dual_edge_irqs);
		irq_set_handler_locked(d, handle_fasteoi_irq);
		वापस 0;
	पूर्ण

	g = &pctrl->soc->groups[d->hwirq];

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	/*
	 * For hw without possibility of detecting both edges
	 */
	अगर (g->पूर्णांकr_detection_width == 1 && type == IRQ_TYPE_EDGE_BOTH)
		set_bit(d->hwirq, pctrl->dual_edge_irqs);
	अन्यथा
		clear_bit(d->hwirq, pctrl->dual_edge_irqs);

	/* Route पूर्णांकerrupts to application cpu.
	 * With पूर्णांकr_target_use_scm पूर्णांकerrupts are routed to
	 * application cpu using scm calls.
	 */
	अगर (pctrl->पूर्णांकr_target_use_scm) अणु
		u32 addr = pctrl->phys_base[0] + g->पूर्णांकr_target_reg;
		पूर्णांक ret;

		qcom_scm_io_पढ़ोl(addr, &val);

		val &= ~(7 << g->पूर्णांकr_target_bit);
		val |= g->पूर्णांकr_target_kpss_val << g->पूर्णांकr_target_bit;

		ret = qcom_scm_io_ग_लिखोl(addr, val);
		अगर (ret)
			dev_err(pctrl->dev,
				"Failed routing %lu interrupt to Apps proc",
				d->hwirq);
	पूर्ण अन्यथा अणु
		val = msm_पढ़ोl_पूर्णांकr_target(pctrl, g);
		val &= ~(7 << g->पूर्णांकr_target_bit);
		val |= g->पूर्णांकr_target_kpss_val << g->पूर्णांकr_target_bit;
		msm_ग_लिखोl_पूर्णांकr_target(val, pctrl, g);
	पूर्ण

	/* Update configuration क्रम gpio.
	 * RAW_STATUS_EN is left on क्रम all gpio irqs. Due to the
	 * पूर्णांकernal circuitry of TLMM, toggling the RAW_STATUS
	 * could cause the INTR_STATUS to be set क्रम EDGE पूर्णांकerrupts.
	 */
	val = msm_पढ़ोl_पूर्णांकr_cfg(pctrl, g);
	was_enabled = val & BIT(g->पूर्णांकr_raw_status_bit);
	val |= BIT(g->पूर्णांकr_raw_status_bit);
	अगर (g->पूर्णांकr_detection_width == 2) अणु
		val &= ~(3 << g->पूर्णांकr_detection_bit);
		val &= ~(1 << g->पूर्णांकr_polarity_bit);
		चयन (type) अणु
		हाल IRQ_TYPE_EDGE_RISING:
			val |= 1 << g->पूर्णांकr_detection_bit;
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		हाल IRQ_TYPE_EDGE_FALLING:
			val |= 2 << g->पूर्णांकr_detection_bit;
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		हाल IRQ_TYPE_EDGE_BOTH:
			val |= 3 << g->पूर्णांकr_detection_bit;
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			अवरोध;
		हाल IRQ_TYPE_LEVEL_HIGH:
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (g->पूर्णांकr_detection_width == 1) अणु
		val &= ~(1 << g->पूर्णांकr_detection_bit);
		val &= ~(1 << g->पूर्णांकr_polarity_bit);
		चयन (type) अणु
		हाल IRQ_TYPE_EDGE_RISING:
			val |= BIT(g->पूर्णांकr_detection_bit);
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		हाल IRQ_TYPE_EDGE_FALLING:
			val |= BIT(g->पूर्णांकr_detection_bit);
			अवरोध;
		हाल IRQ_TYPE_EDGE_BOTH:
			val |= BIT(g->पूर्णांकr_detection_bit);
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			अवरोध;
		हाल IRQ_TYPE_LEVEL_HIGH:
			val |= BIT(g->पूर्णांकr_polarity_bit);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	msm_ग_लिखोl_पूर्णांकr_cfg(val, pctrl, g);

	/*
	 * The first समय we set RAW_STATUS_EN it could trigger an पूर्णांकerrupt.
	 * Clear the पूर्णांकerrupt.  This is safe because we have
	 * IRQCHIP_SET_TYPE_MASKED.
	 */
	अगर (!was_enabled)
		msm_ack_पूर्णांकr_status(pctrl, g);

	अगर (test_bit(d->hwirq, pctrl->dual_edge_irqs))
		msm_gpio_update_dual_edge_pos(pctrl, g, d);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		irq_set_handler_locked(d, handle_edge_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	/*
	 * While they may not wake up when the TLMM is घातered off,
	 * some GPIOs would like to wakeup the प्रणाली from suspend
	 * when TLMM is घातered on. To allow that, enable the GPIO
	 * summary line to be wakeup capable at GIC.
	 */
	अगर (d->parent_data && test_bit(d->hwirq, pctrl->skip_wake_irqs))
		वापस irq_chip_set_wake_parent(d, on);

	वापस irq_set_irq_wake(pctrl->irq, on);
पूर्ण

अटल पूर्णांक msm_gpio_irq_reqres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	पूर्णांक ret;

	अगर (!try_module_get(gc->owner))
		वापस -ENODEV;

	ret = msm_pinmux_request_gpio(pctrl->pctrl, शून्य, d->hwirq);
	अगर (ret)
		जाओ out;
	msm_gpio_direction_input(gc, d->hwirq);

	अगर (gpiochip_lock_as_irq(gc, d->hwirq)) अणु
		dev_err(gc->parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			d->hwirq);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * The disable / clear-enable workaround we करो in msm_pinmux_set_mux()
	 * only works अगर disable is not lazy since we only clear any bogus
	 * पूर्णांकerrupt in hardware. Explicitly mark the पूर्णांकerrupt as UNLAZY.
	 */
	irq_set_status_flags(d->irq, IRQ_DISABLE_UNLAZY);

	वापस 0;
out:
	module_put(gc->owner);
	वापस ret;
पूर्ण

अटल व्योम msm_gpio_irq_relres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gpiochip_unlock_as_irq(gc, d->hwirq);
	module_put(gc->owner);
पूर्ण

अटल पूर्णांक msm_gpio_irq_set_affinity(काष्ठा irq_data *d,
				स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	अगर (d->parent_data && test_bit(d->hwirq, pctrl->skip_wake_irqs))
		वापस irq_chip_set_affinity_parent(d, dest, क्रमce);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpio_irq_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu_info)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);

	अगर (d->parent_data && test_bit(d->hwirq, pctrl->skip_wake_irqs))
		वापस irq_chip_set_vcpu_affinity_parent(d, vcpu_info);

	वापस 0;
पूर्ण

अटल व्योम msm_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	स्थिर काष्ठा msm_pingroup *g;
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक irq_pin;
	पूर्णांक handled = 0;
	u32 val;
	पूर्णांक i;

	chained_irq_enter(chip, desc);

	/*
	 * Each pin has it's own IRQ status रेजिस्टर, so use
	 * enabled_irq biपंचांगap to limit the number of पढ़ोs.
	 */
	क्रम_each_set_bit(i, pctrl->enabled_irqs, pctrl->chip.ngpio) अणु
		g = &pctrl->soc->groups[i];
		val = msm_पढ़ोl_पूर्णांकr_status(pctrl, g);
		अगर (val & BIT(g->पूर्णांकr_status_bit)) अणु
			irq_pin = irq_find_mapping(gc->irq.करोमुख्य, i);
			generic_handle_irq(irq_pin);
			handled++;
		पूर्ण
	पूर्ण

	/* No पूर्णांकerrupts were flagged */
	अगर (handled == 0)
		handle_bad_irq(desc);

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक msm_gpio_wakeirq(काष्ठा gpio_chip *gc,
			    अचिन्हित पूर्णांक child,
			    अचिन्हित पूर्णांक child_type,
			    अचिन्हित पूर्णांक *parent,
			    अचिन्हित पूर्णांक *parent_type)
अणु
	काष्ठा msm_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा msm_gpio_wakeirq_map *map;
	पूर्णांक i;

	*parent = GPIO_NO_WAKE_IRQ;
	*parent_type = IRQ_TYPE_EDGE_RISING;

	क्रम (i = 0; i < pctrl->soc->nwakeirq_map; i++) अणु
		map = &pctrl->soc->wakeirq_map[i];
		अगर (map->gpio == child) अणु
			*parent = map->wakeirq;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool msm_gpio_needs_valid_mask(काष्ठा msm_pinctrl *pctrl)
अणु
	अगर (pctrl->soc->reserved_gpios)
		वापस true;

	वापस device_property_count_u16(pctrl->dev, "gpios") > 0;
पूर्ण

अटल पूर्णांक msm_gpio_init(काष्ठा msm_pinctrl *pctrl)
अणु
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक i, ret;
	अचिन्हित gpio, ngpio = pctrl->soc->ngpios;
	काष्ठा device_node *np;
	bool skip;

	अगर (WARN_ON(ngpio > MAX_NR_GPIO))
		वापस -EINVAL;

	chip = &pctrl->chip;
	chip->base = -1;
	chip->ngpio = ngpio;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->owner = THIS_MODULE;
	chip->of_node = pctrl->dev->of_node;
	अगर (msm_gpio_needs_valid_mask(pctrl))
		chip->init_valid_mask = msm_gpio_init_valid_mask;

	pctrl->irq_chip.name = "msmgpio";
	pctrl->irq_chip.irq_enable = msm_gpio_irq_enable;
	pctrl->irq_chip.irq_disable = msm_gpio_irq_disable;
	pctrl->irq_chip.irq_mask = msm_gpio_irq_mask;
	pctrl->irq_chip.irq_unmask = msm_gpio_irq_unmask;
	pctrl->irq_chip.irq_ack = msm_gpio_irq_ack;
	pctrl->irq_chip.irq_set_type = msm_gpio_irq_set_type;
	pctrl->irq_chip.irq_set_wake = msm_gpio_irq_set_wake;
	pctrl->irq_chip.irq_request_resources = msm_gpio_irq_reqres;
	pctrl->irq_chip.irq_release_resources = msm_gpio_irq_relres;
	pctrl->irq_chip.irq_set_affinity = msm_gpio_irq_set_affinity;
	pctrl->irq_chip.irq_set_vcpu_affinity = msm_gpio_irq_set_vcpu_affinity;
	pctrl->irq_chip.flags = IRQCHIP_MASK_ON_SUSPEND |
				IRQCHIP_SET_TYPE_MASKED |
				IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND;

	np = of_parse_phandle(pctrl->dev->of_node, "wakeup-parent", 0);
	अगर (np) अणु
		chip->irq.parent_करोमुख्य = irq_find_matching_host(np,
						 DOMAIN_BUS_WAKEUP);
		of_node_put(np);
		अगर (!chip->irq.parent_करोमुख्य)
			वापस -EPROBE_DEFER;
		chip->irq.child_to_parent_hwirq = msm_gpio_wakeirq;
		pctrl->irq_chip.irq_eoi = irq_chip_eoi_parent;
		/*
		 * Let's skip handling the GPIOs, अगर the parent irqchip
		 * is handling the direct connect IRQ of the GPIO.
		 */
		skip = irq_करोमुख्य_qcom_handle_wakeup(chip->irq.parent_करोमुख्य);
		क्रम (i = 0; skip && i < pctrl->soc->nwakeirq_map; i++) अणु
			gpio = pctrl->soc->wakeirq_map[i].gpio;
			set_bit(gpio, pctrl->skip_wake_irqs);
		पूर्ण
	पूर्ण

	girq = &chip->irq;
	girq->chip = &pctrl->irq_chip;
	girq->parent_handler = msm_gpio_irq_handler;
	girq->fwnode = pctrl->dev->fwnode;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(pctrl->dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = pctrl->irq;

	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "Failed register gpiochip\n");
		वापस ret;
	पूर्ण

	/*
	 * For DeviceTree-supported प्रणालीs, the gpio core checks the
	 * pinctrl's device node क्रम the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * क्रम the driver. In this हाल the driver can skip ahead.
	 *
	 * In order to reमुख्य compatible with older, existing DeviceTree
	 * files which करोn't set the "gpio-ranges" property or प्रणालीs that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	अगर (!of_property_पढ़ो_bool(pctrl->dev->of_node, "gpio-ranges")) अणु
		ret = gpiochip_add_pin_range(&pctrl->chip,
			dev_name(pctrl->dev), 0, 0, chip->ngpio);
		अगर (ret) अणु
			dev_err(pctrl->dev, "Failed to add pin range\n");
			gpiochip_हटाओ(&pctrl->chip);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm_ps_hold_restart(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			       व्योम *data)
अणु
	काष्ठा msm_pinctrl *pctrl = container_of(nb, काष्ठा msm_pinctrl, restart_nb);

	ग_लिखोl(0, pctrl->regs[0] + PS_HOLD_OFFSET);
	mdelay(1000);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा msm_pinctrl *घातeroff_pctrl;

अटल व्योम msm_ps_hold_घातeroff(व्योम)
अणु
	msm_ps_hold_restart(&घातeroff_pctrl->restart_nb, 0, शून्य);
पूर्ण

अटल व्योम msm_pinctrl_setup_pm_reset(काष्ठा msm_pinctrl *pctrl)
अणु
	पूर्णांक i;
	स्थिर काष्ठा msm_function *func = pctrl->soc->functions;

	क्रम (i = 0; i < pctrl->soc->nfunctions; i++)
		अगर (!म_भेद(func[i].name, "ps_hold")) अणु
			pctrl->restart_nb.notअगरier_call = msm_ps_hold_restart;
			pctrl->restart_nb.priority = 128;
			अगर (रेजिस्टर_restart_handler(&pctrl->restart_nb))
				dev_err(pctrl->dev,
					"failed to setup restart handler.\n");
			घातeroff_pctrl = pctrl;
			pm_घातer_off = msm_ps_hold_घातeroff;
			अवरोध;
		पूर्ण
पूर्ण

अटल __maybe_unused पूर्णांक msm_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा msm_pinctrl *pctrl = dev_get_drvdata(dev);

	वापस pinctrl_क्रमce_sleep(pctrl->pctrl);
पूर्ण

अटल __maybe_unused पूर्णांक msm_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा msm_pinctrl *pctrl = dev_get_drvdata(dev);

	वापस pinctrl_क्रमce_शेष(pctrl->pctrl);
पूर्ण

SIMPLE_DEV_PM_OPS(msm_pinctrl_dev_pm_ops, msm_pinctrl_suspend,
		  msm_pinctrl_resume);

EXPORT_SYMBOL(msm_pinctrl_dev_pm_ops);

पूर्णांक msm_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      स्थिर काष्ठा msm_pinctrl_soc_data *soc_data)
अणु
	काष्ठा msm_pinctrl *pctrl;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक i;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = &pdev->dev;
	pctrl->soc = soc_data;
	pctrl->chip = msm_gpio_ढाँचा;
	pctrl->पूर्णांकr_target_use_scm = of_device_is_compatible(
					pctrl->dev->of_node,
					"qcom,ipq8064-pinctrl");

	raw_spin_lock_init(&pctrl->lock);

	अगर (soc_data->tiles) अणु
		क्रम (i = 0; i < soc_data->ntiles; i++) अणु
			res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
							   soc_data->tiles[i]);
			pctrl->regs[i] = devm_ioremap_resource(&pdev->dev, res);
			अगर (IS_ERR(pctrl->regs[i]))
				वापस PTR_ERR(pctrl->regs[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		pctrl->regs[0] = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(pctrl->regs[0]))
			वापस PTR_ERR(pctrl->regs[0]);

		pctrl->phys_base[0] = res->start;
	पूर्ण

	msm_pinctrl_setup_pm_reset(pctrl);

	pctrl->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pctrl->irq < 0)
		वापस pctrl->irq;

	pctrl->desc.owner = THIS_MODULE;
	pctrl->desc.pctlops = &msm_pinctrl_ops;
	pctrl->desc.pmxops = &msm_pinmux_ops;
	pctrl->desc.confops = &msm_pinconf_ops;
	pctrl->desc.name = dev_name(&pdev->dev);
	pctrl->desc.pins = pctrl->soc->pins;
	pctrl->desc.npins = pctrl->soc->npins;

	pctrl->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctrl->desc, pctrl);
	अगर (IS_ERR(pctrl->pctrl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(pctrl->pctrl);
	पूर्ण

	ret = msm_gpio_init(pctrl);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, pctrl);

	dev_dbg(&pdev->dev, "Probed Qualcomm pinctrl driver\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(msm_pinctrl_probe);

पूर्णांक msm_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_pinctrl *pctrl = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&pctrl->chip);

	unरेजिस्टर_restart_handler(&pctrl->restart_nb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(msm_pinctrl_हटाओ);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. TLMM driver");
MODULE_LICENSE("GPL v2");
