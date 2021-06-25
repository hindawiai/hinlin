<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DPU_ENCODER_PHYS_H__
#घोषणा __DPU_ENCODER_PHYS_H__

#समावेश <linux/jअगरfies.h>

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_intf.h"
#समावेश "dpu_hw_pingpong.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_hw_top.h"
#समावेश "dpu_encoder.h"
#समावेश "dpu_crtc.h"

#घोषणा DPU_ENCODER_NAME_MAX	16

/* रुको क्रम at most 2 vsync क्रम lowest refresh rate (24hz) */
#घोषणा KICKOFF_TIMEOUT_MS		84
#घोषणा KICKOFF_TIMEOUT_JIFFIES		msecs_to_jअगरfies(KICKOFF_TIMEOUT_MS)

/**
 * क्रमागत dpu_enc_split_role - Role this physical encoder will play in a
 *	split-panel configuration, where one panel is master, and others slaves.
 *	Masters have extra responsibilities, like managing the VBLANK IRQ.
 * @ENC_ROLE_SOLO:	This is the one and only panel. This encoder is master.
 * @ENC_ROLE_MASTER:	This encoder is the master of a split panel config.
 * @ENC_ROLE_SLAVE:	This encoder is not the master of a split panel config.
 */
क्रमागत dpu_enc_split_role अणु
	ENC_ROLE_SOLO,
	ENC_ROLE_MASTER,
	ENC_ROLE_SLAVE,
पूर्ण;

/**
 * क्रमागत dpu_enc_enable_state - current enabled state of the physical encoder
 * @DPU_ENC_DISABLING:	Encoder transitioning to disable state
 *			Events bounding transition are encoder type specअगरic
 * @DPU_ENC_DISABLED:	Encoder is disabled
 * @DPU_ENC_ENABLING:	Encoder transitioning to enabled
 *			Events bounding transition are encoder type specअगरic
 * @DPU_ENC_ENABLED:	Encoder is enabled
 * @DPU_ENC_ERR_NEEDS_HW_RESET:	Encoder is enabled, but requires a hw_reset
 *				to recover from a previous error
 */
क्रमागत dpu_enc_enable_state अणु
	DPU_ENC_DISABLING,
	DPU_ENC_DISABLED,
	DPU_ENC_ENABLING,
	DPU_ENC_ENABLED,
	DPU_ENC_ERR_NEEDS_HW_RESET
पूर्ण;

काष्ठा dpu_encoder_phys;

/**
 * काष्ठा dpu_encoder_virt_ops - Interface the containing भव encoder
 *	provides क्रम the physical encoders to use to callback.
 * @handle_vblank_virt:	Notअगरy भव encoder of vblank IRQ reception
 *			Note: This is called from IRQ handler context.
 * @handle_underrun_virt: Notअगरy भव encoder of underrun IRQ reception
 *			Note: This is called from IRQ handler context.
 * @handle_frame_करोne:	Notअगरy भव encoder that this phys encoder
 *			completes last request frame.
 */
काष्ठा dpu_encoder_virt_ops अणु
	व्योम (*handle_vblank_virt)(काष्ठा drm_encoder *,
			काष्ठा dpu_encoder_phys *phys);
	व्योम (*handle_underrun_virt)(काष्ठा drm_encoder *,
			काष्ठा dpu_encoder_phys *phys);
	व्योम (*handle_frame_करोne)(काष्ठा drm_encoder *,
			काष्ठा dpu_encoder_phys *phys, u32 event);
पूर्ण;

