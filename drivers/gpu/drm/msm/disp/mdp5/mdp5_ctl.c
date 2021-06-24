<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
 */

#समावेश "mdp5_kms.h"
#समावेश "mdp5_ctl.h"

/*
 * CTL - MDP Control Pool Manager
 *
 * Controls are shared between all display पूर्णांकerfaces.
 *
 * They are पूर्णांकended to be used क्रम data path configuration.
 * The top level रेजिस्टर programming describes the complete data path क्रम
 * a specअगरic data path ID - REG_MDP5_CTL_*(<id>, ...)
 *
 * Hardware capabilities determine the number of concurrent data paths
 *
 * In certain use हालs (high-resolution dual pipe), one single CTL can be
 * shared across multiple CRTCs.
 */

#घोषणा CTL_STAT_BUSY		0x1
#घोषणा CTL_STAT_BOOKED	0x2

काष्ठा mdp5_ctl अणु
	काष्ठा mdp5_ctl_manager *ctlm;

	u32 id;

	/* CTL status biपंचांगask */
	u32 status;

	bool encoder_enabled;

	/* pending flush_mask bits */
	u32 flush_mask;

	/* REG_MDP5_CTL_*(<id>) रेजिस्टरs access info + lock: */
	spinlock_t hw_lock;
	u32 reg_offset;

	/* when करो CTL रेजिस्टरs need to be flushed? (mask of trigger bits) */
	u32 pending_ctl_trigger;

	bool cursor_on;

	/* True अगर the current CTL has FLUSH bits pending क्रम single FLUSH. */
	bool flush_pending;

	काष्ठा mdp5_ctl *pair; /* Paired CTL to be flushed together */
पूर्ण;

काष्ठा mdp5_ctl_manager अणु
	काष्ठा drm_device *dev;

	/* number of CTL / Layer Mixers in this hw config: */
	u32 nlm;
	u32 nctl;

	/* to filter out non-present bits in the current hardware config */
	u32 flush_hw_mask;

	/* status क्रम single FLUSH */
	bool single_flush_supported;
	u32 single_flush_pending_mask;

	/* pool of CTLs + lock to protect resource allocation (ctls[i].busy) */
	spinlock_t pool_lock;
	काष्ठा mdp5_ctl ctls[MAX_CTL];
पूर्ण;

अटल अंतरभूत
काष्ठा mdp5_kms *get_kms(काष्ठा mdp5_ctl_manager *ctl_mgr)
अणु
	काष्ठा msm_drm_निजी *priv = ctl_mgr->dev->dev_निजी;

	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल अंतरभूत
व्योम ctl_ग_लिखो(काष्ठा mdp5_ctl *ctl, u32 reg, u32 data)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(ctl->ctlm);

	(व्योम)ctl->reg_offset; /* TODO use this instead of mdp5_ग_लिखो */
	mdp5_ग_लिखो(mdp5_kms, reg, data);
पूर्ण

अटल अंतरभूत
u32 ctl_पढ़ो(काष्ठा mdp5_ctl *ctl, u32 reg)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(ctl->ctlm);

	(व्योम)ctl->reg_offset; /* TODO use this instead of mdp5_ग_लिखो */
	वापस mdp5_पढ़ो(mdp5_kms, reg);
पूर्ण

अटल व्योम set_display_पूर्णांकf(काष्ठा mdp5_kms *mdp5_kms,
		काष्ठा mdp5_पूर्णांकerface *पूर्णांकf)
