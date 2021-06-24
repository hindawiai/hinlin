<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
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

#घोषणा DISP_REG_RDMA_INT_ENABLE		0x0000
#घोषणा DISP_REG_RDMA_INT_STATUS		0x0004
#घोषणा RDMA_TARGET_LINE_INT				BIT(5)
#घोषणा RDMA_FIFO_UNDERFLOW_INT				BIT(4)
#घोषणा RDMA_खातापूर्ण_ABNORMAL_INT				BIT(3)
#घोषणा RDMA_FRAME_END_INT				BIT(2)
#घोषणा RDMA_FRAME_START_INT				BIT(1)
#घोषणा RDMA_REG_UPDATE_INT				BIT(0)
#घोषणा DISP_REG_RDMA_GLOBAL_CON		0x0010
#घोषणा RDMA_ENGINE_EN					BIT(0)
#घोषणा RDMA_MODE_MEMORY				BIT(1)
#घोषणा DISP_REG_RDMA_SIZE_CON_0		0x0014
#घोषणा RDMA_MATRIX_ENABLE				BIT(17)
#घोषणा RDMA_MATRIX_INT_MTX_SEL				GENMASK(23, 20)
#घोषणा RDMA_MATRIX_INT_MTX_BT601_to_RGB		(6 << 20)
#घोषणा DISP_REG_RDMA_SIZE_CON_1		0x0018
#घोषणा DISP_REG_RDMA_TARGET_LINE		0x001c
#घोषणा DISP_RDMA_MEM_CON			0x0024
#घोषणा MEM_MODE_INPUT_FORMAT_RGB565			(0x000 << 4)
#घोषणा MEM_MODE_INPUT_FORMAT_RGB888			(0x001 << 4)
#घोषणा MEM_MODE_INPUT_FORMAT_RGBA8888			(0x002 << 4)
#घोषणा MEM_MODE_INPUT_FORMAT_ARGB8888			(0x003 << 4)
#घोषणा MEM_MODE_INPUT_FORMAT_UYVY			(0x004 << 4)
#घोषणा MEM_MODE_INPUT_FORMAT_YUYV			(0x005 << 4)
#घोषणा MEM_MODE_INPUT_SWAP				BIT(8)
#घोषणा DISP_RDMA_MEM_SRC_PITCH			0x002c
#घोषणा DISP_RDMA_MEM_GMC_SETTING_0		0x0030
#घोषणा DISP_REG_RDMA_FIFO_CON			0x0040
#घोषणा RDMA_FIFO_UNDERFLOW_EN				BIT(31)
#घोषणा RDMA_FIFO_PSEUDO_SIZE(bytes)			(((bytes) / 16) << 16)
#घोषणा RDMA_OUTPUT_VALID_FIFO_THRESHOLD(bytes)		((bytes) / 16)
#घोषणा RDMA_FIFO_SIZE(rdma)			((rdma)->data->fअगरo_size)
#घोषणा DISP_RDMA_MEM_START_ADDR		0x0f00

#घोषणा RDMA_MEM_GMC				0x40402020

काष्ठा mtk_disp_rdma_data अणु
	अचिन्हित पूर्णांक fअगरo_size;
पूर्ण;

/**
 * काष्ठा mtk_disp_rdma - DISP_RDMA driver काष्ठाure
 * @ddp_comp: काष्ठाure containing type क्रमागत and hardware resources
 * @crtc: associated crtc to report irq events to
 * @data: local driver data
 */
काष्ठा mtk_disp_rdma अणु
	काष्ठा clk			*clk;
	व्योम __iomem			*regs;
	काष्ठा cmdq_client_reg		cmdq_reg;
	स्थिर काष्ठा mtk_disp_rdma_data	*data;
	व्योम				(*vblank_cb)(व्योम *data);
	व्योम				*vblank_cb_data;
	u32				fअगरo_size;
पूर्ण;

अटल irqवापस_t mtk_disp_rdma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_disp_rdma *priv = dev_id;

	/* Clear frame completion पूर्णांकerrupt */
	ग_लिखोl(0x0, priv->regs + DISP_REG_RDMA_INT_STATUS);

	अगर (!priv->vblank_cb)
		वापस IRQ_NONE;

	priv->vblank_cb(priv->vblank_cb_data);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rdma_update_bits(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp = पढ़ोl(rdma->regs + reg);

	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	ग_लिखोl(पंचांगp, rdma->regs + reg);
पूर्ण

व्योम mtk_rdma_enable_vblank(काष्ठा device *dev,
			    व्योम (*vblank_cb)(व्योम *),
			    व्योम *vblank_cb_data)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);

	rdma->vblank_cb = vblank_cb;
	rdma->vblank_cb_data = vblank_cb_data;
	rdma_update_bits(dev, DISP_REG_RDMA_INT_ENABLE, RDMA_FRAME_END_INT,
			 RDMA_FRAME_END_INT);
