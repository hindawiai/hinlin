<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_SSPP_H
#घोषणा _DPU_HW_SSPP_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"
#समावेश "dpu_formats.h"

काष्ठा dpu_hw_pipe;

/**
 * Flags
 */
#घोषणा DPU_SSPP_FLIP_LR		BIT(0)
#घोषणा DPU_SSPP_FLIP_UD		BIT(1)
#घोषणा DPU_SSPP_SOURCE_ROTATED_90	BIT(2)
#घोषणा DPU_SSPP_ROT_90			BIT(3)
#घोषणा DPU_SSPP_SOLID_FILL		BIT(4)

/**
 * Define all scaler feature bits in catalog
 */
#घोषणा DPU_SSPP_SCALER ((1UL << DPU_SSPP_SCALER_RGB) | \
	(1UL << DPU_SSPP_SCALER_QSEED2) | \
	 (1UL << DPU_SSPP_SCALER_QSEED3) | \
	 (1UL << DPU_SSPP_SCALER_QSEED3LITE) | \
	  (1UL << DPU_SSPP_SCALER_QSEED4))

/**
 * Component indices
 */
क्रमागत अणु
	DPU_SSPP_COMP_0,
	DPU_SSPP_COMP_1_2,
	DPU_SSPP_COMP_2,
	DPU_SSPP_COMP_3,

	DPU_SSPP_COMP_MAX
पूर्ण;

/**
 * DPU_SSPP_RECT_SOLO - multirect disabled
 * DPU_SSPP_RECT_0 - rect0 of a multirect pipe
 * DPU_SSPP_RECT_1 - rect1 of a multirect pipe
 *
 * Note: HW supports multirect with either RECT0 or
 * RECT1. Considering no benefit of such configs over
 * SOLO mode and to keep the plane management simple,
 * we करोnt support single rect multirect configs.
 */
क्रमागत dpu_sspp_multirect_index अणु
	DPU_SSPP_RECT_SOLO = 0,
	DPU_SSPP_RECT_0,
	DPU_SSPP_RECT_1,
पूर्ण;

क्रमागत dpu_sspp_multirect_mode अणु
	DPU_SSPP_MULTIRECT_NONE = 0,
	DPU_SSPP_MULTIRECT_PARALLEL,
	DPU_SSPP_MULTIRECT_TIME_MX,
पूर्ण;

क्रमागत अणु
	DPU_FRAME_LINEAR,
	DPU_FRAME_TILE_A4X,
	DPU_FRAME_TILE_A5X,
पूर्ण;

क्रमागत dpu_hw_filter अणु
	DPU_SCALE_FILTER_NEAREST = 0,
	DPU_SCALE_FILTER_BIL,
	DPU_SCALE_FILTER_PCMN,
	DPU_SCALE_FILTER_CA,
	DPU_SCALE_FILTER_MAX
पूर्ण;

क्रमागत dpu_hw_filter_alpa अणु
	DPU_SCALE_ALPHA_PIXEL_REP,
	DPU_SCALE_ALPHA_BIL
पूर्ण;

क्रमागत dpu_hw_filter_yuv अणु
	DPU_SCALE_2D_4X4,
	DPU_SCALE_2D_CIR,
	DPU_SCALE_1D_SEP,
	DPU_SCALE_BIL
पूर्ण;

काष्ठा dpu_hw_sharp_cfg अणु
	u32 strength;
	u32 edge_thr;
	u32 smooth_thr;
	u32 noise_thr;
पूर्ण;