अणु
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकf_sel;

	spin_lock_irqsave(&mdp5_kms->resource_lock, flags);
	पूर्णांकf_sel = mdp5_पढ़ो(mdp5_kms, REG_MDP5_DISP_INTF_SEL);

	चयन (पूर्णांकf->num) अणु
	हाल 0:
		पूर्णांकf_sel &= ~MDP5_DISP_INTF_SEL_INTF0__MASK;
		पूर्णांकf_sel |= MDP5_DISP_INTF_SEL_INTF0(पूर्णांकf->type);
		अवरोध;
	हाल 1:
		पूर्णांकf_sel &= ~MDP5_DISP_INTF_SEL_INTF1__MASK;
		पूर्णांकf_sel |= MDP5_DISP_INTF_SEL_INTF1(पूर्णांकf->type);
		अवरोध;
	हाल 2:
		पूर्णांकf_sel &= ~MDP5_DISP_INTF_SEL_INTF2__MASK;
		पूर्णांकf_sel |= MDP5_DISP_INTF_SEL_INTF2(पूर्णांकf->type);
		अवरोध;
	हाल 3:
		पूर्णांकf_sel &= ~MDP5_DISP_INTF_SEL_INTF3__MASK;
		पूर्णांकf_sel |= MDP5_DISP_INTF_SEL_INTF3(पूर्णांकf->type);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_DISP_INTF_SEL, पूर्णांकf_sel);
	spin_unlock_irqrestore(&mdp5_kms->resource_lock, flags);
पूर्ण

अटल व्योम set_ctl_op(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = pipeline->पूर्णांकf;
	u32 ctl_op = 0;

	अगर (!mdp5_cfg_पूर्णांकf_is_भव(पूर्णांकf->type))
		ctl_op |= MDP5_CTL_OP_INTF_NUM(INTF0 + पूर्णांकf->num);

	चयन (पूर्णांकf->type) अणु
	हाल INTF_DSI:
		अगर (पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND)
			ctl_op |= MDP5_CTL_OP_CMD_MODE;
		अवरोध;

	हाल INTF_WB:
		अगर (पूर्णांकf->mode == MDP5_INTF_WB_MODE_LINE)
			ctl_op |= MDP5_CTL_OP_MODE(MODE_WB_2_LINE);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (pipeline->r_mixer)
		ctl_op |= MDP5_CTL_OP_PACK_3D_ENABLE |
			  MDP5_CTL_OP_PACK_3D(1);

	spin_lock_irqsave(&ctl->hw_lock, flags);
	ctl_ग_लिखो(ctl, REG_MDP5_CTL_OP(ctl->id), ctl_op);
	spin_unlock_irqrestore(&ctl->hw_lock, flags);
पूर्ण

पूर्णांक mdp5_ctl_set_pipeline(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(ctl->ctlm);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = pipeline->पूर्णांकf;

	/* Virtual पूर्णांकerfaces need not set a display पूर्णांकf (e.g.: Writeback) */
	अगर (!mdp5_cfg_पूर्णांकf_is_भव(पूर्णांकf->type))
		set_display_पूर्णांकf(mdp5_kms, पूर्णांकf);

	set_ctl_op(ctl, pipeline);

	वापस 0;
पूर्ण

अटल bool start_संकेत_needed(काष्ठा mdp5_ctl *ctl,
				काष्ठा mdp5_pipeline *pipeline)
अणु
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = pipeline->पूर्णांकf;

	अगर (!ctl->encoder_enabled)
		वापस false;

	चयन (पूर्णांकf->type) अणु
	हाल INTF_WB:
		वापस true;
	हाल INTF_DSI:
		वापस पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * send_start_संकेत() - Overlay Processor Start Signal
 *
 * For a given control operation (display pipeline), a START संकेत needs to be
 * executed in order to kick off operation and activate all layers.
 * e.g.: DSI command mode, Writeback
 */
अटल व्योम send_start_संकेत(काष्ठा mdp5_ctl *ctl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctl->hw_lock, flags);
	ctl_ग_लिखो(ctl, REG_MDP5_CTL_START(ctl->id), 1);
	spin_unlock_irqrestore(&ctl->hw_lock, flags);
पूर्ण

/**
 * mdp5_ctl_set_encoder_state() - set the encoder state
 *
 * @ctl:      the CTL instance
 * @pipeline: the encoder's INTF + MIXER configuration
 * @enabled:  true, when encoder is पढ़ोy क्रम data streaming; false, otherwise.
 *
 * Note:
 * This encoder state is needed to trigger START संकेत (data path kickoff).
 */
पूर्णांक mdp5_ctl_set_encoder_state(काष्ठा mdp5_ctl *ctl,
			       काष्ठा mdp5_pipeline *pipeline,
			       bool enabled)
अणु
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = pipeline->पूर्णांकf;

	अगर (WARN_ON(!ctl))
		वापस -EINVAL;

	ctl->encoder_enabled = enabled;
	DBG("intf_%d: %s", पूर्णांकf->num, enabled ? "on" : "off");

	अगर (start_संकेत_needed(ctl, pipeline)) अणु
		send_start_संकेत(ctl);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note:
 * CTL रेजिस्टरs need to be flushed after calling this function
 * (call mdp5_ctl_commit() with mdp_ctl_flush_mask_ctl() mask)
 */
पूर्णांक mdp5_ctl_set_cursor(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
			पूर्णांक cursor_id, bool enable)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	अचिन्हित दीर्घ flags;
	u32 blend_cfg;
	काष्ठा mdp5_hw_mixer *mixer = pipeline->mixer;

	अगर (WARN_ON(!mixer)) अणु
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "CTL %d cannot find LM",
			ctl->id);
		वापस -EINVAL;
	पूर्ण

	अगर (pipeline->r_mixer) अणु
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "unsupported configuration");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&ctl->hw_lock, flags);

	blend_cfg = ctl_पढ़ो(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, mixer->lm));

	अगर (enable)
		blend_cfg |=  MDP5_CTL_LAYER_REG_CURSOR_OUT;
	अन्यथा
		blend_cfg &= ~MDP5_CTL_LAYER_REG_CURSOR_OUT;

	ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, mixer->lm), blend_cfg);
	ctl->cursor_on = enable;

	spin_unlock_irqrestore(&ctl->hw_lock, flags);

	ctl->pending_ctl_trigger = mdp_ctl_flush_mask_cursor(cursor_id);

	वापस 0;
