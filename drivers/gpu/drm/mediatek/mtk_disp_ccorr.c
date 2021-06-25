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

#घोषणा DISP_CCORR_EN				0x0000
#घोषणा CCORR_EN					BIT(0)
#घोषणा DISP_CCORR_CFG				0x0020
#घोषणा CCORR_RELAY_MODE				BIT(0)
#घोषणा CCORR_ENGINE_EN					BIT(1)
#घोषणा CCORR_GAMMA_OFF					BIT(2)
#घोषणा CCORR_WGAMUT_SRC_CLIP				BIT(3)
#घोषणा DISP_CCORR_SIZE				0x0030
#घोषणा DISP_CCORR_COEF_0			0x0080
#घोषणा DISP_CCORR_COEF_1			0x0084
#घोषणा DISP_CCORR_COEF_2			0x0088
#घोषणा DISP_CCORR_COEF_3			0x008C
#घोषणा DISP_CCORR_COEF_4			0x0090

काष्ठा mtk_disp_ccorr_data अणु
	u32 matrix_bits;
पूर्ण;

/**
 * काष्ठा mtk_disp_ccorr - DISP_CCORR driver काष्ठाure
 * @ddp_comp - काष्ठाure containing type क्रमागत and hardware resources
 * @crtc - associated crtc to report irq events to
 */
काष्ठा mtk_disp_ccorr अणु
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	काष्ठा cmdq_client_reg cmdq_reg;
	स्थिर काष्ठा mtk_disp_ccorr_data	*data;
पूर्ण;

पूर्णांक mtk_ccorr_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);

	वापस clk_prepare_enable(ccorr->clk);
पूर्ण

व्योम mtk_ccorr_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);

	clk_disable_unprepare(ccorr->clk);
पूर्ण

व्योम mtk_ccorr_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
			     अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
			     अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, w << 16 | h, &ccorr->cmdq_reg, ccorr->regs,
		      DISP_CCORR_SIZE);
	mtk_ddp_ग_लिखो(cmdq_pkt, CCORR_ENGINE_EN, &ccorr->cmdq_reg, ccorr->regs,
		      DISP_CCORR_CFG);
पूर्ण

व्योम mtk_ccorr_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);

	ग_लिखोl(CCORR_EN, ccorr->regs + DISP_CCORR_EN);
पूर्ण

व्योम mtk_ccorr_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(0x0, ccorr->regs + DISP_CCORR_EN);
पूर्ण

/* Converts a DRM S31.32 value to the HW S1.n क्रमmat. */
अटल u16 mtk_cपंचांग_s31_32_to_s1_n(u64 in, u32 n)
अणु
	u16 r;

	/* Sign bit. */
	r = in & BIT_ULL(63) ? BIT(n + 1) : 0;

	अगर ((in & GENMASK_ULL(62, 33)) > 0) अणु
		/* identity value 0x100000000 -> 0x400(mt8183), */
		/* identity value 0x100000000 -> 0x800(mt8192), */
		/* अगर bigger this, set it to max 0x7ff. */
		r |= GENMASK(n, 0);
	पूर्ण अन्यथा अणु
		/* take the n+1 most important bits. */
		r |= (in >> (32 - n)) & GENMASK(n, 0);
	पूर्ण

	वापस r;
पूर्ण

व्योम mtk_ccorr_cपंचांग_set(काष्ठा device *dev, काष्ठा drm_crtc_state *state)
अणु
	काष्ठा mtk_disp_ccorr *ccorr = dev_get_drvdata(dev);
	काष्ठा drm_property_blob *blob = state->cपंचांग;
	काष्ठा drm_color_cपंचांग *cपंचांग;
	स्थिर u64 *input;
	uपूर्णांक16_t coeffs[9] = अणु 0 पूर्ण;
	पूर्णांक i;
	काष्ठा cmdq_pkt *cmdq_pkt = शून्य;
	u32 matrix_bits = ccorr->data->matrix_bits;

	अगर (!blob)
		वापस;

	cपंचांग = (काष्ठा drm_color_cपंचांग *)blob->data;
	input = cपंचांग->matrix;

	क्रम (i = 0; i < ARRAY_SIZE(coeffs); i++)
		coeffs[i] = mtk_cपंचांग_s31_32_to_s1_n(input[i], matrix_bits);

	mtk_ddp_ग_लिखो(cmdq_pkt, coeffs[0] << 16 | coeffs[1],
		      &ccorr->cmdq_reg, ccorr->regs, DISP_CCORR_COEF_0);
	mtk_ddp_ग_लिखो(cmdq_pkt, coeffs[2] << 16 | coeffs[3],
		      &ccorr->cmdq_reg, ccorr->regs, DISP_CCORR_COEF_1);
	mtk_ddp_ग_लिखो(cmdq_pkt, coeffs[4] << 16 | coeffs[5],
		      &ccorr->cmdq_reg, ccorr->regs, DISP_CCORR_COEF_2);
	mtk_ddp_ग_लिखो(cmdq_pkt, coeffs[6] << 16 | coeffs[7],
		      &ccorr->cmdq_reg, ccorr->regs, DISP_CCORR_COEF_3);
	mtk_ddp_ग_लिखो(cmdq_pkt, coeffs[8] << 16,
		      &ccorr->cmdq_reg, ccorr->regs, DISP_CCORR_COEF_4);
पूर्ण

अटल पूर्णांक mtk_disp_ccorr_bind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल व्योम mtk_disp_ccorr_unbind(काष्ठा device *dev, काष्ठा device *master,
				  व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_disp_ccorr_component_ops = अणु
	.bind	= mtk_disp_ccorr_bind,
	.unbind	= mtk_disp_ccorr_unbind,
पूर्ण;

अटल पूर्णांक mtk_disp_ccorr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_disp_ccorr *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get ccorr clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "failed to ioremap ccorr\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	priv->data = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, priv);

	ret = component_add(dev, &mtk_disp_ccorr_component_ops);
	अगर (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_ccorr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &mtk_disp_ccorr_component_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_disp_ccorr_data mt8183_ccorr_driver_data = अणु
	.matrix_bits = 10,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_ccorr_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8183-disp-ccorr",
	  .data = &mt8183_ccorr_driver_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_ccorr_driver_dt_match);

काष्ठा platक्रमm_driver mtk_disp_ccorr_driver = अणु
	.probe		= mtk_disp_ccorr_probe,
	.हटाओ		= mtk_disp_ccorr_हटाओ,
	.driver		= अणु
		.name	= "mediatek-disp-ccorr",
		.owner	= THIS_MODULE,
		.of_match_table = mtk_disp_ccorr_driver_dt_match,
	पूर्ण,
पूर्ण;
