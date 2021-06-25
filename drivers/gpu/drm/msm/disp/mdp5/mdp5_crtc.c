<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/sort.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_flip_work.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mdp5_kms.h"
#समावेश "msm_gem.h"

#घोषणा CURSOR_WIDTH	64
#घोषणा CURSOR_HEIGHT	64

काष्ठा mdp5_crtc अणु
	काष्ठा drm_crtc base;
	पूर्णांक id;
	bool enabled;

	spinlock_t lm_lock;     /* protect REG_MDP5_LM_* रेजिस्टरs */

	/* अगर there is a pending flip, these will be non-null: */
	काष्ठा drm_pending_vblank_event *event;

	/* Bits have been flushed at the last commit,
	 * used to decide अगर a vsync has happened since last commit.
	 */
	u32 flushed_mask;

#घोषणा PENDING_CURSOR 0x1
#घोषणा PENDING_FLIP   0x2
	atomic_t pending;

	/* क्रम unref'ing cursor bo's after scanout completes: */
	काष्ठा drm_flip_work unref_cursor_work;

	काष्ठा mdp_irq vblank;
	काष्ठा mdp_irq err;
	काष्ठा mdp_irq pp_करोne;

	काष्ठा completion pp_completion;

	bool lm_cursor_enabled;

	काष्ठा अणु
		/* protect REG_MDP5_LM_CURSOR* रेजिस्टरs and cursor scanout_bo*/
		spinlock_t lock;

		/* current cursor being scanned out: */
		काष्ठा drm_gem_object *scanout_bo;
		uपूर्णांक64_t iova;
		uपूर्णांक32_t width, height;
		पूर्णांक x, y;
	पूर्ण cursor;
पूर्ण;
#घोषणा to_mdp5_crtc(x) container_of(x, काष्ठा mdp5_crtc, base)

अटल व्योम mdp5_crtc_restore_cursor(काष्ठा drm_crtc *crtc);

अटल काष्ठा mdp5_kms *get_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा msm_drm_निजी *priv = crtc->dev->dev_निजी;
	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम request_pending(काष्ठा drm_crtc *crtc, uपूर्णांक32_t pending)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);

	atomic_or(pending, &mdp5_crtc->pending);
	mdp_irq_रेजिस्टर(&get_kms(crtc)->base, &mdp5_crtc->vblank);
पूर्ण

अटल व्योम request_pp_करोne_pending(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	reinit_completion(&mdp5_crtc->pp_completion);
पूर्ण

अटल u32 crtc_flush(काष्ठा drm_crtc *crtc, u32 flush_mask)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_ctl *ctl = mdp5_cstate->ctl;
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	bool start = !mdp5_cstate->defer_start;

	mdp5_cstate->defer_start = false;

	DBG("%s: flush=%08x", crtc->name, flush_mask);

	वापस mdp5_ctl_commit(ctl, pipeline, flush_mask, start);
पूर्ण

/*
 * flush updates, to make sure hw is updated to new scanout fb,
 * so that we can safely queue unref to current fb (ie. next
 * vblank we know hw is करोne w/ previous scanout_fb).
 */
अटल u32 crtc_flush_all(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_hw_mixer *mixer, *r_mixer;
	काष्ठा drm_plane *plane;
	uपूर्णांक32_t flush_mask = 0;

	/* this should not happen: */
	अगर (WARN_ON(!mdp5_cstate->ctl))
		वापस 0;

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		अगर (!plane->state->visible)
			जारी;
		flush_mask |= mdp5_plane_get_flush(plane);
	पूर्ण

	mixer = mdp5_cstate->pipeline.mixer;
	flush_mask |= mdp_ctl_flush_mask_lm(mixer->lm);

	r_mixer = mdp5_cstate->pipeline.r_mixer;
	अगर (r_mixer)
		flush_mask |= mdp_ctl_flush_mask_lm(r_mixer->lm);

	वापस crtc_flush(crtc, flush_mask);
पूर्ण

/* अगर file!=शून्य, this is preबंद potential cancel-flip path */
अटल व्योम complete_flip(काष्ठा drm_crtc *crtc, काष्ठा drm_file *file)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_ctl *ctl = mdp5_cstate->ctl;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_pending_vblank_event *event;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = mdp5_crtc->event;
	अगर (event) अणु
		mdp5_crtc->event = शून्य;
		DBG("%s: send event: %p", crtc->name, event);
		drm_crtc_send_vblank_event(crtc, event);
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);

	अगर (ctl && !crtc->state->enable) अणु
		/* set STAGE_UNUSED क्रम all layers */
		mdp5_ctl_blend(ctl, pipeline, शून्य, शून्य, 0, 0);
		/* XXX: What to करो here? */
		/* mdp5_crtc->ctl = शून्य; */
	पूर्ण
पूर्ण

अटल व्योम unref_cursor_worker(काष्ठा drm_flip_work *work, व्योम *val)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc =
		container_of(work, काष्ठा mdp5_crtc, unref_cursor_work);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(&mdp5_crtc->base);
	काष्ठा msm_kms *kms = &mdp5_kms->base.base;

	msm_gem_unpin_iova(val, kms->aspace);
	drm_gem_object_put(val);
पूर्ण

अटल व्योम mdp5_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);

	drm_crtc_cleanup(crtc);
	drm_flip_work_cleanup(&mdp5_crtc->unref_cursor_work);

	kमुक्त(mdp5_crtc);
पूर्ण

अटल अंतरभूत u32 mdp5_lm_use_fg_alpha_mask(क्रमागत mdp_mixer_stage_id stage)
अणु
	चयन (stage) अणु
	हाल STAGE0: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE0_FG_ALPHA;
	हाल STAGE1: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE1_FG_ALPHA;
	हाल STAGE2: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE2_FG_ALPHA;
	हाल STAGE3: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE3_FG_ALPHA;
	हाल STAGE4: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE4_FG_ALPHA;
	हाल STAGE5: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE5_FG_ALPHA;
	हाल STAGE6: वापस MDP5_LM_BLEND_COLOR_OUT_STAGE6_FG_ALPHA;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * left/right pipe offsets क्रम the stage array used in blend_setup()
 */
