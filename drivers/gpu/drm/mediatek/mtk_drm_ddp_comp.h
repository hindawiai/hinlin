<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित MTK_DRM_DDP_COMP_H
#घोषणा MTK_DRM_DDP_COMP_H

#समावेश <linux/पन.स>
#समावेश <linux/soc/mediatek/mtk-cmdq.h>
#समावेश <linux/soc/mediatek/mtk-mmsys.h>

काष्ठा device;
काष्ठा device_node;
काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा mtk_plane_state;
काष्ठा drm_crtc_state;

क्रमागत mtk_ddp_comp_type अणु
	MTK_DISP_OVL,
	MTK_DISP_OVL_2L,
	MTK_DISP_RDMA,
	MTK_DISP_WDMA,
	MTK_DISP_COLOR,
	MTK_DISP_CCORR,
	MTK_DISP_DITHER,
	MTK_DISP_AAL,
	MTK_DISP_GAMMA,
	MTK_DISP_UFOE,
	MTK_DSI,
	MTK_DPI,
	MTK_DISP_PWM,
	MTK_DISP_MUTEX,
	MTK_DISP_OD,
	MTK_DISP_BLS,
	MTK_DDP_COMP_TYPE_MAX,
पूर्ण;

काष्ठा mtk_ddp_comp;
काष्ठा cmdq_pkt;
काष्ठा mtk_ddp_comp_funcs अणु
	पूर्णांक (*clk_enable)(काष्ठा device *dev);
	व्योम (*clk_disable)(काष्ठा device *dev);
	व्योम (*config)(काष्ठा device *dev, अचिन्हित पूर्णांक w,
		       अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक vrefresh,
		       अचिन्हित पूर्णांक bpc, काष्ठा cmdq_pkt *cmdq_pkt);
	व्योम (*start)(काष्ठा device *dev);
	व्योम (*stop)(काष्ठा device *dev);
	व्योम (*enable_vblank)(काष्ठा device *dev,
			      व्योम (*vblank_cb)(व्योम *),
			      व्योम *vblank_cb_data);
	व्योम (*disable_vblank)(काष्ठा device *dev);
	अचिन्हित पूर्णांक (*supported_rotations)(काष्ठा device *dev);
	अचिन्हित पूर्णांक (*layer_nr)(काष्ठा device *dev);
	पूर्णांक (*layer_check)(काष्ठा device *dev,
			   अचिन्हित पूर्णांक idx,
			   काष्ठा mtk_plane_state *state);
	व्योम (*layer_config)(काष्ठा device *dev, अचिन्हित पूर्णांक idx,
			     काष्ठा mtk_plane_state *state,
			     काष्ठा cmdq_pkt *cmdq_pkt);
	व्योम (*gamma_set)(काष्ठा device *dev,
			  काष्ठा drm_crtc_state *state);
	व्योम (*bgclr_in_on)(काष्ठा device *dev);
	व्योम (*bgclr_in_off)(काष्ठा device *dev);
	व्योम (*cपंचांग_set)(काष्ठा device *dev,
			काष्ठा drm_crtc_state *state);
पूर्ण;

काष्ठा mtk_ddp_comp अणु
	काष्ठा device *dev;
	पूर्णांक irq;
	काष्ठा device *larb_dev;
	क्रमागत mtk_ddp_comp_id id;
	स्थिर काष्ठा mtk_ddp_comp_funcs *funcs;
पूर्ण;

