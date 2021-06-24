<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__
#समावेश <linux/debugfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "msm_drv.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_intf.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_hw_dspp.h"
#समावेश "dpu_formats.h"
#समावेश "dpu_encoder_phys.h"
#समावेश "dpu_crtc.h"
#समावेश "dpu_trace.h"
#समावेश "dpu_core_irq.h"

#घोषणा DPU_DEBUG_ENC(e, fmt, ...) DPU_DEBUG("enc%d " fmt,\
		(e) ? (e)->base.base.id : -1, ##__VA_ARGS__)

#घोषणा DPU_ERROR_ENC(e, fmt, ...) DPU_ERROR("enc%d " fmt,\
		(e) ? (e)->base.base.id : -1, ##__VA_ARGS__)

#घोषणा DPU_DEBUG_PHYS(p, fmt, ...) DPU_DEBUG("enc%d intf%d pp%d " fmt,\
		(p) ? (p)->parent->base.id : -1, \
		(p) ? (p)->पूर्णांकf_idx - INTF_0 : -1, \
		(p) ? ((p)->hw_pp ? (p)->hw_pp->idx - PINGPONG_0 : -1) : -1, \
		##__VA_ARGS__)

#घोषणा DPU_ERROR_PHYS(p, fmt, ...) DPU_ERROR("enc%d intf%d pp%d " fmt,\
		(p) ? (p)->parent->base.id : -1, \
		(p) ? (p)->पूर्णांकf_idx - INTF_0 : -1, \
		(p) ? ((p)->hw_pp ? (p)->hw_pp->idx - PINGPONG_0 : -1) : -1, \
		##__VA_ARGS__)

/*
 * Two to anticipate panels that can करो cmd/vid dynamic चयनing
 * plan is to create all possible physical encoder types, and चयन between
 * them at runसमय
 */
#घोषणा NUM_PHYS_ENCODER_TYPES 2

#घोषणा MAX_PHYS_ENCODERS_PER_VIRTUAL \
	(MAX_H_TILES_PER_DISPLAY * NUM_PHYS_ENCODER_TYPES)

#घोषणा MAX_CHANNELS_PER_ENC 2

#घोषणा IDLE_SHORT_TIMEOUT	1

#घोषणा MAX_HDISPLAY_SPLIT 1080

/* समयout in frames रुकोing क्रम frame करोne */
#घोषणा DPU_ENCODER_FRAME_DONE_TIMEOUT_FRAMES 5

/**
 * क्रमागत dpu_enc_rc_events - events क्रम resource control state machine
 * @DPU_ENC_RC_EVENT_KICKOFF:
 *	This event happens at NORMAL priority.
 *	Event that संकेतs the start of the transfer. When this event is
 *	received, enable MDP/DSI core घड़ीs. Regardless of the previous
 *	state, the resource should be in ON state at the end of this event.
 * @DPU_ENC_RC_EVENT_FRAME_DONE:
 *	This event happens at INTERRUPT level.
 *	Event संकेतs the end of the data transfer after the PP FRAME_DONE
 *	event. At the end of this event, a delayed work is scheduled to go to
 *	IDLE_PC state after IDLE_TIMEOUT समय.
 * @DPU_ENC_RC_EVENT_PRE_STOP:
 *	This event happens at NORMAL priority.
 *	This event, when received during the ON state, leave the RC STATE
 *	in the PRE_OFF state. It should be followed by the STOP event as
 *	part of encoder disable.
 *	If received during IDLE or OFF states, it will करो nothing.
 * @DPU_ENC_RC_EVENT_STOP:
 *	This event happens at NORMAL priority.
 *	When this event is received, disable all the MDP/DSI core घड़ीs, and
 *	disable IRQs. It should be called from the PRE_OFF or IDLE states.
 *	IDLE is expected when IDLE_PC has run, and PRE_OFF did nothing.
 *	PRE_OFF is expected when PRE_STOP was executed during the ON state.
 *	Resource state should be in OFF at the end of the event.
 * @DPU_ENC_RC_EVENT_ENTER_IDLE:
 *	This event happens at NORMAL priority from a work item.
 *	Event संकेतs that there were no frame updates क्रम IDLE_TIMEOUT समय.
 *	This would disable MDP/DSI core घड़ीs and change the resource state
 *	to IDLE.
 */
क्रमागत dpu_enc_rc_events अणु
	DPU_ENC_RC_EVENT_KICKOFF = 1,
	DPU_ENC_RC_EVENT_FRAME_DONE,
	DPU_ENC_RC_EVENT_PRE_STOP,
	DPU_ENC_RC_EVENT_STOP,
	DPU_ENC_RC_EVENT_ENTER_IDLE
पूर्ण;

/*
 * क्रमागत dpu_enc_rc_states - states that the resource control मुख्यtains
 * @DPU_ENC_RC_STATE_OFF: Resource is in OFF state
 * @DPU_ENC_RC_STATE_PRE_OFF: Resource is transitioning to OFF state
 * @DPU_ENC_RC_STATE_ON: Resource is in ON state
 * @DPU_ENC_RC_STATE_MODESET: Resource is in modeset state
 * @DPU_ENC_RC_STATE_IDLE: Resource is in IDLE state
 */
क्रमागत dpu_enc_rc_states अणु
	DPU_ENC_RC_STATE_OFF,
	DPU_ENC_RC_STATE_PRE_OFF,
	DPU_ENC_RC_STATE_ON,
	DPU_ENC_RC_STATE_IDLE
पूर्ण;

/**
 * काष्ठा dpu_encoder_virt - भव encoder. Container of one or more physical
 *	encoders. Virtual encoder manages one "logical" display. Physical
 *	encoders manage one पूर्णांकf block, tied to a specअगरic panel/sub-panel.
 *	Virtual encoder defers as much as possible to the physical encoders.
 *	Virtual encoder रेजिस्टरs itself with the DRM Framework as the encoder.
 * @base:		drm_encoder base class क्रम registration with DRM
 * @enc_spinlock:	Virtual-Encoder-Wide Spin Lock क्रम IRQ purposes
 * @bus_scaling_client:	Client handle to the bus scaling पूर्णांकerface
 * @enabled:		True अगर the encoder is active, रक्षित by enc_lock
 * @num_phys_encs:	Actual number of physical encoders contained.
 * @phys_encs:		Container of physical encoders managed.
 * @cur_master:		Poपूर्णांकer to the current master in this mode. Optimization
 *			Only valid after enable. Cleared as disable.
 * @cur_slave:		As above but क्रम the slave encoder.
 * @hw_pp:		Handle to the pingpong blocks used क्रम the display. No.
 *			pingpong blocks can be dअगरferent than num_phys_encs.
 * @पूर्णांकfs_swapped:	Whether or not the phys_enc पूर्णांकerfaces have been swapped
 *			क्रम partial update right-only हालs, such as pingpong
 *			split where भव pingpong करोes not generate IRQs
 * @crtc:		Poपूर्णांकer to the currently asचिन्हित crtc. Normally you
 *			would use crtc->state->encoder_mask to determine the
 *			link between encoder/crtc. However in this हाल we need
 *			to track crtc in the disable() hook which is called
 *			_after_ encoder_mask is cleared.
 * @crtc_kickoff_cb:		Callback पूर्णांकo CRTC that will flush & start
 *				all CTL paths
 * @crtc_kickoff_cb_data:	Opaque user data given to crtc_kickoff_cb
 * @debugfs_root:		Debug file प्रणाली root file node
 * @enc_lock:			Lock around physical encoder
 *				create/destroy/enable/disable
 * @frame_busy_mask:		Biपंचांगask tracking which phys_enc we are still
 *				busy processing current command.
 *				Bit0 = phys_encs[0] etc.
 * @crtc_frame_event_cb:	callback handler क्रम frame event
 * @crtc_frame_event_cb_data:	callback handler निजी data
 * @frame_करोne_समयout_ms:	frame करोne समयout in ms
 * @frame_करोne_समयr:		watchकरोg समयr क्रम frame करोne event
 * @vsync_event_समयr:		vsync समयr
 * @disp_info:			local copy of msm_display_info काष्ठा
 * @idle_pc_supported:		indicate अगर idle घातer collaps is supported
 * @rc_lock:			resource control mutex lock to protect
 *				virt encoder over various state changes
 * @rc_state:			resource controller state
 * @delayed_off_work:		delayed worker to schedule disabling of
 *				clks and resources after IDLE_TIMEOUT समय.
 * @vsync_event_work:		worker to handle vsync event क्रम स्वतःrefresh
 * @topology:                   topology of the display
 * @idle_समयout:		idle समयout duration in milliseconds
 */
काष्ठा dpu_encoder_virt अणु
	काष्ठा drm_encoder base;
	spinlock_t enc_spinlock;
	uपूर्णांक32_t bus_scaling_client;

	bool enabled;

	अचिन्हित पूर्णांक num_phys_encs;
	काष्ठा dpu_encoder_phys *phys_encs[MAX_PHYS_ENCODERS_PER_VIRTUAL];
	काष्ठा dpu_encoder_phys *cur_master;
	काष्ठा dpu_encoder_phys *cur_slave;
	काष्ठा dpu_hw_pingpong *hw_pp[MAX_CHANNELS_PER_ENC];

	bool पूर्णांकfs_swapped;

	काष्ठा drm_crtc *crtc;

	काष्ठा dentry *debugfs_root;
	काष्ठा mutex enc_lock;
	DECLARE_BITMAP(frame_busy_mask, MAX_PHYS_ENCODERS_PER_VIRTUAL);
	व्योम (*crtc_frame_event_cb)(व्योम *, u32 event);
	व्योम *crtc_frame_event_cb_data;

	atomic_t frame_करोne_समयout_ms;
	काष्ठा समयr_list frame_करोne_समयr;
	काष्ठा समयr_list vsync_event_समयr;

	काष्ठा msm_display_info disp_info;

	bool idle_pc_supported;
	काष्ठा mutex rc_lock;
	क्रमागत dpu_enc_rc_states rc_state;
	काष्ठा delayed_work delayed_off_work;
	काष्ठा kthपढ़ो_work vsync_event_work;
	काष्ठा msm_display_topology topology;

	u32 idle_समयout;
पूर्ण;

#घोषणा to_dpu_encoder_virt(x) container_of(x, काष्ठा dpu_encoder_virt, base)

अटल u32 dither_matrix[DITHER_MATRIX_SZ] = अणु
	15, 7, 13, 5, 3, 11, 1, 9, 12, 4, 14, 6, 0, 8, 2, 10
पूर्ण;