पूर्ण

अटल u32 mdp_ctl_blend_mask(क्रमागत mdp5_pipe pipe,
		क्रमागत mdp_mixer_stage_id stage)
अणु
	चयन (pipe) अणु
	हाल SSPP_VIG0: वापस MDP5_CTL_LAYER_REG_VIG0(stage);
	हाल SSPP_VIG1: वापस MDP5_CTL_LAYER_REG_VIG1(stage);
	हाल SSPP_VIG2: वापस MDP5_CTL_LAYER_REG_VIG2(stage);
	हाल SSPP_RGB0: वापस MDP5_CTL_LAYER_REG_RGB0(stage);
	हाल SSPP_RGB1: वापस MDP5_CTL_LAYER_REG_RGB1(stage);
	हाल SSPP_RGB2: वापस MDP5_CTL_LAYER_REG_RGB2(stage);
	हाल SSPP_DMA0: वापस MDP5_CTL_LAYER_REG_DMA0(stage);
	हाल SSPP_DMA1: वापस MDP5_CTL_LAYER_REG_DMA1(stage);
	हाल SSPP_VIG3: वापस MDP5_CTL_LAYER_REG_VIG3(stage);
	हाल SSPP_RGB3: वापस MDP5_CTL_LAYER_REG_RGB3(stage);
	हाल SSPP_CURSOR0:
	हाल SSPP_CURSOR1:
	शेष:	वापस 0;
	पूर्ण
पूर्ण

अटल u32 mdp_ctl_blend_ext_mask(क्रमागत mdp5_pipe pipe,
		क्रमागत mdp_mixer_stage_id stage)
