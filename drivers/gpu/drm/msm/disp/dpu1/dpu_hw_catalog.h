<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_CATALOG_H
#घोषणा _DPU_HW_CATALOG_H

#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>

/**
 * Max hardware block count: For ex: max 12 SSPP pipes or
 * 5 ctl paths. In all हालs, it can have max 12 hardware blocks
 * based on current design
 */
#घोषणा MAX_BLOCKS    12

#घोषणा DPU_HW_VER(MAJOR, MINOR, STEP) (((MAJOR & 0xF) << 28)    |\
		((MINOR & 0xFFF) << 16)  |\
		(STEP & 0xFFFF))

#घोषणा DPU_HW_MAJOR(rev)		((rev) >> 28)
#घोषणा DPU_HW_MINOR(rev)		(((rev) >> 16) & 0xFFF)
#घोषणा DPU_HW_STEP(rev)		((rev) & 0xFFFF)
#घोषणा DPU_HW_MAJOR_MINOR(rev)		((rev) >> 16)

#घोषणा IS_DPU_MAJOR_MINOR_SAME(rev1, rev2)   \
	(DPU_HW_MAJOR_MINOR((rev1)) == DPU_HW_MAJOR_MINOR((rev2)))

#घोषणा DPU_HW_VER_170	DPU_HW_VER(1, 7, 0) /* 8996 v1.0 */
#घोषणा DPU_HW_VER_171	DPU_HW_VER(1, 7, 1) /* 8996 v2.0 */
#घोषणा DPU_HW_VER_172	DPU_HW_VER(1, 7, 2) /* 8996 v3.0 */
#घोषणा DPU_HW_VER_300	DPU_HW_VER(3, 0, 0) /* 8998 v1.0 */
#घोषणा DPU_HW_VER_301	DPU_HW_VER(3, 0, 1) /* 8998 v1.1 */
#घोषणा DPU_HW_VER_400	DPU_HW_VER(4, 0, 0) /* sdm845 v1.0 */
#घोषणा DPU_HW_VER_401	DPU_HW_VER(4, 0, 1) /* sdm845 v2.0 */
#घोषणा DPU_HW_VER_410	DPU_HW_VER(4, 1, 0) /* sdm670 v1.0 */
#घोषणा DPU_HW_VER_500	DPU_HW_VER(5, 0, 0) /* sm8150 v1.0 */
#घोषणा DPU_HW_VER_501	DPU_HW_VER(5, 0, 1) /* sm8150 v2.0 */
#घोषणा DPU_HW_VER_600	DPU_HW_VER(6, 0, 0) /* sm8250 */
#घोषणा DPU_HW_VER_620	DPU_HW_VER(6, 2, 0) /* sc7180 v1.0 */
#घोषणा DPU_HW_VER_720	DPU_HW_VER(7, 2, 0) /* sc7280 */

#घोषणा IS_MSM8996_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_170)
#घोषणा IS_MSM8998_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_300)
#घोषणा IS_SDM845_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_400)
#घोषणा IS_SDM670_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_410)
#घोषणा IS_SDM855_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_500)
#घोषणा IS_SC7180_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_620)
#घोषणा IS_SC7280_TARGET(rev) IS_DPU_MAJOR_MINOR_SAME((rev), DPU_HW_VER_720)

#घोषणा DPU_HW_BLK_NAME_LEN	16

#घोषणा MAX_IMG_WIDTH 0x3fff
#घोषणा MAX_IMG_HEIGHT 0x3fff

#घोषणा CRTC_DUAL_MIXERS	2

#घोषणा MAX_XIN_COUNT 16

/**
 * Supported UBWC feature versions
 */
क्रमागत अणु
	DPU_HW_UBWC_VER_10 = 0x100,
	DPU_HW_UBWC_VER_20 = 0x200,
	DPU_HW_UBWC_VER_30 = 0x300,
	DPU_HW_UBWC_VER_40 = 0x400,
पूर्ण;

/**
 * MDP TOP BLOCK features
 * @DPU_MDP_PANIC_PER_PIPE Panic configuration needs to be be करोne per pipe
 * @DPU_MDP_10BIT_SUPPORT, Chipset supports 10 bit pixel क्रमmats
 * @DPU_MDP_BWC,           MDSS HW supports Bandwidth compression.
 * @DPU_MDP_UBWC_1_0,      This chipsets supports Universal Bandwidth
 *                         compression initial revision
 * @DPU_MDP_UBWC_1_5,      Universal Bandwidth compression version 1.5
 * @DPU_MDP_MAX            Maximum value

 */