/**
 * काष्ठा dpu_encoder_phys_ops - Interface the physical encoders provide to
 *	the containing भव encoder.
 * @late_रेजिस्टर:		DRM Call. Add Userspace पूर्णांकerfaces, debugfs.
 * @prepare_commit:		MSM Atomic Call, start of atomic commit sequence
 * @is_master:			Whether this phys_enc is the current master
 *				encoder. Can be चयनed at enable समय. Based
 *				on split_role and current mode (CMD/VID).
 * @mode_fixup:			DRM Call. Fixup a DRM mode.
 * @mode_set:			DRM Call. Set a DRM mode.
 *				This likely caches the mode, क्रम use at enable.
 * @enable:			DRM Call. Enable a DRM mode.
 * @disable:			DRM Call. Disable mode.
 * @atomic_check:		DRM Call. Atomic check new DRM state.
 * @destroy:			DRM Call. Destroy and release resources.
 * @get_hw_resources:		Populate the काष्ठाure with the hardware
 *				resources that this phys_enc is using.
 *				Expect no overlap between phys_encs.
 * @control_vblank_irq		Register/Deरेजिस्टर क्रम VBLANK IRQ
 * @रुको_क्रम_commit_करोne:	Wait क्रम hardware to have flushed the
 *				current pending frames to hardware
 * @रुको_क्रम_tx_complete:	Wait क्रम hardware to transfer the pixels
 *				to the panel
 * @रुको_क्रम_vblank:		Wait क्रम VBLANK, क्रम sub-driver पूर्णांकernal use
 * @prepare_क्रम_kickoff:	Do any work necessary prior to a kickoff
 *				For CMD encoder, may रुको क्रम previous tx करोne
 * @handle_post_kickoff:	Do any work necessary post-kickoff work
 * @trigger_start:		Process start event on physical encoder
 * @needs_single_flush:		Whether encoder slaves need to be flushed
 * @irq_control:		Handler to enable/disable all the encoder IRQs
 * @prepare_idle_pc:		phys encoder can update the vsync_enable status
 *                              on idle घातer collapse prepare
 * @restore:			Restore all the encoder configs.
 * @get_line_count:		Obtain current vertical line count
 */

काष्ठा dpu_encoder_phys_ops अणु
	पूर्णांक (*late_रेजिस्टर)(काष्ठा dpu_encoder_phys *encoder,
			काष्ठा dentry *debugfs_root);
	व्योम (*prepare_commit)(काष्ठा dpu_encoder_phys *encoder);
	bool (*is_master)(काष्ठा dpu_encoder_phys *encoder);
	bool (*mode_fixup)(काष्ठा dpu_encoder_phys *encoder,
			स्थिर काष्ठा drm_display_mode *mode,
			काष्ठा drm_display_mode *adjusted_mode);
	व्योम (*mode_set)(काष्ठा dpu_encoder_phys *encoder,
			काष्ठा drm_display_mode *mode,
			काष्ठा drm_display_mode *adjusted_mode);
	व्योम (*enable)(काष्ठा dpu_encoder_phys *encoder);
	व्योम (*disable)(काष्ठा dpu_encoder_phys *encoder);
	पूर्णांक (*atomic_check)(काष्ठा dpu_encoder_phys *encoder,
			    काष्ठा drm_crtc_state *crtc_state,
			    काष्ठा drm_connector_state *conn_state);
	व्योम (*destroy)(काष्ठा dpu_encoder_phys *encoder);
	व्योम (*get_hw_resources)(काष्ठा dpu_encoder_phys *encoder,
				 काष्ठा dpu_encoder_hw_resources *hw_res);
	पूर्णांक (*control_vblank_irq)(काष्ठा dpu_encoder_phys *enc, bool enable);
	पूर्णांक (*रुको_क्रम_commit_करोne)(काष्ठा dpu_encoder_phys *phys_enc);
	पूर्णांक (*रुको_क्रम_tx_complete)(काष्ठा dpu_encoder_phys *phys_enc);
	पूर्णांक (*रुको_क्रम_vblank)(काष्ठा dpu_encoder_phys *phys_enc);
	व्योम (*prepare_क्रम_kickoff)(काष्ठा dpu_encoder_phys *phys_enc);
	व्योम (*handle_post_kickoff)(काष्ठा dpu_encoder_phys *phys_enc);
	व्योम (*trigger_start)(काष्ठा dpu_encoder_phys *phys_enc);
	bool (*needs_single_flush)(काष्ठा dpu_encoder_phys *phys_enc);
	व्योम (*irq_control)(काष्ठा dpu_encoder_phys *phys, bool enable);
	व्योम (*prepare_idle_pc)(काष्ठा dpu_encoder_phys *phys_enc);
	व्योम (*restore)(काष्ठा dpu_encoder_phys *phys);
	पूर्णांक (*get_line_count)(काष्ठा dpu_encoder_phys *phys);
	पूर्णांक (*get_frame_count)(काष्ठा dpu_encoder_phys *phys);
