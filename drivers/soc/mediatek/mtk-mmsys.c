<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/mediatek/mtk-mmsys.h>

#समावेश "mtk-mmsys.h"
#समावेश "mt8167-mmsys.h"
#समावेश "mt8183-mmsys.h"

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt2701_mmsys_driver_data = अणु
	.clk_driver = "clk-mt2701-mm",
	.routes = mmsys_शेष_routing_table,
	.num_routes = ARRAY_SIZE(mmsys_शेष_routing_table),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt2712_mmsys_driver_data = अणु
	.clk_driver = "clk-mt2712-mm",
	.routes = mmsys_शेष_routing_table,
	.num_routes = ARRAY_SIZE(mmsys_शेष_routing_table),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt6779_mmsys_driver_data = अणु
	.clk_driver = "clk-mt6779-mm",
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt6797_mmsys_driver_data = अणु
	.clk_driver = "clk-mt6797-mm",
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt8167_mmsys_driver_data = अणु
	.clk_driver = "clk-mt8167-mm",
	.routes = mt8167_mmsys_routing_table,
	.num_routes = ARRAY_SIZE(mt8167_mmsys_routing_table),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt8173_mmsys_driver_data = अणु
	.clk_driver = "clk-mt8173-mm",
	.routes = mmsys_शेष_routing_table,
	.num_routes = ARRAY_SIZE(mmsys_शेष_routing_table),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt8183_mmsys_driver_data = अणु
	.clk_driver = "clk-mt8183-mm",
	.routes = mmsys_mt8183_routing_table,
	.num_routes = ARRAY_SIZE(mmsys_mt8183_routing_table),
पूर्ण;

काष्ठा mtk_mmsys अणु
	व्योम __iomem *regs;
	स्थिर काष्ठा mtk_mmsys_driver_data *data;
पूर्ण;

व्योम mtk_mmsys_ddp_connect(काष्ठा device *dev,
			   क्रमागत mtk_ddp_comp_id cur,
			   क्रमागत mtk_ddp_comp_id next)
अणु
	काष्ठा mtk_mmsys *mmsys = dev_get_drvdata(dev);
	स्थिर काष्ठा mtk_mmsys_routes *routes = mmsys->data->routes;
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < mmsys->data->num_routes; i++)
		अगर (cur == routes[i].from_comp && next == routes[i].to_comp) अणु
			reg = पढ़ोl_relaxed(mmsys->regs + routes[i].addr) | routes[i].val;
			ग_लिखोl_relaxed(reg, mmsys->regs + routes[i].addr);
		पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mmsys_ddp_connect);

व्योम mtk_mmsys_ddp_disconnect(काष्ठा device *dev,
			      क्रमागत mtk_ddp_comp_id cur,
			      क्रमागत mtk_ddp_comp_id next)
अणु
	काष्ठा mtk_mmsys *mmsys = dev_get_drvdata(dev);
	स्थिर काष्ठा mtk_mmsys_routes *routes = mmsys->data->routes;
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < mmsys->data->num_routes; i++)
		अगर (cur == routes[i].from_comp && next == routes[i].to_comp) अणु
			reg = पढ़ोl_relaxed(mmsys->regs + routes[i].addr) & ~routes[i].val;
			ग_लिखोl_relaxed(reg, mmsys->regs + routes[i].addr);
		पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_mmsys_ddp_disconnect);

अटल पूर्णांक mtk_mmsys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा platक्रमm_device *clks;
	काष्ठा platक्रमm_device *drm;
	काष्ठा mtk_mmsys *mmsys;
	पूर्णांक ret;

	mmsys = devm_kzalloc(dev, माप(*mmsys), GFP_KERNEL);
	अगर (!mmsys)
		वापस -ENOMEM;

	mmsys->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mmsys->regs)) अणु
		ret = PTR_ERR(mmsys->regs);
		dev_err(dev, "Failed to ioremap mmsys registers: %d\n", ret);
		वापस ret;
	पूर्ण

	mmsys->data = of_device_get_match_data(&pdev->dev);
	platक्रमm_set_drvdata(pdev, mmsys);

	clks = platक्रमm_device_रेजिस्टर_data(&pdev->dev, mmsys->data->clk_driver,
					     PLATFORM_DEVID_AUTO, शून्य, 0);
	अगर (IS_ERR(clks))
		वापस PTR_ERR(clks);

	drm = platक्रमm_device_रेजिस्टर_data(&pdev->dev, "mediatek-drm",
					    PLATFORM_DEVID_AUTO, शून्य, 0);
	अगर (IS_ERR(drm)) अणु
		platक्रमm_device_unरेजिस्टर(clks);
		वापस PTR_ERR(drm);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_mtk_mmsys[] = अणु
	अणु
		.compatible = "mediatek,mt2701-mmsys",
		.data = &mt2701_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2712-mmsys",
		.data = &mt2712_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt6779-mmsys",
		.data = &mt6779_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt6797-mmsys",
		.data = &mt6797_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8167-mmsys",
		.data = &mt8167_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8173-mmsys",
		.data = &mt8173_mmsys_driver_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183-mmsys",
		.data = &mt8183_mmsys_driver_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_mmsys_drv = अणु
	.driver = अणु
		.name = "mtk-mmsys",
		.of_match_table = of_match_mtk_mmsys,
	पूर्ण,
	.probe = mtk_mmsys_probe,
पूर्ण;

builtin_platक्रमm_driver(mtk_mmsys_drv);
