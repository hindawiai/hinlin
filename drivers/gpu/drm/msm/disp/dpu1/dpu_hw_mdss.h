<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_MDSS_H
#घोषणा _DPU_HW_MDSS_H

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>

#समावेश "msm_drv.h"

#घोषणा DPU_DBG_NAME			"dpu"

#घोषणा DPU_NONE                        0

#अगर_अघोषित DPU_CSC_MATRIX_COEFF_SIZE
#घोषणा DPU_CSC_MATRIX_COEFF_SIZE	9
#पूर्ण_अगर

#अगर_अघोषित DPU_CSC_CLAMP_SIZE
#घोषणा DPU_CSC_CLAMP_SIZE		6
#पूर्ण_अगर

#अगर_अघोषित DPU_CSC_BIAS_SIZE
#घोषणा DPU_CSC_BIAS_SIZE		3
#पूर्ण_अगर

#अगर_अघोषित DPU_MAX_PLANES
#घोषणा DPU_MAX_PLANES			4
#पूर्ण_अगर

#घोषणा PIPES_PER_STAGE			2
#अगर_अघोषित DPU_MAX_DE_CURVES
#घोषणा DPU_MAX_DE_CURVES		3
#पूर्ण_अगर

क्रमागत dpu_क्रमmat_flags अणु
	DPU_FORMAT_FLAG_YUV_BIT,
	DPU_FORMAT_FLAG_DX_BIT,
	DPU_FORMAT_FLAG_COMPRESSED_BIT,
	DPU_FORMAT_FLAG_BIT_MAX,
पूर्ण;

#घोषणा DPU_FORMAT_FLAG_YUV		BIT(DPU_FORMAT_FLAG_YUV_BIT)
#घोषणा DPU_FORMAT_FLAG_DX		BIT(DPU_FORMAT_FLAG_DX_BIT)
#घोषणा DPU_FORMAT_FLAG_COMPRESSED	BIT(DPU_FORMAT_FLAG_COMPRESSED_BIT)
#घोषणा DPU_FORMAT_IS_YUV(X)		\
	(test_bit(DPU_FORMAT_FLAG_YUV_BIT, (X)->flag))
#घोषणा DPU_FORMAT_IS_DX(X)		\
	(test_bit(DPU_FORMAT_FLAG_DX_BIT, (X)->flag))
#घोषणा DPU_FORMAT_IS_LINEAR(X)		((X)->fetch_mode == DPU_FETCH_LINEAR)
#घोषणा DPU_FORMAT_IS_TILE(X) \
	(((X)->fetch_mode == DPU_FETCH_UBWC) && \
			!test_bit(DPU_FORMAT_FLAG_COMPRESSED_BIT, (X)->flag))
#घोषणा DPU_FORMAT_IS_UBWC(X) \
	(((X)->fetch_mode == DPU_FETCH_UBWC) && \
			test_bit(DPU_FORMAT_FLAG_COMPRESSED_BIT, (X)->flag))

#घोषणा DPU_BLEND_FG_ALPHA_FG_CONST	(0 << 0)
#घोषणा DPU_BLEND_FG_ALPHA_BG_CONST	(1 << 0)
#घोषणा DPU_BLEND_FG_ALPHA_FG_PIXEL	(2 << 0)
#घोषणा DPU_BLEND_FG_ALPHA_BG_PIXEL	(3 << 0)
#घोषणा DPU_BLEND_FG_INV_ALPHA		(1 << 2)
#घोषणा DPU_BLEND_FG_MOD_ALPHA		(1 << 3)
#घोषणा DPU_BLEND_FG_INV_MOD_ALPHA	(1 << 4)
#घोषणा DPU_BLEND_FG_TRANSP_EN		(1 << 5)
#घोषणा DPU_BLEND_BG_ALPHA_FG_CONST	(0 << 8)
#घोषणा DPU_BLEND_BG_ALPHA_BG_CONST	(1 << 8)
#घोषणा DPU_BLEND_BG_ALPHA_FG_PIXEL	(2 << 8)
#घोषणा DPU_BLEND_BG_ALPHA_BG_PIXEL	(3 << 8)
#घोषणा DPU_BLEND_BG_INV_ALPHA		(1 << 10)
#घोषणा DPU_BLEND_BG_MOD_ALPHA		(1 << 11)
#घोषणा DPU_BLEND_BG_INV_MOD_ALPHA	(1 << 12)
#घोषणा DPU_BLEND_BG_TRANSP_EN		(1 << 13)

