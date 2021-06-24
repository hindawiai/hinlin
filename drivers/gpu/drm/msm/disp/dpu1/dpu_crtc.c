<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2018 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__
#समावेश <linux/sort.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/bits.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_flip_work.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_vblank.h>

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_hw_dspp.h"
#समावेश "dpu_crtc.h"
#समावेश "dpu_plane.h"
#समावेश "dpu_encoder.h"
#समावेश "dpu_vbif.h"
#समावेश "dpu_core_perf.h"
#समावेश "dpu_trace.h"

#घोषणा DPU_DRM_BLEND_OP_NOT_DEFINED    0
#घोषणा DPU_DRM_BLEND_OP_OPAQUE         1
#घोषणा DPU_DRM_BLEND_OP_PREMULTIPLIED  2
#घोषणा DPU_DRM_BLEND_OP_COVERAGE       3
#घोषणा DPU_DRM_BLEND_OP_MAX            4

/* layer mixer index on dpu_crtc */
#घोषणा LEFT_MIXER 0
#घोषणा RIGHT_MIXER 1

/* समयout in ms रुकोing क्रम frame करोne */
#घोषणा DPU_CRTC_FRAME_DONE_TIMEOUT_MS	60

#घोषणा	CONVERT_S3_15(val) \
	(((((u64)val) & ~BIT_ULL(63)) >> 17) & GENMASK_ULL(17, 0))

अटल काष्ठा dpu_kms *_dpu_crtc_get_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा msm_drm_निजी *priv = crtc->dev->dev_निजी;

	वापस to_dpu_kms(priv->kms);
पूर्ण

अटल व्योम dpu_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	DPU_DEBUG("\n");

	अगर (!crtc)
		वापस;

	drm_crtc_cleanup(crtc);
	kमुक्त(dpu_crtc);
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

अटल u32 dpu_crtc_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	encoder = get_encoder_from_crtc(crtc);
	अगर (!encoder) अणु
		DRM_ERROR("no encoder found for crtc %d\n", crtc->index);
		वापस false;
	पूर्ण

	वापस dpu_encoder_get_frame_count(encoder);
पूर्ण

अटल bool dpu_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
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

	line = dpu_encoder_get_linecount(encoder);

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

अटल व्योम _dpu_crtc_setup_blend_cfg(काष्ठा dpu_crtc_mixer *mixer,
		काष्ठा dpu_plane_state *pstate, काष्ठा dpu_क्रमmat *क्रमmat)
अणु
	काष्ठा dpu_hw_mixer *lm = mixer->hw_lm;
	uपूर्णांक32_t blend_op;

	/* शेष to opaque blending */
	blend_op = DPU_BLEND_FG_ALPHA_FG_CONST |
		DPU_BLEND_BG_ALPHA_BG_CONST;

	अगर (क्रमmat->alpha_enable) अणु
		/* coverage blending */
		blend_op = DPU_BLEND_FG_ALPHA_FG_PIXEL |
			DPU_BLEND_BG_ALPHA_FG_PIXEL |
			DPU_BLEND_BG_INV_ALPHA;
	पूर्ण

	lm->ops.setup_blend_config(lm, pstate->stage,
				0xFF, 0, blend_op);

	DPU_DEBUG("format:%p4cc, alpha_en:%u blend_op:0x%x\n",
		  &क्रमmat->base.pixel_क्रमmat, क्रमmat->alpha_enable, blend_op);
पूर्ण

अटल व्योम _dpu_crtc_program_lm_output_roi(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc_state *crtc_state;
	पूर्णांक lm_idx, lm_horiz_position;

	crtc_state = to_dpu_crtc_state(crtc->state);

	lm_horiz_position = 0;
	क्रम (lm_idx = 0; lm_idx < crtc_state->num_mixers; lm_idx++) अणु
		स्थिर काष्ठा drm_rect *lm_roi = &crtc_state->lm_bounds[lm_idx];
		काष्ठा dpu_hw_mixer *hw_lm = crtc_state->mixers[lm_idx].hw_lm;
		काष्ठा dpu_hw_mixer_cfg cfg;

		अगर (!lm_roi || !drm_rect_visible(lm_roi))
			जारी;

		cfg.out_width = drm_rect_width(lm_roi);
		cfg.out_height = drm_rect_height(lm_roi);
		cfg.right_mixer = lm_horiz_position++;
		cfg.flags = 0;
		hw_lm->ops.setup_mixer_out(hw_lm, &cfg);
	पूर्ण
पूर्ण

अटल व्योम _dpu_crtc_blend_setup_mixer(काष्ठा drm_crtc *crtc,
	काष्ठा dpu_crtc *dpu_crtc, काष्ठा dpu_crtc_mixer *mixer)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_plane_state *state;
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);
	काष्ठा dpu_plane_state *pstate = शून्य;
	काष्ठा dpu_क्रमmat *क्रमmat;
	काष्ठा dpu_hw_ctl *ctl = mixer->lm_ctl;
	काष्ठा dpu_hw_stage_cfg *stage_cfg = &dpu_crtc->stage_cfg;

	u32 flush_mask;
	uपूर्णांक32_t stage_idx, lm_idx;
	पूर्णांक zpos_cnt[DPU_STAGE_MAX + 1] = अणु 0 पूर्ण;
	bool bg_alpha_enable = false;
	DECLARE_BITMAP(fetch_active, SSPP_MAX);

	स_रखो(fetch_active, 0, माप(fetch_active));
	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		state = plane->state;
		अगर (!state)
			जारी;

		pstate = to_dpu_plane_state(state);
		fb = state->fb;

		dpu_plane_get_ctl_flush(plane, ctl, &flush_mask);
		set_bit(dpu_plane_pipe(plane), fetch_active);
		DPU_DEBUG("crtc %d stage:%d - plane %d sspp %d fb %d\n",
				crtc->base.id,
				pstate->stage,
				plane->base.id,
				dpu_plane_pipe(plane) - SSPP_VIG0,
				state->fb ? state->fb->base.id : -1);

		क्रमmat = to_dpu_क्रमmat(msm_framebuffer_क्रमmat(pstate->base.fb));

		अगर (pstate->stage == DPU_STAGE_BASE && क्रमmat->alpha_enable)
			bg_alpha_enable = true;

		stage_idx = zpos_cnt[pstate->stage]++;
		stage_cfg->stage[pstate->stage][stage_idx] =
					dpu_plane_pipe(plane);
		stage_cfg->multirect_index[pstate->stage][stage_idx] =
					pstate->multirect_index;

		trace_dpu_crtc_setup_mixer(DRMID(crtc), DRMID(plane),
					   state, pstate, stage_idx,
					   dpu_plane_pipe(plane) - SSPP_VIG0,
					   क्रमmat->base.pixel_क्रमmat,
					   fb ? fb->modअगरier : 0);

		/* blend config update */
		क्रम (lm_idx = 0; lm_idx < cstate->num_mixers; lm_idx++) अणु
			_dpu_crtc_setup_blend_cfg(mixer + lm_idx,
						pstate, क्रमmat);

			mixer[lm_idx].flush_mask |= flush_mask;

			अगर (bg_alpha_enable && !क्रमmat->alpha_enable)
				mixer[lm_idx].mixer_op_mode = 0;
			अन्यथा
				mixer[lm_idx].mixer_op_mode |=
						1 << pstate->stage;
		पूर्ण
	पूर्ण

	अगर (ctl->ops.set_active_pipes)
		ctl->ops.set_active_pipes(ctl, fetch_active);

	 _dpu_crtc_program_lm_output_roi(crtc);
