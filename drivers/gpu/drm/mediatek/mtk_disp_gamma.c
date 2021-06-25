<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2021 MediaTek Inc.
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

#घोषणा DISP_GAMMA_EN				0x0000
#घोषणा GAMMA_EN					BIT(0)
#घोषणा DISP_GAMMA_CFG				0x0020
#घोषणा GAMMA_LUT_EN					BIT(1)
#घोषणा GAMMA_DITHERING					BIT(2)
#घोषणा DISP_GAMMA_SIZE				0x0030
#घोषणा DISP_GAMMA_LUT				0x0700

#घोषणा LUT_10BIT_MASK				0x03ff

काष्ठा mtk_disp_gamma_data अणु
	bool has_dither;
पूर्ण;

/**
 * काष्ठा mtk_disp_gamma - DISP_GAMMA driver काष्ठाure
 * @ddp_comp - काष्ठाure containing type क्रमागत and hardware resources
 * @crtc - associated crtc to report irq events to
 */
काष्ठा mtk_disp_gamma अणु
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	काष्ठा cmdq_client_reg cmdq_reg;
	स्थिर काष्ठा mtk_disp_gamma_data *data;
पूर्ण;

पूर्णांक mtk_gamma_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	वापस clk_prepare_enable(gamma->clk);
पूर्ण

व्योम mtk_gamma_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	clk_disable_unprepare(gamma->clk);
पूर्ण

व्योम mtk_gamma_set_common(व्योम __iomem *regs, काष्ठा drm_crtc_state *state)
अणु
	अचिन्हित पूर्णांक i, reg;
	काष्ठा drm_color_lut *lut;
	व्योम __iomem *lut_base;
	u32 word;

	अगर (state->gamma_lut) अणु
		reg = पढ़ोl(regs + DISP_GAMMA_CFG);
		reg = reg | GAMMA_LUT_EN;
		ग_लिखोl(reg, regs + DISP_GAMMA_CFG);
		lut_base = regs + DISP_GAMMA_LUT;
		lut = (काष्ठा drm_color_lut *)state->gamma_lut->data;
		क्रम (i = 0; i < MTK_LUT_SIZE; i++) अणु
			word = (((lut[i].red >> 6) & LUT_10BIT_MASK) << 20) +
				(((lut[i].green >> 6) & LUT_10BIT_MASK) << 10) +
				((lut[i].blue >> 6) & LUT_10BIT_MASK);
			ग_लिखोl(word, (lut_base + i * 4));
		पूर्ण
	पूर्ण
पूर्ण

व्योम mtk_gamma_set(काष्ठा device *dev, काष्ठा drm_crtc_state *state)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	mtk_gamma_set_common(gamma->regs, state);
पूर्ण

व्योम mtk_gamma_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, h << 16 | w, &gamma->cmdq_reg, gamma->regs,
		      DISP_GAMMA_SIZE);
	अगर (gamma->data && gamma->data->has_dither)
		mtk_dither_set_common(gamma->regs, &gamma->cmdq_reg, bpc,
				      DISP_GAMMA_CFG, GAMMA_DITHERING, cmdq_pkt);
पूर्ण

व्योम mtk_gamma_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	ग_लिखोl(GAMMA_EN, gamma->regs + DISP_GAMMA_EN);
पूर्ण

व्योम mtk_gamma_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_gamma *gamma = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(0x0, gamma->regs + DISP_GAMMA_EN);
पूर्ण

अटल पूर्णांक mtk_disp_gamma_bind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल व्योम mtk_disp_gamma_unbind(काष्ठा device *dev, काष्ठा device *master,
				  व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_disp_gamma_component_ops = अणु
	.bind	= mtk_disp_gamma_bind,
	.unbind = mtk_disp_gamma_unbind,
पूर्ण;

अटल पूर्णांक mtk_disp_gamma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_disp_gamma *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get gamma clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "failed to ioremap gamma\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	priv->data = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, priv);

	ret = component_add(dev, &mtk_disp_gamma_component_ops);
	अगर (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_gamma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &mtk_disp_gamma_component_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_disp_gamma_data mt8173_gamma_driver_data = अणु
	.has_dither = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_gamma_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8173-disp-gamma",
	  .data = &mt8173_gamma_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-gamma"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_gamma_driver_dt_match);

काष्ठा platक्रमm_driver mtk_disp_gamma_driver = अणु
	.probe		= mtk_disp_gamma_probe,
	.हटाओ		= mtk_disp_gamma_हटाओ,
	.driver		= अणु
		.name	= "mediatek-disp-gamma",
		.owner	= THIS_MODULE,
		.of_match_table = mtk_disp_gamma_driver_dt_match,
	पूर्ण,
पूर्ण;