क्रमागत अणु
	DPU_MDP_PANIC_PER_PIPE = 0x1,
	DPU_MDP_10BIT_SUPPORT,
	DPU_MDP_BWC,
	DPU_MDP_UBWC_1_0,
	DPU_MDP_UBWC_1_5,
	DPU_MDP_MAX
पूर्ण;

/**
 * SSPP sub-blocks/features
 * @DPU_SSPP_SRC             Src and fetch part of the pipes,
 * @DPU_SSPP_SCALER_QSEED2,  QSEED2 algorithm support
 * @DPU_SSPP_SCALER_QSEED3,  QSEED3 alogorithm support
 * @DPU_SSPP_SCALER_QSEED3LITE,  QSEED3 Lite alogorithm support
 * @DPU_SSPP_SCALER_QSEED4,  QSEED4 algorithm support
 * @DPU_SSPP_SCALER_RGB,     RGB Scaler, supported by RGB pipes
 * @DPU_SSPP_CSC,            Support of Color space converion
 * @DPU_SSPP_CSC_10BIT,      Support of 10-bit Color space conversion
 * @DPU_SSPP_CURSOR,         SSPP can be used as a cursor layer
 * @DPU_SSPP_QOS,            SSPP support QoS control, danger/safe/creq
 * @DPU_SSPP_QOS_8LVL,       SSPP support 8-level QoS control
 * @DPU_SSPP_EXCL_RECT,      SSPP supports exclusion rect
 * @DPU_SSPP_SMART_DMA_V1,   SmartDMA 1.0 support
 * @DPU_SSPP_SMART_DMA_V2,   SmartDMA 2.0 support
 * @DPU_SSPP_TS_PREFILL      Supports prefill with traffic shaper
 * @DPU_SSPP_TS_PREFILL_REC1 Supports prefill with traffic shaper multirec
 * @DPU_SSPP_CDP             Supports client driven prefetch
 * @DPU_SSPP_MAX             maximum value
 */
क्रमागत अणु
	DPU_SSPP_SRC = 0x1,
	DPU_SSPP_SCALER_QSEED2,
	DPU_SSPP_SCALER_QSEED3,
	DPU_SSPP_SCALER_QSEED3LITE,
	DPU_SSPP_SCALER_QSEED4,
	DPU_SSPP_SCALER_RGB,
	DPU_SSPP_CSC,
	DPU_SSPP_CSC_10BIT,
	DPU_SSPP_CURSOR,
	DPU_SSPP_QOS,
	DPU_SSPP_QOS_8LVL,
	DPU_SSPP_EXCL_RECT,
	DPU_SSPP_SMART_DMA_V1,
	DPU_SSPP_SMART_DMA_V2,
	DPU_SSPP_TS_PREFILL,
	DPU_SSPP_TS_PREFILL_REC1,
	DPU_SSPP_CDP,
	DPU_SSPP_MAX
पूर्ण;

/*
 * MIXER sub-blocks/features
 * @DPU_MIXER_LAYER           Layer mixer layer blend configuration,
 * @DPU_MIXER_SOURCESPLIT     Layer mixer supports source-split configuration
 * @DPU_MIXER_GC              Gamma correction block
 * @DPU_DIM_LAYER             Layer mixer supports dim layer
 * @DPU_MIXER_MAX             maximum value
 */
क्रमागत अणु
	DPU_MIXER_LAYER = 0x1,
	DPU_MIXER_SOURCESPLIT,
	DPU_MIXER_GC,
	DPU_DIM_LAYER,
	DPU_MIXER_MAX
पूर्ण;

/**
 * DSPP sub-blocks
 * @DPU_DSPP_PCC             Panel color correction block
 * @DPU_DSPP_GC              Gamma correction block
 */
क्रमागत अणु
	DPU_DSPP_PCC = 0x1,
	DPU_DSPP_GC,
	DPU_DSPP_MAX
पूर्ण;

/**
 * PINGPONG sub-blocks
 * @DPU_PINGPONG_TE         Tear check block
 * @DPU_PINGPONG_TE2        Additional tear check block क्रम split pipes
 * @DPU_PINGPONG_SPLIT      PP block supports split fअगरo
 * @DPU_PINGPONG_SLAVE      PP block is a suitable slave क्रम split fअगरo
 * @DPU_PINGPONG_DITHER,    Dither blocks
 * @DPU_PINGPONG_MAX
 */