पूर्ण

/**
 * _dpu_crtc_blend_setup - configure crtc mixers
 * @crtc: Poपूर्णांकer to drm crtc काष्ठाure
 */
अटल व्योम _dpu_crtc_blend_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);
	काष्ठा dpu_crtc_mixer *mixer = cstate->mixers;
	काष्ठा dpu_hw_ctl *ctl;
	काष्ठा dpu_hw_mixer *lm;
	पूर्णांक i;

	DPU_DEBUG("%s\n", dpu_crtc->name);

	क्रम (i = 0; i < cstate->num_mixers; i++) अणु
		mixer[i].mixer_op_mode = 0;
		mixer[i].flush_mask = 0;
		अगर (mixer[i].lm_ctl->ops.clear_all_blendstages)
			mixer[i].lm_ctl->ops.clear_all_blendstages(
					mixer[i].lm_ctl);
	पूर्ण

	/* initialize stage cfg */
	स_रखो(&dpu_crtc->stage_cfg, 0, माप(काष्ठा dpu_hw_stage_cfg));

	_dpu_crtc_blend_setup_mixer(crtc, dpu_crtc, mixer);

	क्रम (i = 0; i < cstate->num_mixers; i++) अणु
		ctl = mixer[i].lm_ctl;
		lm = mixer[i].hw_lm;

		lm->ops.setup_alpha_out(lm, mixer[i].mixer_op_mode);

		mixer[i].flush_mask |= ctl->ops.get_biपंचांगask_mixer(ctl,
			mixer[i].hw_lm->idx);

		/* stage config flush mask */
		ctl->ops.update_pending_flush(ctl, mixer[i].flush_mask);

		DPU_DEBUG("lm %d, op_mode 0x%X, ctl %d, flush mask 0x%x\n",
			mixer[i].hw_lm->idx - LM_0,
			mixer[i].mixer_op_mode,
			ctl->idx - CTL_0,
			mixer[i].flush_mask);

		ctl->ops.setup_blendstage(ctl, mixer[i].hw_lm->idx,
			&dpu_crtc->stage_cfg);
	पूर्ण
पूर्ण

/**
 *  _dpu_crtc_complete_flip - संकेत pending page_flip events
 * Any pending vblank events are added to the vblank_event_list
 * so that the next vblank पूर्णांकerrupt shall संकेत them.
 * However PAGE_FLIP events are not handled through the vblank_event_list.
 * This API संकेतs any pending PAGE_FLIP events requested through
 * DRM_IOCTL_MODE_PAGE_FLIP and are cached in the dpu_crtc->event.
 * @crtc: Poपूर्णांकer to drm crtc काष्ठाure
 */