अणु
	अगर (stage < STAGE6 && (pipe != SSPP_CURSOR0 && pipe != SSPP_CURSOR1))
		वापस 0;

	चयन (pipe) अणु
	हाल SSPP_VIG0: वापस MDP5_CTL_LAYER_EXT_REG_VIG0_BIT3;
	हाल SSPP_VIG1: वापस MDP5_CTL_LAYER_EXT_REG_VIG1_BIT3;
	हाल SSPP_VIG2: वापस MDP5_CTL_LAYER_EXT_REG_VIG2_BIT3;
	हाल SSPP_RGB0: वापस MDP5_CTL_LAYER_EXT_REG_RGB0_BIT3;
	हाल SSPP_RGB1: वापस MDP5_CTL_LAYER_EXT_REG_RGB1_BIT3;
	हाल SSPP_RGB2: वापस MDP5_CTL_LAYER_EXT_REG_RGB2_BIT3;
	हाल SSPP_DMA0: वापस MDP5_CTL_LAYER_EXT_REG_DMA0_BIT3;
	हाल SSPP_DMA1: वापस MDP5_CTL_LAYER_EXT_REG_DMA1_BIT3;
	हाल SSPP_VIG3: वापस MDP5_CTL_LAYER_EXT_REG_VIG3_BIT3;
	हाल SSPP_RGB3: वापस MDP5_CTL_LAYER_EXT_REG_RGB3_BIT3;
	हाल SSPP_CURSOR0: वापस MDP5_CTL_LAYER_EXT_REG_CURSOR0(stage);
	हाल SSPP_CURSOR1: वापस MDP5_CTL_LAYER_EXT_REG_CURSOR1(stage);
	शेष:	वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mdp5_ctl_reset_blend_regs(काष्ठा mdp5_ctl *ctl)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	पूर्णांक i;

	spin_lock_irqsave(&ctl->hw_lock, flags);

	क्रम (i = 0; i < ctl_mgr->nlm; i++) अणु
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, i), 0x0);
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_EXT_REG(ctl->id, i), 0x0);
	पूर्ण

	spin_unlock_irqrestore(&ctl->hw_lock, flags);
पूर्ण

#घोषणा PIPE_LEFT	0
#घोषणा PIPE_RIGHT	1
पूर्णांक mdp5_ctl_blend(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
		   क्रमागत mdp5_pipe stage[][MAX_PIPE_STAGE],
		   क्रमागत mdp5_pipe r_stage[][MAX_PIPE_STAGE],
		   u32 stage_cnt, u32 ctl_blend_op_flags)
अणु
	काष्ठा mdp5_hw_mixer *mixer = pipeline->mixer;
	काष्ठा mdp5_hw_mixer *r_mixer = pipeline->r_mixer;
	अचिन्हित दीर्घ flags;
	u32 blend_cfg = 0, blend_ext_cfg = 0;
	u32 r_blend_cfg = 0, r_blend_ext_cfg = 0;
	पूर्णांक i, start_stage;

	mdp5_ctl_reset_blend_regs(ctl);

	अगर (ctl_blend_op_flags & MDP5_CTL_BLEND_OP_FLAG_BORDER_OUT) अणु
		start_stage = STAGE0;
		blend_cfg |= MDP5_CTL_LAYER_REG_BORDER_COLOR;
		अगर (r_mixer)
			r_blend_cfg |= MDP5_CTL_LAYER_REG_BORDER_COLOR;
	पूर्ण अन्यथा अणु
		start_stage = STAGE_BASE;
	पूर्ण

	क्रम (i = start_stage; stage_cnt && i <= STAGE_MAX; i++) अणु
		blend_cfg |=
			mdp_ctl_blend_mask(stage[i][PIPE_LEFT], i) |
			mdp_ctl_blend_mask(stage[i][PIPE_RIGHT], i);
		blend_ext_cfg |=
			mdp_ctl_blend_ext_mask(stage[i][PIPE_LEFT], i) |
			mdp_ctl_blend_ext_mask(stage[i][PIPE_RIGHT], i);
		अगर (r_mixer) अणु
			r_blend_cfg |=
				mdp_ctl_blend_mask(r_stage[i][PIPE_LEFT], i) |
				mdp_ctl_blend_mask(r_stage[i][PIPE_RIGHT], i);
			r_blend_ext_cfg |=
			     mdp_ctl_blend_ext_mask(r_stage[i][PIPE_LEFT], i) |
			     mdp_ctl_blend_ext_mask(r_stage[i][PIPE_RIGHT], i);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ctl->hw_lock, flags);
	अगर (ctl->cursor_on)
		blend_cfg |=  MDP5_CTL_LAYER_REG_CURSOR_OUT;

	ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, mixer->lm), blend_cfg);
	ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_EXT_REG(ctl->id, mixer->lm),
		  blend_ext_cfg);
	अगर (r_mixer) अणु
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, r_mixer->lm),
			  r_blend_cfg);
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_LAYER_EXT_REG(ctl->id, r_mixer->lm),
			  r_blend_ext_cfg);
	पूर्ण
	spin_unlock_irqrestore(&ctl->hw_lock, flags);

	ctl->pending_ctl_trigger = mdp_ctl_flush_mask_lm(mixer->lm);
	अगर (r_mixer)
		ctl->pending_ctl_trigger |= mdp_ctl_flush_mask_lm(r_mixer->lm);

	DBG("lm%d: blend config = 0x%08x. ext_cfg = 0x%08x", mixer->lm,
		blend_cfg, blend_ext_cfg);
	अगर (r_mixer)
		DBG("lm%d: blend config = 0x%08x. ext_cfg = 0x%08x",
		    r_mixer->lm, r_blend_cfg, r_blend_ext_cfg);

	वापस 0;
