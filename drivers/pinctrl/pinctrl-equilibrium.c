<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019 Intel Corporation */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinmux.h"
#समावेश "pinctrl-equilibrium.h"

#घोषणा PIN_NAME_FMT	"io-%d"
#घोषणा PIN_NAME_LEN	10
#घोषणा PAD_REG_OFF	0x100

अटल व्योम eqbr_gpio_disable_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा eqbr_gpio_ctrl *gctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gctrl->lock, flags);
	ग_लिखोl(BIT(offset), gctrl->membase + GPIO_IRNENCLR);
	raw_spin_unlock_irqrestore(&gctrl->lock, flags);
पूर्ण

अटल व्योम eqbr_gpio_enable_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा eqbr_gpio_ctrl *gctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	gc->direction_input(gc, offset);
	raw_spin_lock_irqsave(&gctrl->lock, flags);
	ग_लिखोl(BIT(offset), gctrl->membase + GPIO_IRNRNSET);
	raw_spin_unlock_irqrestore(&gctrl->lock, flags);
पूर्ण

अटल व्योम eqbr_gpio_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा eqbr_gpio_ctrl *gctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gctrl->lock, flags);
	ग_लिखोl(BIT(offset), gctrl->membase + GPIO_IRNCR);
	raw_spin_unlock_irqrestore(&gctrl->lock, flags);
पूर्ण

अटल व्योम eqbr_gpio_mask_ack_irq(काष्ठा irq_data *d)
अणु
	eqbr_gpio_disable_irq(d);
	eqbr_gpio_ack_irq(d);
पूर्ण

अटल अंतरभूत व्योम eqbr_cfg_bit(व्योम __iomem *addr,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक set)
अणु
	अगर (set)
		ग_लिखोl(पढ़ोl(addr) | BIT(offset), addr);
	अन्यथा
		ग_लिखोl(पढ़ोl(addr) & ~BIT(offset), addr);
पूर्ण

अटल पूर्णांक eqbr_irq_type_cfg(काष्ठा gpio_irq_type *type,
			     काष्ठा eqbr_gpio_ctrl *gctrl,
			     अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&gctrl->lock, flags);
	eqbr_cfg_bit(gctrl->membase + GPIO_IRNCFG, offset, type->trig_type);
	eqbr_cfg_bit(gctrl->membase + GPIO_EXINTCR1, offset, type->trig_type);
	eqbr_cfg_bit(gctrl->membase + GPIO_EXINTCR0, offset, type->logic_type);
	raw_spin_unlock_irqrestore(&gctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_gpio_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा eqbr_gpio_ctrl *gctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक offset = irqd_to_hwirq(d);
	काष्ठा gpio_irq_type it;

	स_रखो(&it, 0, माप(it));

	अगर ((type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_NONE)
		वापस 0;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		it.trig_type = GPIO_EDGE_TRIG;
		it.edge_type = GPIO_SINGLE_EDGE;
		it.logic_type = GPIO_POSITIVE_TRIG;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		it.trig_type = GPIO_EDGE_TRIG;
		it.edge_type = GPIO_SINGLE_EDGE;
		it.logic_type = GPIO_NEGATIVE_TRIG;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		it.trig_type = GPIO_EDGE_TRIG;
		it.edge_type = GPIO_BOTH_EDGE;
		it.logic_type = GPIO_POSITIVE_TRIG;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		it.trig_type = GPIO_LEVEL_TRIG;
		it.edge_type = GPIO_SINGLE_EDGE;
		it.logic_type = GPIO_POSITIVE_TRIG;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		it.trig_type = GPIO_LEVEL_TRIG;
		it.edge_type = GPIO_SINGLE_EDGE;
		it.logic_type = GPIO_NEGATIVE_TRIG;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	eqbr_irq_type_cfg(&it, gctrl, offset);
	अगर (it.trig_type == GPIO_EDGE_TRIG)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);

	वापस 0;
पूर्ण

अटल व्योम eqbr_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा eqbr_gpio_ctrl *gctrl = gpiochip_get_data(gc);
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ pins, offset;

	chained_irq_enter(ic, desc);
	pins = पढ़ोl(gctrl->membase + GPIO_IRNCR);

	क्रम_each_set_bit(offset, &pins, gc->ngpio)
		generic_handle_irq(irq_find_mapping(gc->irq.करोमुख्य, offset));

	chained_irq_निकास(ic, desc);
पूर्ण

अटल पूर्णांक gpiochip_setup(काष्ठा device *dev, काष्ठा eqbr_gpio_ctrl *gctrl)
अणु
	काष्ठा gpio_irq_chip *girq;
	काष्ठा gpio_chip *gc;

	gc = &gctrl->chip;
	gc->label = gctrl->name;
#अगर defined(CONFIG_OF_GPIO)
	gc->of_node = gctrl->node;
#पूर्ण_अगर

	अगर (!of_property_पढ़ो_bool(gctrl->node, "interrupt-controller")) अणु
		dev_dbg(dev, "gc %s: doesn't act as interrupt controller!\n",
			gctrl->name);
		वापस 0;
	पूर्ण

	gctrl->ic.name = "gpio_irq";
	gctrl->ic.irq_mask = eqbr_gpio_disable_irq;
	gctrl->ic.irq_unmask = eqbr_gpio_enable_irq;
	gctrl->ic.irq_ack = eqbr_gpio_ack_irq;
	gctrl->ic.irq_mask_ack = eqbr_gpio_mask_ack_irq;
	gctrl->ic.irq_set_type = eqbr_gpio_set_irq_type;

	girq = &gctrl->chip.irq;
	girq->chip = &gctrl->ic;
	girq->parent_handler = eqbr_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents), GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;

	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = gctrl->virq;

	वापस 0;
