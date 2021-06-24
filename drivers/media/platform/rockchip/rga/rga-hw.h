<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Jacob Chen <jacob-chen@iotwrt.com>
 */
#अगर_अघोषित __RGA_HW_H__
#घोषणा __RGA_HW_H__

#घोषणा RGA_CMDBUF_SIZE 0x20

/* Hardware limits */
#घोषणा MAX_WIDTH 8192
#घोषणा MAX_HEIGHT 8192

#घोषणा MIN_WIDTH 34
#घोषणा MIN_HEIGHT 34

#घोषणा DEFAULT_WIDTH 100
#घोषणा DEFAULT_HEIGHT 100

#घोषणा RGA_TIMEOUT 500

/* Registers address */
#घोषणा RGA_SYS_CTRL 0x0000
#घोषणा RGA_CMD_CTRL 0x0004
#घोषणा RGA_CMD_BASE 0x0008
#घोषणा RGA_INT 0x0010
#घोषणा RGA_MMU_CTRL0 0x0014
#घोषणा RGA_VERSION_INFO 0x0028

#घोषणा RGA_MODE_BASE_REG 0x0100
#घोषणा RGA_MODE_MAX_REG 0x017C

#घोषणा RGA_MODE_CTRL 0x0100
#घोषणा RGA_SRC_INFO 0x0104
#घोषणा RGA_SRC_Y_RGB_BASE_ADDR 0x0108
#घोषणा RGA_SRC_CB_BASE_ADDR 0x010c
#घोषणा RGA_SRC_CR_BASE_ADDR 0x0110
#घोषणा RGA_SRC1_RGB_BASE_ADDR 0x0114
#घोषणा RGA_SRC_VIR_INFO 0x0118
#घोषणा RGA_SRC_ACT_INFO 0x011c
#घोषणा RGA_SRC_X_FACTOR 0x0120
#घोषणा RGA_SRC_Y_FACTOR 0x0124
#घोषणा RGA_SRC_BG_COLOR 0x0128
#घोषणा RGA_SRC_FG_COLOR 0x012c
#घोषणा RGA_SRC_TR_COLOR0 0x0130
#घोषणा RGA_SRC_TR_COLOR1 0x0134

#घोषणा RGA_DST_INFO 0x0138
#घोषणा RGA_DST_Y_RGB_BASE_ADDR 0x013c
#घोषणा RGA_DST_CB_BASE_ADDR 0x0140
#घोषणा RGA_DST_CR_BASE_ADDR 0x0144
#घोषणा RGA_DST_VIR_INFO 0x0148
#घोषणा RGA_DST_ACT_INFO 0x014c

#घोषणा RGA_ALPHA_CTRL0 0x0150
#घोषणा RGA_ALPHA_CTRL1 0x0154
#घोषणा RGA_FADING_CTRL 0x0158
#घोषणा RGA_PAT_CON 0x015c
#घोषणा RGA_ROP_CON0 0x0160
#घोषणा RGA_ROP_CON1 0x0164
#घोषणा RGA_MASK_BASE 0x0168

#घोषणा RGA_MMU_CTRL1 0x016C
#घोषणा RGA_MMU_SRC_BASE 0x0170
#घोषणा RGA_MMU_SRC1_BASE 0x0174
#घोषणा RGA_MMU_DST_BASE 0x0178

/* Registers value */
#घोषणा RGA_MODE_RENDER_BITBLT 0
#घोषणा RGA_MODE_RENDER_COLOR_PALETTE 1
#घोषणा RGA_MODE_RENDER_RECTANGLE_FILL 2
#घोषणा RGA_MODE_RENDER_UPDATE_PALETTE_LUT_RAM 3

#घोषणा RGA_MODE_BITBLT_MODE_SRC_TO_DST 0
#घोषणा RGA_MODE_BITBLT_MODE_SRC_SRC1_TO_DST 1

#घोषणा RGA_MODE_CF_ROP4_SOLID 0
#घोषणा RGA_MODE_CF_ROP4_PATTERN 1

