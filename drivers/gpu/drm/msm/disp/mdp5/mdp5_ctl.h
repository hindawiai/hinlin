<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __MDP5_CTL_H__
#घोषणा __MDP5_CTL_H__

#समावेश "msm_drv.h"

/*
 * CTL Manager prototypes:
 * mdp5_ctlm_init() वापसs a ctlm (CTL Manager) handler,
 * which is then used to call the other mdp5_ctlm_*(ctlm, ...) functions.
 */
काष्ठा mdp5_ctl_manager;
काष्ठा mdp5_ctl_manager *mdp5_ctlm_init(काष्ठा drm_device *dev,
		व्योम __iomem *mmio_base, काष्ठा mdp5_cfg_handler *cfg_hnd);
व्योम mdp5_ctlm_hw_reset(काष्ठा mdp5_ctl_manager *ctlm);
व्योम mdp5_ctlm_destroy(काष्ठा mdp5_ctl_manager *ctlm);

/*
 * CTL prototypes:
 * mdp5_ctl_request(ctlm, ...) वापसs a ctl (CTL resource) handler,
 * which is then used to call the other mdp5_ctl_*(ctl, ...) functions.
 */
काष्ठा mdp5_ctl *mdp5_ctlm_request(काष्ठा mdp5_ctl_manager *ctlm, पूर्णांक पूर्णांकf_num);

पूर्णांक mdp5_ctl_get_ctl_id(काष्ठा mdp5_ctl *ctl);

काष्ठा mdp5_पूर्णांकerface;
काष्ठा mdp5_pipeline;
पूर्णांक mdp5_ctl_set_pipeline(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *p);
पूर्णांक mdp5_ctl_set_encoder_state(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *p,
			       bool enabled);

पूर्णांक mdp5_ctl_set_cursor(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
			पूर्णांक cursor_id, bool enable);
पूर्णांक mdp5_ctl_pair(काष्ठा mdp5_ctl *ctlx, काष्ठा mdp5_ctl *ctly, bool enable);

#घोषणा MAX_PIPE_STAGE		2

/*
 * mdp5_ctl_blend() - Blend multiple layers on a Layer Mixer (LM)
 *
 * @stage: array to contain the pipe num क्रम each stage
 * @stage_cnt: valid stage number in stage array
 * @ctl_blend_op_flags: blender operation mode flags
 *
 * Note:
 * CTL रेजिस्टरs need to be flushed after calling this function
 * (call mdp5_ctl_commit() with mdp_ctl_flush_mask_ctl() mask)
 */
#घोषणा MDP5_CTL_BLEND_OP_FLAG_BORDER_OUT	BIT(0)
पूर्णांक mdp5_ctl_blend(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
		   क्रमागत mdp5_pipe stage[][MAX_PIPE_STAGE],
		   क्रमागत mdp5_pipe r_stage[][MAX_PIPE_STAGE],
		   u32 stage_cnt, u32 ctl_blend_op_flags);

/**
 * mdp_ctl_flush_mask...() - Register FLUSH masks
 *
 * These masks are used to specअगरy which block(s) need to be flushed
 * through @flush_mask parameter in mdp5_ctl_commit(.., flush_mask).
 */
u32 mdp_ctl_flush_mask_lm(पूर्णांक lm);
u32 mdp_ctl_flush_mask_pipe(क्रमागत mdp5_pipe pipe);
u32 mdp_ctl_flush_mask_cursor(पूर्णांक cursor_id);
u32 mdp_ctl_flush_mask_encoder(काष्ठा mdp5_पूर्णांकerface *पूर्णांकf);

/* @flush_mask: see CTL flush masks definitions below */
u32 mdp5_ctl_commit(काष्ठा mdp5_ctl *ctl, काष्ठा mdp5_pipeline *pipeline,
		    u32 flush_mask, bool start);
u32 mdp5_ctl_get_commit_status(काष्ठा mdp5_ctl *ctl);



#पूर्ण_अगर /* __MDP5_CTL_H__ */