पूर्ण

अटल पूर्णांक gpiolib_reg(काष्ठा eqbr_pinctrl_drv_data *drvdata)
अणु
	काष्ठा device *dev = drvdata->dev;
	काष्ठा eqbr_gpio_ctrl *gctrl;
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक i, ret;

	क्रम (i = 0; i < drvdata->nr_gpio_ctrls; i++) अणु
		gctrl = drvdata->gpio_ctrls + i;
		np = gctrl->node;

		gctrl->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "gpiochip%d", i);
		अगर (!gctrl->name)
			वापस -ENOMEM;

		अगर (of_address_to_resource(np, 0, &res)) अणु
			dev_err(dev, "Failed to get GPIO register address\n");
			वापस -ENXIO;
		पूर्ण

		gctrl->membase = devm_ioremap_resource(dev, &res);
		अगर (IS_ERR(gctrl->membase))
			वापस PTR_ERR(gctrl->membase);

		gctrl->virq = irq_of_parse_and_map(np, 0);
		अगर (!gctrl->virq) अणु
			dev_err(dev, "%s: failed to parse and map irq\n",
				gctrl->name);
			वापस -ENXIO;
		पूर्ण
		raw_spin_lock_init(&gctrl->lock);

		ret = bgpio_init(&gctrl->chip, dev, gctrl->bank->nr_pins / 8,
				 gctrl->membase + GPIO_IN,
				 gctrl->membase + GPIO_OUTSET,
				 gctrl->membase + GPIO_OUTCLR,
				 gctrl->membase + GPIO_सूची,
				 शून्य, 0);
		अगर (ret) अणु
			dev_err(dev, "unable to init generic GPIO\n");
			वापस ret;
		पूर्ण

		ret = gpiochip_setup(dev, gctrl);
		अगर (ret)
			वापस ret;

		ret = devm_gpiochip_add_data(dev, &gctrl->chip, gctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा eqbr_pin_bank
*find_pinbank_via_pin(काष्ठा eqbr_pinctrl_drv_data *pctl, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा eqbr_pin_bank *bank;
	पूर्णांक i;

	क्रम (i = 0; i < pctl->nr_banks; i++) अणु
		bank = &pctl->pin_banks[i];
		अगर (pin >= bank->pin_base &&
		    (pin - bank->pin_base) < bank->nr_pins)
			वापस bank;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops eqbr_pctl_ops = अणु
	.get_groups_count	= pinctrl_generic_get_group_count,
	.get_group_name		= pinctrl_generic_get_group_name,
	.get_group_pins		= pinctrl_generic_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map		= pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक eqbr_set_pin_mux(काष्ठा eqbr_pinctrl_drv_data *pctl,
			    अचिन्हित पूर्णांक pmx, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा eqbr_pin_bank *bank;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;
	व्योम __iomem *mem;

	bank = find_pinbank_via_pin(pctl, pin);
	अगर (!bank) अणु
		dev_err(pctl->dev, "Couldn't find pin bank for pin %u\n", pin);
		वापस -ENODEV;
	पूर्ण
	mem = bank->membase;
	offset = pin - bank->pin_base;

	अगर (!(bank->aval_pinmap & BIT(offset))) अणु
		dev_err(pctl->dev,
			"PIN: %u is not valid, pinbase: %u, bitmap: %u\n",
			pin, bank->pin_base, bank->aval_pinmap);
		वापस -ENODEV;
	पूर्ण

	raw_spin_lock_irqsave(&pctl->lock, flags);
	ग_लिखोl(pmx, mem + (offset * 4));
	raw_spin_unlock_irqrestore(&pctl->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक group)
अणु
	काष्ठा eqbr_pinctrl_drv_data *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	अचिन्हित पूर्णांक *pinmux;
	पूर्णांक i;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	pinmux = grp->data;
	क्रम (i = 0; i < grp->num_pins; i++)
		eqbr_set_pin_mux(pctl, pinmux[i], grp->pins[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinmux_gpio_request(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित पूर्णांक pin)
अणु
	काष्ठा eqbr_pinctrl_drv_data *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस eqbr_set_pin_mux(pctl, EQBR_GPIO_MODE, pin);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops eqbr_pinmux_ops = अणु
	.get_functions_count	= pinmux_generic_get_function_count,
	.get_function_name	= pinmux_generic_get_function_name,
	.get_function_groups	= pinmux_generic_get_function_groups,
	.set_mux		= eqbr_pinmux_set_mux,
	.gpio_request_enable	= eqbr_pinmux_gpio_request,
	.strict			= true,
पूर्ण;

अटल पूर्णांक get_drv_cur(व्योम __iomem *mem, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक idx = offset / DRV_CUR_PINS; /* 0-15, 16-31 per रेजिस्टर*/
	अचिन्हित पूर्णांक pin_offset = offset % DRV_CUR_PINS;

	वापस PARSE_DRV_CURRENT(पढ़ोl(mem + REG_DRCC(idx)), pin_offset);
पूर्ण

अटल काष्ठा eqbr_gpio_ctrl
*get_gpio_ctrls_via_bank(काष्ठा eqbr_pinctrl_drv_data *pctl,
			काष्ठा eqbr_pin_bank *bank)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->nr_gpio_ctrls; i++) अणु
		अगर (pctl->gpio_ctrls[i].bank == bank)
			वापस &pctl->gpio_ctrls[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक eqbr_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *config)
अणु
	काष्ठा eqbr_pinctrl_drv_data *pctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	काष्ठा eqbr_gpio_ctrl *gctrl;
	काष्ठा eqbr_pin_bank *bank;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;
	व्योम __iomem *mem;
	u32 val;

	bank = find_pinbank_via_pin(pctl, pin);
	अगर (!bank) अणु
		dev_err(pctl->dev, "Couldn't find pin bank for pin %u\n", pin);
		वापस -ENODEV;
	पूर्ण
	mem = bank->membase;
	offset = pin - bank->pin_base;

	अगर (!(bank->aval_pinmap & BIT(offset))) अणु
		dev_err(pctl->dev,
			"PIN: %u is not valid, pinbase: %u, bitmap: %u\n",
			pin, bank->pin_base, bank->aval_pinmap);
		वापस -ENODEV;
	पूर्ण

	raw_spin_lock_irqsave(&pctl->lock, flags);
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		val = !!(पढ़ोl(mem + REG_PUEN) & BIT(offset));
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		val = !!(पढ़ोl(mem + REG_PDEN) & BIT(offset));
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		val = !!(पढ़ोl(mem + REG_OD) & BIT(offset));
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		val = get_drv_cur(mem, offset);
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		val = !!(पढ़ोl(mem + REG_SRC) & BIT(offset));
		अवरोध;
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		gctrl = get_gpio_ctrls_via_bank(pctl, bank);
		अगर (!gctrl) अणु
			dev_err(pctl->dev, "Failed to find gpio via bank pinbase: %u, pin: %u\n",
				bank->pin_base, pin);
			raw_spin_unlock_irqrestore(&pctl->lock, flags);
			वापस -ENODEV;
		पूर्ण
		val = !!(पढ़ोl(gctrl->membase + GPIO_सूची) & BIT(offset));
		अवरोध;
	शेष:
		raw_spin_unlock_irqrestore(&pctl->lock, flags);
		वापस -ENOTSUPP;
	पूर्ण
	raw_spin_unlock_irqrestore(&pctl->lock, flags);
	*config = pinconf_to_config_packed(param, val);
;
	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा eqbr_pinctrl_drv_data *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा eqbr_gpio_ctrl *gctrl;
	क्रमागत pin_config_param param;
	काष्ठा eqbr_pin_bank *bank;
	अचिन्हित पूर्णांक val, offset;
	काष्ठा gpio_chip *gc;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *mem;
	u32 regval, mask;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		val = pinconf_to_config_argument(configs[i]);

		bank = find_pinbank_via_pin(pctl, pin);
		अगर (!bank) अणु
			dev_err(pctl->dev,
				"Couldn't find pin bank for pin %u\n", pin);
			वापस -ENODEV;
		पूर्ण
		mem = bank->membase;
		offset = pin - bank->pin_base;

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			mem += REG_PUEN;
			mask = BIT(offset);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			mem += REG_PDEN;
			mask = BIT(offset);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			mem += REG_OD;
			mask = BIT(offset);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			mem += REG_DRCC(offset / DRV_CUR_PINS);
			offset = (offset % DRV_CUR_PINS) * 2;
			mask = GENMASK(1, 0) << offset;
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			mem += REG_SRC;
			mask = BIT(offset);
			अवरोध;
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			gctrl = get_gpio_ctrls_via_bank(pctl, bank);
			अगर (!gctrl) अणु
				dev_err(pctl->dev, "Failed to find gpio via bank pinbase: %u, pin: %u\n",
					bank->pin_base, pin);
				वापस -ENODEV;
			पूर्ण
			gc = &gctrl->chip;
			gc->direction_output(gc, offset, 0);
			जारी;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		raw_spin_lock_irqsave(&pctl->lock, flags);
		regval = पढ़ोl(mem);
		regval = (regval & ~mask) | ((val << offset) & mask);
		ग_लिखोl(regval, mem);
		raw_spin_unlock_irqrestore(&pctl->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक i, npins, old = 0;
	स्थिर अचिन्हित पूर्णांक *pins;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		अगर (eqbr_pinconf_get(pctldev, pins[i], config))
			वापस -ENOTSUPP;

		अगर (i && old != *config)
			वापस -ENOTSUPP;

		old = *config;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक i, npins;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		ret = eqbr_pinconf_set(pctldev, pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops eqbr_pinconf_ops = अणु
	.is_generic			= true,
	.pin_config_get			= eqbr_pinconf_get,
	.pin_config_set			= eqbr_pinconf_set,
	.pin_config_group_get		= eqbr_pinconf_group_get,
	.pin_config_group_set		= eqbr_pinconf_group_set,
	.pin_config_config_dbg_show	= pinconf_generic_dump_config,
पूर्ण;

अटल bool is_func_exist(काष्ठा eqbr_pmx_func *funcs, स्थिर अक्षर *name,
			 अचिन्हित पूर्णांक nr_funcs, अचिन्हित पूर्णांक *idx)
अणु
	पूर्णांक i;

	अगर (!funcs)
		वापस false;

	क्रम (i = 0; i < nr_funcs; i++) अणु
		अगर (funcs[i].name && !म_भेद(funcs[i].name, name)) अणु
			*idx = i;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक funcs_utils(काष्ठा device *dev, काष्ठा eqbr_pmx_func *funcs,
		       अचिन्हित पूर्णांक *nr_funcs, funcs_util_ops op)
अणु
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *np;
	काष्ठा property *prop;
	स्थिर अक्षर *fn_name;
	अचिन्हित पूर्णांक fid;
	पूर्णांक i, j;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		prop = of_find_property(np, "groups", शून्य);
		अगर (!prop)
			जारी;

		अगर (of_property_पढ़ो_string(np, "function", &fn_name)) अणु
			/* some groups may not have function, it's OK */
			dev_dbg(dev, "Group %s: not function binded!\n",
				(अक्षर *)prop->value);
			जारी;
		पूर्ण

		चयन (op) अणु
		हाल OP_COUNT_NR_FUNCS:
			अगर (!is_func_exist(funcs, fn_name, *nr_funcs, &fid))
				*nr_funcs = *nr_funcs + 1;
			अवरोध;

		हाल OP_ADD_FUNCS:
			अगर (!is_func_exist(funcs, fn_name, *nr_funcs, &fid))
				funcs[i].name = fn_name;
			अवरोध;

		हाल OP_COUNT_NR_FUNC_GRPS:
			अगर (is_func_exist(funcs, fn_name, *nr_funcs, &fid))
				funcs[fid].nr_groups++;
			अवरोध;

		हाल OP_ADD_FUNC_GRPS:
			अगर (is_func_exist(funcs, fn_name, *nr_funcs, &fid)) अणु
				क्रम (j = 0; j < funcs[fid].nr_groups; j++)
					अगर (!funcs[fid].groups[j])
						अवरोध;
				funcs[fid].groups[j] = prop->value;
			पूर्ण
			अवरोध;

		शेष:
			of_node_put(np);
			वापस -EINVAL;
		पूर्ण
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_build_functions(काष्ठा eqbr_pinctrl_drv_data *drvdata)
अणु
	काष्ठा device *dev = drvdata->dev;
	काष्ठा eqbr_pmx_func *funcs = शून्य;
	अचिन्हित पूर्णांक nr_funcs = 0;
	पूर्णांक i, ret;

	ret = funcs_utils(dev, funcs, &nr_funcs, OP_COUNT_NR_FUNCS);
	अगर (ret)
		वापस ret;

	funcs = devm_kसुस्मृति(dev, nr_funcs, माप(*funcs), GFP_KERNEL);
	अगर (!funcs)
		वापस -ENOMEM;

	ret = funcs_utils(dev, funcs, &nr_funcs, OP_ADD_FUNCS);
	अगर (ret)
		वापस ret;

	ret = funcs_utils(dev, funcs, &nr_funcs, OP_COUNT_NR_FUNC_GRPS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_funcs; i++) अणु
		अगर (!funcs[i].nr_groups)
			जारी;
		funcs[i].groups = devm_kसुस्मृति(dev, funcs[i].nr_groups,
					       माप(*(funcs[i].groups)),
					       GFP_KERNEL);
		अगर (!funcs[i].groups)
			वापस -ENOMEM;
	पूर्ण

	ret = funcs_utils(dev, funcs, &nr_funcs, OP_ADD_FUNC_GRPS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_funcs; i++) अणु
		ret = pinmux_generic_add_function(drvdata->pctl_dev,
						  funcs[i].name,
						  funcs[i].groups,
						  funcs[i].nr_groups,
						  drvdata);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register function %s\n",
				funcs[i].name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_build_groups(काष्ठा eqbr_pinctrl_drv_data *drvdata)
अणु
	काष्ठा device *dev = drvdata->dev;
	काष्ठा device_node *node = dev->of_node;
	अचिन्हित पूर्णांक *pinmux, pin_id, pinmux_id;
	काष्ठा group_desc group;
	काष्ठा device_node *np;
	काष्ठा property *prop;
	पूर्णांक j, err;

	क्रम_each_child_of_node(node, np) अणु
		prop = of_find_property(np, "groups", शून्य);
		अगर (!prop)
			जारी;

		group.num_pins = of_property_count_u32_elems(np, "pins");
		अगर (group.num_pins < 0) अणु
			dev_err(dev, "No pins in the group: %s\n", prop->name);
			of_node_put(np);
			वापस -EINVAL;
		पूर्ण
		group.name = prop->value;
		group.pins = devm_kसुस्मृति(dev, group.num_pins,
					  माप(*(group.pins)), GFP_KERNEL);
		अगर (!group.pins) अणु
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण

		pinmux = devm_kसुस्मृति(dev, group.num_pins, माप(*pinmux),
				      GFP_KERNEL);
		अगर (!pinmux) अणु
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण

		क्रम (j = 0; j < group.num_pins; j++) अणु
			अगर (of_property_पढ़ो_u32_index(np, "pins", j, &pin_id)) अणु
				dev_err(dev, "Group %s: Read intel pins id failed\n",
					group.name);
				of_node_put(np);
				वापस -EINVAL;
			पूर्ण
			अगर (pin_id >= drvdata->pctl_desc.npins) अणु
				dev_err(dev, "Group %s: Invalid pin ID, idx: %d, pin %u\n",
					group.name, j, pin_id);
				of_node_put(np);
				वापस -EINVAL;
			पूर्ण
			group.pins[j] = pin_id;
			अगर (of_property_पढ़ो_u32_index(np, "pinmux", j, &pinmux_id)) अणु
				dev_err(dev, "Group %s: Read intel pinmux id failed\n",
					group.name);
				of_node_put(np);
				वापस -EINVAL;
			पूर्ण
			pinmux[j] = pinmux_id;
		पूर्ण

		err = pinctrl_generic_add_group(drvdata->pctl_dev, group.name,
						group.pins, group.num_pins,
						pinmux);
		अगर (err < 0) अणु
			dev_err(dev, "Failed to register group %s\n", group.name);
			of_node_put(np);
			वापस err;
		पूर्ण
		स_रखो(&group, 0, माप(group));
		pinmux = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pinctrl_reg(काष्ठा eqbr_pinctrl_drv_data *drvdata)
अणु
	काष्ठा pinctrl_desc *pctl_desc;
	काष्ठा pinctrl_pin_desc *pdesc;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक nr_pins;
	अक्षर *pin_names;
	पूर्णांक i, ret;

	dev = drvdata->dev;
	pctl_desc = &drvdata->pctl_desc;
	pctl_desc->name = "eqbr-pinctrl";
	pctl_desc->owner = THIS_MODULE;
	pctl_desc->pctlops = &eqbr_pctl_ops;
	pctl_desc->pmxops = &eqbr_pinmux_ops;
	pctl_desc->confops = &eqbr_pinconf_ops;
	raw_spin_lock_init(&drvdata->lock);

	क्रम (i = 0, nr_pins = 0; i < drvdata->nr_banks; i++)
		nr_pins += drvdata->pin_banks[i].nr_pins;

	pdesc = devm_kसुस्मृति(dev, nr_pins, माप(*pdesc), GFP_KERNEL);
	अगर (!pdesc)
		वापस -ENOMEM;
	pin_names = devm_kसुस्मृति(dev, nr_pins, PIN_NAME_LEN, GFP_KERNEL);
	अगर (!pin_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_pins; i++) अणु
		प्र_लिखो(pin_names, PIN_NAME_FMT, i);
		pdesc[i].number = i;
		pdesc[i].name = pin_names;
		pin_names += PIN_NAME_LEN;
	पूर्ण
	pctl_desc->pins = pdesc;
	pctl_desc->npins = nr_pins;
	dev_dbg(dev, "pinctrl total pin number: %u\n", nr_pins);

	ret = devm_pinctrl_रेजिस्टर_and_init(dev, pctl_desc, drvdata,
					     &drvdata->pctl_dev);
	अगर (ret)
		वापस ret;

	ret = eqbr_build_groups(drvdata);
	अगर (ret) अणु
		dev_err(dev, "Failed to build groups\n");
		वापस ret;
	पूर्ण

	ret = eqbr_build_functions(drvdata);
	अगर (ret) अणु
		dev_err(dev, "Failed to build groups\n");
		वापस ret;
	पूर्ण

	वापस pinctrl_enable(drvdata->pctl_dev);
पूर्ण

अटल पूर्णांक pinbank_init(काष्ठा device_node *np,
			काष्ठा eqbr_pinctrl_drv_data *drvdata,
			काष्ठा eqbr_pin_bank *bank, अचिन्हित पूर्णांक id)
अणु
	काष्ठा device *dev = drvdata->dev;
	काष्ठा of_phandle_args spec;
	पूर्णांक ret;

	bank->membase = drvdata->membase + id * PAD_REG_OFF;

	ret = of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3, 0, &spec);
	अगर (ret) अणु
		dev_err(dev, "gpio-range not available!\n");
		वापस ret;
	पूर्ण

	bank->pin_base = spec.args[1];
	bank->nr_pins = spec.args[2];

	bank->aval_pinmap = पढ़ोl(bank->membase + REG_AVAIL);
	bank->id = id;

	dev_dbg(dev, "pinbank id: %d, reg: %px, pinbase: %u, pin number: %u, pinmap: 0x%x\n",
		id, bank->membase, bank->pin_base,
		bank->nr_pins, bank->aval_pinmap);

	वापस ret;
पूर्ण

अटल पूर्णांक pinbank_probe(काष्ठा eqbr_pinctrl_drv_data *drvdata)
अणु
	काष्ठा device *dev = drvdata->dev;
	काष्ठा device_node *np_gpio;
	काष्ठा eqbr_gpio_ctrl *gctrls;
	काष्ठा eqbr_pin_bank *banks;
	पूर्णांक i, nr_gpio;

	/* Count gpio bank number */
	nr_gpio = 0;
	क्रम_each_node_by_name(np_gpio, "gpio") अणु
		अगर (of_device_is_available(np_gpio))
			nr_gpio++;
	पूर्ण

	अगर (!nr_gpio) अणु
		dev_err(dev, "NO pin bank available!\n");
		वापस -ENODEV;
	पूर्ण

	/* Count pin bank number and gpio controller number */
	banks = devm_kसुस्मृति(dev, nr_gpio, माप(*banks), GFP_KERNEL);
	अगर (!banks)
		वापस -ENOMEM;

	gctrls = devm_kसुस्मृति(dev, nr_gpio, माप(*gctrls), GFP_KERNEL);
	अगर (!gctrls)
		वापस -ENOMEM;

	dev_dbg(dev, "found %d gpio controller!\n", nr_gpio);

	/* Initialize Pin bank */
	i = 0;
	क्रम_each_node_by_name(np_gpio, "gpio") अणु
		अगर (!of_device_is_available(np_gpio))
			जारी;

		pinbank_init(np_gpio, drvdata, banks + i, i);

		gctrls[i].node = np_gpio;
		gctrls[i].bank = banks + i;
		i++;
	पूर्ण

	drvdata->pin_banks = banks;
	drvdata->nr_banks = nr_gpio;
	drvdata->gpio_ctrls = gctrls;
	drvdata->nr_gpio_ctrls = nr_gpio;

	वापस 0;
पूर्ण

अटल पूर्णांक eqbr_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा eqbr_pinctrl_drv_data *drvdata;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->dev = dev;

	drvdata->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(drvdata->membase))
		वापस PTR_ERR(drvdata->membase);

	ret = pinbank_probe(drvdata);
	अगर (ret)
		वापस ret;

	ret = pinctrl_reg(drvdata);
	अगर (ret)
		वापस ret;

	ret = gpiolib_reg(drvdata);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, drvdata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id eqbr_pinctrl_dt_match[] = अणु
	अणु .compatible = "intel,lgm-io" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver eqbr_pinctrl_driver = अणु
	.probe	= eqbr_pinctrl_probe,
	.driver = अणु
		.name = "eqbr-pinctrl",
		.of_match_table = eqbr_pinctrl_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(eqbr_pinctrl_driver);

MODULE_AUTHOR("Zhu Yixin <yixin.zhu@intel.com>, Rahul Tanwar <rahul.tanwar@intel.com>");
MODULE_DESCRIPTION("Pinctrl Driver for LGM SoC (Equilibrium)");
MODULE_LICENSE("GPL v2");
