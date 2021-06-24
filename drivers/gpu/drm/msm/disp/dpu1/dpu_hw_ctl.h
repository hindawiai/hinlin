<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_CTL_H
#घोषणा _DPU_HW_CTL_H

#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_sspp.h"
#समावेश "dpu_hw_blk.h"

/**
 * dpu_ctl_mode_sel: Interface mode selection
 * DPU_CTL_MODE_SEL_VID:    Video mode पूर्णांकerface
 * DPU_CTL_MODE_SEL_CMD:    Command mode पूर्णांकerface
 */
क्रमागत dpu_ctl_mode_sel अणु
	DPU_CTL_MODE_SEL_VID = 0,
	DPU_CTL_MODE_SEL_CMD
पूर्ण;

काष्ठा dpu_hw_ctl;
/**
 * काष्ठा dpu_hw_stage_cfg - blending stage cfg
 * @stage : SSPP_ID at each stage
 * @multirect_index: index of the rectangle of SSPP.
 */
काष्ठा dpu_hw_stage_cfg अणु
	क्रमागत dpu_sspp stage[DPU_STAGE_MAX][PIPES_PER_STAGE];
	क्रमागत dpu_sspp_multirect_index multirect_index
					[DPU_STAGE_MAX][PIPES_PER_STAGE];
पूर्ण;

/**
 * काष्ठा dpu_hw_पूर्णांकf_cfg :Describes how the DPU ग_लिखोs data to output पूर्णांकerface
 * @पूर्णांकf :                 Interface id
 * @mode_3d:               3d mux configuration
 * @merge_3d:              3d merge block used
 * @पूर्णांकf_mode_sel:         Interface mode, cmd / vid
 * @stream_sel:            Stream selection क्रम multi-stream पूर्णांकerfaces
 */
काष्ठा dpu_hw_पूर्णांकf_cfg अणु
	क्रमागत dpu_पूर्णांकf पूर्णांकf;
	क्रमागत dpu_3d_blend_mode mode_3d;
	क्रमागत dpu_merge_3d merge_3d;
	क्रमागत dpu_ctl_mode_sel पूर्णांकf_mode_sel;
	पूर्णांक stream_sel;
पूर्ण;

/**
 * काष्ठा dpu_hw_ctl_ops - Interface to the wb Hw driver functions
 * Assumption is these functions will be called after घड़ीs are enabled
 */