अटल व्योम _dpu_crtc_complete_flip(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (dpu_crtc->event) अणु
		DRM_DEBUG_VBL("%s: send event: %pK\n", dpu_crtc->name,
			      dpu_crtc->event);
		trace_dpu_crtc_complete_flip(DRMID(crtc));
		drm_crtc_send_vblank_event(crtc, dpu_crtc->event);
		dpu_crtc->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

क्रमागत dpu_पूर्णांकf_mode dpu_crtc_get_पूर्णांकf_mode(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	/*
	 * TODO: This function is called from dpu debugfs and as part of atomic
	 * check. When called from debugfs, the crtc->mutex must be held to
	 * पढ़ो crtc->state. However पढ़ोing crtc->state from atomic check isn't
	 * allowed (unless you have a good reason, a big comment, and a deep
	 * understanding of how the atomic/modeset locks work (<- and this is
	 * probably not possible)). So we'll keep the WARN_ON here क्रम now, but
	 * really we need to figure out a better way to track our operating mode
	 */
	WARN_ON(!drm_modeset_is_locked(&crtc->mutex));

	/* TODO: Returns the first INTF_MODE, could there be multiple values? */
	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask)
		वापस dpu_encoder_get_पूर्णांकf_mode(encoder);

	वापस INTF_MODE_NONE;
पूर्ण

व्योम dpu_crtc_vblank_callback(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	/* keep statistics on vblank callback - with स्वतः reset via debugfs */
	अगर (kसमय_compare(dpu_crtc->vblank_cb_समय, kसमय_set(0, 0)) == 0)
		dpu_crtc->vblank_cb_समय = kसमय_get();
	अन्यथा
		dpu_crtc->vblank_cb_count++;
	drm_crtc_handle_vblank(crtc);
	trace_dpu_crtc_vblank_cb(DRMID(crtc));
पूर्ण

अटल व्योम dpu_crtc_frame_event_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा dpu_crtc_frame_event *fevent = container_of(work,
			काष्ठा dpu_crtc_frame_event, work);
	काष्ठा drm_crtc *crtc = fevent->crtc;
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	अचिन्हित दीर्घ flags;
	bool frame_करोne = false;

	DPU_ATRACE_BEGIN("crtc_frame_event");

	DRM_DEBUG_KMS("crtc%d event:%u ts:%lld\n", crtc->base.id, fevent->event,
			kसमय_प्रकारo_ns(fevent->ts));

	अगर (fevent->event & (DPU_ENCODER_FRAME_EVENT_DONE
				| DPU_ENCODER_FRAME_EVENT_ERROR
				| DPU_ENCODER_FRAME_EVENT_PANEL_DEAD)) अणु

		अगर (atomic_पढ़ो(&dpu_crtc->frame_pending) < 1) अणु
			/* ignore vblank when not pending */
		पूर्ण अन्यथा अगर (atomic_dec_वापस(&dpu_crtc->frame_pending) == 0) अणु
			/* release bandwidth and other resources */
			trace_dpu_crtc_frame_event_करोne(DRMID(crtc),
							fevent->event);
			dpu_core_perf_crtc_release_bw(crtc);
		पूर्ण अन्यथा अणु
			trace_dpu_crtc_frame_event_more_pending(DRMID(crtc),
								fevent->event);
		पूर्ण

		अगर (fevent->event & DPU_ENCODER_FRAME_EVENT_DONE)
			dpu_core_perf_crtc_update(crtc, 0, false);

		अगर (fevent->event & (DPU_ENCODER_FRAME_EVENT_DONE
					| DPU_ENCODER_FRAME_EVENT_ERROR))
			frame_करोne = true;
	पूर्ण

	अगर (fevent->event & DPU_ENCODER_FRAME_EVENT_PANEL_DEAD)
		DPU_ERROR("crtc%d ts:%lld received panel dead event\n",
				crtc->base.id, kसमय_प्रकारo_ns(fevent->ts));

	अगर (frame_करोne)
		complete_all(&dpu_crtc->frame_करोne_comp);

	spin_lock_irqsave(&dpu_crtc->spin_lock, flags);
	list_add_tail(&fevent->list, &dpu_crtc->frame_event_list);
	spin_unlock_irqrestore(&dpu_crtc->spin_lock, flags);
	DPU_ATRACE_END("crtc_frame_event");
पूर्ण

/*
 * dpu_crtc_frame_event_cb - crtc frame event callback API. CRTC module
 * रेजिस्टरs this API to encoder क्रम all frame event callbacks like
 * frame_error, frame_करोne, idle_समयout, etc. Encoder may call dअगरferent events
 * from dअगरferent context - IRQ, user thपढ़ो, commit_thपढ़ो, etc. Each event
 * should be carefully reviewed and should be processed in proper task context
 * to aव्योम schedulin delay or properly manage the irq context's bottom half
 * processing.
 */
अटल व्योम dpu_crtc_frame_event_cb(व्योम *data, u32 event)
अणु
	काष्ठा drm_crtc *crtc = (काष्ठा drm_crtc *)data;
	काष्ठा dpu_crtc *dpu_crtc;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_crtc_frame_event *fevent;
	अचिन्हित दीर्घ flags;
	u32 crtc_id;

	/* Nothing to करो on idle event */
	अगर (event & DPU_ENCODER_FRAME_EVENT_IDLE)
		वापस;

	dpu_crtc = to_dpu_crtc(crtc);
	priv = crtc->dev->dev_निजी;
	crtc_id = drm_crtc_index(crtc);

	trace_dpu_crtc_frame_event_cb(DRMID(crtc), event);

	spin_lock_irqsave(&dpu_crtc->spin_lock, flags);
	fevent = list_first_entry_or_null(&dpu_crtc->frame_event_list,
			काष्ठा dpu_crtc_frame_event, list);
	अगर (fevent)
		list_del_init(&fevent->list);
	spin_unlock_irqrestore(&dpu_crtc->spin_lock, flags);

	अगर (!fevent) अणु
		DRM_ERROR_RATELIMITED("crtc%d event %d overflow\n", crtc->base.id, event);
		वापस;
	पूर्ण

	fevent->event = event;
	fevent->crtc = crtc;
	fevent->ts = kसमय_get();
	kthपढ़ो_queue_work(priv->event_thपढ़ो[crtc_id].worker, &fevent->work);
पूर्ण

व्योम dpu_crtc_complete_commit(काष्ठा drm_crtc *crtc)
अणु
	trace_dpu_crtc_complete_commit(DRMID(crtc));
	_dpu_crtc_complete_flip(crtc);
पूर्ण

अटल व्योम _dpu_crtc_setup_lm_bounds(काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state)
अणु
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(state);
	काष्ठा drm_display_mode *adj_mode = &state->adjusted_mode;
	u32 crtc_split_width = adj_mode->hdisplay / cstate->num_mixers;
	पूर्णांक i;

	क्रम (i = 0; i < cstate->num_mixers; i++) अणु
		काष्ठा drm_rect *r = &cstate->lm_bounds[i];
		r->x1 = crtc_split_width * i;
		r->y1 = 0;
		r->x2 = r->x1 + crtc_split_width;
		r->y2 = adj_mode->vdisplay;

		trace_dpu_crtc_setup_lm_bounds(DRMID(crtc), i, r);
	पूर्ण
पूर्ण

अटल व्योम _dpu_crtc_get_pcc_coeff(काष्ठा drm_crtc_state *state,
		काष्ठा dpu_hw_pcc_cfg *cfg)
अणु
	काष्ठा drm_color_cपंचांग *cपंचांग;

	स_रखो(cfg, 0, माप(काष्ठा dpu_hw_pcc_cfg));

	cपंचांग = (काष्ठा drm_color_cपंचांग *)state->cपंचांग->data;

	अगर (!cपंचांग)
		वापस;

	cfg->r.r = CONVERT_S3_15(cपंचांग->matrix[0]);
	cfg->g.r = CONVERT_S3_15(cपंचांग->matrix[1]);
	cfg->b.r = CONVERT_S3_15(cपंचांग->matrix[2]);

	cfg->r.g = CONVERT_S3_15(cपंचांग->matrix[3]);
	cfg->g.g = CONVERT_S3_15(cपंचांग->matrix[4]);
	cfg->b.g = CONVERT_S3_15(cपंचांग->matrix[5]);

	cfg->r.b = CONVERT_S3_15(cपंचांग->matrix[6]);
	cfg->g.b = CONVERT_S3_15(cपंचांग->matrix[7]);
	cfg->b.b = CONVERT_S3_15(cपंचांग->matrix[8]);
पूर्ण

अटल व्योम _dpu_crtc_setup_cp_blocks(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *state = crtc->state;
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);
	काष्ठा dpu_crtc_mixer *mixer = cstate->mixers;
	काष्ठा dpu_hw_pcc_cfg cfg;
	काष्ठा dpu_hw_ctl *ctl;
	काष्ठा dpu_hw_dspp *dspp;
	पूर्णांक i;


	अगर (!state->color_mgmt_changed)
		वापस;

	क्रम (i = 0; i < cstate->num_mixers; i++) अणु
		ctl = mixer[i].lm_ctl;
		dspp = mixer[i].hw_dspp;

		अगर (!dspp || !dspp->ops.setup_pcc)
			जारी;

		अगर (!state->cपंचांग) अणु
			dspp->ops.setup_pcc(dspp, शून्य);
		पूर्ण अन्यथा अणु
			_dpu_crtc_get_pcc_coeff(state, &cfg);
			dspp->ops.setup_pcc(dspp, &cfg);
		पूर्ण

		mixer[i].flush_mask |= ctl->ops.get_biपंचांगask_dspp(ctl,
			mixer[i].hw_dspp->idx);

		/* stage config flush mask */
		ctl->ops.update_pending_flush(ctl, mixer[i].flush_mask);

		DPU_DEBUG("lm %d, ctl %d, flush mask 0x%x\n",
			mixer[i].hw_lm->idx - DSPP_0,
			ctl->idx - CTL_0,
			mixer[i].flush_mask);
	पूर्ण
पूर्ण

अटल व्योम dpu_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);
	काष्ठा drm_encoder *encoder;

	अगर (!crtc->state->enable) अणु
		DPU_DEBUG("crtc%d -> enable %d, skip atomic_begin\n",
				crtc->base.id, crtc->state->enable);
		वापस;
	पूर्ण

	DPU_DEBUG("crtc%d\n", crtc->base.id);

	_dpu_crtc_setup_lm_bounds(crtc, crtc->state);

	/* encoder will trigger pending mask now */
	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask)
		dpu_encoder_trigger_kickoff_pending(encoder);

	/*
	 * If no mixers have been allocated in dpu_crtc_atomic_check(),
	 * it means we are trying to flush a CRTC whose state is disabled:
	 * nothing अन्यथा needs to be करोne.
	 */
	अगर (unlikely(!cstate->num_mixers))
		वापस;

	_dpu_crtc_blend_setup(crtc);

	_dpu_crtc_setup_cp_blocks(crtc);

	/*
	 * PP_DONE irq is only used by command mode क्रम now.
	 * It is better to request pending beक्रमe FLUSH and START trigger
	 * to make sure no pp_करोne irq missed.
	 * This is safe because no pp_करोne will happen beक्रमe SW trigger
	 * in command mode.
	 */