क्रमागत अणु
	DPU_PINGPONG_TE = 0x1,
	DPU_PINGPONG_TE2,
	DPU_PINGPONG_SPLIT,
	DPU_PINGPONG_SLAVE,
	DPU_PINGPONG_DITHER,
	DPU_PINGPONG_MAX
पूर्ण;

/**
 * CTL sub-blocks
 * @DPU_CTL_SPLIT_DISPLAY       CTL supports video mode split display
 * @DPU_CTL_MAX
 */
क्रमागत अणु
	DPU_CTL_SPLIT_DISPLAY = 0x1,
	DPU_CTL_ACTIVE_CFG,
	DPU_CTL_FETCH_ACTIVE,
	DPU_CTL_MAX
पूर्ण;

/**
 * INTF sub-blocks
 * @DPU_INTF_INPUT_CTRL         Supports the setting of pp block from which
 *                              pixel data arrives to this INTF
 * @DPU_INTF_TE                 INTF block has TE configuration support
 * @DPU_DATA_HCTL_EN            Allows data to be transferred at dअगरferent rate
                                than video timing
 * @DPU_INTF_MAX
 */
क्रमागत अणु
	DPU_INTF_INPUT_CTRL = 0x1,
	DPU_INTF_TE,
	DPU_DATA_HCTL_EN,
	DPU_INTF_MAX
पूर्ण;

/**
 * VBIF sub-blocks and features
 * @DPU_VBIF_QOS_OTLIM        VBIF supports OT Limit
 * @DPU_VBIF_QOS_REMAP        VBIF supports QoS priority remap
 * @DPU_VBIF_MAX              maximum value
 */
क्रमागत अणु
	DPU_VBIF_QOS_OTLIM = 0x1,
	DPU_VBIF_QOS_REMAP,
	DPU_VBIF_MAX
पूर्ण;

/**
 * MACRO DPU_HW_BLK_INFO - inक्रमmation of HW blocks inside DPU
 * @name:              string name क्रम debug purposes
 * @id:                क्रमागत identअगरying this block
 * @base:              रेजिस्टर base offset to mdss
 * @len:               length of hardware block
 * @features           bit mask identअगरying sub-blocks/features
 */
#घोषणा DPU_HW_BLK_INFO \
	अक्षर name[DPU_HW_BLK_NAME_LEN]; \
	u32 id; \
	u32 base; \
	u32 len; \
	अचिन्हित दीर्घ features

/**
 * MACRO DPU_HW_SUBBLK_INFO - inक्रमmation of HW sub-block inside DPU
 * @name:              string name क्रम debug purposes
 * @id:                क्रमागत identअगरying this sub-block
 * @base:              offset of this sub-block relative to the block
 *                     offset
 * @len                रेजिस्टर block length of this sub-block
 */
#घोषणा DPU_HW_SUBBLK_INFO \
	अक्षर name[DPU_HW_BLK_NAME_LEN]; \
	u32 id; \
	u32 base; \
	u32 len

/**
 * काष्ठा dpu_src_blk: SSPP part of the source pipes
 * @info:   HW रेजिस्टर and features supported by this sub-blk
 */
काष्ठा dpu_src_blk अणु
	DPU_HW_SUBBLK_INFO;
पूर्ण;

/**
 * काष्ठा dpu_scaler_blk: Scaler inक्रमmation
 * @info:   HW रेजिस्टर and features supported by this sub-blk
 * @version: qseed block revision
 */
काष्ठा dpu_scaler_blk अणु
	DPU_HW_SUBBLK_INFO;
	u32 version;
पूर्ण;

काष्ठा dpu_csc_blk अणु
	DPU_HW_SUBBLK_INFO;
पूर्ण;

/**
 * काष्ठा dpu_pp_blk : Pixel processing sub-blk inक्रमmation
 * @info:   HW रेजिस्टर and features supported by this sub-blk
 * @version: HW Algorithm version
 */
काष्ठा dpu_pp_blk अणु
	DPU_HW_SUBBLK_INFO;
	u32 version;
पूर्ण;

/**
 * क्रमागत dpu_qos_lut_usage - define QoS LUT use हालs
 */
क्रमागत dpu_qos_lut_usage अणु
	DPU_QOS_LUT_USAGE_LINEAR,
	DPU_QOS_LUT_USAGE_MACROTILE,
	DPU_QOS_LUT_USAGE_NRT,
	DPU_QOS_LUT_USAGE_MAX,
पूर्ण;

/**
 * काष्ठा dpu_qos_lut_entry - define QoS LUT table entry
 * @fl: fill level, or zero on last entry to indicate शेष lut
 * @lut: lut to use अगर equal to or less than fill level
 */