पूर्ण

u32 mdp_ctl_flush_mask_encoder(काष्ठा mdp5_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (पूर्णांकf->type == INTF_WB)
		वापस MDP5_CTL_FLUSH_WB;

	चयन (पूर्णांकf->num) अणु
	हाल 0: वापस MDP5_CTL_FLUSH_TIMING_0;
	हाल 1: वापस MDP5_CTL_FLUSH_TIMING_1;
	हाल 2: वापस MDP5_CTL_FLUSH_TIMING_2;
	हाल 3: वापस MDP5_CTL_FLUSH_TIMING_3;
	शेष: वापस 0;
	पूर्ण
पूर्ण

u32 mdp_ctl_flush_mask_cursor(पूर्णांक cursor_id)
अणु
	चयन (cursor_id) अणु
	हाल 0: वापस MDP5_CTL_FLUSH_CURSOR_0;
	हाल 1: वापस MDP5_CTL_FLUSH_CURSOR_1;
	शेष: वापस 0;
	पूर्ण
पूर्ण

u32 mdp_ctl_flush_mask_pipe(क्रमागत mdp5_pipe pipe)
अणु
	चयन (pipe) अणु
	हाल SSPP_VIG0: वापस MDP5_CTL_FLUSH_VIG0;
	हाल SSPP_VIG1: वापस MDP5_CTL_FLUSH_VIG1;
	हाल SSPP_VIG2: वापस MDP5_CTL_FLUSH_VIG2;
	हाल SSPP_RGB0: वापस MDP5_CTL_FLUSH_RGB0;
	हाल SSPP_RGB1: वापस MDP5_CTL_FLUSH_RGB1;
	हाल SSPP_RGB2: वापस MDP5_CTL_FLUSH_RGB2;
	हाल SSPP_DMA0: वापस MDP5_CTL_FLUSH_DMA0;
	हाल SSPP_DMA1: वापस MDP5_CTL_FLUSH_DMA1;
	हाल SSPP_VIG3: वापस MDP5_CTL_FLUSH_VIG3;
	हाल SSPP_RGB3: वापस MDP5_CTL_FLUSH_RGB3;
	हाल SSPP_CURSOR0: वापस MDP5_CTL_FLUSH_CURSOR_0;
	हाल SSPP_CURSOR1: वापस MDP5_CTL_FLUSH_CURSOR_1;
	शेष:        वापस 0;
	पूर्ण
पूर्ण

u32 mdp_ctl_flush_mask_lm(पूर्णांक lm)
अणु
	चयन (lm) अणु
	हाल 0:  वापस MDP5_CTL_FLUSH_LM0;
	हाल 1:  वापस MDP5_CTL_FLUSH_LM1;
	हाल 2:  वापस MDP5_CTL_FLUSH_LM2;
	हाल 3:  वापस MDP5_CTL_FLUSH_LM3;
	हाल 4:  वापस MDP5_CTL_FLUSH_LM4;
	हाल 5:  वापस MDP5_CTL_FLUSH_LM5;
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल u32 fix_sw_flush(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
			u32 flush_mask)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	u32 sw_mask = 0;
#घोषणा BIT_NEEDS_SW_FIX(bit) \
	(!(ctl_mgr->flush_hw_mask & bit) && (flush_mask & bit))

	/* क्रम some tarमाला_लो, cursor bit is the same as LM bit */
	अगर (BIT_NEEDS_SW_FIX(MDP5_CTL_FLUSH_CURSOR_0))
		sw_mask |= mdp_ctl_flush_mask_lm(pipeline->mixer->lm);

	वापस sw_mask;
पूर्ण

अटल व्योम fix_क्रम_single_flush(काष्ठा mdp5_ctl *ctl, u32 *flush_mask,
		u32 *flush_id)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctl->ctlm;

	अगर (ctl->pair) अणु
		DBG("CTL %d FLUSH pending mask %x", ctl->id, *flush_mask);
		ctl->flush_pending = true;
		ctl_mgr->single_flush_pending_mask |= (*flush_mask);
		*flush_mask = 0;

		अगर (ctl->pair->flush_pending) अणु
			*flush_id = min_t(u32, ctl->id, ctl->pair->id);
			*flush_mask = ctl_mgr->single_flush_pending_mask;

			ctl->flush_pending = false;
			ctl->pair->flush_pending = false;
			ctl_mgr->single_flush_pending_mask = 0;

			DBG("Single FLUSH mask %x,ID %d", *flush_mask,
				*flush_id);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mdp5_ctl_commit() - Register Flush
 *
 * @ctl:        the CTL instance
 * @pipeline:   the encoder's INTF + MIXER configuration
 * @flush_mask: biपंचांगask of display controller hw blocks to flush
 * @start:      अगर true, immediately update flush रेजिस्टरs and set START
 *              bit, otherwise accumulate flush_mask bits until we are
 *              पढ़ोy to START
 *
 * The flush रेजिस्टर is used to indicate several रेजिस्टरs are all
 * programmed, and are safe to update to the back copy of the द्विगुन
 * buffered रेजिस्टरs.
 *
 * Some रेजिस्टरs FLUSH bits are shared when the hardware करोes not have
 * dedicated bits क्रम them; handling these is the job of fix_sw_flush().
 *
 * CTL रेजिस्टरs need to be flushed in some circumstances; अगर that is the
 * हाल, some trigger bits will be present in both flush mask and
 * ctl->pending_ctl_trigger.
 *
 * Return H/W flushed bit mask.
 */
u32 mdp5_ctl_commit(काष्ठा mdp5_ctl *ctl,
		    काष्ठा mdp5_pipeline *pipeline,
		    u32 flush_mask, bool start)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	अचिन्हित दीर्घ flags;
	u32 flush_id = ctl->id;
	u32 curr_ctl_flush_mask;

	VERB("flush_mask=%x, trigger=%x", flush_mask, ctl->pending_ctl_trigger);

	अगर (ctl->pending_ctl_trigger & flush_mask) अणु
		flush_mask |= MDP5_CTL_FLUSH_CTL;
		ctl->pending_ctl_trigger = 0;
	पूर्ण

	flush_mask |= fix_sw_flush(ctl, pipeline, flush_mask);

	flush_mask &= ctl_mgr->flush_hw_mask;

	curr_ctl_flush_mask = flush_mask;

	fix_क्रम_single_flush(ctl, &flush_mask, &flush_id);

	अगर (!start) अणु
		ctl->flush_mask |= flush_mask;
		वापस curr_ctl_flush_mask;
	पूर्ण अन्यथा अणु
		flush_mask |= ctl->flush_mask;
		ctl->flush_mask = 0;
	पूर्ण

	अगर (flush_mask) अणु
		spin_lock_irqsave(&ctl->hw_lock, flags);
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_FLUSH(flush_id), flush_mask);
		spin_unlock_irqrestore(&ctl->hw_lock, flags);
	पूर्ण

	अगर (start_संकेत_needed(ctl, pipeline)) अणु
		send_start_संकेत(ctl);
	पूर्ण

	वापस curr_ctl_flush_mask;
