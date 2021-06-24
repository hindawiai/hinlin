<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__
#समावेश "dpu_encoder_phys.h"
#समावेश "dpu_hw_interrupts.h"
#समावेश "dpu_hw_merge3d.h"
#समावेश "dpu_core_irq.h"
#समावेश "dpu_formats.h"
#समावेश "dpu_trace.h"

#घोषणा DPU_DEBUG_VIDENC(e, fmt, ...) DPU_DEBUG("enc%d intf%d " fmt, \
		(e) && (e)->parent ? \
		(e)->parent->base.id : -1, \
		(e) && (e)->hw_पूर्णांकf ? \
		(e)->hw_पूर्णांकf->idx - INTF_0 : -1, ##__VA_ARGS__)

#घोषणा DPU_ERROR_VIDENC(e, fmt, ...) DPU_ERROR("enc%d intf%d " fmt, \
		(e) && (e)->parent ? \
		(e)->parent->base.id : -1, \
		(e) && (e)->hw_पूर्णांकf ? \
		(e)->hw_पूर्णांकf->idx - INTF_0 : -1, ##__VA_ARGS__)

#घोषणा to_dpu_encoder_phys_vid(x) \
	container_of(x, काष्ठा dpu_encoder_phys_vid, base)

अटल bool dpu_encoder_phys_vid_is_master(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	bool ret = false;

	अगर (phys_enc->split_role != ENC_ROLE_SLAVE)
		ret = true;

	वापस ret;
पूर्ण

अटल व्योम drm_mode_to_पूर्णांकf_timing_params(
		स्थिर काष्ठा dpu_encoder_phys *phys_enc,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा पूर्णांकf_timing_params *timing)
अणु
	स_रखो(timing, 0, माप(*timing));

	अगर ((mode->htotal < mode->hsync_end)
			|| (mode->hsync_start < mode->hdisplay)
			|| (mode->vtotal < mode->vsync_end)
			|| (mode->vsync_start < mode->vdisplay)
			|| (mode->hsync_end < mode->hsync_start)
			|| (mode->vsync_end < mode->vsync_start)) अणु
		DPU_ERROR(
		    "invalid params - hstart:%d,hend:%d,htot:%d,hdisplay:%d\n",
				mode->hsync_start, mode->hsync_end,
				mode->htotal, mode->hdisplay);
		DPU_ERROR("vstart:%d,vend:%d,vtot:%d,vdisplay:%d\n",
				mode->vsync_start, mode->vsync_end,
				mode->vtotal, mode->vdisplay);
		वापस;
	पूर्ण

	/*
	 * https://www.kernel.org/करोc/hपंचांगlकरोcs/drm/ch02s05.hपंचांगl
	 *  Active Region      Front Porch   Sync   Back Porch
	 * <-----------------><------------><-----><----------->
	 * <- [hv]display --->
	 * <--------- [hv]sync_start ------>
	 * <----------------- [hv]sync_end ------->
	 * <---------------------------- [hv]total ------------->
	 */
	timing->width = mode->hdisplay;	/* active width */
	timing->height = mode->vdisplay;	/* active height */
	timing->xres = timing->width;
	timing->yres = timing->height;
	timing->h_back_porch = mode->htotal - mode->hsync_end;
	timing->h_front_porch = mode->hsync_start - mode->hdisplay;
	timing->v_back_porch = mode->vtotal - mode->vsync_end;
	timing->v_front_porch = mode->vsync_start - mode->vdisplay;
	timing->hsync_pulse_width = mode->hsync_end - mode->hsync_start;
	timing->vsync_pulse_width = mode->vsync_end - mode->vsync_start;
	timing->hsync_polarity = (mode->flags & DRM_MODE_FLAG_NHSYNC) ? 1 : 0;
	timing->vsync_polarity = (mode->flags & DRM_MODE_FLAG_NVSYNC) ? 1 : 0;
	timing->border_clr = 0;
	timing->underflow_clr = 0xff;
	timing->hsync_skew = mode->hskew;

	/* DSI controller cannot handle active-low sync संकेतs. */
	अगर (phys_enc->hw_पूर्णांकf->cap->type == INTF_DSI) अणु
		timing->hsync_polarity = 0;
		timing->vsync_polarity = 0;
	पूर्ण

	/*
	 * For edp only:
	 * DISPLAY_V_START = (VBP * HCYCLE) + HBP
	 * DISPLAY_V_END = (VBP + VACTIVE) * HCYCLE - 1 - HFP
	 */
	/*
	 * अगर (vid_enc->hw->cap->type == INTF_EDP) अणु
	 * display_v_start += mode->htotal - mode->hsync_start;
	 * display_v_end -= mode->hsync_start - mode->hdisplay;
	 * पूर्ण
	 */
	/* क्रम DP/EDP, Shअगरt timings to align it to bottom right */
	अगर ((phys_enc->hw_पूर्णांकf->cap->type == INTF_DP) ||
		(phys_enc->hw_पूर्णांकf->cap->type == INTF_EDP)) अणु
		timing->h_back_porch += timing->h_front_porch;
		timing->h_front_porch = 0;
		timing->v_back_porch += timing->v_front_porch;
		timing->v_front_porch = 0;
	पूर्ण
पूर्ण

अटल u32 get_horizontal_total(स्थिर काष्ठा पूर्णांकf_timing_params *timing)
अणु
	u32 active = timing->xres;
	u32 inactive =
	    timing->h_back_porch + timing->h_front_porch +
	    timing->hsync_pulse_width;
	वापस active + inactive;
पूर्ण

अटल u32 get_vertical_total(स्थिर काष्ठा पूर्णांकf_timing_params *timing)
अणु
	u32 active = timing->yres;
	u32 inactive =
	    timing->v_back_porch + timing->v_front_porch +
	    timing->vsync_pulse_width;
	वापस active + inactive;
पूर्ण

/*
 * programmable_fetch_get_num_lines:
 *	Number of fetch lines in vertical front porch
 * @timing: Poपूर्णांकer to the पूर्णांकf timing inक्रमmation क्रम the requested mode
 *
 * Returns the number of fetch lines in vertical front porch at which mdp
 * can start fetching the next frame.
 *
 * Number of needed prefetch lines is anything that cannot be असलorbed in the
 * start of frame समय (back porch + vsync pulse width).
 *
 * Some panels have very large VFP, however we only need a total number of
 * lines based on the chip worst हाल latencies.
 */
अटल u32 programmable_fetch_get_num_lines(
		काष्ठा dpu_encoder_phys *phys_enc,
		स्थिर काष्ठा पूर्णांकf_timing_params *timing)
अणु
	u32 worst_हाल_needed_lines =
	    phys_enc->hw_पूर्णांकf->cap->prog_fetch_lines_worst_हाल;
	u32 start_of_frame_lines =
	    timing->v_back_porch + timing->vsync_pulse_width;
	u32 needed_vfp_lines = worst_हाल_needed_lines - start_of_frame_lines;
	u32 actual_vfp_lines = 0;

	/* Fetch must be outside active lines, otherwise undefined. */
	अगर (start_of_frame_lines >= worst_हाल_needed_lines) अणु
		DPU_DEBUG_VIDENC(phys_enc,
				"prog fetch is not needed, large vbp+vsw\n");
		actual_vfp_lines = 0;
	पूर्ण अन्यथा अगर (timing->v_front_porch < needed_vfp_lines) अणु
		/* Warn fetch needed, but not enough porch in panel config */
		pr_warn_once
			("low vbp+vfp may lead to perf issues in some cases\n");
		DPU_DEBUG_VIDENC(phys_enc,
				"less vfp than fetch req, using entire vfp\n");
		actual_vfp_lines = timing->v_front_porch;
	पूर्ण अन्यथा अणु
		DPU_DEBUG_VIDENC(phys_enc, "room in vfp for needed prefetch\n");
		actual_vfp_lines = needed_vfp_lines;
	पूर्ण

	DPU_DEBUG_VIDENC(phys_enc,
		"v_front_porch %u v_back_porch %u vsync_pulse_width %u\n",
		timing->v_front_porch, timing->v_back_porch,
		timing->vsync_pulse_width);
	DPU_DEBUG_VIDENC(phys_enc,
		"wc_lines %u needed_vfp_lines %u actual_vfp_lines %u\n",
		worst_हाल_needed_lines, needed_vfp_lines, actual_vfp_lines);

	वापस actual_vfp_lines;
पूर्ण

/*
 * programmable_fetch_config: Programs HW to prefetch lines by offsetting
 *	the start of fetch पूर्णांकo the vertical front porch क्रम हालs where the
 *	vsync pulse width and vertical back porch समय is insufficient
 *
 *	Gets # of lines to pre-fetch, then calculate VSYNC counter value.
 *	HW layer requires VSYNC counter of first pixel of tgt VFP line.
 *
 * @timing: Poपूर्णांकer to the पूर्णांकf timing inक्रमmation क्रम the requested mode
 */
अटल व्योम programmable_fetch_config(काष्ठा dpu_encoder_phys *phys_enc,
				      स्थिर काष्ठा पूर्णांकf_timing_params *timing)
अणु
	काष्ठा पूर्णांकf_prog_fetch f = अणु 0 पूर्ण;
	u32 vfp_fetch_lines = 0;
	u32 horiz_total = 0;
	u32 vert_total = 0;
	u32 vfp_fetch_start_vsync_counter = 0;
	अचिन्हित दीर्घ lock_flags;

	अगर (WARN_ON_ONCE(!phys_enc->hw_पूर्णांकf->ops.setup_prg_fetch))
		वापस;

	vfp_fetch_lines = programmable_fetch_get_num_lines(phys_enc, timing);
	अगर (vfp_fetch_lines) अणु
		vert_total = get_vertical_total(timing);
		horiz_total = get_horizontal_total(timing);
		vfp_fetch_start_vsync_counter =
		    (vert_total - vfp_fetch_lines) * horiz_total + 1;
		f.enable = 1;
		f.fetch_start = vfp_fetch_start_vsync_counter;
	पूर्ण

	DPU_DEBUG_VIDENC(phys_enc,
		"vfp_fetch_lines %u vfp_fetch_start_vsync_counter %u\n",
		vfp_fetch_lines, vfp_fetch_start_vsync_counter);

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	phys_enc->hw_पूर्णांकf->ops.setup_prg_fetch(phys_enc->hw_पूर्णांकf, &f);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);
पूर्ण