अटल व्योम _dpu_encoder_setup_dither(काष्ठा dpu_hw_pingpong *hw_pp, अचिन्हित bpc)
अणु
	काष्ठा dpu_hw_dither_cfg dither_cfg = अणु 0 पूर्ण;

	अगर (!hw_pp->ops.setup_dither)
		वापस;

	चयन (bpc) अणु
	हाल 6:
		dither_cfg.c0_bitdepth = 6;
		dither_cfg.c1_bitdepth = 6;
		dither_cfg.c2_bitdepth = 6;
		dither_cfg.c3_bitdepth = 6;
		dither_cfg.temporal_en = 0;
		अवरोध;
	शेष:
		hw_pp->ops.setup_dither(hw_pp, शून्य);
		वापस;
	पूर्ण

	स_नकल(&dither_cfg.matrix, dither_matrix,
			माप(u32) * DITHER_MATRIX_SZ);

	hw_pp->ops.setup_dither(hw_pp, &dither_cfg);
पूर्ण

व्योम dpu_encoder_helper_report_irq_समयout(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx)
अणु
	DRM_ERROR("irq timeout id=%u, intf=%d, pp=%d, intr=%d\n",
		  DRMID(phys_enc->parent), phys_enc->पूर्णांकf_idx - INTF_0,
		  phys_enc->hw_pp->idx - PINGPONG_0, पूर्णांकr_idx);

	अगर (phys_enc->parent_ops->handle_frame_करोne)
		phys_enc->parent_ops->handle_frame_करोne(
				phys_enc->parent, phys_enc,
				DPU_ENCODER_FRAME_EVENT_ERROR);
पूर्ण

अटल पूर्णांक dpu_encoder_helper_रुको_event_समयout(पूर्णांक32_t drm_id,
		पूर्णांक32_t hw_id, काष्ठा dpu_encoder_रुको_info *info);

पूर्णांक dpu_encoder_helper_रुको_क्रम_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx,
		काष्ठा dpu_encoder_रुको_info *रुको_info)
अणु
	काष्ठा dpu_encoder_irq *irq;
	u32 irq_status;
	पूर्णांक ret;

	अगर (!रुको_info || पूर्णांकr_idx >= INTR_IDX_MAX) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण
	irq = &phys_enc->irq[पूर्णांकr_idx];

	/* note: करो master / slave checking outside */

	/* वापस EWOULDBLOCK since we know the रुको isn't necessary */
	अगर (phys_enc->enable_state == DPU_ENC_DISABLED) अणु
		DRM_ERROR("encoder is disabled id=%u, intr=%d, hw=%d, irq=%d",
			  DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			  irq->irq_idx);
		वापस -EWOULDBLOCK;
	पूर्ण

	अगर (irq->irq_idx < 0) अणु
		DRM_DEBUG_KMS("skip irq wait id=%u, intr=%d, hw=%d, irq=%s",
			      DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			      irq->name);
		वापस 0;
	पूर्ण

	DRM_DEBUG_KMS("id=%u, intr=%d, hw=%d, irq=%d, pp=%d, pending_cnt=%d",
		      DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
		      irq->irq_idx, phys_enc->hw_pp->idx - PINGPONG_0,
		      atomic_पढ़ो(रुको_info->atomic_cnt));

	ret = dpu_encoder_helper_रुको_event_समयout(
			DRMID(phys_enc->parent),
			irq->hw_idx,
			रुको_info);

	अगर (ret <= 0) अणु
		irq_status = dpu_core_irq_पढ़ो(phys_enc->dpu_kms,
				irq->irq_idx, true);
		अगर (irq_status) अणु
			अचिन्हित दीर्घ flags;

			DRM_DEBUG_KMS("irq not triggered id=%u, intr=%d, "
				      "hw=%d, irq=%d, pp=%d, atomic_cnt=%d",
				      DRMID(phys_enc->parent), पूर्णांकr_idx,
				      irq->hw_idx, irq->irq_idx,
				      phys_enc->hw_pp->idx - PINGPONG_0,
				      atomic_पढ़ो(रुको_info->atomic_cnt));
			local_irq_save(flags);
			irq->cb.func(phys_enc, irq->irq_idx);
			local_irq_restore(flags);
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = -ETIMEDOUT;
			DRM_DEBUG_KMS("irq timeout id=%u, intr=%d, "
				      "hw=%d, irq=%d, pp=%d, atomic_cnt=%d",
				      DRMID(phys_enc->parent), पूर्णांकr_idx,
				      irq->hw_idx, irq->irq_idx,
				      phys_enc->hw_pp->idx - PINGPONG_0,
				      atomic_पढ़ो(रुको_info->atomic_cnt));
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
		trace_dpu_enc_irq_रुको_success(DRMID(phys_enc->parent),
			पूर्णांकr_idx, irq->hw_idx, irq->irq_idx,
			phys_enc->hw_pp->idx - PINGPONG_0,
			atomic_पढ़ो(रुको_info->atomic_cnt));
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dpu_encoder_helper_रेजिस्टर_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx)
अणु
	काष्ठा dpu_encoder_irq *irq;
	पूर्णांक ret = 0;

	अगर (पूर्णांकr_idx >= INTR_IDX_MAX) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण
	irq = &phys_enc->irq[पूर्णांकr_idx];

	अगर (irq->irq_idx >= 0) अणु
		DPU_DEBUG_PHYS(phys_enc,
				"skipping already registered irq %s type %d\n",
				irq->name, irq->पूर्णांकr_type);
		वापस 0;
	पूर्ण

	irq->irq_idx = dpu_core_irq_idx_lookup(phys_enc->dpu_kms,
			irq->पूर्णांकr_type, irq->hw_idx);
	अगर (irq->irq_idx < 0) अणु
		DPU_ERROR_PHYS(phys_enc,
			"failed to lookup IRQ index for %s type:%d\n",
			irq->name, irq->पूर्णांकr_type);
		वापस -EINVAL;
	पूर्ण

	ret = dpu_core_irq_रेजिस्टर_callback(phys_enc->dpu_kms, irq->irq_idx,
			&irq->cb);
	अगर (ret) अणु
		DPU_ERROR_PHYS(phys_enc,
			"failed to register IRQ callback for %s\n",
			irq->name);
		irq->irq_idx = -EINVAL;
		वापस ret;
	पूर्ण

	ret = dpu_core_irq_enable(phys_enc->dpu_kms, &irq->irq_idx, 1);
	अगर (ret) अणु
		DRM_ERROR("enable failed id=%u, intr=%d, hw=%d, irq=%d",
			  DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			  irq->irq_idx);
		dpu_core_irq_unरेजिस्टर_callback(phys_enc->dpu_kms,
				irq->irq_idx, &irq->cb);
		irq->irq_idx = -EINVAL;
		वापस ret;
	पूर्ण

	trace_dpu_enc_irq_रेजिस्टर_success(DRMID(phys_enc->parent), पूर्णांकr_idx,
				irq->hw_idx, irq->irq_idx);

	वापस ret;
पूर्ण

