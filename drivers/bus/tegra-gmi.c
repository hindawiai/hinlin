<शैली गुरु>
/*
 * Driver क्रम NVIDIA Generic Memory Interface
 *
 * Copyright (C) 2016 Host Mobility AB. All rights reserved.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>

#घोषणा TEGRA_GMI_CONFIG		0x00
#घोषणा TEGRA_GMI_CONFIG_GO		BIT(31)
#घोषणा TEGRA_GMI_BUS_WIDTH_32BIT	BIT(30)
#घोषणा TEGRA_GMI_MUX_MODE		BIT(28)
#घोषणा TEGRA_GMI_RDY_BEFORE_DATA	BIT(24)
#घोषणा TEGRA_GMI_RDY_ACTIVE_HIGH	BIT(23)
#घोषणा TEGRA_GMI_ADV_ACTIVE_HIGH	BIT(22)
#घोषणा TEGRA_GMI_OE_ACTIVE_HIGH	BIT(21)
#घोषणा TEGRA_GMI_CS_ACTIVE_HIGH	BIT(20)
#घोषणा TEGRA_GMI_CS_SELECT(x)		((x & 0x7) << 4)

#घोषणा TEGRA_GMI_TIMING0		0x10
#घोषणा TEGRA_GMI_MUXED_WIDTH(x)	((x & 0xf) << 12)
#घोषणा TEGRA_GMI_HOLD_WIDTH(x)		((x & 0xf) << 8)
#घोषणा TEGRA_GMI_ADV_WIDTH(x)		((x & 0xf) << 4)
#घोषणा TEGRA_GMI_CE_WIDTH(x)		(x & 0xf)

#घोषणा TEGRA_GMI_TIMING1		0x14
#घोषणा TEGRA_GMI_WE_WIDTH(x)		((x & 0xff) << 16)
#घोषणा TEGRA_GMI_OE_WIDTH(x)		((x & 0xff) << 8)
#घोषणा TEGRA_GMI_WAIT_WIDTH(x)		(x & 0xff)

#घोषणा TEGRA_GMI_MAX_CHIP_SELECT	8

काष्ठा tegra_gmi अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;

	u32 snor_config;
	u32 snor_timing0;
	u32 snor_timing1;
पूर्ण;

अटल पूर्णांक tegra_gmi_enable(काष्ठा tegra_gmi *gmi)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(gmi->clk);
	अगर (err < 0) अणु
		dev_err(gmi->dev, "failed to enable clock: %d\n", err);
		वापस err;
	पूर्ण

	reset_control_निश्चित(gmi->rst);
	usleep_range(2000, 4000);
	reset_control_deनिश्चित(gmi->rst);

	ग_लिखोl(gmi->snor_timing0, gmi->base + TEGRA_GMI_TIMING0);
	ग_लिखोl(gmi->snor_timing1, gmi->base + TEGRA_GMI_TIMING1);

	gmi->snor_config |= TEGRA_GMI_CONFIG_GO;
	ग_लिखोl(gmi->snor_config, gmi->base + TEGRA_GMI_CONFIG);

	वापस 0;
पूर्ण

अटल व्योम tegra_gmi_disable(काष्ठा tegra_gmi *gmi)
अणु
	u32 config;

	/* stop GMI operation */
	config = पढ़ोl(gmi->base + TEGRA_GMI_CONFIG);
	config &= ~TEGRA_GMI_CONFIG_GO;
	ग_लिखोl(config, gmi->base + TEGRA_GMI_CONFIG);

	reset_control_निश्चित(gmi->rst);
	clk_disable_unprepare(gmi->clk);
पूर्ण

