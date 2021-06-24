<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#अगर_अघोषित _MTK_DISP_DRV_H_
#घोषणा _MTK_DISP_DRV_H_

#समावेश <linux/soc/mediatek/mtk-cmdq.h>
#समावेश "mtk_drm_plane.h"

व्योम mtk_ccorr_cपंचांग_set(काष्ठा device *dev, काष्ठा drm_crtc_state *state);
पूर्णांक mtk_ccorr_clk_enable(काष्ठा device *dev);
व्योम mtk_ccorr_clk_disable(काष्ठा device *dev);
व्योम mtk_ccorr_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_ccorr_start(काष्ठा device *dev);
व्योम mtk_ccorr_stop(काष्ठा device *dev);

व्योम mtk_color_bypass_shaकरोw(काष्ठा device *dev);
पूर्णांक mtk_color_clk_enable(काष्ठा device *dev);
व्योम mtk_color_clk_disable(काष्ठा device *dev);
व्योम mtk_color_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_color_start(काष्ठा device *dev);

व्योम mtk_dither_set_common(व्योम __iomem *regs, काष्ठा cmdq_client_reg *cmdq_reg,
			   अचिन्हित पूर्णांक bpc, अचिन्हित पूर्णांक cfg,
			   अचिन्हित पूर्णांक dither_en, काष्ठा cmdq_pkt *cmdq_pkt);

व्योम mtk_dpi_start(काष्ठा device *dev);
व्योम mtk_dpi_stop(काष्ठा device *dev);

व्योम mtk_dsi_ddp_start(काष्ठा device *dev);
व्योम mtk_dsi_ddp_stop(काष्ठा device *dev);

पूर्णांक mtk_gamma_clk_enable(काष्ठा device *dev);
व्योम mtk_gamma_clk_disable(काष्ठा device *dev);
व्योम mtk_gamma_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		      अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		      अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_gamma_set(काष्ठा device *dev, काष्ठा drm_crtc_state *state);
व्योम mtk_gamma_set_common(व्योम __iomem *regs, काष्ठा drm_crtc_state *state);
व्योम mtk_gamma_start(काष्ठा device *dev);
व्योम mtk_gamma_stop(काष्ठा device *dev);

व्योम mtk_ovl_bgclr_in_on(काष्ठा device *dev);
व्योम mtk_ovl_bgclr_in_off(काष्ठा device *dev);
व्योम mtk_ovl_bypass_shaकरोw(काष्ठा device *dev);
पूर्णांक mtk_ovl_clk_enable(काष्ठा device *dev);
व्योम mtk_ovl_clk_disable(काष्ठा device *dev);
व्योम mtk_ovl_config(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		    अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		    अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
पूर्णांक mtk_ovl_layer_check(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			काष्ठा mtk_plane_state *mtk_state);
व्योम mtk_ovl_layer_config(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			  काष्ठा mtk_plane_state *state,
			  काष्ठा cmdq_pkt *cmdq_pkt);
अचिन्हित पूर्णांक mtk_ovl_layer_nr(काष्ठा device *dev);
व्योम mtk_ovl_layer_on(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
		      काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_ovl_layer_off(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
		       काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_ovl_start(काष्ठा device *dev);
व्योम mtk_ovl_stop(काष्ठा device *dev);
अचिन्हित पूर्णांक mtk_ovl_supported_rotations(काष्ठा device *dev);
व्योम mtk_ovl_enable_vblank(काष्ठा device *dev,
			   व्योम (*vblank_cb)(व्योम *),
			   व्योम *vblank_cb_data);
व्योम mtk_ovl_disable_vblank(काष्ठा device *dev);

व्योम mtk_rdma_bypass_shaकरोw(काष्ठा device *dev);
पूर्णांक mtk_rdma_clk_enable(काष्ठा device *dev);
व्योम mtk_rdma_clk_disable(काष्ठा device *dev);
व्योम mtk_rdma_config(काष्ठा device *dev, अचिन्हित पूर्णांक width,
		     अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक vrefresh,
		     अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
अचिन्हित पूर्णांक mtk_rdma_layer_nr(काष्ठा device *dev);
व्योम mtk_rdma_layer_config(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			   काष्ठा mtk_plane_state *state,
			   काष्ठा cmdq_pkt *cmdq_pkt);
व्योम mtk_rdma_start(काष्ठा device *dev);
व्योम mtk_rdma_stop(काष्ठा device *dev);
व्योम mtk_rdma_enable_vblank(काष्ठा device *dev,
			    व्योम (*vblank_cb)(व्योम *),
			    व्योम *vblank_cb_data);
व्योम mtk_rdma_disable_vblank(काष्ठा device *dev);

#पूर्ण_अगर