#घोषणा RGA_COLOR_FMT_ABGR8888 0
#घोषणा RGA_COLOR_FMT_XBGR8888 1
#घोषणा RGA_COLOR_FMT_RGB888 2
#घोषणा RGA_COLOR_FMT_BGR565 4
#घोषणा RGA_COLOR_FMT_ABGR1555 5
#घोषणा RGA_COLOR_FMT_ABGR4444 6
#घोषणा RGA_COLOR_FMT_YUV422SP 8
#घोषणा RGA_COLOR_FMT_YUV422P 9
#घोषणा RGA_COLOR_FMT_YUV420SP 10
#घोषणा RGA_COLOR_FMT_YUV420P 11
/* SRC_COLOR Palette */
#घोषणा RGA_COLOR_FMT_CP_1BPP 12
#घोषणा RGA_COLOR_FMT_CP_2BPP 13
#घोषणा RGA_COLOR_FMT_CP_4BPP 14
#घोषणा RGA_COLOR_FMT_CP_8BPP 15
#घोषणा RGA_COLOR_FMT_MASK 15

#घोषणा RGA_COLOR_FMT_IS_YUV(fmt) \
	(((fmt) >= RGA_COLOR_FMT_YUV422SP) && ((fmt) < RGA_COLOR_FMT_CP_1BPP))
#घोषणा RGA_COLOR_FMT_IS_RGB(fmt) \
	((fmt) < RGA_COLOR_FMT_YUV422SP)

#घोषणा RGA_COLOR_NONE_SWAP 0
#घोषणा RGA_COLOR_RB_SWAP 1
#घोषणा RGA_COLOR_ALPHA_SWAP 2
#घोषणा RGA_COLOR_UV_SWAP 4

#घोषणा RGA_SRC_CSC_MODE_BYPASS 0
#घोषणा RGA_SRC_CSC_MODE_BT601_R0 1
#घोषणा RGA_SRC_CSC_MODE_BT601_R1 2
#घोषणा RGA_SRC_CSC_MODE_BT709_R0 3
#घोषणा RGA_SRC_CSC_MODE_BT709_R1 4

#घोषणा RGA_SRC_ROT_MODE_0_DEGREE 0
#घोषणा RGA_SRC_ROT_MODE_90_DEGREE 1
#घोषणा RGA_SRC_ROT_MODE_180_DEGREE 2
#घोषणा RGA_SRC_ROT_MODE_270_DEGREE 3

#घोषणा RGA_SRC_MIRR_MODE_NO 0
#घोषणा RGA_SRC_MIRR_MODE_X 1
#घोषणा RGA_SRC_MIRR_MODE_Y 2
#घोषणा RGA_SRC_MIRR_MODE_X_Y 3

#घोषणा RGA_SRC_HSCL_MODE_NO 0
#घोषणा RGA_SRC_HSCL_MODE_DOWN 1
#घोषणा RGA_SRC_HSCL_MODE_UP 2

#घोषणा RGA_SRC_VSCL_MODE_NO 0
#घोषणा RGA_SRC_VSCL_MODE_DOWN 1
#घोषणा RGA_SRC_VSCL_MODE_UP 2

#घोषणा RGA_SRC_TRANS_ENABLE_R 1
#घोषणा RGA_SRC_TRANS_ENABLE_G 2
#घोषणा RGA_SRC_TRANS_ENABLE_B 4
#घोषणा RGA_SRC_TRANS_ENABLE_A 8

#घोषणा RGA_SRC_BIC_COE_SELEC_CATROM 0
#घोषणा RGA_SRC_BIC_COE_SELEC_MITCHELL 1
#घोषणा RGA_SRC_BIC_COE_SELEC_HERMITE 2
#घोषणा RGA_SRC_BIC_COE_SELEC_BSPLINE 3

#घोषणा RGA_DST_DITHER_MODE_888_TO_666 0
#घोषणा RGA_DST_DITHER_MODE_888_TO_565 1
#घोषणा RGA_DST_DITHER_MODE_888_TO_555 2
#घोषणा RGA_DST_DITHER_MODE_888_TO_444 3

#घोषणा RGA_DST_CSC_MODE_BYPASS 0
#घोषणा RGA_DST_CSC_MODE_BT601_R0 1
#घोषणा RGA_DST_CSC_MODE_BT601_R1 2
#घोषणा RGA_DST_CSC_MODE_BT709_R0 3

#घोषणा RGA_ALPHA_ROP_MODE_2 0
#घोषणा RGA_ALPHA_ROP_MODE_3 1
#घोषणा RGA_ALPHA_ROP_MODE_4 2

#घोषणा RGA_ALPHA_SELECT_ALPHA 0
#घोषणा RGA_ALPHA_SELECT_ROP 1

#घोषणा RGA_ALPHA_MASK_BIG_ENDIAN 0
#घोषणा RGA_ALPHA_MASK_LITTLE_ENDIAN 1

#घोषणा RGA_ALPHA_NORMAL 0
#घोषणा RGA_ALPHA_REVERSE 1

