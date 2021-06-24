<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Authors:
 *	YT Shen <yt.shen@mediatek.com>
 *	CK Hu <ck.hu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/mediatek/mtk-cmdq.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "mtk_disp_drv.h"
#समावेश "mtk_drm_drv.h"
#समावेश "mtk_drm_plane.h"
#समावेश "mtk_drm_ddp_comp.h"
#समावेश "mtk_drm_crtc.h"

#घोषणा DISP_OD_EN				0x0000
#घोषणा DISP_OD_INTEN				0x0008
#घोषणा DISP_OD_INTSTA				0x000c
#घोषणा DISP_OD_CFG				0x0020
#घोषणा DISP_OD_SIZE				0x0030
#घोषणा DISP_DITHER_5				0x0114
#घोषणा DISP_DITHER_7				0x011c
#घोषणा DISP_DITHER_15				0x013c
#घोषणा DISP_DITHER_16				0x0140

#घोषणा DISP_REG_UFO_START			0x0000

#घोषणा DISP_AAL_EN				0x0000
#घोषणा DISP_AAL_SIZE				0x0030

#घोषणा DISP_DITHER_EN				0x0000
#घोषणा DITHER_EN				BIT(0)
#घोषणा DISP_DITHER_CFG				0x0020
#घोषणा DITHER_RELAY_MODE			BIT(0)
#घोषणा DITHER_ENGINE_EN			BIT(1)
#घोषणा DISP_DITHER_SIZE			0x0030

#घोषणा LUT_10BIT_MASK				0x03ff

#घोषणा OD_RELAYMODE				BIT(0)

#घोषणा UFO_BYPASS				BIT(2)

#घोषणा AAL_EN					BIT(0)

#घोषणा DISP_DITHERING				BIT(2)
#घोषणा DITHER_LSB_ERR_SHIFT_R(x)		(((x) & 0x7) << 28)
#घोषणा DITHER_OVFLW_BIT_R(x)			(((x) & 0x7) << 24)
#घोषणा DITHER_ADD_LSHIFT_R(x)			(((x) & 0x7) << 20)
#घोषणा DITHER_ADD_RSHIFT_R(x)			(((x) & 0x7) << 16)
#घोषणा DITHER_NEW_BIT_MODE			BIT(0)
#घोषणा DITHER_LSB_ERR_SHIFT_B(x)		(((x) & 0x7) << 28)
#घोषणा DITHER_OVFLW_BIT_B(x)			(((x) & 0x7) << 24)
#घोषणा DITHER_ADD_LSHIFT_B(x)			(((x) & 0x7) << 20)
#घोषणा DITHER_ADD_RSHIFT_B(x)			(((x) & 0x7) << 16)
#घोषणा DITHER_LSB_ERR_SHIFT_G(x)		(((x) & 0x7) << 12)
#घोषणा DITHER_OVFLW_BIT_G(x)			(((x) & 0x7) << 8)
#घोषणा DITHER_ADD_LSHIFT_G(x)			(((x) & 0x7) << 4)
#घोषणा DITHER_ADD_RSHIFT_G(x)			(((x) & 0x7) << 0)

काष्ठा mtk_ddp_comp_dev अणु
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	काष्ठा cmdq_client_reg cmdq_reg;
पूर्ण;

व्योम mtk_ddp_ग_लिखो(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
		   काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
		   अचिन्हित पूर्णांक offset)
अणु
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	अगर (cmdq_pkt)
		cmdq_pkt_ग_लिखो(cmdq_pkt, cmdq_reg->subsys,
			       cmdq_reg->offset + offset, value);
	अन्यथा
#पूर्ण_अगर
		ग_लिखोl(value, regs + offset);
पूर्ण

व्योम mtk_ddp_ग_लिखो_relaxed(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
			   काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
			   अचिन्हित पूर्णांक offset)
अणु
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	अगर (cmdq_pkt)
		cmdq_pkt_ग_लिखो(cmdq_pkt, cmdq_reg->subsys,
			       cmdq_reg->offset + offset, value);
	अन्यथा
#पूर्ण_अगर
		ग_लिखोl_relaxed(value, regs + offset);
पूर्ण

व्योम mtk_ddp_ग_लिखो_mask(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
			काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
			अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक mask)
अणु
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	अगर (cmdq_pkt) अणु
		cmdq_pkt_ग_लिखो_mask(cmdq_pkt, cmdq_reg->subsys,
				    cmdq_reg->offset + offset, value, mask);
	पूर्ण अन्यथा अणु