#घोषणा DPU_VSYNC0_SOURCE_GPIO		0
#घोषणा DPU_VSYNC1_SOURCE_GPIO		1
#घोषणा DPU_VSYNC2_SOURCE_GPIO		2
#घोषणा DPU_VSYNC_SOURCE_INTF_0		3
#घोषणा DPU_VSYNC_SOURCE_INTF_1		4
#घोषणा DPU_VSYNC_SOURCE_INTF_2		5
#घोषणा DPU_VSYNC_SOURCE_INTF_3		6
#घोषणा DPU_VSYNC_SOURCE_WD_TIMER_4	11
#घोषणा DPU_VSYNC_SOURCE_WD_TIMER_3	12
#घोषणा DPU_VSYNC_SOURCE_WD_TIMER_2	13
#घोषणा DPU_VSYNC_SOURCE_WD_TIMER_1	14
#घोषणा DPU_VSYNC_SOURCE_WD_TIMER_0	15

क्रमागत dpu_hw_blk_type अणु
	DPU_HW_BLK_TOP = 0,
	DPU_HW_BLK_SSPP,
	DPU_HW_BLK_LM,
	DPU_HW_BLK_CTL,
	DPU_HW_BLK_PINGPONG,
	DPU_HW_BLK_INTF,
	DPU_HW_BLK_WB,
	DPU_HW_BLK_DSPP,
	DPU_HW_BLK_MERGE_3D,
	DPU_HW_BLK_MAX,
पूर्ण;

क्रमागत dpu_mdp अणु
	MDP_TOP = 0x1,
	MDP_MAX,
पूर्ण;

क्रमागत dpu_sspp अणु
	SSPP_NONE,
	SSPP_VIG0,
	SSPP_VIG1,
	SSPP_VIG2,
	SSPP_VIG3,
	SSPP_RGB0,
	SSPP_RGB1,
	SSPP_RGB2,
	SSPP_RGB3,
	SSPP_DMA0,
	SSPP_DMA1,
	SSPP_DMA2,
	SSPP_DMA3,
	SSPP_CURSOR0,
	SSPP_CURSOR1,
	SSPP_MAX
पूर्ण;

क्रमागत dpu_sspp_type अणु
	SSPP_TYPE_VIG,
	SSPP_TYPE_RGB,
	SSPP_TYPE_DMA,
	SSPP_TYPE_CURSOR,
	SSPP_TYPE_MAX
पूर्ण;

क्रमागत dpu_lm अणु
	LM_0 = 1,
	LM_1,
	LM_2,
	LM_3,
	LM_4,
	LM_5,
	LM_6,
	LM_MAX
पूर्ण;

क्रमागत dpu_stage अणु
	DPU_STAGE_BASE = 0,
	DPU_STAGE_0,
	DPU_STAGE_1,
	DPU_STAGE_2,
	DPU_STAGE_3,
	DPU_STAGE_4,
	DPU_STAGE_5,
	DPU_STAGE_6,
	DPU_STAGE_7,
	DPU_STAGE_8,
	DPU_STAGE_9,
	DPU_STAGE_10,
	DPU_STAGE_MAX
पूर्ण;
क्रमागत dpu_dspp अणु
	DSPP_0 = 1,
	DSPP_1,
	DSPP_2,
	DSPP_3,
	DSPP_MAX
पूर्ण;

क्रमागत dpu_ctl अणु
	CTL_0 = 1,
	CTL_1,
	CTL_2,
	CTL_3,
	CTL_4,
	CTL_5,
	CTL_MAX
पूर्ण;

क्रमागत dpu_pingpong अणु
	PINGPONG_0 = 1,
	PINGPONG_1,
	PINGPONG_2,
	PINGPONG_3,
	PINGPONG_4,
	PINGPONG_5,
	PINGPONG_S0,
	PINGPONG_MAX
पूर्ण;

क्रमागत dpu_merge_3d अणु
	MERGE_3D_0 = 1,
	MERGE_3D_1,
	MERGE_3D_2,
	MERGE_3D_MAX
पूर्ण;

क्रमागत dpu_पूर्णांकf अणु
	INTF_0 = 1,
	INTF_1,
	INTF_2,
	INTF_3,
	INTF_4,
	INTF_5,
	INTF_6,
	INTF_MAX
पूर्ण;

क्रमागत dpu_पूर्णांकf_type अणु
	INTF_NONE = 0x0,
	INTF_DSI = 0x1,
	INTF_HDMI = 0x3,
	INTF_LCDC = 0x5,
	INTF_EDP = 0x9,
	INTF_DP = 0xa,
	INTF_TYPE_MAX,

	/* भव पूर्णांकerfaces */
	INTF_WB = 0x100,
पूर्ण;