#घोषणा PIPE_LEFT	0
#घोषणा PIPE_RIGHT	1

/*
 * blend_setup() - blend all the planes of a CRTC
 *
 * If no base layer is available, border will be enabled as the base layer.
 * Otherwise all layers will be blended based on their stage calculated
 * in mdp5_crtc_atomic_check.
 */
अटल व्योम blend_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा drm_plane *plane;
	काष्ठा mdp5_plane_state *pstate, *pstates[STAGE_MAX + 1] = अणुशून्यपूर्ण;
	स्थिर काष्ठा mdp_क्रमmat *क्रमmat;
	काष्ठा mdp5_hw_mixer *mixer = pipeline->mixer;
	uपूर्णांक32_t lm = mixer->lm;
	काष्ठा mdp5_hw_mixer *r_mixer = pipeline->r_mixer;
	uपूर्णांक32_t r_lm = r_mixer ? r_mixer->lm : 0;
	काष्ठा mdp5_ctl *ctl = mdp5_cstate->ctl;
	uपूर्णांक32_t blend_op, fg_alpha, bg_alpha, ctl_blend_flags = 0;
	अचिन्हित दीर्घ flags;
	क्रमागत mdp5_pipe stage[STAGE_MAX + 1][MAX_PIPE_STAGE] = अणु अणु SSPP_NONE पूर्ण पूर्ण;
	क्रमागत mdp5_pipe r_stage[STAGE_MAX + 1][MAX_PIPE_STAGE] = अणु अणु SSPP_NONE पूर्ण पूर्ण;
	पूर्णांक i, plane_cnt = 0;
	bool bg_alpha_enabled = false;
	u32 mixer_op_mode = 0;
	u32 val;
#घोषणा blender(stage)	((stage) - STAGE0)

	spin_lock_irqsave(&mdp5_crtc->lm_lock, flags);

	/* ctl could be released alपढ़ोy when we are shutting करोwn: */
	/* XXX: Can this happen now? */
	अगर (!ctl)
		जाओ out;

	/* Collect all plane inक्रमmation */
	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		क्रमागत mdp5_pipe right_pipe;

		अगर (!plane->state->visible)
			जारी;

		pstate = to_mdp5_plane_state(plane->state);
		pstates[pstate->stage] = pstate;
		stage[pstate->stage][PIPE_LEFT] = mdp5_plane_pipe(plane);
		/*
		 * अगर we have a right mixer, stage the same pipe as we
		 * have on the left mixer
		 */
		अगर (r_mixer)
			r_stage[pstate->stage][PIPE_LEFT] =
						mdp5_plane_pipe(plane);
		/*
		 * अगर we have a right pipe (i.e, the plane comprises of 2
		 * hwpipes, then stage the right pipe on the right side of both
		 * the layer mixers
		 */
		right_pipe = mdp5_plane_right_pipe(plane);
		अगर (right_pipe) अणु
			stage[pstate->stage][PIPE_RIGHT] = right_pipe;
			r_stage[pstate->stage][PIPE_RIGHT] = right_pipe;
		पूर्ण

		plane_cnt++;
	पूर्ण

	अगर (!pstates[STAGE_BASE]) अणु
		ctl_blend_flags |= MDP5_CTL_BLEND_OP_FLAG_BORDER_OUT;
		DBG("Border Color is enabled");
	पूर्ण अन्यथा अगर (plane_cnt) अणु
		क्रमmat = to_mdp_क्रमmat(msm_framebuffer_क्रमmat(pstates[STAGE_BASE]->base.fb));

		अगर (क्रमmat->alpha_enable)
			bg_alpha_enabled = true;
	पूर्ण

	/* The reset क्रम blending */
	क्रम (i = STAGE0; i <= STAGE_MAX; i++) अणु
		अगर (!pstates[i])
			जारी;

		क्रमmat = to_mdp_क्रमmat(
			msm_framebuffer_क्रमmat(pstates[i]->base.fb));
		plane = pstates[i]->base.plane;
		blend_op = MDP5_LM_BLEND_OP_MODE_FG_ALPHA(FG_CONST) |
			MDP5_LM_BLEND_OP_MODE_BG_ALPHA(BG_CONST);
		fg_alpha = pstates[i]->alpha;
		bg_alpha = 0xFF - pstates[i]->alpha;

		अगर (!क्रमmat->alpha_enable && bg_alpha_enabled)
			mixer_op_mode = 0;
		अन्यथा
			mixer_op_mode |= mdp5_lm_use_fg_alpha_mask(i);

		DBG("Stage %d fg_alpha %x bg_alpha %x", i, fg_alpha, bg_alpha);

		अगर (क्रमmat->alpha_enable && pstates[i]->premultiplied) अणु
			blend_op = MDP5_LM_BLEND_OP_MODE_FG_ALPHA(FG_CONST) |
				MDP5_LM_BLEND_OP_MODE_BG_ALPHA(FG_PIXEL);
			अगर (fg_alpha != 0xff) अणु
				bg_alpha = fg_alpha;
				blend_op |=
					MDP5_LM_BLEND_OP_MODE_BG_MOD_ALPHA |
					MDP5_LM_BLEND_OP_MODE_BG_INV_MOD_ALPHA;
			पूर्ण अन्यथा अणु
				blend_op |= MDP5_LM_BLEND_OP_MODE_BG_INV_ALPHA;
			पूर्ण
		पूर्ण अन्यथा अगर (क्रमmat->alpha_enable) अणु
			blend_op = MDP5_LM_BLEND_OP_MODE_FG_ALPHA(FG_PIXEL) |
				MDP5_LM_BLEND_OP_MODE_BG_ALPHA(FG_PIXEL);
			अगर (fg_alpha != 0xff) अणु
				bg_alpha = fg_alpha;
				blend_op |=
				       MDP5_LM_BLEND_OP_MODE_FG_MOD_ALPHA |
				       MDP5_LM_BLEND_OP_MODE_FG_INV_MOD_ALPHA |
				       MDP5_LM_BLEND_OP_MODE_BG_MOD_ALPHA |
				       MDP5_LM_BLEND_OP_MODE_BG_INV_MOD_ALPHA;
			पूर्ण अन्यथा अणु
				blend_op |= MDP5_LM_BLEND_OP_MODE_BG_INV_ALPHA;
			पूर्ण
		पूर्ण

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_OP_MODE(lm,
				blender(i)), blend_op);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_FG_ALPHA(lm,
				blender(i)), fg_alpha);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_BG_ALPHA(lm,
				blender(i)), bg_alpha);
		अगर (r_mixer) अणु
			mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_OP_MODE(r_lm,
					blender(i)), blend_op);
			mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_FG_ALPHA(r_lm,
					blender(i)), fg_alpha);
			mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_BG_ALPHA(r_lm,
					blender(i)), bg_alpha);
		पूर्ण
	पूर्ण

	val = mdp5_पढ़ो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm),
		   val | mixer_op_mode);
	अगर (r_mixer) अणु
		val = mdp5_पढ़ो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm));
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm),
			   val | mixer_op_mode);
	पूर्ण

	mdp5_ctl_blend(ctl, pipeline, stage, r_stage, plane_cnt,
		       ctl_blend_flags);