काष्ठा dpu_hw_pixel_ext अणु
	/* scaling factors are enabled क्रम this input layer */
	uपूर्णांक8_t enable_pxl_ext;

	पूर्णांक init_phase_x[DPU_MAX_PLANES];
	पूर्णांक phase_step_x[DPU_MAX_PLANES];
	पूर्णांक init_phase_y[DPU_MAX_PLANES];
	पूर्णांक phase_step_y[DPU_MAX_PLANES];

	/*
	 * Number of pixels extension in left, right, top and bottom direction
	 * क्रम all color components. This pixel value क्रम each color component
	 * should be sum of fetch + repeat pixels.
	 */
	पूर्णांक num_ext_pxls_left[DPU_MAX_PLANES];
	पूर्णांक num_ext_pxls_right[DPU_MAX_PLANES];
	पूर्णांक num_ext_pxls_top[DPU_MAX_PLANES];
	पूर्णांक num_ext_pxls_bपंचांग[DPU_MAX_PLANES];

	/*
	 * Number of pixels needs to be overfetched in left, right, top and
	 * bottom directions from source image क्रम scaling.
	 */
	पूर्णांक left_ftch[DPU_MAX_PLANES];
	पूर्णांक right_ftch[DPU_MAX_PLANES];
	पूर्णांक top_ftch[DPU_MAX_PLANES];
	पूर्णांक bपंचांग_ftch[DPU_MAX_PLANES];

	/*
	 * Number of pixels needs to be repeated in left, right, top and
	 * bottom directions क्रम scaling.
	 */
	पूर्णांक left_rpt[DPU_MAX_PLANES];
	पूर्णांक right_rpt[DPU_MAX_PLANES];
	पूर्णांक top_rpt[DPU_MAX_PLANES];
	पूर्णांक bपंचांग_rpt[DPU_MAX_PLANES];

	uपूर्णांक32_t roi_w[DPU_MAX_PLANES];
	uपूर्णांक32_t roi_h[DPU_MAX_PLANES];

	/*
	 * Filter type to be used क्रम scaling in horizontal and vertical
	 * directions
	 */
	क्रमागत dpu_hw_filter horz_filter[DPU_MAX_PLANES];
	क्रमागत dpu_hw_filter vert_filter[DPU_MAX_PLANES];

पूर्ण;

/**
 * काष्ठा dpu_hw_pipe_cfg : Pipe description
 * @layout:    क्रमmat layout inक्रमmation क्रम programming buffer to hardware
 * @src_rect:  src ROI, caller takes पूर्णांकo account the dअगरferent operations
 *             such as decimation, flip etc to program this field
 * @dest_rect: destination ROI.
 * @index:     index of the rectangle of SSPP
 * @mode:      parallel or समय multiplex multirect mode
 */
काष्ठा dpu_hw_pipe_cfg अणु
	काष्ठा dpu_hw_fmt_layout layout;
	काष्ठा drm_rect src_rect;
	काष्ठा drm_rect dst_rect;
	क्रमागत dpu_sspp_multirect_index index;
	क्रमागत dpu_sspp_multirect_mode mode;
पूर्ण;

/**
 * काष्ठा dpu_hw_pipe_qos_cfg : Source pipe QoS configuration
 * @danger_lut: LUT क्रम generate danger level based on fill level
 * @safe_lut: LUT क्रम generate safe level based on fill level
 * @creq_lut: LUT क्रम generate creq level based on fill level
 * @creq_vblank: creq value generated to vbअगर during vertical blanking
 * @danger_vblank: danger value generated during vertical blanking
 * @vblank_en: enable creq_vblank and danger_vblank during vblank
 * @danger_safe_en: enable danger safe generation
 */
काष्ठा dpu_hw_pipe_qos_cfg अणु
	u32 danger_lut;
	u32 safe_lut;
	u64 creq_lut;
	u32 creq_vblank;
	u32 danger_vblank;
	bool vblank_en;
	bool danger_safe_en;
पूर्ण;

/**
 * क्रमागत CDP preload ahead address size
 */
क्रमागत अणु
	DPU_SSPP_CDP_PRELOAD_AHEAD_32,
	DPU_SSPP_CDP_PRELOAD_AHEAD_64
पूर्ण;

