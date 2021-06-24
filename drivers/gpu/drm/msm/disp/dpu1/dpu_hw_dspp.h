<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_DSPP_H
#घोषणा _DPU_HW_DSPP_H

#समावेश "dpu_hw_blk.h"

काष्ठा dpu_hw_dspp;

/**
 * काष्ठा dpu_hw_pcc_coeff - PCC coefficient काष्ठाure क्रम each color
 *                            component.
 * @r: red coefficient.
 * @g: green coefficient.
 * @b: blue coefficient.
 */

काष्ठा dpu_hw_pcc_coeff अणु
	__u32 r;
	__u32 g;
	__u32 b;
पूर्ण;

/**
 * काष्ठा dpu_hw_pcc - pcc feature काष्ठाure
 * @r: red coefficients.
 * @g: green coefficients.
 * @b: blue coefficients.
 */
काष्ठा dpu_hw_pcc_cfg अणु
	काष्ठा dpu_hw_pcc_coeff r;
	काष्ठा dpu_hw_pcc_coeff g;
	काष्ठा dpu_hw_pcc_coeff b;
पूर्ण;

/**
 * काष्ठा dpu_hw_dspp_ops - पूर्णांकerface to the dspp hardware driver functions
 * Caller must call the init function to get the dspp context क्रम each dspp
 * Assumption is these functions will be called after घड़ीs are enabled
 */
काष्ठा dpu_hw_dspp_ops अणु
	/**
	 * setup_pcc - setup dspp pcc
	 * @ctx: Poपूर्णांकer to dspp context
	 * @cfg: Poपूर्णांकer to configuration
	 */
	व्योम (*setup_pcc)(काष्ठा dpu_hw_dspp *ctx, काष्ठा dpu_hw_pcc_cfg *cfg);

पूर्ण;

/**
 * काष्ठा dpu_hw_dspp - dspp description
 * @base: Hardware block base काष्ठाure
 * @hw: Block hardware details
 * @idx: DSPP index
 * @cap: Poपूर्णांकer to layer_cfg
 * @ops: Poपूर्णांकer to operations possible क्रम this DSPP
 */
काष्ठा dpu_hw_dspp अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* dspp */
	पूर्णांक idx;
	स्थिर काष्ठा dpu_dspp_cfg *cap;

	/* Ops */
	काष्ठा dpu_hw_dspp_ops ops;
पूर्ण;

/**
 * dpu_hw_dspp - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_dspp *to_dpu_hw_dspp(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_dspp, base);
पूर्ण

/**
 * dpu_hw_dspp_init - initializes the dspp hw driver object.
 * should be called once beक्रमe accessing every dspp.
 * @idx:  DSPP index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDP
 * @Return: poपूर्णांकer to काष्ठाure or ERR_PTR
 */
काष्ठा dpu_hw_dspp *dpu_hw_dspp_init(क्रमागत dpu_dspp idx,
	व्योम __iomem *addr, स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_dspp_destroy(): Destroys DSPP driver context
 * @dspp: Poपूर्णांकer to DSPP driver context
 */
व्योम dpu_hw_dspp_destroy(काष्ठा dpu_hw_dspp *dspp);

#पूर्ण_अगर /*_DPU_HW_DSPP_H */