#पूर्ण_अगर
		u32 पंचांगp = पढ़ोl(regs + offset);

		पंचांगp = (पंचांगp & ~mask) | (value & mask);
		ग_लिखोl(पंचांगp, regs + offset);
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mtk_ddp_clk_enable(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	वापस clk_prepare_enable(priv->clk);
पूर्ण

अटल व्योम mtk_ddp_clk_disable(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->clk);
पूर्ण

व्योम mtk_dither_set_common(व्योम __iomem *regs, काष्ठा cmdq_client_reg *cmdq_reg,
			   अचिन्हित पूर्णांक bpc, अचिन्हित पूर्णांक cfg,
			   अचिन्हित पूर्णांक dither_en, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	/* If bpc equal to 0, the dithering function didn't be enabled */
	अगर (bpc == 0)
		वापस;

	अगर (bpc >= MTK_MIN_BPC) अणु
		mtk_ddp_ग_लिखो(cmdq_pkt, 0, cmdq_reg, regs, DISP_DITHER_5);
		mtk_ddp_ग_लिखो(cmdq_pkt, 0, cmdq_reg, regs, DISP_DITHER_7);
		mtk_ddp_ग_लिखो(cmdq_pkt,
			      DITHER_LSB_ERR_SHIFT_R(MTK_MAX_BPC - bpc) |
			      DITHER_ADD_LSHIFT_R(MTK_MAX_BPC - bpc) |
			      DITHER_NEW_BIT_MODE,
			      cmdq_reg, regs, DISP_DITHER_15);
		mtk_ddp_ग_लिखो(cmdq_pkt,
			      DITHER_LSB_ERR_SHIFT_B(MTK_MAX_BPC - bpc) |
			      DITHER_ADD_LSHIFT_B(MTK_MAX_BPC - bpc) |
			      DITHER_LSB_ERR_SHIFT_G(MTK_MAX_BPC - bpc) |
			      DITHER_ADD_LSHIFT_G(MTK_MAX_BPC - bpc),
			      cmdq_reg, regs, DISP_DITHER_16);
		mtk_ddp_ग_लिखो(cmdq_pkt, dither_en, cmdq_reg, regs, cfg);
	पूर्ण
पूर्ण

अटल व्योम mtk_dither_set(काष्ठा device *dev, अचिन्हित पूर्णांक bpc,
		    अचिन्हित पूर्णांक cfg, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	mtk_dither_set_common(priv->regs, &priv->cmdq_reg, bpc, cfg,
			      DISP_DITHERING, cmdq_pkt);
पूर्ण

अटल व्योम mtk_od_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
			  अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
			  अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, w << 16 | h, &priv->cmdq_reg, priv->regs, DISP_OD_SIZE);
	mtk_ddp_ग_लिखो(cmdq_pkt, OD_RELAYMODE, &priv->cmdq_reg, priv->regs, DISP_OD_CFG);
	mtk_dither_set(dev, bpc, DISP_OD_CFG, cmdq_pkt);
पूर्ण

अटल व्योम mtk_od_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl(1, priv->regs + DISP_OD_EN);
पूर्ण

अटल व्योम mtk_ufoe_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl(UFO_BYPASS, priv->regs + DISP_REG_UFO_START);
पूर्ण

अटल व्योम mtk_aal_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
			   अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
			   अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, w << 16 | h, &priv->cmdq_reg, priv->regs, DISP_AAL_SIZE);
पूर्ण

अटल व्योम mtk_aal_gamma_set(काष्ठा device *dev, काष्ठा drm_crtc_state *state)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	mtk_gamma_set_common(priv->regs, state);
पूर्ण

अटल व्योम mtk_aal_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl(AAL_EN, priv->regs + DISP_AAL_EN);
पूर्ण

अटल व्योम mtk_aal_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(0x0, priv->regs + DISP_AAL_EN);
पूर्ण

अटल व्योम mtk_dither_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
			      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
			      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	mtk_ddp_ग_लिखो(cmdq_pkt, h << 16 | w, &priv->cmdq_reg, priv->regs, DISP_DITHER_SIZE);
	mtk_ddp_ग_लिखो(cmdq_pkt, DITHER_RELAY_MODE, &priv->cmdq_reg, priv->regs, DISP_DITHER_CFG);
	mtk_dither_set_common(priv->regs, &priv->cmdq_reg, bpc, DISP_DITHER_CFG,
			      DITHER_ENGINE_EN, cmdq_pkt);
पूर्ण

अटल व्योम mtk_dither_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl(DITHER_EN, priv->regs + DISP_DITHER_EN);
पूर्ण

अटल व्योम mtk_dither_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_ddp_comp_dev *priv = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(0x0, priv->regs + DISP_DITHER_EN);
पूर्ण

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_aal = अणु
	.clk_enable = mtk_ddp_clk_enable,
	.clk_disable = mtk_ddp_clk_disable,
	.gamma_set = mtk_aal_gamma_set,
	.config = mtk_aal_config,
	.start = mtk_aal_start,
	.stop = mtk_aal_stop,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_ccorr = अणु
	.clk_enable = mtk_ccorr_clk_enable,
	.clk_disable = mtk_ccorr_clk_disable,
	.config = mtk_ccorr_config,
	.start = mtk_ccorr_start,
	.stop = mtk_ccorr_stop,
	.cपंचांग_set = mtk_ccorr_cपंचांग_set,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_color = अणु
	.clk_enable = mtk_color_clk_enable,
	.clk_disable = mtk_color_clk_disable,
	.config = mtk_color_config,
	.start = mtk_color_start,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_dither = अणु
	.clk_enable = mtk_ddp_clk_enable,
	.clk_disable = mtk_ddp_clk_disable,
	.config = mtk_dither_config,
	.start = mtk_dither_start,
	.stop = mtk_dither_stop,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_dpi = अणु
	.start = mtk_dpi_start,
	.stop = mtk_dpi_stop,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_dsi = अणु
	.start = mtk_dsi_ddp_start,
	.stop = mtk_dsi_ddp_stop,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_gamma = अणु
	.clk_enable = mtk_gamma_clk_enable,
	.clk_disable = mtk_gamma_clk_disable,
	.gamma_set = mtk_gamma_set,
	.config = mtk_gamma_config,
	.start = mtk_gamma_start,
	.stop = mtk_gamma_stop,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_od = अणु
	.clk_enable = mtk_ddp_clk_enable,
	.clk_disable = mtk_ddp_clk_disable,
	.config = mtk_od_config,
	.start = mtk_od_start,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_ovl = अणु
	.clk_enable = mtk_ovl_clk_enable,
	.clk_disable = mtk_ovl_clk_disable,
	.config = mtk_ovl_config,
	.start = mtk_ovl_start,
	.stop = mtk_ovl_stop,
	.enable_vblank = mtk_ovl_enable_vblank,
	.disable_vblank = mtk_ovl_disable_vblank,
	.supported_rotations = mtk_ovl_supported_rotations,
	.layer_nr = mtk_ovl_layer_nr,
	.layer_check = mtk_ovl_layer_check,
	.layer_config = mtk_ovl_layer_config,
	.bgclr_in_on = mtk_ovl_bgclr_in_on,
	.bgclr_in_off = mtk_ovl_bgclr_in_off,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_rdma = अणु
	.clk_enable = mtk_rdma_clk_enable,
	.clk_disable = mtk_rdma_clk_disable,
	.config = mtk_rdma_config,
	.start = mtk_rdma_start,
	.stop = mtk_rdma_stop,
	.enable_vblank = mtk_rdma_enable_vblank,
	.disable_vblank = mtk_rdma_disable_vblank,
	.layer_nr = mtk_rdma_layer_nr,
	.layer_config = mtk_rdma_layer_config,
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_funcs ddp_ufoe = अणु
	.clk_enable = mtk_ddp_clk_enable,
	.clk_disable = mtk_ddp_clk_disable,
	.start = mtk_ufoe_start,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mtk_ddp_comp_stem[MTK_DDP_COMP_TYPE_MAX] = अणु
	[MTK_DISP_OVL] = "ovl",
	[MTK_DISP_OVL_2L] = "ovl-2l",
	[MTK_DISP_RDMA] = "rdma",
	[MTK_DISP_WDMA] = "wdma",
	[MTK_DISP_COLOR] = "color",
	[MTK_DISP_CCORR] = "ccorr",
	[MTK_DISP_AAL] = "aal",
	[MTK_DISP_GAMMA] = "gamma",
	[MTK_DISP_DITHER] = "dither",
	[MTK_DISP_UFOE] = "ufoe",
	[MTK_DSI] = "dsi",
	[MTK_DPI] = "dpi",
	[MTK_DISP_PWM] = "pwm",
	[MTK_DISP_MUTEX] = "mutex",
	[MTK_DISP_OD] = "od",
	[MTK_DISP_BLS] = "bls",
पूर्ण;

काष्ठा mtk_ddp_comp_match अणु
	क्रमागत mtk_ddp_comp_type type;
	पूर्णांक alias_id;
	स्थिर काष्ठा mtk_ddp_comp_funcs *funcs;
पूर्ण;

अटल स्थिर काष्ठा mtk_ddp_comp_match mtk_ddp_matches[DDP_COMPONENT_ID_MAX] = अणु
	[DDP_COMPONENT_AAL0]	= अणु MTK_DISP_AAL,	0, &ddp_aal पूर्ण,
	[DDP_COMPONENT_AAL1]	= अणु MTK_DISP_AAL,	1, &ddp_aal पूर्ण,
	[DDP_COMPONENT_BLS]	= अणु MTK_DISP_BLS,	0, शून्य पूर्ण,
	[DDP_COMPONENT_CCORR]	= अणु MTK_DISP_CCORR,	0, &ddp_ccorr पूर्ण,
	[DDP_COMPONENT_COLOR0]	= अणु MTK_DISP_COLOR,	0, &ddp_color पूर्ण,
	[DDP_COMPONENT_COLOR1]	= अणु MTK_DISP_COLOR,	1, &ddp_color पूर्ण,
	[DDP_COMPONENT_DITHER]	= अणु MTK_DISP_DITHER,	0, &ddp_dither पूर्ण,
	[DDP_COMPONENT_DPI0]	= अणु MTK_DPI,		0, &ddp_dpi पूर्ण,
	[DDP_COMPONENT_DPI1]	= अणु MTK_DPI,		1, &ddp_dpi पूर्ण,
	[DDP_COMPONENT_DSI0]	= अणु MTK_DSI,		0, &ddp_dsi पूर्ण,
	[DDP_COMPONENT_DSI1]	= अणु MTK_DSI,		1, &ddp_dsi पूर्ण,
	[DDP_COMPONENT_DSI2]	= अणु MTK_DSI,		2, &ddp_dsi पूर्ण,
	[DDP_COMPONENT_DSI3]	= अणु MTK_DSI,		3, &ddp_dsi पूर्ण,
	[DDP_COMPONENT_GAMMA]	= अणु MTK_DISP_GAMMA,	0, &ddp_gamma पूर्ण,
	[DDP_COMPONENT_OD0]	= अणु MTK_DISP_OD,	0, &ddp_od पूर्ण,
	[DDP_COMPONENT_OD1]	= अणु MTK_DISP_OD,	1, &ddp_od पूर्ण,
	[DDP_COMPONENT_OVL0]	= अणु MTK_DISP_OVL,	0, &ddp_ovl पूर्ण,
	[DDP_COMPONENT_OVL1]	= अणु MTK_DISP_OVL,	1, &ddp_ovl पूर्ण,
	[DDP_COMPONENT_OVL_2L0]	= अणु MTK_DISP_OVL_2L,	0, &ddp_ovl पूर्ण,
	[DDP_COMPONENT_OVL_2L1]	= अणु MTK_DISP_OVL_2L,	1, &ddp_ovl पूर्ण,
	[DDP_COMPONENT_PWM0]	= अणु MTK_DISP_PWM,	0, शून्य पूर्ण,
	[DDP_COMPONENT_PWM1]	= अणु MTK_DISP_PWM,	1, शून्य पूर्ण,
	[DDP_COMPONENT_PWM2]	= अणु MTK_DISP_PWM,	2, शून्य पूर्ण,
	[DDP_COMPONENT_RDMA0]	= अणु MTK_DISP_RDMA,	0, &ddp_rdma पूर्ण,
	[DDP_COMPONENT_RDMA1]	= अणु MTK_DISP_RDMA,	1, &ddp_rdma पूर्ण,
	[DDP_COMPONENT_RDMA2]	= अणु MTK_DISP_RDMA,	2, &ddp_rdma पूर्ण,
	[DDP_COMPONENT_UFOE]	= अणु MTK_DISP_UFOE,	0, &ddp_ufoe पूर्ण,
	[DDP_COMPONENT_WDMA0]	= अणु MTK_DISP_WDMA,	0, शून्य पूर्ण,
	[DDP_COMPONENT_WDMA1]	= अणु MTK_DISP_WDMA,	1, शून्य पूर्ण,
पूर्ण;

अटल bool mtk_drm_find_comp_in_ddp(काष्ठा device *dev,
				     स्थिर क्रमागत mtk_ddp_comp_id *path,
				     अचिन्हित पूर्णांक path_len,
				     काष्ठा mtk_ddp_comp *ddp_comp)
अणु
	अचिन्हित पूर्णांक i;

	अगर (path == शून्य)
		वापस false;

	क्रम (i = 0U; i < path_len; i++)
		अगर (dev == ddp_comp[path[i]].dev)
			वापस true;

	वापस false;
पूर्ण

पूर्णांक mtk_ddp_comp_get_id(काष्ठा device_node *node,
			क्रमागत mtk_ddp_comp_type comp_type)
अणु
	पूर्णांक id = of_alias_get_id(node, mtk_ddp_comp_stem[comp_type]);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mtk_ddp_matches); i++) अणु
		अगर (comp_type == mtk_ddp_matches[i].type &&
		    (id < 0 || id == mtk_ddp_matches[i].alias_id))
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अचिन्हित पूर्णांक mtk_drm_find_possible_crtc_by_comp(काष्ठा drm_device *drm,
						काष्ठा device *dev)