काष्ठा dpu_qos_lut_entry अणु
	u32 fl;
	u64 lut;
पूर्ण;

/**
 * काष्ठा dpu_qos_lut_tbl - define QoS LUT table
 * @nentry: number of entry in this table
 * @entries: Poपूर्णांकer to table entries
 */
काष्ठा dpu_qos_lut_tbl अणु
	u32 nentry;
	स्थिर काष्ठा dpu_qos_lut_entry *entries;
पूर्ण;

/**
 * काष्ठा dpu_caps - define DPU capabilities
 * @max_mixer_width    max layer mixer line width support.
 * @max_mixer_blendstages max layer mixer blend stages or
 *                       supported z order
 * @qseed_type         qseed2 or qseed3 support.
 * @smart_dma_rev      Supported version of SmartDMA feature.
 * @ubwc_version       UBWC feature version (0x0 क्रम not supported)
 * @has_src_split      source split feature status
 * @has_dim_layer      dim layer feature status
 * @has_idle_pc        indicate अगर idle घातer collapse feature is supported
 * @has_3d_merge       indicate अगर 3D merge is supported
 * @max_linewidth      max linewidth क्रम sspp
 * @pixel_ram_size     size of latency hiding and de-tiling buffer in bytes
 * @max_hdeci_exp      max horizontal decimation supported (max is 2^value)
 * @max_vdeci_exp      max vertical decimation supported (max is 2^value)
 */
काष्ठा dpu_caps अणु
	u32 max_mixer_width;
	u32 max_mixer_blendstages;
	u32 qseed_type;
	u32 smart_dma_rev;
	u32 ubwc_version;
	bool has_src_split;
	bool has_dim_layer;
	bool has_idle_pc;
	bool has_3d_merge;
	/* SSPP limits */
	u32 max_linewidth;
	u32 pixel_ram_size;
	u32 max_hdeci_exp;
	u32 max_vdeci_exp;
पूर्ण;

/**
 * काष्ठा dpu_sspp_sub_blks : SSPP sub-blocks
 * common: Poपूर्णांकer to common configurations shared by sub blocks
 * @creq_vblank: creq priority during vertical blanking
 * @danger_vblank: danger priority during vertical blanking
 * @maxdwnscale: max करोwnscale ratio supported(without DECIMATION)
 * @maxupscale:  maxupscale ratio supported
 * @smart_dma_priority: hw priority of rect1 of multirect pipe
 * @max_per_pipe_bw: maximum allowable bandwidth of this pipe in kBps
 * @qseed_ver: qseed version
 * @src_blk:
 * @scaler_blk:
 * @csc_blk:
 * @hsic:
 * @memcolor:
 * @pcc_blk:
 * @igc_blk:
 * @क्रमmat_list: Poपूर्णांकer to list of supported क्रमmats
 * @num_क्रमmats: Number of supported क्रमmats
 * @virt_क्रमmat_list: Poपूर्णांकer to list of supported क्रमmats क्रम भव planes
 * @virt_num_क्रमmats: Number of supported क्रमmats क्रम भव planes
 */
काष्ठा dpu_sspp_sub_blks अणु
	u32 creq_vblank;
	u32 danger_vblank;
	u32 maxdwnscale;
	u32 maxupscale;
	u32 smart_dma_priority;
	u32 max_per_pipe_bw;
	u32 qseed_ver;
	काष्ठा dpu_src_blk src_blk;
	काष्ठा dpu_scaler_blk scaler_blk;
	काष्ठा dpu_pp_blk csc_blk;
	काष्ठा dpu_pp_blk hsic_blk;
	काष्ठा dpu_pp_blk memcolor_blk;
	काष्ठा dpu_pp_blk pcc_blk;
	काष्ठा dpu_pp_blk igc_blk;

	स्थिर u32 *क्रमmat_list;
	u32 num_क्रमmats;
	स्थिर u32 *virt_क्रमmat_list;
	u32 virt_num_क्रमmats;
पूर्ण;

/**
 * काष्ठा dpu_lm_sub_blks:      inक्रमmation of mixer block
 * @maxwidth:               Max pixel width supported by this mixer
 * @maxblendstages:         Max number of blend-stages supported
 * @blendstage_base:        Blend-stage रेजिस्टर base offset
 * @gc: gamma correction block
 */
