<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock driver क्रम the ARM Integrator/IM-PD1 board
 * Copyright (C) 2012-2013 Linus Walleij
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "icst.h"
#समावेश "clk-icst.h"

#घोषणा IMPD1_OSC1	0x00
#घोषणा IMPD1_OSC2	0x04
#घोषणा IMPD1_LOCK	0x08

/*
 * There are two VCO's on the IM-PD1
 */

अटल स्थिर काष्ठा icst_params impd1_vco1_params = अणु
	.ref		= 24000000,	/* 24 MHz */
	.vco_max	= ICST525_VCO_MAX_3V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 12,
	.vd_max		= 519,
	.rd_min		= 3,
	.rd_max		= 120,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा clk_icst_desc impd1_icst1_desc = अणु
	.params = &impd1_vco1_params,
	.vco_offset = IMPD1_OSC1,
	.lock_offset = IMPD1_LOCK,
पूर्ण;

अटल स्थिर काष्ठा icst_params impd1_vco2_params = अणु
	.ref		= 24000000,	/* 24 MHz */
	.vco_max	= ICST525_VCO_MAX_3V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 12,
	.vd_max		= 519,
	.rd_min		= 3,
	.rd_max		= 120,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा clk_icst_desc impd1_icst2_desc = अणु
	.params = &impd1_vco2_params,
	.vco_offset = IMPD1_OSC2,
	.lock_offset = IMPD1_LOCK,
पूर्ण;

अटल पूर्णांक पूर्णांकegrator_impd1_clk_spawn(काष्ठा device *dev,
				      काष्ठा device_node *parent,
				      काष्ठा device_node *np)
अणु
	काष्ठा regmap *map;
	काष्ठा clk *clk = ERR_PTR(-EINVAL);
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	स्थिर काष्ठा clk_icst_desc *desc;
	पूर्णांक ret;

	map = syscon_node_to_regmap(parent);
	अगर (IS_ERR(map)) अणु
		pr_err("no regmap for syscon IM-PD1 ICST clock parent\n");
		वापस PTR_ERR(map);
	पूर्ण

	अगर (of_device_is_compatible(np, "arm,impd1-vco1")) अणु
		desc = &impd1_icst1_desc;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,impd1-vco2")) अणु
		desc = &impd1_icst2_desc;
	पूर्ण अन्यथा अणु
		dev_err(dev, "not a clock node %s\n", name);
		वापस -ENODEV;
	पूर्ण

	of_property_पढ़ो_string(np, "clock-output-names", &name);
	parent_name = of_clk_get_parent_name(np, 0);
	clk = icst_clk_setup(शून्य, desc, name, parent_name, map,
			     ICST_INTEGRATOR_IM_PD1);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(np, of_clk_src_simple_get, clk);
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_err(dev, "error setting up IM-PD1 ICST clock\n");
		ret = PTR_ERR(clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकegrator_impd1_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक ret = 0;

	क्रम_each_available_child_of_node(np, child) अणु
		ret = पूर्णांकegrator_impd1_clk_spawn(dev, np, child);
		अगर (ret) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id impd1_syscon_match[] = अणु
	अणु .compatible = "arm,im-pd1-syscon", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, impd1_syscon_match);

अटल काष्ठा platक्रमm_driver impd1_clk_driver = अणु
	.driver = अणु
		.name = "impd1-clk",
		.of_match_table = impd1_syscon_match,
	पूर्ण,
	.probe  = पूर्णांकegrator_impd1_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(impd1_clk_driver);

MODULE_AUTHOR("Linus Walleij <linusw@kernel.org>");
MODULE_DESCRIPTION("Arm IM-PD1 module clock driver");
MODULE_LICENSE("GPL v2");
