<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित _DPU_CRTC_H_
#घोषणा _DPU_CRTC_H_

#समावेश <linux/kthपढ़ो.h>
#समावेश <drm/drm_crtc.h>
#समावेश "dpu_kms.h"
#समावेश "dpu_core_perf.h"
#समावेश "dpu_hw_blk.h"

#घोषणा DPU_CRTC_NAME_SIZE	12

/* define the maximum number of in-flight frame events */
#घोषणा DPU_CRTC_FRAME_EVENT_SIZE	4

/**
 * क्रमागत dpu_crtc_client_type: crtc client type
 * @RT_CLIENT:	RealTime client like video/cmd mode display
 *              voting through apps rsc
 * @NRT_CLIENT:	Non-RealTime client like WB display
 *              voting through apps rsc
 */
क्रमागत dpu_crtc_client_type अणु
	RT_CLIENT,
	NRT_CLIENT,
पूर्ण;

/**
 * क्रमागत dpu_crtc_smmu_state:	smmu state
 * @ATTACHED:	 all the context banks are attached.
 * @DETACHED:	 all the context banks are detached.
 * @ATTACH_ALL_REQ:	 transient state of attaching context banks.
 * @DETACH_ALL_REQ:	 transient state of detaching context banks.
 */
क्रमागत dpu_crtc_smmu_state अणु
	ATTACHED = 0,
	DETACHED,
	ATTACH_ALL_REQ,
	DETACH_ALL_REQ,
पूर्ण;

/**
 * क्रमागत dpu_crtc_smmu_state_transition_type: state transition type
 * @NONE: no pending state transitions
 * @PRE_COMMIT: state transitions should be करोne beक्रमe processing the commit
 * @POST_COMMIT: state transitions to be करोne after processing the commit.
 */
क्रमागत dpu_crtc_smmu_state_transition_type अणु
	NONE,
	PRE_COMMIT,
	POST_COMMIT
पूर्ण;

/**
 * काष्ठा dpu_crtc_smmu_state_data: stores the smmu state and transition type
 * @state: current state of smmu context banks
 * @transition_type: transition request type
 * @transition_error: whether there is error जबतक transitioning the state
 */
काष्ठा dpu_crtc_smmu_state_data अणु
	uपूर्णांक32_t state;
	uपूर्णांक32_t transition_type;
	uपूर्णांक32_t transition_error;
पूर्ण;

/**
 * काष्ठा dpu_crtc_mixer: stores the map क्रम each भव pipeline in the CRTC
 * @hw_lm:	LM HW Driver context
 * @lm_ctl:	CTL Path HW driver context
 * @lm_dspp:	DSPP HW driver context
 * @mixer_op_mode:	mixer blending operation mode
 * @flush_mask:	mixer flush mask क्रम ctl, mixer and pipe
 */
काष्ठा dpu_crtc_mixer अणु
	काष्ठा dpu_hw_mixer *hw_lm;
	काष्ठा dpu_hw_ctl *lm_ctl;
	काष्ठा dpu_hw_dspp *hw_dspp;
	u32 mixer_op_mode;
	u32 flush_mask;
पूर्ण;

/**
 * काष्ठा dpu_crtc_frame_event: stores crtc frame event क्रम crtc processing
 * @work:	base work काष्ठाure
 * @crtc:	Poपूर्णांकer to crtc handling this event
 * @list:	event list
 * @ts:		बारtamp at queue entry
 * @event:	event identअगरier
 */
काष्ठा dpu_crtc_frame_event अणु
	काष्ठा kthपढ़ो_work work;
	काष्ठा drm_crtc *crtc;
	काष्ठा list_head list;
	kसमय_प्रकार ts;
	u32 event;
पूर्ण;

/*
 * Maximum number of मुक्त event काष्ठाures to cache
 */
#घोषणा DPU_CRTC_MAX_EVENT_COUNT	16