काष्ठा dpu_lm_sub_blks अणु
	u32 maxwidth;
	u32 maxblendstages;
	u32 blendstage_base[MAX_BLOCKS];
	काष्ठा dpu_pp_blk gc;
पूर्ण;

/**
 * काष्ठा dpu_dspp_sub_blks: Inक्रमmation of DSPP block
 * @gc : gamma correction block
 * @pcc: pixel color correction block
 */
काष्ठा dpu_dspp_sub_blks अणु
	काष्ठा dpu_pp_blk gc;
	काष्ठा dpu_pp_blk pcc;
पूर्ण;

काष्ठा dpu_pingpong_sub_blks अणु
	काष्ठा dpu_pp_blk te;
	काष्ठा dpu_pp_blk te2;
	काष्ठा dpu_pp_blk dither;
पूर्ण;

/**
 * dpu_clk_ctrl_type - Defines top level घड़ी control संकेतs
 */
क्रमागत dpu_clk_ctrl_type अणु
	DPU_CLK_CTRL_NONE,
	DPU_CLK_CTRL_VIG0,
	DPU_CLK_CTRL_VIG1,
	DPU_CLK_CTRL_VIG2,
	DPU_CLK_CTRL_VIG3,
	DPU_CLK_CTRL_VIG4,
	DPU_CLK_CTRL_RGB0,
	DPU_CLK_CTRL_RGB1,
	DPU_CLK_CTRL_RGB2,
	DPU_CLK_CTRL_RGB3,
	DPU_CLK_CTRL_DMA0,
	DPU_CLK_CTRL_DMA1,
	DPU_CLK_CTRL_CURSOR0,
	DPU_CLK_CTRL_CURSOR1,
	DPU_CLK_CTRL_INLINE_ROT0_SSPP,
	DPU_CLK_CTRL_REG_DMA,
	DPU_CLK_CTRL_MAX,
पूर्ण;

/* काष्ठा dpu_clk_ctrl_reg : Clock control रेजिस्टर
 * @reg_off:           रेजिस्टर offset
 * @bit_off:           bit offset
 */
काष्ठा dpu_clk_ctrl_reg अणु
	u32 reg_off;
	u32 bit_off;
पूर्ण;

/* काष्ठा dpu_mdp_cfg : MDP TOP-BLK instance info
 * @id:                index identअगरying this block
 * @base:              रेजिस्टर base offset to mdss
 * @features           bit mask identअगरying sub-blocks/features
 * @highest_bank_bit:  UBWC parameter
 * @ubwc_अटल:       ubwc अटल configuration
 * @ubwc_swizzle:      ubwc शेष swizzle setting
 * @clk_ctrls          घड़ी control रेजिस्टर definition
 */
काष्ठा dpu_mdp_cfg अणु
	DPU_HW_BLK_INFO;
	u32 highest_bank_bit;
	u32 ubwc_swizzle;
	काष्ठा dpu_clk_ctrl_reg clk_ctrls[DPU_CLK_CTRL_MAX];
पूर्ण;

/* काष्ठा dpu_mdp_cfg : MDP TOP-BLK instance info
 * @id:                index identअगरying this block
 * @base:              रेजिस्टर base offset to mdss
 * @features           bit mask identअगरying sub-blocks/features
 */
काष्ठा dpu_ctl_cfg अणु
	DPU_HW_BLK_INFO;
पूर्ण;

/**
 * काष्ठा dpu_sspp_cfg - inक्रमmation of source pipes
 * @id:                index identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @sblk:              SSPP sub-blocks inक्रमmation
 * @xin_id:            bus client identअगरier
 * @clk_ctrl           घड़ी control identअगरier
 * @type               sspp type identअगरier
 */
काष्ठा dpu_sspp_cfg अणु
	DPU_HW_BLK_INFO;
	स्थिर काष्ठा dpu_sspp_sub_blks *sblk;
	u32 xin_id;
	क्रमागत dpu_clk_ctrl_type clk_ctrl;
	u32 type;
पूर्ण;

/**
 * काष्ठा dpu_lm_cfg - inक्रमmation of layer mixer blocks
 * @id:                index identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @sblk:              LM Sub-blocks inक्रमmation
 * @pingpong:          ID of connected PingPong, PINGPONG_MAX अगर unsupported
 * @lm_pair_mask:      Biपंचांगask of LMs that can be controlled by same CTL
 */
काष्ठा dpu_lm_cfg अणु
	DPU_HW_BLK_INFO;
	स्थिर काष्ठा dpu_lm_sub_blks *sblk;
	u32 pingpong;
	u32 dspp;
	अचिन्हित दीर्घ lm_pair_mask;