पूर्ण

व्योम mtk_rdma_disable_vblank(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);

	rdma->vblank_cb = शून्य;
	rdma->vblank_cb_data = शून्य;
	rdma_update_bits(dev, DISP_REG_RDMA_INT_ENABLE, RDMA_FRAME_END_INT, 0);
पूर्ण

पूर्णांक mtk_rdma_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);

	वापस clk_prepare_enable(rdma->clk);
पूर्ण

व्योम mtk_rdma_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);

	clk_disable_unprepare(rdma->clk);
पूर्ण

व्योम mtk_rdma_start(काष्ठा device *dev)
अणु
	rdma_update_bits(dev, DISP_REG_RDMA_GLOBAL_CON, RDMA_ENGINE_EN,
			 RDMA_ENGINE_EN);
पूर्ण

व्योम mtk_rdma_stop(काष्ठा device *dev)
अणु
	rdma_update_bits(dev, DISP_REG_RDMA_GLOBAL_CON, RDMA_ENGINE_EN, 0);
पूर्ण

व्योम mtk_rdma_config(काष्ठा device *dev, अचिन्हित पूर्णांक width,
		     अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक vrefresh,
		     अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	अचिन्हित पूर्णांक threshold;
	अचिन्हित पूर्णांक reg;
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);
	u32 rdma_fअगरo_size;

	mtk_ddp_ग_लिखो_mask(cmdq_pkt, width, &rdma->cmdq_reg, rdma->regs,
			   DISP_REG_RDMA_SIZE_CON_0, 0xfff);
	mtk_ddp_ग_लिखो_mask(cmdq_pkt, height, &rdma->cmdq_reg, rdma->regs,
			   DISP_REG_RDMA_SIZE_CON_1, 0xfffff);

	अगर (rdma->fअगरo_size)
		rdma_fअगरo_size = rdma->fअगरo_size;
	अन्यथा
		rdma_fअगरo_size = RDMA_FIFO_SIZE(rdma);

	/*
	 * Enable FIFO underflow since DSI and DPI can't be blocked.
	 * Keep the FIFO pseuकरो size reset शेष of 8 KiB. Set the
	 * output threshold to 6 microseconds with 7/6 overhead to
	 * account क्रम blanking, and with a pixel depth of 4 bytes:
	 */
	threshold = width * height * vrefresh * 4 * 7 / 1000000;
	reg = RDMA_FIFO_UNDERFLOW_EN |
	      RDMA_FIFO_PSEUDO_SIZE(rdma_fअगरo_size) |
	      RDMA_OUTPUT_VALID_FIFO_THRESHOLD(threshold);
	mtk_ddp_ग_लिखो(cmdq_pkt, reg, &rdma->cmdq_reg, rdma->regs, DISP_REG_RDMA_FIFO_CON);
पूर्ण

अटल अचिन्हित पूर्णांक rdma_fmt_convert(काष्ठा mtk_disp_rdma *rdma,
				     अचिन्हित पूर्णांक fmt)
अणु
	/* The वापस value in चयन "MEM_MODE_INPUT_FORMAT_XXX"
	 * is defined in mediatek HW data sheet.
	 * The alphabet order in XXX is no relation to data
	 * arrangement in memory.
	 */
	चयन (fmt) अणु
	शेष:
	हाल DRM_FORMAT_RGB565:
		वापस MEM_MODE_INPUT_FORMAT_RGB565;
	हाल DRM_FORMAT_BGR565:
		वापस MEM_MODE_INPUT_FORMAT_RGB565 | MEM_MODE_INPUT_SWAP;
	हाल DRM_FORMAT_RGB888:
		वापस MEM_MODE_INPUT_FORMAT_RGB888;
	हाल DRM_FORMAT_BGR888:
		वापस MEM_MODE_INPUT_FORMAT_RGB888 | MEM_MODE_INPUT_SWAP;
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_RGBA8888:
		वापस MEM_MODE_INPUT_FORMAT_ARGB8888;
	हाल DRM_FORMAT_BGRX8888:
	हाल DRM_FORMAT_BGRA8888:
		वापस MEM_MODE_INPUT_FORMAT_ARGB8888 | MEM_MODE_INPUT_SWAP;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		वापस MEM_MODE_INPUT_FORMAT_RGBA8888;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		वापस MEM_MODE_INPUT_FORMAT_RGBA8888 | MEM_MODE_INPUT_SWAP;
	हाल DRM_FORMAT_UYVY:
		वापस MEM_MODE_INPUT_FORMAT_UYVY;
	हाल DRM_FORMAT_YUYV:
		वापस MEM_MODE_INPUT_FORMAT_YUYV;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक mtk_rdma_layer_nr(काष्ठा device *dev)
अणु
	वापस 1;
पूर्ण

