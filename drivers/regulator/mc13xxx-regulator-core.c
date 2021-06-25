<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Regulator Driver क्रम Freescale MC13xxx PMIC
//
// Copyright 2010 Yong Shen <yong.shen@linaro.org>
//
// Based on mc13783 regulator driver :
// Copyright (C) 2008 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
// Copyright 2009 Alberto Panizzo <maramaopercheseimorto@gmail.com>
//
// Regs infos taken from mc13xxx drivers from मुक्तscale and mc13xxx.pdf file
// from मुक्तscale

#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश "mc13xxx.h"

अटल पूर्णांक mc13xxx_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक id = rdev_get_id(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	वापस mc13xxx_reg_rmw(priv->mc13xxx, mc13xxx_regulators[id].reg,
			       mc13xxx_regulators[id].enable_bit,
			       mc13xxx_regulators[id].enable_bit);
पूर्ण

अटल पूर्णांक mc13xxx_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक id = rdev_get_id(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	वापस mc13xxx_reg_rmw(priv->mc13xxx, mc13xxx_regulators[id].reg,
			       mc13xxx_regulators[id].enable_bit, 0);
पूर्ण

अटल पूर्णांक mc13xxx_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, mc13xxx_regulators[id].reg, &val);
	अगर (ret)
		वापस ret;

	वापस (val & mc13xxx_regulators[id].enable_bit) != 0;
पूर्ण

अटल पूर्णांक mc13xxx_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					     अचिन्हित selector)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक id = rdev_get_id(rdev);

	वापस mc13xxx_reg_rmw(priv->mc13xxx, mc13xxx_regulators[id].vsel_reg,
			       mc13xxx_regulators[id].vsel_mask,
			       selector << mc13xxx_regulators[id].vsel_shअगरt);
पूर्ण

अटल पूर्णांक mc13xxx_regulator_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	पूर्णांक ret, id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx,
				mc13xxx_regulators[id].vsel_reg, &val);
	अगर (ret)
		वापस ret;

	val = (val & mc13xxx_regulators[id].vsel_mask)
		>> mc13xxx_regulators[id].vsel_shअगरt;

	dev_dbg(rdev_get_dev(rdev), "%s id: %d val: %d\n", __func__, id, val);

	BUG_ON(val >= mc13xxx_regulators[id].desc.n_voltages);

	वापस rdev->desc->volt_table[val];
पूर्ण

स्थिर काष्ठा regulator_ops mc13xxx_regulator_ops = अणु
	.enable = mc13xxx_regulator_enable,
	.disable = mc13xxx_regulator_disable,
	.is_enabled = mc13xxx_regulator_is_enabled,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = mc13xxx_regulator_set_voltage_sel,
	.get_voltage = mc13xxx_regulator_get_voltage,
पूर्ण;
EXPORT_SYMBOL_GPL(mc13xxx_regulator_ops);

पूर्णांक mc13xxx_fixed_regulator_set_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
	       पूर्णांक max_uV, अचिन्हित *selector)
अणु
	पूर्णांक id = rdev_get_id(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s id: %d min_uV: %d max_uV: %d\n",
		__func__, id, min_uV, max_uV);

	अगर (min_uV <= rdev->desc->volt_table[0] &&
	    rdev->desc->volt_table[0] <= max_uV) अणु
		*selector = 0;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_fixed_regulator_set_voltage);

स्थिर काष्ठा regulator_ops mc13xxx_fixed_regulator_ops = अणु
	.enable = mc13xxx_regulator_enable,
	.disable = mc13xxx_regulator_disable,
	.is_enabled = mc13xxx_regulator_is_enabled,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage = mc13xxx_fixed_regulator_set_voltage,
पूर्ण;
EXPORT_SYMBOL_GPL(mc13xxx_fixed_regulator_ops);

#अगर_घोषित CONFIG_OF
पूर्णांक mc13xxx_get_num_regulators_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *parent;
	पूर्णांक num;

	अगर (!pdev->dev.parent->of_node)
		वापस -ENODEV;

	parent = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	अगर (!parent)
		वापस -ENODEV;

	num = of_get_child_count(parent);
	of_node_put(parent);
	वापस num;
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_get_num_regulators_dt);

काष्ठा mc13xxx_regulator_init_data *mc13xxx_parse_regulators_dt(
	काष्ठा platक्रमm_device *pdev, काष्ठा mc13xxx_regulator *regulators,
	पूर्णांक num_regulators)
अणु
	काष्ठा mc13xxx_regulator_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा mc13xxx_regulator_init_data *data, *p;
	काष्ठा device_node *parent, *child;
	पूर्णांक i, parsed = 0;

	अगर (!pdev->dev.parent->of_node)
		वापस शून्य;

	parent = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	अगर (!parent)
		वापस शून्य;

	data = devm_kसुस्मृति(&pdev->dev, priv->num_regulators, माप(*data),
			    GFP_KERNEL);
	अगर (!data) अणु
		of_node_put(parent);
		वापस शून्य;
	पूर्ण

	p = data;

	क्रम_each_child_of_node(parent, child) अणु
		पूर्णांक found = 0;

		क्रम (i = 0; i < num_regulators; i++) अणु
			अगर (!regulators[i].desc.name)
				जारी;
			अगर (of_node_name_eq(child,
					 regulators[i].desc.name)) अणु
				p->id = i;
				p->init_data = of_get_regulator_init_data(
							&pdev->dev, child,
							&regulators[i].desc);
				p->node = child;
				p++;

				parsed++;
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			dev_warn(&pdev->dev,
				 "Unknown regulator: %pOFn\n", child);
	पूर्ण
	of_node_put(parent);

	priv->num_regulators = parsed;

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_parse_regulators_dt);
#पूर्ण_अगर

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yong Shen <yong.shen@linaro.org>");
MODULE_DESCRIPTION("Regulator Driver for Freescale MC13xxx PMIC");
MODULE_ALIAS("mc13xxx-regulator-core");