पूर्ण;

/**
 * काष्ठा dpu_dspp_cfg - inक्रमmation of DSPP blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 *                     supported by this block
 * @sblk               sub-blocks inक्रमmation
 */
काष्ठा dpu_dspp_cfg  अणु
	DPU_HW_BLK_INFO;
	स्थिर काष्ठा dpu_dspp_sub_blks *sblk;
पूर्ण;

/**
 * काष्ठा dpu_pingpong_cfg - inक्रमmation of PING-PONG blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @sblk               sub-blocks inक्रमmation
 */
काष्ठा dpu_pingpong_cfg  अणु
	DPU_HW_BLK_INFO;
	u32 merge_3d;
	स्थिर काष्ठा dpu_pingpong_sub_blks *sblk;
पूर्ण;

/**
 * काष्ठा dpu_merge_3d_cfg - inक्रमmation of DSPP blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 *                     supported by this block
 * @sblk               sub-blocks inक्रमmation
 */
काष्ठा dpu_merge_3d_cfg  अणु
	DPU_HW_BLK_INFO;
	स्थिर काष्ठा dpu_merge_3d_sub_blks *sblk;
पूर्ण;

/**
 * काष्ठा dpu_पूर्णांकf_cfg - inक्रमmation of timing engine blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @type:              Interface type(DSI, DP, HDMI)
 * @controller_id:     Controller Instance ID in हाल of multiple of पूर्णांकf type
 * @prog_fetch_lines_worst_हाल	Worst हाल latency num lines needed to prefetch
 */
काष्ठा dpu_पूर्णांकf_cfg  अणु
	DPU_HW_BLK_INFO;
	u32 type;   /* पूर्णांकerface type*/
	u32 controller_id;
	u32 prog_fetch_lines_worst_हाल;
पूर्ण;

/**
 * काष्ठा dpu_vbअगर_dynamic_ot_cfg - dynamic OT setting
 * @pps                pixel per seconds
 * @ot_limit           OT limit to use up to specअगरied pixel per second
 */
काष्ठा dpu_vbअगर_dynamic_ot_cfg अणु
	u64 pps;
	u32 ot_limit;
पूर्ण;

/**
 * काष्ठा dpu_vbअगर_dynamic_ot_tbl - dynamic OT setting table
 * @count              length of cfg
 * @cfg                poपूर्णांकer to array of configuration settings with
 *                     ascending requirements
 */
काष्ठा dpu_vbअगर_dynamic_ot_tbl अणु
	u32 count;
	स्थिर काष्ठा dpu_vbअगर_dynamic_ot_cfg *cfg;
पूर्ण;

/**
 * काष्ठा dpu_vbअगर_qos_tbl - QoS priority table
 * @npriority_lvl      num of priority level
 * @priority_lvl       poपूर्णांकer to array of priority level in ascending order
 */
काष्ठा dpu_vbअगर_qos_tbl अणु
	u32 npriority_lvl;
	स्थिर u32 *priority_lvl;
पूर्ण;

/**
 * काष्ठा dpu_vbअगर_cfg - inक्रमmation of VBIF blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @ot_rd_limit        शेष OT पढ़ो limit
 * @ot_wr_limit        शेष OT ग_लिखो limit
 * @xin_halt_समयout   maximum समय (in usec) क्रम xin to halt
 * @dynamic_ot_rd_tbl  dynamic OT पढ़ो configuration table
 * @dynamic_ot_wr_tbl  dynamic OT ग_लिखो configuration table
 * @qos_rt_tbl         real-समय QoS priority table
 * @qos_nrt_tbl        non-real-समय QoS priority table
 * @memtype_count      number of defined memtypes
 * @memtype            array of xin memtype definitions
 */
काष्ठा dpu_vbअगर_cfg अणु
	DPU_HW_BLK_INFO;
	u32 शेष_ot_rd_limit;
	u32 शेष_ot_wr_limit;
	u32 xin_halt_समयout;
	काष्ठा dpu_vbअगर_dynamic_ot_tbl dynamic_ot_rd_tbl;
	काष्ठा dpu_vbअगर_dynamic_ot_tbl dynamic_ot_wr_tbl;
	काष्ठा dpu_vbअगर_qos_tbl qos_rt_tbl;
	काष्ठा dpu_vbअगर_qos_tbl qos_nrt_tbl;
	u32 memtype_count;
	u32 memtype[MAX_XIN_COUNT];