अणु
	काष्ठा mtk_drm_निजी *निजी = drm->dev_निजी;
	अचिन्हित पूर्णांक ret = 0;

	अगर (mtk_drm_find_comp_in_ddp(dev, निजी->data->मुख्य_path, निजी->data->मुख्य_len,
				     निजी->ddp_comp))
		ret = BIT(0);
	अन्यथा अगर (mtk_drm_find_comp_in_ddp(dev, निजी->data->ext_path,
					  निजी->data->ext_len, निजी->ddp_comp))
		ret = BIT(1);
	अन्यथा अगर (mtk_drm_find_comp_in_ddp(dev, निजी->data->third_path,
					  निजी->data->third_len, निजी->ddp_comp))
		ret = BIT(2);
	अन्यथा
		DRM_INFO("Failed to find comp in ddp table\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_ddp_get_larb_dev(काष्ठा device_node *node, काष्ठा mtk_ddp_comp *comp,
				काष्ठा device *dev)
अणु
	काष्ठा device_node *larb_node;
	काष्ठा platक्रमm_device *larb_pdev;

	larb_node = of_parse_phandle(node, "mediatek,larb", 0);
	अगर (!larb_node) अणु
		dev_err(dev, "Missing mediadek,larb phandle in %pOF node\n", node);
		वापस -EINVAL;
	पूर्ण

	larb_pdev = of_find_device_by_node(larb_node);
	अगर (!larb_pdev) अणु
		dev_warn(dev, "Waiting for larb device %pOF\n", larb_node);
		of_node_put(larb_node);
		वापस -EPROBE_DEFER;
	पूर्ण
	of_node_put(larb_node);
	comp->larb_dev = &larb_pdev->dev;

	वापस 0;
