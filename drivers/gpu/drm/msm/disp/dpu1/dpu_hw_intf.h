<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_INTF_H
#घोषणा _DPU_HW_INTF_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"

काष्ठा dpu_hw_पूर्णांकf;

/* पूर्णांकf timing settings */
काष्ठा पूर्णांकf_timing_params अणु
	u32 width;		/* active width */
	u32 height;		/* active height */
	u32 xres;		/* Display panel width */
	u32 yres;		/* Display panel height */

	u32 h_back_porch;
	u32 h_front_porch;
	u32 v_back_porch;
	u32 v_front_porch;
	u32 hsync_pulse_width;
	u32 vsync_pulse_width;
	u32 hsync_polarity;
	u32 vsync_polarity;
	u32 border_clr;
	u32 underflow_clr;
	u32 hsync_skew;
पूर्ण;

काष्ठा पूर्णांकf_prog_fetch अणु
	u8 enable;
	/* vsync counter क्रम the front porch pixel line */
	u32 fetch_start;
पूर्ण;

काष्ठा पूर्णांकf_status अणु
	u8 is_en;		/* पूर्णांकerface timing engine is enabled or not */
	u8 is_prog_fetch_en;	/* पूर्णांकerface prog fetch counter is enabled or not */
	u32 frame_count;	/* frame count since timing engine enabled */
	u32 line_count;		/* current line count including blanking */
पूर्ण;

/**
 * काष्ठा dpu_hw_पूर्णांकf_ops : Interface to the पूर्णांकerface Hw driver functions
 *  Assumption is these functions will be called after घड़ीs are enabled
 * @ setup_timing_gen : programs the timing engine
 * @ setup_prog_fetch : enables/disables the programmable fetch logic
 * @ enable_timing: enable/disable timing engine
 * @ get_status: वापसs अगर timing engine is enabled or not
 * @ get_line_count: पढ़ोs current vertical line counter
 * @bind_pingpong_blk: enable/disable the connection with pingpong which will
 *                     feed pixels to this पूर्णांकerface
 */
काष्ठा dpu_hw_पूर्णांकf_ops अणु
	व्योम (*setup_timing_gen)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
			स्थिर काष्ठा पूर्णांकf_timing_params *p,
			स्थिर काष्ठा dpu_क्रमmat *fmt);

	व्योम (*setup_prg_fetch)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
			स्थिर काष्ठा पूर्णांकf_prog_fetch *fetch);

	व्योम (*enable_timing)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
			u8 enable);

	व्योम (*get_status)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
			काष्ठा पूर्णांकf_status *status);

	u32 (*get_line_count)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf);

	व्योम (*bind_pingpong_blk)(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
			bool enable,
			स्थिर क्रमागत dpu_pingpong pp);
पूर्ण;

काष्ठा dpu_hw_पूर्णांकf अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* पूर्णांकf */
	क्रमागत dpu_पूर्णांकf idx;
	स्थिर काष्ठा dpu_पूर्णांकf_cfg *cap;
	स्थिर काष्ठा dpu_mdss_cfg *mdss;

	/* ops */
	काष्ठा dpu_hw_पूर्णांकf_ops ops;
पूर्ण;

/**
 * to_dpu_hw_पूर्णांकf - convert base object dpu_hw_base to container
 * @hw: Poपूर्णांकer to base hardware block
 * वापस: Poपूर्णांकer to hardware block container
 */
अटल अंतरभूत काष्ठा dpu_hw_पूर्णांकf *to_dpu_hw_पूर्णांकf(काष्ठा dpu_hw_blk *hw)
अणु
	वापस container_of(hw, काष्ठा dpu_hw_पूर्णांकf, base);
पूर्ण

/**
 * dpu_hw_पूर्णांकf_init(): Initializes the पूर्णांकf driver क्रम the passed
 * पूर्णांकerface idx.
 * @idx:  पूर्णांकerface index क्रम which driver object is required
 * @addr: mapped रेजिस्टर io address of MDP
 * @m :   poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_पूर्णांकf *dpu_hw_पूर्णांकf_init(क्रमागत dpu_पूर्णांकf idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

/**
 * dpu_hw_पूर्णांकf_destroy(): Destroys INTF driver context
 * @पूर्णांकf:   Poपूर्णांकer to INTF driver context
 */
व्योम dpu_hw_पूर्णांकf_destroy(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf);

#पूर्ण_अगर /*_DPU_HW_INTF_H */