पूर्णांक dpu_encoder_helper_unरेजिस्टर_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx)
अणु
	काष्ठा dpu_encoder_irq *irq;
	पूर्णांक ret;

	irq = &phys_enc->irq[पूर्णांकr_idx];

	/* silently skip irqs that weren't रेजिस्टरed */
	अगर (irq->irq_idx < 0) अणु
		DRM_ERROR("duplicate unregister id=%u, intr=%d, hw=%d, irq=%d",
			  DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			  irq->irq_idx);
		वापस 0;
	पूर्ण

	ret = dpu_core_irq_disable(phys_enc->dpu_kms, &irq->irq_idx, 1);
	अगर (ret) अणु
		DRM_ERROR("disable failed id=%u, intr=%d, hw=%d, irq=%d ret=%d",
			  DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			  irq->irq_idx, ret);
	पूर्ण

	ret = dpu_core_irq_unरेजिस्टर_callback(phys_enc->dpu_kms, irq->irq_idx,
			&irq->cb);
	अगर (ret) अणु
		DRM_ERROR("unreg cb fail id=%u, intr=%d, hw=%d, irq=%d ret=%d",
			  DRMID(phys_enc->parent), पूर्णांकr_idx, irq->hw_idx,
			  irq->irq_idx, ret);
	पूर्ण

	trace_dpu_enc_irq_unरेजिस्टर_success(DRMID(phys_enc->parent), पूर्णांकr_idx,
					     irq->hw_idx, irq->irq_idx);

	irq->irq_idx = -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक dpu_encoder_get_frame_count(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	पूर्णांक framecount = 0;

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	phys = dpu_enc ? dpu_enc->cur_master : शून्य;

	अगर (phys && phys->ops.get_frame_count)
		framecount = phys->ops.get_frame_count(phys);

	वापस framecount;
पूर्ण

पूर्णांक dpu_encoder_get_linecount(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	पूर्णांक linecount = 0;

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	phys = dpu_enc ? dpu_enc->cur_master : शून्य;

	अगर (phys && phys->ops.get_line_count)
		linecount = phys->ops.get_line_count(phys);

	वापस linecount;
पूर्ण

व्योम dpu_encoder_get_hw_resources(काष्ठा drm_encoder *drm_enc,
				  काष्ठा dpu_encoder_hw_resources *hw_res)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक i = 0;

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	/* Query resources used by phys encs, expected to be without overlap */
	स_रखो(hw_res, 0, माप(*hw_res));

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.get_hw_resources)
			phys->ops.get_hw_resources(phys, hw_res);
	पूर्ण
पूर्ण

अटल व्योम dpu_encoder_destroy(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक i = 0;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	mutex_lock(&dpu_enc->enc_lock);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.destroy) अणु
			phys->ops.destroy(phys);
			--dpu_enc->num_phys_encs;
			dpu_enc->phys_encs[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (dpu_enc->num_phys_encs)
		DPU_ERROR_ENC(dpu_enc, "expected 0 num_phys_encs not %d\n",
				dpu_enc->num_phys_encs);
	dpu_enc->num_phys_encs = 0;
	mutex_unlock(&dpu_enc->enc_lock);

	drm_encoder_cleanup(drm_enc);
	mutex_destroy(&dpu_enc->enc_lock);
पूर्ण

व्योम dpu_encoder_helper_split_config(
		काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकf पूर्णांकerface)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा split_pipe_cfg cfg = अणु 0 पूर्ण;
	काष्ठा dpu_hw_mdp *hw_mdptop;
	काष्ठा msm_display_info *disp_info;

	अगर (!phys_enc->hw_mdptop || !phys_enc->parent) अणु
		DPU_ERROR("invalid arg(s), encoder %d\n", phys_enc != शून्य);
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(phys_enc->parent);
	hw_mdptop = phys_enc->hw_mdptop;
	disp_info = &dpu_enc->disp_info;

	अगर (disp_info->पूर्णांकf_type != DRM_MODE_ENCODER_DSI)
		वापस;

	/**
	 * disable split modes since encoder will be operating in as the only
	 * encoder, either क्रम the entire use हाल in the हाल of, क्रम example,
	 * single DSI, or क्रम this frame in the हाल of left/right only partial
	 * update.
	 */
	अगर (phys_enc->split_role == ENC_ROLE_SOLO) अणु
		अगर (hw_mdptop->ops.setup_split_pipe)
			hw_mdptop->ops.setup_split_pipe(hw_mdptop, &cfg);
		वापस;
	पूर्ण

	cfg.en = true;
	cfg.mode = phys_enc->पूर्णांकf_mode;
	cfg.पूर्णांकf = पूर्णांकerface;

	अगर (cfg.en && phys_enc->ops.needs_single_flush &&
			phys_enc->ops.needs_single_flush(phys_enc))
		cfg.split_flush_en = true;

	अगर (phys_enc->split_role == ENC_ROLE_MASTER) अणु
		DPU_DEBUG_ENC(dpu_enc, "enable %d\n", cfg.en);

		अगर (hw_mdptop->ops.setup_split_pipe)
			hw_mdptop->ops.setup_split_pipe(hw_mdptop, &cfg);
	पूर्ण
पूर्ण

अटल काष्ठा msm_display_topology dpu_encoder_get_topology(
			काष्ठा dpu_encoder_virt *dpu_enc,
			काष्ठा dpu_kms *dpu_kms,
			काष्ठा drm_display_mode *mode)
अणु
	काष्ठा msm_display_topology topology = अणु0पूर्ण;
	पूर्णांक i, पूर्णांकf_count = 0;

	क्रम (i = 0; i < MAX_PHYS_ENCODERS_PER_VIRTUAL; i++)
		अगर (dpu_enc->phys_encs[i])
			पूर्णांकf_count++;

	/* Datapath topology selection
	 *
	 * Dual display
	 * 2 LM, 2 INTF ( Split display using 2 पूर्णांकerfaces)
	 *
	 * Single display
	 * 1 LM, 1 INTF
	 * 2 LM, 1 INTF (stream merge to support high resolution पूर्णांकerfaces)
	 *
	 * Adding color blocks only to primary पूर्णांकerface अगर available in
	 * sufficient number
	 */
	अगर (पूर्णांकf_count == 2)
		topology.num_lm = 2;
	अन्यथा अगर (!dpu_kms->catalog->caps->has_3d_merge)
		topology.num_lm = 1;
	अन्यथा
		topology.num_lm = (mode->hdisplay > MAX_HDISPLAY_SPLIT) ? 2 : 1;

	अगर (dpu_enc->disp_info.पूर्णांकf_type == DRM_MODE_ENCODER_DSI) अणु
		अगर (dpu_kms->catalog->dspp &&
			(dpu_kms->catalog->dspp_count >= topology.num_lm))
			topology.num_dspp = topology.num_lm;
	पूर्ण

	topology.num_enc = 0;
	topology.num_पूर्णांकf = पूर्णांकf_count;

	वापस topology;
पूर्ण
अटल पूर्णांक dpu_encoder_virt_atomic_check(
		काष्ठा drm_encoder *drm_enc,
		काष्ठा drm_crtc_state *crtc_state,
		काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms;
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा drm_display_mode *adj_mode;
	काष्ठा msm_display_topology topology;
	काष्ठा dpu_global_state *global_state;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	अगर (!drm_enc || !crtc_state || !conn_state) अणु
		DPU_ERROR("invalid arg(s), drm_enc %d, crtc/conn state %d/%d\n",
				drm_enc != शून्य, crtc_state != शून्य, conn_state != शून्य);
		वापस -EINVAL;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	priv = drm_enc->dev->dev_निजी;
	dpu_kms = to_dpu_kms(priv->kms);
	mode = &crtc_state->mode;
	adj_mode = &crtc_state->adjusted_mode;
	global_state = dpu_kms_get_global_state(crtc_state->state);
	अगर (IS_ERR(global_state))
		वापस PTR_ERR(global_state);

	trace_dpu_enc_atomic_check(DRMID(drm_enc));

	/* perक्रमm atomic check on the first physical encoder (master) */
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.atomic_check)
			ret = phys->ops.atomic_check(phys, crtc_state,
					conn_state);
		अन्यथा अगर (phys->ops.mode_fixup)
			अगर (!phys->ops.mode_fixup(phys, mode, adj_mode))
				ret = -EINVAL;

		अगर (ret) अणु
			DPU_ERROR_ENC(dpu_enc,
					"mode unsupported, phys idx %d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	topology = dpu_encoder_get_topology(dpu_enc, dpu_kms, adj_mode);

	/* Reserve dynamic resources now. */
	अगर (!ret) अणु
		/*
		 * Release and Allocate resources on every modeset
		 * Dont allocate when active is false.
		 */
		अगर (drm_atomic_crtc_needs_modeset(crtc_state)) अणु
			dpu_rm_release(global_state, drm_enc);

			अगर (!crtc_state->active_changed || crtc_state->active)
				ret = dpu_rm_reserve(&dpu_kms->rm, global_state,
						drm_enc, crtc_state, topology);
		पूर्ण
	पूर्ण

	trace_dpu_enc_atomic_check_flags(DRMID(drm_enc), adj_mode->flags);

	वापस ret;
पूर्ण

अटल व्योम _dpu_encoder_update_vsync_source(काष्ठा dpu_encoder_virt *dpu_enc,
			काष्ठा msm_display_info *disp_info)
अणु
	काष्ठा dpu_vsync_source_cfg vsync_cfg = अणु 0 पूर्ण;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा dpu_hw_mdp *hw_mdptop;
	काष्ठा drm_encoder *drm_enc;
	पूर्णांक i;

	अगर (!dpu_enc || !disp_info) अणु
		DPU_ERROR("invalid param dpu_enc:%d or disp_info:%d\n",
					dpu_enc != शून्य, disp_info != शून्य);
		वापस;
	पूर्ण अन्यथा अगर (dpu_enc->num_phys_encs > ARRAY_SIZE(dpu_enc->hw_pp)) अणु
		DPU_ERROR("invalid num phys enc %d/%d\n",
				dpu_enc->num_phys_encs,
				(पूर्णांक) ARRAY_SIZE(dpu_enc->hw_pp));
		वापस;
	पूर्ण

	drm_enc = &dpu_enc->base;
	/* this poपूर्णांकers are checked in virt_enable_helper */
	priv = drm_enc->dev->dev_निजी;

	dpu_kms = to_dpu_kms(priv->kms);
	hw_mdptop = dpu_kms->hw_mdp;
	अगर (!hw_mdptop) अणु
		DPU_ERROR("invalid mdptop\n");
		वापस;
	पूर्ण

	अगर (hw_mdptop->ops.setup_vsync_source &&
			disp_info->capabilities & MSM_DISPLAY_CAP_CMD_MODE) अणु
		क्रम (i = 0; i < dpu_enc->num_phys_encs; i++)
			vsync_cfg.ppnumber[i] = dpu_enc->hw_pp[i]->idx;

		vsync_cfg.pp_count = dpu_enc->num_phys_encs;
		अगर (disp_info->is_te_using_watchकरोg_समयr)
			vsync_cfg.vsync_source = DPU_VSYNC_SOURCE_WD_TIMER_0;
		अन्यथा
			vsync_cfg.vsync_source = DPU_VSYNC0_SOURCE_GPIO;

		hw_mdptop->ops.setup_vsync_source(hw_mdptop, &vsync_cfg);
	पूर्ण
पूर्ण

अटल व्योम _dpu_encoder_irq_control(काष्ठा drm_encoder *drm_enc, bool enable)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	पूर्णांक i;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);

	DPU_DEBUG_ENC(dpu_enc, "enable:%d\n", enable);
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.irq_control)
			phys->ops.irq_control(phys, enable);
	पूर्ण

पूर्ण

अटल व्योम _dpu_encoder_resource_control_helper(काष्ठा drm_encoder *drm_enc,
		bool enable)
अणु
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा dpu_encoder_virt *dpu_enc;

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	priv = drm_enc->dev->dev_निजी;
	dpu_kms = to_dpu_kms(priv->kms);

	trace_dpu_enc_rc_helper(DRMID(drm_enc), enable);

	अगर (!dpu_enc->cur_master) अणु
		DPU_ERROR("encoder master not set\n");
		वापस;
	पूर्ण

	अगर (enable) अणु
		/* enable DPU core clks */
		pm_runसमय_get_sync(&dpu_kms->pdev->dev);

		/* enable all the irq */
		_dpu_encoder_irq_control(drm_enc, true);

	पूर्ण अन्यथा अणु
		/* disable all the irq */
		_dpu_encoder_irq_control(drm_enc, false);

		/* disable DPU core clks */
		pm_runसमय_put_sync(&dpu_kms->pdev->dev);
	पूर्ण

पूर्ण

अटल पूर्णांक dpu_encoder_resource_control(काष्ठा drm_encoder *drm_enc,
		u32 sw_event)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा msm_drm_निजी *priv;
	bool is_vid_mode = false;

	अगर (!drm_enc || !drm_enc->dev || !drm_enc->crtc) अणु
		DPU_ERROR("invalid parameters\n");
		वापस -EINVAL;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(drm_enc);
	priv = drm_enc->dev->dev_निजी;
	is_vid_mode = dpu_enc->disp_info.capabilities &
						MSM_DISPLAY_CAP_VID_MODE;

	/*
	 * when idle_pc is not supported, process only KICKOFF, STOP and MODESET
	 * events and वापस early क्रम other events (ie wb display).
	 */
	अगर (!dpu_enc->idle_pc_supported &&
			(sw_event != DPU_ENC_RC_EVENT_KICKOFF &&
			sw_event != DPU_ENC_RC_EVENT_STOP &&
			sw_event != DPU_ENC_RC_EVENT_PRE_STOP))
		वापस 0;

	trace_dpu_enc_rc(DRMID(drm_enc), sw_event, dpu_enc->idle_pc_supported,
			 dpu_enc->rc_state, "begin");

	चयन (sw_event) अणु
	हाल DPU_ENC_RC_EVENT_KICKOFF:
		/* cancel delayed off work, अगर any */
		अगर (cancel_delayed_work_sync(&dpu_enc->delayed_off_work))
			DPU_DEBUG_ENC(dpu_enc, "sw_event:%d, work cancelled\n",
					sw_event);

		mutex_lock(&dpu_enc->rc_lock);

		/* वापस अगर the resource control is alपढ़ोy in ON state */
		अगर (dpu_enc->rc_state == DPU_ENC_RC_STATE_ON) अणु
			DRM_DEBUG_KMS("id;%u, sw_event:%d, rc in ON state\n",
				      DRMID(drm_enc), sw_event);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस 0;
		पूर्ण अन्यथा अगर (dpu_enc->rc_state != DPU_ENC_RC_STATE_OFF &&
				dpu_enc->rc_state != DPU_ENC_RC_STATE_IDLE) अणु
			DRM_DEBUG_KMS("id;%u, sw_event:%d, rc in state %d\n",
				      DRMID(drm_enc), sw_event,
				      dpu_enc->rc_state);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस -EINVAL;
		पूर्ण

		अगर (is_vid_mode && dpu_enc->rc_state == DPU_ENC_RC_STATE_IDLE)
			_dpu_encoder_irq_control(drm_enc, true);
		अन्यथा
			_dpu_encoder_resource_control_helper(drm_enc, true);

		dpu_enc->rc_state = DPU_ENC_RC_STATE_ON;

		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "kickoff");

		mutex_unlock(&dpu_enc->rc_lock);
		अवरोध;

	हाल DPU_ENC_RC_EVENT_FRAME_DONE:
		/*
		 * mutex lock is not used as this event happens at पूर्णांकerrupt
		 * context. And locking is not required as, the other events
		 * like KICKOFF and STOP करोes a रुको-क्रम-idle beक्रमe executing
		 * the resource_control
		 */
		अगर (dpu_enc->rc_state != DPU_ENC_RC_STATE_ON) अणु
			DRM_DEBUG_KMS("id:%d, sw_event:%d,rc:%d-unexpected\n",
				      DRMID(drm_enc), sw_event,
				      dpu_enc->rc_state);
			वापस -EINVAL;
		पूर्ण

		/*
		 * schedule off work item only when there are no
		 * frames pending
		 */
		अगर (dpu_crtc_frame_pending(drm_enc->crtc) > 1) अणु
			DRM_DEBUG_KMS("id:%d skip schedule work\n",
				      DRMID(drm_enc));
			वापस 0;
		पूर्ण

		queue_delayed_work(priv->wq, &dpu_enc->delayed_off_work,
				   msecs_to_jअगरfies(dpu_enc->idle_समयout));

		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "frame done");
		अवरोध;

	हाल DPU_ENC_RC_EVENT_PRE_STOP:
		/* cancel delayed off work, अगर any */
		अगर (cancel_delayed_work_sync(&dpu_enc->delayed_off_work))
			DPU_DEBUG_ENC(dpu_enc, "sw_event:%d, work cancelled\n",
					sw_event);

		mutex_lock(&dpu_enc->rc_lock);

		अगर (is_vid_mode &&
			  dpu_enc->rc_state == DPU_ENC_RC_STATE_IDLE) अणु
			_dpu_encoder_irq_control(drm_enc, true);
		पूर्ण
		/* skip अगर is alपढ़ोy OFF or IDLE, resources are off alपढ़ोy */
		अन्यथा अगर (dpu_enc->rc_state == DPU_ENC_RC_STATE_OFF ||
				dpu_enc->rc_state == DPU_ENC_RC_STATE_IDLE) अणु
			DRM_DEBUG_KMS("id:%u, sw_event:%d, rc in %d state\n",
				      DRMID(drm_enc), sw_event,
				      dpu_enc->rc_state);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस 0;
		पूर्ण

		dpu_enc->rc_state = DPU_ENC_RC_STATE_PRE_OFF;

		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "pre stop");

		mutex_unlock(&dpu_enc->rc_lock);
		अवरोध;

	हाल DPU_ENC_RC_EVENT_STOP:
		mutex_lock(&dpu_enc->rc_lock);

		/* वापस अगर the resource control is alपढ़ोy in OFF state */
		अगर (dpu_enc->rc_state == DPU_ENC_RC_STATE_OFF) अणु
			DRM_DEBUG_KMS("id: %u, sw_event:%d, rc in OFF state\n",
				      DRMID(drm_enc), sw_event);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस 0;
		पूर्ण अन्यथा अगर (dpu_enc->rc_state == DPU_ENC_RC_STATE_ON) अणु
			DRM_ERROR("id: %u, sw_event:%d, rc in state %d\n",
				  DRMID(drm_enc), sw_event, dpu_enc->rc_state);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस -EINVAL;
		पूर्ण

		/**
		 * expect to arrive here only अगर in either idle state or pre-off
		 * and in IDLE state the resources are alपढ़ोy disabled
		 */
		अगर (dpu_enc->rc_state == DPU_ENC_RC_STATE_PRE_OFF)
			_dpu_encoder_resource_control_helper(drm_enc, false);

		dpu_enc->rc_state = DPU_ENC_RC_STATE_OFF;

		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "stop");

		mutex_unlock(&dpu_enc->rc_lock);
		अवरोध;

	हाल DPU_ENC_RC_EVENT_ENTER_IDLE:
		mutex_lock(&dpu_enc->rc_lock);

		अगर (dpu_enc->rc_state != DPU_ENC_RC_STATE_ON) अणु
			DRM_ERROR("id: %u, sw_event:%d, rc:%d !ON state\n",
				  DRMID(drm_enc), sw_event, dpu_enc->rc_state);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस 0;
		पूर्ण

		/*
		 * अगर we are in ON but a frame was just kicked off,
		 * ignore the IDLE event, it's probably a stale समयr event
		 */
		अगर (dpu_enc->frame_busy_mask[0]) अणु
			DRM_ERROR("id:%u, sw_event:%d, rc:%d frame pending\n",
				  DRMID(drm_enc), sw_event, dpu_enc->rc_state);
			mutex_unlock(&dpu_enc->rc_lock);
			वापस 0;
		पूर्ण

		अगर (is_vid_mode)
			_dpu_encoder_irq_control(drm_enc, false);
		अन्यथा
			_dpu_encoder_resource_control_helper(drm_enc, false);

		dpu_enc->rc_state = DPU_ENC_RC_STATE_IDLE;

		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "idle");

		mutex_unlock(&dpu_enc->rc_lock);
		अवरोध;

	शेष:
		DRM_ERROR("id:%u, unexpected sw_event: %d\n", DRMID(drm_enc),
			  sw_event);
		trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
				 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
				 "error");
		अवरोध;
	पूर्ण

	trace_dpu_enc_rc(DRMID(drm_enc), sw_event,
			 dpu_enc->idle_pc_supported, dpu_enc->rc_state,
			 "end");
	वापस 0;