व्योम mtk_rdma_layer_config(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			   काष्ठा mtk_plane_state *state,
			   काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_rdma *rdma = dev_get_drvdata(dev);
	काष्ठा mtk_plane_pending_state *pending = &state->pending;
	अचिन्हित पूर्णांक addr = pending->addr;
	अचिन्हित पूर्णांक pitch = pending->pitch & 0xffff;
	अचिन्हित पूर्णांक fmt = pending->क्रमmat;
	अचिन्हित पूर्णांक con;

	con = rdma_fmt_convert(rdma, fmt);
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, con, &rdma->cmdq_reg, rdma->regs, DISP_RDMA_MEM_CON);

	अगर (fmt == DRM_FORMAT_UYVY || fmt == DRM_FORMAT_YUYV) अणु
		mtk_ddp_ग_लिखो_mask(cmdq_pkt, RDMA_MATRIX_ENABLE, &rdma->cmdq_reg, rdma->regs,
				   DISP_REG_RDMA_SIZE_CON_0,
				   RDMA_MATRIX_ENABLE);
		mtk_ddp_ग_लिखो_mask(cmdq_pkt, RDMA_MATRIX_INT_MTX_BT601_to_RGB,
				   &rdma->cmdq_reg, rdma->regs, DISP_REG_RDMA_SIZE_CON_0,
				   RDMA_MATRIX_INT_MTX_SEL);
	पूर्ण अन्यथा अणु
		mtk_ddp_ग_लिखो_mask(cmdq_pkt, 0, &rdma->cmdq_reg, rdma->regs,
				   DISP_REG_RDMA_SIZE_CON_0,
				   RDMA_MATRIX_ENABLE);
	पूर्ण
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, addr, &rdma->cmdq_reg, rdma->regs,
			      DISP_RDMA_MEM_START_ADDR);
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, pitch, &rdma->cmdq_reg, rdma->regs,
			      DISP_RDMA_MEM_SRC_PITCH);
	mtk_ddp_ग_लिखो(cmdq_pkt, RDMA_MEM_GMC, &rdma->cmdq_reg, rdma->regs,
		      DISP_RDMA_MEM_GMC_SETTING_0);
	mtk_ddp_ग_लिखो_mask(cmdq_pkt, RDMA_MODE_MEMORY, &rdma->cmdq_reg, rdma->regs,
			   DISP_REG_RDMA_GLOBAL_CON, RDMA_MODE_MEMORY);

पूर्ण

अटल पूर्णांक mtk_disp_rdma_bind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	वापस 0;

पूर्ण

अटल व्योम mtk_disp_rdma_unbind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_disp_rdma_component_ops = अणु
	.bind	= mtk_disp_rdma_bind,
	.unbind = mtk_disp_rdma_unbind,
पूर्ण;

अटल पूर्णांक mtk_disp_rdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_disp_rdma *priv;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get rdma clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "failed to ioremap rdma\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	अगर (of_find_property(dev->of_node, "mediatek,rdma-fifo-size", &ret)) अणु
		ret = of_property_पढ़ो_u32(dev->of_node,
					   "mediatek,rdma-fifo-size",
					   &priv->fअगरo_size);
		अगर (ret) अणु
			dev_err(dev, "Failed to get rdma fifo size\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Disable and clear pending पूर्णांकerrupts */
	ग_लिखोl(0x0, priv->regs + DISP_REG_RDMA_INT_ENABLE);
	ग_लिखोl(0x0, priv->regs + DISP_REG_RDMA_INT_STATUS);

	ret = devm_request_irq(dev, irq, mtk_disp_rdma_irq_handler,
			       IRQF_TRIGGER_NONE, dev_name(dev), priv);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request irq %d: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	priv->data = of_device_get_match_data(dev);

	platक्रमm_set_drvdata(pdev, priv);

	ret = component_add(dev, &mtk_disp_rdma_component_ops);
	अगर (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_rdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &mtk_disp_rdma_component_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_disp_rdma_data mt2701_rdma_driver_data = अणु
	.fअगरo_size = SZ_4K,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_rdma_data mt8173_rdma_driver_data = अणु
	.fअगरo_size = SZ_8K,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_rdma_data mt8183_rdma_driver_data = अणु
	.fअगरo_size = 5 * SZ_1K,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_rdma_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-rdma",
	  .data = &mt2701_rdma_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-rdma",
	  .data = &mt8173_rdma_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-rdma",
	  .data = &mt8183_rdma_driver_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_rdma_driver_dt_match);

काष्ठा platक्रमm_driver mtk_disp_rdma_driver = अणु
	.probe		= mtk_disp_rdma_probe,
	.हटाओ		= mtk_disp_rdma_हटाओ,
	.driver		= अणु
		.name	= "mediatek-disp-rdma",
		.owner	= THIS_MODULE,
		.of_match_table = mtk_disp_rdma_driver_dt_match,
	पूर्ण,
पूर्ण;