पूर्ण

u32 mdp5_ctl_get_commit_status(काष्ठा mdp5_ctl *ctl)
अणु
	वापस ctl_पढ़ो(ctl, REG_MDP5_CTL_FLUSH(ctl->id));
पूर्ण

पूर्णांक mdp5_ctl_get_ctl_id(काष्ठा mdp5_ctl *ctl)
अणु
	वापस WARN_ON(!ctl) ? -EINVAL : ctl->id;
पूर्ण

/*
 * mdp5_ctl_pair() - Associate 2 booked CTLs क्रम single FLUSH
 */
पूर्णांक mdp5_ctl_pair(काष्ठा mdp5_ctl *ctlx, काष्ठा mdp5_ctl *ctly, bool enable)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr = ctlx->ctlm;
	काष्ठा mdp5_kms *mdp5_kms = get_kms(ctl_mgr);

	/* करो nothing silently अगर hw करोesn't support */
	अगर (!ctl_mgr->single_flush_supported)
		वापस 0;

	अगर (!enable) अणु
		ctlx->pair = शून्य;
		ctly->pair = शून्य;
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPARE_0, 0);
		वापस 0;
	पूर्ण अन्यथा अगर ((ctlx->pair != शून्य) || (ctly->pair != शून्य)) अणु
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "CTLs already paired\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!(ctlx->status & ctly->status & CTL_STAT_BOOKED)) अणु
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "Only pair booked CTLs\n");
		वापस -EINVAL;
	पूर्ण

	ctlx->pair = ctly;
	ctly->pair = ctlx;

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPARE_0,
		   MDP5_SPARE_0_SPLIT_DPL_SINGLE_FLUSH_EN);

	वापस 0;
