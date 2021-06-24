<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_LM_H
#घोषणा _DPU_HW_LM_H

#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"

काष्ठा dpu_hw_mixer;

काष्ठा dpu_hw_mixer_cfg अणु
	u32 out_width;
	u32 out_height;
	bool right_mixer;
	पूर्णांक flags;
पूर्ण;

काष्ठा dpu_hw_color3_cfg अणु
	u8 keep_fg[DPU_STAGE_MAX];
पूर्ण;

/**
 *
 * काष्ठा dpu_hw_lm_ops : Interface to the mixer Hw driver functions
 *  Assumption is these functions will be called after घड़ीs are enabled
 */
काष्ठा dpu_hw_lm_ops अणु
	/*
	 * Sets up mixer output width and height
	 * and border color अगर enabled
	 */
	व्योम (*setup_mixer_out)(काष्ठा dpu_hw_mixer *ctx,
		काष्ठा dpu_hw_mixer_cfg *cfg);

	/*
	 * Alpha blending configuration
	 * क्रम the specअगरied stage
	 */
	व्योम (*setup_blend_config)(काष्ठा dpu_hw_mixer *ctx, uपूर्णांक32_t stage,
		uपूर्णांक32_t fg_alpha, uपूर्णांक32_t bg_alpha, uपूर्णांक32_t blend_op);

	/*
	 * Alpha color component selection from either fg or bg
	 */
	व्योम (*setup_alpha_out)(काष्ठा dpu_hw_mixer *ctx, uपूर्णांक32_t mixer_op);

	/**
	 * setup_border_color : enable/disable border color
	 */
	व्योम (*setup_border_color)(काष्ठा dpu_hw_mixer *ctx,
		काष्ठा dpu_mdss_color *color,
		u8 border_en);
पूर्ण;

काष्ठा dpu_hw_mixer अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* lm */
	क्रमागत dpu_lm  idx;
	स्थिर काष्ठा dpu_lm_cfg   *cap;
	स्थिर काष्ठा dpu_mdp_cfg  *mdp;
	स्थिर काष्ठा dpu_ctl_cfg  *ctl;

	/* ops */
	काष्ठा dpu_hw_lm_ops ops;

	/* store mixer info specअगरic to display */
	काष्ठा dpu_hw_mixer_cfg cfg;
पूर्ण;

/**
 * to_dpu_hw_mixer - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_mixer *to_dpu_hw_mixer(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_mixer, base);
पूर्ण

/**
 * dpu_hw_lm_init(): Initializes the mixer hw driver object.
 * should be called once beक्रमe accessing every mixer.
 * @idx:  mixer index क्रम which driver object is required
 * @addr: mapped रेजिस्टर io address of MDP
 * @m :   poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_mixer *dpu_hw_lm_init(क्रमागत dpu_lm idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_lm_destroy(): Destroys layer mixer driver context
 * @lm:   Poपूर्णांकer to LM driver context
 */
व्योम dpu_hw_lm_destroy(काष्ठा dpu_hw_mixer *lm);

#पूर्ण_अगर /*_DPU_HW_LM_H */