अटल bool dpu_encoder_phys_vid_mode_fixup(
		काष्ठा dpu_encoder_phys *phys_enc,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adj_mode)
अणु
	DPU_DEBUG_VIDENC(phys_enc, "\n");

	/*
	 * Modअगरying mode has consequences when the mode comes back to us
	 */
	वापस true;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_setup_timing_engine(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा drm_display_mode mode;
	काष्ठा पूर्णांकf_timing_params timing_params = अणु 0 पूर्ण;
	स्थिर काष्ठा dpu_क्रमmat *fmt = शून्य;
	u32 fmt_fourcc = DRM_FORMAT_RGB888;
	अचिन्हित दीर्घ lock_flags;
	काष्ठा dpu_hw_पूर्णांकf_cfg पूर्णांकf_cfg = अणु 0 पूर्ण;

	अगर (!phys_enc->hw_ctl->ops.setup_पूर्णांकf_cfg) अणु
		DPU_ERROR("invalid encoder %d\n", phys_enc != शून्य);
		वापस;
	पूर्ण

	mode = phys_enc->cached_mode;
	अगर (!phys_enc->hw_पूर्णांकf->ops.setup_timing_gen) अणु
		DPU_ERROR("timing engine setup is not supported\n");
		वापस;
	पूर्ण

	DPU_DEBUG_VIDENC(phys_enc, "enabling mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(&mode);

	अगर (phys_enc->split_role != ENC_ROLE_SOLO) अणु
		mode.hdisplay >>= 1;
		mode.htotal >>= 1;
		mode.hsync_start >>= 1;
		mode.hsync_end >>= 1;

		DPU_DEBUG_VIDENC(phys_enc,
			"split_role %d, halve horizontal %d %d %d %d\n",
			phys_enc->split_role,
			mode.hdisplay, mode.htotal,
			mode.hsync_start, mode.hsync_end);
	पूर्ण

	drm_mode_to_पूर्णांकf_timing_params(phys_enc, &mode, &timing_params);

	fmt = dpu_get_dpu_क्रमmat(fmt_fourcc);
	DPU_DEBUG_VIDENC(phys_enc, "fmt_fourcc 0x%X\n", fmt_fourcc);

	पूर्णांकf_cfg.पूर्णांकf = phys_enc->hw_पूर्णांकf->idx;
	पूर्णांकf_cfg.पूर्णांकf_mode_sel = DPU_CTL_MODE_SEL_VID;
	पूर्णांकf_cfg.stream_sel = 0; /* Don't care value क्रम video mode */
	पूर्णांकf_cfg.mode_3d = dpu_encoder_helper_get_3d_blend_mode(phys_enc);
	अगर (phys_enc->hw_pp->merge_3d)
		पूर्णांकf_cfg.merge_3d = phys_enc->hw_pp->merge_3d->id;

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	phys_enc->hw_पूर्णांकf->ops.setup_timing_gen(phys_enc->hw_पूर्णांकf,
			&timing_params, fmt);
	phys_enc->hw_ctl->ops.setup_पूर्णांकf_cfg(phys_enc->hw_ctl, &पूर्णांकf_cfg);

	/* setup which pp blk will connect to this पूर्णांकf */
	अगर (phys_enc->hw_पूर्णांकf->ops.bind_pingpong_blk)
		phys_enc->hw_पूर्णांकf->ops.bind_pingpong_blk(
				phys_enc->hw_पूर्णांकf,
				true,
				phys_enc->hw_pp->idx);

	अगर (phys_enc->hw_pp->merge_3d) अणु
		काष्ठा dpu_hw_merge_3d *merge_3d = to_dpu_hw_merge_3d(phys_enc->hw_pp->merge_3d);

		merge_3d->ops.setup_3d_mode(merge_3d, पूर्णांकf_cfg.mode_3d);
	पूर्ण

	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	programmable_fetch_config(phys_enc, &timing_params);
पूर्ण

अटल व्योम dpu_encoder_phys_vid_vblank_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;
	काष्ठा dpu_hw_ctl *hw_ctl;
	अचिन्हित दीर्घ lock_flags;
	u32 flush_रेजिस्टर = 0;

	hw_ctl = phys_enc->hw_ctl;

	DPU_ATRACE_BEGIN("vblank_irq");

	अगर (phys_enc->parent_ops->handle_vblank_virt)
		phys_enc->parent_ops->handle_vblank_virt(phys_enc->parent,
				phys_enc);

	atomic_पढ़ो(&phys_enc->pending_kickoff_cnt);

	/*
	 * only decrement the pending flush count अगर we've actually flushed
	 * hardware. due to sw irq latency, vblank may have alपढ़ोy happened
	 * so we need to द्विगुन-check with hw that it accepted the flush bits
	 */
	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	अगर (hw_ctl->ops.get_flush_रेजिस्टर)
		flush_रेजिस्टर = hw_ctl->ops.get_flush_रेजिस्टर(hw_ctl);

	अगर (!(flush_रेजिस्टर & hw_ctl->ops.get_pending_flush(hw_ctl)))
		atomic_add_unless(&phys_enc->pending_kickoff_cnt, -1, 0);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	/* Signal any रुकोing atomic commit thपढ़ो */
	wake_up_all(&phys_enc->pending_kickoff_wq);

	phys_enc->parent_ops->handle_frame_करोne(phys_enc->parent, phys_enc,
			DPU_ENCODER_FRAME_EVENT_DONE);

	DPU_ATRACE_END("vblank_irq");
पूर्ण

अटल व्योम dpu_encoder_phys_vid_underrun_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;

	अगर (phys_enc->parent_ops->handle_underrun_virt)
		phys_enc->parent_ops->handle_underrun_virt(phys_enc->parent,
			phys_enc);
पूर्ण

अटल bool dpu_encoder_phys_vid_needs_single_flush(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	वापस phys_enc->split_role != ENC_ROLE_SOLO;
पूर्ण

अटल व्योम _dpu_encoder_phys_vid_setup_irq_hw_idx(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_irq *irq;

	/*
	 * Initialize irq->hw_idx only when irq is not रेजिस्टरed.
	 * Prevent invalidating irq->irq_idx as modeset may be
	 * called many बार during dfps.
	 */

	irq = &phys_enc->irq[INTR_IDX_VSYNC];
	अगर (irq->irq_idx < 0)
		irq->hw_idx = phys_enc->पूर्णांकf_idx;

	irq = &phys_enc->irq[INTR_IDX_UNDERRUN];
	अगर (irq->irq_idx < 0)
		irq->hw_idx = phys_enc->पूर्णांकf_idx;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_mode_set(
		काष्ठा dpu_encoder_phys *phys_enc,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adj_mode)
अणु
	अगर (adj_mode) अणु
		phys_enc->cached_mode = *adj_mode;
		drm_mode_debug_prपूर्णांकmodeline(adj_mode);
		DPU_DEBUG_VIDENC(phys_enc, "caching mode:\n");
	पूर्ण

	_dpu_encoder_phys_vid_setup_irq_hw_idx(phys_enc);
पूर्ण

अटल पूर्णांक dpu_encoder_phys_vid_control_vblank_irq(
		काष्ठा dpu_encoder_phys *phys_enc,
		bool enable)
अणु
	पूर्णांक ret = 0;
	पूर्णांक refcount;

	refcount = atomic_पढ़ो(&phys_enc->vblank_refcount);

	/* Slave encoders करोn't report vblank */
	अगर (!dpu_encoder_phys_vid_is_master(phys_enc))
		जाओ end;

	/* protect against negative */
	अगर (!enable && refcount == 0) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	DRM_DEBUG_KMS("id:%u enable=%d/%d\n", DRMID(phys_enc->parent), enable,
		      atomic_पढ़ो(&phys_enc->vblank_refcount));

	अगर (enable && atomic_inc_वापस(&phys_enc->vblank_refcount) == 1)
		ret = dpu_encoder_helper_रेजिस्टर_irq(phys_enc, INTR_IDX_VSYNC);
	अन्यथा अगर (!enable && atomic_dec_वापस(&phys_enc->vblank_refcount) == 0)
		ret = dpu_encoder_helper_unरेजिस्टर_irq(phys_enc,
				INTR_IDX_VSYNC);

end:
	अगर (ret) अणु
		DRM_ERROR("failed: id:%u intf:%d ret:%d enable:%d refcnt:%d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_पूर्णांकf->idx - INTF_0, ret, enable,
			  refcount);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_enable(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_ctl *ctl;

	ctl = phys_enc->hw_ctl;

	DPU_DEBUG_VIDENC(phys_enc, "\n");

	अगर (WARN_ON(!phys_enc->hw_पूर्णांकf->ops.enable_timing))
		वापस;

	dpu_encoder_helper_split_config(phys_enc, phys_enc->hw_पूर्णांकf->idx);

	dpu_encoder_phys_vid_setup_timing_engine(phys_enc);

	/*
	 * For single flush हालs (dual-ctl or pp-split), skip setting the
	 * flush bit क्रम the slave पूर्णांकf, since both पूर्णांकfs use same ctl
	 * and HW will only flush the master.
	 */
	अगर (dpu_encoder_phys_vid_needs_single_flush(phys_enc) &&
		!dpu_encoder_phys_vid_is_master(phys_enc))
		जाओ skip_flush;

	ctl->ops.update_pending_flush_पूर्णांकf(ctl, phys_enc->hw_पूर्णांकf->idx);
	अगर (ctl->ops.update_pending_flush_merge_3d && phys_enc->hw_pp->merge_3d)
		ctl->ops.update_pending_flush_merge_3d(ctl, phys_enc->hw_pp->merge_3d->id);

skip_flush:
	DPU_DEBUG_VIDENC(phys_enc,
		"update pending flush ctl %d intf %d\n",
		ctl->idx - CTL_0, phys_enc->hw_पूर्णांकf->idx);


	/* ctl_flush & timing engine enable will be triggered by framework */
	अगर (phys_enc->enable_state == DPU_ENC_DISABLED)
		phys_enc->enable_state = DPU_ENC_ENABLING;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_destroy(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	DPU_DEBUG_VIDENC(phys_enc, "\n");
	kमुक्त(phys_enc);
पूर्ण

अटल व्योम dpu_encoder_phys_vid_get_hw_resources(
		काष्ठा dpu_encoder_phys *phys_enc,
		काष्ठा dpu_encoder_hw_resources *hw_res)
अणु
	hw_res->पूर्णांकfs[phys_enc->पूर्णांकf_idx - INTF_0] = INTF_MODE_VIDEO;
पूर्ण

अटल पूर्णांक dpu_encoder_phys_vid_रुको_क्रम_vblank(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_रुको_info रुको_info;
	पूर्णांक ret;

	रुको_info.wq = &phys_enc->pending_kickoff_wq;
	रुको_info.atomic_cnt = &phys_enc->pending_kickoff_cnt;
	रुको_info.समयout_ms = KICKOFF_TIMEOUT_MS;

	अगर (!dpu_encoder_phys_vid_is_master(phys_enc)) अणु
		वापस 0;
	पूर्ण

	/* Wait क्रम kickoff to complete */
	ret = dpu_encoder_helper_रुको_क्रम_irq(phys_enc, INTR_IDX_VSYNC,
			&रुको_info);

	अगर (ret == -ETIMEDOUT) अणु
		dpu_encoder_helper_report_irq_समयout(phys_enc, INTR_IDX_VSYNC);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dpu_encoder_phys_vid_रुको_क्रम_commit_करोne(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_ctl *hw_ctl = phys_enc->hw_ctl;
	पूर्णांक ret;

	अगर (!hw_ctl)
		वापस 0;

	ret = रुको_event_समयout(phys_enc->pending_kickoff_wq,
		(hw_ctl->ops.get_flush_रेजिस्टर(hw_ctl) == 0),
		msecs_to_jअगरfies(50));
	अगर (ret <= 0) अणु
		DPU_ERROR("vblank timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_prepare_क्रम_kickoff(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_ctl *ctl;
	पूर्णांक rc;

	ctl = phys_enc->hw_ctl;
	अगर (!ctl->ops.रुको_reset_status)
		वापस;

	/*
	 * hw supports hardware initiated ctl reset, so beक्रमe we kickoff a new
	 * frame, need to check and रुको क्रम hw initiated ctl reset completion
	 */
	rc = ctl->ops.रुको_reset_status(ctl);
	अगर (rc) अणु
		DPU_ERROR_VIDENC(phys_enc, "ctl %d reset failure: %d\n",
				ctl->idx, rc);
		dpu_encoder_helper_unरेजिस्टर_irq(phys_enc, INTR_IDX_VSYNC);
	पूर्ण
पूर्ण

अटल व्योम dpu_encoder_phys_vid_disable(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक ret;

	अगर (!phys_enc->parent || !phys_enc->parent->dev) अणु
		DPU_ERROR("invalid encoder/device\n");
		वापस;
	पूर्ण

	अगर (!phys_enc->hw_पूर्णांकf) अणु
		DPU_ERROR("invalid hw_intf %d hw_ctl %d\n",
				phys_enc->hw_पूर्णांकf != शून्य, phys_enc->hw_ctl != शून्य);
		वापस;
	पूर्ण

	अगर (WARN_ON(!phys_enc->hw_पूर्णांकf->ops.enable_timing))
		वापस;

	अगर (phys_enc->enable_state == DPU_ENC_DISABLED) अणु
		DPU_ERROR("already disabled\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	phys_enc->hw_पूर्णांकf->ops.enable_timing(phys_enc->hw_पूर्णांकf, 0);
	अगर (dpu_encoder_phys_vid_is_master(phys_enc))
		dpu_encoder_phys_inc_pending(phys_enc);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	/*
	 * Wait क्रम a vsync so we know the ENABLE=0 latched beक्रमe
	 * the (connector) source of the vsync's माला_लो disabled,
	 * otherwise we end up in a funny state अगर we re-enable
	 * beक्रमe the disable latches, which results that some of
	 * the settings changes क्रम the new modeset (like new
	 * scanout buffer) करोn't latch properly..
	 */
	अगर (dpu_encoder_phys_vid_is_master(phys_enc)) अणु
		ret = dpu_encoder_phys_vid_रुको_क्रम_vblank(phys_enc);
		अगर (ret) अणु
			atomic_set(&phys_enc->pending_kickoff_cnt, 0);
			DRM_ERROR("wait disable failed: id:%u intf:%d ret:%d\n",
				  DRMID(phys_enc->parent),
				  phys_enc->hw_पूर्णांकf->idx - INTF_0, ret);
		पूर्ण
	पूर्ण

	phys_enc->enable_state = DPU_ENC_DISABLED;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_handle_post_kickoff(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	अचिन्हित दीर्घ lock_flags;

	/*
	 * Video mode must flush CTL beक्रमe enabling timing engine
	 * Video encoders need to turn on their पूर्णांकerfaces now
	 */
	अगर (phys_enc->enable_state == DPU_ENC_ENABLING) अणु
		trace_dpu_enc_phys_vid_post_kickoff(DRMID(phys_enc->parent),
				    phys_enc->hw_पूर्णांकf->idx - INTF_0);
		spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
		phys_enc->hw_पूर्णांकf->ops.enable_timing(phys_enc->hw_पूर्णांकf, 1);
		spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);
		phys_enc->enable_state = DPU_ENC_ENABLED;
	पूर्ण
पूर्ण

अटल व्योम dpu_encoder_phys_vid_irq_control(काष्ठा dpu_encoder_phys *phys_enc,
		bool enable)
अणु
	पूर्णांक ret;

	trace_dpu_enc_phys_vid_irq_ctrl(DRMID(phys_enc->parent),
			    phys_enc->hw_पूर्णांकf->idx - INTF_0,
			    enable,
			    atomic_पढ़ो(&phys_enc->vblank_refcount));

	अगर (enable) अणु
		ret = dpu_encoder_phys_vid_control_vblank_irq(phys_enc, true);
		अगर (ret)
			वापस;

		dpu_encoder_helper_रेजिस्टर_irq(phys_enc, INTR_IDX_UNDERRUN);
	पूर्ण अन्यथा अणु
		dpu_encoder_phys_vid_control_vblank_irq(phys_enc, false);
		dpu_encoder_helper_unरेजिस्टर_irq(phys_enc, INTR_IDX_UNDERRUN);
	पूर्ण
पूर्ण

अटल पूर्णांक dpu_encoder_phys_vid_get_line_count(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	अगर (!dpu_encoder_phys_vid_is_master(phys_enc))
		वापस -EINVAL;

	अगर (!phys_enc->hw_पूर्णांकf || !phys_enc->hw_पूर्णांकf->ops.get_line_count)
		वापस -EINVAL;

	वापस phys_enc->hw_पूर्णांकf->ops.get_line_count(phys_enc->hw_पूर्णांकf);
पूर्ण

अटल पूर्णांक dpu_encoder_phys_vid_get_frame_count(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा पूर्णांकf_status s = अणु0पूर्ण;
	u32 fetch_start = 0;
	काष्ठा drm_display_mode mode = phys_enc->cached_mode;

	अगर (!dpu_encoder_phys_vid_is_master(phys_enc))
		वापस -EINVAL;

	अगर (!phys_enc->hw_पूर्णांकf || !phys_enc->hw_पूर्णांकf->ops.get_status)
		वापस -EINVAL;

	phys_enc->hw_पूर्णांकf->ops.get_status(phys_enc->hw_पूर्णांकf, &s);

	अगर (s.is_prog_fetch_en && s.is_en) अणु
		fetch_start = mode.vtotal - (mode.vsync_start - mode.vdisplay);
		अगर ((s.line_count > fetch_start) &&
			(s.line_count <= mode.vtotal))
			वापस s.frame_count + 1;
	पूर्ण

	वापस s.frame_count;
पूर्ण

अटल व्योम dpu_encoder_phys_vid_init_ops(काष्ठा dpu_encoder_phys_ops *ops)
अणु
	ops->is_master = dpu_encoder_phys_vid_is_master;
	ops->mode_set = dpu_encoder_phys_vid_mode_set;
	ops->mode_fixup = dpu_encoder_phys_vid_mode_fixup;
	ops->enable = dpu_encoder_phys_vid_enable;
	ops->disable = dpu_encoder_phys_vid_disable;
	ops->destroy = dpu_encoder_phys_vid_destroy;
	ops->get_hw_resources = dpu_encoder_phys_vid_get_hw_resources;
	ops->control_vblank_irq = dpu_encoder_phys_vid_control_vblank_irq;
	ops->रुको_क्रम_commit_करोne = dpu_encoder_phys_vid_रुको_क्रम_commit_करोne;
	ops->रुको_क्रम_vblank = dpu_encoder_phys_vid_रुको_क्रम_vblank;
	ops->रुको_क्रम_tx_complete = dpu_encoder_phys_vid_रुको_क्रम_vblank;
	ops->irq_control = dpu_encoder_phys_vid_irq_control;
	ops->prepare_क्रम_kickoff = dpu_encoder_phys_vid_prepare_क्रम_kickoff;
	ops->handle_post_kickoff = dpu_encoder_phys_vid_handle_post_kickoff;
	ops->needs_single_flush = dpu_encoder_phys_vid_needs_single_flush;
	ops->get_line_count = dpu_encoder_phys_vid_get_line_count;
	ops->get_frame_count = dpu_encoder_phys_vid_get_frame_count;
पूर्ण

काष्ठा dpu_encoder_phys *dpu_encoder_phys_vid_init(
		काष्ठा dpu_enc_phys_init_params *p)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = शून्य;
	काष्ठा dpu_encoder_irq *irq;
	पूर्णांक i, ret = 0;

	अगर (!p) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	phys_enc = kzalloc(माप(*phys_enc), GFP_KERNEL);
	अगर (!phys_enc) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	phys_enc->hw_mdptop = p->dpu_kms->hw_mdp;
	phys_enc->पूर्णांकf_idx = p->पूर्णांकf_idx;

	DPU_DEBUG_VIDENC(phys_enc, "\n");

	dpu_encoder_phys_vid_init_ops(&phys_enc->ops);
	phys_enc->parent = p->parent;
	phys_enc->parent_ops = p->parent_ops;
	phys_enc->dpu_kms = p->dpu_kms;
	phys_enc->split_role = p->split_role;
	phys_enc->पूर्णांकf_mode = INTF_MODE_VIDEO;
	phys_enc->enc_spinlock = p->enc_spinlock;
	क्रम (i = 0; i < INTR_IDX_MAX; i++) अणु
		irq = &phys_enc->irq[i];
		INIT_LIST_HEAD(&irq->cb.list);
		irq->irq_idx = -EINVAL;
		irq->hw_idx = -EINVAL;
		irq->cb.arg = phys_enc;
	पूर्ण

	irq = &phys_enc->irq[INTR_IDX_VSYNC];
	irq->name = "vsync_irq";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_INTF_VSYNC;
	irq->पूर्णांकr_idx = INTR_IDX_VSYNC;
	irq->cb.func = dpu_encoder_phys_vid_vblank_irq;

	irq = &phys_enc->irq[INTR_IDX_UNDERRUN];
	irq->name = "underrun";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_INTF_UNDER_RUN;
	irq->पूर्णांकr_idx = INTR_IDX_UNDERRUN;
	irq->cb.func = dpu_encoder_phys_vid_underrun_irq;

	atomic_set(&phys_enc->vblank_refcount, 0);
	atomic_set(&phys_enc->pending_kickoff_cnt, 0);
	init_रुकोqueue_head(&phys_enc->pending_kickoff_wq);
	phys_enc->enable_state = DPU_ENC_DISABLED;

	DPU_DEBUG_VIDENC(phys_enc, "created intf idx:%d\n", p->पूर्णांकf_idx);

	वापस phys_enc;

fail:
	DPU_ERROR("failed to create encoder\n");
	अगर (phys_enc)
		dpu_encoder_phys_vid_destroy(phys_enc);

	वापस ERR_PTR(ret);
पूर्ण
