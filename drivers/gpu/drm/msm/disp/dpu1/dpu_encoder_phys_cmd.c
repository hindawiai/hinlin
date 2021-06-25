<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2018 The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__
#समावेश <linux/delay.h>
#समावेश "dpu_encoder_phys.h"
#समावेश "dpu_hw_interrupts.h"
#समावेश "dpu_hw_pingpong.h"
#समावेश "dpu_core_irq.h"
#समावेश "dpu_formats.h"
#समावेश "dpu_trace.h"

#घोषणा DPU_DEBUG_CMDENC(e, fmt, ...) DPU_DEBUG("enc%d intf%d " fmt, \
		(e) && (e)->base.parent ? \
		(e)->base.parent->base.id : -1, \
		(e) ? (e)->base.पूर्णांकf_idx - INTF_0 : -1, ##__VA_ARGS__)

#घोषणा DPU_ERROR_CMDENC(e, fmt, ...) DPU_ERROR("enc%d intf%d " fmt, \
		(e) && (e)->base.parent ? \
		(e)->base.parent->base.id : -1, \
		(e) ? (e)->base.पूर्णांकf_idx - INTF_0 : -1, ##__VA_ARGS__)

#घोषणा to_dpu_encoder_phys_cmd(x) \
	container_of(x, काष्ठा dpu_encoder_phys_cmd, base)

#घोषणा PP_TIMEOUT_MAX_TRIALS	10

/*
 * Tearcheck sync start and जारी thresholds are empirically found
 * based on common panels In the future, may want to allow panels to override
 * these शेष values
 */
#घोषणा DEFAULT_TEARCHECK_SYNC_THRESH_START	4
#घोषणा DEFAULT_TEARCHECK_SYNC_THRESH_CONTINUE	4

#घोषणा DPU_ENC_WR_PTR_START_TIMEOUT_US 20000

#घोषणा DPU_ENC_MAX_POLL_TIMEOUT_US	2000

