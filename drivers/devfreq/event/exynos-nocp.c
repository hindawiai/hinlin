<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * exynos-nocp.c - Exynos NoC (Network On Chip) Probe support
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 * Author : Chanwoo Choi <cw00.choi@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/devfreq-event.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "exynos-nocp.h"

काष्ठा exynos_nocp अणु
	काष्ठा devfreq_event_dev *edev;
	काष्ठा devfreq_event_desc desc;

	काष्ठा device *dev;

	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
पूर्ण;

/*
 * The devfreq-event ops काष्ठाure क्रम nocp probe.
 */
अटल पूर्णांक exynos_nocp_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा exynos_nocp *nocp = devfreq_event_get_drvdata(edev);
	पूर्णांक ret;

	/* Disable NoC probe */
	ret = regmap_update_bits(nocp->regmap, NOCP_MAIN_CTL,
				NOCP_MAIN_CTL_STATEN_MASK, 0);
	अगर (ret < 0) अणु
		dev_err(nocp->dev, "failed to disable the NoC probe device\n");
		वापस ret;
	पूर्ण

	/* Set a statistics dump period to 0 */
	ret = regmap_ग_लिखो(nocp->regmap, NOCP_STAT_PERIOD, 0x0);
	अगर (ret < 0)
		जाओ out;

	/* Set the IntEvent fields of *_SRC */
	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_0_SRC,
				NOCP_CNT_SRC_INTEVENT_MASK,
				NOCP_CNT_SRC_INTEVENT_BYTE_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_1_SRC,
				NOCP_CNT_SRC_INTEVENT_MASK,
				NOCP_CNT_SRC_INTEVENT_CHAIN_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_2_SRC,
				NOCP_CNT_SRC_INTEVENT_MASK,
				NOCP_CNT_SRC_INTEVENT_CYCLE_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_3_SRC,
				NOCP_CNT_SRC_INTEVENT_MASK,
				NOCP_CNT_SRC_INTEVENT_CHAIN_MASK);
	अगर (ret < 0)
		जाओ out;


	/* Set an alarm with a max/min value of 0 to generate StatALARM */
	ret = regmap_ग_लिखो(nocp->regmap, NOCP_STAT_ALARM_MIN, 0x0);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_ग_लिखो(nocp->regmap, NOCP_STAT_ALARM_MAX, 0x0);
	अगर (ret < 0)
		जाओ out;

	/* Set AlarmMode */
	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_0_ALARM_MODE,
				NOCP_CNT_ALARM_MODE_MASK,
				NOCP_CNT_ALARM_MODE_MIN_MAX_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_1_ALARM_MODE,
				NOCP_CNT_ALARM_MODE_MASK,
				NOCP_CNT_ALARM_MODE_MIN_MAX_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_2_ALARM_MODE,
				NOCP_CNT_ALARM_MODE_MASK,
				NOCP_CNT_ALARM_MODE_MIN_MAX_MASK);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(nocp->regmap, NOCP_COUNTERS_3_ALARM_MODE,
				NOCP_CNT_ALARM_MODE_MASK,
				NOCP_CNT_ALARM_MODE_MIN_MAX_MASK);
	अगर (ret < 0)
		जाओ out;

	/* Enable the measurements by setting AlarmEn and StatEn */
	ret = regmap_update_bits(nocp->regmap, NOCP_MAIN_CTL,
			NOCP_MAIN_CTL_STATEN_MASK | NOCP_MAIN_CTL_ALARMEN_MASK,
			NOCP_MAIN_CTL_STATEN_MASK | NOCP_MAIN_CTL_ALARMEN_MASK);
	अगर (ret < 0)
		जाओ out;

	/* Set GlobalEN */
	ret = regmap_update_bits(nocp->regmap, NOCP_CFG_CTL,
				NOCP_CFG_CTL_GLOBALEN_MASK,
				NOCP_CFG_CTL_GLOBALEN_MASK);
	अगर (ret < 0)
		जाओ out;

	/* Enable NoC probe */
	ret = regmap_update_bits(nocp->regmap, NOCP_MAIN_CTL,
				NOCP_MAIN_CTL_STATEN_MASK,
				NOCP_MAIN_CTL_STATEN_MASK);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	/* Reset NoC probe */
	अगर (regmap_update_bits(nocp->regmap, NOCP_MAIN_CTL,
				NOCP_MAIN_CTL_STATEN_MASK, 0)) अणु
		dev_err(nocp->dev, "Failed to reset NoC probe device\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_nocp_get_event(काष्ठा devfreq_event_dev *edev,
				काष्ठा devfreq_event_data *edata)
