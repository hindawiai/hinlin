<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_MERGE3D_H
#घोषणा _DPU_HW_MERGE3D_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"

काष्ठा dpu_hw_merge_3d;

/**
 *
 * काष्ठा dpu_hw_merge_3d_ops : Interface to the merge_3d Hw driver functions
 *  Assumption is these functions will be called after घड़ीs are enabled
 *  @setup_3d_mode : enable 3D merge
 */
काष्ठा dpu_hw_merge_3d_ops अणु
	व्योम (*setup_3d_mode)(काष्ठा dpu_hw_merge_3d *merge_3d,
			क्रमागत dpu_3d_blend_mode mode_3d);

पूर्ण;

काष्ठा dpu_hw_merge_3d अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* merge_3d */
	क्रमागत dpu_merge_3d idx;
	स्थिर काष्ठा dpu_merge_3d_cfg *caps;

	/* ops */
	काष्ठा dpu_hw_merge_3d_ops ops;
पूर्ण;

/**
 * to_dpu_hw_merge_3d - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_merge_3d *to_dpu_hw_merge_3d(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_merge_3d, base);
पूर्ण

/**
 * dpu_hw_merge_3d_init - initializes the merge_3d driver क्रम the passed
 *	merge_3d idx.
 * @idx:  Pingpong index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDP
 * @m:    Poपूर्णांकer to mdss catalog data
 * Returns: Error code or allocated dpu_hw_merge_3d context
 */
काष्ठा dpu_hw_merge_3d *dpu_hw_merge_3d_init(क्रमागत dpu_merge_3d idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_merge_3d_destroy - destroys merge_3d driver context
 *	should be called to मुक्त the context
 * @pp:   Poपूर्णांकer to PP driver context वापसed by dpu_hw_merge_3d_init
 */
व्योम dpu_hw_merge_3d_destroy(काष्ठा dpu_hw_merge_3d *pp);

#पूर्ण_अगर /*_DPU_HW_MERGE3D_H */
