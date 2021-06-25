<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co., Ltd
 * Author: Lin Huang <hl@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/devfreq-event.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>

#समावेश <soc/rockchip/rk3399_grf.h>

#घोषणा RK3399_DMC_NUM_CH	2

/* DDRMON_CTRL */
#घोषणा DDRMON_CTRL	0x04
#घोषणा CLR_DDRMON_CTRL	(0x1f0000 << 0)
#घोषणा LPDDR4_EN	(0x10001 << 4)
#घोषणा HARDWARE_EN	(0x10001 << 3)
#घोषणा LPDDR3_EN	(0x10001 << 2)
#घोषणा SOFTWARE_EN	(0x10001 << 1)
#घोषणा SOFTWARE_DIS	(0x10000 << 1)
#घोषणा TIME_CNT_EN	(0x10001 << 0)

#घोषणा DDRMON_CH0_COUNT_NUM		0x28
#घोषणा DDRMON_CH0_DFI_ACCESS_NUM	0x2c
#घोषणा DDRMON_CH1_COUNT_NUM		0x3c
#घोषणा DDRMON_CH1_DFI_ACCESS_NUM	0x40

काष्ठा dmc_usage अणु
	u32 access;
	u32 total;
पूर्ण;

/*
 * The dfi controller can monitor DDR load. It has an upper and lower threshold
 * क्रम the operating poपूर्णांकs. Whenever the usage leaves these bounds an event is
 * generated to indicate the DDR frequency should be changed.
 */
काष्ठा rockchip_dfi अणु
	काष्ठा devfreq_event_dev *edev;
	काष्ठा devfreq_event_desc *desc;
	काष्ठा dmc_usage ch_usage[RK3399_DMC_NUM_CH];
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा regmap *regmap_pmu;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम rockchip_dfi_start_hardware_counter(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	व्योम __iomem *dfi_regs = info->regs;
	u32 val;
	u32 ddr_type;

	/* get ddr type */
	regmap_पढ़ो(info->regmap_pmu, RK3399_PMUGRF_OS_REG2, &val);
	ddr_type = (val >> RK3399_PMUGRF_DDRTYPE_SHIFT) &
		    RK3399_PMUGRF_DDRTYPE_MASK;

	/* clear DDRMON_CTRL setting */
	ग_लिखोl_relaxed(CLR_DDRMON_CTRL, dfi_regs + DDRMON_CTRL);

	/* set ddr type to dfi */
	अगर (ddr_type == RK3399_PMUGRF_DDRTYPE_LPDDR3)
		ग_लिखोl_relaxed(LPDDR3_EN, dfi_regs + DDRMON_CTRL);
	अन्यथा अगर (ddr_type == RK3399_PMUGRF_DDRTYPE_LPDDR4)
		ग_लिखोl_relaxed(LPDDR4_EN, dfi_regs + DDRMON_CTRL);

	/* enable count, use software mode */
	ग_लिखोl_relaxed(SOFTWARE_EN, dfi_regs + DDRMON_CTRL);
पूर्ण

अटल व्योम rockchip_dfi_stop_hardware_counter(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	व्योम __iomem *dfi_regs = info->regs;

	ग_लिखोl_relaxed(SOFTWARE_DIS, dfi_regs + DDRMON_CTRL);
पूर्ण

अटल पूर्णांक rockchip_dfi_get_busier_ch(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	u32 पंचांगp, max = 0;
	u32 i, busier_ch = 0;
	व्योम __iomem *dfi_regs = info->regs;

	rockchip_dfi_stop_hardware_counter(edev);

	/* Find out which channel is busier */
	क्रम (i = 0; i < RK3399_DMC_NUM_CH; i++) अणु
		info->ch_usage[i].access = पढ़ोl_relaxed(dfi_regs +
				DDRMON_CH0_DFI_ACCESS_NUM + i * 20) * 4;
		info->ch_usage[i].total = पढ़ोl_relaxed(dfi_regs +
				DDRMON_CH0_COUNT_NUM + i * 20);
		पंचांगp = info->ch_usage[i].access;
		अगर (पंचांगp > max) अणु
			busier_ch = i;
			max = पंचांगp;
		पूर्ण
	पूर्ण
	rockchip_dfi_start_hardware_counter(edev);

	वापस busier_ch;
पूर्ण

अटल पूर्णांक rockchip_dfi_disable(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);

	rockchip_dfi_stop_hardware_counter(edev);
	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dfi_enable(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	पूर्णांक ret;

	ret = clk_prepare_enable(info->clk);
	अगर (ret) अणु
		dev_err(&edev->dev, "failed to enable dfi clk: %d\n", ret);
		वापस ret;
	पूर्ण

	rockchip_dfi_start_hardware_counter(edev);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dfi_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dfi_get_event(काष्ठा devfreq_event_dev *edev,
				  काष्ठा devfreq_event_data *edata)
अणु
	काष्ठा rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	पूर्णांक busier_ch;

	busier_ch = rockchip_dfi_get_busier_ch(edev);

	edata->load_count = info->ch_usage[busier_ch].access;
	edata->total_count = info->ch_usage[busier_ch].total;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devfreq_event_ops rockchip_dfi_ops = अणु
	.disable = rockchip_dfi_disable,
	.enable = rockchip_dfi_enable,
	.get_event = rockchip_dfi_get_event,
	.set_event = rockchip_dfi_set_event,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_dfi_id_match[] = अणु
	अणु .compatible = "rockchip,rk3399-dfi" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_dfi_id_match);

अटल पूर्णांक rockchip_dfi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_dfi *data;
	काष्ठा devfreq_event_desc *desc;
	काष्ठा device_node *np = pdev->dev.of_node, *node;

	data = devm_kzalloc(dev, माप(काष्ठा rockchip_dfi), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->regs))
		वापस PTR_ERR(data->regs);

	data->clk = devm_clk_get(dev, "pclk_ddr_mon");
	अगर (IS_ERR(data->clk)) अणु
		dev_err(dev, "Cannot get the clk dmc_clk\n");
		वापस PTR_ERR(data->clk);
	पूर्ण

	/* try to find the optional reference to the pmu syscon */
	node = of_parse_phandle(np, "rockchip,pmu", 0);
	अगर (node) अणु
		data->regmap_pmu = syscon_node_to_regmap(node);
		of_node_put(node);
		अगर (IS_ERR(data->regmap_pmu))
			वापस PTR_ERR(data->regmap_pmu);
	पूर्ण
	data->dev = dev;

	desc = devm_kzalloc(dev, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	desc->ops = &rockchip_dfi_ops;
	desc->driver_data = data;
	desc->name = np->name;
	data->desc = desc;

	data->edev = devm_devfreq_event_add_edev(&pdev->dev, desc);
	अगर (IS_ERR(data->edev)) अणु
		dev_err(&pdev->dev,
			"failed to add devfreq-event device\n");
		वापस PTR_ERR(data->edev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_dfi_driver = अणु
	.probe	= rockchip_dfi_probe,
	.driver = अणु
		.name	= "rockchip-dfi",
		.of_match_table = rockchip_dfi_id_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rockchip_dfi_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lin Huang <hl@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip DFI driver");