पूर्ण;
/**
 * काष्ठा dpu_reg_dma_cfg - inक्रमmation of lut dma blocks
 * @id                 क्रमागत identअगरying this block
 * @base               रेजिस्टर offset of this block
 * @features           bit mask identअगरying sub-blocks/features
 * @version            version of lutdma hw block
 * @trigger_sel_off    offset to trigger select रेजिस्टरs of lutdma
 */
काष्ठा dpu_reg_dma_cfg अणु
	DPU_HW_BLK_INFO;
	u32 version;
	u32 trigger_sel_off;
	u32 xin_id;
	क्रमागत dpu_clk_ctrl_type clk_ctrl;
पूर्ण;

/**
 * Define CDP use हालs
 * @DPU_PERF_CDP_UDAGE_RT: real-समय use हालs
 * @DPU_PERF_CDP_USAGE_NRT: non real-समय use हालs such as WFD
 */
क्रमागत अणु
	DPU_PERF_CDP_USAGE_RT,
	DPU_PERF_CDP_USAGE_NRT,
	DPU_PERF_CDP_USAGE_MAX
पूर्ण;

/**
 * काष्ठा dpu_perf_cdp_cfg - define CDP use हाल configuration
 * @rd_enable: true अगर पढ़ो pipe CDP is enabled
 * @wr_enable: true अगर ग_लिखो pipe CDP is enabled
 */
काष्ठा dpu_perf_cdp_cfg अणु
	bool rd_enable;
	bool wr_enable;
पूर्ण;

/**
 * काष्ठा dpu_perf_cfg - perक्रमmance control settings
 * @max_bw_low         low threshold of maximum bandwidth (kbps)
 * @max_bw_high        high threshold of maximum bandwidth (kbps)
 * @min_core_ib        minimum bandwidth क्रम core (kbps)
 * @min_core_ib        minimum mnoc ib vote in kbps
 * @min_llcc_ib        minimum llcc ib vote in kbps
 * @min_dram_ib        minimum dram ib vote in kbps
 * @core_ib_ff         core instantaneous bandwidth fudge factor
 * @core_clk_ff        core घड़ी fudge factor
 * @comp_ratio_rt      string of 0 or more of <fourcc>/<ven>/<mod>/<comp ratio>
 * @comp_ratio_nrt     string of 0 or more of <fourcc>/<ven>/<mod>/<comp ratio>
 * @undersized_prefill_lines   undersized prefill in lines
 * @xtra_prefill_lines         extra prefill latency in lines
 * @dest_scale_prefill_lines   destination scaler latency in lines
 * @macrotile_perfill_lines    macrotile latency in lines
 * @yuv_nv12_prefill_lines     yuv_nv12 latency in lines
 * @linear_prefill_lines       linear latency in lines
 * @करोwnscaling_prefill_lines  करोwnscaling latency in lines
 * @amortizable_theshold minimum y position क्रम traffic shaping prefill
 * @min_prefill_lines  minimum pipeline latency in lines
 * @clk_inefficiency_factor DPU src घड़ी inefficiency factor
 * @bw_inefficiency_factor DPU axi bus bw inefficiency factor
 * @safe_lut_tbl: LUT tables क्रम safe संकेतs
 * @danger_lut_tbl: LUT tables क्रम danger संकेतs
 * @qos_lut_tbl: LUT tables क्रम QoS संकेतs
 * @cdp_cfg            cdp use हाल configurations
 */
काष्ठा dpu_perf_cfg अणु
	u32 max_bw_low;
	u32 max_bw_high;
	u32 min_core_ib;
	u32 min_llcc_ib;
	u32 min_dram_ib;
	स्थिर अक्षर *core_ib_ff;
	स्थिर अक्षर *core_clk_ff;
	स्थिर अक्षर *comp_ratio_rt;
	स्थिर अक्षर *comp_ratio_nrt;
	u32 undersized_prefill_lines;
	u32 xtra_prefill_lines;
	u32 dest_scale_prefill_lines;
	u32 macrotile_prefill_lines;
	u32 yuv_nv12_prefill_lines;
	u32 linear_prefill_lines;
	u32 करोwnscaling_prefill_lines;
	u32 amortizable_threshold;
	u32 min_prefill_lines;
	u32 clk_inefficiency_factor;
	u32 bw_inefficiency_factor;
	u32 safe_lut_tbl[DPU_QOS_LUT_USAGE_MAX];
	u32 danger_lut_tbl[DPU_QOS_LUT_USAGE_MAX];
	काष्ठा dpu_qos_lut_tbl qos_lut_tbl[DPU_QOS_LUT_USAGE_MAX];
	काष्ठा dpu_perf_cdp_cfg cdp_cfg[DPU_PERF_CDP_USAGE_MAX];
