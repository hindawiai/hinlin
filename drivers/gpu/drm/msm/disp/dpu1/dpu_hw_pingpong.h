<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_PINGPONG_H
#घोषणा _DPU_HW_PINGPONG_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"

#घोषणा DITHER_MATRIX_SZ 16

काष्ठा dpu_hw_pingpong;

काष्ठा dpu_hw_tear_check अणु
	/*
	 * This is ratio of MDP VSYNC clk freq(Hz) to
	 * refresh rate भागided by no of lines
	 */
	u32 vsync_count;
	u32 sync_cfg_height;
	u32 vsync_init_val;
	u32 sync_threshold_start;
	u32 sync_threshold_जारी;
	u32 start_pos;
	u32 rd_ptr_irq;
	u8 hw_vsync_mode;
पूर्ण;

काष्ठा dpu_hw_pp_vsync_info अणु
	u32 rd_ptr_init_val;	/* value of rd poपूर्णांकer at vsync edge */
	u32 rd_ptr_frame_count;	/* num frames sent since enabling पूर्णांकerface */
	u32 rd_ptr_line_count;	/* current line on panel (rd ptr) */
	u32 wr_ptr_line_count;	/* current line within pp fअगरo (wr ptr) */
पूर्ण;

/**
 * काष्ठा dpu_hw_dither_cfg - dither feature काष्ठाure
 * @flags: क्रम customizing operations
 * @temporal_en: temperal dither enable
 * @c0_bitdepth: c0 component bit depth
 * @c1_bitdepth: c1 component bit depth
 * @c2_bitdepth: c2 component bit depth
 * @c3_bitdepth: c2 component bit depth
 * @matrix: dither strength matrix
 */
काष्ठा dpu_hw_dither_cfg अणु
	u64 flags;
	u32 temporal_en;
	u32 c0_bitdepth;
	u32 c1_bitdepth;
	u32 c2_bitdepth;
	u32 c3_bitdepth;
	u32 matrix[DITHER_MATRIX_SZ];
पूर्ण;

/**
 *
 * काष्ठा dpu_hw_pingpong_ops : Interface to the pingpong Hw driver functions
 *  Assumption is these functions will be called after घड़ीs are enabled
 *  @setup_tearcheck : program tear check values
 *  @enable_tearcheck : enables tear check
 *  @get_vsync_info : retries timing info of the panel
 *  @setup_स्वतःrefresh : configure and enable the स्वतःrefresh config
 *  @get_स्वतःrefresh : retrieve स्वतःrefresh config from hardware
 *  @setup_dither : function to program the dither hw block
 *  @get_line_count: obtain current vertical line counter
 */
काष्ठा dpu_hw_pingpong_ops अणु
	/**
	 * enables vysnc generation and sets up init value of
	 * पढ़ो poपूर्णांकer and programs the tear check cofiguration
	 */
	पूर्णांक (*setup_tearcheck)(काष्ठा dpu_hw_pingpong *pp,
			काष्ठा dpu_hw_tear_check *cfg);

	/**
	 * enables tear check block
	 */
	पूर्णांक (*enable_tearcheck)(काष्ठा dpu_hw_pingpong *pp,
			bool enable);

	/**
	 * पढ़ो, modअगरy, ग_लिखो to either set or clear listening to बाह्यal TE
	 * @Return: 1 अगर TE was originally connected, 0 अगर not, or -ERROR
	 */
	पूर्णांक (*connect_बाह्यal_te)(काष्ठा dpu_hw_pingpong *pp,
			bool enable_बाह्यal_te);

	/**
	 * provides the programmed and current
	 * line_count
	 */
	पूर्णांक (*get_vsync_info)(काष्ठा dpu_hw_pingpong *pp,
			काष्ठा dpu_hw_pp_vsync_info  *info);

	/**
	 * configure and enable the स्वतःrefresh config
	 */
	व्योम (*setup_स्वतःrefresh)(काष्ठा dpu_hw_pingpong *pp,
				  u32 frame_count, bool enable);

	/**
	 * retrieve स्वतःrefresh config from hardware
	 */
	bool (*get_स्वतःrefresh)(काष्ठा dpu_hw_pingpong *pp,
				u32 *frame_count);

	/**
	 * poll until ग_लिखो poपूर्णांकer transmission starts
	 * @Return: 0 on success, -ETIMEDOUT on समयout
	 */
	पूर्णांक (*poll_समयout_wr_ptr)(काष्ठा dpu_hw_pingpong *pp, u32 समयout_us);

	/**
	 * Obtain current vertical line counter
	 */
	u32 (*get_line_count)(काष्ठा dpu_hw_pingpong *pp);

	/**
	 * Setup dither matix क्रम pingpong block
	 */
	व्योम (*setup_dither)(काष्ठा dpu_hw_pingpong *pp,
			काष्ठा dpu_hw_dither_cfg *cfg);
पूर्ण;

काष्ठा dpu_hw_pingpong अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* pingpong */
	क्रमागत dpu_pingpong idx;
	स्थिर काष्ठा dpu_pingpong_cfg *caps;
	काष्ठा dpu_hw_blk *merge_3d;

	/* ops */
	काष्ठा dpu_hw_pingpong_ops ops;
पूर्ण;

/**
 * to_dpu_hw_pingpong - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_pingpong *to_dpu_hw_pingpong(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_pingpong, base);
पूर्ण

/**
 * dpu_hw_pingpong_init - initializes the pingpong driver क्रम the passed
 *	pingpong idx.
 * @idx:  Pingpong index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDP
 * @m:    Poपूर्णांकer to mdss catalog data
 * Returns: Error code or allocated dpu_hw_pingpong context
 */
काष्ठा dpu_hw_pingpong *dpu_hw_pingpong_init(क्रमागत dpu_pingpong idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_pingpong_destroy - destroys pingpong driver context
 *	should be called to मुक्त the context
 * @pp:   Poपूर्णांकer to PP driver context वापसed by dpu_hw_pingpong_init
 */
व्योम dpu_hw_pingpong_destroy(काष्ठा dpu_hw_pingpong *pp);

#पूर्ण_अगर /*_DPU_HW_PINGPONG_H */