पूर्ण

/*
 * mdp5_ctl_request() - CTL allocation
 *
 * Try to वापस booked CTL क्रम @पूर्णांकf_num is 1 or 2, unbooked क्रम other INTFs.
 * If no CTL is available in preferred category, allocate from the other one.
 *
 * @वापस fail अगर no CTL is available.
 */
काष्ठा mdp5_ctl *mdp5_ctlm_request(काष्ठा mdp5_ctl_manager *ctl_mgr,
		पूर्णांक पूर्णांकf_num)
अणु
	काष्ठा mdp5_ctl *ctl = शून्य;
	स्थिर u32 checkm = CTL_STAT_BUSY | CTL_STAT_BOOKED;
	u32 match = ((पूर्णांकf_num == 1) || (पूर्णांकf_num == 2)) ? CTL_STAT_BOOKED : 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक c;

	spin_lock_irqsave(&ctl_mgr->pool_lock, flags);

	/* search the preferred */
	क्रम (c = 0; c < ctl_mgr->nctl; c++)
		अगर ((ctl_mgr->ctls[c].status & checkm) == match)
			जाओ found;

	dev_warn(ctl_mgr->dev->dev,
		"fall back to the other CTL category for INTF %d!\n", पूर्णांकf_num);

	match ^= CTL_STAT_BOOKED;
	क्रम (c = 0; c < ctl_mgr->nctl; c++)
		अगर ((ctl_mgr->ctls[c].status & checkm) == match)
			जाओ found;

	DRM_DEV_ERROR(ctl_mgr->dev->dev, "No more CTL available!");
	जाओ unlock;

found:
	ctl = &ctl_mgr->ctls[c];
	ctl->status |= CTL_STAT_BUSY;
	ctl->pending_ctl_trigger = 0;
	DBG("CTL %d allocated", ctl->id);

unlock:
	spin_unlock_irqrestore(&ctl_mgr->pool_lock, flags);
	वापस ctl;
पूर्ण