#घोषणा RGA_ALPHA_BLEND_GLOBAL 0
#घोषणा RGA_ALPHA_BLEND_NORMAL 1
#घोषणा RGA_ALPHA_BLEND_MULTIPLY 2

#घोषणा RGA_ALPHA_CAL_CUT 0
#घोषणा RGA_ALPHA_CAL_NORMAL 1

#घोषणा RGA_ALPHA_FACTOR_ZERO 0
#घोषणा RGA_ALPHA_FACTOR_ONE 1
#घोषणा RGA_ALPHA_FACTOR_OTHER 2
#घोषणा RGA_ALPHA_FACTOR_OTHER_REVERSE 3
#घोषणा RGA_ALPHA_FACTOR_SELF 4

#घोषणा RGA_ALPHA_COLOR_NORMAL 0
#घोषणा RGA_ALPHA_COLOR_MULTIPLY_CAL 1

/* Registers जोड़ */
जोड़ rga_mode_ctrl अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:2] */
		अचिन्हित पूर्णांक render:3;
		/* [3:6] */
		अचिन्हित पूर्णांक bitblt:1;
		अचिन्हित पूर्णांक cf_rop4_pat:1;
		अचिन्हित पूर्णांक alpha_zero_key:1;
		अचिन्हित पूर्णांक gradient_sat:1;
		/* [7:31] */
		अचिन्हित पूर्णांक reserved:25;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:3] */
		अचिन्हित पूर्णांक क्रमmat:4;
		/* [4:7] */
		अचिन्हित पूर्णांक swap:3;
		अचिन्हित पूर्णांक cp_endian:1;
		/* [8:17] */
		अचिन्हित पूर्णांक csc_mode:2;
		अचिन्हित पूर्णांक rot_mode:2;
		अचिन्हित पूर्णांक mir_mode:2;
		अचिन्हित पूर्णांक hscl_mode:2;
		अचिन्हित पूर्णांक vscl_mode:2;
		/* [18:22] */
		अचिन्हित पूर्णांक trans_mode:1;
		अचिन्हित पूर्णांक trans_enable:4;
		/* [23:25] */
		अचिन्हित पूर्णांक dither_up_en:1;
		अचिन्हित पूर्णांक bic_coe_sel:2;
		/* [26:31] */
		अचिन्हित पूर्णांक reserved:6;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_vir_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक vir_width:15;
		अचिन्हित पूर्णांक reserved:1;
		/* [16:25] */
		अचिन्हित पूर्णांक vir_stride:10;
		/* [26:31] */
		अचिन्हित पूर्णांक reserved1:6;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_act_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक act_width:13;
		अचिन्हित पूर्णांक reserved:3;
		/* [16:31] */
		अचिन्हित पूर्णांक act_height:13;
		अचिन्हित पूर्णांक reserved1:3;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_x_factor अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक करोwn_scale_factor:16;
		/* [16:31] */
		अचिन्हित पूर्णांक up_scale_factor:16;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_y_factor अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक करोwn_scale_factor:16;
		/* [16:31] */
		अचिन्हित पूर्णांक up_scale_factor:16;
	पूर्ण data;
पूर्ण;

/* Alpha / Red / Green / Blue */
जोड़ rga_src_cp_gr_color अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक gradient_x:16;
		/* [16:31] */
		अचिन्हित पूर्णांक gradient_y:16;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_transparency_color0 अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:7] */
		अचिन्हित पूर्णांक trans_rmin:8;
		/* [8:15] */
		अचिन्हित पूर्णांक trans_gmin:8;
		/* [16:23] */
		अचिन्हित पूर्णांक trans_bmin:8;
		/* [24:31] */
		अचिन्हित पूर्णांक trans_amin:8;
	पूर्ण data;
पूर्ण;

जोड़ rga_src_transparency_color1 अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:7] */
		अचिन्हित पूर्णांक trans_rmax:8;
		/* [8:15] */
		अचिन्हित पूर्णांक trans_gmax:8;
		/* [16:23] */
		अचिन्हित पूर्णांक trans_bmax:8;
		/* [24:31] */
		अचिन्हित पूर्णांक trans_amax:8;
	पूर्ण data;
पूर्ण;