अणु
	काष्ठा exynos_nocp *nocp = devfreq_event_get_drvdata(edev);
	अचिन्हित पूर्णांक counter[4];
	पूर्णांक ret;

	/* Read cycle count */
	ret = regmap_पढ़ो(nocp->regmap, NOCP_COUNTERS_0_VAL, &counter[0]);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_पढ़ो(nocp->regmap, NOCP_COUNTERS_1_VAL, &counter[1]);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_पढ़ो(nocp->regmap, NOCP_COUNTERS_2_VAL, &counter[2]);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_पढ़ो(nocp->regmap, NOCP_COUNTERS_3_VAL, &counter[3]);
	अगर (ret < 0)
		जाओ out;

	edata->load_count = ((counter[1] << 16) | counter[0]);
	edata->total_count = ((counter[3] << 16) | counter[2]);

	dev_dbg(&edev->dev, "%s (event: %ld/%ld)\n", edev->desc->name,
					edata->load_count, edata->total_count);

	वापस 0;

out:
	dev_err(nocp->dev, "Failed to read the counter of NoC probe device\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा devfreq_event_ops exynos_nocp_ops = अणु
	.set_event = exynos_nocp_set_event,
	.get_event = exynos_nocp_get_event,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_nocp_id_match[] = अणु
	अणु .compatible = "samsung,exynos5420-nocp", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_nocp_id_match);

अटल काष्ठा regmap_config exynos_nocp_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = NOCP_COUNTERS_3_VAL,
पूर्ण;

अटल पूर्णांक exynos_nocp_parse_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा exynos_nocp *nocp)
अणु
	काष्ठा device *dev = nocp->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	व्योम __iomem *base;

	अगर (!np) अणु
		dev_err(dev, "failed to find devicetree node\n");
		वापस -EINVAL;
	पूर्ण

	nocp->clk = devm_clk_get(dev, "nocp");
	अगर (IS_ERR(nocp->clk))
		nocp->clk = शून्य;

	/* Maps the memory mapped IO to control nocp रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	exynos_nocp_regmap_config.max_रेजिस्टर = resource_size(res) - 4;

	nocp->regmap = devm_regmap_init_mmio(dev, base,
					&exynos_nocp_regmap_config);
	अगर (IS_ERR(nocp->regmap)) अणु
		dev_err(dev, "failed to initialize regmap\n");
		वापस PTR_ERR(nocp->regmap);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_nocp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा exynos_nocp *nocp;
	पूर्णांक ret;

	nocp = devm_kzalloc(&pdev->dev, माप(*nocp), GFP_KERNEL);
	अगर (!nocp)
		वापस -ENOMEM;

	nocp->dev = &pdev->dev;

	/* Parse dt data to get resource */
	ret = exynos_nocp_parse_dt(pdev, nocp);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to parse devicetree for resource\n");
		वापस ret;
	पूर्ण

	/* Add devfreq-event device to measure the bandwidth of NoC */
	nocp->desc.ops = &exynos_nocp_ops;
	nocp->desc.driver_data = nocp;
	nocp->desc.name = np->full_name;
	nocp->edev = devm_devfreq_event_add_edev(&pdev->dev, &nocp->desc);
	अगर (IS_ERR(nocp->edev)) अणु
		dev_err(&pdev->dev,
			"failed to add devfreq-event device\n");
		वापस PTR_ERR(nocp->edev);
	पूर्ण
	platक्रमm_set_drvdata(pdev, nocp);

	ret = clk_prepare_enable(nocp->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare ppmu clock\n");
		वापस ret;
	पूर्ण

	pr_info("exynos-nocp: new NoC Probe device registered: %s\n",
			dev_name(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_nocp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_nocp *nocp = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(nocp->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_nocp_driver = अणु
	.probe	= exynos_nocp_probe,
	.हटाओ	= exynos_nocp_हटाओ,
	.driver = अणु
		.name	= "exynos-nocp",
		.of_match_table = exynos_nocp_id_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos_nocp_driver);

MODULE_DESCRIPTION("Exynos NoC (Network on Chip) Probe driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
