<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश <drm/drm_fourcc.h>

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

#घोषणा DISP_REG_OVL_INTEN			0x0004
#घोषणा OVL_FME_CPL_INT					BIT(1)
#घोषणा DISP_REG_OVL_INTSTA			0x0008
#घोषणा DISP_REG_OVL_EN				0x000c
#घोषणा DISP_REG_OVL_RST			0x0014
#घोषणा DISP_REG_OVL_ROI_SIZE			0x0020
#घोषणा DISP_REG_OVL_DATAPATH_CON		0x0024
#घोषणा OVL_LAYER_SMI_ID_EN				BIT(0)
#घोषणा OVL_BGCLR_SEL_IN				BIT(2)
#घोषणा DISP_REG_OVL_ROI_BGCLR			0x0028
#घोषणा DISP_REG_OVL_SRC_CON			0x002c
#घोषणा DISP_REG_OVL_CON(n)			(0x0030 + 0x20 * (n))
#घोषणा DISP_REG_OVL_SRC_SIZE(n)		(0x0038 + 0x20 * (n))
#घोषणा DISP_REG_OVL_OFFSET(n)			(0x003c + 0x20 * (n))
#घोषणा DISP_REG_OVL_PITCH(n)			(0x0044 + 0x20 * (n))
#घोषणा DISP_REG_OVL_RDMA_CTRL(n)		(0x00c0 + 0x20 * (n))
#घोषणा DISP_REG_OVL_RDMA_GMC(n)		(0x00c8 + 0x20 * (n))
#घोषणा DISP_REG_OVL_ADDR_MT2701		0x0040
#घोषणा DISP_REG_OVL_ADDR_MT8173		0x0f40
#घोषणा DISP_REG_OVL_ADDR(ovl, n)		((ovl)->data->addr + 0x20 * (n))

#घोषणा GMC_THRESHOLD_BITS	16
#घोषणा GMC_THRESHOLD_HIGH	((1 << GMC_THRESHOLD_BITS) / 4)
#घोषणा GMC_THRESHOLD_LOW	((1 << GMC_THRESHOLD_BITS) / 8)

#घोषणा OVL_CON_BYTE_SWAP	BIT(24)
#घोषणा OVL_CON_MTX_YUV_TO_RGB	(6 << 16)
#घोषणा OVL_CON_CLRFMT_RGB	(1 << 12)
#घोषणा OVL_CON_CLRFMT_RGBA8888	(2 << 12)
#घोषणा OVL_CON_CLRFMT_ARGB8888	(3 << 12)
#घोषणा OVL_CON_CLRFMT_UYVY	(4 << 12)
#घोषणा OVL_CON_CLRFMT_YUYV	(5 << 12)
#घोषणा OVL_CON_CLRFMT_RGB565(ovl)	((ovl)->data->fmt_rgb565_is_0 ? \
					0 : OVL_CON_CLRFMT_RGB)
#घोषणा OVL_CON_CLRFMT_RGB888(ovl)	((ovl)->data->fmt_rgb565_is_0 ? \
					OVL_CON_CLRFMT_RGB : 0)
#घोषणा	OVL_CON_AEN		BIT(8)
#घोषणा	OVL_CON_ALPHA		0xff
#घोषणा	OVL_CON_VIRT_FLIP	BIT(9)
#घोषणा	OVL_CON_HORZ_FLIP	BIT(10)

काष्ठा mtk_disp_ovl_data अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक gmc_bits;
	अचिन्हित पूर्णांक layer_nr;
	bool fmt_rgb565_is_0;
	bool smi_id_en;
पूर्ण;

/**
 * काष्ठा mtk_disp_ovl - DISP_OVL driver काष्ठाure
 * @ddp_comp: काष्ठाure containing type क्रमागत and hardware resources
 * @crtc: associated crtc to report vblank events to
 * @data: platक्रमm data
 */
काष्ठा mtk_disp_ovl अणु
	काष्ठा drm_crtc			*crtc;
	काष्ठा clk			*clk;
	व्योम __iomem			*regs;
	काष्ठा cmdq_client_reg		cmdq_reg;
	स्थिर काष्ठा mtk_disp_ovl_data	*data;
	व्योम				(*vblank_cb)(व्योम *data);
	व्योम				*vblank_cb_data;
पूर्ण;

अटल irqवापस_t mtk_disp_ovl_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_disp_ovl *priv = dev_id;

	/* Clear frame completion पूर्णांकerrupt */
	ग_लिखोl(0x0, priv->regs + DISP_REG_OVL_INTSTA);

	अगर (!priv->vblank_cb)
		वापस IRQ_NONE;

	priv->vblank_cb(priv->vblank_cb_data);

	वापस IRQ_HANDLED;