पूर्ण

अटल व्योम dpu_encoder_virt_mode_set(काष्ठा drm_encoder *drm_enc,
				      काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा list_head *connector_list;
	काष्ठा drm_connector *conn = शून्य, *conn_iter;
	काष्ठा drm_crtc *drm_crtc;
	काष्ठा dpu_crtc_state *cstate;
	काष्ठा dpu_global_state *global_state;
	काष्ठा dpu_hw_blk *hw_pp[MAX_CHANNELS_PER_ENC];
	काष्ठा dpu_hw_blk *hw_ctl[MAX_CHANNELS_PER_ENC];
	काष्ठा dpu_hw_blk *hw_lm[MAX_CHANNELS_PER_ENC];
	काष्ठा dpu_hw_blk *hw_dspp[MAX_CHANNELS_PER_ENC] = अणु शून्य पूर्ण;
	पूर्णांक num_lm, num_ctl, num_pp;
	पूर्णांक i, j;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	priv = drm_enc->dev->dev_निजी;
	dpu_kms = to_dpu_kms(priv->kms);
	connector_list = &dpu_kms->dev->mode_config.connector_list;

	global_state = dpu_kms_get_existing_global_state(dpu_kms);
	अगर (IS_ERR_OR_शून्य(global_state)) अणु
		DPU_ERROR("Failed to get global state");
		वापस;
	पूर्ण

	trace_dpu_enc_mode_set(DRMID(drm_enc));

	अगर (drm_enc->encoder_type == DRM_MODE_ENCODER_TMDS && priv->dp)
		msm_dp_display_mode_set(priv->dp, drm_enc, mode, adj_mode);

	list_क्रम_each_entry(conn_iter, connector_list, head)
		अगर (conn_iter->encoder == drm_enc)
			conn = conn_iter;

	अगर (!conn) अणु
		DPU_ERROR_ENC(dpu_enc, "failed to find attached connector\n");
		वापस;
	पूर्ण अन्यथा अगर (!conn->state) अणु
		DPU_ERROR_ENC(dpu_enc, "invalid connector state\n");
		वापस;
	पूर्ण

	drm_क्रम_each_crtc(drm_crtc, drm_enc->dev)
		अगर (drm_crtc->state->encoder_mask & drm_encoder_mask(drm_enc))
			अवरोध;

	/* Query resource that have been reserved in atomic check step. */
	num_pp = dpu_rm_get_asचिन्हित_resources(&dpu_kms->rm, global_state,
		drm_enc->base.id, DPU_HW_BLK_PINGPONG, hw_pp,
		ARRAY_SIZE(hw_pp));
	num_ctl = dpu_rm_get_asचिन्हित_resources(&dpu_kms->rm, global_state,
		drm_enc->base.id, DPU_HW_BLK_CTL, hw_ctl, ARRAY_SIZE(hw_ctl));
	num_lm = dpu_rm_get_asचिन्हित_resources(&dpu_kms->rm, global_state,
		drm_enc->base.id, DPU_HW_BLK_LM, hw_lm, ARRAY_SIZE(hw_lm));
	dpu_rm_get_asचिन्हित_resources(&dpu_kms->rm, global_state,
		drm_enc->base.id, DPU_HW_BLK_DSPP, hw_dspp,
		ARRAY_SIZE(hw_dspp));

	क्रम (i = 0; i < MAX_CHANNELS_PER_ENC; i++)
		dpu_enc->hw_pp[i] = i < num_pp ? to_dpu_hw_pingpong(hw_pp[i])
						: शून्य;

	cstate = to_dpu_crtc_state(drm_crtc->state);

	क्रम (i = 0; i < num_lm; i++) अणु
		पूर्णांक ctl_idx = (i < num_ctl) ? i : (num_ctl-1);

		cstate->mixers[i].hw_lm = to_dpu_hw_mixer(hw_lm[i]);
		cstate->mixers[i].lm_ctl = to_dpu_hw_ctl(hw_ctl[ctl_idx]);
		cstate->mixers[i].hw_dspp = to_dpu_hw_dspp(hw_dspp[i]);
	पूर्ण

	cstate->num_mixers = num_lm;

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		पूर्णांक num_blk;
		काष्ठा dpu_hw_blk *hw_blk[MAX_CHANNELS_PER_ENC];
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (!dpu_enc->hw_pp[i]) अणु
			DPU_ERROR_ENC(dpu_enc,
				"no pp block assigned at idx: %d\n", i);
			वापस;
		पूर्ण

		अगर (!hw_ctl[i]) अणु
			DPU_ERROR_ENC(dpu_enc,
				"no ctl block assigned at idx: %d\n", i);
			वापस;
		पूर्ण

		phys->hw_pp = dpu_enc->hw_pp[i];
		phys->hw_ctl = to_dpu_hw_ctl(hw_ctl[i]);

		num_blk = dpu_rm_get_asचिन्हित_resources(&dpu_kms->rm,
			global_state, drm_enc->base.id, DPU_HW_BLK_INTF,
			hw_blk, ARRAY_SIZE(hw_blk));
		क्रम (j = 0; j < num_blk; j++) अणु
			काष्ठा dpu_hw_पूर्णांकf *hw_पूर्णांकf;

			hw_पूर्णांकf = to_dpu_hw_पूर्णांकf(hw_blk[i]);
			अगर (hw_पूर्णांकf->idx == phys->पूर्णांकf_idx)
				phys->hw_पूर्णांकf = hw_पूर्णांकf;
		पूर्ण

		अगर (!phys->hw_पूर्णांकf) अणु
			DPU_ERROR_ENC(dpu_enc,
				      "no intf block assigned at idx: %d\n", i);
			वापस;
		पूर्ण

		phys->connector = conn->state->connector;
		अगर (phys->ops.mode_set)
			phys->ops.mode_set(phys, mode, adj_mode);
	पूर्ण
पूर्ण

अटल व्योम _dpu_encoder_virt_enable_helper(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक i;

	अगर (!drm_enc || !drm_enc->dev) अणु
		DPU_ERROR("invalid parameters\n");
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	अगर (!dpu_enc || !dpu_enc->cur_master) अणु
		DPU_ERROR("invalid dpu encoder/master\n");
		वापस;
	पूर्ण


	अगर (dpu_enc->disp_info.पूर्णांकf_type == DRM_MODE_CONNECTOR_DisplayPort &&
		dpu_enc->cur_master->hw_mdptop &&
		dpu_enc->cur_master->hw_mdptop->ops.पूर्णांकf_audio_select)
		dpu_enc->cur_master->hw_mdptop->ops.पूर्णांकf_audio_select(
			dpu_enc->cur_master->hw_mdptop);

	_dpu_encoder_update_vsync_source(dpu_enc, &dpu_enc->disp_info);

	अगर (dpu_enc->disp_info.पूर्णांकf_type == DRM_MODE_ENCODER_DSI &&
			!WARN_ON(dpu_enc->num_phys_encs == 0)) अणु
		अचिन्हित bpc = dpu_enc->phys_encs[0]->connector->display_info.bpc;
		क्रम (i = 0; i < MAX_CHANNELS_PER_ENC; i++) अणु
			अगर (!dpu_enc->hw_pp[i])
				जारी;
			_dpu_encoder_setup_dither(dpu_enc->hw_pp[i], bpc);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dpu_encoder_virt_runसमय_resume(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);

	mutex_lock(&dpu_enc->enc_lock);

	अगर (!dpu_enc->enabled)
		जाओ out;

	अगर (dpu_enc->cur_slave && dpu_enc->cur_slave->ops.restore)
		dpu_enc->cur_slave->ops.restore(dpu_enc->cur_slave);
	अगर (dpu_enc->cur_master && dpu_enc->cur_master->ops.restore)
		dpu_enc->cur_master->ops.restore(dpu_enc->cur_master);

	_dpu_encoder_virt_enable_helper(drm_enc);

out:
	mutex_unlock(&dpu_enc->enc_lock);
पूर्ण

अटल व्योम dpu_encoder_virt_enable(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक ret = 0;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा drm_display_mode *cur_mode = शून्य;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	mutex_lock(&dpu_enc->enc_lock);
	cur_mode = &dpu_enc->base.crtc->state->adjusted_mode;
	priv = drm_enc->dev->dev_निजी;

	trace_dpu_enc_enable(DRMID(drm_enc), cur_mode->hdisplay,
			     cur_mode->vdisplay);

	/* always enable slave encoder beक्रमe master */
	अगर (dpu_enc->cur_slave && dpu_enc->cur_slave->ops.enable)
		dpu_enc->cur_slave->ops.enable(dpu_enc->cur_slave);

	अगर (dpu_enc->cur_master && dpu_enc->cur_master->ops.enable)
		dpu_enc->cur_master->ops.enable(dpu_enc->cur_master);

	ret = dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_KICKOFF);
	अगर (ret) अणु
		DPU_ERROR_ENC(dpu_enc, "dpu resource control failed: %d\n",
				ret);
		जाओ out;
	पूर्ण

	_dpu_encoder_virt_enable_helper(drm_enc);

	अगर (drm_enc->encoder_type == DRM_MODE_ENCODER_TMDS && priv->dp) अणु
		ret = msm_dp_display_enable(priv->dp,
						drm_enc);
		अगर (ret) अणु
			DPU_ERROR_ENC(dpu_enc, "dp display enable failed: %d\n",
				ret);
			जाओ out;
		पूर्ण
	पूर्ण
	dpu_enc->enabled = true;

out:
	mutex_unlock(&dpu_enc->enc_lock);
पूर्ण

अटल व्योम dpu_encoder_virt_disable(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	काष्ठा msm_drm_निजी *priv;
	पूर्णांक i = 0;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण अन्यथा अगर (!drm_enc->dev) अणु
		DPU_ERROR("invalid dev\n");
		वापस;
	पूर्ण

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	mutex_lock(&dpu_enc->enc_lock);
	dpu_enc->enabled = false;

	priv = drm_enc->dev->dev_निजी;

	trace_dpu_enc_disable(DRMID(drm_enc));

	/* रुको क्रम idle */
	dpu_encoder_रुको_क्रम_event(drm_enc, MSM_ENC_TX_COMPLETE);

	अगर (drm_enc->encoder_type == DRM_MODE_ENCODER_TMDS && priv->dp) अणु
		अगर (msm_dp_display_pre_disable(priv->dp, drm_enc))
			DPU_ERROR_ENC(dpu_enc, "dp display push idle failed\n");
	पूर्ण

	dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_PRE_STOP);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.disable)
			phys->ops.disable(phys);
	पूर्ण


	/* after phys रुकोs क्रम frame-करोne, should be no more frames pending */
	अगर (atomic_xchg(&dpu_enc->frame_करोne_समयout_ms, 0)) अणु
		DPU_ERROR("enc%d timeout pending\n", drm_enc->base.id);
		del_समयr_sync(&dpu_enc->frame_करोne_समयr);
	पूर्ण

	dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_STOP);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		dpu_enc->phys_encs[i]->connector = शून्य;
	पूर्ण

	DPU_DEBUG_ENC(dpu_enc, "encoder disabled\n");

	अगर (drm_enc->encoder_type == DRM_MODE_ENCODER_TMDS && priv->dp) अणु
		अगर (msm_dp_display_disable(priv->dp, drm_enc))
			DPU_ERROR_ENC(dpu_enc, "dp display disable failed\n");
	पूर्ण

	mutex_unlock(&dpu_enc->enc_lock);