क्रमागत dpu_पूर्णांकf_mode अणु
	INTF_MODE_NONE = 0,
	INTF_MODE_CMD,
	INTF_MODE_VIDEO,
	INTF_MODE_WB_BLOCK,
	INTF_MODE_WB_LINE,
	INTF_MODE_MAX
पूर्ण;

क्रमागत dpu_wb अणु
	WB_0 = 1,
	WB_1,
	WB_2,
	WB_3,
	WB_MAX
पूर्ण;

क्रमागत dpu_cwb अणु
	CWB_0 = 0x1,
	CWB_1,
	CWB_2,
	CWB_3,
	CWB_MAX
पूर्ण;

क्रमागत dpu_wd_समयr अणु
	WD_TIMER_0 = 0x1,
	WD_TIMER_1,
	WD_TIMER_2,
	WD_TIMER_3,
	WD_TIMER_4,
	WD_TIMER_5,
	WD_TIMER_MAX
पूर्ण;

क्रमागत dpu_vbअगर अणु
	VBIF_0,
	VBIF_1,
	VBIF_MAX,
	VBIF_RT = VBIF_0,
	VBIF_NRT = VBIF_1
पूर्ण;

/**
 * DPU HW,Component order color map
 */
क्रमागत अणु
	C0_G_Y = 0,
	C1_B_Cb = 1,
	C2_R_Cr = 2,
	C3_ALPHA = 3
पूर्ण;

/**
 * क्रमागत dpu_plane_type - defines how the color component pixel packing
 * @DPU_PLANE_INTERLEAVED   : Color components in single plane
 * @DPU_PLANE_PLANAR        : Color component in separate planes
 * @DPU_PLANE_PSEUDO_PLANAR : Chroma components पूर्णांकerleaved in separate plane
 */
क्रमागत dpu_plane_type अणु
	DPU_PLANE_INTERLEAVED,
	DPU_PLANE_PLANAR,
	DPU_PLANE_PSEUDO_PLANAR,
पूर्ण;

/**
 * क्रमागत dpu_chroma_samp_type - chroma sub-samplng type
 * @DPU_CHROMA_RGB   : No chroma subsampling
 * @DPU_CHROMA_H2V1  : Chroma pixels are horizontally subsampled
 * @DPU_CHROMA_H1V2  : Chroma pixels are vertically subsampled
 * @DPU_CHROMA_420   : 420 subsampling
 */
क्रमागत dpu_chroma_samp_type अणु
	DPU_CHROMA_RGB,
	DPU_CHROMA_H2V1,
	DPU_CHROMA_H1V2,
	DPU_CHROMA_420
पूर्ण;

/**
 * dpu_fetch_type - Defines How DPU HW fetches data
 * @DPU_FETCH_LINEAR   : fetch is line by line
 * @DPU_FETCH_TILE     : fetches data in Z order from a tile
 * @DPU_FETCH_UBWC     : fetch and decompress data
 */
क्रमागत dpu_fetch_type अणु
	DPU_FETCH_LINEAR,
	DPU_FETCH_TILE,
	DPU_FETCH_UBWC
पूर्ण;

/**
 * Value of क्रमागत chosen to fit the number of bits
 * expected by the HW programming.
 */
क्रमागत अणु
	COLOR_ALPHA_1BIT = 0,
	COLOR_ALPHA_4BIT = 1,
	COLOR_4BIT = 0,
	COLOR_5BIT = 1, /* No 5-bit Alpha */
	COLOR_6BIT = 2, /* 6-Bit Alpha also = 2 */
	COLOR_8BIT = 3, /* 8-Bit Alpha also = 3 */
पूर्ण;

/**
 * क्रमागत dpu_3d_blend_mode
 * Desribes how the 3d data is blended
 * @BLEND_3D_NONE      : 3d blending not enabled
 * @BLEND_3D_FRAME_INT : Frame पूर्णांकerleaving
 * @BLEND_3D_H_ROW_INT : Horizontal row पूर्णांकerleaving
 * @BLEND_3D_V_ROW_INT : vertical row पूर्णांकerleaving
 * @BLEND_3D_COL_INT   : column पूर्णांकerleaving
 * @BLEND_3D_MAX       :
 */
क्रमागत dpu_3d_blend_mode अणु
	BLEND_3D_NONE = 0,
	BLEND_3D_FRAME_INT,
	BLEND_3D_H_ROW_INT,
	BLEND_3D_V_ROW_INT,
	BLEND_3D_COL_INT,
	BLEND_3D_MAX
पूर्ण;