out:
	spin_unlock_irqrestore(&mdp5_crtc->lm_lock, flags);
पूर्ण

अटल व्योम mdp5_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा mdp5_hw_mixer *mixer = mdp5_cstate->pipeline.mixer;
	काष्ठा mdp5_hw_mixer *r_mixer = mdp5_cstate->pipeline.r_mixer;
	uपूर्णांक32_t lm = mixer->lm;
	u32 mixer_width, val;
	अचिन्हित दीर्घ flags;
	काष्ठा drm_display_mode *mode;

	अगर (WARN_ON(!crtc->state))
		वापस;

	mode = &crtc->state->adjusted_mode;

	DBG("%s: set mode: " DRM_MODE_FMT, crtc->name, DRM_MODE_ARG(mode));

	mixer_width = mode->hdisplay;
	अगर (r_mixer)
		mixer_width /= 2;

	spin_lock_irqsave(&mdp5_crtc->lm_lock, flags);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_OUT_SIZE(lm),
			MDP5_LM_OUT_SIZE_WIDTH(mixer_width) |
			MDP5_LM_OUT_SIZE_HEIGHT(mode->vdisplay));

	/* Assign mixer to LEFT side in source split mode */
	val = mdp5_पढ़ो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm));
	val &= ~MDP5_LM_BLEND_COLOR_OUT_SPLIT_LEFT_RIGHT;
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm), val);

	अगर (r_mixer) अणु
		u32 r_lm = r_mixer->lm;

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_OUT_SIZE(r_lm),
			   MDP5_LM_OUT_SIZE_WIDTH(mixer_width) |
			   MDP5_LM_OUT_SIZE_HEIGHT(mode->vdisplay));

		/* Assign mixer to RIGHT side in source split mode */
		val = mdp5_पढ़ो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm));
		val |= MDP5_LM_BLEND_COLOR_OUT_SPLIT_LEFT_RIGHT;
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm), val);
	पूर्ण

	spin_unlock_irqrestore(&mdp5_crtc->lm_lock, flags);
पूर्ण