/**
 * काष्ठा dpu_crtc - भवized CRTC data काष्ठाure
 * @base          : Base drm crtc काष्ठाure
 * @name          : ASCII description of this crtc
 * @event         : Poपूर्णांकer to last received drm vblank event. If there is a
 *                  pending vblank event, this will be non-null.
 * @vsync_count   : Running count of received vsync events
 * @drm_requested_vblank : Whether vblanks have been enabled in the encoder
 * @property_info : Opaque काष्ठाure क्रम generic property support
 * @property_शेषs : Array of शेष values क्रम generic property support
 * @stage_cfg     : H/w mixer stage configuration
 * @debugfs_root  : Parent of debugfs node
 * @vblank_cb_count : count of vblank callback since last reset
 * @play_count    : frame count between crtc enable and disable
 * @vblank_cb_समय  : kसमय at vblank count reset
 * @enabled       : whether the DPU CRTC is currently enabled. updated in the
 *                  commit-thपढ़ो, not state-swap समय which is earlier, so
 *                  safe to make decisions on during VBLANK on/off work
 * @feature_list  : list of color processing features supported on a crtc
 * @active_list   : list of color processing features are active
 * @dirty_list    : list of color processing features are dirty
 * @ad_dirty: list containing ad properties that are dirty
 * @ad_active: list containing ad properties that are active
 * @frame_pending : Whether or not an update is pending
 * @frame_events  : अटल allocation of in-flight frame events
 * @frame_event_list : available frame event list
 * @spin_lock     : spin lock क्रम frame event, transaction status, etc...
 * @frame_करोne_comp    : क्रम frame_event_करोne synchronization
 * @event_thपढ़ो  : Poपूर्णांकer to event handler thपढ़ो
 * @event_worker  : Event worker queue
 * @event_lock    : Spinlock around event handling code
 * @phandle: Poपूर्णांकer to घातer handler
 * @cur_perf      : current perक्रमmance committed to घड़ी/bandwidth driver
 */
काष्ठा dpu_crtc अणु
	काष्ठा drm_crtc base;
	अक्षर name[DPU_CRTC_NAME_SIZE];

	काष्ठा drm_pending_vblank_event *event;
	u32 vsync_count;

	काष्ठा dpu_hw_stage_cfg stage_cfg;
	काष्ठा dentry *debugfs_root;

	u32 vblank_cb_count;
	u64 play_count;
	kसमय_प्रकार vblank_cb_समय;
	bool enabled;

	काष्ठा list_head feature_list;
	काष्ठा list_head active_list;
	काष्ठा list_head dirty_list;
	काष्ठा list_head ad_dirty;
	काष्ठा list_head ad_active;

	atomic_t frame_pending;
	काष्ठा dpu_crtc_frame_event frame_events[DPU_CRTC_FRAME_EVENT_SIZE];
	काष्ठा list_head frame_event_list;
	spinlock_t spin_lock;
	काष्ठा completion frame_करोne_comp;

	/* क्रम handling पूर्णांकernal event thपढ़ो */
	spinlock_t event_lock;

	काष्ठा dpu_core_perf_params cur_perf;

	काष्ठा dpu_crtc_smmu_state_data smmu_state;
पूर्ण;

#घोषणा to_dpu_crtc(x) container_of(x, काष्ठा dpu_crtc, base)

/**
 * काष्ठा dpu_crtc_state - dpu container क्रम atomic crtc state
 * @base: Base drm crtc state काष्ठाure
 * @bw_control    : true अगर bw/clk controlled by core bw/clk properties
 * @bw_split_vote : true अगर bw controlled by llcc/dram bw properties
 * @lm_bounds     : LM boundaries based on current mode full resolution, no ROI.
 *                  Origin top left of CRTC.
 * @property_state: Local storage क्रम msm_prop properties
 * @property_values: Current crtc property values
 * @input_fence_समयout_ns : Cached input fence समयout, in ns
 * @new_perf: new perक्रमmance state being requested
 * @num_mixers    : Number of mixers in use
 * @mixers        : List of active mixers
 * @num_ctls      : Number of ctl paths in use
 * @hw_ctls       : List of active ctl paths
 */