अटल अंतरभूत पूर्णांक mtk_ddp_comp_clk_enable(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->clk_enable)
		वापस comp->funcs->clk_enable(comp->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_clk_disable(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->clk_disable)
		comp->funcs->clk_disable(comp->dev);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_config(काष्ठा mtk_ddp_comp *comp,
				       अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h,
				       अचिन्हित पूर्णांक vrefresh, अचिन्हित पूर्णांक bpc,
				       काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	अगर (comp->funcs && comp->funcs->config)
		comp->funcs->config(comp->dev, w, h, vrefresh, bpc, cmdq_pkt);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_start(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->start)
		comp->funcs->start(comp->dev);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_stop(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->stop)
		comp->funcs->stop(comp->dev);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_enable_vblank(काष्ठा mtk_ddp_comp *comp,
					      व्योम (*vblank_cb)(व्योम *),
					      व्योम *vblank_cb_data)
अणु
	अगर (comp->funcs && comp->funcs->enable_vblank)
		comp->funcs->enable_vblank(comp->dev, vblank_cb, vblank_cb_data);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_disable_vblank(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->disable_vblank)
		comp->funcs->disable_vblank(comp->dev);
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक mtk_ddp_comp_supported_rotations(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->supported_rotations)
		वापस comp->funcs->supported_rotations(comp->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mtk_ddp_comp_layer_nr(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->layer_nr)
		वापस comp->funcs->layer_nr(comp->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_ddp_comp_layer_check(काष्ठा mtk_ddp_comp *comp,
					   अचिन्हित पूर्णांक idx,
					   काष्ठा mtk_plane_state *state)
अणु
	अगर (comp->funcs && comp->funcs->layer_check)
		वापस comp->funcs->layer_check(comp->dev, idx, state);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_layer_config(काष्ठा mtk_ddp_comp *comp,
					     अचिन्हित पूर्णांक idx,
					     काष्ठा mtk_plane_state *state,
					     काष्ठा cmdq_pkt *cmdq_pkt)
अणु
	अगर (comp->funcs && comp->funcs->layer_config)
		comp->funcs->layer_config(comp->dev, idx, state, cmdq_pkt);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_gamma_set(काष्ठा mtk_ddp_comp *comp,
				     काष्ठा drm_crtc_state *state)
अणु
	अगर (comp->funcs && comp->funcs->gamma_set)
		comp->funcs->gamma_set(comp->dev, state);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_bgclr_in_on(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->bgclr_in_on)
		comp->funcs->bgclr_in_on(comp->dev);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_comp_bgclr_in_off(काष्ठा mtk_ddp_comp *comp)
अणु
	अगर (comp->funcs && comp->funcs->bgclr_in_off)
		comp->funcs->bgclr_in_off(comp->dev);
पूर्ण

अटल अंतरभूत व्योम mtk_ddp_cपंचांग_set(काष्ठा mtk_ddp_comp *comp,
				   काष्ठा drm_crtc_state *state)
अणु
	अगर (comp->funcs && comp->funcs->cपंचांग_set)
		comp->funcs->cपंचांग_set(comp->dev, state);
पूर्ण

पूर्णांक mtk_ddp_comp_get_id(काष्ठा device_node *node,
			क्रमागत mtk_ddp_comp_type comp_type);
अचिन्हित पूर्णांक mtk_drm_find_possible_crtc_by_comp(काष्ठा drm_device *drm,
						काष्ठा device *dev);
पूर्णांक mtk_ddp_comp_init(काष्ठा device_node *comp_node, काष्ठा mtk_ddp_comp *comp,
		      क्रमागत mtk_ddp_comp_id comp_id);
क्रमागत mtk_ddp_comp_type mtk_ddp_comp_get_type(क्रमागत mtk_ddp_comp_id comp_id);
व्योम mtk_ddp_ग_लिखो(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
		   काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
		   अचिन्हित पूर्णांक offset);
व्योम mtk_ddp_ग_लिखो_relaxed(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
			   काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
			   अचिन्हित पूर्णांक offset);
व्योम mtk_ddp_ग_लिखो_mask(काष्ठा cmdq_pkt *cmdq_pkt, अचिन्हित पूर्णांक value,
			काष्ठा cmdq_client_reg *cmdq_reg, व्योम __iomem *regs,
			अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक mask);
#पूर्ण_अगर /* MTK_DRM_DDP_COMP_H */