व्योम mdp5_ctlm_hw_reset(काष्ठा mdp5_ctl_manager *ctl_mgr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c;

	क्रम (c = 0; c < ctl_mgr->nctl; c++) अणु
		काष्ठा mdp5_ctl *ctl = &ctl_mgr->ctls[c];

		spin_lock_irqsave(&ctl->hw_lock, flags);
		ctl_ग_लिखो(ctl, REG_MDP5_CTL_OP(ctl->id), 0);
		spin_unlock_irqrestore(&ctl->hw_lock, flags);
	पूर्ण
पूर्ण

व्योम mdp5_ctlm_destroy(काष्ठा mdp5_ctl_manager *ctl_mgr)
अणु
	kमुक्त(ctl_mgr);
पूर्ण

काष्ठा mdp5_ctl_manager *mdp5_ctlm_init(काष्ठा drm_device *dev,
		व्योम __iomem *mmio_base, काष्ठा mdp5_cfg_handler *cfg_hnd)
अणु
	काष्ठा mdp5_ctl_manager *ctl_mgr;
	स्थिर काष्ठा mdp5_cfg_hw *hw_cfg = mdp5_cfg_get_hw_config(cfg_hnd);
	पूर्णांक rev = mdp5_cfg_get_hw_rev(cfg_hnd);
	अचिन्हित dsi_cnt = 0;
	स्थिर काष्ठा mdp5_ctl_block *ctl_cfg = &hw_cfg->ctl;
	अचिन्हित दीर्घ flags;
	पूर्णांक c, ret;

	ctl_mgr = kzalloc(माप(*ctl_mgr), GFP_KERNEL);
	अगर (!ctl_mgr) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate CTL manager\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (WARN_ON(ctl_cfg->count > MAX_CTL)) अणु
		DRM_DEV_ERROR(dev->dev, "Increase static pool size to at least %d\n",
				ctl_cfg->count);
		ret = -ENOSPC;
		जाओ fail;
	पूर्ण

	/* initialize the CTL manager: */
	ctl_mgr->dev = dev;
	ctl_mgr->nlm = hw_cfg->lm.count;
	ctl_mgr->nctl = ctl_cfg->count;
	ctl_mgr->flush_hw_mask = ctl_cfg->flush_hw_mask;
	spin_lock_init(&ctl_mgr->pool_lock);

	/* initialize each CTL of the pool: */
	spin_lock_irqsave(&ctl_mgr->pool_lock, flags);
	क्रम (c = 0; c < ctl_mgr->nctl; c++) अणु
		काष्ठा mdp5_ctl *ctl = &ctl_mgr->ctls[c];

		अगर (WARN_ON(!ctl_cfg->base[c])) अणु
			DRM_DEV_ERROR(dev->dev, "CTL_%d: base is null!\n", c);
			ret = -EINVAL;
			spin_unlock_irqrestore(&ctl_mgr->pool_lock, flags);
			जाओ fail;
		पूर्ण
		ctl->ctlm = ctl_mgr;
		ctl->id = c;
		ctl->reg_offset = ctl_cfg->base[c];
		ctl->status = 0;
		spin_lock_init(&ctl->hw_lock);
	पूर्ण

	/*
	 * In Dual DSI हाल, CTL0 and CTL1 are always asचिन्हित to two DSI
	 * पूर्णांकerfaces to support single FLUSH feature (Flush CTL0 and CTL1 when
	 * only ग_लिखो पूर्णांकo CTL0's FLUSH रेजिस्टर) to keep two DSI pipes in sync.
	 * Single FLUSH is supported from hw rev v3.0.
	 */
	क्रम (c = 0; c < ARRAY_SIZE(hw_cfg->पूर्णांकf.connect); c++)
		अगर (hw_cfg->पूर्णांकf.connect[c] == INTF_DSI)
			dsi_cnt++;
	अगर ((rev >= 3) && (dsi_cnt > 1)) अणु
		ctl_mgr->single_flush_supported = true;
		/* Reserve CTL0/1 क्रम INTF1/2 */
		ctl_mgr->ctls[0].status |= CTL_STAT_BOOKED;
		ctl_mgr->ctls[1].status |= CTL_STAT_BOOKED;
	पूर्ण
	spin_unlock_irqrestore(&ctl_mgr->pool_lock, flags);
	DBG("Pool of %d CTLs created.", ctl_mgr->nctl);

	वापस ctl_mgr;

fail:
	अगर (ctl_mgr)
		mdp5_ctlm_destroy(ctl_mgr);

	वापस ERR_PTR(ret);
पूर्ण