पूर्ण

व्योम mtk_ovl_enable_vblank(काष्ठा device *dev,
			   व्योम (*vblank_cb)(व्योम *),
			   व्योम *vblank_cb_data)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	ovl->vblank_cb = vblank_cb;
	ovl->vblank_cb_data = vblank_cb_data;
	ग_लिखोl(0x0, ovl->regs + DISP_REG_OVL_INTSTA);
	ग_लिखोl_relaxed(OVL_FME_CPL_INT, ovl->regs + DISP_REG_OVL_INTEN);
पूर्ण

व्योम mtk_ovl_disable_vblank(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	ovl->vblank_cb = शून्य;
	ovl->vblank_cb_data = शून्य;
	ग_लिखोl_relaxed(0x0, ovl->regs + DISP_REG_OVL_INTEN);
पूर्ण

पूर्णांक mtk_ovl_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	वापस clk_prepare_enable(ovl->clk);
पूर्ण

व्योम mtk_ovl_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	clk_disable_unprepare(ovl->clk);
पूर्ण

व्योम mtk_ovl_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	अगर (ovl->data->smi_id_en) अणु
		अचिन्हित पूर्णांक reg;

		reg = पढ़ोl(ovl->regs + DISP_REG_OVL_DATAPATH_CON);
		reg = reg | OVL_LAYER_SMI_ID_EN;
		ग_लिखोl_relaxed(reg, ovl->regs + DISP_REG_OVL_DATAPATH_CON);
	पूर्ण
	ग_लिखोl_relaxed(0x1, ovl->regs + DISP_REG_OVL_EN);
पूर्ण

व्योम mtk_ovl_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(0x0, ovl->regs + DISP_REG_OVL_EN);
	अगर (ovl->data->smi_id_en) अणु
		अचिन्हित पूर्णांक reg;

		reg = पढ़ोl(ovl->regs + DISP_REG_OVL_DATAPATH_CON);
		reg = reg & ~OVL_LAYER_SMI_ID_EN;
		ग_लिखोl_relaxed(reg, ovl->regs + DISP_REG_OVL_DATAPATH_CON);
	पूर्ण

पूर्ण

व्योम mtk_ovl_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		    अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		    अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	अगर (w != 0 && h != 0)
		mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, h << 16 | w, &ovl->cmdq_reg, ovl->regs,
				      DISP_REG_OVL_ROI_SIZE);
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, 0x0, &ovl->cmdq_reg, ovl->regs, DISP_REG_OVL_ROI_BGCLR);

	mtk_ddp_ग_लिखो(cmdq_pkt, 0x1, &ovl->cmdq_reg, ovl->regs, DISP_REG_OVL_RST);
	mtk_ddp_ग_लिखो(cmdq_pkt, 0x0, &ovl->cmdq_reg, ovl->regs, DISP_REG_OVL_RST);
पूर्ण