अटल bool dpu_encoder_phys_cmd_is_master(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	वापस (phys_enc->split_role != ENC_ROLE_SLAVE) ? true : false;
पूर्ण

अटल bool dpu_encoder_phys_cmd_mode_fixup(
		काष्ठा dpu_encoder_phys *phys_enc,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adj_mode)
अणु
	DPU_DEBUG_CMDENC(to_dpu_encoder_phys_cmd(phys_enc), "\n");
	वापस true;
पूर्ण

अटल व्योम _dpu_encoder_phys_cmd_update_पूर्णांकf_cfg(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	काष्ठा dpu_hw_ctl *ctl;
	काष्ठा dpu_hw_पूर्णांकf_cfg पूर्णांकf_cfg = अणु 0 पूर्ण;

	ctl = phys_enc->hw_ctl;
	अगर (!ctl->ops.setup_पूर्णांकf_cfg)
		वापस;

	पूर्णांकf_cfg.पूर्णांकf = phys_enc->पूर्णांकf_idx;
	पूर्णांकf_cfg.पूर्णांकf_mode_sel = DPU_CTL_MODE_SEL_CMD;
	पूर्णांकf_cfg.stream_sel = cmd_enc->stream_sel;
	पूर्णांकf_cfg.mode_3d = dpu_encoder_helper_get_3d_blend_mode(phys_enc);
	ctl->ops.setup_पूर्णांकf_cfg(ctl, &पूर्णांकf_cfg);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_pp_tx_करोne_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक new_cnt;
	u32 event = DPU_ENCODER_FRAME_EVENT_DONE;

	अगर (!phys_enc->hw_pp)
		वापस;

	DPU_ATRACE_BEGIN("pp_done_irq");
	/* notअगरy all synchronous clients first, then asynchronous clients */
	अगर (phys_enc->parent_ops->handle_frame_करोne)
		phys_enc->parent_ops->handle_frame_करोne(phys_enc->parent,
				phys_enc, event);

	spin_lock_irqsave(phys_enc->enc_spinlock, lock_flags);
	new_cnt = atomic_add_unless(&phys_enc->pending_kickoff_cnt, -1, 0);
	spin_unlock_irqrestore(phys_enc->enc_spinlock, lock_flags);

	trace_dpu_enc_phys_cmd_pp_tx_करोne(DRMID(phys_enc->parent),
					  phys_enc->hw_pp->idx - PINGPONG_0,
					  new_cnt, event);

	/* Signal any रुकोing atomic commit thपढ़ो */
	wake_up_all(&phys_enc->pending_kickoff_wq);
	DPU_ATRACE_END("pp_done_irq");
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_pp_rd_ptr_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;
	काष्ठा dpu_encoder_phys_cmd *cmd_enc;

	अगर (!phys_enc->hw_pp)
		वापस;

	DPU_ATRACE_BEGIN("rd_ptr_irq");
	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	अगर (phys_enc->parent_ops->handle_vblank_virt)
		phys_enc->parent_ops->handle_vblank_virt(phys_enc->parent,
			phys_enc);

	atomic_add_unless(&cmd_enc->pending_vblank_cnt, -1, 0);
	wake_up_all(&cmd_enc->pending_vblank_wq);
	DPU_ATRACE_END("rd_ptr_irq");
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_ctl_start_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;

	DPU_ATRACE_BEGIN("ctl_start_irq");

	atomic_add_unless(&phys_enc->pending_ctlstart_cnt, -1, 0);

	/* Signal any रुकोing ctl start पूर्णांकerrupt */
	wake_up_all(&phys_enc->pending_kickoff_wq);
	DPU_ATRACE_END("ctl_start_irq");
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_underrun_irq(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = arg;

	अगर (phys_enc->parent_ops->handle_underrun_virt)
		phys_enc->parent_ops->handle_underrun_virt(phys_enc->parent,
			phys_enc);
पूर्ण

अटल व्योम _dpu_encoder_phys_cmd_setup_irq_hw_idx(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_irq *irq;

	irq = &phys_enc->irq[INTR_IDX_CTL_START];
	irq->hw_idx = phys_enc->hw_ctl->idx;
	irq->irq_idx = -EINVAL;

	irq = &phys_enc->irq[INTR_IDX_PINGPONG];
	irq->hw_idx = phys_enc->hw_pp->idx;
	irq->irq_idx = -EINVAL;

	irq = &phys_enc->irq[INTR_IDX_RDPTR];
	irq->hw_idx = phys_enc->hw_pp->idx;
	irq->irq_idx = -EINVAL;

	irq = &phys_enc->irq[INTR_IDX_UNDERRUN];
	irq->hw_idx = phys_enc->पूर्णांकf_idx;
	irq->irq_idx = -EINVAL;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_mode_set(
		काष्ठा dpu_encoder_phys *phys_enc,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	अगर (!mode || !adj_mode) अणु
		DPU_ERROR("invalid args\n");
		वापस;
	पूर्ण
	phys_enc->cached_mode = *adj_mode;
	DPU_DEBUG_CMDENC(cmd_enc, "caching mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(adj_mode);

	_dpu_encoder_phys_cmd_setup_irq_hw_idx(phys_enc);
पूर्ण

अटल पूर्णांक _dpu_encoder_phys_cmd_handle_ppकरोne_समयout(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	u32 frame_event = DPU_ENCODER_FRAME_EVENT_ERROR;
	bool करो_log = false;

	अगर (!phys_enc->hw_pp)
		वापस -EINVAL;

	cmd_enc->pp_समयout_report_cnt++;
	अगर (cmd_enc->pp_समयout_report_cnt == PP_TIMEOUT_MAX_TRIALS) अणु
		frame_event |= DPU_ENCODER_FRAME_EVENT_PANEL_DEAD;
		करो_log = true;
	पूर्ण अन्यथा अगर (cmd_enc->pp_समयout_report_cnt == 1) अणु
		करो_log = true;
	पूर्ण

	trace_dpu_enc_phys_cmd_pकरोne_समयout(DRMID(phys_enc->parent),
		     phys_enc->hw_pp->idx - PINGPONG_0,
		     cmd_enc->pp_समयout_report_cnt,
		     atomic_पढ़ो(&phys_enc->pending_kickoff_cnt),
		     frame_event);

	/* to aव्योम flooding, only log first समय, and "dead" समय */
	अगर (करो_log) अणु
		DRM_ERROR("id:%d pp:%d kickoff timeout %d cnt %d koff_cnt %d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_pp->idx - PINGPONG_0,
			  phys_enc->hw_ctl->idx - CTL_0,
			  cmd_enc->pp_समयout_report_cnt,
			  atomic_पढ़ो(&phys_enc->pending_kickoff_cnt));

		dpu_encoder_helper_unरेजिस्टर_irq(phys_enc, INTR_IDX_RDPTR);
	पूर्ण

	atomic_add_unless(&phys_enc->pending_kickoff_cnt, -1, 0);

	/* request a ctl reset beक्रमe the next kickoff */
	phys_enc->enable_state = DPU_ENC_ERR_NEEDS_HW_RESET;

	अगर (phys_enc->parent_ops->handle_frame_करोne)
		phys_enc->parent_ops->handle_frame_करोne(
				phys_enc->parent, phys_enc, frame_event);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक _dpu_encoder_phys_cmd_रुको_क्रम_idle(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	काष्ठा dpu_encoder_रुको_info रुको_info;
	पूर्णांक ret;

	रुको_info.wq = &phys_enc->pending_kickoff_wq;
	रुको_info.atomic_cnt = &phys_enc->pending_kickoff_cnt;
	रुको_info.समयout_ms = KICKOFF_TIMEOUT_MS;

	ret = dpu_encoder_helper_रुको_क्रम_irq(phys_enc, INTR_IDX_PINGPONG,
			&रुको_info);
	अगर (ret == -ETIMEDOUT)
		_dpu_encoder_phys_cmd_handle_ppकरोne_समयout(phys_enc);
	अन्यथा अगर (!ret)
		cmd_enc->pp_समयout_report_cnt = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक dpu_encoder_phys_cmd_control_vblank_irq(
		काष्ठा dpu_encoder_phys *phys_enc,
		bool enable)
अणु
	पूर्णांक ret = 0;
	पूर्णांक refcount;

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid encoder\n");
		वापस -EINVAL;
	पूर्ण

	refcount = atomic_पढ़ो(&phys_enc->vblank_refcount);

	/* Slave encoders करोn't report vblank */
	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		जाओ end;

	/* protect against negative */
	अगर (!enable && refcount == 0) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	DRM_DEBUG_KMS("id:%u pp:%d enable=%s/%d\n", DRMID(phys_enc->parent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      enable ? "true" : "false", refcount);

	अगर (enable && atomic_inc_वापस(&phys_enc->vblank_refcount) == 1)
		ret = dpu_encoder_helper_रेजिस्टर_irq(phys_enc, INTR_IDX_RDPTR);
	अन्यथा अगर (!enable && atomic_dec_वापस(&phys_enc->vblank_refcount) == 0)
		ret = dpu_encoder_helper_unरेजिस्टर_irq(phys_enc,
				INTR_IDX_RDPTR);

end:
	अगर (ret) अणु
		DRM_ERROR("vblank irq err id:%u pp:%d ret:%d, enable %s/%d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_pp->idx - PINGPONG_0, ret,
			  enable ? "true" : "false", refcount);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_irq_control(काष्ठा dpu_encoder_phys *phys_enc,
		bool enable)
अणु
	trace_dpu_enc_phys_cmd_irq_ctrl(DRMID(phys_enc->parent),
			phys_enc->hw_pp->idx - PINGPONG_0,
			enable, atomic_पढ़ो(&phys_enc->vblank_refcount));

	अगर (enable) अणु
		dpu_encoder_helper_रेजिस्टर_irq(phys_enc, INTR_IDX_PINGPONG);
		dpu_encoder_helper_रेजिस्टर_irq(phys_enc, INTR_IDX_UNDERRUN);
		dpu_encoder_phys_cmd_control_vblank_irq(phys_enc, true);

		अगर (dpu_encoder_phys_cmd_is_master(phys_enc))
			dpu_encoder_helper_रेजिस्टर_irq(phys_enc,
					INTR_IDX_CTL_START);
	पूर्ण अन्यथा अणु
		अगर (dpu_encoder_phys_cmd_is_master(phys_enc))
			dpu_encoder_helper_unरेजिस्टर_irq(phys_enc,
					INTR_IDX_CTL_START);

		dpu_encoder_helper_unरेजिस्टर_irq(phys_enc, INTR_IDX_UNDERRUN);
		dpu_encoder_phys_cmd_control_vblank_irq(phys_enc, false);
		dpu_encoder_helper_unरेजिस्टर_irq(phys_enc, INTR_IDX_PINGPONG);
	पूर्ण
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_tearcheck_config(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);
	काष्ठा dpu_hw_tear_check tc_cfg = अणु 0 पूर्ण;
	काष्ठा drm_display_mode *mode;
	bool tc_enable = true;
	u32 vsync_hz;
	काष्ठा dpu_kms *dpu_kms;

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	mode = &phys_enc->cached_mode;

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d\n", phys_enc->hw_pp->idx - PINGPONG_0);

	अगर (!phys_enc->hw_pp->ops.setup_tearcheck ||
		!phys_enc->hw_pp->ops.enable_tearcheck) अणु
		DPU_DEBUG_CMDENC(cmd_enc, "tearcheck not supported\n");
		वापस;
	पूर्ण

	dpu_kms = phys_enc->dpu_kms;

	/*
	 * TE शेष: dsi byte घड़ी calculated base on 70 fps;
	 * around 14 ms to complete a kickoff cycle अगर te disabled;
	 * vclk_line base on 60 fps; ग_लिखो is faster than पढ़ो;
	 * init == start == rdptr;
	 *
	 * vsync_count is ratio of MDP VSYNC घड़ी frequency to LCD panel
	 * frequency भागided by the no. of rows (lines) in the LCDpanel.
	 */
	vsync_hz = dpu_kms_get_clk_rate(dpu_kms, "vsync");
	अगर (vsync_hz <= 0) अणु
		DPU_DEBUG_CMDENC(cmd_enc, "invalid - vsync_hz %u\n",
				 vsync_hz);
		वापस;
	पूर्ण

	tc_cfg.vsync_count = vsync_hz /
				(mode->vtotal * drm_mode_vrefresh(mode));

	/*
	 * Set the sync_cfg_height to twice vtotal so that अगर we lose a
	 * TE event coming from the display TE pin we won't stall immediately
	 */
	tc_cfg.hw_vsync_mode = 1;
	tc_cfg.sync_cfg_height = mode->vtotal * 2;
	tc_cfg.vsync_init_val = mode->vdisplay;
	tc_cfg.sync_threshold_start = DEFAULT_TEARCHECK_SYNC_THRESH_START;
	tc_cfg.sync_threshold_जारी = DEFAULT_TEARCHECK_SYNC_THRESH_CONTINUE;
	tc_cfg.start_pos = mode->vdisplay;
	tc_cfg.rd_ptr_irq = mode->vdisplay + 1;

	DPU_DEBUG_CMDENC(cmd_enc,
		"tc %d vsync_clk_speed_hz %u vtotal %u vrefresh %u\n",
		phys_enc->hw_pp->idx - PINGPONG_0, vsync_hz,
		mode->vtotal, drm_mode_vrefresh(mode));
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc %d enable %u start_pos %u rd_ptr_irq %u\n",
		phys_enc->hw_pp->idx - PINGPONG_0, tc_enable, tc_cfg.start_pos,
		tc_cfg.rd_ptr_irq);
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc %d hw_vsync_mode %u vsync_count %u vsync_init_val %u\n",
		phys_enc->hw_pp->idx - PINGPONG_0, tc_cfg.hw_vsync_mode,
		tc_cfg.vsync_count, tc_cfg.vsync_init_val);
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc %d cfgheight %u thresh_start %u thresh_cont %u\n",
		phys_enc->hw_pp->idx - PINGPONG_0, tc_cfg.sync_cfg_height,
		tc_cfg.sync_threshold_start, tc_cfg.sync_threshold_जारी);

	phys_enc->hw_pp->ops.setup_tearcheck(phys_enc->hw_pp, &tc_cfg);
	phys_enc->hw_pp->ops.enable_tearcheck(phys_enc->hw_pp, tc_enable);
पूर्ण

अटल व्योम _dpu_encoder_phys_cmd_pingpong_config(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	अगर (!phys_enc->hw_pp || !phys_enc->hw_ctl->ops.setup_पूर्णांकf_cfg) अणु
		DPU_ERROR("invalid arg(s), enc %d\n", phys_enc != शून्य);
		वापस;
	पूर्ण

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d, enabling mode:\n",
			phys_enc->hw_pp->idx - PINGPONG_0);
	drm_mode_debug_prपूर्णांकmodeline(&phys_enc->cached_mode);

	_dpu_encoder_phys_cmd_update_पूर्णांकf_cfg(phys_enc);
	dpu_encoder_phys_cmd_tearcheck_config(phys_enc);
पूर्ण

अटल bool dpu_encoder_phys_cmd_needs_single_flush(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	/**
	 * we करो separate flush क्रम each CTL and let
	 * CTL_START synchronize them
	 */
	वापस false;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_enable_helper(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_ctl *ctl;

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid arg(s), encoder %d\n", phys_enc != शून्य);
		वापस;
	पूर्ण

	dpu_encoder_helper_split_config(phys_enc, phys_enc->पूर्णांकf_idx);

	_dpu_encoder_phys_cmd_pingpong_config(phys_enc);

	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		वापस;

	ctl = phys_enc->hw_ctl;
	ctl->ops.update_pending_flush_पूर्णांकf(ctl, phys_enc->पूर्णांकf_idx);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_enable(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid phys encoder\n");
		वापस;
	पूर्ण

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d\n", phys_enc->hw_pp->idx - PINGPONG_0);

	अगर (phys_enc->enable_state == DPU_ENC_ENABLED) अणु
		DPU_ERROR("already enabled\n");
		वापस;
	पूर्ण

	dpu_encoder_phys_cmd_enable_helper(phys_enc);
	phys_enc->enable_state = DPU_ENC_ENABLED;
पूर्ण

अटल व्योम _dpu_encoder_phys_cmd_connect_te(
		काष्ठा dpu_encoder_phys *phys_enc, bool enable)
अणु
	अगर (!phys_enc->hw_pp || !phys_enc->hw_pp->ops.connect_बाह्यal_te)
		वापस;

	trace_dpu_enc_phys_cmd_connect_te(DRMID(phys_enc->parent), enable);
	phys_enc->hw_pp->ops.connect_बाह्यal_te(phys_enc->hw_pp, enable);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_prepare_idle_pc(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	_dpu_encoder_phys_cmd_connect_te(phys_enc, false);
पूर्ण

अटल पूर्णांक dpu_encoder_phys_cmd_get_line_count(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_pingpong *hw_pp;

	अगर (!phys_enc->hw_pp)
		वापस -EINVAL;

	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		वापस -EINVAL;

	hw_pp = phys_enc->hw_pp;
	अगर (!hw_pp->ops.get_line_count)
		वापस -EINVAL;

	वापस hw_pp->ops.get_line_count(hw_pp);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_disable(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	DRM_DEBUG_KMS("id:%u pp:%d state:%d\n", DRMID(phys_enc->parent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      phys_enc->enable_state);

	अगर (phys_enc->enable_state == DPU_ENC_DISABLED) अणु
		DPU_ERROR_CMDENC(cmd_enc, "already disabled\n");
		वापस;
	पूर्ण

	अगर (phys_enc->hw_pp->ops.enable_tearcheck)
		phys_enc->hw_pp->ops.enable_tearcheck(phys_enc->hw_pp, false);
	phys_enc->enable_state = DPU_ENC_DISABLED;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_destroy(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	kमुक्त(cmd_enc);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_get_hw_resources(
		काष्ठा dpu_encoder_phys *phys_enc,
		काष्ठा dpu_encoder_hw_resources *hw_res)
अणु
	hw_res->पूर्णांकfs[phys_enc->पूर्णांकf_idx - INTF_0] = INTF_MODE_CMD;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_prepare_क्रम_kickoff(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	पूर्णांक ret;

	अगर (!phys_enc->hw_pp) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	DRM_DEBUG_KMS("id:%u pp:%d pending_cnt:%d\n", DRMID(phys_enc->parent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      atomic_पढ़ो(&phys_enc->pending_kickoff_cnt));

	/*
	 * Mark kickoff request as outstanding. If there are more than one,
	 * outstanding, then we have to रुको क्रम the previous one to complete
	 */
	ret = _dpu_encoder_phys_cmd_रुको_क्रम_idle(phys_enc);
	अगर (ret) अणु
		/* क्रमce pending_kickoff_cnt 0 to discard failed kickoff */
		atomic_set(&phys_enc->pending_kickoff_cnt, 0);
		DRM_ERROR("failed wait_for_idle: id:%u ret:%d pp:%d\n",
			  DRMID(phys_enc->parent), ret,
			  phys_enc->hw_pp->idx - PINGPONG_0);
	पूर्ण

	DPU_DEBUG_CMDENC(cmd_enc, "pp:%d pending_cnt %d\n",
			phys_enc->hw_pp->idx - PINGPONG_0,
			atomic_पढ़ो(&phys_enc->pending_kickoff_cnt));
पूर्ण

अटल bool dpu_encoder_phys_cmd_is_ongoing_pptx(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_pp_vsync_info info;

	अगर (!phys_enc)
		वापस false;

	phys_enc->hw_pp->ops.get_vsync_info(phys_enc->hw_pp, &info);
	अगर (info.wr_ptr_line_count > 0 &&
	    info.wr_ptr_line_count < phys_enc->cached_mode.vdisplay)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_prepare_commit(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);
	पूर्णांक trial = 0;

	अगर (!phys_enc)
		वापस;
	अगर (!phys_enc->hw_pp)
		वापस;
	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		वापस;

	/* If स्वतःrefresh is alपढ़ोy disabled, we have nothing to करो */
	अगर (!phys_enc->hw_pp->ops.get_स्वतःrefresh(phys_enc->hw_pp, शून्य))
		वापस;

	/*
	 * If स्वतःrefresh is enabled, disable it and make sure it is safe to
	 * proceed with current frame commit/push. Sequence fallowed is,
	 * 1. Disable TE
	 * 2. Disable स्वतःrefresh config
	 * 4. Poll क्रम frame transfer ongoing to be false
	 * 5. Enable TE back
	 */
	_dpu_encoder_phys_cmd_connect_te(phys_enc, false);
	phys_enc->hw_pp->ops.setup_स्वतःrefresh(phys_enc->hw_pp, 0, false);

	करो अणु
		udelay(DPU_ENC_MAX_POLL_TIMEOUT_US);
		अगर ((trial * DPU_ENC_MAX_POLL_TIMEOUT_US)
				> (KICKOFF_TIMEOUT_MS * USEC_PER_MSEC)) अणु
			DPU_ERROR_CMDENC(cmd_enc,
					"disable autorefresh failed\n");
			अवरोध;
		पूर्ण

		trial++;
	पूर्ण जबतक (dpu_encoder_phys_cmd_is_ongoing_pptx(phys_enc));

	_dpu_encoder_phys_cmd_connect_te(phys_enc, true);

	DPU_DEBUG_CMDENC(to_dpu_encoder_phys_cmd(phys_enc),
			 "disabled autorefresh\n");
पूर्ण

अटल पूर्णांक _dpu_encoder_phys_cmd_रुको_क्रम_ctl_start(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	काष्ठा dpu_encoder_रुको_info रुको_info;
	पूर्णांक ret;

	रुको_info.wq = &phys_enc->pending_kickoff_wq;
	रुको_info.atomic_cnt = &phys_enc->pending_ctlstart_cnt;
	रुको_info.समयout_ms = KICKOFF_TIMEOUT_MS;

	ret = dpu_encoder_helper_रुको_क्रम_irq(phys_enc, INTR_IDX_CTL_START,
			&रुको_info);
	अगर (ret == -ETIMEDOUT) अणु
		DPU_ERROR_CMDENC(cmd_enc, "ctl start interrupt wait failed\n");
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (!ret)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक dpu_encoder_phys_cmd_रुको_क्रम_tx_complete(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	पूर्णांक rc;

	rc = _dpu_encoder_phys_cmd_रुको_क्रम_idle(phys_enc);
	अगर (rc) अणु
		DRM_ERROR("failed wait_for_idle: id:%u ret:%d intf:%d\n",
			  DRMID(phys_enc->parent), rc,
			  phys_enc->पूर्णांकf_idx - INTF_0);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dpu_encoder_phys_cmd_रुको_क्रम_commit_करोne(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_phys_cmd *cmd_enc;

	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	/* only required क्रम master controller */
	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		वापस 0;

	वापस _dpu_encoder_phys_cmd_रुको_क्रम_ctl_start(phys_enc);
पूर्ण

अटल पूर्णांक dpu_encoder_phys_cmd_रुको_क्रम_vblank(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	पूर्णांक rc = 0;
	काष्ठा dpu_encoder_phys_cmd *cmd_enc;
	काष्ठा dpu_encoder_रुको_info रुको_info;

	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	/* only required क्रम master controller */
	अगर (!dpu_encoder_phys_cmd_is_master(phys_enc))
		वापस rc;

	रुको_info.wq = &cmd_enc->pending_vblank_wq;
	रुको_info.atomic_cnt = &cmd_enc->pending_vblank_cnt;
	रुको_info.समयout_ms = KICKOFF_TIMEOUT_MS;

	atomic_inc(&cmd_enc->pending_vblank_cnt);

	rc = dpu_encoder_helper_रुको_क्रम_irq(phys_enc, INTR_IDX_RDPTR,
			&रुको_info);

	वापस rc;
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_handle_post_kickoff(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	/**
	 * re-enable बाह्यal TE, either क्रम the first समय after enabling
	 * or अगर disabled क्रम Autorefresh
	 */
	_dpu_encoder_phys_cmd_connect_te(phys_enc, true);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_trigger_start(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	dpu_encoder_helper_trigger_start(phys_enc);
पूर्ण

अटल व्योम dpu_encoder_phys_cmd_init_ops(
		काष्ठा dpu_encoder_phys_ops *ops)
अणु
	ops->prepare_commit = dpu_encoder_phys_cmd_prepare_commit;
	ops->is_master = dpu_encoder_phys_cmd_is_master;
	ops->mode_set = dpu_encoder_phys_cmd_mode_set;
	ops->mode_fixup = dpu_encoder_phys_cmd_mode_fixup;
	ops->enable = dpu_encoder_phys_cmd_enable;
	ops->disable = dpu_encoder_phys_cmd_disable;
	ops->destroy = dpu_encoder_phys_cmd_destroy;
	ops->get_hw_resources = dpu_encoder_phys_cmd_get_hw_resources;
	ops->control_vblank_irq = dpu_encoder_phys_cmd_control_vblank_irq;
	ops->रुको_क्रम_commit_करोne = dpu_encoder_phys_cmd_रुको_क्रम_commit_करोne;
	ops->prepare_क्रम_kickoff = dpu_encoder_phys_cmd_prepare_क्रम_kickoff;
	ops->रुको_क्रम_tx_complete = dpu_encoder_phys_cmd_रुको_क्रम_tx_complete;
	ops->रुको_क्रम_vblank = dpu_encoder_phys_cmd_रुको_क्रम_vblank;
	ops->trigger_start = dpu_encoder_phys_cmd_trigger_start;
	ops->needs_single_flush = dpu_encoder_phys_cmd_needs_single_flush;
	ops->irq_control = dpu_encoder_phys_cmd_irq_control;
	ops->restore = dpu_encoder_phys_cmd_enable_helper;
	ops->prepare_idle_pc = dpu_encoder_phys_cmd_prepare_idle_pc;
	ops->handle_post_kickoff = dpu_encoder_phys_cmd_handle_post_kickoff;
	ops->get_line_count = dpu_encoder_phys_cmd_get_line_count;
पूर्ण

काष्ठा dpu_encoder_phys *dpu_encoder_phys_cmd_init(
		काष्ठा dpu_enc_phys_init_params *p)
अणु
	काष्ठा dpu_encoder_phys *phys_enc = शून्य;
	काष्ठा dpu_encoder_phys_cmd *cmd_enc = शून्य;
	काष्ठा dpu_encoder_irq *irq;
	पूर्णांक i, ret = 0;

	DPU_DEBUG("intf %d\n", p->पूर्णांकf_idx - INTF_0);

	cmd_enc = kzalloc(माप(*cmd_enc), GFP_KERNEL);
	अगर (!cmd_enc) अणु
		ret = -ENOMEM;
		DPU_ERROR("failed to allocate\n");
		वापस ERR_PTR(ret);
	पूर्ण
	phys_enc = &cmd_enc->base;
	phys_enc->hw_mdptop = p->dpu_kms->hw_mdp;
	phys_enc->पूर्णांकf_idx = p->पूर्णांकf_idx;

	dpu_encoder_phys_cmd_init_ops(&phys_enc->ops);
	phys_enc->parent = p->parent;
	phys_enc->parent_ops = p->parent_ops;
	phys_enc->dpu_kms = p->dpu_kms;
	phys_enc->split_role = p->split_role;
	phys_enc->पूर्णांकf_mode = INTF_MODE_CMD;
	phys_enc->enc_spinlock = p->enc_spinlock;
	cmd_enc->stream_sel = 0;
	phys_enc->enable_state = DPU_ENC_DISABLED;
	क्रम (i = 0; i < INTR_IDX_MAX; i++) अणु
		irq = &phys_enc->irq[i];
		INIT_LIST_HEAD(&irq->cb.list);
		irq->irq_idx = -EINVAL;
		irq->hw_idx = -EINVAL;
		irq->cb.arg = phys_enc;
	पूर्ण

	irq = &phys_enc->irq[INTR_IDX_CTL_START];
	irq->name = "ctl_start";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_CTL_START;
	irq->पूर्णांकr_idx = INTR_IDX_CTL_START;
	irq->cb.func = dpu_encoder_phys_cmd_ctl_start_irq;

	irq = &phys_enc->irq[INTR_IDX_PINGPONG];
	irq->name = "pp_done";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_PING_PONG_COMP;
	irq->पूर्णांकr_idx = INTR_IDX_PINGPONG;
	irq->cb.func = dpu_encoder_phys_cmd_pp_tx_करोne_irq;

	irq = &phys_enc->irq[INTR_IDX_RDPTR];
	irq->name = "pp_rd_ptr";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_PING_PONG_RD_PTR;
	irq->पूर्णांकr_idx = INTR_IDX_RDPTR;
	irq->cb.func = dpu_encoder_phys_cmd_pp_rd_ptr_irq;

	irq = &phys_enc->irq[INTR_IDX_UNDERRUN];
	irq->name = "underrun";
	irq->पूर्णांकr_type = DPU_IRQ_TYPE_INTF_UNDER_RUN;
	irq->पूर्णांकr_idx = INTR_IDX_UNDERRUN;
	irq->cb.func = dpu_encoder_phys_cmd_underrun_irq;

	atomic_set(&phys_enc->vblank_refcount, 0);
	atomic_set(&phys_enc->pending_kickoff_cnt, 0);
	atomic_set(&phys_enc->pending_ctlstart_cnt, 0);
	atomic_set(&cmd_enc->pending_vblank_cnt, 0);
	init_रुकोqueue_head(&phys_enc->pending_kickoff_wq);
	init_रुकोqueue_head(&cmd_enc->pending_vblank_wq);

	DPU_DEBUG_CMDENC(cmd_enc, "created\n");

	वापस phys_enc;
पूर्ण