पूर्ण;

/**
 * क्रमागत dpu_पूर्णांकr_idx - dpu encoder पूर्णांकerrupt index
 * @INTR_IDX_VSYNC:    Vsync पूर्णांकerrupt क्रम video mode panel
 * @INTR_IDX_PINGPONG: Pingpong करोne unterrupt क्रम cmd mode panel
 * @INTR_IDX_UNDERRUN: Underrun unterrupt क्रम video and cmd mode panel
 * @INTR_IDX_RDPTR:    Readpoपूर्णांकer करोne unterrupt क्रम cmd mode panel
 */
क्रमागत dpu_पूर्णांकr_idx अणु
	INTR_IDX_VSYNC,
	INTR_IDX_PINGPONG,
	INTR_IDX_UNDERRUN,
	INTR_IDX_CTL_START,
	INTR_IDX_RDPTR,
	INTR_IDX_MAX,
पूर्ण;

/**
 * dpu_encoder_irq - tracking काष्ठाure क्रम पूर्णांकerrupts
 * @name:		string name of पूर्णांकerrupt
 * @पूर्णांकr_type:		Encoder पूर्णांकerrupt type
 * @पूर्णांकr_idx:		Encoder पूर्णांकerrupt क्रमागतeration
 * @hw_idx:		HW Block ID
 * @irq_idx:		IRQ पूर्णांकerface lookup index from DPU IRQ framework
 *			will be -EINVAL अगर IRQ is not रेजिस्टरed
 * @irq_cb:		पूर्णांकerrupt callback
 */
काष्ठा dpu_encoder_irq अणु
	स्थिर अक्षर *name;
	क्रमागत dpu_पूर्णांकr_type पूर्णांकr_type;
	क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx;
	पूर्णांक hw_idx;
	पूर्णांक irq_idx;
	काष्ठा dpu_irq_callback cb;
पूर्ण;

/**
 * काष्ठा dpu_encoder_phys - physical encoder that drives a single INTF block
 *	tied to a specअगरic panel / sub-panel. Abstract type, sub-classed by
 *	phys_vid or phys_cmd क्रम video mode or command mode encs respectively.
 * @parent:		Poपूर्णांकer to the containing भव encoder
 * @connector:		If a mode is set, cached poपूर्णांकer to the active connector
 * @ops:		Operations exposed to the भव encoder
 * @parent_ops:		Callbacks exposed by the parent to the phys_enc
 * @hw_mdptop:		Hardware पूर्णांकerface to the top रेजिस्टरs
 * @hw_ctl:		Hardware पूर्णांकerface to the ctl रेजिस्टरs
 * @hw_pp:		Hardware पूर्णांकerface to the ping pong रेजिस्टरs
 * @hw_पूर्णांकf:		Hardware पूर्णांकerface to the पूर्णांकf रेजिस्टरs
 * @dpu_kms:		Poपूर्णांकer to the dpu_kms top level
 * @cached_mode:	DRM mode cached at mode_set समय, acted on in enable
 * @enabled:		Whether the encoder has enabled and running a mode
 * @split_role:		Role to play in a split-panel configuration
 * @पूर्णांकf_mode:		Interface mode
 * @पूर्णांकf_idx:		Interface index on dpu hardware
 * @enc_spinlock:	Virtual-Encoder-Wide Spin Lock क्रम IRQ purposes
 * @enable_state:	Enable state tracking
 * @vblank_refcount:	Reference count of vblank request
 * @vsync_cnt:		Vsync count क्रम the physical encoder
 * @underrun_cnt:	Underrun count क्रम the physical encoder
 * @pending_kickoff_cnt:	Atomic counter tracking the number of kickoffs
 *				vs. the number of करोne/vblank irqs. Should hover
 *				between 0-2 Incremented when a new kickoff is
 *				scheduled. Decremented in irq handler
 * @pending_ctlstart_cnt:	Atomic counter tracking the number of ctl start
 *                              pending.
 * @pending_kickoff_wq:		Wait queue क्रम blocking until kickoff completes
 * @irq:			IRQ tracking काष्ठाures
 */
