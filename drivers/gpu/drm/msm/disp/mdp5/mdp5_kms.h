<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MDP5_KMS_H__
#घोषणा __MDP5_KMS_H__

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "disp/mdp_kms.h"
#समावेश "mdp5_cfg.h"	/* must be included beक्रमe mdp5.xml.h */
#समावेश "mdp5.xml.h"
#समावेश "mdp5_pipe.h"
#समावेश "mdp5_mixer.h"
#समावेश "mdp5_ctl.h"
#समावेश "mdp5_smp.h"

काष्ठा mdp5_kms अणु
	काष्ठा mdp_kms base;

	काष्ठा drm_device *dev;

	काष्ठा platक्रमm_device *pdev;

	अचिन्हित num_hwpipes;
	काष्ठा mdp5_hw_pipe *hwpipes[SSPP_MAX];

	अचिन्हित num_hwmixers;
	काष्ठा mdp5_hw_mixer *hwmixers[8];

	अचिन्हित num_पूर्णांकfs;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकfs[5];

	काष्ठा mdp5_cfg_handler *cfg;
	uपूर्णांक32_t caps;	/* MDP capabilities (MDP_CAP_XXX bits) */

	/*
	 * Global निजी object state, Do not access directly, use
	 * mdp5_global_get_state()
	 */
	काष्ठा drm_modeset_lock glob_state_lock;
	काष्ठा drm_निजी_obj glob_state;

	काष्ठा mdp5_smp *smp;
	काष्ठा mdp5_ctl_manager *ctlm;

	/* io/रेजिस्टर spaces: */
	व्योम __iomem *mmio;

	काष्ठा clk *axi_clk;
	काष्ठा clk *ahb_clk;
	काष्ठा clk *core_clk;
	काष्ठा clk *lut_clk;
	काष्ठा clk *tbu_clk;
	काष्ठा clk *tbu_rt_clk;
	काष्ठा clk *vsync_clk;

	/*
	 * lock to protect access to global resources: ie., following रेजिस्टर:
	 *	- REG_MDP5_DISP_INTF_SEL
	 */
	spinlock_t resource_lock;

	bool rpm_enabled;

	काष्ठा mdp_irq error_handler;

	पूर्णांक enable_count;
पूर्ण;
#घोषणा to_mdp5_kms(x) container_of(x, काष्ठा mdp5_kms, base)

/* Global निजी object state क्रम tracking resources that are shared across
 * multiple kms objects (planes/crtcs/etc).
 */
#घोषणा to_mdp5_global_state(x) container_of(x, काष्ठा mdp5_global_state, base)
काष्ठा mdp5_global_state अणु
	काष्ठा drm_निजी_state base;

	काष्ठा drm_atomic_state *state;
	काष्ठा mdp5_kms *mdp5_kms;

	काष्ठा mdp5_hw_pipe_state hwpipe;
	काष्ठा mdp5_hw_mixer_state hwmixer;
	काष्ठा mdp5_smp_state smp;
पूर्ण;

काष्ठा mdp5_global_state * mdp5_get_existing_global_state(काष्ठा mdp5_kms *mdp5_kms);
काष्ठा mdp5_global_state *__must_check mdp5_get_global_state(काष्ठा drm_atomic_state *s);

/* Atomic plane state.  Subclasses the base drm_plane_state in order to
 * track asचिन्हित hwpipe and hw specअगरic state.
 */
काष्ठा mdp5_plane_state अणु
	काष्ठा drm_plane_state base;

	काष्ठा mdp5_hw_pipe *hwpipe;
	काष्ठा mdp5_hw_pipe *r_hwpipe;	/* right hwpipe */

	/* aligned with property */
	uपूर्णांक8_t premultiplied;
	uपूर्णांक8_t zpos;
	uपूर्णांक8_t alpha;

	/* asचिन्हित by crtc blender */
	क्रमागत mdp_mixer_stage_id stage;
पूर्ण;
#घोषणा to_mdp5_plane_state(x) \
		container_of(x, काष्ठा mdp5_plane_state, base)

काष्ठा mdp5_pipeline अणु
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf;
	काष्ठा mdp5_hw_mixer *mixer;
	काष्ठा mdp5_hw_mixer *r_mixer;	/* right mixer */
पूर्ण;

काष्ठा mdp5_crtc_state अणु
	काष्ठा drm_crtc_state base;

	काष्ठा mdp5_ctl *ctl;
	काष्ठा mdp5_pipeline pipeline;

	/* these are derivatives of पूर्णांकf/mixer state in mdp5_pipeline */
	u32 vblank_irqmask;
	u32 err_irqmask;
	u32 pp_करोne_irqmask;

	bool cmd_mode;

	/* should we not ग_लिखो CTL[n].START रेजिस्टर on flush?  If the
	 * encoder has changed this is set to true, since encoder->enable()
	 * is called after crtc state is committed, but we only want to
	 * ग_लिखो the CTL[n].START रेजिस्टर once.  This lets us defer
	 * writing CTL[n].START until encoder->enable()
	 */
	bool defer_start;