पूर्ण

अटल क्रमागत dpu_पूर्णांकf dpu_encoder_get_पूर्णांकf(काष्ठा dpu_mdss_cfg *catalog,
		क्रमागत dpu_पूर्णांकf_type type, u32 controller_id)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < catalog->पूर्णांकf_count; i++) अणु
		अगर (catalog->पूर्णांकf[i].type == type
		    && catalog->पूर्णांकf[i].controller_id == controller_id) अणु
			वापस catalog->पूर्णांकf[i].id;
		पूर्ण
	पूर्ण

	वापस INTF_MAX;
पूर्ण

अटल व्योम dpu_encoder_vblank_callback(काष्ठा drm_encoder *drm_enc,
		काष्ठा dpu_encoder_phys *phy_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	अचिन्हित दीर्घ lock_flags;

	अगर (!drm_enc || !phy_enc)
		वापस;

	DPU_ATRACE_BEGIN("encoder_vblank_callback");
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	अगर (dpu_enc->crtc)
		dpu_crtc_vblank_callback(dpu_enc->crtc);
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);

	atomic_inc(&phy_enc->vsync_cnt);
	DPU_ATRACE_END("encoder_vblank_callback");
पूर्ण

अटल व्योम dpu_encoder_underrun_callback(काष्ठा drm_encoder *drm_enc,
		काष्ठा dpu_encoder_phys *phy_enc)
अणु
	अगर (!phy_enc)
		वापस;

	DPU_ATRACE_BEGIN("encoder_underrun_callback");
	atomic_inc(&phy_enc->underrun_cnt);
	trace_dpu_enc_underrun_cb(DRMID(drm_enc),
				  atomic_पढ़ो(&phy_enc->underrun_cnt));
	DPU_ATRACE_END("encoder_underrun_callback");
पूर्ण

व्योम dpu_encoder_assign_crtc(काष्ठा drm_encoder *drm_enc, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	/* crtc should always be cleared beक्रमe re-assigning */
	WARN_ON(crtc && dpu_enc->crtc);
	dpu_enc->crtc = crtc;
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);
पूर्ण

व्योम dpu_encoder_toggle_vblank_क्रम_crtc(काष्ठा drm_encoder *drm_enc,
					काष्ठा drm_crtc *crtc, bool enable)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक i;

	trace_dpu_enc_vblank_cb(DRMID(drm_enc), enable);

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	अगर (dpu_enc->crtc != crtc) अणु
		spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->ops.control_vblank_irq)
			phys->ops.control_vblank_irq(phys, enable);
	पूर्ण
पूर्ण

व्योम dpu_encoder_रेजिस्टर_frame_event_callback(काष्ठा drm_encoder *drm_enc,
		व्योम (*frame_event_cb)(व्योम *, u32 event),
		व्योम *frame_event_cb_data)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	अचिन्हित दीर्घ lock_flags;
	bool enable;

	enable = frame_event_cb ? true : false;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	trace_dpu_enc_frame_event_cb(DRMID(drm_enc), enable);

	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);
	dpu_enc->crtc_frame_event_cb = frame_event_cb;
	dpu_enc->crtc_frame_event_cb_data = frame_event_cb_data;
	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);
पूर्ण

अटल व्योम dpu_encoder_frame_करोne_callback(
		काष्ठा drm_encoder *drm_enc,
		काष्ठा dpu_encoder_phys *पढ़ोy_phys, u32 event)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	अचिन्हित पूर्णांक i;

	अगर (event & (DPU_ENCODER_FRAME_EVENT_DONE
			| DPU_ENCODER_FRAME_EVENT_ERROR
			| DPU_ENCODER_FRAME_EVENT_PANEL_DEAD)) अणु

		अगर (!dpu_enc->frame_busy_mask[0]) अणु
			/**
			 * suppress frame_करोne without रुकोer,
			 * likely स्वतःrefresh
			 */
			trace_dpu_enc_frame_करोne_cb_not_busy(DRMID(drm_enc),
					event, पढ़ोy_phys->पूर्णांकf_idx);
			वापस;
		पूर्ण

		/* One of the physical encoders has become idle */
		क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
			अगर (dpu_enc->phys_encs[i] == पढ़ोy_phys) अणु
				trace_dpu_enc_frame_करोne_cb(DRMID(drm_enc), i,
						dpu_enc->frame_busy_mask[0]);
				clear_bit(i, dpu_enc->frame_busy_mask);
			पूर्ण
		पूर्ण

		अगर (!dpu_enc->frame_busy_mask[0]) अणु
			atomic_set(&dpu_enc->frame_करोne_समयout_ms, 0);
			del_समयr(&dpu_enc->frame_करोne_समयr);

			dpu_encoder_resource_control(drm_enc,
					DPU_ENC_RC_EVENT_FRAME_DONE);

			अगर (dpu_enc->crtc_frame_event_cb)
				dpu_enc->crtc_frame_event_cb(
					dpu_enc->crtc_frame_event_cb_data,
					event);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dpu_enc->crtc_frame_event_cb)
			dpu_enc->crtc_frame_event_cb(
				dpu_enc->crtc_frame_event_cb_data, event);
	पूर्ण