अटल काष्ठा drm_encoder *get_encoder_from_crtc(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder(encoder, dev)
		अगर (encoder->crtc == crtc)
			वापस encoder;

	वापस शून्य;
पूर्ण

अटल bool mdp5_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
					   bool in_vblank_irq,
					   पूर्णांक *vpos, पूर्णांक *hpos,
					   kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
					   स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा drm_encoder *encoder;
	पूर्णांक line, vsw, vbp, vactive_start, vactive_end, vfp_end;


	encoder = get_encoder_from_crtc(crtc);
	अगर (!encoder) अणु
		DRM_ERROR("no encoder found for crtc %d\n", pipe);
		वापस false;
	पूर्ण

	vsw = mode->crtc_vsync_end - mode->crtc_vsync_start;
	vbp = mode->crtc_vtotal - mode->crtc_vsync_end;

	/*
	 * the line counter is 1 at the start of the VSYNC pulse and VTOTAL at
	 * the end of VFP. Translate the porch values relative to the line
	 * counter positions.
	 */

	vactive_start = vsw + vbp + 1;

	vactive_end = vactive_start + mode->crtc_vdisplay;

	/* last scan line beक्रमe VSYNC */
	vfp_end = mode->crtc_vtotal;

	अगर (sसमय)
		*sसमय = kसमय_get();

	line = mdp5_encoder_get_linecount(encoder);

	अगर (line < vactive_start)
		line -= vactive_start;
	अन्यथा अगर (line > vactive_end)
		line = line - vfp_end - vactive_start;
	अन्यथा
		line -= vactive_start;

	*vpos = line;
	*hpos = 0;

	अगर (eसमय)
		*eसमय = kसमय_get();

	वापस true;
पूर्ण

अटल u32 mdp5_crtc_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	encoder = get_encoder_from_crtc(crtc);
	अगर (!encoder)
		वापस 0;

	वापस mdp5_encoder_get_framecount(encoder);
पूर्ण

अटल व्योम mdp5_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा device *dev = &mdp5_kms->pdev->dev;
	अचिन्हित दीर्घ flags;

	DBG("%s", crtc->name);

	अगर (WARN_ON(!mdp5_crtc->enabled))
		वापस;

	/* Disable/save vblank irq handling beक्रमe घातer is disabled */
	drm_crtc_vblank_off(crtc);

	अगर (mdp5_cstate->cmd_mode)
		mdp_irq_unरेजिस्टर(&mdp5_kms->base, &mdp5_crtc->pp_करोne);

	mdp_irq_unरेजिस्टर(&mdp5_kms->base, &mdp5_crtc->err);
	pm_runसमय_put_sync(dev);

	अगर (crtc->state->event && !crtc->state->active) अणु
		WARN_ON(mdp5_crtc->event);
		spin_lock_irqsave(&mdp5_kms->dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
		spin_unlock_irqrestore(&mdp5_kms->dev->event_lock, flags);
	पूर्ण

	mdp5_crtc->enabled = false;
पूर्ण

अटल व्योम mdp5_crtc_vblank_on(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_cstate->pipeline.पूर्णांकf;
	u32 count;

	count = पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND ? 0 : 0xffffffff;
	drm_crtc_set_max_vblank_count(crtc, count);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम mdp5_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा device *dev = &mdp5_kms->pdev->dev;

	DBG("%s", crtc->name);

	अगर (WARN_ON(mdp5_crtc->enabled))
		वापस;

	pm_runसमय_get_sync(dev);

	अगर (mdp5_crtc->lm_cursor_enabled) अणु
		/*
		 * Restore LM cursor state, as it might have been lost
		 * with suspend:
		 */
		अगर (mdp5_crtc->cursor.iova) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&mdp5_crtc->cursor.lock, flags);
			mdp5_crtc_restore_cursor(crtc);
			spin_unlock_irqrestore(&mdp5_crtc->cursor.lock, flags);

			mdp5_ctl_set_cursor(mdp5_cstate->ctl,
					    &mdp5_cstate->pipeline, 0, true);
		पूर्ण अन्यथा अणु
			mdp5_ctl_set_cursor(mdp5_cstate->ctl,
					    &mdp5_cstate->pipeline, 0, false);
		पूर्ण
	पूर्ण

	/* Restore vblank irq handling after घातer is enabled */
	mdp5_crtc_vblank_on(crtc);

	mdp5_crtc_mode_set_nofb(crtc);

	mdp_irq_रेजिस्टर(&mdp5_kms->base, &mdp5_crtc->err);

	अगर (mdp5_cstate->cmd_mode)
		mdp_irq_रेजिस्टर(&mdp5_kms->base, &mdp5_crtc->pp_करोne);

	mdp5_crtc->enabled = true;
पूर्ण

अटल पूर्णांक mdp5_crtc_setup_pipeline(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_crtc_state *new_crtc_state,
				    bool need_right_mixer)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate =
			to_mdp5_crtc_state(new_crtc_state);
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf;
	bool new_mixer = false;

	new_mixer = !pipeline->mixer;

	अगर ((need_right_mixer && !pipeline->r_mixer) ||
	    (!need_right_mixer && pipeline->r_mixer))
		new_mixer = true;

	अगर (new_mixer) अणु
		काष्ठा mdp5_hw_mixer *old_mixer = pipeline->mixer;
		काष्ठा mdp5_hw_mixer *old_r_mixer = pipeline->r_mixer;
		u32 caps;
		पूर्णांक ret;

		caps = MDP_LM_CAP_DISPLAY;
		अगर (need_right_mixer)
			caps |= MDP_LM_CAP_PAIR;

		ret = mdp5_mixer_assign(new_crtc_state->state, crtc, caps,
					&pipeline->mixer, need_right_mixer ?
					&pipeline->r_mixer : शून्य);
		अगर (ret)
			वापस ret;

		mdp5_mixer_release(new_crtc_state->state, old_mixer);
		अगर (old_r_mixer) अणु
			mdp5_mixer_release(new_crtc_state->state, old_r_mixer);
			अगर (!need_right_mixer)
				pipeline->r_mixer = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * these should have been alपढ़ोy set up in the encoder's atomic
	 * check (called by drm_atomic_helper_check_modeset)
	 */
	पूर्णांकf = pipeline->पूर्णांकf;

	mdp5_cstate->err_irqmask = पूर्णांकf2err(पूर्णांकf->num);
	mdp5_cstate->vblank_irqmask = पूर्णांकf2vblank(pipeline->mixer, पूर्णांकf);

	अगर ((पूर्णांकf->type == INTF_DSI) &&
	    (पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND)) अणु
		mdp5_cstate->pp_करोne_irqmask = lm2ppकरोne(pipeline->mixer);
		mdp5_cstate->cmd_mode = true;
	पूर्ण अन्यथा अणु
		mdp5_cstate->pp_करोne_irqmask = 0;
		mdp5_cstate->cmd_mode = false;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा plane_state अणु
	काष्ठा drm_plane *plane;
	काष्ठा mdp5_plane_state *state;
पूर्ण;

अटल पूर्णांक pstate_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा plane_state *pa = (काष्ठा plane_state *)a;
	काष्ठा plane_state *pb = (काष्ठा plane_state *)b;
	वापस pa->state->zpos - pb->state->zpos;
पूर्ण

/* is there a helper क्रम this? */
अटल bool is_fullscreen(काष्ठा drm_crtc_state *cstate,
		काष्ठा drm_plane_state *pstate)
अणु
	वापस (pstate->crtc_x <= 0) && (pstate->crtc_y <= 0) &&
		((pstate->crtc_x + pstate->crtc_w) >= cstate->mode.hdisplay) &&
		((pstate->crtc_y + pstate->crtc_h) >= cstate->mode.vdisplay);
पूर्ण

अटल क्रमागत mdp_mixer_stage_id get_start_stage(काष्ठा drm_crtc *crtc,
					काष्ठा drm_crtc_state *new_crtc_state,
					काष्ठा drm_plane_state *bpstate)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate =
			to_mdp5_crtc_state(new_crtc_state);

	/*
	 * अगर we're in source split mode, it's mandatory to have
	 * border out on the base stage
	 */
	अगर (mdp5_cstate->pipeline.r_mixer)
		वापस STAGE0;

	/* अगर the bottom-most layer is not fullscreen, we need to use
	 * it क्रम solid-color:
	 */
	अगर (!is_fullscreen(new_crtc_state, bpstate))
		वापस STAGE0;

	वापस STAGE_BASE;
पूर्ण

अटल पूर्णांक mdp5_crtc_atomic_check(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा drm_plane *plane;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा plane_state pstates[STAGE_MAX + 1];
	स्थिर काष्ठा mdp5_cfg_hw *hw_cfg;
	स्थिर काष्ठा drm_plane_state *pstate;
	स्थिर काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;
	bool cursor_plane = false;
	bool need_right_mixer = false;
	पूर्णांक cnt = 0, i;
	पूर्णांक ret;
	क्रमागत mdp_mixer_stage_id start;

	DBG("%s: check", crtc->name);

	drm_atomic_crtc_state_क्रम_each_plane_state(plane, pstate, crtc_state) अणु
		अगर (!pstate->visible)
			जारी;

		pstates[cnt].plane = plane;
		pstates[cnt].state = to_mdp5_plane_state(pstate);

		/*
		 * अगर any plane on this crtc uses 2 hwpipes, then we need
		 * the crtc to have a right hwmixer.
		 */
		अगर (pstates[cnt].state->r_hwpipe)
			need_right_mixer = true;
		cnt++;

		अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			cursor_plane = true;
	पूर्ण

	/* bail out early अगर there aren't any planes */
	अगर (!cnt)
		वापस 0;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	/*
	 * we need a right hwmixer अगर the mode's width is greater than a single
	 * LM's max width
	 */
	अगर (mode->hdisplay > hw_cfg->lm.max_width)
		need_right_mixer = true;

	ret = mdp5_crtc_setup_pipeline(crtc, crtc_state, need_right_mixer);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "couldn't assign mixers %d\n", ret);
		वापस ret;
	पूर्ण

	/* assign a stage based on sorted zpos property */
	sort(pstates, cnt, माप(pstates[0]), pstate_cmp, शून्य);

	/* trigger a warning अगर cursor isn't the highest zorder */
	WARN_ON(cursor_plane &&
		(pstates[cnt - 1].plane->type != DRM_PLANE_TYPE_CURSOR));

	start = get_start_stage(crtc, crtc_state, &pstates[0].state->base);

	/* verअगरy that there are not too many planes attached to crtc
	 * and that we करोn't have conflicting mixer stages:
	 */
	अगर ((cnt + start - 1) >= hw_cfg->lm.nb_stages) अणु
		DRM_DEV_ERROR(dev->dev, "too many planes! cnt=%d, start stage=%d\n",
			cnt, start);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (cursor_plane && (i == (cnt - 1)))
			pstates[i].state->stage = hw_cfg->lm.nb_stages;
		अन्यथा
			pstates[i].state->stage = start + i;
		DBG("%s: assign pipe %s on stage=%d", crtc->name,
				pstates[i].plane->name,
				pstates[i].state->stage);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mdp5_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	DBG("%s: begin", crtc->name);
पूर्ण

अटल व्योम mdp5_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित दीर्घ flags;

	DBG("%s: event: %p", crtc->name, crtc->state->event);

	WARN_ON(mdp5_crtc->event);

	spin_lock_irqsave(&dev->event_lock, flags);
	mdp5_crtc->event = crtc->state->event;
	crtc->state->event = शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/*
	 * If no CTL has been allocated in mdp5_crtc_atomic_check(),
	 * it means we are trying to flush a CRTC whose state is disabled:
	 * nothing अन्यथा needs to be करोne.
	 */
	/* XXX: Can this happen now ? */
	अगर (unlikely(!mdp5_cstate->ctl))
		वापस;

	blend_setup(crtc);

	/* PP_DONE irq is only used by command mode क्रम now.
	 * It is better to request pending beक्रमe FLUSH and START trigger
	 * to make sure no pp_करोne irq missed.
	 * This is safe because no pp_करोne will happen beक्रमe SW trigger
	 * in command mode.
	 */
	अगर (mdp5_cstate->cmd_mode)
		request_pp_करोne_pending(crtc);

	mdp5_crtc->flushed_mask = crtc_flush_all(crtc);

	/* XXX are we leaking out state here? */
	mdp5_crtc->vblank.irqmask = mdp5_cstate->vblank_irqmask;
	mdp5_crtc->err.irqmask = mdp5_cstate->err_irqmask;
	mdp5_crtc->pp_करोne.irqmask = mdp5_cstate->pp_करोne_irqmask;

	request_pending(crtc, PENDING_FLIP);
पूर्ण

अटल व्योम get_roi(काष्ठा drm_crtc *crtc, uपूर्णांक32_t *roi_w, uपूर्णांक32_t *roi_h)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	uपूर्णांक32_t xres = crtc->mode.hdisplay;
	uपूर्णांक32_t yres = crtc->mode.vdisplay;

	/*
	 * Cursor Region Of Interest (ROI) is a plane पढ़ो from cursor
	 * buffer to render. The ROI region is determined by the visibility of
	 * the cursor poपूर्णांक. In the शेष Cursor image the cursor poपूर्णांक will
	 * be at the top left of the cursor image.
	 *
	 * Without rotation:
	 * If the cursor poपूर्णांक reaches the right (xres - x < cursor.width) or
	 * bottom (yres - y < cursor.height) boundary of the screen, then ROI
	 * width and ROI height need to be evaluated to crop the cursor image
	 * accordingly.
	 * (xres-x) will be new cursor width when x > (xres - cursor.width)
	 * (yres-y) will be new cursor height when y > (yres - cursor.height)
	 *
	 * With rotation:
	 * We get negative x and/or y coordinates.
	 * (cursor.width - असल(x)) will be new cursor width when x < 0
	 * (cursor.height - असल(y)) will be new cursor width when y < 0
	 */
	अगर (mdp5_crtc->cursor.x >= 0)
		*roi_w = min(mdp5_crtc->cursor.width, xres -
			mdp5_crtc->cursor.x);
	अन्यथा
		*roi_w = mdp5_crtc->cursor.width - असल(mdp5_crtc->cursor.x);
	अगर (mdp5_crtc->cursor.y >= 0)
		*roi_h = min(mdp5_crtc->cursor.height, yres -
			mdp5_crtc->cursor.y);
	अन्यथा
		*roi_h = mdp5_crtc->cursor.height - असल(mdp5_crtc->cursor.y);
पूर्ण

अटल व्योम mdp5_crtc_restore_cursor(काष्ठा drm_crtc *crtc)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(DRM_FORMAT_ARGB8888);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	स्थिर क्रमागत mdp5_cursor_alpha cur_alpha = CURSOR_ALPHA_PER_PIXEL;
	uपूर्णांक32_t blendcfg, stride;
	uपूर्णांक32_t x, y, src_x, src_y, width, height;
	uपूर्णांक32_t roi_w, roi_h;
	पूर्णांक lm;

	निश्चित_spin_locked(&mdp5_crtc->cursor.lock);

	lm = mdp5_cstate->pipeline.mixer->lm;

	x = mdp5_crtc->cursor.x;
	y = mdp5_crtc->cursor.y;
	width = mdp5_crtc->cursor.width;
	height = mdp5_crtc->cursor.height;

	stride = width * info->cpp[0];

	get_roi(crtc, &roi_w, &roi_h);

	/* If cusror buffer overlaps due to rotation on the
	 * upper or left screen border the pixel offset inside
	 * the cursor buffer of the ROI is the positive overlap
	 * distance.
	 */
	अगर (mdp5_crtc->cursor.x < 0) अणु
		src_x = असल(mdp5_crtc->cursor.x);
		x = 0;
	पूर्ण अन्यथा अणु
		src_x = 0;
	पूर्ण
	अगर (mdp5_crtc->cursor.y < 0) अणु
		src_y = असल(mdp5_crtc->cursor.y);
		y = 0;
	पूर्ण अन्यथा अणु
		src_y = 0;
	पूर्ण
	DBG("%s: x=%d, y=%d roi_w=%d roi_h=%d src_x=%d src_y=%d",
		crtc->name, x, y, roi_w, roi_h, src_x, src_y);

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_STRIDE(lm), stride);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_FORMAT(lm),
			MDP5_LM_CURSOR_FORMAT_FORMAT(CURSOR_FMT_ARGB8888));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_IMG_SIZE(lm),
			MDP5_LM_CURSOR_IMG_SIZE_SRC_H(height) |
			MDP5_LM_CURSOR_IMG_SIZE_SRC_W(width));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_SIZE(lm),
			MDP5_LM_CURSOR_SIZE_ROI_H(roi_h) |
			MDP5_LM_CURSOR_SIZE_ROI_W(roi_w));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_START_XY(lm),
			MDP5_LM_CURSOR_START_XY_Y_START(y) |
			MDP5_LM_CURSOR_START_XY_X_START(x));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_XY(lm),
			MDP5_LM_CURSOR_XY_SRC_Y(src_y) |
			MDP5_LM_CURSOR_XY_SRC_X(src_x));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_BASE_ADDR(lm),
			mdp5_crtc->cursor.iova);

	blendcfg = MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_EN;
	blendcfg |= MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_ALPHA_SEL(cur_alpha);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_LM_CURSOR_BLEND_CONFIG(lm), blendcfg);