पूर्ण;
#घोषणा to_mdp5_crtc_state(x) \
		container_of(x, काष्ठा mdp5_crtc_state, base)

क्रमागत mdp5_पूर्णांकf_mode अणु
	MDP5_INTF_MODE_NONE = 0,

	/* Modes used क्रम DSI पूर्णांकerface (INTF_DSI type): */
	MDP5_INTF_DSI_MODE_VIDEO,
	MDP5_INTF_DSI_MODE_COMMAND,

	/* Modes used क्रम WB पूर्णांकerface (INTF_WB type):  */
	MDP5_INTF_WB_MODE_BLOCK,
	MDP5_INTF_WB_MODE_LINE,
पूर्ण;

काष्ठा mdp5_पूर्णांकerface अणु
	पूर्णांक idx;
	पूर्णांक num; /* display पूर्णांकerface number */
	क्रमागत mdp5_पूर्णांकf_type type;
	क्रमागत mdp5_पूर्णांकf_mode mode;
पूर्ण;

काष्ठा mdp5_encoder अणु
	काष्ठा drm_encoder base;
	spinlock_t पूर्णांकf_lock;	/* protect REG_MDP5_INTF_* रेजिस्टरs */
	bool enabled;
	uपूर्णांक32_t bsc;

	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf;
	काष्ठा mdp5_ctl *ctl;
पूर्ण;
#घोषणा to_mdp5_encoder(x) container_of(x, काष्ठा mdp5_encoder, base)

अटल अंतरभूत व्योम mdp5_ग_लिखो(काष्ठा mdp5_kms *mdp5_kms, u32 reg, u32 data)
अणु
	WARN_ON(mdp5_kms->enable_count <= 0);
	msm_ग_लिखोl(data, mdp5_kms->mmio + reg);
पूर्ण

अटल अंतरभूत u32 mdp5_पढ़ो(काष्ठा mdp5_kms *mdp5_kms, u32 reg)
अणु
	WARN_ON(mdp5_kms->enable_count <= 0);
	वापस msm_पढ़ोl(mdp5_kms->mmio + reg);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *stage2name(क्रमागत mdp_mixer_stage_id stage)
अणु
	अटल स्थिर अक्षर *names[] = अणु
#घोषणा NAME(n) [n] = #n
		NAME(STAGE_UNUSED), NAME(STAGE_BASE),
		NAME(STAGE0), NAME(STAGE1), NAME(STAGE2),
		NAME(STAGE3), NAME(STAGE4), NAME(STAGE6),
#अघोषित NAME
	पूर्ण;
	वापस names[stage];
पूर्ण

अटल अंतरभूत स्थिर अक्षर *pipe2name(क्रमागत mdp5_pipe pipe)
अणु
	अटल स्थिर अक्षर *names[] = अणु
#घोषणा NAME(n) [SSPP_ ## n] = #n
		NAME(VIG0), NAME(VIG1), NAME(VIG2),
		NAME(RGB0), NAME(RGB1), NAME(RGB2),
		NAME(DMA0), NAME(DMA1),
		NAME(VIG3), NAME(RGB3),
		NAME(CURSOR0), NAME(CURSOR1),
#अघोषित NAME
	पूर्ण;
	वापस names[pipe];
पूर्ण

अटल अंतरभूत पूर्णांक pipe2nclients(क्रमागत mdp5_pipe pipe)
अणु
	चयन (pipe) अणु
	हाल SSPP_RGB0:
	हाल SSPP_RGB1:
	हाल SSPP_RGB2:
	हाल SSPP_RGB3:
		वापस 1;
	शेष:
		वापस 3;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पूर्णांकf2err(पूर्णांक पूर्णांकf_num)
अणु
	चयन (पूर्णांकf_num) अणु
	हाल 0:  वापस MDP5_IRQ_INTF0_UNDER_RUN;
	हाल 1:  वापस MDP5_IRQ_INTF1_UNDER_RUN;
	हाल 2:  वापस MDP5_IRQ_INTF2_UNDER_RUN;
	हाल 3:  वापस MDP5_IRQ_INTF3_UNDER_RUN;
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पूर्णांकf2vblank(काष्ठा mdp5_hw_mixer *mixer,
				   काष्ठा mdp5_पूर्णांकerface *पूर्णांकf)