पूर्ण

अटल व्योम dpu_encoder_off_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = container_of(work,
			काष्ठा dpu_encoder_virt, delayed_off_work.work);

	अगर (!dpu_enc) अणु
		DPU_ERROR("invalid dpu encoder\n");
		वापस;
	पूर्ण

	dpu_encoder_resource_control(&dpu_enc->base,
						DPU_ENC_RC_EVENT_ENTER_IDLE);

	dpu_encoder_frame_करोne_callback(&dpu_enc->base, शून्य,
				DPU_ENCODER_FRAME_EVENT_IDLE);
पूर्ण

/**
 * _dpu_encoder_trigger_flush - trigger flush क्रम a physical encoder
 * @drm_enc: Poपूर्णांकer to drm encoder काष्ठाure
 * @phys: Poपूर्णांकer to physical encoder काष्ठाure
 * @extra_flush_bits: Additional bit mask to include in flush trigger
 */
अटल व्योम _dpu_encoder_trigger_flush(काष्ठा drm_encoder *drm_enc,
		काष्ठा dpu_encoder_phys *phys, uपूर्णांक32_t extra_flush_bits)
अणु
	काष्ठा dpu_hw_ctl *ctl;
	पूर्णांक pending_kickoff_cnt;
	u32 ret = अच_पूर्णांक_उच्च;

	अगर (!phys->hw_pp) अणु
		DPU_ERROR("invalid pingpong hw\n");
		वापस;
	पूर्ण

	ctl = phys->hw_ctl;
	अगर (!ctl->ops.trigger_flush) अणु
		DPU_ERROR("missing trigger cb\n");
		वापस;
	पूर्ण

	pending_kickoff_cnt = dpu_encoder_phys_inc_pending(phys);

	अगर (extra_flush_bits && ctl->ops.update_pending_flush)
		ctl->ops.update_pending_flush(ctl, extra_flush_bits);

	ctl->ops.trigger_flush(ctl);

	अगर (ctl->ops.get_pending_flush)
		ret = ctl->ops.get_pending_flush(ctl);

	trace_dpu_enc_trigger_flush(DRMID(drm_enc), phys->पूर्णांकf_idx,
				    pending_kickoff_cnt, ctl->idx,
				    extra_flush_bits, ret);
पूर्ण

/**
 * _dpu_encoder_trigger_start - trigger start क्रम a physical encoder
 * @phys: Poपूर्णांकer to physical encoder काष्ठाure
 */
अटल व्योम _dpu_encoder_trigger_start(काष्ठा dpu_encoder_phys *phys)
अणु
	अगर (!phys) अणु
		DPU_ERROR("invalid argument(s)\n");
		वापस;
	पूर्ण

	अगर (!phys->hw_pp) अणु
		DPU_ERROR("invalid pingpong hw\n");
		वापस;
	पूर्ण

	अगर (phys->ops.trigger_start && phys->enable_state != DPU_ENC_DISABLED)
		phys->ops.trigger_start(phys);
पूर्ण