पूर्ण

अटल व्योम dpu_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dpu_crtc *dpu_crtc;
	काष्ठा drm_device *dev;
	काष्ठा drm_plane *plane;
	काष्ठा msm_drm_निजी *priv;
	अचिन्हित दीर्घ flags;
	काष्ठा dpu_crtc_state *cstate;

	अगर (!crtc->state->enable) अणु
		DPU_DEBUG("crtc%d -> enable %d, skip atomic_flush\n",
				crtc->base.id, crtc->state->enable);
		वापस;
	पूर्ण

	DPU_DEBUG("crtc%d\n", crtc->base.id);

	dpu_crtc = to_dpu_crtc(crtc);
	cstate = to_dpu_crtc_state(crtc->state);
	dev = crtc->dev;
	priv = dev->dev_निजी;

	अगर (crtc->index >= ARRAY_SIZE(priv->event_thपढ़ो)) अणु
		DPU_ERROR("invalid crtc index[%d]\n", crtc->index);
		वापस;
	पूर्ण

	WARN_ON(dpu_crtc->event);
	spin_lock_irqsave(&dev->event_lock, flags);
	dpu_crtc->event = crtc->state->event;
	crtc->state->event = शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/*
	 * If no mixers has been allocated in dpu_crtc_atomic_check(),
	 * it means we are trying to flush a CRTC whose state is disabled:
	 * nothing अन्यथा needs to be करोne.
	 */
	अगर (unlikely(!cstate->num_mixers))
		वापस;

	/* update perक्रमmance setting beक्रमe crtc kickoff */
	dpu_core_perf_crtc_update(crtc, 1, false);

	/*
	 * Final plane updates: Give each plane a chance to complete all
	 *                      required ग_लिखोs/flushing beक्रमe crtc's "flush
	 *                      everything" call below.
	 */
	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		अगर (dpu_crtc->smmu_state.transition_error)
			dpu_plane_set_error(plane, true);
		dpu_plane_flush(plane);
	पूर्ण

	/* Kickoff will be scheduled by outer layer */
पूर्ण

/**
 * dpu_crtc_destroy_state - state destroy hook
 * @crtc: drm CRTC
 * @state: CRTC state object to release
 */
अटल व्योम dpu_crtc_destroy_state(काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state)
अणु
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(state);

	DPU_DEBUG("crtc%d\n", crtc->base.id);

	__drm_atomic_helper_crtc_destroy_state(state);

	kमुक्त(cstate);
पूर्ण

अटल पूर्णांक _dpu_crtc_रुको_क्रम_frame_करोne(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	पूर्णांक ret, rc = 0;

	अगर (!atomic_पढ़ो(&dpu_crtc->frame_pending)) अणु
		DPU_DEBUG("no frames pending\n");
		वापस 0;
	पूर्ण

	DPU_ATRACE_BEGIN("frame done completion wait");
	ret = रुको_क्रम_completion_समयout(&dpu_crtc->frame_करोne_comp,
			msecs_to_jअगरfies(DPU_CRTC_FRAME_DONE_TIMEOUT_MS));
	अगर (!ret) अणु
		DRM_ERROR("frame done wait timed out, ret:%d\n", ret);
		rc = -ETIMEDOUT;
	पूर्ण
	DPU_ATRACE_END("frame done completion wait");

	वापस rc;
पूर्ण

व्योम dpu_crtc_commit_kickoff(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा dpu_kms *dpu_kms = _dpu_crtc_get_kms(crtc);
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);

	/*
	 * If no mixers has been allocated in dpu_crtc_atomic_check(),
	 * it means we are trying to start a CRTC whose state is disabled:
	 * nothing अन्यथा needs to be करोne.
	 */
	अगर (unlikely(!cstate->num_mixers))
		वापस;

	DPU_ATRACE_BEGIN("crtc_commit");

	/*
	 * Encoder will flush/start now, unless it has a tx pending. If so, it
	 * may delay and flush at an irq event (e.g. ppकरोne)
	 */
	drm_क्रम_each_encoder_mask(encoder, crtc->dev,
				  crtc->state->encoder_mask)
		dpu_encoder_prepare_क्रम_kickoff(encoder);

	अगर (atomic_inc_वापस(&dpu_crtc->frame_pending) == 1) अणु
		/* acquire bandwidth and other resources */
		DPU_DEBUG("crtc%d first commit\n", crtc->base.id);
	पूर्ण अन्यथा
		DPU_DEBUG("crtc%d commit\n", crtc->base.id);

	dpu_crtc->play_count++;

	dpu_vbअगर_clear_errors(dpu_kms);

	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask)
		dpu_encoder_kickoff(encoder);

	reinit_completion(&dpu_crtc->frame_करोne_comp);
	DPU_ATRACE_END("crtc_commit");