पूर्ण

अटल पूर्णांक mdp5_crtc_cursor_set(काष्ठा drm_crtc *crtc,
		काष्ठा drm_file *file, uपूर्णांक32_t handle,
		uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा platक्रमm_device *pdev = mdp5_kms->pdev;
	काष्ठा msm_kms *kms = &mdp5_kms->base.base;
	काष्ठा drm_gem_object *cursor_bo, *old_bo = शून्य;
	काष्ठा mdp5_ctl *ctl;
	पूर्णांक ret;
	uपूर्णांक32_t flush_mask = mdp_ctl_flush_mask_cursor(0);
	bool cursor_enable = true;
	अचिन्हित दीर्घ flags;

	अगर (!mdp5_crtc->lm_cursor_enabled) अणु
		dev_warn(dev->dev,
			 "cursor_set is deprecated with cursor planes\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((width > CURSOR_WIDTH) || (height > CURSOR_HEIGHT)) अणु
		DRM_DEV_ERROR(dev->dev, "bad cursor size: %dx%d\n", width, height);
		वापस -EINVAL;
	पूर्ण

	ctl = mdp5_cstate->ctl;
	अगर (!ctl)
		वापस -EINVAL;

	/* करोn't support LM cursors when we have source split enabled */
	अगर (mdp5_cstate->pipeline.r_mixer)
		वापस -EINVAL;

	अगर (!handle) अणु
		DBG("Cursor off");
		cursor_enable = false;
		mdp5_crtc->cursor.iova = 0;
		pm_runसमय_get_sync(&pdev->dev);
		जाओ set_cursor;
	पूर्ण

	cursor_bo = drm_gem_object_lookup(file, handle);
	अगर (!cursor_bo)
		वापस -ENOENT;

	ret = msm_gem_get_and_pin_iova(cursor_bo, kms->aspace,
			&mdp5_crtc->cursor.iova);
	अगर (ret)
		वापस -EINVAL;

	pm_runसमय_get_sync(&pdev->dev);

	spin_lock_irqsave(&mdp5_crtc->cursor.lock, flags);
	old_bo = mdp5_crtc->cursor.scanout_bo;

	mdp5_crtc->cursor.scanout_bo = cursor_bo;
	mdp5_crtc->cursor.width = width;
	mdp5_crtc->cursor.height = height;

	mdp5_crtc_restore_cursor(crtc);

	spin_unlock_irqrestore(&mdp5_crtc->cursor.lock, flags);

set_cursor:
	ret = mdp5_ctl_set_cursor(ctl, pipeline, 0, cursor_enable);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to %sable cursor: %d\n",
				cursor_enable ? "en" : "dis", ret);
		जाओ end;
	पूर्ण

	crtc_flush(crtc, flush_mask);

end:
	pm_runसमय_put_sync(&pdev->dev);
	अगर (old_bo) अणु
		drm_flip_work_queue(&mdp5_crtc->unref_cursor_work, old_bo);
		/* enable vblank to complete cursor work: */
		request_pending(crtc, PENDING_CURSOR);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mdp5_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	uपूर्णांक32_t flush_mask = mdp_ctl_flush_mask_cursor(0);
	काष्ठा drm_device *dev = crtc->dev;
	uपूर्णांक32_t roi_w;
	uपूर्णांक32_t roi_h;
	अचिन्हित दीर्घ flags;

	अगर (!mdp5_crtc->lm_cursor_enabled) अणु
		dev_warn(dev->dev,
			 "cursor_move is deprecated with cursor planes\n");
		वापस -EINVAL;
	पूर्ण

	/* करोn't support LM cursors when we have source split enabled */
	अगर (mdp5_cstate->pipeline.r_mixer)
		वापस -EINVAL;

	/* In हाल the CRTC is disabled, just drop the cursor update */
	अगर (unlikely(!crtc->state->enable))
		वापस 0;

	/* accept negative x/y coordinates up to maximum cursor overlap */
	mdp5_crtc->cursor.x = x = max(x, -(पूर्णांक)mdp5_crtc->cursor.width);
	mdp5_crtc->cursor.y = y = max(y, -(पूर्णांक)mdp5_crtc->cursor.height);

	get_roi(crtc, &roi_w, &roi_h);

	pm_runसमय_get_sync(&mdp5_kms->pdev->dev);

	spin_lock_irqsave(&mdp5_crtc->cursor.lock, flags);
	mdp5_crtc_restore_cursor(crtc);
	spin_unlock_irqrestore(&mdp5_crtc->cursor.lock, flags);

	crtc_flush(crtc, flush_mask);

	pm_runसमय_put_sync(&mdp5_kms->pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम
mdp5_crtc_atomic_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
			     स्थिर काष्ठा drm_crtc_state *state)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(state);
	काष्ठा mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	काष्ठा mdp5_kms *mdp5_kms = get_kms(state->crtc);

	अगर (WARN_ON(!pipeline))
		वापस;

	अगर (mdp5_cstate->ctl)
		drm_म_लिखो(p, "\tctl=%d\n", mdp5_ctl_get_ctl_id(mdp5_cstate->ctl));

	drm_म_लिखो(p, "\thwmixer=%s\n", pipeline->mixer ?
			pipeline->mixer->name : "(null)");

	अगर (mdp5_kms->caps & MDP_CAP_SRC_SPLIT)
		drm_म_लिखो(p, "\tright hwmixer=%s\n", pipeline->r_mixer ?
			   pipeline->r_mixer->name : "(null)");

	drm_म_लिखो(p, "\tcmd_mode=%d\n", mdp5_cstate->cmd_mode);
पूर्ण

अटल काष्ठा drm_crtc_state *
mdp5_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	mdp5_cstate = kmemdup(to_mdp5_crtc_state(crtc->state),
			      माप(*mdp5_cstate), GFP_KERNEL);
	अगर (!mdp5_cstate)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &mdp5_cstate->base);

	वापस &mdp5_cstate->base;