अटल पूर्णांक tegra_gmi_parse_dt(काष्ठा tegra_gmi *gmi)
अणु
	काष्ठा device_node *child;
	u32 property, ranges[4];
	पूर्णांक err;

	child = of_get_next_available_child(gmi->dev->of_node, शून्य);
	अगर (!child) अणु
		dev_err(gmi->dev, "no child nodes found\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * We currently only support one child device due to lack of
	 * chip-select address decoding. Which means that we only have one
	 * chip-select line from the GMI controller.
	 */
	अगर (of_get_child_count(gmi->dev->of_node) > 1)
		dev_warn(gmi->dev, "only one child device is supported.");

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-data-width-32bit"))
		gmi->snor_config |= TEGRA_GMI_BUS_WIDTH_32BIT;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-mux-mode"))
		gmi->snor_config |= TEGRA_GMI_MUX_MODE;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-rdy-active-before-data"))
		gmi->snor_config |= TEGRA_GMI_RDY_BEFORE_DATA;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-rdy-active-high"))
		gmi->snor_config |= TEGRA_GMI_RDY_ACTIVE_HIGH;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-adv-active-high"))
		gmi->snor_config |= TEGRA_GMI_ADV_ACTIVE_HIGH;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-oe-active-high"))
		gmi->snor_config |= TEGRA_GMI_OE_ACTIVE_HIGH;

	अगर (of_property_पढ़ो_bool(child, "nvidia,snor-cs-active-high"))
		gmi->snor_config |= TEGRA_GMI_CS_ACTIVE_HIGH;

	/* Decode the CS# */
	err = of_property_पढ़ो_u32_array(child, "ranges", ranges, 4);
	अगर (err < 0) अणु
		/* Invalid binding */
		अगर (err == -EOVERFLOW) अणु
			dev_err(gmi->dev,
				"failed to decode CS: invalid ranges length\n");
			जाओ error_cs;
		पूर्ण

		/*
		 * If we reach here it means that the child node has an empty
		 * ranges or it करोes not exist at all. Attempt to decode the
		 * CS# from the reg property instead.
		 */
		err = of_property_पढ़ो_u32(child, "reg", &property);
		अगर (err < 0) अणु
			dev_err(gmi->dev,
				"failed to decode CS: no reg property found\n");
			जाओ error_cs;
		पूर्ण
	पूर्ण अन्यथा अणु
		property = ranges[1];
	पूर्ण

	/* Valid chip selects are CS0-CS7 */
	अगर (property >= TEGRA_GMI_MAX_CHIP_SELECT) अणु
		dev_err(gmi->dev, "invalid chip select: %d", property);
		err = -EINVAL;
		जाओ error_cs;
	पूर्ण

	gmi->snor_config |= TEGRA_GMI_CS_SELECT(property);

	/* The शेष values that are provided below are reset values */
	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-muxed-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_MUXED_WIDTH(property);
	अन्यथा
		gmi->snor_timing0 |= TEGRA_GMI_MUXED_WIDTH(1);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-hold-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_HOLD_WIDTH(property);
	अन्यथा
		gmi->snor_timing0 |= TEGRA_GMI_HOLD_WIDTH(1);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-adv-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_ADV_WIDTH(property);
	अन्यथा
		gmi->snor_timing0 |= TEGRA_GMI_ADV_WIDTH(1);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-ce-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_CE_WIDTH(property);
	अन्यथा
		gmi->snor_timing0 |= TEGRA_GMI_CE_WIDTH(4);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-we-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_WE_WIDTH(property);
	अन्यथा
		gmi->snor_timing1 |= TEGRA_GMI_WE_WIDTH(1);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-oe-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_OE_WIDTH(property);
	अन्यथा
		gmi->snor_timing1 |= TEGRA_GMI_OE_WIDTH(1);

	अगर (!of_property_पढ़ो_u32(child, "nvidia,snor-wait-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_WAIT_WIDTH(property);
	अन्यथा
		gmi->snor_timing1 |= TEGRA_GMI_WAIT_WIDTH(3);

error_cs:
	of_node_put(child);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_gmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra_gmi *gmi;
	काष्ठा resource *res;
	पूर्णांक err;

	gmi = devm_kzalloc(dev, माप(*gmi), GFP_KERNEL);
	अगर (!gmi)
		वापस -ENOMEM;

	gmi->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gmi->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(gmi->base))
		वापस PTR_ERR(gmi->base);

	gmi->clk = devm_clk_get(dev, "gmi");
	अगर (IS_ERR(gmi->clk)) अणु
		dev_err(dev, "can not get clock\n");
		वापस PTR_ERR(gmi->clk);
	पूर्ण

	gmi->rst = devm_reset_control_get(dev, "gmi");
	अगर (IS_ERR(gmi->rst)) अणु
		dev_err(dev, "can not get reset\n");
		वापस PTR_ERR(gmi->rst);
	पूर्ण

	err = tegra_gmi_parse_dt(gmi);
	अगर (err)
		वापस err;

	err = tegra_gmi_enable(gmi);
	अगर (err < 0)
		वापस err;

	err = of_platक्रमm_शेष_populate(dev->of_node, शून्य, dev);
	अगर (err < 0) अणु
		dev_err(dev, "fail to create devices.\n");
		tegra_gmi_disable(gmi);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gmi);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_gmi *gmi = platक्रमm_get_drvdata(pdev);

	of_platक्रमm_depopulate(gmi->dev);
	tegra_gmi_disable(gmi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_gmi_id_table[] = अणु
	अणु .compatible = "nvidia,tegra20-gmi", पूर्ण,
	अणु .compatible = "nvidia,tegra30-gmi", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_gmi_id_table);

अटल काष्ठा platक्रमm_driver tegra_gmi_driver = अणु
	.probe = tegra_gmi_probe,
	.हटाओ = tegra_gmi_हटाओ,
	.driver = अणु
		.name		= "tegra-gmi",
		.of_match_table	= tegra_gmi_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_gmi_driver);

MODULE_AUTHOR("Mirza Krak <mirza.krak@gmail.com");
MODULE_DESCRIPTION("NVIDIA Tegra GMI Bus Driver");
MODULE_LICENSE("GPL v2");