पूर्ण

पूर्णांक mtk_ddp_comp_init(काष्ठा device_node *node, काष्ठा mtk_ddp_comp *comp,
		      क्रमागत mtk_ddp_comp_id comp_id)
अणु
	काष्ठा platक्रमm_device *comp_pdev;
	क्रमागत mtk_ddp_comp_type type;
	काष्ठा mtk_ddp_comp_dev *priv;
	पूर्णांक ret;

	अगर (comp_id < 0 || comp_id >= DDP_COMPONENT_ID_MAX)
		वापस -EINVAL;

	type = mtk_ddp_matches[comp_id].type;

	comp->id = comp_id;
	comp->funcs = mtk_ddp_matches[comp_id].funcs;
	comp_pdev = of_find_device_by_node(node);
	अगर (!comp_pdev) अणु
		DRM_INFO("Waiting for device %s\n", node->full_name);
		वापस -EPROBE_DEFER;
	पूर्ण
	comp->dev = &comp_pdev->dev;

	/* Only DMA capable components need the LARB property */
	अगर (type == MTK_DISP_OVL ||
	    type == MTK_DISP_OVL_2L ||
	    type == MTK_DISP_RDMA ||
	    type == MTK_DISP_WDMA) अणु
		ret = mtk_ddp_get_larb_dev(node, comp, comp->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (type == MTK_DISP_BLS ||
	    type == MTK_DISP_CCORR ||
	    type == MTK_DISP_COLOR ||
	    type == MTK_DISP_GAMMA ||
	    type == MTK_DPI ||
	    type == MTK_DSI ||
	    type == MTK_DISP_OVL ||
	    type == MTK_DISP_OVL_2L ||
	    type == MTK_DISP_PWM ||
	    type == MTK_DISP_RDMA)
		वापस 0;

	priv = devm_kzalloc(comp->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = of_iomap(node, 0);
	priv->clk = of_clk_get(node, 0);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	ret = cmdq_dev_get_client_reg(comp->dev, &priv->cmdq_reg, 0);
	अगर (ret)
		dev_dbg(comp->dev, "get mediatek,gce-client-reg fail!\n");
#पूर्ण_अगर

	platक्रमm_set_drvdata(comp_pdev, priv);

	वापस 0;
पूर्ण