पूर्ण

अटल व्योम mdp5_crtc_destroy_state(काष्ठा drm_crtc *crtc, काष्ठा drm_crtc_state *state)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(state);

	__drm_atomic_helper_crtc_destroy_state(state);

	kमुक्त(mdp5_cstate);
पूर्ण

अटल व्योम mdp5_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate =
		kzalloc(माप(*mdp5_cstate), GFP_KERNEL);

	अगर (crtc->state)
		mdp5_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &mdp5_cstate->base);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs mdp5_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = mdp5_crtc_destroy,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = mdp5_crtc_reset,
	.atomic_duplicate_state = mdp5_crtc_duplicate_state,
	.atomic_destroy_state = mdp5_crtc_destroy_state,
	.cursor_set = mdp5_crtc_cursor_set,
	.cursor_move = mdp5_crtc_cursor_move,
	.atomic_prपूर्णांक_state = mdp5_crtc_atomic_prपूर्णांक_state,
	.get_vblank_counter = mdp5_crtc_get_vblank_counter,
	.enable_vblank  = msm_crtc_enable_vblank,
	.disable_vblank = msm_crtc_disable_vblank,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs mdp5_crtc_helper_funcs = अणु
	.mode_set_nofb = mdp5_crtc_mode_set_nofb,
	.atomic_check = mdp5_crtc_atomic_check,
	.atomic_begin = mdp5_crtc_atomic_begin,
	.atomic_flush = mdp5_crtc_atomic_flush,
	.atomic_enable = mdp5_crtc_atomic_enable,
	.atomic_disable = mdp5_crtc_atomic_disable,
	.get_scanout_position = mdp5_crtc_get_scanout_position,
