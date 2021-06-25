<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <dt-bindings/soc/qcom,gsbi.h>

#घोषणा GSBI_CTRL_REG		0x0000
#घोषणा GSBI_PROTOCOL_SHIFT	4
#घोषणा MAX_GSBI		12

#घोषणा TCSR_ADM_CRCI_BASE	0x70

काष्ठा crci_config अणु
	u32 num_rows;
	स्थिर u32 (*array)[MAX_GSBI];
पूर्ण;

अटल स्थिर u32 crci_ipq8064[][MAX_GSBI] = अणु
	अणु
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
	अणु
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा crci_config config_ipq8064 = अणु
	.num_rows = ARRAY_SIZE(crci_ipq8064),
	.array = crci_ipq8064,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक crci_apq8064[][MAX_GSBI] = अणु
	अणु
		0x001800, 0x006000, 0x000030, 0x0000c0,
		0x000300, 0x000400, 0x000000, 0x000000,
		0x000000, 0x000000, 0x000000, 0x000000
	पूर्ण,
	अणु
		0x000000, 0x000000, 0x000000, 0x000000,
		0x000000, 0x000020, 0x0000c0, 0x000000,
		0x000000, 0x000000, 0x000000, 0x000000
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा crci_config config_apq8064 = अणु
	.num_rows = ARRAY_SIZE(crci_apq8064),
	.array = crci_apq8064,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक crci_msm8960[][MAX_GSBI] = अणु
	अणु
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000400, 0x000000, 0x000000,
		0x000000, 0x000000, 0x000000, 0x000000
	पूर्ण,
	अणु
		0x000000, 0x000000, 0x000000, 0x000000,
		0x000000, 0x000020, 0x0000c0, 0x000300,
		0x001800, 0x006000, 0x000000, 0x000000
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा crci_config config_msm8960 = अणु
	.num_rows = ARRAY_SIZE(crci_msm8960),
	.array = crci_msm8960,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक crci_msm8660[][MAX_GSBI] = अणु
	अणु	/* ADM 0 - B */
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
	अणु	/* ADM 0 - B */
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
	अणु	/* ADM 1 - A */
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
	अणु	/* ADM 1 - B */
		0x000003, 0x00000c, 0x000030, 0x0000c0,
		0x000300, 0x000c00, 0x003000, 0x00c000,
		0x030000, 0x0c0000, 0x300000, 0xc00000
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा crci_config config_msm8660 = अणु
	.num_rows = ARRAY_SIZE(crci_msm8660),
	.array = crci_msm8660,
पूर्ण;

काष्ठा gsbi_info अणु
	काष्ठा clk *hclk;
	u32 mode;
	u32 crci;
	काष्ठा regmap *tcsr;
पूर्ण;

अटल स्थिर काष्ठा of_device_id tcsr_dt_match[] = अणु
	अणु .compatible = "qcom,tcsr-ipq8064", .data = &config_ipq8064पूर्ण,
	अणु .compatible = "qcom,tcsr-apq8064", .data = &config_apq8064पूर्ण,
	अणु .compatible = "qcom,tcsr-msm8960", .data = &config_msm8960पूर्ण,
	अणु .compatible = "qcom,tcsr-msm8660", .data = &config_msm8660पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक gsbi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *tcsr_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	व्योम __iomem *base;
	काष्ठा gsbi_info *gsbi;
	पूर्णांक i, ret;
	u32 mask, gsbi_num;
	स्थिर काष्ठा crci_config *config = शून्य;

	gsbi = devm_kzalloc(&pdev->dev, माप(*gsbi), GFP_KERNEL);

	अगर (!gsbi)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* get the tcsr node and setup the config and regmap */
	gsbi->tcsr = syscon_regmap_lookup_by_phandle(node, "syscon-tcsr");

	अगर (!IS_ERR(gsbi->tcsr)) अणु
		tcsr_node = of_parse_phandle(node, "syscon-tcsr", 0);
		अगर (tcsr_node) अणु
			match = of_match_node(tcsr_dt_match, tcsr_node);
			अगर (match)
				config = match->data;
			अन्यथा
				dev_warn(&pdev->dev, "no matching TCSR\n");

			of_node_put(tcsr_node);
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "cell-index", &gsbi_num)) अणु
		dev_err(&pdev->dev, "missing cell-index\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gsbi_num < 1 || gsbi_num > MAX_GSBI) अणु
		dev_err(&pdev->dev, "invalid cell-index\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "qcom,mode", &gsbi->mode)) अणु
		dev_err(&pdev->dev, "missing mode configuration\n");
		वापस -EINVAL;
	पूर्ण

	/* not required, so शेष to 0 अगर not present */
	of_property_पढ़ो_u32(node, "qcom,crci", &gsbi->crci);

	dev_info(&pdev->dev, "GSBI port protocol: %d crci: %d\n",
		 gsbi->mode, gsbi->crci);
	gsbi->hclk = devm_clk_get(&pdev->dev, "iface");
	अगर (IS_ERR(gsbi->hclk))
		वापस PTR_ERR(gsbi->hclk);

	clk_prepare_enable(gsbi->hclk);

	ग_लिखोl_relaxed((gsbi->mode << GSBI_PROTOCOL_SHIFT) | gsbi->crci,
				base + GSBI_CTRL_REG);

	/*
	 * modअगरy tcsr to reflect mode and ADM CRCI mux
	 * Each gsbi contains a pair of bits, one क्रम RX and one क्रम TX
	 * SPI mode requires both bits cleared, otherwise they are set
	 */
	अगर (config) अणु
		क्रम (i = 0; i < config->num_rows; i++) अणु
			mask = config->array[i][gsbi_num - 1];

			अगर (gsbi->mode == GSBI_PROT_SPI)
				regmap_update_bits(gsbi->tcsr,
					TCSR_ADM_CRCI_BASE + 4 * i, mask, 0);
			अन्यथा
				regmap_update_bits(gsbi->tcsr,
					TCSR_ADM_CRCI_BASE + 4 * i, mask, mask);

		पूर्ण
	पूर्ण

	/* make sure the gsbi control ग_लिखो is not reordered */
	wmb();

	platक्रमm_set_drvdata(pdev, gsbi);

	ret = of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	अगर (ret)
		clk_disable_unprepare(gsbi->hclk);
	वापस ret;
पूर्ण

अटल पूर्णांक gsbi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gsbi_info *gsbi = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(gsbi->hclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gsbi_dt_match[] = अणु
	अणु .compatible = "qcom,gsbi-v1.0.0", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, gsbi_dt_match);

अटल काष्ठा platक्रमm_driver gsbi_driver = अणु
	.driver = अणु
		.name		= "gsbi",
		.of_match_table	= gsbi_dt_match,
	पूर्ण,
	.probe = gsbi_probe,
	.हटाओ	= gsbi_हटाओ,
पूर्ण;

module_platक्रमm_driver(gsbi_driver);

MODULE_AUTHOR("Andy Gross <agross@codeaurora.org>");
MODULE_DESCRIPTION("QCOM GSBI driver");
MODULE_LICENSE("GPL v2");