पूर्ण

अटल व्योम dpu_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc_state *cstate = kzalloc(माप(*cstate), GFP_KERNEL);

	अगर (crtc->state)
		dpu_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &cstate->base);
पूर्ण

/**
 * dpu_crtc_duplicate_state - state duplicate hook
 * @crtc: Poपूर्णांकer to drm crtc काष्ठाure
 */
अटल काष्ठा drm_crtc_state *dpu_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc_state *cstate, *old_cstate = to_dpu_crtc_state(crtc->state);

	cstate = kmemdup(old_cstate, माप(*old_cstate), GFP_KERNEL);
	अगर (!cstate) अणु
		DPU_ERROR("failed to allocate state\n");
		वापस शून्य;
	पूर्ण

	/* duplicate base helper */
	__drm_atomic_helper_crtc_duplicate_state(crtc, &cstate->base);

	वापस &cstate->base;
पूर्ण

अटल व्योम dpu_crtc_disable(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc->state);
	काष्ठा drm_encoder *encoder;
	अचिन्हित दीर्घ flags;
	bool release_bandwidth = false;

	DRM_DEBUG_KMS("crtc%d\n", crtc->base.id);

	/* Disable/save vblank irq handling */
	drm_crtc_vblank_off(crtc);

	drm_क्रम_each_encoder_mask(encoder, crtc->dev,
				  old_crtc_state->encoder_mask) अणु
		/* in video mode, we hold an extra bandwidth reference
		 * as we cannot drop bandwidth at frame-करोne अगर any
		 * crtc is being used in video mode.
		 */
		अगर (dpu_encoder_get_पूर्णांकf_mode(encoder) == INTF_MODE_VIDEO)
			release_bandwidth = true;
		dpu_encoder_assign_crtc(encoder, शून्य);
	पूर्ण

	/* रुको क्रम frame_event_करोne completion */
	अगर (_dpu_crtc_रुको_क्रम_frame_करोne(crtc))
		DPU_ERROR("crtc%d wait for frame done failed;frame_pending%d\n",
				crtc->base.id,
				atomic_पढ़ो(&dpu_crtc->frame_pending));

	trace_dpu_crtc_disable(DRMID(crtc), false, dpu_crtc);
	dpu_crtc->enabled = false;

	अगर (atomic_पढ़ो(&dpu_crtc->frame_pending)) अणु
		trace_dpu_crtc_disable_frame_pending(DRMID(crtc),
				     atomic_पढ़ो(&dpu_crtc->frame_pending));
		अगर (release_bandwidth)
			dpu_core_perf_crtc_release_bw(crtc);
		atomic_set(&dpu_crtc->frame_pending, 0);
	पूर्ण

	dpu_core_perf_crtc_update(crtc, 0, true);

	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask)
		dpu_encoder_रेजिस्टर_frame_event_callback(encoder, शून्य, शून्य);

	स_रखो(cstate->mixers, 0, माप(cstate->mixers));
	cstate->num_mixers = 0;

	/* disable clk & bw control until clk & bw properties are set */
	cstate->bw_control = false;
	cstate->bw_split_vote = false;

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	पूर्ण

	pm_runसमय_put_sync(crtc->dev->dev);
पूर्ण

अटल व्योम dpu_crtc_enable(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा drm_encoder *encoder;
	bool request_bandwidth = false;

	pm_runसमय_get_sync(crtc->dev->dev);

	DRM_DEBUG_KMS("crtc%d\n", crtc->base.id);

	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask) अणु
		/* in video mode, we hold an extra bandwidth reference
		 * as we cannot drop bandwidth at frame-करोne अगर any
		 * crtc is being used in video mode.
		 */
		अगर (dpu_encoder_get_पूर्णांकf_mode(encoder) == INTF_MODE_VIDEO)
			request_bandwidth = true;
		dpu_encoder_रेजिस्टर_frame_event_callback(encoder,
				dpu_crtc_frame_event_cb, (व्योम *)crtc);
	पूर्ण

	अगर (request_bandwidth)
		atomic_inc(&_dpu_crtc_get_kms(crtc)->bandwidth_ref);

	trace_dpu_crtc_enable(DRMID(crtc), true, dpu_crtc);
	dpu_crtc->enabled = true;

	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask)
		dpu_encoder_assign_crtc(encoder, crtc);

	/* Enable/restore vblank irq handling */
	drm_crtc_vblank_on(crtc);
पूर्ण

काष्ठा plane_state अणु
	काष्ठा dpu_plane_state *dpu_pstate;
	स्थिर काष्ठा drm_plane_state *drm_pstate;
	पूर्णांक stage;
	u32 pipe_id;
पूर्ण;