पूर्ण;

अटल व्योम mdp5_crtc_vblank_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = container_of(irq, काष्ठा mdp5_crtc, vblank);
	काष्ठा drm_crtc *crtc = &mdp5_crtc->base;
	काष्ठा msm_drm_निजी *priv = crtc->dev->dev_निजी;
	अचिन्हित pending;

	mdp_irq_unरेजिस्टर(&get_kms(crtc)->base, &mdp5_crtc->vblank);

	pending = atomic_xchg(&mdp5_crtc->pending, 0);

	अगर (pending & PENDING_FLIP) अणु
		complete_flip(crtc, शून्य);
	पूर्ण

	अगर (pending & PENDING_CURSOR)
		drm_flip_work_commit(&mdp5_crtc->unref_cursor_work, priv->wq);
पूर्ण

अटल व्योम mdp5_crtc_err_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = container_of(irq, काष्ठा mdp5_crtc, err);

	DBG("%s: error: %08x", mdp5_crtc->base.name, irqstatus);
पूर्ण

अटल व्योम mdp5_crtc_pp_करोne_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = container_of(irq, काष्ठा mdp5_crtc,
								pp_करोne);

	complete_all(&mdp5_crtc->pp_completion);
पूर्ण

अटल व्योम mdp5_crtc_रुको_क्रम_pp_करोne(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&mdp5_crtc->pp_completion,
						msecs_to_jअगरfies(50));
	अगर (ret == 0)
		dev_warn_ratelimited(dev->dev, "pp done time out, lm=%d\n",
				     mdp5_cstate->pipeline.mixer->lm);