/** काष्ठा dpu_क्रमmat - defines the क्रमmat configuration which
 * allows DPU HW to correctly fetch and decode the क्रमmat
 * @base: base msm_क्रमmat struture containing fourcc code
 * @fetch_planes: how the color components are packed in pixel क्रमmat
 * @element: element color ordering
 * @bits: element bit widths
 * @chroma_sample: chroma sub-samplng type
 * @unpack_align_msb: unpack aligned, 0 to LSB, 1 to MSB
 * @unpack_tight: 0 क्रम loose, 1 क्रम tight
 * @unpack_count: 0 = 1 component, 1 = 2 component
 * @bpp: bytes per pixel
 * @alpha_enable: whether the क्रमmat has an alpha channel
 * @num_planes: number of planes (including meta data planes)
 * @fetch_mode: linear, tiled, or ubwc hw fetch behavior
 * @flag: usage bit flags
 * @tile_width: क्रमmat tile width
 * @tile_height: क्रमmat tile height
 */
काष्ठा dpu_क्रमmat अणु
	काष्ठा msm_क्रमmat base;
	क्रमागत dpu_plane_type fetch_planes;
	u8 element[DPU_MAX_PLANES];
	u8 bits[DPU_MAX_PLANES];
	क्रमागत dpu_chroma_samp_type chroma_sample;
	u8 unpack_align_msb;
	u8 unpack_tight;
	u8 unpack_count;
	u8 bpp;
	u8 alpha_enable;
	u8 num_planes;
	क्रमागत dpu_fetch_type fetch_mode;
	DECLARE_BITMAP(flag, DPU_FORMAT_FLAG_BIT_MAX);
	u16 tile_width;
	u16 tile_height;
पूर्ण;
#घोषणा to_dpu_क्रमmat(x) container_of(x, काष्ठा dpu_क्रमmat, base)

/**
 * काष्ठा dpu_hw_fmt_layout - क्रमmat inक्रमmation of the source pixel data
 * @क्रमmat: pixel क्रमmat parameters
 * @num_planes: number of planes (including meta data planes)
 * @width: image width
 * @height: image height
 * @total_size: total size in bytes
 * @plane_addr: address of each plane
 * @plane_size: length of each plane
 * @plane_pitch: pitch of each plane
 */
काष्ठा dpu_hw_fmt_layout अणु
	स्थिर काष्ठा dpu_क्रमmat *क्रमmat;
	uपूर्णांक32_t num_planes;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t total_size;
	uपूर्णांक32_t plane_addr[DPU_MAX_PLANES];
	uपूर्णांक32_t plane_size[DPU_MAX_PLANES];
	uपूर्णांक32_t plane_pitch[DPU_MAX_PLANES];
पूर्ण;

काष्ठा dpu_csc_cfg अणु
	/* matrix coefficients in S15.16 क्रमmat */
	uपूर्णांक32_t csc_mv[DPU_CSC_MATRIX_COEFF_SIZE];
	uपूर्णांक32_t csc_pre_bv[DPU_CSC_BIAS_SIZE];
	uपूर्णांक32_t csc_post_bv[DPU_CSC_BIAS_SIZE];
	uपूर्णांक32_t csc_pre_lv[DPU_CSC_CLAMP_SIZE];
	uपूर्णांक32_t csc_post_lv[DPU_CSC_CLAMP_SIZE];
पूर्ण;

/**
 * काष्ठा dpu_mdss_color - mdss color description
 * color 0 : green
 * color 1 : blue
 * color 2 : red
 * color 3 : alpha
 */
काष्ठा dpu_mdss_color अणु
	u32 color_0;
	u32 color_1;
	u32 color_2;
	u32 color_3;
पूर्ण;

/*
 * Define bit masks क्रम h/w logging.
 */
#घोषणा DPU_DBG_MASK_NONE     (1 << 0)
#घोषणा DPU_DBG_MASK_INTF     (1 << 1)
#घोषणा DPU_DBG_MASK_LM       (1 << 2)
#घोषणा DPU_DBG_MASK_CTL      (1 << 3)
#घोषणा DPU_DBG_MASK_PINGPONG (1 << 4)
#घोषणा DPU_DBG_MASK_SSPP     (1 << 5)
#घोषणा DPU_DBG_MASK_WB       (1 << 6)
#घोषणा DPU_DBG_MASK_TOP      (1 << 7)
#घोषणा DPU_DBG_MASK_VBIF     (1 << 8)
#घोषणा DPU_DBG_MASK_ROT      (1 << 9)
#घोषणा DPU_DBG_MASK_DSPP     (1 << 10)

#पूर्ण_अगर  /* _DPU_HW_MDSS_H */