पूर्ण;

/**
 * काष्ठा dpu_mdss_cfg - inक्रमmation of MDSS HW
 * This is the मुख्य catalog data काष्ठाure representing
 * this HW version. Contains number of instances,
 * रेजिस्टर offsets, capabilities of the all MDSS HW sub-blocks.
 *
 * @dma_क्रमmats        Supported क्रमmats क्रम dma pipe
 * @cursor_क्रमmats     Supported क्रमmats क्रम cursor pipe
 * @vig_क्रमmats        Supported क्रमmats क्रम vig pipe
 * @mdss_irqs:         Biपंचांगap with the irqs supported by the target
 * @obsolete_irq:       Irq types that are obsolete क्रम a particular target
 */
काष्ठा dpu_mdss_cfg अणु
	u32 hwversion;

	स्थिर काष्ठा dpu_caps *caps;

	u32 mdp_count;
	स्थिर काष्ठा dpu_mdp_cfg *mdp;

	u32 ctl_count;
	स्थिर काष्ठा dpu_ctl_cfg *ctl;

	u32 sspp_count;
	स्थिर काष्ठा dpu_sspp_cfg *sspp;

	u32 mixer_count;
	स्थिर काष्ठा dpu_lm_cfg *mixer;

	u32 pingpong_count;
	स्थिर काष्ठा dpu_pingpong_cfg *pingpong;

	u32 merge_3d_count;
	स्थिर काष्ठा dpu_merge_3d_cfg *merge_3d;

	u32 पूर्णांकf_count;
	स्थिर काष्ठा dpu_पूर्णांकf_cfg *पूर्णांकf;

	u32 vbअगर_count;
	स्थिर काष्ठा dpu_vbअगर_cfg *vbअगर;

	u32 reg_dma_count;
	काष्ठा dpu_reg_dma_cfg dma_cfg;

	u32 ad_count;

	u32 dspp_count;
	स्थिर काष्ठा dpu_dspp_cfg *dspp;

	/* Add additional block data काष्ठाures here */

	काष्ठा dpu_perf_cfg perf;
	स्थिर काष्ठा dpu_क्रमmat_extended *dma_क्रमmats;
	स्थिर काष्ठा dpu_क्रमmat_extended *cursor_क्रमmats;
	स्थिर काष्ठा dpu_क्रमmat_extended *vig_क्रमmats;

	अचिन्हित दीर्घ mdss_irqs;
	अचिन्हित दीर्घ obsolete_irq;
पूर्ण;

काष्ठा dpu_mdss_hw_cfg_handler अणु
	u32 hw_rev;
	व्योम (*cfg_init)(काष्ठा dpu_mdss_cfg *dpu_cfg);
पूर्ण;

/*
 * Access Macros
 */
#घोषणा BLK_MDP(s) ((s)->mdp)
#घोषणा BLK_CTL(s) ((s)->ctl)
#घोषणा BLK_VIG(s) ((s)->vig)
#घोषणा BLK_RGB(s) ((s)->rgb)
#घोषणा BLK_DMA(s) ((s)->dma)
#घोषणा BLK_CURSOR(s) ((s)->cursor)
#घोषणा BLK_MIXER(s) ((s)->mixer)
#घोषणा BLK_PINGPONG(s) ((s)->pingpong)
#घोषणा BLK_INTF(s) ((s)->पूर्णांकf)
#घोषणा BLK_AD(s) ((s)->ad)
#घोषणा BLK_DSPP(s) ((s)->dspp)
#घोषणा BLK_MERGE3d(s) ((s)->merge_3d)

/**
 * dpu_hw_catalog_init - dpu hardware catalog init API retrieves
 * hardcoded target specअगरic catalog inक्रमmation in config काष्ठाure
 * @hw_rev:       caller needs provide the hardware revision.
 *
 * Return: dpu config काष्ठाure
 */
काष्ठा dpu_mdss_cfg *dpu_hw_catalog_init(u32 hw_rev);

/**
 * dpu_hw_catalog_deinit - dpu hardware catalog cleanup
 * @dpu_cfg:      poपूर्णांकer वापसed from init function
 */
व्योम dpu_hw_catalog_deinit(काष्ठा dpu_mdss_cfg *dpu_cfg);

#पूर्ण_अगर /* _DPU_HW_CATALOG_H */