पूर्ण

अटल व्योम mdp5_crtc_रुको_क्रम_flush_करोne(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_ctl *ctl = mdp5_cstate->ctl;
	पूर्णांक ret;

	/* Should not call this function अगर crtc is disabled. */
	अगर (!ctl)
		वापस;

	ret = drm_crtc_vblank_get(crtc);
	अगर (ret)
		वापस;

	ret = रुको_event_समयout(dev->vblank[drm_crtc_index(crtc)].queue,
		((mdp5_ctl_get_commit_status(ctl) &
		mdp5_crtc->flushed_mask) == 0),
		msecs_to_jअगरfies(50));
	अगर (ret <= 0)
		dev_warn(dev->dev, "vblank time out, crtc=%d\n", mdp5_crtc->id);

	mdp5_crtc->flushed_mask = 0;

	drm_crtc_vblank_put(crtc);
पूर्ण

uपूर्णांक32_t mdp5_crtc_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	वापस mdp5_crtc->vblank.irqmask;
पूर्ण

व्योम mdp5_crtc_set_pipeline(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(crtc);

	/* should this be करोne अन्यथाwhere ? */
	mdp_irq_update(&mdp5_kms->base);

	mdp5_ctl_set_pipeline(mdp5_cstate->ctl, &mdp5_cstate->pipeline);
पूर्ण

काष्ठा mdp5_ctl *mdp5_crtc_get_ctl(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);

	वापस mdp5_cstate->ctl;
पूर्ण

काष्ठा mdp5_hw_mixer *mdp5_crtc_get_mixer(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate;

	अगर (WARN_ON(!crtc))
		वापस ERR_PTR(-EINVAL);

	mdp5_cstate = to_mdp5_crtc_state(crtc->state);

	वापस WARN_ON(!mdp5_cstate->pipeline.mixer) ?
		ERR_PTR(-EINVAL) : mdp5_cstate->pipeline.mixer;
पूर्ण

काष्ठा mdp5_pipeline *mdp5_crtc_get_pipeline(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate;

	अगर (WARN_ON(!crtc))
		वापस ERR_PTR(-EINVAL);

	mdp5_cstate = to_mdp5_crtc_state(crtc->state);

	वापस &mdp5_cstate->pipeline;
पूर्ण

व्योम mdp5_crtc_रुको_क्रम_commit_करोne(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);

	अगर (mdp5_cstate->cmd_mode)
		mdp5_crtc_रुको_क्रम_pp_करोne(crtc);
	अन्यथा
		mdp5_crtc_रुको_क्रम_flush_करोne(crtc);
पूर्ण

/* initialize crtc */
काष्ठा drm_crtc *mdp5_crtc_init(काष्ठा drm_device *dev,
				काष्ठा drm_plane *plane,
				काष्ठा drm_plane *cursor_plane, पूर्णांक id)
अणु
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा mdp5_crtc *mdp5_crtc;

	mdp5_crtc = kzalloc(माप(*mdp5_crtc), GFP_KERNEL);
	अगर (!mdp5_crtc)
		वापस ERR_PTR(-ENOMEM);

	crtc = &mdp5_crtc->base;

	mdp5_crtc->id = id;

	spin_lock_init(&mdp5_crtc->lm_lock);
	spin_lock_init(&mdp5_crtc->cursor.lock);
	init_completion(&mdp5_crtc->pp_completion);

	mdp5_crtc->vblank.irq = mdp5_crtc_vblank_irq;
	mdp5_crtc->err.irq = mdp5_crtc_err_irq;
	mdp5_crtc->pp_करोne.irq = mdp5_crtc_pp_करोne_irq;

	mdp5_crtc->lm_cursor_enabled = cursor_plane ? false : true;

	drm_crtc_init_with_planes(dev, crtc, plane, cursor_plane,
				  &mdp5_crtc_funcs, शून्य);

	drm_flip_work_init(&mdp5_crtc->unref_cursor_work,
			"unref cursor", unref_cursor_worker);

	drm_crtc_helper_add(crtc, &mdp5_crtc_helper_funcs);

	वापस crtc;
पूर्ण