व्योम dpu_encoder_helper_trigger_start(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_hw_ctl *ctl;

	ctl = phys_enc->hw_ctl;
	अगर (ctl->ops.trigger_start) अणु
		ctl->ops.trigger_start(ctl);
		trace_dpu_enc_trigger_start(DRMID(phys_enc->parent), ctl->idx);
	पूर्ण
पूर्ण

अटल पूर्णांक dpu_encoder_helper_रुको_event_समयout(
		पूर्णांक32_t drm_id,
		पूर्णांक32_t hw_id,
		काष्ठा dpu_encoder_रुको_info *info)
अणु
	पूर्णांक rc = 0;
	s64 expected_समय = kसमय_प्रकारo_ms(kसमय_get()) + info->समयout_ms;
	s64 jअगरfies = msecs_to_jअगरfies(info->समयout_ms);
	s64 समय;

	करो अणु
		rc = रुको_event_समयout(*(info->wq),
				atomic_पढ़ो(info->atomic_cnt) == 0, jअगरfies);
		समय = kसमय_प्रकारo_ms(kसमय_get());

		trace_dpu_enc_रुको_event_समयout(drm_id, hw_id, rc, समय,
						 expected_समय,
						 atomic_पढ़ो(info->atomic_cnt));
	/* If we समयd out, counter is valid and समय is less, रुको again */
	पूर्ण जबतक (atomic_पढ़ो(info->atomic_cnt) && (rc == 0) &&
			(समय < expected_समय));

	वापस rc;
पूर्ण

अटल व्योम dpu_encoder_helper_hw_reset(काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_hw_ctl *ctl;
	पूर्णांक rc;

	dpu_enc = to_dpu_encoder_virt(phys_enc->parent);
	ctl = phys_enc->hw_ctl;

	अगर (!ctl->ops.reset)
		वापस;

	DRM_DEBUG_KMS("id:%u ctl %d reset\n", DRMID(phys_enc->parent),
		      ctl->idx);

	rc = ctl->ops.reset(ctl);
	अगर (rc)
		DPU_ERROR_ENC(dpu_enc, "ctl %d reset failure\n",  ctl->idx);

	phys_enc->enable_state = DPU_ENC_ENABLED;
पूर्ण

/**
 * _dpu_encoder_kickoff_phys - handle physical encoder kickoff
 *	Iterate through the physical encoders and perक्रमm consolidated flush
 *	and/or control start triggering as needed. This is करोne in the भव
 *	encoder rather than the inभागidual physical ones in order to handle
 *	use हालs that require visibility पूर्णांकo multiple physical encoders at
 *	a समय.
 * @dpu_enc: Poपूर्णांकer to भव encoder काष्ठाure
 */
अटल व्योम _dpu_encoder_kickoff_phys(काष्ठा dpu_encoder_virt *dpu_enc)
अणु
	काष्ठा dpu_hw_ctl *ctl;
	uपूर्णांक32_t i, pending_flush;
	अचिन्हित दीर्घ lock_flags;

	pending_flush = 0x0;

	/* update pending counts and trigger kickoff ctl flush atomically */
	spin_lock_irqsave(&dpu_enc->enc_spinlock, lock_flags);

	/* करोn't perक्रमm flush/start operations क्रम slave encoders */
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		अगर (phys->enable_state == DPU_ENC_DISABLED)
			जारी;

		ctl = phys->hw_ctl;

		/*
		 * This is cleared in frame_करोne worker, which isn't invoked
		 * क्रम async commits. So करोn't set this for async, since it'll
		 * roll over to the next commit.
		 */
		अगर (phys->split_role != ENC_ROLE_SLAVE)
			set_bit(i, dpu_enc->frame_busy_mask);

		अगर (!phys->ops.needs_single_flush ||
				!phys->ops.needs_single_flush(phys))
			_dpu_encoder_trigger_flush(&dpu_enc->base, phys, 0x0);
		अन्यथा अगर (ctl->ops.get_pending_flush)
			pending_flush |= ctl->ops.get_pending_flush(ctl);
	पूर्ण

	/* क्रम split flush, combine pending flush masks and send to master */
	अगर (pending_flush && dpu_enc->cur_master) अणु
		_dpu_encoder_trigger_flush(
				&dpu_enc->base,
				dpu_enc->cur_master,
				pending_flush);
	पूर्ण

	_dpu_encoder_trigger_start(dpu_enc->cur_master);

	spin_unlock_irqrestore(&dpu_enc->enc_spinlock, lock_flags);
पूर्ण

व्योम dpu_encoder_trigger_kickoff_pending(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	अचिन्हित पूर्णांक i;
	काष्ठा dpu_hw_ctl *ctl;
	काष्ठा msm_display_info *disp_info;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(drm_enc);
	disp_info = &dpu_enc->disp_info;

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		phys = dpu_enc->phys_encs[i];

		ctl = phys->hw_ctl;
		अगर (ctl->ops.clear_pending_flush)
			ctl->ops.clear_pending_flush(ctl);

		/* update only क्रम command mode primary ctl */
		अगर ((phys == dpu_enc->cur_master) &&
		   (disp_info->capabilities & MSM_DISPLAY_CAP_CMD_MODE)
		    && ctl->ops.trigger_pending)
			ctl->ops.trigger_pending(ctl);
	पूर्ण
पूर्ण

अटल u32 _dpu_encoder_calculate_lineसमय(काष्ठा dpu_encoder_virt *dpu_enc,
		काष्ठा drm_display_mode *mode)
अणु
	u64 pclk_rate;
	u32 pclk_period;
	u32 line_समय;

	/*
	 * For lineसमय calculation, only operate on master encoder.
	 */
	अगर (!dpu_enc->cur_master)
		वापस 0;

	अगर (!dpu_enc->cur_master->ops.get_line_count) अणु
		DPU_ERROR("get_line_count function not defined\n");
		वापस 0;
	पूर्ण

	pclk_rate = mode->घड़ी; /* pixel घड़ी in kHz */
	अगर (pclk_rate == 0) अणु
		DPU_ERROR("pclk is 0, cannot calculate line time\n");
		वापस 0;
	पूर्ण

	pclk_period = DIV_ROUND_UP_ULL(1000000000ull, pclk_rate);
	अगर (pclk_period == 0) अणु
		DPU_ERROR("pclk period is 0\n");
		वापस 0;
	पूर्ण

	/*
	 * Line समय calculation based on Pixel घड़ी and HTOTAL.
	 * Final unit is in ns.
	 */
	line_समय = (pclk_period * mode->htotal) / 1000;
	अगर (line_समय == 0) अणु
		DPU_ERROR("line time calculation is 0\n");
		वापस 0;
	पूर्ण

	DPU_DEBUG_ENC(dpu_enc,
			"clk_rate=%lldkHz, clk_period=%d, linetime=%dns\n",
			pclk_rate, pclk_period, line_समय);

	वापस line_समय;
पूर्ण

पूर्णांक dpu_encoder_vsync_समय(काष्ठा drm_encoder *drm_enc, kसमय_प्रकार *wakeup_समय)
अणु
	काष्ठा drm_display_mode *mode;
	काष्ठा dpu_encoder_virt *dpu_enc;
	u32 cur_line;
	u32 line_समय;
	u32 vtotal, समय_प्रकारo_vsync;
	kसमय_प्रकार cur_समय;

	dpu_enc = to_dpu_encoder_virt(drm_enc);

	अगर (!drm_enc->crtc || !drm_enc->crtc->state) अणु
		DPU_ERROR("crtc/crtc state object is NULL\n");
		वापस -EINVAL;
	पूर्ण
	mode = &drm_enc->crtc->state->adjusted_mode;

	line_समय = _dpu_encoder_calculate_lineसमय(dpu_enc, mode);
	अगर (!line_समय)
		वापस -EINVAL;

	cur_line = dpu_enc->cur_master->ops.get_line_count(dpu_enc->cur_master);

	vtotal = mode->vtotal;
	अगर (cur_line >= vtotal)
		समय_प्रकारo_vsync = line_समय * vtotal;
	अन्यथा
		समय_प्रकारo_vsync = line_समय * (vtotal - cur_line);

	अगर (समय_प्रकारo_vsync == 0) अणु
		DPU_ERROR("time to vsync should not be zero, vtotal=%d\n",
				vtotal);
		वापस -EINVAL;
	पूर्ण

	cur_समय = kसमय_get();
	*wakeup_समय = kसमय_add_ns(cur_समय, समय_प्रकारo_vsync);

	DPU_DEBUG_ENC(dpu_enc,
			"cur_line=%u vtotal=%u time_to_vsync=%u, cur_time=%lld, wakeup_time=%lld\n",
			cur_line, vtotal, समय_प्रकारo_vsync,
			kसमय_प्रकारo_ms(cur_समय),
			kसमय_प्रकारo_ms(*wakeup_समय));
	वापस 0;
पूर्ण

अटल व्योम dpu_encoder_vsync_event_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = from_समयr(dpu_enc, t,
			vsync_event_समयr);
	काष्ठा drm_encoder *drm_enc = &dpu_enc->base;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा msm_drm_thपढ़ो *event_thपढ़ो;

	अगर (!drm_enc->dev || !drm_enc->crtc) अणु
		DPU_ERROR("invalid parameters\n");
		वापस;
	पूर्ण

	priv = drm_enc->dev->dev_निजी;

	अगर (drm_enc->crtc->index >= ARRAY_SIZE(priv->event_thपढ़ो)) अणु
		DPU_ERROR("invalid crtc index\n");
		वापस;
	पूर्ण
	event_thपढ़ो = &priv->event_thपढ़ो[drm_enc->crtc->index];
	अगर (!event_thपढ़ो) अणु
		DPU_ERROR("event_thread not found for crtc:%d\n",
				drm_enc->crtc->index);
		वापस;
	पूर्ण

	del_समयr(&dpu_enc->vsync_event_समयr);
पूर्ण

अटल व्योम dpu_encoder_vsync_event_work_handler(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = container_of(work,
			काष्ठा dpu_encoder_virt, vsync_event_work);
	kसमय_प्रकार wakeup_समय;

	अगर (!dpu_enc) अणु
		DPU_ERROR("invalid dpu encoder\n");
		वापस;
	पूर्ण

	अगर (dpu_encoder_vsync_समय(&dpu_enc->base, &wakeup_समय))
		वापस;

	trace_dpu_enc_vsync_event_work(DRMID(&dpu_enc->base), wakeup_समय);
	mod_समयr(&dpu_enc->vsync_event_समयr,
			nsecs_to_jअगरfies(kसमय_प्रकारo_ns(wakeup_समय)));
पूर्ण

व्योम dpu_encoder_prepare_क्रम_kickoff(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	bool needs_hw_reset = false;
	अचिन्हित पूर्णांक i;

	dpu_enc = to_dpu_encoder_virt(drm_enc);

	trace_dpu_enc_prepare_kickoff(DRMID(drm_enc));

	/* prepare क्रम next kickoff, may include रुकोing on previous kickoff */
	DPU_ATRACE_BEGIN("enc_prepare_for_kickoff");
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		phys = dpu_enc->phys_encs[i];
		अगर (phys->ops.prepare_क्रम_kickoff)
			phys->ops.prepare_क्रम_kickoff(phys);
		अगर (phys->enable_state == DPU_ENC_ERR_NEEDS_HW_RESET)
			needs_hw_reset = true;
	पूर्ण
	DPU_ATRACE_END("enc_prepare_for_kickoff");

	dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_KICKOFF);

	/* अगर any phys needs reset, reset all phys, in-order */
	अगर (needs_hw_reset) अणु
		trace_dpu_enc_prepare_kickoff_reset(DRMID(drm_enc));
		क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
			dpu_encoder_helper_hw_reset(dpu_enc->phys_encs[i]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dpu_encoder_kickoff(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	kसमय_प्रकार wakeup_समय;
	अचिन्हित दीर्घ समयout_ms;
	अचिन्हित पूर्णांक i;

	DPU_ATRACE_BEGIN("encoder_kickoff");
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	trace_dpu_enc_kickoff(DRMID(drm_enc));

	समयout_ms = DPU_ENCODER_FRAME_DONE_TIMEOUT_FRAMES * 1000 /
			drm_mode_vrefresh(&drm_enc->crtc->state->adjusted_mode);

	atomic_set(&dpu_enc->frame_करोne_समयout_ms, समयout_ms);
	mod_समयr(&dpu_enc->frame_करोne_समयr,
			jअगरfies + msecs_to_jअगरfies(समयout_ms));

	/* All phys encs are पढ़ोy to go, trigger the kickoff */
	_dpu_encoder_kickoff_phys(dpu_enc);

	/* allow phys encs to handle any post-kickoff business */
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		phys = dpu_enc->phys_encs[i];
		अगर (phys->ops.handle_post_kickoff)
			phys->ops.handle_post_kickoff(phys);
	पूर्ण

	अगर (dpu_enc->disp_info.पूर्णांकf_type == DRM_MODE_ENCODER_DSI &&
			!dpu_encoder_vsync_समय(drm_enc, &wakeup_समय)) अणु
		trace_dpu_enc_early_kickoff(DRMID(drm_enc),
					    kसमय_प्रकारo_ms(wakeup_समय));
		mod_समयr(&dpu_enc->vsync_event_समयr,
				nsecs_to_jअगरfies(kसमय_प्रकारo_ns(wakeup_समय)));
	पूर्ण

	DPU_ATRACE_END("encoder_kickoff");
पूर्ण

व्योम dpu_encoder_prepare_commit(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc;
	काष्ठा dpu_encoder_phys *phys;
	पूर्णांक i;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		phys = dpu_enc->phys_encs[i];
		अगर (phys->ops.prepare_commit)
			phys->ops.prepare_commit(phys);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक _dpu_encoder_status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = s->निजी;
	पूर्णांक i;

	mutex_lock(&dpu_enc->enc_lock);
	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		seq_म_लिखो(s, "intf:%d    vsync:%8d     underrun:%8d    ",
				phys->पूर्णांकf_idx - INTF_0,
				atomic_पढ़ो(&phys->vsync_cnt),
				atomic_पढ़ो(&phys->underrun_cnt));

		चयन (phys->पूर्णांकf_mode) अणु
		हाल INTF_MODE_VIDEO:
			seq_माला_दो(s, "mode: video\n");
			अवरोध;
		हाल INTF_MODE_CMD:
			seq_माला_दो(s, "mode: command\n");
			अवरोध;
		शेष:
			seq_माला_दो(s, "mode: ???\n");
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&dpu_enc->enc_lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(_dpu_encoder_status);

अटल पूर्णांक _dpu_encoder_init_debugfs(काष्ठा drm_encoder *drm_enc)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	पूर्णांक i;

	अक्षर name[DPU_NAME_SIZE];

	अगर (!drm_enc->dev) अणु
		DPU_ERROR("invalid encoder or kms\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(name, DPU_NAME_SIZE, "encoder%u", drm_enc->base.id);

	/* create overall sub-directory क्रम the encoder */
	dpu_enc->debugfs_root = debugfs_create_dir(name,
			drm_enc->dev->primary->debugfs_root);

	/* करोn't error check these */
	debugfs_create_file("status", 0600,
		dpu_enc->debugfs_root, dpu_enc, &_dpu_encoder_status_fops);

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++)
		अगर (dpu_enc->phys_encs[i]->ops.late_रेजिस्टर)
			dpu_enc->phys_encs[i]->ops.late_रेजिस्टर(
					dpu_enc->phys_encs[i],
					dpu_enc->debugfs_root);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक _dpu_encoder_init_debugfs(काष्ठा drm_encoder *drm_enc)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dpu_encoder_late_रेजिस्टर(काष्ठा drm_encoder *encoder)
अणु
	वापस _dpu_encoder_init_debugfs(encoder);
पूर्ण

अटल व्योम dpu_encoder_early_unरेजिस्टर(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(encoder);

	debugfs_हटाओ_recursive(dpu_enc->debugfs_root);
पूर्ण

अटल पूर्णांक dpu_encoder_virt_add_phys_encs(
		u32 display_caps,
		काष्ठा dpu_encoder_virt *dpu_enc,
		काष्ठा dpu_enc_phys_init_params *params)
अणु
	काष्ठा dpu_encoder_phys *enc = शून्य;

	DPU_DEBUG_ENC(dpu_enc, "\n");

	/*
	 * We may create up to NUM_PHYS_ENCODER_TYPES physical encoder types
	 * in this function, check up-front.
	 */
	अगर (dpu_enc->num_phys_encs + NUM_PHYS_ENCODER_TYPES >=
			ARRAY_SIZE(dpu_enc->phys_encs)) अणु
		DPU_ERROR_ENC(dpu_enc, "too many physical encoders %d\n",
			  dpu_enc->num_phys_encs);
		वापस -EINVAL;
	पूर्ण

	अगर (display_caps & MSM_DISPLAY_CAP_VID_MODE) अणु
		enc = dpu_encoder_phys_vid_init(params);

		अगर (IS_ERR_OR_शून्य(enc)) अणु
			DPU_ERROR_ENC(dpu_enc, "failed to init vid enc: %ld\n",
				PTR_ERR(enc));
			वापस enc == शून्य ? -EINVAL : PTR_ERR(enc);
		पूर्ण

		dpu_enc->phys_encs[dpu_enc->num_phys_encs] = enc;
		++dpu_enc->num_phys_encs;
	पूर्ण

	अगर (display_caps & MSM_DISPLAY_CAP_CMD_MODE) अणु
		enc = dpu_encoder_phys_cmd_init(params);

		अगर (IS_ERR_OR_शून्य(enc)) अणु
			DPU_ERROR_ENC(dpu_enc, "failed to init cmd enc: %ld\n",
				PTR_ERR(enc));
			वापस enc == शून्य ? -EINVAL : PTR_ERR(enc);
		पूर्ण

		dpu_enc->phys_encs[dpu_enc->num_phys_encs] = enc;
		++dpu_enc->num_phys_encs;
	पूर्ण

	अगर (params->split_role == ENC_ROLE_SLAVE)
		dpu_enc->cur_slave = enc;
	अन्यथा
		dpu_enc->cur_master = enc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dpu_encoder_virt_ops dpu_encoder_parent_ops = अणु
	.handle_vblank_virt = dpu_encoder_vblank_callback,
	.handle_underrun_virt = dpu_encoder_underrun_callback,
	.handle_frame_करोne = dpu_encoder_frame_करोne_callback,
पूर्ण;

अटल पूर्णांक dpu_encoder_setup_display(काष्ठा dpu_encoder_virt *dpu_enc,
				 काष्ठा dpu_kms *dpu_kms,
				 काष्ठा msm_display_info *disp_info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i = 0;
	क्रमागत dpu_पूर्णांकf_type पूर्णांकf_type = INTF_NONE;
	काष्ठा dpu_enc_phys_init_params phys_params;

	अगर (!dpu_enc) अणु
		DPU_ERROR("invalid arg(s), enc %d\n", dpu_enc != शून्य);
		वापस -EINVAL;
	पूर्ण

	dpu_enc->cur_master = शून्य;

	स_रखो(&phys_params, 0, माप(phys_params));
	phys_params.dpu_kms = dpu_kms;
	phys_params.parent = &dpu_enc->base;
	phys_params.parent_ops = &dpu_encoder_parent_ops;
	phys_params.enc_spinlock = &dpu_enc->enc_spinlock;

	DPU_DEBUG("\n");

	चयन (disp_info->पूर्णांकf_type) अणु
	हाल DRM_MODE_ENCODER_DSI:
		पूर्णांकf_type = INTF_DSI;
		अवरोध;
	हाल DRM_MODE_ENCODER_TMDS:
		पूर्णांकf_type = INTF_DP;
		अवरोध;
	पूर्ण

	WARN_ON(disp_info->num_of_h_tiles < 1);

	DPU_DEBUG("dsi_info->num_of_h_tiles %d\n", disp_info->num_of_h_tiles);

	अगर ((disp_info->capabilities & MSM_DISPLAY_CAP_CMD_MODE) ||
	    (disp_info->capabilities & MSM_DISPLAY_CAP_VID_MODE))
		dpu_enc->idle_pc_supported =
				dpu_kms->catalog->caps->has_idle_pc;

	mutex_lock(&dpu_enc->enc_lock);
	क्रम (i = 0; i < disp_info->num_of_h_tiles && !ret; i++) अणु
		/*
		 * Left-most tile is at index 0, content is controller id
		 * h_tile_instance_ids[2] = अणु0, 1पूर्ण; DSI0 = left, DSI1 = right
		 * h_tile_instance_ids[2] = अणु1, 0पूर्ण; DSI1 = left, DSI0 = right
		 */
		u32 controller_id = disp_info->h_tile_instance[i];

		अगर (disp_info->num_of_h_tiles > 1) अणु
			अगर (i == 0)
				phys_params.split_role = ENC_ROLE_MASTER;
			अन्यथा
				phys_params.split_role = ENC_ROLE_SLAVE;
		पूर्ण अन्यथा अणु
			phys_params.split_role = ENC_ROLE_SOLO;
		पूर्ण

		DPU_DEBUG("h_tile_instance %d = %d, split_role %d\n",
				i, controller_id, phys_params.split_role);

		phys_params.पूर्णांकf_idx = dpu_encoder_get_पूर्णांकf(dpu_kms->catalog,
													पूर्णांकf_type,
													controller_id);
		अगर (phys_params.पूर्णांकf_idx == INTF_MAX) अणु
			DPU_ERROR_ENC(dpu_enc, "could not get intf: type %d, id %d\n",
						  पूर्णांकf_type, controller_id);
			ret = -EINVAL;
		पूर्ण

		अगर (!ret) अणु
			ret = dpu_encoder_virt_add_phys_encs(disp_info->capabilities,
												 dpu_enc,
												 &phys_params);
			अगर (ret)
				DPU_ERROR_ENC(dpu_enc, "failed to add phys encs\n");
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];
		atomic_set(&phys->vsync_cnt, 0);
		atomic_set(&phys->underrun_cnt, 0);
	पूर्ण
	mutex_unlock(&dpu_enc->enc_lock);

	वापस ret;
पूर्ण

अटल व्योम dpu_encoder_frame_करोne_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = from_समयr(dpu_enc, t,
			frame_करोne_समयr);
	काष्ठा drm_encoder *drm_enc = &dpu_enc->base;
	u32 event;

	अगर (!drm_enc->dev) अणु
		DPU_ERROR("invalid parameters\n");
		वापस;
	पूर्ण

	अगर (!dpu_enc->frame_busy_mask[0] || !dpu_enc->crtc_frame_event_cb) अणु
		DRM_DEBUG_KMS("id:%u invalid timeout frame_busy_mask=%lu\n",
			      DRMID(drm_enc), dpu_enc->frame_busy_mask[0]);
		वापस;
	पूर्ण अन्यथा अगर (!atomic_xchg(&dpu_enc->frame_करोne_समयout_ms, 0)) अणु
		DRM_DEBUG_KMS("id:%u invalid timeout\n", DRMID(drm_enc));
		वापस;
	पूर्ण

	DPU_ERROR_ENC(dpu_enc, "frame done timeout\n");

	event = DPU_ENCODER_FRAME_EVENT_ERROR;
	trace_dpu_enc_frame_करोne_समयout(DRMID(drm_enc), event);
	dpu_enc->crtc_frame_event_cb(dpu_enc->crtc_frame_event_cb_data, event);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dpu_encoder_helper_funcs = अणु
	.mode_set = dpu_encoder_virt_mode_set,
	.disable = dpu_encoder_virt_disable,
	.enable = dpu_kms_encoder_enable,
	.atomic_check = dpu_encoder_virt_atomic_check,

	/* This is called by dpu_kms_encoder_enable */
	.commit = dpu_encoder_virt_enable,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs dpu_encoder_funcs = अणु
		.destroy = dpu_encoder_destroy,
		.late_रेजिस्टर = dpu_encoder_late_रेजिस्टर,
		.early_unरेजिस्टर = dpu_encoder_early_unरेजिस्टर,
पूर्ण;

पूर्णांक dpu_encoder_setup(काष्ठा drm_device *dev, काष्ठा drm_encoder *enc,
		काष्ठा msm_display_info *disp_info)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(priv->kms);
	काष्ठा drm_encoder *drm_enc = शून्य;
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक ret = 0;

	dpu_enc = to_dpu_encoder_virt(enc);

	ret = dpu_encoder_setup_display(dpu_enc, dpu_kms, disp_info);
	अगर (ret)
		जाओ fail;

	atomic_set(&dpu_enc->frame_करोne_समयout_ms, 0);
	समयr_setup(&dpu_enc->frame_करोne_समयr,
			dpu_encoder_frame_करोne_समयout, 0);

	अगर (disp_info->पूर्णांकf_type == DRM_MODE_ENCODER_DSI)
		समयr_setup(&dpu_enc->vsync_event_समयr,
				dpu_encoder_vsync_event_handler,
				0);


	INIT_DELAYED_WORK(&dpu_enc->delayed_off_work,
			dpu_encoder_off_work);
	dpu_enc->idle_समयout = IDLE_TIMEOUT;

	kthपढ़ो_init_work(&dpu_enc->vsync_event_work,
			dpu_encoder_vsync_event_work_handler);

	स_नकल(&dpu_enc->disp_info, disp_info, माप(*disp_info));

	DPU_DEBUG_ENC(dpu_enc, "created\n");

	वापस ret;

fail:
	DPU_ERROR("failed to create encoder\n");
	अगर (drm_enc)
		dpu_encoder_destroy(drm_enc);

	वापस ret;


पूर्ण

काष्ठा drm_encoder *dpu_encoder_init(काष्ठा drm_device *dev,
		पूर्णांक drm_enc_mode)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक rc = 0;

	dpu_enc = devm_kzalloc(dev->dev, माप(*dpu_enc), GFP_KERNEL);
	अगर (!dpu_enc)
		वापस ERR_PTR(-ENOMEM);

	rc = drm_encoder_init(dev, &dpu_enc->base, &dpu_encoder_funcs,
			drm_enc_mode, शून्य);
	अगर (rc) अणु
		devm_kमुक्त(dev->dev, dpu_enc);
		वापस ERR_PTR(rc);
	पूर्ण

	drm_encoder_helper_add(&dpu_enc->base, &dpu_encoder_helper_funcs);

	spin_lock_init(&dpu_enc->enc_spinlock);
	dpu_enc->enabled = false;
	mutex_init(&dpu_enc->enc_lock);
	mutex_init(&dpu_enc->rc_lock);

	वापस &dpu_enc->base;
पूर्ण

पूर्णांक dpu_encoder_रुको_क्रम_event(काष्ठा drm_encoder *drm_enc,
	क्रमागत msm_event_रुको event)
अणु
	पूर्णांक (*fn_रुको)(काष्ठा dpu_encoder_phys *phys_enc) = शून्य;
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;
	पूर्णांक i, ret = 0;

	अगर (!drm_enc) अणु
		DPU_ERROR("invalid encoder\n");
		वापस -EINVAL;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(drm_enc);
	DPU_DEBUG_ENC(dpu_enc, "\n");

	क्रम (i = 0; i < dpu_enc->num_phys_encs; i++) अणु
		काष्ठा dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		चयन (event) अणु
		हाल MSM_ENC_COMMIT_DONE:
			fn_रुको = phys->ops.रुको_क्रम_commit_करोne;
			अवरोध;
		हाल MSM_ENC_TX_COMPLETE:
			fn_रुको = phys->ops.रुको_क्रम_tx_complete;
			अवरोध;
		हाल MSM_ENC_VBLANK:
			fn_रुको = phys->ops.रुको_क्रम_vblank;
			अवरोध;
		शेष:
			DPU_ERROR_ENC(dpu_enc, "unknown wait event %d\n",
					event);
			वापस -EINVAL;
		पूर्ण

		अगर (fn_रुको) अणु
			DPU_ATRACE_BEGIN("wait_for_completion_event");
			ret = fn_रुको(phys);
			DPU_ATRACE_END("wait_for_completion_event");
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत dpu_पूर्णांकf_mode dpu_encoder_get_पूर्णांकf_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dpu_encoder_virt *dpu_enc = शून्य;

	अगर (!encoder) अणु
		DPU_ERROR("invalid encoder\n");
		वापस INTF_MODE_NONE;
	पूर्ण
	dpu_enc = to_dpu_encoder_virt(encoder);

	अगर (dpu_enc->cur_master)
		वापस dpu_enc->cur_master->पूर्णांकf_mode;

	अगर (dpu_enc->num_phys_encs)
		वापस dpu_enc->phys_encs[0]->पूर्णांकf_mode;

	वापस INTF_MODE_NONE;
पूर्ण