अचिन्हित पूर्णांक mtk_ovl_layer_nr(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	वापस ovl->data->layer_nr;
पूर्ण

अचिन्हित पूर्णांक mtk_ovl_supported_rotations(काष्ठा device *dev)
अणु
	वापस DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
	       DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y;
पूर्ण

पूर्णांक mtk_ovl_layer_check(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			काष्ठा mtk_plane_state *mtk_state)
अणु
	काष्ठा drm_plane_state *state = &mtk_state->base;
	अचिन्हित पूर्णांक rotation = 0;

	rotation = drm_rotation_simplअगरy(state->rotation,
					 DRM_MODE_ROTATE_0 |
					 DRM_MODE_REFLECT_X |
					 DRM_MODE_REFLECT_Y);
	rotation &= ~DRM_MODE_ROTATE_0;

	/* We can only करो reflection, not rotation */
	अगर ((rotation & DRM_MODE_ROTATE_MASK) != 0)
		वापस -EINVAL;

	/*
	 * TODO: Rotating/reflecting YUV buffers is not supported at this समय.
	 *	 Only RGB[AX] variants are supported.
	 */
	अगर (state->fb->क्रमmat->is_yuv && rotation != 0)
		वापस -EINVAL;

	state->rotation = rotation;

	वापस 0;
पूर्ण

व्योम mtk_ovl_layer_on(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
		      काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	अचिन्हित पूर्णांक gmc_thrshd_l;
	अचिन्हित पूर्णांक gmc_thrshd_h;
	अचिन्हित पूर्णांक gmc_value;
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, 0x1, &ovl->cmdq_reg, ovl->regs,
		      DISP_REG_OVL_RDMA_CTRL(idx));
	gmc_thrshd_l = GMC_THRESHOLD_LOW >>
		      (GMC_THRESHOLD_BITS - ovl->data->gmc_bits);
	gmc_thrshd_h = GMC_THRESHOLD_HIGH >>
		      (GMC_THRESHOLD_BITS - ovl->data->gmc_bits);
	अगर (ovl->data->gmc_bits == 10)
		gmc_value = gmc_thrshd_h | gmc_thrshd_h << 16;
	अन्यथा
		gmc_value = gmc_thrshd_l | gmc_thrshd_l << 8 |
			    gmc_thrshd_h << 16 | gmc_thrshd_h << 24;
	mtk_ddp_ग_लिखो(cmdq_pkt, gmc_value,
		      &ovl->cmdq_reg, ovl->regs, DISP_REG_OVL_RDMA_GMC(idx));
	mtk_ddp_ग_लिखो_mask(cmdq_pkt, BIT(idx), &ovl->cmdq_reg, ovl->regs,
			   DISP_REG_OVL_SRC_CON, BIT(idx));
पूर्ण

व्योम mtk_ovl_layer_off(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
		       काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो_mask(cmdq_pkt, 0, &ovl->cmdq_reg, ovl->regs,
			   DISP_REG_OVL_SRC_CON, BIT(idx));
	mtk_ddp_ग_लिखो(cmdq_pkt, 0, &ovl->cmdq_reg, ovl->regs,
		      DISP_REG_OVL_RDMA_CTRL(idx));
पूर्ण

अटल अचिन्हित पूर्णांक ovl_fmt_convert(काष्ठा mtk_disp_ovl *ovl, अचिन्हित पूर्णांक fmt)
अणु
	/* The वापस value in चयन "MEM_MODE_INPUT_FORMAT_XXX"
	 * is defined in mediatek HW data sheet.
	 * The alphabet order in XXX is no relation to data
	 * arrangement in memory.
	 */
	चयन (fmt) अणु
	शेष:
	हाल DRM_FORMAT_RGB565:
		वापस OVL_CON_CLRFMT_RGB565(ovl);
	हाल DRM_FORMAT_BGR565:
		वापस OVL_CON_CLRFMT_RGB565(ovl) | OVL_CON_BYTE_SWAP;
	हाल DRM_FORMAT_RGB888:
		वापस OVL_CON_CLRFMT_RGB888(ovl);
	हाल DRM_FORMAT_BGR888:
		वापस OVL_CON_CLRFMT_RGB888(ovl) | OVL_CON_BYTE_SWAP;
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_RGBA8888:
		वापस OVL_CON_CLRFMT_ARGB8888;
	हाल DRM_FORMAT_BGRX8888:
	हाल DRM_FORMAT_BGRA8888:
		वापस OVL_CON_CLRFMT_ARGB8888 | OVL_CON_BYTE_SWAP;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		वापस OVL_CON_CLRFMT_RGBA8888;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		वापस OVL_CON_CLRFMT_RGBA8888 | OVL_CON_BYTE_SWAP;
	हाल DRM_FORMAT_UYVY:
		वापस OVL_CON_CLRFMT_UYVY | OVL_CON_MTX_YUV_TO_RGB;
	हाल DRM_FORMAT_YUYV:
		वापस OVL_CON_CLRFMT_YUYV | OVL_CON_MTX_YUV_TO_RGB;
	पूर्ण
पूर्ण

व्योम mtk_ovl_layer_config(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			  काष्ठा mtk_plane_state *state,
			  काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);
	काष्ठा mtk_plane_pending_state *pending = &state->pending;
	अचिन्हित पूर्णांक addr = pending->addr;
	अचिन्हित पूर्णांक pitch = pending->pitch & 0xffff;
	अचिन्हित पूर्णांक fmt = pending->क्रमmat;
	अचिन्हित पूर्णांक offset = (pending->y << 16) | pending->x;
	अचिन्हित पूर्णांक src_size = (pending->height << 16) | pending->width;
	अचिन्हित पूर्णांक con;

	अगर (!pending->enable) अणु
		mtk_ovl_layer_off(dev, idx, cmdq_pkt);
		वापस;
	पूर्ण

	con = ovl_fmt_convert(ovl, fmt);
	अगर (state->base.fb && state->base.fb->क्रमmat->has_alpha)
		con |= OVL_CON_AEN | OVL_CON_ALPHA;

	अगर (pending->rotation & DRM_MODE_REFLECT_Y) अणु
		con |= OVL_CON_VIRT_FLIP;
		addr += (pending->height - 1) * pending->pitch;
	पूर्ण

	अगर (pending->rotation & DRM_MODE_REFLECT_X) अणु
		con |= OVL_CON_HORZ_FLIP;
		addr += pending->pitch - 1;
	पूर्ण

	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, con, &ovl->cmdq_reg, ovl->regs,
			      DISP_REG_OVL_CON(idx));
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, pitch, &ovl->cmdq_reg, ovl->regs,
			      DISP_REG_OVL_PITCH(idx));
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, src_size, &ovl->cmdq_reg, ovl->regs,
			      DISP_REG_OVL_SRC_SIZE(idx));
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, offset, &ovl->cmdq_reg, ovl->regs,
			      DISP_REG_OVL_OFFSET(idx));
	mtk_ddp_ग_लिखो_relaxed(cmdq_pkt, addr, &ovl->cmdq_reg, ovl->regs,
			      DISP_REG_OVL_ADDR(ovl, idx));

	mtk_ovl_layer_on(dev, idx, cmdq_pkt);