अणु
	/*
	 * In हाल of DSI Command Mode, the Ping Pong's पढ़ो poपूर्णांकer IRQ
	 * acts as a Vblank संकेत. The Ping Pong buffer used is bound to
	 * layer mixer.
	 */

	अगर ((पूर्णांकf->type == INTF_DSI) &&
			(पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND))
		वापस MDP5_IRQ_PING_PONG_0_RD_PTR << mixer->pp;

	अगर (पूर्णांकf->type == INTF_WB)
		वापस MDP5_IRQ_WB_2_DONE;

	चयन (पूर्णांकf->num) अणु
	हाल 0:  वापस MDP5_IRQ_INTF0_VSYNC;
	हाल 1:  वापस MDP5_IRQ_INTF1_VSYNC;
	हाल 2:  वापस MDP5_IRQ_INTF2_VSYNC;
	हाल 3:  वापस MDP5_IRQ_INTF3_VSYNC;
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत uपूर्णांक32_t lm2ppकरोne(काष्ठा mdp5_hw_mixer *mixer)
अणु
	वापस MDP5_IRQ_PING_PONG_0_DONE << mixer->pp;
पूर्ण

व्योम mdp5_set_irqmask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask,
		uपूर्णांक32_t old_irqmask);
व्योम mdp5_irq_preinstall(काष्ठा msm_kms *kms);
पूर्णांक mdp5_irq_postinstall(काष्ठा msm_kms *kms);
व्योम mdp5_irq_uninstall(काष्ठा msm_kms *kms);
irqवापस_t mdp5_irq(काष्ठा msm_kms *kms);
पूर्णांक mdp5_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);
व्योम mdp5_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);
पूर्णांक mdp5_irq_करोमुख्य_init(काष्ठा mdp5_kms *mdp5_kms);
व्योम mdp5_irq_करोमुख्य_fini(काष्ठा mdp5_kms *mdp5_kms);

uपूर्णांक32_t mdp5_plane_get_flush(काष्ठा drm_plane *plane);
क्रमागत mdp5_pipe mdp5_plane_pipe(काष्ठा drm_plane *plane);
क्रमागत mdp5_pipe mdp5_plane_right_pipe(काष्ठा drm_plane *plane);
काष्ठा drm_plane *mdp5_plane_init(काष्ठा drm_device *dev,
				  क्रमागत drm_plane_type type);

काष्ठा mdp5_ctl *mdp5_crtc_get_ctl(काष्ठा drm_crtc *crtc);
uपूर्णांक32_t mdp5_crtc_vblank(काष्ठा drm_crtc *crtc);

काष्ठा mdp5_hw_mixer *mdp5_crtc_get_mixer(काष्ठा drm_crtc *crtc);
काष्ठा mdp5_pipeline *mdp5_crtc_get_pipeline(काष्ठा drm_crtc *crtc);
व्योम mdp5_crtc_set_pipeline(काष्ठा drm_crtc *crtc);
व्योम mdp5_crtc_रुको_क्रम_commit_करोne(काष्ठा drm_crtc *crtc);
काष्ठा drm_crtc *mdp5_crtc_init(काष्ठा drm_device *dev,
				काष्ठा drm_plane *plane,
				काष्ठा drm_plane *cursor_plane, पूर्णांक id);

काष्ठा drm_encoder *mdp5_encoder_init(काष्ठा drm_device *dev,
		काष्ठा mdp5_पूर्णांकerface *पूर्णांकf, काष्ठा mdp5_ctl *ctl);
पूर्णांक mdp5_vid_encoder_set_split_display(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_encoder *slave_encoder);
व्योम mdp5_encoder_set_पूर्णांकf_mode(काष्ठा drm_encoder *encoder, bool cmd_mode);
पूर्णांक mdp5_encoder_get_linecount(काष्ठा drm_encoder *encoder);
u32 mdp5_encoder_get_framecount(काष्ठा drm_encoder *encoder);

#अगर_घोषित CONFIG_DRM_MSM_DSI
व्योम mdp5_cmd_encoder_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode);
व्योम mdp5_cmd_encoder_disable(काष्ठा drm_encoder *encoder);
व्योम mdp5_cmd_encoder_enable(काष्ठा drm_encoder *encoder);
पूर्णांक mdp5_cmd_encoder_set_split_display(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_encoder *slave_encoder);
#अन्यथा
अटल अंतरभूत व्योम mdp5_cmd_encoder_mode_set(काष्ठा drm_encoder *encoder,
					     काष्ठा drm_display_mode *mode,
					     काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण
अटल अंतरभूत व्योम mdp5_cmd_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण
अटल अंतरभूत व्योम mdp5_cmd_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक mdp5_cmd_encoder_set_split_display(
	काष्ठा drm_encoder *encoder, काष्ठा drm_encoder *slave_encoder)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MDP5_KMS_H__ */