काष्ठा dpu_crtc_state अणु
	काष्ठा drm_crtc_state base;

	bool bw_control;
	bool bw_split_vote;
	काष्ठा drm_rect lm_bounds[CRTC_DUAL_MIXERS];

	uपूर्णांक64_t input_fence_समयout_ns;

	काष्ठा dpu_core_perf_params new_perf;

	/* HW Resources reserved क्रम the crtc */
	u32 num_mixers;
	काष्ठा dpu_crtc_mixer mixers[CRTC_DUAL_MIXERS];

	u32 num_ctls;
	काष्ठा dpu_hw_ctl *hw_ctls[CRTC_DUAL_MIXERS];
पूर्ण;

#घोषणा to_dpu_crtc_state(x) \
	container_of(x, काष्ठा dpu_crtc_state, base)

/**
 * dpu_crtc_frame_pending - retun the number of pending frames
 * @crtc: Poपूर्णांकer to drm crtc object
 */
अटल अंतरभूत पूर्णांक dpu_crtc_frame_pending(काष्ठा drm_crtc *crtc)
अणु
	वापस crtc ? atomic_पढ़ो(&to_dpu_crtc(crtc)->frame_pending) : -EINVAL;
पूर्ण

/**
 * dpu_crtc_vblank - enable or disable vblanks क्रम this crtc
 * @crtc: Poपूर्णांकer to drm crtc object
 * @en: true to enable vblanks, false to disable
 */
पूर्णांक dpu_crtc_vblank(काष्ठा drm_crtc *crtc, bool en);

/**
 * dpu_crtc_vblank_callback - called on vblank irq, issues completion events
 * @crtc: Poपूर्णांकer to drm crtc object
 */
व्योम dpu_crtc_vblank_callback(काष्ठा drm_crtc *crtc);

/**
 * dpu_crtc_commit_kickoff - trigger kickoff of the commit क्रम this crtc
 * @crtc: Poपूर्णांकer to drm crtc object
 */
व्योम dpu_crtc_commit_kickoff(काष्ठा drm_crtc *crtc);

/**
 * dpu_crtc_complete_commit - callback संकेतling completion of current commit
 * @crtc: Poपूर्णांकer to drm crtc object
 */
व्योम dpu_crtc_complete_commit(काष्ठा drm_crtc *crtc);

/**
 * dpu_crtc_init - create a new crtc object
 * @dev: dpu device
 * @plane: base plane
 * @cursor: cursor plane
 * @Return: new crtc object or error
 */
काष्ठा drm_crtc *dpu_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
			       काष्ठा drm_plane *cursor);

/**
 * dpu_crtc_रेजिस्टर_custom_event - api क्रम enabling/disabling crtc event
 * @kms: Poपूर्णांकer to dpu_kms
 * @crtc_drm: Poपूर्णांकer to crtc object
 * @event: Event that client is पूर्णांकerested
 * @en: Flag to enable/disable the event
 */
पूर्णांक dpu_crtc_रेजिस्टर_custom_event(काष्ठा dpu_kms *kms,
		काष्ठा drm_crtc *crtc_drm, u32 event, bool en);

/**
 * dpu_crtc_get_पूर्णांकf_mode - get पूर्णांकerface mode of the given crtc
 * @crtc: Poपूर्णांकert to crtc
 */
क्रमागत dpu_पूर्णांकf_mode dpu_crtc_get_पूर्णांकf_mode(काष्ठा drm_crtc *crtc);

/**
 * dpu_crtc_get_client_type - check the crtc type- rt, nrt etc.
 * @crtc: Poपूर्णांकer to crtc
 */
अटल अंतरभूत क्रमागत dpu_crtc_client_type dpu_crtc_get_client_type(
						काष्ठा drm_crtc *crtc)
अणु
	वापस crtc && crtc->state ? RT_CLIENT : NRT_CLIENT;
पूर्ण

#पूर्ण_अगर /* _DPU_CRTC_H_ */