/**
 * काष्ठा dpu_hw_pipe_cdp_cfg : CDP configuration
 * @enable: true to enable CDP
 * @ubwc_meta_enable: true to enable ubwc metadata preload
 * @tile_amortize_enable: true to enable amortization control क्रम tile क्रमmat
 * @preload_ahead: number of request to preload ahead
 *	DPU_SSPP_CDP_PRELOAD_AHEAD_32,
 *	DPU_SSPP_CDP_PRELOAD_AHEAD_64
 */
काष्ठा dpu_hw_pipe_cdp_cfg अणु
	bool enable;
	bool ubwc_meta_enable;
	bool tile_amortize_enable;
	u32 preload_ahead;
पूर्ण;

/**
 * काष्ठा dpu_hw_pipe_ts_cfg - traffic shaper configuration
 * @size: size to prefill in bytes, or zero to disable
 * @समय: समय to prefill in usec, or zero to disable
 */
काष्ठा dpu_hw_pipe_ts_cfg अणु
	u64 size;
	u64 समय;
पूर्ण;

/**
 * काष्ठा dpu_hw_sspp_ops - पूर्णांकerface to the SSPP Hw driver functions
 * Caller must call the init function to get the pipe context क्रम each pipe
 * Assumption is these functions will be called after घड़ीs are enabled
 */
काष्ठा dpu_hw_sspp_ops अणु
	/**
	 * setup_क्रमmat - setup pixel क्रमmat cropping rectangle, flip
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe config काष्ठाure
	 * @flags: Extra flags क्रम क्रमmat config
	 * @index: rectangle index in multirect
	 */
	व्योम (*setup_क्रमmat)(काष्ठा dpu_hw_pipe *ctx,
			स्थिर काष्ठा dpu_क्रमmat *fmt, u32 flags,
			क्रमागत dpu_sspp_multirect_index index);

	/**
	 * setup_rects - setup pipe ROI rectangles
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe config काष्ठाure
	 * @index: rectangle index in multirect
	 */
	व्योम (*setup_rects)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_cfg *cfg,
			क्रमागत dpu_sspp_multirect_index index);

	/**
	 * setup_pe - setup pipe pixel extension
	 * @ctx: Poपूर्णांकer to pipe context
	 * @pe_ext: Poपूर्णांकer to pixel ext settings
	 */
	व्योम (*setup_pe)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pixel_ext *pe_ext);

	/**
	 * setup_sourceaddress - setup pipe source addresses
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe config काष्ठाure
	 * @index: rectangle index in multirect
	 */
	व्योम (*setup_sourceaddress)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_cfg *cfg,
			क्रमागत dpu_sspp_multirect_index index);

	/**
	 * setup_csc - setup color space coversion
	 * @ctx: Poपूर्णांकer to pipe context
	 * @data: Poपूर्णांकer to config काष्ठाure
	 */
	व्योम (*setup_csc)(काष्ठा dpu_hw_pipe *ctx, काष्ठा dpu_csc_cfg *data);

	/**
	 * setup_solidfill - enable/disable colorfill
	 * @ctx: Poपूर्णांकer to pipe context
	 * @स्थिर_color: Fill color value
	 * @flags: Pipe flags
	 * @index: rectangle index in multirect
	 */
	व्योम (*setup_solidfill)(काष्ठा dpu_hw_pipe *ctx, u32 color,
			क्रमागत dpu_sspp_multirect_index index);

	/**
	 * setup_multirect - setup multirect configuration
	 * @ctx: Poपूर्णांकer to pipe context
	 * @index: rectangle index in multirect
	 * @mode: parallel fetch / समय multiplex multirect mode
	 */

	व्योम (*setup_multirect)(काष्ठा dpu_hw_pipe *ctx,
			क्रमागत dpu_sspp_multirect_index index,
			क्रमागत dpu_sspp_multirect_mode mode);

	/**
	 * setup_sharpening - setup sharpening
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to config काष्ठाure
	 */
	व्योम (*setup_sharpening)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_sharp_cfg *cfg);

	/**
	 * setup_danger_safe_lut - setup danger safe LUTs
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe QoS configuration
	 *
	 */
	व्योम (*setup_danger_safe_lut)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_qos_cfg *cfg);

	/**
	 * setup_creq_lut - setup CREQ LUT
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe QoS configuration
	 *
	 */
	व्योम (*setup_creq_lut)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_qos_cfg *cfg);

	/**
	 * setup_qos_ctrl - setup QoS control
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to pipe QoS configuration
	 *
	 */
	व्योम (*setup_qos_ctrl)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_qos_cfg *cfg);

	/**
	 * setup_histogram - setup histograms
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to histogram configuration
	 */
	व्योम (*setup_histogram)(काष्ठा dpu_hw_pipe *ctx,
			व्योम *cfg);

	/**
	 * setup_scaler - setup scaler
	 * @ctx: Poपूर्णांकer to pipe context
	 * @pipe_cfg: Poपूर्णांकer to pipe configuration
	 * @pe_cfg: Poपूर्णांकer to pixel extension configuration
	 * @scaler_cfg: Poपूर्णांकer to scaler configuration
	 */
	व्योम (*setup_scaler)(काष्ठा dpu_hw_pipe *ctx,
		काष्ठा dpu_hw_pipe_cfg *pipe_cfg,
		काष्ठा dpu_hw_pixel_ext *pe_cfg,
		व्योम *scaler_cfg);

	/**
	 * get_scaler_ver - get scaler h/w version
	 * @ctx: Poपूर्णांकer to pipe context
	 */
	u32 (*get_scaler_ver)(काष्ठा dpu_hw_pipe *ctx);

	/**
	 * setup_cdp - setup client driven prefetch
	 * @ctx: Poपूर्णांकer to pipe context
	 * @cfg: Poपूर्णांकer to cdp configuration
	 */
	व्योम (*setup_cdp)(काष्ठा dpu_hw_pipe *ctx,
			काष्ठा dpu_hw_pipe_cdp_cfg *cfg);
