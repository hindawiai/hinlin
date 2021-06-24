<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * Allwinner PRCM (Power/Reset/Clock Management) driver
 */

#समावेश <linux/mfd/core.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>

#घोषणा SUN8I_CODEC_ANALOG_BASE	0x1c0
#घोषणा SUN8I_CODEC_ANALOG_SIZE	0x4

काष्ठा prcm_data अणु
	पूर्णांक nsubdevs;
	स्थिर काष्ठा mfd_cell *subdevs;
पूर्ण;

अटल स्थिर काष्ठा resource sun6i_a31_ar100_clk_res[] = अणु
	अणु
		.start = 0x0,
		.end = 0x3,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sun6i_a31_apb0_clk_res[] = अणु
	अणु
		.start = 0xc,
		.end = 0xf,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sun6i_a31_apb0_gates_clk_res[] = अणु
	अणु
		.start = 0x28,
		.end = 0x2b,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sun6i_a31_ir_clk_res[] = अणु
	अणु
		.start = 0x54,
		.end = 0x57,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sun6i_a31_apb0_rstc_res[] = अणु
	अणु
		.start = 0xb0,
		.end = 0xb3,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sun8i_codec_analog_res[] = अणु
	DEFINE_RES_MEM(SUN8I_CODEC_ANALOG_BASE, SUN8I_CODEC_ANALOG_SIZE),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sun6i_a31_prcm_subdevs[] = अणु
	अणु
		.name = "sun6i-a31-ar100-clk",
		.of_compatible = "allwinner,sun6i-a31-ar100-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_ar100_clk_res),
		.resources = sun6i_a31_ar100_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-apb0-clk",
		.of_compatible = "allwinner,sun6i-a31-apb0-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_clk_res),
		.resources = sun6i_a31_apb0_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-apb0-gates-clk",
		.of_compatible = "allwinner,sun6i-a31-apb0-gates-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_gates_clk_res),
		.resources = sun6i_a31_apb0_gates_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-ir-clk",
		.of_compatible = "allwinner,sun4i-a10-mod0-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_ir_clk_res),
		.resources = sun6i_a31_ir_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-apb0-clock-reset",
		.of_compatible = "allwinner,sun6i-a31-clock-reset",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_rstc_res),
		.resources = sun6i_a31_apb0_rstc_res,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sun8i_a23_prcm_subdevs[] = अणु
	अणु
		.name = "sun8i-a23-apb0-clk",
		.of_compatible = "allwinner,sun8i-a23-apb0-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_clk_res),
		.resources = sun6i_a31_apb0_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-apb0-gates-clk",
		.of_compatible = "allwinner,sun8i-a23-apb0-gates-clk",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_gates_clk_res),
		.resources = sun6i_a31_apb0_gates_clk_res,
	पूर्ण,
	अणु
		.name = "sun6i-a31-apb0-clock-reset",
		.of_compatible = "allwinner,sun6i-a31-clock-reset",
		.num_resources = ARRAY_SIZE(sun6i_a31_apb0_rstc_res),
		.resources = sun6i_a31_apb0_rstc_res,
	पूर्ण,
	अणु
		.name		= "sun8i-codec-analog",
		.of_compatible	= "allwinner,sun8i-a23-codec-analog",
		.num_resources	= ARRAY_SIZE(sun8i_codec_analog_res),
		.resources	= sun8i_codec_analog_res,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा prcm_data sun6i_a31_prcm_data = अणु
	.nsubdevs = ARRAY_SIZE(sun6i_a31_prcm_subdevs),
	.subdevs = sun6i_a31_prcm_subdevs,
पूर्ण;

अटल स्थिर काष्ठा prcm_data sun8i_a23_prcm_data = अणु
	.nsubdevs = ARRAY_SIZE(sun8i_a23_prcm_subdevs),
	.subdevs = sun8i_a23_prcm_subdevs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun6i_prcm_dt_ids[] = अणु
	अणु
		.compatible = "allwinner,sun6i-a31-prcm",
		.data = &sun6i_a31_prcm_data,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-prcm",
		.data = &sun8i_a23_prcm_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक sun6i_prcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा prcm_data *data;
	काष्ठा resource *res;
	पूर्णांक ret;

	match = of_match_node(sun6i_prcm_dt_ids, pdev->dev.of_node);
	अगर (!match)
		वापस -EINVAL;

	data = match->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no prcm memory region provided\n");
		वापस -ENOENT;
	पूर्ण

	ret = mfd_add_devices(&pdev->dev, 0, data->subdevs, data->nsubdevs,
			      res, -1, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add subdevices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun6i_prcm_driver = अणु
	.driver = अणु
		.name = "sun6i-prcm",
		.of_match_table = sun6i_prcm_dt_ids,
	पूर्ण,
	.probe = sun6i_prcm_probe,
पूर्ण;
builtin_platक्रमm_driver(sun6i_prcm_driver);