काष्ठा dpu_encoder_phys अणु
	काष्ठा drm_encoder *parent;
	काष्ठा drm_connector *connector;
	काष्ठा dpu_encoder_phys_ops ops;
	स्थिर काष्ठा dpu_encoder_virt_ops *parent_ops;
	काष्ठा dpu_hw_mdp *hw_mdptop;
	काष्ठा dpu_hw_ctl *hw_ctl;
	काष्ठा dpu_hw_pingpong *hw_pp;
	काष्ठा dpu_hw_पूर्णांकf *hw_पूर्णांकf;
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा drm_display_mode cached_mode;
	क्रमागत dpu_enc_split_role split_role;
	क्रमागत dpu_पूर्णांकf_mode पूर्णांकf_mode;
	क्रमागत dpu_पूर्णांकf पूर्णांकf_idx;
	spinlock_t *enc_spinlock;
	क्रमागत dpu_enc_enable_state enable_state;
	atomic_t vblank_refcount;
	atomic_t vsync_cnt;
	atomic_t underrun_cnt;
	atomic_t pending_ctlstart_cnt;
	atomic_t pending_kickoff_cnt;
	रुको_queue_head_t pending_kickoff_wq;
	काष्ठा dpu_encoder_irq irq[INTR_IDX_MAX];
पूर्ण;

अटल अंतरभूत पूर्णांक dpu_encoder_phys_inc_pending(काष्ठा dpu_encoder_phys *phys)
अणु
	atomic_inc_वापस(&phys->pending_ctlstart_cnt);
	वापस atomic_inc_वापस(&phys->pending_kickoff_cnt);
पूर्ण

/**
 * काष्ठा dpu_encoder_phys_cmd - sub-class of dpu_encoder_phys to handle command
 *	mode specअगरic operations
 * @base:	Baseclass physical encoder काष्ठाure
 * @पूर्णांकf_idx:	Intf Block index used by this phys encoder
 * @stream_sel:	Stream selection क्रम multi-stream पूर्णांकerfaces
 * @serialize_रुको4pp:	serialize रुको4pp feature रुकोs क्रम pp_करोne पूर्णांकerrupt
 *			after ctl_start instead of beक्रमe next frame kickoff
 * @pp_समयout_report_cnt: number of pingpong करोne irq समयout errors
 * @pending_vblank_cnt: Atomic counter tracking pending रुको क्रम VBLANK
 * @pending_vblank_wq: Wait queue क्रम blocking until VBLANK received
 */
काष्ठा dpu_encoder_phys_cmd अणु
	काष्ठा dpu_encoder_phys base;
	पूर्णांक stream_sel;
	bool serialize_रुको4pp;
	पूर्णांक pp_समयout_report_cnt;
	atomic_t pending_vblank_cnt;
	रुको_queue_head_t pending_vblank_wq;
पूर्ण;

/**
 * काष्ठा dpu_enc_phys_init_params - initialization parameters क्रम phys encs
 * @dpu_kms:		Poपूर्णांकer to the dpu_kms top level
 * @parent:		Poपूर्णांकer to the containing भव encoder
 * @parent_ops:		Callbacks exposed by the parent to the phys_enc
 * @split_role:		Role to play in a split-panel configuration
 * @पूर्णांकf_idx:		Interface index this phys_enc will control
 * @enc_spinlock:	Virtual-Encoder-Wide Spin Lock क्रम IRQ purposes
 */
काष्ठा dpu_enc_phys_init_params अणु
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा drm_encoder *parent;
	स्थिर काष्ठा dpu_encoder_virt_ops *parent_ops;
	क्रमागत dpu_enc_split_role split_role;
	क्रमागत dpu_पूर्णांकf पूर्णांकf_idx;
	spinlock_t *enc_spinlock;
पूर्ण;

/**
 * dpu_encoder_रुको_info - container क्रम passing arguments to irq रुको functions
 * @wq: रुको queue काष्ठाure
 * @atomic_cnt: रुको until atomic_cnt equals zero
 * @समयout_ms: समयout value in milliseconds
 */
