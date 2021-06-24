<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM63xx GPIO unit (pinctrl + GPIO)
 *
 * Copyright (C) 2021 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright (C) 2016 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/gpio/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pinctrl-bcm63xx.h"

#घोषणा BCM63XX_BANK_SIZE	4

#घोषणा BCM63XX_सूचीOUT_REG	0x04
#घोषणा BCM63XX_DATA_REG	0x0c

अटल पूर्णांक bcm63xx_reg_mask_xlate(काष्ठा gpio_regmap *gpio,
				  अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *mask)
अणु
	अचिन्हित पूर्णांक line = offset % BCM63XX_BANK_GPIOS;
	अचिन्हित पूर्णांक stride = offset / BCM63XX_BANK_GPIOS;

	*reg = base - stride * BCM63XX_BANK_SIZE;
	*mask = BIT(line);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63xx_gpio_of_match[] = अणु
	अणु .compatible = "brcm,bcm6318-gpio", पूर्ण,
	अणु .compatible = "brcm,bcm6328-gpio", पूर्ण,
	अणु .compatible = "brcm,bcm6358-gpio", पूर्ण,
	अणु .compatible = "brcm,bcm6362-gpio", पूर्ण,
	अणु .compatible = "brcm,bcm6368-gpio", पूर्ण,
	अणु .compatible = "brcm,bcm63268-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक bcm63xx_gpio_probe(काष्ठा device *dev, काष्ठा device_node *node,
			      स्थिर काष्ठा bcm63xx_pinctrl_soc *soc,
			      काष्ठा bcm63xx_pinctrl *pc)
अणु
	काष्ठा gpio_regmap_config grc = अणु0पूर्ण;

	grc.parent = dev;
	grc.fwnode = &node->fwnode;
	grc.ngpio = soc->ngpios;
	grc.ngpio_per_reg = BCM63XX_BANK_GPIOS;
	grc.regmap = pc->regs;
	grc.reg_dat_base = BCM63XX_DATA_REG;
	grc.reg_dir_out_base = BCM63XX_सूचीOUT_REG;
	grc.reg_set_base = BCM63XX_DATA_REG;
	grc.reg_mask_xlate = bcm63xx_reg_mask_xlate;

	वापस PTR_ERR_OR_ZERO(devm_gpio_regmap_रेजिस्टर(dev, &grc));
पूर्ण

पूर्णांक bcm63xx_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा bcm63xx_pinctrl_soc *soc,
			  व्योम *driver_data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63xx_pinctrl *pc;
	काष्ठा device_node *node;
	पूर्णांक err;

	pc = devm_kzalloc(dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pc);

	pc->dev = dev;
	pc->driver_data = driver_data;

	pc->regs = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(pc->regs))
		वापस PTR_ERR(pc->regs);

	pc->pctl_desc.name = dev_name(dev);
	pc->pctl_desc.pins = soc->pins;
	pc->pctl_desc.npins = soc->npins;
	pc->pctl_desc.pctlops = soc->pctl_ops;
	pc->pctl_desc.pmxops = soc->pmx_ops;
	pc->pctl_desc.owner = THIS_MODULE;

	pc->pctl_dev = devm_pinctrl_रेजिस्टर(dev, &pc->pctl_desc, pc);
	अगर (IS_ERR(pc->pctl_dev))
		वापस PTR_ERR(pc->pctl_dev);

	क्रम_each_child_of_node(dev->parent->of_node, node) अणु
		अगर (of_match_node(bcm63xx_gpio_of_match, node)) अणु
			err = bcm63xx_gpio_probe(dev, node, soc, pc);
			अगर (err) अणु
				dev_err(dev, "could not add GPIO chip\n");
				of_node_put(node);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
