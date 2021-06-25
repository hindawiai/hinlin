<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DPU_RM_H__
#घोषणा __DPU_RM_H__

#समावेश <linux/list.h>

#समावेश "msm_kms.h"
#समावेश "dpu_hw_top.h"

काष्ठा dpu_global_state;

/**
 * काष्ठा dpu_rm - DPU dynamic hardware resource manager
 * @pingpong_blks: array of pingpong hardware resources
 * @mixer_blks: array of layer mixer hardware resources
 * @ctl_blks: array of ctl hardware resources
 * @पूर्णांकf_blks: array of पूर्णांकf hardware resources
 * @dspp_blks: array of dspp hardware resources
 * @lm_max_width: cached layer mixer maximum width
 * @rm_lock: resource manager mutex
 */
काष्ठा dpu_rm अणु
	काष्ठा dpu_hw_blk *pingpong_blks[PINGPONG_MAX - PINGPONG_0];
	काष्ठा dpu_hw_blk *mixer_blks[LM_MAX - LM_0];
	काष्ठा dpu_hw_blk *ctl_blks[CTL_MAX - CTL_0];
	काष्ठा dpu_hw_blk *पूर्णांकf_blks[INTF_MAX - INTF_0];
	काष्ठा dpu_hw_blk *dspp_blks[DSPP_MAX - DSPP_0];
	काष्ठा dpu_hw_blk *merge_3d_blks[MERGE_3D_MAX - MERGE_3D_0];

	uपूर्णांक32_t lm_max_width;
पूर्ण;

/**
 * dpu_rm_init - Read hardware catalog and create reservation tracking objects
 *	क्रम all HW blocks.
 * @rm: DPU Resource Manager handle
 * @cat: Poपूर्णांकer to hardware catalog
 * @mmio: mapped रेजिस्टर io address of MDP
 * @Return: 0 on Success otherwise -ERROR
 */
पूर्णांक dpu_rm_init(काष्ठा dpu_rm *rm,
		काष्ठा dpu_mdss_cfg *cat,
		व्योम __iomem *mmio);

/**
 * dpu_rm_destroy - Free all memory allocated by dpu_rm_init
 * @rm: DPU Resource Manager handle
 * @Return: 0 on Success otherwise -ERROR
 */
पूर्णांक dpu_rm_destroy(काष्ठा dpu_rm *rm);

/**
 * dpu_rm_reserve - Given a CRTC->Encoder->Connector display chain, analyze
 *	the use connections and user requirements, specअगरied through related
 *	topology control properties, and reserve hardware blocks to that
 *	display chain.
 *	HW blocks can then be accessed through dpu_rm_get_* functions.
 *	HW Reservations should be released via dpu_rm_release_hw.
 * @rm: DPU Resource Manager handle
 * @drm_enc: DRM Encoder handle
 * @crtc_state: Proposed Atomic DRM CRTC State handle
 * @topology: Poपूर्णांकer to topology info क्रम the display
 * @Return: 0 on Success otherwise -ERROR
 */
पूर्णांक dpu_rm_reserve(काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		काष्ठा drm_encoder *drm_enc,
		काष्ठा drm_crtc_state *crtc_state,
		काष्ठा msm_display_topology topology);

/**
 * dpu_rm_reserve - Given the encoder क्रम the display chain, release any
 *	HW blocks previously reserved क्रम that use हाल.
 * @rm: DPU Resource Manager handle
 * @enc: DRM Encoder handle
 * @Return: 0 on Success otherwise -ERROR
 */
व्योम dpu_rm_release(काष्ठा dpu_global_state *global_state,
		काष्ठा drm_encoder *enc);

/**
 * Get hw resources of the given type that are asचिन्हित to this encoder.
 */
पूर्णांक dpu_rm_get_asचिन्हित_resources(काष्ठा dpu_rm *rm,
	काष्ठा dpu_global_state *global_state, uपूर्णांक32_t enc_id,
	क्रमागत dpu_hw_blk_type type, काष्ठा dpu_hw_blk **blks, पूर्णांक blks_size);
#पूर्ण_अगर /* __DPU_RM_H__ */