जोड़ rga_dst_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:3] */
		अचिन्हित पूर्णांक क्रमmat:4;
		/* [4:6] */
		अचिन्हित पूर्णांक swap:3;
		/* [7:9] */
		अचिन्हित पूर्णांक src1_क्रमmat:3;
		/* [10:11] */
		अचिन्हित पूर्णांक src1_swap:2;
		/* [12:15] */
		अचिन्हित पूर्णांक dither_up_en:1;
		अचिन्हित पूर्णांक dither_करोwn_en:1;
		अचिन्हित पूर्णांक dither_करोwn_mode:2;
		/* [16:18] */
		अचिन्हित पूर्णांक csc_mode:2;
		अचिन्हित पूर्णांक csc_clip:1;
		/* [19:31] */
		अचिन्हित पूर्णांक reserved:13;
	पूर्ण data;
पूर्ण;

जोड़ rga_dst_vir_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक vir_stride:15;
		अचिन्हित पूर्णांक reserved:1;
		/* [16:31] */
		अचिन्हित पूर्णांक src1_vir_stride:15;
		अचिन्हित पूर्णांक reserved1:1;
	पूर्ण data;
पूर्ण;

जोड़ rga_dst_act_info अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:15] */
		अचिन्हित पूर्णांक act_width:12;
		अचिन्हित पूर्णांक reserved:4;
		/* [16:31] */
		अचिन्हित पूर्णांक act_height:12;
		अचिन्हित पूर्णांक reserved1:4;
	पूर्ण data;
पूर्ण;

जोड़ rga_alpha_ctrl0 अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:3] */
		अचिन्हित पूर्णांक rop_en:1;
		अचिन्हित पूर्णांक rop_select:1;
		अचिन्हित पूर्णांक rop_mode:2;
		/* [4:11] */
		अचिन्हित पूर्णांक src_fading_val:8;
		/* [12:20] */
		अचिन्हित पूर्णांक dst_fading_val:8;
		अचिन्हित पूर्णांक mask_endian:1;
		/* [21:31] */
		अचिन्हित पूर्णांक reserved:11;
	पूर्ण data;
पूर्ण;

जोड़ rga_alpha_ctrl1 अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:1] */
		अचिन्हित पूर्णांक dst_color_m0:1;
		अचिन्हित पूर्णांक src_color_m0:1;
		/* [2:7] */
		अचिन्हित पूर्णांक dst_factor_m0:3;
		अचिन्हित पूर्णांक src_factor_m0:3;
		/* [8:9] */
		अचिन्हित पूर्णांक dst_alpha_cal_m0:1;
		अचिन्हित पूर्णांक src_alpha_cal_m0:1;
		/* [10:13] */
		अचिन्हित पूर्णांक dst_blend_m0:2;
		अचिन्हित पूर्णांक src_blend_m0:2;
		/* [14:15] */
		अचिन्हित पूर्णांक dst_alpha_m0:1;
		अचिन्हित पूर्णांक src_alpha_m0:1;
		/* [16:21] */
		अचिन्हित पूर्णांक dst_factor_m1:3;
		अचिन्हित पूर्णांक src_factor_m1:3;
		/* [22:23] */
		अचिन्हित पूर्णांक dst_alpha_cal_m1:1;
		अचिन्हित पूर्णांक src_alpha_cal_m1:1;
		/* [24:27] */
		अचिन्हित पूर्णांक dst_blend_m1:2;
		अचिन्हित पूर्णांक src_blend_m1:2;
		/* [28:29] */
		अचिन्हित पूर्णांक dst_alpha_m1:1;
		अचिन्हित पूर्णांक src_alpha_m1:1;
		/* [30:31] */
		अचिन्हित पूर्णांक reserved:2;
	पूर्ण data;
पूर्ण;

जोड़ rga_fading_ctrl अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:7] */
		अचिन्हित पूर्णांक fading_offset_r:8;
		/* [8:15] */
		अचिन्हित पूर्णांक fading_offset_g:8;
		/* [16:23] */
		अचिन्हित पूर्णांक fading_offset_b:8;
		/* [24:31] */
		अचिन्हित पूर्णांक fading_en:1;
		अचिन्हित पूर्णांक reserved:7;
	पूर्ण data;
पूर्ण;

जोड़ rga_pat_con अणु
	अचिन्हित पूर्णांक val;
	काष्ठा अणु
		/* [0:7] */
		अचिन्हित पूर्णांक width:8;
		/* [8:15] */
		अचिन्हित पूर्णांक height:8;
		/* [16:23] */
		अचिन्हित पूर्णांक offset_x:8;
		/* [24:31] */
		अचिन्हित पूर्णांक offset_y:8;
	पूर्ण data;
पूर्ण;

#पूर्ण_अगर
