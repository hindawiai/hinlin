<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MDP4_KMS_H__
#घोषणा __MDP4_KMS_H__

#समावेश <drm/drm_panel.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "disp/mdp_kms.h"
#समावेश "mdp4.xml.h"

काष्ठा device_node;

काष्ठा mdp4_kms अणु
	काष्ठा mdp_kms base;

	काष्ठा drm_device *dev;

	पूर्णांक rev;

	व्योम __iomem *mmio;

	काष्ठा regulator *vdd;

	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	काष्ठा clk *lut_clk;
	काष्ठा clk *axi_clk;

	काष्ठा mdp_irq error_handler;

	bool rpm_enabled;

	/* empty/blank cursor bo to use when cursor is "disabled" */
	काष्ठा drm_gem_object *blank_cursor_bo;
	uपूर्णांक64_t blank_cursor_iova;
पूर्ण;
#घोषणा to_mdp4_kms(x) container_of(x, काष्ठा mdp4_kms, base)

/* platक्रमm config data (ie. from DT, or pdata) */
काष्ठा mdp4_platक्रमm_config अणु
	काष्ठा iommu_करोमुख्य *iommu;
	uपूर्णांक32_t max_clk;
पूर्ण;

अटल अंतरभूत व्योम mdp4_ग_लिखो(काष्ठा mdp4_kms *mdp4_kms, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, mdp4_kms->mmio + reg);
पूर्ण

अटल अंतरभूत u32 mdp4_पढ़ो(काष्ठा mdp4_kms *mdp4_kms, u32 reg)
अणु
	वापस msm_पढ़ोl(mdp4_kms->mmio + reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t pipe2flush(क्रमागत mdp4_pipe pipe)
अणु
	चयन (pipe) अणु
	हाल VG1:      वापस MDP4_OVERLAY_FLUSH_VG1;
	हाल VG2:      वापस MDP4_OVERLAY_FLUSH_VG2;
	हाल RGB1:     वापस MDP4_OVERLAY_FLUSH_RGB1;
	हाल RGB2:     वापस MDP4_OVERLAY_FLUSH_RGB2;
	शेष:       वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t ovlp2flush(पूर्णांक ovlp)
अणु
	चयन (ovlp) अणु
	हाल 0:        वापस MDP4_OVERLAY_FLUSH_OVLP0;
	हाल 1:        वापस MDP4_OVERLAY_FLUSH_OVLP1;
	शेष:       वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t dma2irq(क्रमागत mdp4_dma dma)
अणु
	चयन (dma) अणु
	हाल DMA_P:    वापस MDP4_IRQ_DMA_P_DONE;
	हाल DMA_S:    वापस MDP4_IRQ_DMA_S_DONE;
	हाल DMA_E:    वापस MDP4_IRQ_DMA_E_DONE;
	शेष:       वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t dma2err(क्रमागत mdp4_dma dma)
अणु
	चयन (dma) अणु
	हाल DMA_P:    वापस MDP4_IRQ_PRIMARY_INTF_UDERRUN;
	हाल DMA_S:    वापस 0;  // ???
	हाल DMA_E:    वापस MDP4_IRQ_EXTERNAL_INTF_UDERRUN;
	शेष:       वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t mixercfg(uपूर्णांक32_t mixer_cfg, पूर्णांक mixer,
		क्रमागत mdp4_pipe pipe, क्रमागत mdp_mixer_stage_id stage)
अणु
	चयन (pipe) अणु
	हाल VG1:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE0__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE0_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE0(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE0_MIXER1);
		अवरोध;
	हाल VG2:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE1__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE1_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE1(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE1_MIXER1);
		अवरोध;
	हाल RGB1:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE2__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE2_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE2(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE2_MIXER1);
		अवरोध;
	हाल RGB2:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE3__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE3_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE3(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE3_MIXER1);
		अवरोध;
	हाल RGB3:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE4__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE4_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE4(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE4_MIXER1);
		अवरोध;
	हाल VG3:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE5__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE5_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE5(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE5_MIXER1);
		अवरोध;
	हाल VG4:
		mixer_cfg &= ~(MDP4_LAYERMIXER_IN_CFG_PIPE6__MASK |
				MDP4_LAYERMIXER_IN_CFG_PIPE6_MIXER1);
		mixer_cfg |= MDP4_LAYERMIXER_IN_CFG_PIPE6(stage) |
			COND(mixer == 1, MDP4_LAYERMIXER_IN_CFG_PIPE6_MIXER1);
		अवरोध;
	शेष:
		WARN(1, "invalid pipe");
		अवरोध;
	पूर्ण

	वापस mixer_cfg;
पूर्ण

पूर्णांक mdp4_disable(काष्ठा mdp4_kms *mdp4_kms);
पूर्णांक mdp4_enable(काष्ठा mdp4_kms *mdp4_kms);

व्योम mdp4_set_irqmask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask,
		uपूर्णांक32_t old_irqmask);