अटल पूर्णांक dpu_crtc_atomic_check(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा dpu_crtc_state *cstate = to_dpu_crtc_state(crtc_state);
	काष्ठा plane_state *pstates;

	स्थिर काष्ठा drm_plane_state *pstate;
	काष्ठा drm_plane *plane;
	काष्ठा drm_display_mode *mode;

	पूर्णांक cnt = 0, rc = 0, mixer_width = 0, i, z_pos;

	काष्ठा dpu_multirect_plane_states multirect_plane[DPU_STAGE_MAX * 2];
	पूर्णांक multirect_count = 0;
	स्थिर काष्ठा drm_plane_state *pipe_staged[SSPP_MAX];
	पूर्णांक left_zpos_cnt = 0, right_zpos_cnt = 0;
	काष्ठा drm_rect crtc_rect = अणु 0 पूर्ण;

	pstates = kzalloc(माप(*pstates) * DPU_STAGE_MAX * 4, GFP_KERNEL);

	अगर (!crtc_state->enable || !crtc_state->active) अणु
		DPU_DEBUG("crtc%d -> enable %d, active %d, skip atomic_check\n",
				crtc->base.id, crtc_state->enable,
				crtc_state->active);
		स_रखो(&cstate->new_perf, 0, माप(cstate->new_perf));
		जाओ end;
	पूर्ण

	mode = &crtc_state->adjusted_mode;
	DPU_DEBUG("%s: check\n", dpu_crtc->name);

	/* क्रमce a full mode set अगर active state changed */
	अगर (crtc_state->active_changed)
		crtc_state->mode_changed = true;

	स_रखो(pipe_staged, 0, माप(pipe_staged));

	अगर (cstate->num_mixers) अणु
		mixer_width = mode->hdisplay / cstate->num_mixers;

		_dpu_crtc_setup_lm_bounds(crtc, crtc_state);
	पूर्ण

	crtc_rect.x2 = mode->hdisplay;
	crtc_rect.y2 = mode->vdisplay;

	 /* get plane state क्रम all drm planes associated with crtc state */
	drm_atomic_crtc_state_क्रम_each_plane_state(plane, pstate, crtc_state) अणु
		काष्ठा drm_rect dst, clip = crtc_rect;

		अगर (IS_ERR_OR_शून्य(pstate)) अणु
			rc = PTR_ERR(pstate);
			DPU_ERROR("%s: failed to get plane%d state, %d\n",
					dpu_crtc->name, plane->base.id, rc);
			जाओ end;
		पूर्ण
		अगर (cnt >= DPU_STAGE_MAX * 4)
			जारी;

		pstates[cnt].dpu_pstate = to_dpu_plane_state(pstate);
		pstates[cnt].drm_pstate = pstate;
		pstates[cnt].stage = pstate->normalized_zpos;
		pstates[cnt].pipe_id = dpu_plane_pipe(plane);

		अगर (pipe_staged[pstates[cnt].pipe_id]) अणु
			multirect_plane[multirect_count].r0 =
				pipe_staged[pstates[cnt].pipe_id];
			multirect_plane[multirect_count].r1 = pstate;
			multirect_count++;

			pipe_staged[pstates[cnt].pipe_id] = शून्य;
		पूर्ण अन्यथा अणु
			pipe_staged[pstates[cnt].pipe_id] = pstate;
		पूर्ण

		cnt++;

		dst = drm_plane_state_dest(pstate);
		अगर (!drm_rect_पूर्णांकersect(&clip, &dst)) अणु
			DPU_ERROR("invalid vertical/horizontal destination\n");
			DPU_ERROR("display: " DRM_RECT_FMT " plane: "
				  DRM_RECT_FMT "\n", DRM_RECT_ARG(&crtc_rect),
				  DRM_RECT_ARG(&dst));
			rc = -E2BIG;
			जाओ end;
		पूर्ण
	पूर्ण

	क्रम (i = 1; i < SSPP_MAX; i++) अणु
		अगर (pipe_staged[i]) अणु
			dpu_plane_clear_multirect(pipe_staged[i]);

			अगर (is_dpu_plane_भव(pipe_staged[i]->plane)) अणु
				DPU_ERROR(
					"r1 only virt plane:%d not supported\n",
					pipe_staged[i]->plane->base.id);
				rc  = -EINVAL;
				जाओ end;
			पूर्ण
		पूर्ण
	पूर्ण

	z_pos = -1;
	क्रम (i = 0; i < cnt; i++) अणु
		/* reset counts at every new blend stage */
		अगर (pstates[i].stage != z_pos) अणु
			left_zpos_cnt = 0;
			right_zpos_cnt = 0;
			z_pos = pstates[i].stage;
		पूर्ण

		/* verअगरy z_pos setting beक्रमe using it */
		अगर (z_pos >= DPU_STAGE_MAX - DPU_STAGE_0) अणु
			DPU_ERROR("> %d plane stages assigned\n",
					DPU_STAGE_MAX - DPU_STAGE_0);
			rc = -EINVAL;
			जाओ end;
		पूर्ण अन्यथा अगर (pstates[i].drm_pstate->crtc_x < mixer_width) अणु
			अगर (left_zpos_cnt == 2) अणु
				DPU_ERROR("> 2 planes @ stage %d on left\n",
					z_pos);
				rc = -EINVAL;
				जाओ end;
			पूर्ण
			left_zpos_cnt++;

		पूर्ण अन्यथा अणु
			अगर (right_zpos_cnt == 2) अणु
				DPU_ERROR("> 2 planes @ stage %d on right\n",
					z_pos);
				rc = -EINVAL;
				जाओ end;
			पूर्ण
			right_zpos_cnt++;
		पूर्ण

		pstates[i].dpu_pstate->stage = z_pos + DPU_STAGE_0;
		DPU_DEBUG("%s: zpos %d\n", dpu_crtc->name, z_pos);
	पूर्ण

	क्रम (i = 0; i < multirect_count; i++) अणु
		अगर (dpu_plane_validate_multirect_v2(&multirect_plane[i])) अणु
			DPU_ERROR(
			"multirect validation failed for planes (%d - %d)\n",
					multirect_plane[i].r0->plane->base.id,
					multirect_plane[i].r1->plane->base.id);
			rc = -EINVAL;
			जाओ end;
		पूर्ण
	पूर्ण

	atomic_inc(&_dpu_crtc_get_kms(crtc)->bandwidth_ref);

	rc = dpu_core_perf_crtc_check(crtc, crtc_state);
	अगर (rc) अणु
		DPU_ERROR("crtc%d failed performance check %d\n",
				crtc->base.id, rc);
		जाओ end;
	पूर्ण

	/* validate source split:
	 * use pstates sorted by stage to check planes on same stage
	 * we assume that all pipes are in source split so its valid to compare
	 * without taking पूर्णांकo account left/right mixer placement
	 */
	क्रम (i = 1; i < cnt; i++) अणु
		काष्ठा plane_state *prv_pstate, *cur_pstate;
		काष्ठा drm_rect left_rect, right_rect;
		पूर्णांक32_t left_pid, right_pid;
		पूर्णांक32_t stage;

		prv_pstate = &pstates[i - 1];
		cur_pstate = &pstates[i];
		अगर (prv_pstate->stage != cur_pstate->stage)
			जारी;

		stage = cur_pstate->stage;

		left_pid = prv_pstate->dpu_pstate->base.plane->base.id;
		left_rect = drm_plane_state_dest(prv_pstate->drm_pstate);

		right_pid = cur_pstate->dpu_pstate->base.plane->base.id;
		right_rect = drm_plane_state_dest(cur_pstate->drm_pstate);

		अगर (right_rect.x1 < left_rect.x1) अणु
			swap(left_pid, right_pid);
			swap(left_rect, right_rect);
		पूर्ण

		/**
		 * - planes are क्रमागतerated in pipe-priority order such that
		 *   planes with lower drm_id must be left-most in a shared
		 *   blend-stage when using source split.
		 * - planes in source split must be contiguous in width
		 * - planes in source split must have same dest yoff and height
		 */
		अगर (right_pid < left_pid) अणु
			DPU_ERROR(
				"invalid src split cfg. priority mismatch. stage: %d left: %d right: %d\n",
				stage, left_pid, right_pid);
			rc = -EINVAL;
			जाओ end;
		पूर्ण अन्यथा अगर (right_rect.x1 != drm_rect_width(&left_rect)) अणु
			DPU_ERROR("non-contiguous coordinates for src split. "
				  "stage: %d left: " DRM_RECT_FMT " right: "
				  DRM_RECT_FMT "\n", stage,
				  DRM_RECT_ARG(&left_rect),
				  DRM_RECT_ARG(&right_rect));
			rc = -EINVAL;
			जाओ end;
		पूर्ण अन्यथा अगर (left_rect.y1 != right_rect.y1 ||
			   drm_rect_height(&left_rect) != drm_rect_height(&right_rect)) अणु
			DPU_ERROR("source split at stage: %d. invalid "
				  "yoff/height: left: " DRM_RECT_FMT " right: "
				  DRM_RECT_FMT "\n", stage,
				  DRM_RECT_ARG(&left_rect),
				  DRM_RECT_ARG(&right_rect));
			rc = -EINVAL;
			जाओ end;
		पूर्ण
	पूर्ण

end:
	kमुक्त(pstates);
	वापस rc;
पूर्ण

पूर्णांक dpu_crtc_vblank(काष्ठा drm_crtc *crtc, bool en)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	काष्ठा drm_encoder *enc;

	trace_dpu_crtc_vblank(DRMID(&dpu_crtc->base), en, dpu_crtc);

	/*
	 * Normally we would iterate through encoder_mask in crtc state to find
	 * attached encoders. In this हाल, we might be disabling vblank _after_
	 * encoder_mask has been cleared.
	 *
	 * Instead, we "assign" a crtc to the encoder in enable and clear it in
	 * disable (which is also after encoder_mask is cleared). So instead of
	 * using encoder mask, we'll ask the encoder to toggle itself iff it's
	 * currently asचिन्हित to our crtc.
	 *
	 * Note also that this function cannot be called जबतक crtc is disabled
	 * since we use drm_crtc_vblank_on/off. So we करोn't need to worry
	 * about the asचिन्हित crtcs being inconsistent with the current state
	 * (which means no need to worry about modeset locks).
	 */
	list_क्रम_each_entry(enc, &crtc->dev->mode_config.encoder_list, head) अणु
		trace_dpu_crtc_vblank_enable(DRMID(crtc), DRMID(enc), en,
					     dpu_crtc);

		dpu_encoder_toggle_vblank_क्रम_crtc(enc, crtc, en);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक _dpu_debugfs_status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा dpu_crtc *dpu_crtc;
	काष्ठा dpu_plane_state *pstate = शून्य;
	काष्ठा dpu_crtc_mixer *m;

	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_plane_state *state;
	काष्ठा dpu_crtc_state *cstate;

	पूर्णांक i, out_width;

	dpu_crtc = s->निजी;
	crtc = &dpu_crtc->base;

	drm_modeset_lock_all(crtc->dev);
	cstate = to_dpu_crtc_state(crtc->state);

	mode = &crtc->state->adjusted_mode;
	out_width = mode->hdisplay / cstate->num_mixers;

	seq_म_लिखो(s, "crtc:%d width:%d height:%d\n", crtc->base.id,
				mode->hdisplay, mode->vdisplay);

	seq_माला_दो(s, "\n");

	क्रम (i = 0; i < cstate->num_mixers; ++i) अणु
		m = &cstate->mixers[i];
		seq_म_लिखो(s, "\tmixer:%d ctl:%d width:%d height:%d\n",
			m->hw_lm->idx - LM_0, m->lm_ctl->idx - CTL_0,
			out_width, mode->vdisplay);
	पूर्ण

	seq_माला_दो(s, "\n");

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		pstate = to_dpu_plane_state(plane->state);
		state = plane->state;

		अगर (!pstate || !state)
			जारी;

		seq_म_लिखो(s, "\tplane:%u stage:%d\n", plane->base.id,
			pstate->stage);

		अगर (plane->state->fb) अणु
			fb = plane->state->fb;

			seq_म_लिखो(s, "\tfb:%d image format:%4.4s wxh:%ux%u ",
				fb->base.id, (अक्षर *) &fb->क्रमmat->क्रमmat,
				fb->width, fb->height);
			क्रम (i = 0; i < ARRAY_SIZE(fb->क्रमmat->cpp); ++i)
				seq_म_लिखो(s, "cpp[%d]:%u ",
						i, fb->क्रमmat->cpp[i]);
			seq_माला_दो(s, "\n\t");

			seq_म_लिखो(s, "modifier:%8llu ", fb->modअगरier);
			seq_माला_दो(s, "\n");

			seq_माला_दो(s, "\t");
			क्रम (i = 0; i < ARRAY_SIZE(fb->pitches); i++)
				seq_म_लिखो(s, "pitches[%d]:%8u ", i,
							fb->pitches[i]);
			seq_माला_दो(s, "\n");

			seq_माला_दो(s, "\t");
			क्रम (i = 0; i < ARRAY_SIZE(fb->offsets); i++)
				seq_म_लिखो(s, "offsets[%d]:%8u ", i,
							fb->offsets[i]);
			seq_माला_दो(s, "\n");
		पूर्ण

		seq_म_लिखो(s, "\tsrc_x:%4d src_y:%4d src_w:%4d src_h:%4d\n",
			state->src_x, state->src_y, state->src_w, state->src_h);

		seq_म_लिखो(s, "\tdst x:%4d dst_y:%4d dst_w:%4d dst_h:%4d\n",
			state->crtc_x, state->crtc_y, state->crtc_w,
			state->crtc_h);
		seq_म_लिखो(s, "\tmultirect: mode: %d index: %d\n",
			pstate->multirect_mode, pstate->multirect_index);

		seq_माला_दो(s, "\n");
	पूर्ण
	अगर (dpu_crtc->vblank_cb_count) अणु
		kसमय_प्रकार dअगरf = kसमय_sub(kसमय_get(), dpu_crtc->vblank_cb_समय);
		s64 dअगरf_ms = kसमय_प्रकारo_ms(dअगरf);
		s64 fps = dअगरf_ms ? भाग_s64(
				dpu_crtc->vblank_cb_count * 1000, dअगरf_ms) : 0;

		seq_म_लिखो(s,
			"vblank fps:%lld count:%u total:%llums total_framecount:%llu\n",
				fps, dpu_crtc->vblank_cb_count,
				kसमय_प्रकारo_ms(dअगरf), dpu_crtc->play_count);

		/* reset समय & count क्रम next measurement */
		dpu_crtc->vblank_cb_count = 0;
		dpu_crtc->vblank_cb_समय = kसमय_set(0, 0);
	पूर्ण

	drm_modeset_unlock_all(crtc->dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(_dpu_debugfs_status);

अटल पूर्णांक dpu_crtc_debugfs_state_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा drm_crtc *crtc = (काष्ठा drm_crtc *) s->निजी;
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	seq_म_लिखो(s, "client type: %d\n", dpu_crtc_get_client_type(crtc));
	seq_म_लिखो(s, "intf_mode: %d\n", dpu_crtc_get_पूर्णांकf_mode(crtc));
	seq_म_लिखो(s, "core_clk_rate: %llu\n",
			dpu_crtc->cur_perf.core_clk_rate);
	seq_म_लिखो(s, "bw_ctl: %llu\n", dpu_crtc->cur_perf.bw_ctl);
	seq_म_लिखो(s, "max_per_pipe_ib: %llu\n",
				dpu_crtc->cur_perf.max_per_pipe_ib);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dpu_crtc_debugfs_state);

अटल पूर्णांक _dpu_crtc_init_debugfs(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	dpu_crtc->debugfs_root = debugfs_create_dir(dpu_crtc->name,
			crtc->dev->primary->debugfs_root);

	debugfs_create_file("status", 0400,
			dpu_crtc->debugfs_root,
			dpu_crtc, &_dpu_debugfs_status_fops);
	debugfs_create_file("state", 0600,
			dpu_crtc->debugfs_root,
			&dpu_crtc->base,
			&dpu_crtc_debugfs_state_fops);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक _dpu_crtc_init_debugfs(काष्ठा drm_crtc *crtc)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक dpu_crtc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	वापस _dpu_crtc_init_debugfs(crtc);
पूर्ण

अटल व्योम dpu_crtc_early_unरेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	debugfs_हटाओ_recursive(dpu_crtc->debugfs_root);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs dpu_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = dpu_crtc_destroy,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = dpu_crtc_reset,
	.atomic_duplicate_state = dpu_crtc_duplicate_state,
	.atomic_destroy_state = dpu_crtc_destroy_state,
	.late_रेजिस्टर = dpu_crtc_late_रेजिस्टर,
	.early_unरेजिस्टर = dpu_crtc_early_unरेजिस्टर,
	.enable_vblank  = msm_crtc_enable_vblank,
	.disable_vblank = msm_crtc_disable_vblank,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
	.get_vblank_counter = dpu_crtc_get_vblank_counter,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs dpu_crtc_helper_funcs = अणु
	.atomic_disable = dpu_crtc_disable,
	.atomic_enable = dpu_crtc_enable,
	.atomic_check = dpu_crtc_atomic_check,
	.atomic_begin = dpu_crtc_atomic_begin,
	.atomic_flush = dpu_crtc_atomic_flush,
	.get_scanout_position = dpu_crtc_get_scanout_position,
पूर्ण;

/* initialize crtc */
काष्ठा drm_crtc *dpu_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
				काष्ठा drm_plane *cursor)
अणु
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा dpu_crtc *dpu_crtc = शून्य;
	पूर्णांक i;

	dpu_crtc = kzalloc(माप(*dpu_crtc), GFP_KERNEL);
	अगर (!dpu_crtc)
		वापस ERR_PTR(-ENOMEM);

	crtc = &dpu_crtc->base;
	crtc->dev = dev;

	spin_lock_init(&dpu_crtc->spin_lock);
	atomic_set(&dpu_crtc->frame_pending, 0);

	init_completion(&dpu_crtc->frame_करोne_comp);

	INIT_LIST_HEAD(&dpu_crtc->frame_event_list);

	क्रम (i = 0; i < ARRAY_SIZE(dpu_crtc->frame_events); i++) अणु
		INIT_LIST_HEAD(&dpu_crtc->frame_events[i].list);
		list_add(&dpu_crtc->frame_events[i].list,
				&dpu_crtc->frame_event_list);
		kthपढ़ो_init_work(&dpu_crtc->frame_events[i].work,
				dpu_crtc_frame_event_work);
	पूर्ण

	drm_crtc_init_with_planes(dev, crtc, plane, cursor, &dpu_crtc_funcs,
				शून्य);

	drm_crtc_helper_add(crtc, &dpu_crtc_helper_funcs);

	drm_crtc_enable_color_mgmt(crtc, 0, true, 0);

	/* save user मित्रly CRTC name क्रम later */
	snम_लिखो(dpu_crtc->name, DPU_CRTC_NAME_SIZE, "crtc%u", crtc->base.id);

	/* initialize event handling */
	spin_lock_init(&dpu_crtc->event_lock);

	DPU_DEBUG("%s: successfully initialized crtc\n", dpu_crtc->name);
	वापस crtc;
पूर्ण