पूर्ण

व्योम mtk_ovl_bgclr_in_on(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(ovl->regs + DISP_REG_OVL_DATAPATH_CON);
	reg = reg | OVL_BGCLR_SEL_IN;
	ग_लिखोl(reg, ovl->regs + DISP_REG_OVL_DATAPATH_CON);
पूर्ण

व्योम mtk_ovl_bgclr_in_off(काष्ठा device *dev)
अणु
	काष्ठा mtk_disp_ovl *ovl = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(ovl->regs + DISP_REG_OVL_DATAPATH_CON);
	reg = reg & ~OVL_BGCLR_SEL_IN;
	ग_लिखोl(reg, ovl->regs + DISP_REG_OVL_DATAPATH_CON);
पूर्ण

अटल पूर्णांक mtk_disp_ovl_bind(काष्ठा device *dev, काष्ठा device *master,
			     व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल व्योम mtk_disp_ovl_unbind(काष्ठा device *dev, काष्ठा device *master,
				व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_disp_ovl_component_ops = अणु
	.bind	= mtk_disp_ovl_bind,
	.unbind = mtk_disp_ovl_unbind,
पूर्ण;

अटल पूर्णांक mtk_disp_ovl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_disp_ovl *priv;
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
		dev_err(dev, "failed to get ovl clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "failed to ioremap ovl\n");
		वापस PTR_ERR(priv->regs);
	पूर्ण
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	priv->data = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, priv);

	ret = devm_request_irq(dev, irq, mtk_disp_ovl_irq_handler,
			       IRQF_TRIGGER_NONE, dev_name(dev), priv);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request irq %d: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	ret = component_add(dev, &mtk_disp_ovl_component_ops);
	अगर (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_ovl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_disp_ovl_data mt2701_ovl_driver_data = अणु
	.addr = DISP_REG_OVL_ADDR_MT2701,
	.gmc_bits = 8,
	.layer_nr = 4,
	.fmt_rgb565_is_0 = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_ovl_data mt8173_ovl_driver_data = अणु
	.addr = DISP_REG_OVL_ADDR_MT8173,
	.gmc_bits = 8,
	.layer_nr = 4,
	.fmt_rgb565_is_0 = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_ovl_data mt8183_ovl_driver_data = अणु
	.addr = DISP_REG_OVL_ADDR_MT8173,
	.gmc_bits = 10,
	.layer_nr = 4,
	.fmt_rgb565_is_0 = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_disp_ovl_data mt8183_ovl_2l_driver_data = अणु
	.addr = DISP_REG_OVL_ADDR_MT8173,
	.gmc_bits = 10,
	.layer_nr = 2,
	.fmt_rgb565_is_0 = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_ovl_driver_dt_match[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-ovl",
	  .data = &mt2701_ovl_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-ovl",
	  .data = &mt8173_ovl_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-ovl",
	  .data = &mt8183_ovl_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-ovl-2l",
	  .data = &mt8183_ovl_2l_driver_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_ovl_driver_dt_match);

काष्ठा platक्रमm_driver mtk_disp_ovl_driver = अणु
	.probe		= mtk_disp_ovl_probe,
	.हटाओ		= mtk_disp_ovl_हटाओ,
	.driver		= अणु
		.name	= "mediatek-disp-ovl",
		.owner	= THIS_MODULE,
		.of_match_table = mtk_disp_ovl_driver_dt_match,
	पूर्ण,
पूर्ण;