काष्ठा dpu_hw_ctl_ops अणु
	/**
	 * kickoff hw operation क्रम Sw controlled पूर्णांकerfaces
	 * DSI cmd mode and WB पूर्णांकerface are SW controlled
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	व्योम (*trigger_start)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * kickoff prepare is in progress hw operation क्रम sw
	 * controlled पूर्णांकerfaces: DSI cmd mode and WB पूर्णांकerface
	 * are SW controlled
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	व्योम (*trigger_pending)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * Clear the value of the cached pending_flush_mask
	 * No effect on hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	व्योम (*clear_pending_flush)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * Query the value of the cached pending_flush_mask
	 * No effect on hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	u32 (*get_pending_flush)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * OR in the given flushbits to the cached pending_flush_mask
	 * No effect on hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 * @flushbits : module flushmask
	 */
	व्योम (*update_pending_flush)(काष्ठा dpu_hw_ctl *ctx,
		u32 flushbits);

	/**
	 * OR in the given flushbits to the cached pending_(पूर्णांकf_)flush_mask
	 * No effect on hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 * @blk       : पूर्णांकerface block index
	 */
	व्योम (*update_pending_flush_पूर्णांकf)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_पूर्णांकf blk);

	/**
	 * OR in the given flushbits to the cached pending_(merge_3d_)flush_mask
	 * No effect on hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 * @blk       : पूर्णांकerface block index
	 */
	व्योम (*update_pending_flush_merge_3d)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_merge_3d blk);

	/**
	 * Write the value of the pending_flush_mask to hardware
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	व्योम (*trigger_flush)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * Read the value of the flush रेजिस्टर
	 * @ctx       : ctl path ctx poपूर्णांकer
	 * @Return: value of the ctl flush रेजिस्टर.
	 */
	u32 (*get_flush_रेजिस्टर)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * Setup ctl_path पूर्णांकerface config
	 * @ctx
	 * @cfg    : पूर्णांकerface config काष्ठाure poपूर्णांकer
	 */
	व्योम (*setup_पूर्णांकf_cfg)(काष्ठा dpu_hw_ctl *ctx,
		काष्ठा dpu_hw_पूर्णांकf_cfg *cfg);

	पूर्णांक (*reset)(काष्ठा dpu_hw_ctl *c);

	/*
	 * रुको_reset_status - checks ctl reset status
	 * @ctx       : ctl path ctx poपूर्णांकer
	 *
	 * This function checks the ctl reset status bit.
	 * If the reset bit is set, it keeps polling the status till the hw
	 * reset is complete.
	 * Returns: 0 on success or -error अगर reset incomplete within पूर्णांकerval
	 */
	पूर्णांक (*रुको_reset_status)(काष्ठा dpu_hw_ctl *ctx);

	uपूर्णांक32_t (*get_biपंचांगask_sspp)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_sspp blk);

	uपूर्णांक32_t (*get_biपंचांगask_mixer)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_lm blk);

	uपूर्णांक32_t (*get_biपंचांगask_dspp)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_dspp blk);

	/**
	 * Set all blend stages to disabled
	 * @ctx       : ctl path ctx poपूर्णांकer
	 */
	व्योम (*clear_all_blendstages)(काष्ठा dpu_hw_ctl *ctx);

	/**
	 * Configure layer mixer to pipe configuration
	 * @ctx       : ctl path ctx poपूर्णांकer
	 * @lm        : layer mixer क्रमागतeration
	 * @cfg       : blend stage configuration
	 */
	व्योम (*setup_blendstage)(काष्ठा dpu_hw_ctl *ctx,
		क्रमागत dpu_lm lm, काष्ठा dpu_hw_stage_cfg *cfg);

	व्योम (*set_active_pipes)(काष्ठा dpu_hw_ctl *ctx,
		अचिन्हित दीर्घ *fetch_active);
पूर्ण;

/**
 * काष्ठा dpu_hw_ctl : CTL PATH driver object
 * @base: hardware block base काष्ठाure
 * @hw: block रेजिस्टर map object
 * @idx: control path index
 * @caps: control path capabilities
 * @mixer_count: number of mixers
 * @mixer_hw_caps: mixer hardware capabilities
 * @pending_flush_mask: storage क्रम pending ctl_flush managed via ops
 * @pending_पूर्णांकf_flush_mask: pending INTF flush
 * @ops: operation list
 */
काष्ठा dpu_hw_ctl अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* ctl path */
	पूर्णांक idx;
	स्थिर काष्ठा dpu_ctl_cfg *caps;
	पूर्णांक mixer_count;
	स्थिर काष्ठा dpu_lm_cfg *mixer_hw_caps;
	u32 pending_flush_mask;
	u32 pending_पूर्णांकf_flush_mask;
	u32 pending_merge_3d_flush_mask;

	/* ops */
	काष्ठा dpu_hw_ctl_ops ops;
पूर्ण;

/**
 * dpu_hw_ctl - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_ctl *to_dpu_hw_ctl(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_ctl, base);
पूर्ण

/**
 * dpu_hw_ctl_init(): Initializes the ctl_path hw driver object.
 * should be called beक्रमe accessing every ctl path रेजिस्टरs.
 * @idx:  ctl_path index क्रम which driver object is required
 * @addr: mapped रेजिस्टर io address of MDP
 * @m :   poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_ctl *dpu_hw_ctl_init(क्रमागत dpu_ctl idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_ctl_destroy(): Destroys ctl driver context
 * should be called to मुक्त the context
 */
व्योम dpu_hw_ctl_destroy(काष्ठा dpu_hw_ctl *ctx);

#पूर्ण_अगर /*_DPU_HW_CTL_H */