व्योम mdp4_irq_preinstall(काष्ठा msm_kms *kms);
पूर्णांक mdp4_irq_postinstall(काष्ठा msm_kms *kms);
व्योम mdp4_irq_uninstall(काष्ठा msm_kms *kms);
irqवापस_t mdp4_irq(काष्ठा msm_kms *kms);
पूर्णांक mdp4_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);
व्योम mdp4_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);

अटल अंतरभूत uपूर्णांक32_t mdp4_pipe_caps(क्रमागत mdp4_pipe pipe)
अणु
	चयन (pipe) अणु
	हाल VG1:
	हाल VG2:
	हाल VG3:
	हाल VG4:
		वापस MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC;
	हाल RGB1:
	हाल RGB2:
	हाल RGB3:
		वापस MDP_PIPE_CAP_SCALE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

क्रमागत mdp4_pipe mdp4_plane_pipe(काष्ठा drm_plane *plane);
काष्ठा drm_plane *mdp4_plane_init(काष्ठा drm_device *dev,
		क्रमागत mdp4_pipe pipe_id, bool निजी_plane);

uपूर्णांक32_t mdp4_crtc_vblank(काष्ठा drm_crtc *crtc);
व्योम mdp4_crtc_set_config(काष्ठा drm_crtc *crtc, uपूर्णांक32_t config);
व्योम mdp4_crtc_set_पूर्णांकf(काष्ठा drm_crtc *crtc, क्रमागत mdp4_पूर्णांकf पूर्णांकf, पूर्णांक mixer);
व्योम mdp4_crtc_रुको_क्रम_commit_करोne(काष्ठा drm_crtc *crtc);
काष्ठा drm_crtc *mdp4_crtc_init(काष्ठा drm_device *dev,
		काष्ठा drm_plane *plane, पूर्णांक id, पूर्णांक ovlp_id,
		क्रमागत mdp4_dma dma_id);

दीर्घ mdp4_dtv_round_pixclk(काष्ठा drm_encoder *encoder, अचिन्हित दीर्घ rate);
काष्ठा drm_encoder *mdp4_dtv_encoder_init(काष्ठा drm_device *dev);

दीर्घ mdp4_lcdc_round_pixclk(काष्ठा drm_encoder *encoder, अचिन्हित दीर्घ rate);
काष्ठा drm_encoder *mdp4_lcdc_encoder_init(काष्ठा drm_device *dev,
		काष्ठा device_node *panel_node);

काष्ठा drm_connector *mdp4_lvds_connector_init(काष्ठा drm_device *dev,
		काष्ठा device_node *panel_node, काष्ठा drm_encoder *encoder);

#अगर_घोषित CONFIG_DRM_MSM_DSI
काष्ठा drm_encoder *mdp4_dsi_encoder_init(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा drm_encoder *mdp4_dsi_encoder_init(काष्ठा drm_device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMMON_CLK
काष्ठा clk *mpd4_lvds_pll_init(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा clk *mpd4_lvds_pll_init(काष्ठा drm_device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MDP4_KMS_H__ */
