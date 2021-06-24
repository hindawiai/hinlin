<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM Integrator Logical Module bus driver
 * Copyright (C) 2020 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * See the device tree bindings क्रम this block क्रम more details on the
 * hardware.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

/* All inक्रमmation about the connected logic modules are in here */
#घोषणा INTEGRATOR_SC_DEC_OFFSET	0x10

/* Base address क्रम the expansion modules */
#घोषणा INTEGRATOR_AP_EXP_BASE		0xc0000000
#घोषणा INTEGRATOR_AP_EXP_STRIDE	0x10000000

अटल पूर्णांक पूर्णांकegrator_lm_populate(पूर्णांक num, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	u32 base;
	पूर्णांक ret;

	base = INTEGRATOR_AP_EXP_BASE + (num * INTEGRATOR_AP_EXP_STRIDE);

	/* Walk over the child nodes and see what chipselects we use */
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा resource res;

		ret = of_address_to_resource(child, 0, &res);
		अगर (ret) अणु
			dev_info(dev, "no valid address on child\n");
			जारी;
		पूर्ण

		/* First populate the syscon then any devices */
		अगर (res.start == base) अणु
			dev_info(dev, "populate module @0x%08x from DT\n",
				 base);
			ret = of_platक्रमm_शेष_populate(child, शून्य, dev);
			अगर (ret) अणु
				dev_err(dev, "failed to populate module\n");
				of_node_put(child);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकegrator_ap_syscon_match[] = अणु
	अणु .compatible = "arm,integrator-ap-syscon"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकegrator_ap_lm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *syscon;
	अटल काष्ठा regmap *map;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	/* Look up the प्रणाली controller */
	syscon = of_find_matching_node(शून्य, पूर्णांकegrator_ap_syscon_match);
	अगर (!syscon) अणु
		dev_err(dev,
			"could not find Integrator/AP system controller\n");
		वापस -ENODEV;
	पूर्ण
	map = syscon_node_to_regmap(syscon);
	अगर (IS_ERR(map)) अणु
		dev_err(dev,
			"could not find Integrator/AP system controller\n");
		वापस PTR_ERR(map);
	पूर्ण

	ret = regmap_पढ़ो(map, INTEGRATOR_SC_DEC_OFFSET, &val);
	अगर (ret) अणु
		dev_err(dev, "could not read from Integrator/AP syscon\n");
		वापस ret;
	पूर्ण

	/* Loop over the connected modules */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(val & BIT(4 + i)))
			जारी;

		dev_info(dev, "detected module in slot %d\n", i);
		ret = पूर्णांकegrator_lm_populate(i, dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकegrator_ap_lm_match[] = अणु
	अणु .compatible = "arm,integrator-ap-lm"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकegrator_ap_lm_driver = अणु
	.probe = पूर्णांकegrator_ap_lm_probe,
	.driver = अणु
		.name = "integratorap-lm",
		.of_match_table = पूर्णांकegrator_ap_lm_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(पूर्णांकegrator_ap_lm_driver);
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Integrator AP Logical Module driver");
MODULE_LICENSE("GPL v2");