पूर्ण;

/**
 * काष्ठा dpu_hw_pipe - pipe description
 * @base: hardware block base काष्ठाure
 * @hw: block hardware details
 * @catalog: back poपूर्णांकer to catalog
 * @mdp: poपूर्णांकer to associated mdp portion of the catalog
 * @idx: pipe index
 * @cap: poपूर्णांकer to layer_cfg
 * @ops: poपूर्णांकer to operations possible क्रम this pipe
 */
काष्ठा dpu_hw_pipe अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;
	काष्ठा dpu_mdss_cfg *catalog;
	स्थिर काष्ठा dpu_mdp_cfg *mdp;

	/* Pipe */
	क्रमागत dpu_sspp idx;
	स्थिर काष्ठा dpu_sspp_cfg *cap;

	/* Ops */
	काष्ठा dpu_hw_sspp_ops ops;
पूर्ण;

/**
 * dpu_hw_sspp_init - initializes the sspp hw driver object.
 * Should be called once beक्रमe accessing every pipe.
 * @idx:  Pipe index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDP
 * @catalog : Poपूर्णांकer to mdss catalog data
 * @is_भव_pipe: is this pipe भव pipe
 */
काष्ठा dpu_hw_pipe *dpu_hw_sspp_init(क्रमागत dpu_sspp idx,
		व्योम __iomem *addr, काष्ठा dpu_mdss_cfg *catalog,
		bool is_भव_pipe);

/**
 * dpu_hw_sspp_destroy(): Destroys SSPP driver context
 * should be called during Hw pipe cleanup.
 * @ctx:  Poपूर्णांकer to SSPP driver context वापसed by dpu_hw_sspp_init
 */
व्योम dpu_hw_sspp_destroy(काष्ठा dpu_hw_pipe *ctx);

#पूर्ण_अगर /*_DPU_HW_SSPP_H */

