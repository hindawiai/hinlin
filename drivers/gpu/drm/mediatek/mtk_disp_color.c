<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 MediaTek Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/mediatek/mtk-cmdq.h>

#समावेश "mtk_disp_drv.h"
#समावेश "mtk_drm_crtc.h"
#समावेश "mtk_drm_ddp_comp.h"

#घोषणा DISP_COLOR_CFG_MAIN			0x0400
#घोषणा DISP_COLOR_START_MT2701			0x0f00
#घोषणा DISP_COLOR_START_MT8167			0x0400
#घोषणा DISP_COLOR_START_MT8173			0x0c00
#घोषणा DISP_COLOR_START(comp)			((comp)->data->color_offset)
#घोषणा DISP_COLOR_WIDTH(comp)			(DISP_COLOR_START(comp) + 0x50)
#घोषणा DISP_COLOR_HEIGHT(comp)			(DISP_COLOR_START(comp) + 0x54)

#घोषणा COLOR_BYPASS_ALL			BIT(7)
#घोषणा COLOR_SEQ_SEL				BIT(13)

काष्ठा mtk_disp_color_data अणु
	अचिन्हित पूर्णांक color_offset;
पूर्ण;

/**
 * काष्ठा mtk_disp_color - DISP_COLOR driver काष्ठाure
 * @ddp_comp: काष्ठाure containing type क्रमागत and hardware resources
 * @crtc: associated crtc to report irq events to
 * @data: platक्रमm colour driver data
 */
काष्ठा mtk_disp_color अणु
	काष्ठा drm_crtc				*crtc;
	काष्ठा clk				*clk;
	व्योम __iomem				*regs;
	काष्ठा cmdq_client_reg			cmdq_reg;
	स्थिर काष्ठा mtk_disp_color_data	*data;
पूर्ण;

पूर्णांक mtk_color_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_color *color = dev_get_drvdata(dev);

	वापस clk_prepare_enable(color->clk);
पूर्ण

व्योम mtk_color_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_color *color = dev_get_drvdata(dev);

	clk_disable_unprepare(color->clk);
पूर्ण

व्योम mtk_color_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_color *color = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, w, &color->cmdq_reg, color->regs, DISP_COLOR_WIDTH(color));
	mtk_ddp_ग_लिखो(cmdq_pkt, h, &color->cmdq_reg, color->regs, DISP_COLOR_HEIGHT(color));
पूर्ण

व्योम mtk_color_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_color *color = dev_get_drvdata(dev);

	ग_लिखोl(COLOR_BYPASS_ALL | COLOR_SEQ_SEL,
	       color->regs + DISP_COLOR_CFG_MAIN);
	ग_लिखोl(0x1, color->regs + DISP_COLOR_START(color));
पूर्ण

अटल पूर्णांक mtk_disp_color_bind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल व्योम mtk_disp_color_unbind(काष्ठा device *dev, काष्ठा device *master,
				  व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_disp_color_component_ops = अणु
	.bind	= mtk_disp_color_bind,
	.unbind = mtk_disp_color_unbind,
पूर्ण;

अटल पूर्णांक mtk_disp_color_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_disp_color *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get color clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "failed to ioremap color\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	priv->data = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, priv);

	ret = component_add(dev, &mtk_disp_color_component_ops);
	अगर (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_color_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_disp_color_data mt2701_color_driver_data = अणु
	.color_offset = DISP_COLOR_START_MT2701,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_color_data mt8167_color_driver_data = अणु
	.color_offset = DISP_COLOR_START_MT8167,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_color_data mt8173_color_driver_data = अणु
	.color_offset = DISP_COLOR_START_MT8173,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_color_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-color",
	  .data = &mt2701_color_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8167-disp-color",
	  .data = &mt8167_color_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-color",
	  .data = &mt8173_color_driver_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_color_driver_dt_match);

काष्ठा platक्रमm_driver mtk_disp_color_driver = अणु
	.probe		= mtk_disp_color_probe,
	.हटाओ		= mtk_disp_color_हटाओ,
	.driver		= अणु
		.name	= "mediatek-disp-color",
		.owner	= THIS_MODULE,
		.of_match_table = mtk_disp_color_driver_dt_match,
	पूर्ण,
पूर्ण;