काष्ठा dpu_encoder_रुको_info अणु
	रुको_queue_head_t *wq;
	atomic_t *atomic_cnt;
	s64 समयout_ms;
पूर्ण;

/**
 * dpu_encoder_phys_vid_init - Conकाष्ठा a new video mode physical encoder
 * @p:	Poपूर्णांकer to init params काष्ठाure
 * Return: Error code or newly allocated encoder
 */
काष्ठा dpu_encoder_phys *dpu_encoder_phys_vid_init(
		काष्ठा dpu_enc_phys_init_params *p);

/**
 * dpu_encoder_phys_cmd_init - Conकाष्ठा a new command mode physical encoder
 * @p:	Poपूर्णांकer to init params काष्ठाure
 * Return: Error code or newly allocated encoder
 */
काष्ठा dpu_encoder_phys *dpu_encoder_phys_cmd_init(
		काष्ठा dpu_enc_phys_init_params *p);

/**
 * dpu_encoder_helper_trigger_start - control start helper function
 *	This helper function may be optionally specअगरied by physical
 *	encoders अगर they require ctl_start triggering.
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 */
व्योम dpu_encoder_helper_trigger_start(काष्ठा dpu_encoder_phys *phys_enc);

अटल अंतरभूत क्रमागत dpu_3d_blend_mode dpu_encoder_helper_get_3d_blend_mode(
		काष्ठा dpu_encoder_phys *phys_enc)
अणु
	काष्ठा dpu_crtc_state *dpu_cstate;

	अगर (!phys_enc || phys_enc->enable_state == DPU_ENC_DISABLING)
		वापस BLEND_3D_NONE;

	dpu_cstate = to_dpu_crtc_state(phys_enc->parent->crtc->state);

	अगर (phys_enc->split_role == ENC_ROLE_SOLO &&
	    dpu_cstate->num_mixers == CRTC_DUAL_MIXERS)
		वापस BLEND_3D_H_ROW_INT;

	वापस BLEND_3D_NONE;
पूर्ण

/**
 * dpu_encoder_helper_split_config - split display configuration helper function
 *	This helper function may be used by physical encoders to configure
 *	the split display related रेजिस्टरs.
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 * @पूर्णांकerface: क्रमागत dpu_पूर्णांकf setting
 */
व्योम dpu_encoder_helper_split_config(
		काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकf पूर्णांकerface);

/**
 * dpu_encoder_helper_report_irq_समयout - utility to report error that irq has
 *	समयd out, including reporting frame error event to crtc and debug dump
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 * @पूर्णांकr_idx: Failing पूर्णांकerrupt index
 */
व्योम dpu_encoder_helper_report_irq_समयout(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx);

/**
 * dpu_encoder_helper_रुको_क्रम_irq - utility to रुको on an irq.
 *	note: will call dpu_encoder_helper_रुको_क्रम_irq on समयout
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 * @पूर्णांकr_idx: encoder पूर्णांकerrupt index
 * @रुको_info: रुको info काष्ठा
 * @Return: 0 or -ERROR
 */
पूर्णांक dpu_encoder_helper_रुको_क्रम_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx,
		काष्ठा dpu_encoder_रुको_info *रुको_info);

/**
 * dpu_encoder_helper_रेजिस्टर_irq - रेजिस्टर and enable an irq
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 * @पूर्णांकr_idx: encoder पूर्णांकerrupt index
 * @Return: 0 or -ERROR
 */
पूर्णांक dpu_encoder_helper_रेजिस्टर_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx);

/**
 * dpu_encoder_helper_unरेजिस्टर_irq - unरेजिस्टर and disable an irq
 * @phys_enc: Poपूर्णांकer to physical encoder काष्ठाure
 * @पूर्णांकr_idx: encoder पूर्णांकerrupt index
 * @Return: 0 or -ERROR
 */
पूर्णांक dpu_encoder_helper_unरेजिस्टर_irq(काष्ठा dpu_encoder_phys *phys_enc,
		क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx);

#पूर्ण_अगर /* __dpu_encoder_phys_H__ */
